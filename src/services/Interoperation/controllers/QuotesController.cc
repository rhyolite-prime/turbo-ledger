#include "QuotesController.h"

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

Task<HttpResponsePtr> QuotesController::createQuote(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp = ApiResponse::httpOk(co_await svc().createQuote(*ctx, *body), "Quote created");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}

Task<HttpResponsePtr> QuotesController::getQuote(HttpRequestPtr req, std::string transactionCode,
                                                 std::string quoteCode) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().getQuote(*ctx, transactionCode, quoteCode)); }
    SELF_CATCH
}

Task<HttpResponsePtr> QuotesController::createRequest(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp =
            ApiResponse::httpOk(co_await svc().createRequestToPay(*ctx, *body), "Request to pay created");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}

Task<HttpResponsePtr> QuotesController::getRequest(HttpRequestPtr req, std::string transactionCode,
                                                   std::string requestCode) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().getRequestToPay(*ctx, transactionCode, requestCode));
    }
    SELF_CATCH
}
