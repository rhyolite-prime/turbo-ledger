#include "GroupLevelsController.h"

#include "services/GroupService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_group::ApiError;
using turbo_ledger_group::GroupService;

namespace {
GroupService &svc() {
    static GroupService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> GroupLevelsController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listGroupLevels(*ctx));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
