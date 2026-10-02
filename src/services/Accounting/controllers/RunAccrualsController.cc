#include "RunAccrualsController.h"

#include "services/AccountingService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_accounting::AccountingService;
using turbo_ledger_accounting::ApiError;

namespace {
AccountingService &svc() {
    static AccountingService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> RunAccrualsController::run(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value payload = body ? *body : Json::Value(Json::objectValue);
    try {
        co_return ApiResponse::httpOk(co_await svc().runPeriodicAccrualAccounting(*ctx, payload),
                                      "Periodic accrual accounting executed");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
