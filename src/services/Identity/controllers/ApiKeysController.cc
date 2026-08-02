#include "ApiKeysController.h"
#include "dto/BaseApiResponse.h"
#include "plugins/IdentityServicePlugin.h"
#include "dto/ApiKeyDto.h"

using namespace drogon;
using namespace turbo_ledger_identity::plugins;
using namespace turbo_ledger_identity::dto;

Task<HttpResponsePtr> ApiKeysController::getAll(HttpRequestPtr req) {
    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    int pageNo = 1;
    int pageSize = 10;
    std::string query = "";

    if (!req->getParameter("pageNo").empty()) {
        try { pageNo = std::stoi(req->getParameter("pageNo")); } catch (...) {}
    }
    if (!req->getParameter("pageSize").empty()) {
        try { pageSize = std::stoi(req->getParameter("pageSize")); } catch (...) {}
    }
    if (!req->getParameter("query").empty()) {
        query = req->getParameter("query");
    }

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& service = plugin->getApiKeyService();

    auto response = co_await service.getAll(businessId, pageNo, pageSize, query);

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    resp->setStatusCode(response.success ? k200OK : k400BadRequest);
    co_return resp;
}

Task<HttpResponsePtr> ApiKeysController::createApiKey(HttpRequestPtr req) {
    auto json = req->getJsonObject();
    if (!json) {
        BaseApiResponse apiResponse;
        apiResponse.success = false;
        apiResponse.message = "Invalid JSON payload";
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    ApiKeyDto dto;
    dto.fromJson(*json);
    dto.setBusinessId(businessId); // Ensure the token's business ID is strictly used

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& service = plugin->getApiKeyService();

    auto result = co_await service.create(dto);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}

Task<HttpResponsePtr> ApiKeysController::revokeApiKey(HttpRequestPtr req, std::string id) {
    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& service = plugin->getApiKeyService();

    auto result = co_await service.revoke(businessId, id);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}

Task<HttpResponsePtr> ApiKeysController::activateApiKey(HttpRequestPtr req, std::string id) {
    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& service = plugin->getApiKeyService();

    auto result = co_await service.activate(businessId, id);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}

Task<HttpResponsePtr> ApiKeysController::deleteApiKey(HttpRequestPtr req, std::string id) {
    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& service = plugin->getApiKeyService();

    auto result = co_await service.deleteApiKey(businessId, id);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}
