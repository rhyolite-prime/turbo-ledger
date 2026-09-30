#include "PermissionsController.h"

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

Task<HttpResponsePtr> PermissionsController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listPermissions(*ctx));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> PermissionsController::updateMakerChecker(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body || !(*body).isMember("code") || !(*body).isMember("enabled"))
        co_return ApiResponse::httpBadRequest("Body must contain 'code' and 'enabled'");
    try {
        co_return ApiResponse::httpOk(
            co_await svc().setMakerChecker(*ctx, (*body)["code"].asString(),
                                           (*body)["enabled"].asBool()),
            "Maker-checker updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
