#include "StandingInstructionsController.h"

#include "services/DepositAccountManagementService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_dam::ApiError;
using turbo_ledger_dam::DepositAccountManagementService;

namespace {
DepositAccountManagementService &svc() {
    static DepositAccountManagementService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> StandingInstructionsController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        auto clientId = req->getParameter("clientId");
        co_return ApiResponse::httpOk(co_await svc().listStandingInstructions(*ctx, clientId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> StandingInstructionsController::create(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        auto resp = ApiResponse::httpOk(co_await svc().createStandingInstruction(*ctx, *body),
                                        "Standing instruction created");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> StandingInstructionsController::getDetails(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getStandingInstruction(*ctx, id));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> StandingInstructionsController::update(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().updateStandingInstruction(*ctx, id, *body),
                                      "Standing instruction updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> StandingInstructionsController::templateEndpoint(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().standingInstructionTemplate(*ctx));
}

Task<HttpResponsePtr> StandingInstructionsController::runHistory(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        auto clientId = req->getParameter("clientId");
        co_return ApiResponse::httpOk(co_await svc().listStandingInstructionHistory(*ctx, clientId));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
