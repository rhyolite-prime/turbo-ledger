#include "MiscController.h"

#include "services/SelfServiceService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_selfservice::ApiError;
using turbo_ledger_selfservice::SelfServiceService;

namespace {
SelfServiceService &svc() {
    static SelfServiceService instance;
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

Task<HttpResponsePtr> SelfMiscController::runReport(HttpRequestPtr req, std::string reportName) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().runReport(*ctx, reportName)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfMiscController::surveys(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().surveys(*ctx)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfMiscController::surveyScorecards(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().surveyScorecards(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfMiscController::submitSurveyScorecard(HttpRequestPtr req,
                                                                std::string surveyId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().submitSurveyScorecard(*ctx, surveyId, b));
    }
    SELF_CATCH
}
