#include "SelfController.h"

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

Task<HttpResponsePtr> SelfController::userDetails(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().selfDetails(*ctx));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SelfController::changePassword(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body || !body->isMember("oldPassword") || !body->isMember("newPassword"))
        co_return ApiResponse::httpBadRequest("Body must contain 'oldPassword' and 'newPassword'");
    try {
        co_await svc().changePassword(*ctx, (*body)["oldPassword"].asString(),
                                      (*body)["newPassword"].asString());
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Password changed");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
