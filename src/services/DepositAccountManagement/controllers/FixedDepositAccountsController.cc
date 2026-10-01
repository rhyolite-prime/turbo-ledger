#include "FixedDepositAccountsController.h"

#include "services/DepositAccountManagementService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_dam::ApiError;
using turbo_ledger_dam::DepositAccountManagementService;
using turbo_ledger_dam::kDepositTypeFixedDeposit;

namespace {
DepositAccountManagementService &svc() {
    static DepositAccountManagementService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> FixedDepositAccountsController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        auto clientId = req->getParameter("clientId");
        auto status = req->getParameter("status");
        int offset = 0, limit = 200;
        if (!req->getParameter("offset").empty()) offset = std::stoi(req->getParameter("offset"));
        if (!req->getParameter("limit").empty()) limit = std::stoi(req->getParameter("limit"));
        co_return ApiResponse::httpOk(
            co_await svc().listAccounts(*ctx, kDepositTypeFixedDeposit, clientId, status, offset, limit));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> FixedDepositAccountsController::create(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().createAccount(*ctx, kDepositTypeFixedDeposit, *body),
                                        "Fixed deposit account created");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> FixedDepositAccountsController::getDetails(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getAccount(*ctx, kDepositTypeFixedDeposit, id));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> FixedDepositAccountsController::update(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().updateAccount(*ctx, kDepositTypeFixedDeposit, id, *body),
            "Fixed deposit account updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> FixedDepositAccountsController::remove(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteAccount(*ctx, kDepositTypeFixedDeposit, id);
        co_return ApiResponse::httpOk(Json::Value(), "Fixed deposit account deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> FixedDepositAccountsController::command(HttpRequestPtr req, std::string id,
                                                              std::string cmd) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    try {
        co_return ApiResponse::httpOk(
            co_await svc().handleAccountCommand(*ctx, kDepositTypeFixedDeposit, id, cmd, b));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> FixedDepositAccountsController::closureTemplate(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().accountClosureTemplate(*ctx, kDepositTypeFixedDeposit, id));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> FixedDepositAccountsController::templateEndpoint(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().accountTemplate(*ctx, kDepositTypeFixedDeposit));
}

Task<HttpResponsePtr> FixedDepositAccountsController::downloadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import spreadsheet template download (no XLSX generation pipeline in this codebase)");
}

Task<HttpResponsePtr> FixedDepositAccountsController::uploadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import spreadsheet upload (no XLSX parsing pipeline in this codebase)");
}

Task<HttpResponsePtr> FixedDepositAccountsController::transactionDownloadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import transaction spreadsheet template download (no XLSX generation pipeline)");
}

Task<HttpResponsePtr> FixedDepositAccountsController::transactionUploadTemplate(HttpRequestPtr req) {
    co_return ApiResponse::httpNotImplemented(
        "Bulk-import transaction spreadsheet upload (no XLSX parsing pipeline)");
}

Task<HttpResponsePtr> FixedDepositAccountsController::calculateInterest(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    Json::Value query;
    for (const auto &key : {"principalAmount", "annualInterestRate", "tenureInDays", "daysInYear"}) {
        auto v = req->getParameter(key);
        if (!v.empty()) query[key] = v;
    }
    try {
        co_return ApiResponse::httpOk(svc().calculateFdInterest(*ctx, query));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> FixedDepositAccountsController::transactionsTemplate(HttpRequestPtr req,
                                                                           std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().accountTransactionTemplate(*ctx, accountId));
}

Task<HttpResponsePtr> FixedDepositAccountsController::transactionsGetDetail(HttpRequestPtr req,
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

Task<HttpResponsePtr> FixedDepositAccountsController::transactionsCommand(HttpRequestPtr req,
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

Task<HttpResponsePtr> FixedDepositAccountsController::transactionsCreate(HttpRequestPtr req,
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
            "Fixed deposit transaction posted");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
