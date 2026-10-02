#include "GlobalConfigController.h"

#include "services/SystemConfigService.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using turbo::ApiResponse;
using turbo_ledger_systemconfig::ApiError;
using turbo_ledger_systemconfig::SystemConfigService;

namespace {
SystemConfigService &svc() {
    static SystemConfigService instance;
    return instance;
}
}  // namespace

Task<HttpResponsePtr> GlobalConfigController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().listConfigurations(*ctx));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> GlobalConfigController::getDetails(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getConfiguration(*ctx, id));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> GlobalConfigController::update(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().updateConfiguration(*ctx, id, *body),
                                      "Configuration updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> GlobalConfigController::getByName(HttpRequestPtr req, std::string name) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    try {
        co_return ApiResponse::httpOk(co_await svc().getConfigurationByName(*ctx, name));
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> GlobalConfigController::updateByName(HttpRequestPtr req, std::string name) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");
    auto body = req->getJsonObject();
    if (!body) co_return ApiResponse::httpBadRequest("Invalid JSON body");
    try {
        co_return ApiResponse::httpOk(co_await svc().updateConfigurationByName(*ctx, name, *body),
                                      "Configuration updated");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
