#include "FieldConfigurationController.h"

#include "services/SystemConfigService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_systemconfig::ApiError;
using turbo_ledger_systemconfig::SystemConfigService;

namespace {
SystemConfigService &svc() {
    static SystemConfigService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> FieldConfigurationController::getDetails(HttpRequestPtr req, std::string entity) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getFieldConfiguration(*ctx, entity));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
