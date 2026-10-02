#include "DisbursementController.h"

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

Task<HttpResponsePtr> DisbursementController::disburse(HttpRequestPtr req, std::string transactionCode) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp = ApiResponse::httpOk(co_await svc().disburse(*ctx, transactionCode, *body),
                                        "Disbursement prepared");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}

Task<HttpResponsePtr> DisbursementController::disburseTransfer(HttpRequestPtr req,
                                                                std::string transactionCode) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().disburseTransfer(*ctx, transactionCode, *body),
                                      "Loan disbursed");
    }
    SELF_CATCH
}

Task<HttpResponsePtr> DisbursementController::loanRepayment(HttpRequestPtr req,
                                                             std::string transactionCode) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY {
        auto resp = ApiResponse::httpOk(co_await svc().loanRepayment(*ctx, transactionCode, *body),
                                        "Loan repayment posted");
        resp->setStatusCode(k201Created);
        co_return resp;
    }
    SELF_CATCH
}
