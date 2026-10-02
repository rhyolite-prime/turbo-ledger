#include "RecurringDepositAccountsController.h"

#include "services/DepositAccountManagementService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_dam::ApiError;
using turbo_ledger_dam::DepositAccountManagementService;
using turbo_ledger_dam::kDepositTypeRecurringDeposit;

namespace {
DepositAccountManagementService &svc() {
    static DepositAccountManagementService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> RecurringDepositAccountsController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        auto clientId = req->getParameter("clientId");
        auto status = req->getParameter("status");
        int offset = 0, limit = 200;
        if (!req->getParameter("offset").empty()) offset = std::stoi(req->getParameter("offset"));
        if (!req->getParameter("limit").empty()) limit = std::stoi(req->getParameter("limit"));
        co_return ApiResponse::httpOk(
            co_await svc().listAccounts(*ctx, kDepositTypeRecurringDeposit, clientId, status, offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> RecurringDepositAccountsController::create(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().createAccount(*ctx, kDepositTypeRecurringDeposit, *body),
                                        "Recurring deposit account created");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> RecurringDepositAccountsController::getDetails(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getAccount(*ctx, kDepositTypeRecurringDeposit, id));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> RecurringDepositAccountsController::update(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().updateAccount(*ctx, kDepositTypeRecurringDeposit, id, *body),
            "Recurring deposit account updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> RecurringDepositAccountsController::remove(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteAccount(*ctx, kDepositTypeRecurringDeposit, id);
        co_return ApiResponse::httpOk(Json::Value(), "Recurring deposit account deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> RecurringDepositAccountsController::command(HttpRequestPtr req, std::string id,
                                                              std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    try {
        co_return ApiResponse::httpOk(
            co_await svc().handleAccountCommand(*ctx, kDepositTypeRecurringDeposit, id, cmd, b));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> RecurringDepositAccountsController::closureTemplate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().accountClosureTemplate(*ctx, kDepositTypeRecurringDeposit, id));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> RecurringDepositAccountsController::templateEndpoint(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().accountTemplate(*ctx, kDepositTypeRecurringDeposit));
}

Task<HttpResponsePtr> RecurringDepositAccountsController::downloadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import spreadsheet template download (no XLSX generation pipeline in this codebase)");
}

Task<HttpResponsePtr> RecurringDepositAccountsController::uploadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import spreadsheet upload (no XLSX parsing pipeline in this codebase)");
}

Task<HttpResponsePtr> RecurringDepositAccountsController::transactionsDownloadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import transaction spreadsheet template download (no XLSX generation pipeline)");
}

Task<HttpResponsePtr> RecurringDepositAccountsController::transactionsUploadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import transaction spreadsheet upload (no XLSX parsing pipeline)");
}


Task<HttpResponsePtr> RecurringDepositAccountsController::transactionsTemplate(HttpRequestPtr req,
                                                                           std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().accountTransactionTemplate(*ctx, accountId));
}

Task<HttpResponsePtr> RecurringDepositAccountsController::transactionsGetDetail(HttpRequestPtr req,
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

Task<HttpResponsePtr> RecurringDepositAccountsController::transactionsCommand(HttpRequestPtr req,
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

Task<HttpResponsePtr> RecurringDepositAccountsController::transactionsCreate(HttpRequestPtr req,
                                                                         std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    std::string command = "deposit";
    if (body->isMember("command") && (*body)["command"].isString()) {
        command = (*body)["command"].asString();
    }
    try {
        auto resp = ApiResponse::httpOk(
            co_await svc().createAccountTransaction(*ctx, accountId, command, *body),
            "Recurring deposit transaction posted");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
