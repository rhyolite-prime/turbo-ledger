#include "ApiKeysController.h"
#include "dto/ApiKeyDto.h"
#include "plugins/IdentityServicePlugin.h"
#include "turbo/ApiResponse.h"
#include "turbo/RequestContext.h"

using namespace drogon;
using namespace turbo_ledger_identity::plugins;
using namespace turbo_ledger_identity::dto;
using turbo::ApiResponse;
using turbo_ledger_identity::services::ApiError;

Task<HttpResponsePtr> ApiKeysController::getAll(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");

    int pageNo = 1;
    int pageSize = 10;
    std::string query;

    if (!req->getParameter("pageNo").empty()) {
        try { pageNo = std::stoi(req->getParameter("pageNo")); } catch (...) {}
    }
    if (!req->getParameter("pageSize").empty()) {
        try { pageSize = std::stoi(req->getParameter("pageSize")); } catch (...) {}
    }
    if (!req->getParameter("query").empty()) query = req->getParameter("query");

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto &service = plugin->getApiKeyService();

    try {
        co_return ApiResponse::httpOk(co_await service.listApiKeys(*ctx, pageNo, pageSize, query),
                                      "Tenant API keys retrieved successfully");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> ApiKeysController::createApiKey(HttpRequestPtr req) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");

    auto json = req->getJsonObject();
    if (!json) co_return ApiResponse::httpBadRequest("Invalid JSON payload");

    ApiKeyDto dto;
    dto.fromJson(*json);

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto &service = plugin->getApiKeyService();

    try {
        auto resp = ApiResponse::httpOk(co_await service.createApiKey(*ctx, dto),
                                        "Tenant API key created successfully");
        resp->setStatusCode(k201Created);
        co_return resp;
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> ApiKeysController::validateApiKeys(HttpRequestPtr req) {
    auto json = req->getJsonObject();
    if (!json) co_return ApiResponse::httpBadRequest("Invalid JSON payload");
    if (!json->isMember("clientId") || !json->isMember("clientSecret"))
        co_return ApiResponse::httpBadRequest("clientId and clientSecret are required");

    // Unauthenticated by design (this IS the credential check) — the caller
    // asserts which tenant schema to look the key up in via TL-Tenant-Id,
    // same convention as AuthController::signIn.
    const std::string tenantId = req->getHeader(turbo::RequestContext::kTenantHeaderName);
    const std::string clientId = (*json)["clientId"].asString();
    const std::string clientSecret = (*json)["clientSecret"].asString();

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto &service = plugin->getApiKeyService();

    auto result = co_await service.validateApiCredentials(tenantId, clientId, clientSecret);

    if (result.isValid) {
        Json::Value body;
        body["tenantId"] = result.tenantId;
        co_return ApiResponse::httpOk(body, "Valid credentials");
    }
    co_return ApiResponse::httpError(
        result.errorCode == drogon::k400BadRequest ? k400BadRequest
            : (result.errorCode == drogon::k404NotFound ? k404NotFound : k401Unauthorized),
        result.errorMessage, "error.msg.identity.apikey.invalid.credentials");
}

Task<HttpResponsePtr> ApiKeysController::revokeApiKey(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto &service = plugin->getApiKeyService();

    try {
        co_return ApiResponse::httpOk(co_await service.revokeApiKey(*ctx, id),
                                      "Tenant API key revoked successfully");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> ApiKeysController::activateApiKey(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto &service = plugin->getApiKeyService();

    try {
        co_return ApiResponse::httpOk(co_await service.activateApiKey(*ctx, id),
                                      "Tenant API key activated successfully");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}

Task<HttpResponsePtr> ApiKeysController::deleteApiKey(HttpRequestPtr req, std::string id) {
    auto ctx = turbo::RequestContext::from(req);
    if (!ctx) co_return ApiResponse::httpUnauthorized("Missing trusted context");

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto &service = plugin->getApiKeyService();

    try {
        co_await service.deleteApiKey(*ctx, id);
        co_return ApiResponse::httpOk(Json::Value(Json::objectValue), "Tenant API key deleted successfully");
    } catch (const ApiError &e) {
        co_return ApiResponse::httpError(e.status(), e.what(), e.globalisationCode());
    } catch (const std::exception &e) {
        co_return ApiResponse::httpError(k500InternalServerError, e.what());
    }
}
