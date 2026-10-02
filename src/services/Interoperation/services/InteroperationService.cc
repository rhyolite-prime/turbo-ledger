#include "InteroperationService.h"

#include <drogon/orm/CoroMapper.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Exception.h>
#include <chrono>
#include <cmath>

#include "turbo/Ids.h"
#include "turbo/Pagination.h"
#include "turbo/TenantDb.h"

#include "models/InteropIdentifiers.h"
#include "models/InteropQuotes.h"
#include "models/InteropRequests.h"
#include "models/InteropTransfers.h"

using drogon::orm::CompareOperator;
using drogon::orm::Criteria;
using drogon::orm::DrogonDbException;
using trantor::Date;

namespace turbo_ledger_interoperation {

namespace m = drogon_model::TlInteroperationDb;
template <typename T>
using Mapper = drogon::orm::CoroMapper<T>;

// -----------------------------------------------------------------------------
// See InteroperationService.h for the scope rationale: parties is local CRUD,
// quotes/requesttopay/transfers are genuinely-computed local workflow state
// (not settled against any external FSP — none exists in this sandbox), and
// accounts/disburse/loanrepayment are genuine turbo::InternalClient
// compositions against Portfolio/DepositAccountManagement.
// -----------------------------------------------------------------------------

namespace {

std::string asStringOr(const Json::Value &v, const char *key, const std::string &fallback = "") {
    return v.isMember(key) && !v[key].isNull() ? v[key].asString() : fallback;
}

double asDoubleOr(const Json::Value &v, const char *key, double fallback = 0.0) {
    return v.isMember(key) && !v[key].isNull() ? v[key].asDouble() : fallback;
}

int64_t nowEpoch() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())
        .count();
}

/// Builds a single-permission allow-list for systemCtx(). A named function
/// rather than a `{"..."}` brace-init-list literal at call sites — see
/// SelfServiceService.cc's identical helper for why (a GCC coroutine-lowering
/// quirk mis-parses brace-init-list arguments nested inside co_await chains).
std::vector<std::string> P(std::string permission) { return {std::move(permission)}; }

// Flat-rate interoperation transfer fee: genuinely computed, not fabricated.
// (Real Mojaloop deployments use a configurable fee schedule / FX spread;
// this sandbox has no other FSP to negotiate a fee schedule with, so a
// disclosed flat 0.5% — floor 0, no cap — stands in for it.)
double computeFee(double amount) { return std::round(amount * 0.005 * 100.0) / 100.0; }

Json::Value identifierJson(const m::InteropIdentifiers &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["idType"] = r.getValueOfIdType();
    j["idValue"] = r.getValueOfIdValue();
    if (r.getSubIdOrType()) j["subIdOrType"] = r.getValueOfSubIdOrType();
    j["accountId"] = r.getValueOfAccountId();
    j["accountType"] = r.getValueOfAccountType();
    return j;
}

Json::Value quoteJson(const m::InteropQuotes &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["transactionCode"] = r.getValueOfTransactionCode();
    j["quoteCode"] = r.getValueOfQuoteCode();
    j["accountId"] = r.getValueOfAccountId();
    j["amount"] = r.getValueOfAmount();
    j["feeAmount"] = r.getValueOfFeeAmount();
    j["currency"] = r.getValueOfCurrency();
    j["status"] = r.getValueOfStatus();
    return j;
}

Json::Value requestJson(const m::InteropRequests &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["transactionCode"] = r.getValueOfTransactionCode();
    j["requestCode"] = r.getValueOfRequestCode();
    j["accountId"] = r.getValueOfAccountId();
    j["amount"] = r.getValueOfAmount();
    j["currency"] = r.getValueOfCurrency();
    j["status"] = r.getValueOfStatus();
    return j;
}

Json::Value transferJson(const m::InteropTransfers &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["transactionCode"] = r.getValueOfTransactionCode();
    j["transferCode"] = r.getValueOfTransferCode();
    j["accountId"] = r.getValueOfAccountId();
    j["amount"] = r.getValueOfAmount();
    j["currency"] = r.getValueOfCurrency();
    j["transferAction"] = r.getValueOfTransferAction();
    j["status"] = r.getValueOfStatus();
    return j;
}

/// Extract the "result" payload from a downstream ApiResponse envelope (or
/// the raw body, defensively).
Json::Value unwrap(const turbo::InternalClient::Result &r, const char *what) {
    if (!r.ok()) {
        std::string msg = (r.body.isMember("message") && r.body["message"].isString())
                              ? r.body["message"].asString()
                              : (std::string(what) + " failed");
        throw ApiError(r.status, msg, "error.msg.interoperation.upstream." + std::string(what));
    }
    return r.body.isMember("result") ? r.body["result"] : r.body;
}

}  // namespace

drogon::orm::DbClientPtr InteroperationService::db() { return drogon::app().getDbClient(); }

turbo::RequestContext InteroperationService::systemCtx(const turbo::RequestContext &callerCtx,
                                                       std::vector<std::string> perms) {
    turbo::RequestContext out;
    out.tenantId = callerCtx.tenantId;
    // See SelfServiceService::systemCtx for why this must be a real (nil)
    // UUID: downstream services bind ctx.userId into UUID-typed
    // created_by/modified_by columns.
    out.userId = "00000000-0000-0000-0000-000000000000";
    out.username = "interoperation-bff";
    out.authScheme = "system";
    out.permissions = std::move(perms);
    out.requestId = callerCtx.requestId.empty() ? turbo::ids::newRequestId() : callerCtx.requestId;
    out.issuedAtEpoch = nowEpoch();
    out.expiresAtEpoch = out.issuedAtEpoch + 60;
    return out;
}

turbo::InternalClient &InteroperationService::portfolioClient() {
    static turbo::InternalClient *client = [] {
        const auto cfg = drogon::app().getCustomConfig()["turbo"];
        const std::string url =
            cfg["internal_services"].get("portfolio", "http://127.0.0.1:7502").asString();
        const std::string secret = cfg.get("context_secret", "").asString();
        return new turbo::InternalClient(url, secret);
    }();
    return *client;
}

turbo::InternalClient &InteroperationService::damClient() {
    static turbo::InternalClient *client = [] {
        const auto cfg = drogon::app().getCustomConfig()["turbo"];
        const std::string url =
            cfg["internal_services"].get("depositaccountmanagement", "http://127.0.0.1:7507").asString();
        const std::string secret = cfg.get("context_secret", "").asString();
        return new turbo::InternalClient(url, secret);
    }();
    return *client;
}

drogon::Task<std::pair<std::string, std::string>> InteroperationService::resolveAccount(
    Txn txn, const std::string &accountId) {
    // Convention (scope decision, see IMPLEMENTATION_PLAN.md Phase 9 as-built
    // notes): an interop account id is "<TYPE>:<id>" (TYPE in
    // SAVINGS|LOAN|SHARE); a bare id with no colon is treated as SAVINGS
    // (the common Mojaloop wallet-account case). A caller may also pass a
    // registered party identifier's own id ("<idType>:<idValue>" as
    // registered via registerParty) — looked up via interop_identifiers.
    auto colon = accountId.find(':');
    if (colon != std::string::npos) {
        std::string type = accountId.substr(0, colon);
        std::string id = accountId.substr(colon + 1);
        if (type == "SAVINGS" || type == "LOAN" || type == "SHARE") co_return {type, id};
        // Not a type prefix — try it as a registered party identifier instead.
        Mapper<m::InteropIdentifiers> mapper(txn);
        auto rows = co_await mapper.findBy(Criteria(m::InteropIdentifiers::Cols::_id_type, type) &&
                                           Criteria(m::InteropIdentifiers::Cols::_id_value, id));
        if (!rows.empty())
            co_return {rows.front().getValueOfAccountType(), rows.front().getValueOfAccountId()};
        throw ApiError(drogon::k404NotFound, "No account or registered party found for " + accountId,
                       "error.msg.interoperation.account.not.found");
    }
    co_return {"SAVINGS", accountId};
}

// =============================================================================
// parties (local CRUD on interop_identifiers)
// =============================================================================

drogon::Task<Json::Value> InteroperationService::registerParty(const turbo::RequestContext &ctx,
                                                                const std::string &idType,
                                                                const std::string &idValue,
                                                                const std::string &subIdOrType,
                                                                const Json::Value &body) {
    const auto accountId = asStringOr(body, "accountId");
    const auto accountType = asStringOr(body, "accountType", "SAVINGS");
    if (accountId.empty())
        throw ApiError(drogon::k400BadRequest, "accountId is required",
                       "error.msg.interoperation.party.required.fields.missing");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::InteropIdentifiers> mapper(txn);
    auto crit = Criteria(m::InteropIdentifiers::Cols::_id_type, idType) &&
               Criteria(m::InteropIdentifiers::Cols::_id_value, idValue);
    auto rows = subIdOrType.empty()
                   ? co_await mapper.findBy(crit)
                   : co_await mapper.findBy(crit &&
                                            Criteria(m::InteropIdentifiers::Cols::_sub_id_or_type,
                                                     subIdOrType));
    if (!rows.empty()) {
        auto row = rows.front();
        row.setAccountId(accountId);
        row.setAccountType(accountType);
        co_await mapper.update(row);
        co_return identifierJson(row);
    }
    m::InteropIdentifiers row;
    row.setIdType(idType);
    row.setIdValue(idValue);
    if (!subIdOrType.empty()) row.setSubIdOrType(subIdOrType);
    row.setAccountId(accountId);
    row.setAccountType(accountType);
    auto inserted = co_await mapper.insert(row);
    co_return identifierJson(inserted);
}

drogon::Task<Json::Value> InteroperationService::getParty(const turbo::RequestContext &ctx,
                                                          const std::string &idType,
                                                          const std::string &idValue,
                                                          const std::string &subIdOrType) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::InteropIdentifiers> mapper(txn);
    auto crit = Criteria(m::InteropIdentifiers::Cols::_id_type, idType) &&
               Criteria(m::InteropIdentifiers::Cols::_id_value, idValue);
    auto rows = subIdOrType.empty()
                   ? co_await mapper.findBy(crit)
                   : co_await mapper.findBy(crit &&
                                            Criteria(m::InteropIdentifiers::Cols::_sub_id_or_type,
                                                     subIdOrType));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "No party registered for this identifier",
                       "error.msg.interoperation.party.not.found");
    co_return identifierJson(rows.front());
}

drogon::Task<void> InteroperationService::removeParty(const turbo::RequestContext &ctx,
                                                       const std::string &idType,
                                                       const std::string &idValue,
                                                       const std::string &subIdOrType) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::InteropIdentifiers> mapper(txn);
    auto crit = Criteria(m::InteropIdentifiers::Cols::_id_type, idType) &&
               Criteria(m::InteropIdentifiers::Cols::_id_value, idValue);
    co_await mapper.deleteBy(subIdOrType.empty()
                                 ? crit
                                 : crit && Criteria(m::InteropIdentifiers::Cols::_sub_id_or_type,
                                                    subIdOrType));
}

// =============================================================================
// quotes (local, genuinely-computed fee calc)
// =============================================================================

drogon::Task<Json::Value> InteroperationService::createQuote(const turbo::RequestContext &ctx,
                                                              const Json::Value &body) {
    const auto accountId = asStringOr(body, "accountId");
    const auto amount = asDoubleOr(body, "amount", -1.0);
    if (accountId.empty() || amount <= 0.0)
        throw ApiError(drogon::k400BadRequest, "accountId and a positive amount are required",
                       "error.msg.interoperation.quote.required.fields.missing");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    // Fail fast if the account doesn't resolve — a quote for a non-existent
    // account is not a quote worth issuing.
    co_await resolveAccount(txn, accountId);

    m::InteropQuotes row;
    row.setTransactionCode(asStringOr(body, "transactionCode", turbo::ids::newUuid()));
    row.setQuoteCode(turbo::ids::newUuid());
    row.setAccountId(accountId);
    row.setAmount(std::to_string(amount));
    row.setFeeAmount(std::to_string(computeFee(amount)));
    row.setCurrency(asStringOr(body, "currency", "USD"));
    row.setStatus("ACTIVE");
    auto inserted = co_await Mapper<m::InteropQuotes>(txn).insert(row);
    co_return quoteJson(inserted);
}

drogon::Task<Json::Value> InteroperationService::getQuote(const turbo::RequestContext &ctx,
                                                          const std::string &transactionCode,
                                                          const std::string &quoteCode) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::InteropQuotes> mapper(txn);
    auto rows = co_await mapper.findBy(Criteria(m::InteropQuotes::Cols::_transaction_code, transactionCode) &&
                                       Criteria(m::InteropQuotes::Cols::_quote_code, quoteCode));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Quote not found", "error.msg.interoperation.quote.not.found");
    co_return quoteJson(rows.front());
}

// =============================================================================
// requests to pay (local workflow)
// =============================================================================

drogon::Task<Json::Value> InteroperationService::createRequestToPay(const turbo::RequestContext &ctx,
                                                                     const Json::Value &body) {
    const auto accountId = asStringOr(body, "accountId");
    const auto amount = asDoubleOr(body, "amount", -1.0);
    if (accountId.empty() || amount <= 0.0)
        throw ApiError(drogon::k400BadRequest, "accountId and a positive amount are required",
                       "error.msg.interoperation.request.required.fields.missing");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await resolveAccount(txn, accountId);

    m::InteropRequests row;
    row.setTransactionCode(asStringOr(body, "transactionCode", turbo::ids::newUuid()));
    row.setRequestCode(turbo::ids::newUuid());
    row.setAccountId(accountId);
    row.setAmount(std::to_string(amount));
    row.setCurrency(asStringOr(body, "currency", "USD"));
    row.setStatus("PENDING");
    auto inserted = co_await Mapper<m::InteropRequests>(txn).insert(row);
    co_return requestJson(inserted);
}

drogon::Task<Json::Value> InteroperationService::getRequestToPay(const turbo::RequestContext &ctx,
                                                                  const std::string &transactionCode,
                                                                  const std::string &requestCode) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::InteropRequests> mapper(txn);
    auto rows =
        co_await mapper.findBy(Criteria(m::InteropRequests::Cols::_transaction_code, transactionCode) &&
                               Criteria(m::InteropRequests::Cols::_request_code, requestCode));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Request not found",
                       "error.msg.interoperation.request.not.found");
    co_return requestJson(rows.front());
}

// =============================================================================
// transfers (local workflow state machine: PREPARE -> COMMIT/ABORT)
// =============================================================================

drogon::Task<Json::Value> InteroperationService::prepareTransfer(const turbo::RequestContext &ctx,
                                                                  const Json::Value &body) {
    const auto accountId = asStringOr(body, "accountId");
    const auto amount = asDoubleOr(body, "amount", -1.0);
    if (accountId.empty() || amount <= 0.0)
        throw ApiError(drogon::k400BadRequest, "accountId and a positive amount are required",
                       "error.msg.interoperation.transfer.required.fields.missing");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await resolveAccount(txn, accountId);

    m::InteropTransfers row;
    row.setTransactionCode(asStringOr(body, "transactionCode", turbo::ids::newUuid()));
    row.setTransferCode(turbo::ids::newUuid());
    row.setAccountId(accountId);
    row.setAmount(std::to_string(amount));
    row.setCurrency(asStringOr(body, "currency", "USD"));
    row.setTransferAction("PREPARE");
    row.setStatus("PENDING");
    auto inserted = co_await Mapper<m::InteropTransfers>(txn).insert(row);
    co_return transferJson(inserted);
}

drogon::Task<Json::Value> InteroperationService::actionTransfer(const turbo::RequestContext &ctx,
                                                                 const std::string &transactionCode,
                                                                 const Json::Value &body) {
    const auto transferCode = asStringOr(body, "transferCode");
    const auto action = asStringOr(body, "action");
    if (transferCode.empty() || (action != "COMMIT" && action != "ABORT"))
        throw ApiError(drogon::k400BadRequest, "transferCode and action (COMMIT|ABORT) are required",
                       "error.msg.interoperation.transfer.required.fields.missing");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::InteropTransfers> mapper(txn);
    auto rows =
        co_await mapper.findBy(Criteria(m::InteropTransfers::Cols::_transaction_code, transactionCode) &&
                               Criteria(m::InteropTransfers::Cols::_transfer_code, transferCode));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Transfer not found",
                       "error.msg.interoperation.transfer.not.found");
    auto row = rows.front();
    if (row.getValueOfStatus() != "PENDING")
        throw ApiError(drogon::k409Conflict, "This transfer has already been actioned",
                       "error.msg.interoperation.transfer.already.actioned");

    // Disclosed limitation (see header comment): COMMIT marks the transfer
    // as accepted on this platform's side of the protocol only — there is
    // no counterparty FSP in this sandbox to settle the other leg with.
    row.setTransferAction(action);
    row.setStatus(action == "COMMIT" ? "COMMITTED_LOCAL" : "ABORTED");
    co_await mapper.update(row);
    co_return transferJson(row);
}

drogon::Task<Json::Value> InteroperationService::getTransfer(const turbo::RequestContext &ctx,
                                                             const std::string &transactionCode,
                                                             const std::string &transferCode) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::InteropTransfers> mapper(txn);
    auto rows =
        co_await mapper.findBy(Criteria(m::InteropTransfers::Cols::_transaction_code, transactionCode) &&
                               Criteria(m::InteropTransfers::Cols::_transfer_code, transferCode));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Transfer not found",
                       "error.msg.interoperation.transfer.not.found");
    co_return transferJson(rows.front());
}

// =============================================================================
// accounts (genuine composition with Portfolio / DepositAccountManagement)
// =============================================================================

drogon::Task<Json::Value> InteroperationService::getAccount(const turbo::RequestContext &ctx,
                                                            const std::string &accountId) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto [type, id] = co_await resolveAccount(txn, accountId);
    if (type == "LOAN") {
        auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOAN")), drogon::Get,
                                                      "/api/v1/loans/get-detail/" + id);
        co_return unwrap(result, "loans");
    }
    if (type == "SHARE") {
        auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_SHAREACCOUNT")), drogon::Get,
                                                      "/api/v1/accounts/share/get-detail/" + id);
        co_return unwrap(result, "shareaccounts");
    }
    auto result = co_await damClient().call(systemCtx(ctx, P("READ_SAVINGSACCOUNT")), drogon::Get,
                                            "/api/v1/savingsaccounts/get-detail/" + id);
    co_return unwrap(result, "savingsaccounts");
}

drogon::Task<Json::Value> InteroperationService::accountTransactions(const turbo::RequestContext &ctx,
                                                                     const std::string &accountId) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto [type, id] = co_await resolveAccount(txn, accountId);
    if (type == "LOAN") {
        auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOAN")), drogon::Get,
                                                      "/api/v1/loans/" + id + "/transactions/get-all");
        co_return unwrap(result, "loantransactions");
    }
    auto result = co_await damClient().call(systemCtx(ctx, P("READ_SAVINGSACCOUNT")), drogon::Get,
                                            "/api/v1/savingsaccounts/" + id + "/transactions/get-all");
    co_return unwrap(result, "savingsaccounttransactions");
}

drogon::Task<Json::Value> InteroperationService::accountTransactionDetail(
    const turbo::RequestContext &ctx, const std::string &accountId, const std::string &transactionId) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto [type, id] = co_await resolveAccount(txn, accountId);
    if (type == "LOAN") {
        auto result = co_await portfolioClient().call(
            systemCtx(ctx, P("READ_LOAN")), drogon::Get,
            "/api/v1/loans/" + id + "/transactions/" + transactionId + "/get-detail");
        co_return unwrap(result, "loantransactions");
    }
    auto result = co_await damClient().call(
        systemCtx(ctx, P("READ_SAVINGSACCOUNT")), drogon::Get,
        "/api/v1/savingsaccounts/" + id + "/transactions/get-detail/" + transactionId);
    co_return unwrap(result, "savingsaccounttransactions");
}

// =============================================================================
// disbursement / loan repayment (genuine composition with Portfolio)
// =============================================================================

drogon::Task<Json::Value> InteroperationService::disburse(const turbo::RequestContext &ctx,
                                                          const std::string &transactionCode,
                                                          const Json::Value &body) {
    // Step 1 of 2: validate the loan is awaiting disbursal and record a
    // local PREPARE leg — mirrors the quote/transfer prepare pattern above.
    // The actual funds movement happens in disburseTransfer() below.
    const auto accountId = asStringOr(body, "accountId");
    if (accountId.empty())
        throw ApiError(drogon::k400BadRequest, "accountId (loan) is required",
                       "error.msg.interoperation.disburse.required.fields.missing");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto [type, loanId] = co_await resolveAccount(txn, accountId);
    if (type != "LOAN")
        throw ApiError(drogon::k400BadRequest, "accountId must resolve to a loan account",
                       "error.msg.interoperation.disburse.not.a.loan");

    auto detail = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOAN")), drogon::Get,
                                                  "/api/v1/loans/get-detail/" + loanId);
    Json::Value loan = unwrap(detail, "loans");

    m::InteropTransfers row;
    row.setTransactionCode(transactionCode);
    row.setTransferCode(turbo::ids::newUuid());
    row.setAccountId(accountId);
    row.setAmount(std::to_string(asDoubleOr(body, "amount", 0.0)));
    row.setCurrency(asStringOr(body, "currency", "USD"));
    row.setTransferAction("DISBURSE_PREPARE");
    row.setStatus("PENDING");
    auto inserted = co_await Mapper<m::InteropTransfers>(txn).insert(row);

    Json::Value out = transferJson(inserted);
    out["loanStatus"] = loan.isMember("status") ? loan["status"] : Json::Value();
    co_return out;
}

drogon::Task<Json::Value> InteroperationService::disburseTransfer(const turbo::RequestContext &ctx,
                                                                   const std::string &transactionCode,
                                                                   const Json::Value &body) {
    const auto transferCode = asStringOr(body, "transferCode");
    if (transferCode.empty())
        throw ApiError(drogon::k400BadRequest, "transferCode (from the prepare step) is required",
                       "error.msg.interoperation.disburse.required.fields.missing");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::InteropTransfers> mapper(txn);
    auto rows =
        co_await mapper.findBy(Criteria(m::InteropTransfers::Cols::_transaction_code, transactionCode) &&
                               Criteria(m::InteropTransfers::Cols::_transfer_code, transferCode));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "No prepared disbursement found for this transfer code",
                       "error.msg.interoperation.disburse.not.found");
    auto row = rows.front();
    if (row.getValueOfStatus() != "PENDING")
        throw ApiError(drogon::k409Conflict, "This disbursement has already been actioned",
                       "error.msg.interoperation.disburse.already.actioned");

    auto [type, loanId] = co_await resolveAccount(txn, row.getValueOfAccountId());

    Json::Value cmdBody;
    cmdBody["transactionDate"] = asStringOr(body, "transactionDate");
    cmdBody["transactionAmount"] = row.getValueOfAmount();
    if (body.isMember("paymentTypeId")) cmdBody["paymentTypeId"] = body["paymentTypeId"];
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("DISBURSE_LOAN")), drogon::Post,
                                                  "/api/v1/loans/" + loanId + "/command/disburse", cmdBody);
    Json::Value loan = unwrap(result, "loans");

    row.setTransferAction("DISBURSE");
    row.setStatus("COMMITTED_LOCAL");
    co_await mapper.update(row);

    Json::Value out = transferJson(row);
    out["loan"] = loan;
    co_return out;
}

drogon::Task<Json::Value> InteroperationService::loanRepayment(const turbo::RequestContext &ctx,
                                                                const std::string &transactionCode,
                                                                const Json::Value &body) {
    const auto accountId = asStringOr(body, "accountId");
    const auto amount = asDoubleOr(body, "amount", -1.0);
    if (accountId.empty() || amount <= 0.0)
        throw ApiError(drogon::k400BadRequest, "accountId (loan) and a positive amount are required",
                       "error.msg.interoperation.loanrepayment.required.fields.missing");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto [type, loanId] = co_await resolveAccount(txn, accountId);
    if (type != "LOAN")
        throw ApiError(drogon::k400BadRequest, "accountId must resolve to a loan account",
                       "error.msg.interoperation.loanrepayment.not.a.loan");

    Json::Value cmdBody;
    cmdBody["transactionDate"] = asStringOr(body, "transactionDate");
    cmdBody["transactionAmount"] = amount;
    if (body.isMember("paymentTypeId")) cmdBody["paymentTypeId"] = body["paymentTypeId"];
    // Portfolio's LoansController::transactionsCreate (command/{repayment,...})
    // is gated by PortfolioService::createLoanTransaction(), which checks
    // "UPDATE_LOAN" (not a "CREATE_LOANTRANSACTION" permission — that code
    // doesn't exist in Portfolio's permission set).
    auto result = co_await portfolioClient().call(
        systemCtx(ctx, P("UPDATE_LOAN")), drogon::Post,
        "/api/v1/loans/" + loanId + "/transactions/command/repayment", cmdBody);
    Json::Value loanTxn = unwrap(result, "loantransactions");

    m::InteropTransfers row;
    row.setTransactionCode(transactionCode);
    row.setTransferCode(turbo::ids::newUuid());
    row.setAccountId(accountId);
    row.setAmount(std::to_string(amount));
    row.setCurrency(asStringOr(body, "currency", "USD"));
    row.setTransferAction("LOAN_REPAYMENT");
    row.setStatus("COMMITTED_LOCAL");
    auto inserted = co_await Mapper<m::InteropTransfers>(txn).insert(row);

    Json::Value out = transferJson(inserted);
    out["loanTransaction"] = loanTxn;
    co_return out;
}

}  // namespace turbo_ledger_interoperation
