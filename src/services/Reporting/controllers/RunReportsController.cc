#include "RunReportsController.h"

#include <unordered_map>

#include "services/ReportingService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_reporting::ApiError;
using turbo_ledger_reporting::ReportingService;

namespace {
ReportingService &svc() {
    static ReportingService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> RunReportsController::run(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        const auto &rawParams = req->getParameters();
        std::unordered_map<std::string, std::string> params(rawParams.begin(), rawParams.end());
        co_return ApiResponse::httpOk(co_await svc().runReport(*ctx, id, params));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
