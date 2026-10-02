#include "SavingsController.h"

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

Task<HttpResponsePtr> SelfSavingsController::productsAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().savingsProducts(*ctx, "")); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfSavingsController::productDetail(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().savingsProducts(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfSavingsController::accountsTemplate(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().savingsTemplate(*ctx)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfSavingsController::getAccount(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().getSavingsAccount(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfSavingsController::updateAccount(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().updateSavingsAccount(*ctx, id, *body),
                                      "Savings account updated");
    }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfSavingsController::createAccount(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp = ApiResponse::httpOk(co_await svc().createSavingsAccount(*ctx, *body),
                                        "Savings application created");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfSavingsController::chargesAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().savingsCharges(*ctx, id, "")); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfSavingsController::chargeDetail(HttpRequestPtr req, std::string id,
                                                          std::string chargeId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().savingsCharges(*ctx, id, chargeId)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfSavingsController::transactionDetail(HttpRequestPtr req, std::string id,
                                                                std::string transactionId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().savingsTransaction(*ctx, id, transactionId));
    }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfSavingsController::transfersTemplate(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().accountTransfersTemplate(*ctx)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfSavingsController::createTransfer(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp = ApiResponse::httpOk(co_await svc().createAccountTransfer(*ctx, *body),
                                        "Transfer created");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}
