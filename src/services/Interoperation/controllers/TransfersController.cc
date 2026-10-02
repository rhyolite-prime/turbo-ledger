#include "TransfersController.h"

#include "services/InteroperationService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_interoperation::ApiError;
using turbo_ledger_interoperation::InteroperationService;

namespace {
InteroperationService &svc() {
    static InteroperationService instance;
    return instance;
}
}  // namespace

#define SELF_TRY try
#define SELF_CATCH                                                                     \
    catch (const ApiError &e) {                                                       \
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode()); \
    }                                                                                 \
    catch (const std::exception &e) {                                                 \
        co_return ApiResponse::httpError(k500InternalServerError, e.what());          \
    }

Task<HttpResponsePtr> TransfersController::prepare(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp = ApiResponse::httpOk(co_await svc().prepareTransfer(*ctx, *body), "Transfer prepared");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}

Task<HttpResponsePtr> TransfersController::action(HttpRequestPtr req, std::string transactionCode) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().actionTransfer(*ctx, transactionCode, *body),
                                      "Transfer actioned");
    }
    SELF_CATCH
}

Task<HttpResponsePtr> TransfersController::get(HttpRequestPtr req, std::string transactionCode,
                                               std::string transferCode) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().getTransfer(*ctx, transactionCode, transferCode));
    }
    SELF_CATCH
}
