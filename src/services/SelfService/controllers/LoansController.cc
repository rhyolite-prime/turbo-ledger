#include "LoansController.h"

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

Task<HttpResponsePtr> SelfLoansController::loanProductsAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().loanProducts(*ctx, "")); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfLoansController::loanProductDetail(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().loanProducts(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfLoansController::loansTemplate(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().loansTemplate(*ctx)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfLoansController::getLoan(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().getLoan(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfLoansController::createLoan(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp = ApiResponse::httpOk(co_await svc().createLoan(*ctx, *body), "Loan application created");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfLoansController::loanCommand(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    Json::Value b = body ? *body : Json::Value(Json::objectValue);
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().loanCommand(*ctx, id, b)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfLoansController::chargesAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().loanCharges(*ctx, id, "")); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfLoansController::chargeDetail(HttpRequestPtr req, std::string id,
                                                        std::string chargeId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().loanCharges(*ctx, id, chargeId)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfLoansController::guarantors(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().loanGuarantors(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfLoansController::transactionDetail(HttpRequestPtr req, std::string id,
                                                              std::string transactionId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().loanTransaction(*ctx, id, transactionId)); }
    SELF_CATCH
}
