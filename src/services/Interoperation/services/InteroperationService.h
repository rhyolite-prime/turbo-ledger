//
// Phase 9 — Interoperation (Payments v1): Mojaloop-style wallet
// interoperability primitives (19 endpoints).
//
// Scope decision (see IMPLEMENTATION_PLAN.md Phase 9 as-built notes): this
// sandbox has no other FSP to settle against. `parties` is pure local CRUD
// on interop_identifiers (an alias registry mapping an external identifier
// — MSISDN/EMAIL/ACCOUNT_ID/ALIAS — to one of this platform's own
// savings/loan/share accounts). `quotes`/`requesttopay`/`transfers` are
// genuinely-computed local workflow-state records (real fee calculation,
// a real state machine, idempotent transaction/quote/transfer codes) but
// the cross-FSP settlement leg of the real Mojaloop prepare/commit
// protocol never happens, because there is nothing on the other side of
// the wire to commit with — every record's status honestly reflects
// "accepted locally, never externally settled", not fabricated success.
//
// `accounts/*`, `disburse*` and `loanrepayment` ARE genuine: they compose
// directly with Portfolio/DepositAccountManagement over turbo::InternalClient
// against this platform's own accounts, the same mechanism SelfService uses.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/InternalClient.h"
#include "turbo/RequestContext.h"

namespace turbo_ledger_interoperation {

/// Error carrying an HTTP status + envelope globalisation code.
class ApiError : public std::runtime_error {
  public:
    ApiError(drogon::HttpStatusCode status, std::string message, std::string globalisationCode = "")
        : std::runtime_error(std::move(message)), status_(status), code_(std::move(globalisationCode)) {}
    drogon::HttpStatusCode status() const { return status_; }
    const std::string &globalisationCode() const { return code_; }

  private:
    drogon::HttpStatusCode status_;
    std::string code_;
};

class InteroperationService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- parties (local CRUD on interop_identifiers) --------------------------
    drogon::Task<Json::Value> registerParty(const turbo::RequestContext &ctx, const std::string &idType,
                                            const std::string &idValue, const std::string &subIdOrType,
                                            const Json::Value &body);
    drogon::Task<Json::Value> getParty(const turbo::RequestContext &ctx, const std::string &idType,
                                       const std::string &idValue, const std::string &subIdOrType);
    drogon::Task<void> removeParty(const turbo::RequestContext &ctx, const std::string &idType,
                                   const std::string &idValue, const std::string &subIdOrType);

    // ---- quotes (local, genuinely-computed fee calc) ---------------------------
    drogon::Task<Json::Value> createQuote(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> getQuote(const turbo::RequestContext &ctx, const std::string &transactionCode,
                                       const std::string &quoteCode);

    // ---- requests to pay (local workflow) --------------------------------------
    drogon::Task<Json::Value> createRequestToPay(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> getRequestToPay(const turbo::RequestContext &ctx,
                                              const std::string &transactionCode,
                                              const std::string &requestCode);

    // ---- transfers (local workflow state machine: PREPARE -> COMMIT/ABORT) ----
    drogon::Task<Json::Value> prepareTransfer(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> actionTransfer(const turbo::RequestContext &ctx,
                                             const std::string &transactionCode, const Json::Value &body);
    drogon::Task<Json::Value> getTransfer(const turbo::RequestContext &ctx,
                                          const std::string &transactionCode,
                                          const std::string &transferCode);

    // ---- accounts (genuine composition with Portfolio/DAM) ---------------------
    drogon::Task<Json::Value> getAccount(const turbo::RequestContext &ctx, const std::string &accountId);
    drogon::Task<Json::Value> accountTransactions(const turbo::RequestContext &ctx,
                                                  const std::string &accountId);
    drogon::Task<Json::Value> accountTransactionDetail(const turbo::RequestContext &ctx,
                                                       const std::string &accountId,
                                                       const std::string &transactionId);

    // ---- disbursement / loan repayment (genuine composition with Portfolio) ---
    drogon::Task<Json::Value> disburse(const turbo::RequestContext &ctx, const std::string &transactionCode,
                                       const Json::Value &body);
    drogon::Task<Json::Value> disburseTransfer(const turbo::RequestContext &ctx,
                                               const std::string &transactionCode,
                                               const Json::Value &body);
    drogon::Task<Json::Value> loanRepayment(const turbo::RequestContext &ctx,
                                            const std::string &transactionCode, const Json::Value &body);

  private:
    static drogon::orm::DbClientPtr db();

    /// Build a short-lived, narrowly-scoped outbound context for an internal
    /// composition call (see turbo/InternalClient.h for the security model).
    static turbo::RequestContext systemCtx(const turbo::RequestContext &callerCtx,
                                           std::vector<std::string> perms);

    turbo::InternalClient &portfolioClient();
    turbo::InternalClient &damClient();

    /// Resolve an interop account id (SAVINGS:<id> / LOAN:<id> / an
    /// interop_identifiers alias) to {accountType, accountId}.
    drogon::Task<std::pair<std::string, std::string>> resolveAccount(Txn txn, const std::string &accountId);
};

}  // namespace turbo_ledger_interoperation
