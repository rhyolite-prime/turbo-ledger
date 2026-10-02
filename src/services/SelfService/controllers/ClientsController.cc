#include "ClientsController.h"

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

#define SELF_TRY try

#define SELF_CATCH                                                         \
    catch (const ApiError &e) {                                           \
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode()); \
    }                                                                     \
    catch (const std::exception &e) {                                     \
        co_return ApiResponse::httpError(k500InternalServerError, e.what()); \
    }
}  // namespace

Task<HttpResponsePtr> SelfClientsController::listClients(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().listClients(*ctx)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfClientsController::getClient(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().getClient(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfClientsController::accountsOverview(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().accountsOverview(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfClientsController::obligeeDetails(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().obligeeDetails(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfClientsController::chargesAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().clientCharges(*ctx, id, "")); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfClientsController::chargeDetail(HttpRequestPtr req, std::string id,
                                                          std::string chargeId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().clientCharges(*ctx, id, chargeId)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfClientsController::transactionsAll(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().clientTransactions(*ctx, id, "")); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfClientsController::transactionDetail(HttpRequestPtr req, std::string id,
                                                                std::string transactionId) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_return ApiResponse::httpOk(co_await svc().clientTransactions(*ctx, id, transactionId));
    }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfClientsController::getImage(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().getClientImage(*ctx, id)); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfClientsController::putImage(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    SELF_TRY { co_return ApiResponse::httpOk(co_await svc().putClientImage(*ctx, id, *body), "Image saved"); }
    SELF_CATCH
}

Task<HttpResponsePtr> SelfClientsController::deleteImage(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    SELF_TRY {
        co_await svc().deleteClientImage(*ctx, id);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Image deleted");
    }
    SELF_CATCH
}
