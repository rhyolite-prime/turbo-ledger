#include "ClientsV2Controller.h"

#include "services/CustomerService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_customer::ApiError;
using turbo_ledger_customer::CustomerService;

namespace {
CustomerService &svc() {
    static CustomerService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> ClientsV2Controller::search(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().searchClientsV2(*ctx, *body));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
