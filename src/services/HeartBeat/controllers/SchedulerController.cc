#include "SchedulerController.h"

#include "services/HeartBeatService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_heartbeat::ApiError;
using turbo_ledger_heartbeat::HeartBeatService;

namespace {
HeartBeatService &svc() {
    static HeartBeatService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> SchedulerController::getStatus(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getSchedulerStatus(*ctx));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> SchedulerController::updateStatus(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value payload = body ? *body : Json::Value(Json::objectValue);
    try {
        co_return ApiResponse::httpOk(co_await svc().updateSchedulerStatus(*ctx, payload),
                                      "Scheduler status updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
