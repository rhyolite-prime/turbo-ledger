#include "MakerCheckersController.h"

#include "services/rbac/RbacService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_identity::rbac::ApiError;
using turbo_ledger_identity::rbac::RbacService;

namespace {
RbacService &svc() {
    static RbacService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> MakerCheckersController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().listCommands(*ctx, req->getParameter("status")));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> MakerCheckersController::approve(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().approveCommand(*ctx, id),
                                      "Command approved and executed");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> MakerCheckersController::reject(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    std::string reason;
    if (auto body = req->getJsonObject(); body && body->isMember("reason"))
        reason = (*body)["reason"].asString();
    try {
        co_return ApiResponse::httpOk(co_await svc().rejectCommand(*ctx, id, reason),
                                      "Command rejected");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> MakerCheckersController::remove(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_await svc().deleteCommand(*ctx, id);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Command deleted");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
