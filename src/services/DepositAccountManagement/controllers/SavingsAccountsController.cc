#include "SavingsAccountsController.h"

#include "services/DepositAccountManagementService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_dam::ApiError;
using turbo_ledger_dam::DepositAccountManagementService;
using turbo_ledger_dam::kDepositTypeSavings;

namespace {
DepositAccountManagementService &svc() {
    static DepositAccountManagementService instance;
    return instance;
}
}  // namespace

// ---- core CRUD + lifecycle --------------------------------------------------

Task<HttpResponsePtr> SavingsAccountsController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        auto clientId = req->getParameter("clientId");
        auto status = req->getParameter("status");
        int offset = 0, limit = 200;
        if (!req->getParameter("offset").empty()) offset = std::stoi(req->getParameter("offset"));
        if (!req->getParameter("limit").empty()) limit = std::stoi(req->getParameter("limit"));
        co_return ApiResponse::httpOk(
            co_await svc().listAccounts(*ctx, kDepositTypeSavings, clientId, status, offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::create(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().createAccount(*ctx, kDepositTypeSavings, *body),
                                        "Savings account created");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::getDetails(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getAccount(*ctx, kDepositTypeSavings, id));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::update(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().updateAccount(*ctx, kDepositTypeSavings, id, *body),
                                      "Savings account updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::remove(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteAccount(*ctx, kDepositTypeSavings, id);
        co_return ApiResponse::httpOk(Json::Value(), "Savings account deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::command(HttpRequestPtr req, std::string id,
                                                         std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    try {
        co_return ApiResponse::httpOk(
            co_await svc().handleAccountCommand(*ctx, kDepositTypeSavings, id, cmd, b));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::templateEndpoint(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().accountTemplate(*ctx, kDepositTypeSavings));
}

Task<HttpResponsePtr> SavingsAccountsController::downloadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import spreadsheet template download (no XLSX generation pipeline in this codebase)");
}

Task<HttpResponsePtr> SavingsAccountsController::uploadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import spreadsheet upload (no XLSX parsing pipeline in this codebase)");
}

Task<HttpResponsePtr> SavingsAccountsController::transactionsDownloadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import transaction spreadsheet template download (no XLSX generation pipeline)");
}

Task<HttpResponsePtr> SavingsAccountsController::transactionsUploadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import transaction spreadsheet upload (no XLSX parsing pipeline)");
}

// ---- external-id addressing --------------------------------------------------

Task<HttpResponsePtr> SavingsAccountsController::getDetailsByExternalId(HttpRequestPtr req,
                                                                        std::string externalId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().getAccountByExternalId(*ctx, kDepositTypeSavings, externalId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::updateByExternalId(HttpRequestPtr req,
                                                                    std::string externalId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().updateAccountByExternalId(*ctx, kDepositTypeSavings, externalId, *body),
            "Savings account updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::removeByExternalId(HttpRequestPtr req,
                                                                    std::string externalId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteAccountByExternalId(*ctx, kDepositTypeSavings, externalId);
        co_return ApiResponse::httpOk(Json::Value(), "Savings account deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::commandByExternalId(HttpRequestPtr req,
                                                                     std::string externalId,
                                                                     std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    try {
        co_return ApiResponse::httpOk(co_await svc().handleAccountCommandByExternalId(
            *ctx, kDepositTypeSavings, externalId, cmd, b));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

// ---- GSIM (documented scope trim — see DepositAccountManagementService.h) ---

Task<HttpResponsePtr> SavingsAccountsController::gsimCreate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "GSIM (Group Savings Integrated Monitoring) requires a Group service that does not exist yet");
}

Task<HttpResponsePtr> SavingsAccountsController::gsimUpdate(HttpRequestPtr req,
                                                            std::string parentAccountId) {
    co_return ApiResponse::httpNotImplemented(
        "GSIM (Group Savings Integrated Monitoring) requires a Group service that does not exist yet");
}

Task<HttpResponsePtr> SavingsAccountsController::gsimCommand(HttpRequestPtr req,
                                                             std::string parentAccountId) {
    co_return ApiResponse::httpNotImplemented(
        "GSIM (Group Savings Integrated Monitoring) requires a Group service that does not exist yet");
}

// ---- charges sub-resource -----------------------------------------------------

Task<HttpResponsePtr> SavingsAccountsController::chargesGetAll(HttpRequestPtr req,
                                                               std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listAccountCharges(*ctx, accountId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::chargesCreate(HttpRequestPtr req,
                                                               std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().addAccountCharge(*ctx, accountId, *body),
                                        "Savings account charge added");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::chargesGetDetail(HttpRequestPtr req,
                                                                  std::string accountId,
                                                                  std::string chargeId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getAccountCharge(*ctx, accountId, chargeId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::chargesUpdate(HttpRequestPtr req, std::string accountId,
                                                               std::string chargeId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().updateAccountCharge(*ctx, accountId, chargeId, *body),
            "Savings account charge updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::chargesDelete(HttpRequestPtr req, std::string accountId,
                                                               std::string chargeId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteAccountCharge(*ctx, accountId, chargeId);
        co_return ApiResponse::httpOk(Json::Value(), "Savings account charge deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::chargesCommand(HttpRequestPtr req, std::string accountId,
                                                                std::string chargeId, std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    try {
        co_return ApiResponse::httpOk(
            co_await svc().handleAccountChargeCommand(*ctx, accountId, chargeId, cmd, b));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::chargesTemplate(HttpRequestPtr req,
                                                                 std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().accountChargeTemplate(*ctx));
}

// ---- transactions sub-resource -------------------------------------------------

Task<HttpResponsePtr> SavingsAccountsController::transactionsCreate(HttpRequestPtr req,
                                                                    std::string accountId,
                                                                    std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(
            co_await svc().createAccountTransaction(*ctx, accountId, cmd, *body), "Transaction posted");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::transactionsGetAll(HttpRequestPtr req,
                                                                    std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listAccountTransactions(*ctx, accountId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

// Advanced search/query have no dedicated server-side filter implementation
// yet (the service exposes only listAccountTransactions) — documented
// simplification: both routes return the full transaction list for the
// account rather than honouring Fineract's rich search-criteria payload.
Task<HttpResponsePtr> SavingsAccountsController::transactionsSearch(HttpRequestPtr req,
                                                                    std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listAccountTransactions(*ctx, accountId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::transactionsQuery(HttpRequestPtr req,
                                                                   std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listAccountTransactions(*ctx, accountId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::transactionsTemplate(HttpRequestPtr req,
                                                                      std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().accountTransactionTemplate(*ctx, accountId));
}

Task<HttpResponsePtr> SavingsAccountsController::transactionsGetDetail(HttpRequestPtr req,
                                                                       std::string accountId,
                                                                       std::string transactionId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getAccountTransaction(*ctx, accountId, transactionId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::transactionsCommand(HttpRequestPtr req,
                                                                     std::string accountId,
                                                                     std::string transactionId,
                                                                     std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    try {
        co_return ApiResponse::httpOk(
            co_await svc().handleAccountTransactionCommand(*ctx, accountId, transactionId, cmd, b));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SavingsAccountsController::onHoldTransactions(HttpRequestPtr req,
                                                                    std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listOnHoldTransactions(*ctx, accountId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
