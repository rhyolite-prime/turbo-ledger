#include "WorkingDaysController.h"

#include "services/OrganizationService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_organization::ApiError;
using turbo_ledger_organization::OrganizationService;

namespace {
OrganizationService &svc() {
    static OrganizationService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> WorkingDaysController::get(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getWorkingDays(*ctx));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> WorkingDaysController::getTemplate(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    co_return ApiResponse::httpOk(svc().workingDaysTemplate(*ctx));
}

Task<HttpResponsePtr> WorkingDaysController::update(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().updateWorkingDays(*ctx, *body), "Working days updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
