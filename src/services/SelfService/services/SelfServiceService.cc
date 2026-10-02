#include "SelfServiceService.h"

#include <drogon/orm/CoroMapper.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Exception.h>
#include <chrono>

#include "turbo/Ids.h"
#include "turbo/Pagination.h"
#include "turbo/TenantDb.h"

#include "models/ClientImages.h"
#include "models/DeviceRegistrations.h"
#include "models/Pockets.h"
#include "models/SelfServiceRegistrations.h"
#include "models/SelfServiceUsers.h"
#include "models/TptBeneficiaries.h"

using drogon::orm::CompareOperator;
using drogon::orm::Criteria;
using drogon::orm::DrogonDbException;
using drogon::orm::SortOrder;
using drogon::orm::UnexpectedRows;
using trantor::Date;

namespace turbo_ledger_selfservice {

namespace m = drogon_model::TlSelfServiceDb;
template <typename T>
using Mapper = drogon::orm::CoroMapper<T>;

// -----------------------------------------------------------------------------
// This file composes three backend services (Customer, Portfolio,
// DepositAccountManagement) over turbo::InternalClient (signed HTTP, not the
// gateway) for everything that isn't a purely local SelfService concern.
// Every composed response is a genuine live call — nothing here fabricates
// downstream data. See SelfServiceService.h for the ownership-enforcement
// model and the disclosed-stub list (runreports/surveys).
// -----------------------------------------------------------------------------

namespace {

std::string asStringOr(const Json::Value &v, const char *key, const std::string &fallback = "") {
    return v.isMember(key) && !v[key].isNull() ? v[key].asString() : fallback;
}

/// Builds a single-permission allow-list for systemCtx(). Deliberately a
/// named function rather than a `{"..."}` brace-init-list literal at call
/// sites: GCC's coroutine lowering mis-parses a brace-init-list argument
/// nested two calls deep inside a `co_await`-ed expression (reproduced in
/// isolation; tracked as a toolchain quirk, not a logic bug) and aborts
/// with a spurious "array used as initializer" diagnostic. Routing the
/// vector construction through an ordinary function call sidesteps it.
std::vector<std::string> P(std::string permission) { return {std::move(permission)}; }

int64_t nowEpoch() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())
        .count();
}

Json::Value selfServiceUserJson(const m::SelfServiceUsers &u) {
    Json::Value j;
    j["id"] = u.getValueOfId();
    j["identityUserId"] = u.getValueOfIdentityUserId();
    j["clientId"] = u.getValueOfClientId();
    j["username"] = u.getValueOfUsername();
    if (u.getMobileNo()) j["mobileNo"] = u.getValueOfMobileNo();
    if (u.getEmail()) j["email"] = u.getValueOfEmail();
    j["status"] = u.getValueOfStatus();
    return j;
}

Json::Value registrationJson(const m::SelfServiceRegistrations &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["firstName"] = r.getValueOfFirstName();
    j["lastName"] = r.getValueOfLastName();
    j["mobileNo"] = r.getValueOfMobileNo();
    if (r.getAccountNumber()) j["accountNumber"] = r.getValueOfAccountNumber();
    j["authenticationMode"] = r.getValueOfAuthenticationMode();
    j["status"] = r.getValueOfStatus();
    return j;
}

Json::Value deviceRegistrationJson(const m::DeviceRegistrations &d) {
    Json::Value j;
    j["id"] = d.getValueOfId();
    j["clientId"] = d.getValueOfClientId();
    j["deviceId"] = d.getValueOfDeviceId();
    if (d.getDeviceName()) j["deviceName"] = d.getValueOfDeviceName();
    j["status"] = d.getValueOfStatus();
    return j;
}

Json::Value tptBeneficiaryJson(const m::TptBeneficiaries &b) {
    Json::Value j;
    j["id"] = b.getValueOfId();
    j["name"] = b.getValueOfName();
    j["accountType"] = b.getValueOfAccountType();
    j["accountNumber"] = b.getValueOfAccountNumber();
    if (b.getTransferLimit()) j["transferLimit"] = b.getValueOfTransferLimit();
    j["status"] = b.getValueOfStatus();
    return j;
}

Json::Value pocketJson(const m::Pockets &p) {
    Json::Value j;
    j["id"] = p.getValueOfId();
    j["accountType"] = p.getValueOfAccountType();
    j["accountId"] = p.getValueOfAccountId();
    j["isDefault"] = p.getValueOfIsDefault();
    return j;
}

/// Extract the "result" payload from a downstream ApiResponse envelope (or
/// the raw body, defensively, if a downstream ever returns an unwrapped JSON).
Json::Value unwrap(const turbo::InternalClient::Result &r, const char *what) {
    if (!r.ok()) {
        std::string msg = (r.body.isMember("message") && r.body["message"].isString())
                              ? r.body["message"].asString()
                              : (std::string(what) + " failed");
        throw ApiError(r.status, msg, "error.msg.selfservice.upstream." + std::string(what));
    }
    return r.body.isMember("result") ? r.body["result"] : r.body;
}

drogon::Task<m::SelfServiceUsers> loadLinkedUser(std::shared_ptr<drogon::orm::Transaction> txn,
                                                const turbo::RequestContext &ctx) {
    Mapper<m::SelfServiceUsers> mapper(txn);
    auto rows = co_await mapper.findBy(Criteria(m::SelfServiceUsers::Cols::_identity_user_id, ctx.userId));
    if (rows.empty())
        throw ApiError(drogon::k403Forbidden,
                       "No self-service profile is linked to this account",
                       "error.msg.selfservice.not.linked");
    co_return rows.front();
}

}  // namespace

drogon::orm::DbClientPtr SelfServiceService::db() { return drogon::app().getDbClient(); }

void SelfServiceService::requirePermission(const turbo::RequestContext &ctx, const std::string &code) {
    if (!ctx.hasPermission(code))
        throw ApiError(drogon::k403Forbidden, "Missing permission: " + code,
                       "error.msg.platform.permission.denied");
}

turbo::RequestContext SelfServiceService::systemCtx(const turbo::RequestContext &callerCtx,
                                                    std::vector<std::string> perms) {
    turbo::RequestContext out;
    out.tenantId = callerCtx.tenantId;
    // Downstream services (Customer/Portfolio/DAM) treat ctx.userId as a
    // created_by/modified_by actor id with a UUID column type, so the system
    // actor must be a real (nil) UUID rather than a human-readable label —
    // the label still goes in `username` for audit/log readability.
    out.userId = "00000000-0000-0000-0000-000000000000";
    out.username = "selfservice-bff";
    out.authScheme = "system";
    out.permissions = std::move(perms);
    out.requestId = callerCtx.requestId.empty() ? turbo::ids::newRequestId() : callerCtx.requestId;
    out.issuedAtEpoch = nowEpoch();
    out.expiresAtEpoch = out.issuedAtEpoch + 60;
    return out;
}

void SelfServiceService::enforceClientOwnership(const Json::Value &body,
                                                const std::string &linkedClientId) {
    const auto clientId = asStringOr(body, "clientId");
    if (clientId.empty() || clientId != linkedClientId)
        throw ApiError(drogon::k403Forbidden, "This resource does not belong to your linked client",
                       "error.msg.selfservice.ownership.denied");
}

turbo::InternalClient &SelfServiceService::customerClient() {
    static turbo::InternalClient *client = [] {
        const auto cfg = drogon::app().getCustomConfig()["turbo"];
        const std::string url =
            cfg["internal_services"].get("customer", "http://127.0.0.1:7504").asString();
        const std::string secret = cfg.get("context_secret", "").asString();
        return new turbo::InternalClient(url, secret);
    }();
    return *client;
}

turbo::InternalClient &SelfServiceService::portfolioClient() {
    static turbo::InternalClient *client = [] {
        const auto cfg = drogon::app().getCustomConfig()["turbo"];
        const std::string url =
            cfg["internal_services"].get("portfolio", "http://127.0.0.1:7502").asString();
        const std::string secret = cfg.get("context_secret", "").asString();
        return new turbo::InternalClient(url, secret);
    }();
    return *client;
}

turbo::InternalClient &SelfServiceService::damClient() {
    static turbo::InternalClient *client = [] {
        const auto cfg = drogon::app().getCustomConfig()["turbo"];
        const std::string url =
            cfg["internal_services"].get("depositaccountmanagement", "http://127.0.0.1:7507").asString();
        const std::string secret = cfg.get("context_secret", "").asString();
        return new turbo::InternalClient(url, secret);
    }();
    return *client;
}

drogon::Task<Json::Value> SelfServiceService::requireLinkedUser(Txn txn,
                                                                 const turbo::RequestContext &ctx) {
    auto row = co_await loadLinkedUser(txn, ctx);
    co_return selfServiceUserJson(row);
}

// =============================================================================
// registration / authentication / profile
// =============================================================================

drogon::Task<Json::Value> SelfServiceService::submitRegistration(const turbo::RequestContext &ctx,
                                                                  const Json::Value &body) {
    const auto firstName = asStringOr(body, "firstName");
    const auto lastName = asStringOr(body, "lastName");
    const auto mobileNo = asStringOr(body, "mobileNo");
    if (firstName.empty() || lastName.empty() || mobileNo.empty())
        throw ApiError(drogon::k400BadRequest, "firstName, lastName and mobileNo are required",
                       "error.msg.selfservice.registration.required.fields.missing");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::SelfServiceRegistrations row;
    row.setFirstName(firstName);
    row.setLastName(lastName);
    row.setMobileNo(mobileNo);
    if (body.isMember("accountNumber")) row.setAccountNumber(asStringOr(body, "accountNumber"));
    row.setAuthenticationMode(asStringOr(body, "authenticationMode", "APP"));
    row.setStatus("PENDING");
    auto inserted = co_await Mapper<m::SelfServiceRegistrations>(txn).insert(row);
    co_return registrationJson(inserted);
}

drogon::Task<Json::Value> SelfServiceService::createRegistrationUser(const turbo::RequestContext &ctx,
                                                                     const Json::Value &body) {
    // Scope decision (see IMPLEMENTATION_PLAN.md Phase 9 as-built notes): this
    // does not re-implement Identity's password hashing/user-creation flow.
    // It links an *already-created* Identity platform user id to an
    // *already-existing* Customer client id, completing the self-service
    // identity. The caller must have platform admin rights to perform this
    // linking (it is an approval action, not something a self-service user
    // does to themselves).
    requirePermission(ctx, "CREATE_SELFSERVICEUSER");

    const auto identityUserId = asStringOr(body, "identityUserId");
    const auto clientId = asStringOr(body, "clientId");
    const auto username = asStringOr(body, "username");
    if (identityUserId.empty() || clientId.empty() || username.empty())
        throw ApiError(drogon::k400BadRequest,
                       "identityUserId, clientId and username are required",
                       "error.msg.selfservice.registration.required.fields.missing");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::SelfServiceUsers> mapper(txn);

    auto existing =
        co_await mapper.findBy(Criteria(m::SelfServiceUsers::Cols::_identity_user_id, identityUserId));
    if (!existing.empty())
        throw ApiError(drogon::k409Conflict, "This Identity user is already linked to a self-service profile",
                       "error.msg.selfservice.already.linked");

    m::SelfServiceUsers row;
    row.setIdentityUserId(identityUserId);
    row.setClientId(clientId);
    row.setUsername(username);
    if (body.isMember("mobileNo")) row.setMobileNo(asStringOr(body, "mobileNo"));
    if (body.isMember("email")) row.setEmail(asStringOr(body, "email"));
    row.setStatus("ACTIVE");
    auto inserted = co_await mapper.insert(row);

    if (body.isMember("registrationId") && !asStringOr(body, "registrationId").empty()) {
        Mapper<m::SelfServiceRegistrations> regMapper(txn);
        auto regs = co_await regMapper.findBy(
            Criteria(m::SelfServiceRegistrations::Cols::_id, asStringOr(body, "registrationId")));
        if (!regs.empty()) {
            auto reg = regs.front();
            reg.setStatus("APPROVED");
            co_await regMapper.update(reg);
        }
    }

    co_return selfServiceUserJson(inserted);
}

drogon::Task<Json::Value> SelfServiceService::authenticate(const turbo::RequestContext &ctx,
                                                           const Json::Value &) {
    // Real password verification already happened in Identity before the
    // ApiGateway ever signed the TL-Context that reached this service — see
    // IMPLEMENTATION_PLAN.md Phase 9 as-built notes. This endpoint's job
    // (matching Fineract's self/authentication response shape) is to echo
    // back the authenticated self-service user's profile + linked client.
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Json::Value j = selfServiceUserJson(user);
    j["authenticated"] = true;
    co_return j;
}

drogon::Task<Json::Value> SelfServiceService::getUserDetails(const turbo::RequestContext &ctx) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Json::Value j = selfServiceUserJson(user);
    j["roles"] = Json::Value(Json::arrayValue);
    j["permissions"] = Json::Value(Json::arrayValue);
    co_return j;
}

drogon::Task<Json::Value> SelfServiceService::updateUser(const turbo::RequestContext &ctx,
                                                         const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    if (body.isMember("mobileNo")) user.setMobileNo(asStringOr(body, "mobileNo"));
    if (body.isMember("email")) user.setEmail(asStringOr(body, "email"));
    if (body.isMember("username")) user.setUsername(asStringOr(body, "username"));
    co_await Mapper<m::SelfServiceUsers>(txn).update(user);
    co_return selfServiceUserJson(user);
}

// =============================================================================
// clients (composes Customer)
// =============================================================================

drogon::Task<Json::Value> SelfServiceService::listClients(const turbo::RequestContext &ctx) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto result = co_await customerClient().call(systemCtx(ctx, P("READ_CLIENT")), drogon::Get,
                                                 "/api/v1/clients/get-detail/" + user.getValueOfClientId());
    Json::Value client = unwrap(result, "clients");
    Json::Value items(Json::arrayValue);
    items.append(client);
    co_return turbo::pagedResult(1, items);
}

drogon::Task<Json::Value> SelfServiceService::getClient(const turbo::RequestContext &ctx,
                                                        const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    if (id != user.getValueOfClientId())
        throw ApiError(drogon::k403Forbidden, "This client does not belong to your self-service profile",
                       "error.msg.selfservice.ownership.denied");
    auto result = co_await customerClient().call(systemCtx(ctx, P("READ_CLIENT")), drogon::Get,
                                                 "/api/v1/clients/get-detail/" + id);
    co_return unwrap(result, "clients");
}

drogon::Task<Json::Value> SelfServiceService::accountsOverview(const turbo::RequestContext &ctx,
                                                               const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    if (id != user.getValueOfClientId())
        throw ApiError(drogon::k403Forbidden, "This client does not belong to your self-service profile",
                       "error.msg.selfservice.ownership.denied");

    auto loansResult = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOAN")), drogon::Get,
                                                       "/api/v1/loans/get-all?clientId=" + id);
    auto savingsResult = co_await damClient().call(systemCtx(ctx, P("READ_SAVINGSACCOUNT")), drogon::Get,
                                                   "/api/v1/savingsaccounts/get-all?clientId=" + id);
    auto sharesResult = co_await portfolioClient().call(systemCtx(ctx, P("READ_SHAREACCOUNT")), drogon::Get,
                                                        "/api/v1/accounts/share/get-all?clientId=" + id);

    Json::Value overview;
    auto loans = unwrap(loansResult, "loans");
    overview["loanAccounts"] = loans.isMember("pageItems") ? loans["pageItems"] : loans;
    auto savings = unwrap(savingsResult, "savingsaccounts");
    overview["savingsAccounts"] = savings.isMember("pageItems") ? savings["pageItems"] : savings;
    auto shares = unwrap(sharesResult, "shareaccounts");
    overview["shareAccounts"] = shares.isArray() ? shares : Json::Value(Json::arrayValue);
    co_return overview;
}

drogon::Task<Json::Value> SelfServiceService::obligeeDetails(const turbo::RequestContext &ctx,
                                                              const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    if (id != user.getValueOfClientId())
        throw ApiError(drogon::k403Forbidden, "This client does not belong to your self-service profile",
                       "error.msg.selfservice.ownership.denied");
    auto result = co_await customerClient().call(systemCtx(ctx, P("READ_CLIENT")), drogon::Get,
                                                 "/api/v1/clients/" + id + "/obligeedetails");
    co_return unwrap(result, "obligeedetails");
}

drogon::Task<Json::Value> SelfServiceService::clientCharges(const turbo::RequestContext &ctx,
                                                            const std::string &id,
                                                            const std::string &chargeId) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    if (id != user.getValueOfClientId())
        throw ApiError(drogon::k403Forbidden, "This client does not belong to your self-service profile",
                       "error.msg.selfservice.ownership.denied");
    const std::string path = chargeId.empty()
                                 ? "/api/v1/clients/" + id + "/charges/get-all"
                                 : "/api/v1/clients/" + id + "/charges/" + chargeId + "/get-detail";
    auto result = co_await customerClient().call(systemCtx(ctx, P("READ_CLIENTCHARGE")), drogon::Get, path);
    co_return unwrap(result, "clientcharges");
}

drogon::Task<Json::Value> SelfServiceService::clientTransactions(const turbo::RequestContext &ctx,
                                                                 const std::string &id,
                                                                 const std::string &transactionId) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    if (id != user.getValueOfClientId())
        throw ApiError(drogon::k403Forbidden, "This client does not belong to your self-service profile",
                       "error.msg.selfservice.ownership.denied");
    const std::string path = transactionId.empty()
                                 ? "/api/v1/clients/" + id + "/transactions/get-all"
                                 : "/api/v1/clients/" + id + "/transactions/" + transactionId + "/get-detail";
    auto result =
        co_await customerClient().call(systemCtx(ctx, P("READ_CLIENTTRANSACTION")), drogon::Get, path);
    co_return unwrap(result, "clienttransactions");
}

drogon::Task<Json::Value> SelfServiceService::getClientImage(const turbo::RequestContext &ctx,
                                                             const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    if (id != user.getValueOfClientId())
        throw ApiError(drogon::k403Forbidden, "This client does not belong to your self-service profile",
                       "error.msg.selfservice.ownership.denied");
    Mapper<m::ClientImages> mapper(txn);
    auto rows = co_await mapper.findBy(Criteria(m::ClientImages::Cols::_client_id, id));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "No image set for this client",
                       "error.msg.selfservice.image.not.found");
    Json::Value j;
    j["clientId"] = id;
    j["contentType"] = rows.front().getValueOfContentType();
    j["imageData"] = rows.front().getValueOfImageData();
    co_return j;
}

drogon::Task<Json::Value> SelfServiceService::putClientImage(const turbo::RequestContext &ctx,
                                                             const std::string &id,
                                                             const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    if (id != user.getValueOfClientId())
        throw ApiError(drogon::k403Forbidden, "This client does not belong to your self-service profile",
                       "error.msg.selfservice.ownership.denied");
    const auto contentType = asStringOr(body, "contentType", "image/jpeg");
    const auto imageData = asStringOr(body, "imageData");
    if (imageData.empty())
        throw ApiError(drogon::k400BadRequest, "imageData (base64) is required",
                       "error.msg.selfservice.image.required.fields.missing");

    Mapper<m::ClientImages> mapper(txn);
    auto rows = co_await mapper.findBy(Criteria(m::ClientImages::Cols::_client_id, id));
    if (rows.empty()) {
        m::ClientImages row;
        row.setClientId(id);
        row.setContentType(contentType);
        row.setImageData(imageData);
        auto inserted = co_await mapper.insert(row);
        Json::Value j;
        j["clientId"] = id;
        j["contentType"] = inserted.getValueOfContentType();
        co_return j;
    }
    auto row = rows.front();
    row.setContentType(contentType);
    row.setImageData(imageData);
    co_await mapper.update(row);
    Json::Value j;
    j["clientId"] = id;
    j["contentType"] = row.getValueOfContentType();
    co_return j;
}

drogon::Task<void> SelfServiceService::deleteClientImage(const turbo::RequestContext &ctx,
                                                         const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    if (id != user.getValueOfClientId())
        throw ApiError(drogon::k403Forbidden, "This client does not belong to your self-service profile",
                       "error.msg.selfservice.ownership.denied");
    Mapper<m::ClientImages> mapper(txn);
    co_await mapper.deleteBy(Criteria(m::ClientImages::Cols::_client_id, id));
}

// =============================================================================
// loans (composes Portfolio)
// =============================================================================

drogon::Task<Json::Value> SelfServiceService::loanProducts(const turbo::RequestContext &ctx,
                                                           const std::string &id) {
    const std::string path =
        id.empty() ? "/api/v1/loanproducts/get-all" : "/api/v1/loanproducts/get-detail/" + id;
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOANPRODUCT")), drogon::Get, path);
    co_return unwrap(result, "loanproducts");
}

drogon::Task<Json::Value> SelfServiceService::loansTemplate(const turbo::RequestContext &ctx) {
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOANPRODUCT")), drogon::Get,
                                                  "/api/v1/loans/template");
    co_return unwrap(result, "loanstemplate");
}

drogon::Task<Json::Value> SelfServiceService::getLoan(const turbo::RequestContext &ctx,
                                                      const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOAN")), drogon::Get,
                                                  "/api/v1/loans/get-detail/" + id);
    auto loan = unwrap(result, "loans");
    enforceClientOwnership(loan, user.getValueOfClientId());
    co_return loan;
}

drogon::Task<Json::Value> SelfServiceService::createLoan(const turbo::RequestContext &ctx,
                                                         const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Json::Value loanBody = body;
    loanBody["clientId"] = user.getValueOfClientId();
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("CREATE_LOAN")), drogon::Post,
                                                  "/api/v1/loans/create", loanBody);
    co_return unwrap(result, "loans");
}

drogon::Task<Json::Value> SelfServiceService::loanCommand(const turbo::RequestContext &ctx,
                                                          const std::string &id,
                                                          const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto detail = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOAN")), drogon::Get,
                                                  "/api/v1/loans/get-detail/" + id);
    enforceClientOwnership(unwrap(detail, "loans"), user.getValueOfClientId());

    const auto command = asStringOr(body, "command", "withdrawnByApplicant");
    // Self-service applicants may only withdraw their own pending application
    // — approve/reject/disburse remain staff-only operations even when the
    // underlying resource is theirs.
    if (command != "withdrawnByApplicant")
        throw ApiError(drogon::k403Forbidden,
                       "Self-service users may only withdraw a pending loan application",
                       "error.msg.selfservice.loan.command.forbidden");
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("WITHDRAW_LOAN")), drogon::Post,
                                                  "/api/v1/loans/" + id + "/command/" + command, body);
    co_return unwrap(result, "loans");
}

drogon::Task<Json::Value> SelfServiceService::loanCharges(const turbo::RequestContext &ctx,
                                                          const std::string &id,
                                                          const std::string &chargeId) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto detail = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOAN")), drogon::Get,
                                                  "/api/v1/loans/get-detail/" + id);
    enforceClientOwnership(unwrap(detail, "loans"), user.getValueOfClientId());

    const std::string path = chargeId.empty() ? "/api/v1/loans/" + id + "/charges/get-all"
                                              : "/api/v1/loans/" + id + "/charges/" + chargeId + "/get-detail";
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOANCHARGE")), drogon::Get, path);
    co_return unwrap(result, "loancharges");
}

drogon::Task<Json::Value> SelfServiceService::loanGuarantors(const turbo::RequestContext &ctx,
                                                             const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto detail = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOAN")), drogon::Get,
                                                  "/api/v1/loans/get-detail/" + id);
    enforceClientOwnership(unwrap(detail, "loans"), user.getValueOfClientId());
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOANGUARANTOR")), drogon::Get,
                                                  "/api/v1/loans/" + id + "/guarantors/get-all");
    co_return unwrap(result, "loanguarantors");
}

drogon::Task<Json::Value> SelfServiceService::loanTransaction(const turbo::RequestContext &ctx,
                                                              const std::string &id,
                                                              const std::string &transactionId) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto detail = co_await portfolioClient().call(systemCtx(ctx, P("READ_LOAN")), drogon::Get,
                                                  "/api/v1/loans/get-detail/" + id);
    enforceClientOwnership(unwrap(detail, "loans"), user.getValueOfClientId());
    auto result = co_await portfolioClient().call(
        systemCtx(ctx, P("READ_LOAN")), drogon::Get,
        "/api/v1/loans/" + id + "/transactions/" + transactionId + "/get-detail");
    co_return unwrap(result, "loantransactions");
}

// =============================================================================
// savings accounts (composes DepositAccountManagement)
// =============================================================================

drogon::Task<Json::Value> SelfServiceService::savingsProducts(const turbo::RequestContext &ctx,
                                                              const std::string &id) {
    const std::string path =
        id.empty() ? "/api/v1/savingsproducts/get-all" : "/api/v1/savingsproducts/get-detail/" + id;
    auto result = co_await damClient().call(systemCtx(ctx, P("READ_SAVINGSPRODUCT")), drogon::Get, path);
    co_return unwrap(result, "savingsproducts");
}

drogon::Task<Json::Value> SelfServiceService::savingsTemplate(const turbo::RequestContext &ctx) {
    auto result = co_await damClient().call(systemCtx(ctx, P("READ_SAVINGSPRODUCT")), drogon::Get,
                                            "/api/v1/savingsaccounts/template");
    co_return unwrap(result, "savingsaccountstemplate");
}

drogon::Task<Json::Value> SelfServiceService::getSavingsAccount(const turbo::RequestContext &ctx,
                                                                const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto result = co_await damClient().call(systemCtx(ctx, P("READ_SAVINGSACCOUNT")), drogon::Get,
                                            "/api/v1/savingsaccounts/get-detail/" + id);
    auto account = unwrap(result, "savingsaccounts");
    enforceClientOwnership(account, user.getValueOfClientId());
    co_return account;
}

drogon::Task<Json::Value> SelfServiceService::updateSavingsAccount(const turbo::RequestContext &ctx,
                                                                   const std::string &id,
                                                                   const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto detail = co_await damClient().call(systemCtx(ctx, P("READ_SAVINGSACCOUNT")), drogon::Get,
                                            "/api/v1/savingsaccounts/get-detail/" + id);
    enforceClientOwnership(unwrap(detail, "savingsaccounts"), user.getValueOfClientId());
    auto result = co_await damClient().call(systemCtx(ctx, P("UPDATE_SAVINGSACCOUNT")), drogon::Put,
                                            "/api/v1/savingsaccounts/" + id + "/update", body);
    co_return unwrap(result, "savingsaccounts");
}

drogon::Task<Json::Value> SelfServiceService::createSavingsAccount(const turbo::RequestContext &ctx,
                                                                   const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Json::Value savingsBody = body;
    savingsBody["clientId"] = user.getValueOfClientId();
    auto result = co_await damClient().call(systemCtx(ctx, P("CREATE_SAVINGSACCOUNT")), drogon::Post,
                                            "/api/v1/savingsaccounts/create", savingsBody);
    co_return unwrap(result, "savingsaccounts");
}

drogon::Task<Json::Value> SelfServiceService::savingsCharges(const turbo::RequestContext &ctx,
                                                             const std::string &id,
                                                             const std::string &chargeId) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto detail = co_await damClient().call(systemCtx(ctx, P("READ_SAVINGSACCOUNT")), drogon::Get,
                                            "/api/v1/savingsaccounts/get-detail/" + id);
    enforceClientOwnership(unwrap(detail, "savingsaccounts"), user.getValueOfClientId());
    const std::string path = chargeId.empty()
                                 ? "/api/v1/savingsaccounts/" + id + "/charges/get-all"
                                 : "/api/v1/savingsaccounts/" + id + "/charges/" + chargeId + "/get-detail";
    auto result =
        co_await damClient().call(systemCtx(ctx, P("READ_SAVINGSACCOUNTCHARGE")), drogon::Get, path);
    co_return unwrap(result, "savingsaccountcharges");
}

drogon::Task<Json::Value> SelfServiceService::savingsTransaction(const turbo::RequestContext &ctx,
                                                                 const std::string &id,
                                                                 const std::string &transactionId) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto detail = co_await damClient().call(systemCtx(ctx, P("READ_SAVINGSACCOUNT")), drogon::Get,
                                            "/api/v1/savingsaccounts/get-detail/" + id);
    enforceClientOwnership(unwrap(detail, "savingsaccounts"), user.getValueOfClientId());
    auto result = co_await damClient().call(
        systemCtx(ctx, P("READ_SAVINGSACCOUNTTRANSACTION")), drogon::Get,
        "/api/v1/savingsaccounts/" + id + "/transactions/get-detail/" + transactionId);
    co_return unwrap(result, "savingsaccounttransactions");
}

// =============================================================================
// share accounts (composes Portfolio)
// =============================================================================

drogon::Task<Json::Value> SelfServiceService::shareProducts(const turbo::RequestContext &ctx,
                                                            const std::string &id) {
    const std::string path = id.empty() ? "/api/v1/products/share/get-all"
                                        : "/api/v1/products/share/get-detail/" + id;
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_SHAREPRODUCT")), drogon::Get, path);
    co_return unwrap(result, "shareproducts");
}

drogon::Task<Json::Value> SelfServiceService::shareAccountsTemplate(const turbo::RequestContext &ctx) {
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_SHAREPRODUCT")), drogon::Get,
                                                  "/api/v1/accounts/share/template");
    co_return unwrap(result, "shareaccountstemplate");
}

drogon::Task<Json::Value> SelfServiceService::getShareAccount(const turbo::RequestContext &ctx,
                                                              const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("READ_SHAREACCOUNT")), drogon::Get,
                                                  "/api/v1/accounts/share/get-detail/" + id);
    auto account = unwrap(result, "shareaccounts");
    enforceClientOwnership(account, user.getValueOfClientId());
    co_return account;
}

drogon::Task<Json::Value> SelfServiceService::createShareAccount(const turbo::RequestContext &ctx,
                                                                 const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Json::Value shareBody = body;
    shareBody["clientId"] = user.getValueOfClientId();
    auto result = co_await portfolioClient().call(systemCtx(ctx, P("CREATE_SHAREACCOUNT")), drogon::Post,
                                                  "/api/v1/accounts/share/create", shareBody);
    co_return unwrap(result, "shareaccounts");
}

// =============================================================================
// account transfers (composes DepositAccountManagement)
// =============================================================================

drogon::Task<Json::Value> SelfServiceService::accountTransfersTemplate(const turbo::RequestContext &ctx) {
    auto result = co_await damClient().call(systemCtx(ctx, P("READ_ACCOUNTTRANSFER")), drogon::Get,
                                            "/api/v1/accounttransfers/template");
    co_return unwrap(result, "accounttransferstemplate");
}

drogon::Task<Json::Value> SelfServiceService::createAccountTransfer(const turbo::RequestContext &ctx,
                                                                    const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    // The transfer's source account must belong to the caller — the
    // destination may be a saved TPT beneficiary's external account.
    const auto fromClientId = asStringOr(body, "fromClientId");
    if (fromClientId != user.getValueOfClientId())
        throw ApiError(drogon::k403Forbidden, "The source account does not belong to your linked client",
                       "error.msg.selfservice.ownership.denied");
    auto result = co_await damClient().call(systemCtx(ctx, P("CREATE_ACCOUNTTRANSFER")), drogon::Post,
                                            "/api/v1/accounttransfers/create", body);
    co_return unwrap(result, "accounttransfers");
}

// =============================================================================
// TPT beneficiaries (local)
// =============================================================================

drogon::Task<Json::Value> SelfServiceService::tptTemplate(const turbo::RequestContext &) {
    Json::Value j;
    j["accountTypeOptions"] = Json::Value(Json::arrayValue);
    for (const char *t : {"SAVINGS", "LOAN", "SHARE"}) j["accountTypeOptions"].append(t);
    co_return j;
}

drogon::Task<Json::Value> SelfServiceService::listTptBeneficiaries(const turbo::RequestContext &ctx) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Mapper<m::TptBeneficiaries> mapper(txn);
    auto rows = co_await mapper.findBy(
        Criteria(m::TptBeneficiaries::Cols::_self_service_user_id, user.getValueOfId()));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(tptBeneficiaryJson(r));
    co_return items;
}

drogon::Task<Json::Value> SelfServiceService::createTptBeneficiary(const turbo::RequestContext &ctx,
                                                                   const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    const auto name = asStringOr(body, "name");
    const auto accountType = asStringOr(body, "accountType");
    const auto accountNumber = asStringOr(body, "accountNumber");
    if (name.empty() || accountType.empty() || accountNumber.empty())
        throw ApiError(drogon::k400BadRequest, "name, accountType and accountNumber are required",
                       "error.msg.selfservice.tpt.required.fields.missing");

    m::TptBeneficiaries row;
    row.setSelfServiceUserId(user.getValueOfId());
    row.setName(name);
    row.setAccountType(accountType);
    row.setAccountNumber(accountNumber);
    if (body.isMember("transferLimit")) row.setTransferLimit(asStringOr(body, "transferLimit"));
    row.setStatus("ACTIVE");
    auto inserted = co_await Mapper<m::TptBeneficiaries>(txn).insert(row);
    co_return tptBeneficiaryJson(inserted);
}

drogon::Task<Json::Value> SelfServiceService::updateTptBeneficiary(const turbo::RequestContext &ctx,
                                                                   const std::string &id,
                                                                   const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Mapper<m::TptBeneficiaries> mapper(txn);
    auto rows = co_await mapper.findBy(Criteria(m::TptBeneficiaries::Cols::_id, id) &&
                                       Criteria(m::TptBeneficiaries::Cols::_self_service_user_id,
                                                user.getValueOfId()));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Beneficiary not found", "error.msg.selfservice.tpt.not.found");
    auto row = rows.front();
    if (body.isMember("name")) row.setName(asStringOr(body, "name"));
    if (body.isMember("transferLimit")) row.setTransferLimit(asStringOr(body, "transferLimit"));
    if (body.isMember("status")) row.setStatus(asStringOr(body, "status"));
    co_await mapper.update(row);
    co_return tptBeneficiaryJson(row);
}

drogon::Task<void> SelfServiceService::deleteTptBeneficiary(const turbo::RequestContext &ctx,
                                                            const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Mapper<m::TptBeneficiaries> mapper(txn);
    co_await mapper.deleteBy(Criteria(m::TptBeneficiaries::Cols::_id, id) &&
                             Criteria(m::TptBeneficiaries::Cols::_self_service_user_id,
                                      user.getValueOfId()));
}

// =============================================================================
// device registration (local)
// =============================================================================

drogon::Task<Json::Value> SelfServiceService::listDeviceRegistrations(const turbo::RequestContext &ctx) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Mapper<m::DeviceRegistrations> mapper(txn);
    auto rows = co_await mapper.findBy(
        Criteria(m::DeviceRegistrations::Cols::_self_service_user_id, user.getValueOfId()));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(deviceRegistrationJson(r));
    co_return items;
}

drogon::Task<Json::Value> SelfServiceService::createDeviceRegistration(const turbo::RequestContext &ctx,
                                                                       const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    const auto deviceId = asStringOr(body, "deviceId");
    if (deviceId.empty())
        throw ApiError(drogon::k400BadRequest, "deviceId is required",
                       "error.msg.selfservice.device.required.fields.missing");
    m::DeviceRegistrations row;
    row.setSelfServiceUserId(user.getValueOfId());
    row.setClientId(user.getValueOfClientId());
    row.setDeviceId(deviceId);
    if (body.isMember("deviceName")) row.setDeviceName(asStringOr(body, "deviceName"));
    row.setStatus("ACTIVE");
    auto inserted = co_await Mapper<m::DeviceRegistrations>(txn).insert(row);
    co_return deviceRegistrationJson(inserted);
}

drogon::Task<Json::Value> SelfServiceService::getDeviceRegistration(const turbo::RequestContext &ctx,
                                                                    const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Mapper<m::DeviceRegistrations> mapper(txn);
    auto rows = co_await mapper.findBy(Criteria(m::DeviceRegistrations::Cols::_id, id) &&
                                       Criteria(m::DeviceRegistrations::Cols::_self_service_user_id,
                                                user.getValueOfId()));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Device registration not found",
                       "error.msg.selfservice.device.not.found");
    co_return deviceRegistrationJson(rows.front());
}

drogon::Task<Json::Value> SelfServiceService::updateDeviceRegistration(const turbo::RequestContext &ctx,
                                                                       const std::string &id,
                                                                       const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Mapper<m::DeviceRegistrations> mapper(txn);
    auto rows = co_await mapper.findBy(Criteria(m::DeviceRegistrations::Cols::_id, id) &&
                                       Criteria(m::DeviceRegistrations::Cols::_self_service_user_id,
                                                user.getValueOfId()));
    if (rows.empty())
        throw ApiError(drogon::k404NotFound, "Device registration not found",
                       "error.msg.selfservice.device.not.found");
    auto row = rows.front();
    if (body.isMember("deviceName")) row.setDeviceName(asStringOr(body, "deviceName"));
    if (body.isMember("status")) row.setStatus(asStringOr(body, "status"));
    co_await mapper.update(row);
    co_return deviceRegistrationJson(row);
}

drogon::Task<void> SelfServiceService::deleteDeviceRegistration(const turbo::RequestContext &ctx,
                                                                const std::string &id) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Mapper<m::DeviceRegistrations> mapper(txn);
    co_await mapper.deleteBy(Criteria(m::DeviceRegistrations::Cols::_id, id) &&
                             Criteria(m::DeviceRegistrations::Cols::_self_service_user_id,
                                      user.getValueOfId()));
}

// =============================================================================
// pockets (local)
// =============================================================================

drogon::Task<Json::Value> SelfServiceService::listPockets(const turbo::RequestContext &ctx) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    Mapper<m::Pockets> mapper(txn);
    auto rows =
        co_await mapper.findBy(Criteria(m::Pockets::Cols::_self_service_user_id, user.getValueOfId()));
    Json::Value items(Json::arrayValue);
    for (const auto &r : rows) items.append(pocketJson(r));
    co_return items;
}

drogon::Task<Json::Value> SelfServiceService::createPocket(const turbo::RequestContext &ctx,
                                                           const Json::Value &body) {
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto user = co_await loadLinkedUser(txn, ctx);
    const auto accountType = asStringOr(body, "accountType");
    const auto accountId = asStringOr(body, "accountId");
    if (accountType.empty() || accountId.empty())
        throw ApiError(drogon::k400BadRequest, "accountType and accountId are required",
                       "error.msg.selfservice.pocket.required.fields.missing");
    m::Pockets row;
    row.setSelfServiceUserId(user.getValueOfId());
    row.setAccountType(accountType);
    row.setAccountId(accountId);
    row.setIsDefault(body.get("isDefault", false).asBool());
    auto inserted = co_await Mapper<m::Pockets>(txn).insert(row);
    co_return pocketJson(inserted);
}

// =============================================================================
// disclosed stubs: runreports / surveys (no Reporting/PPI subsystem exists)
// =============================================================================

drogon::Task<Json::Value> SelfServiceService::runReport(const turbo::RequestContext &, const std::string &) {
    throw ApiError(drogon::k501NotImplemented,
                  "self/runreports requires the Reporting subsystem, which is out of scope for this "
                  "build (see IMPLEMENTATION_PLAN.md)",
                  "error.msg.platform.not.implemented");
    co_return Json::Value();
}

drogon::Task<Json::Value> SelfServiceService::surveys(const turbo::RequestContext &) {
    co_return Json::Value(Json::arrayValue);
}

drogon::Task<Json::Value> SelfServiceService::surveyScorecards(const turbo::RequestContext &,
                                                                const std::string &) {
    throw ApiError(drogon::k501NotImplemented,
                  "self/surveys/scorecards requires the PPI/scorecard subsystem, which is out of scope "
                  "for this build (see IMPLEMENTATION_PLAN.md)",
                  "error.msg.platform.not.implemented");
    co_return Json::Value();
}

drogon::Task<Json::Value> SelfServiceService::submitSurveyScorecard(const turbo::RequestContext &,
                                                                    const std::string &,
                                                                    const Json::Value &) {
    throw ApiError(drogon::k501NotImplemented,
                  "self/surveys/scorecards requires the PPI/scorecard subsystem, which is out of scope "
                  "for this build (see IMPLEMENTATION_PLAN.md)",
                  "error.msg.platform.not.implemented");
    co_return Json::Value();
}

}  // namespace turbo_ledger_selfservice
