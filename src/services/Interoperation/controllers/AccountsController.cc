#include "AccountsController.h"

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

Task<HttpResponsePtr> InteropAccountsController::getAccount(HttpRequestPtr req, std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().getAccount(*ctx, accountId)); }
    SELF_CATCH
}

Task<HttpResponsePtr> InteropAccountsController::transactions(HttpRequestPtr req, std::string accountId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().accountTransactions(*ctx, accountId)); }
    SELF_CATCH
}

Task<HttpResponsePtr> InteropAccountsController::transactionDetail(HttpRequestPtr req,
                                                                    std::string accountId,
                                                                    std::string transactionId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_return ApiResponse::httpOk(
            co_await svc().accountTransactionDetail(*ctx, accountId, transactionId));
    }
    SELF_CATCH
}
