#include "ApiKeysController.h"
#include "dto/BaseApiResponse.h"
#include "plugins/IdentityServicePlugin.h"
#include "dto/ApiKeyDto.h"
#include "dto/UserIdentityDto.h"

using namespace drogon;
using namespace turbo_ledger_identity::plugins;
using namespace turbo_ledger_identity::dto;

Task<HttpResponsePtr> ApiKeysController::getAll(HttpRequestPtr req) {
    auto identity = turbo_ledger_identity::dto::UserIdentityDto::fromRequest(req);

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

    auto response = co_await service.getAll(identity, pageNo, pageSize, query);

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

    auto identity = turbo_ledger_identity::dto::UserIdentityDto::fromRequest(req);

    ApiKeyDto dto;
    dto.fromJson(*json);


    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& service = plugin->getApiKeyService();

    auto result = co_await service.create(identity, dto);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}


Task<HttpResponsePtr> ApiKeysController::validateApiKeys(HttpRequestPtr req) {
    auto json = req->getJsonObject();
    if (!json) {
        BaseApiResponse apiResponse;
        apiResponse.success = false;
        apiResponse.message = "Invalid JSON payload";
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    if (!json->isMember("clientId") || !json->isMember("clientSecret")) {
        BaseApiResponse apiResponse;
        apiResponse.success = false;
        apiResponse.message = "clientId and clientSecret are required";
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    std::string clientId = (*json)["clientId"].asString();
    std::string clientSecret = (*json)["clientSecret"].asString();

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& service = plugin->getApiKeyService();

    auto result = co_await service.validateApiCredentials(clientId, clientSecret);

    BaseApiResponse apiResponse;
    if (result.isValid) {
        apiResponse.success = true;
        apiResponse.message = "Valid credentials";
        apiResponse.result["accountId"] = result.accountId;
        apiResponse.result["businessId"] = result.businessId;
    } else {
        apiResponse.success = false;
        apiResponse.message = result.errorMessage;
        apiResponse.error["code"] = result.errorCode;
    }

    auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
    resp->setStatusCode(result.isValid ? k200OK : k401Unauthorized);
    co_return resp;
}



Task<HttpResponsePtr> ApiKeysController::revokeApiKey(HttpRequestPtr req, std::string id) {
    auto identity = turbo_ledger_identity::dto::UserIdentityDto::fromRequest(req);

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& service = plugin->getApiKeyService();

    auto result = co_await service.revoke(identity, id);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}

Task<HttpResponsePtr> ApiKeysController::activateApiKey(HttpRequestPtr req, std::string id) {
    auto identity = turbo_ledger_identity::dto::UserIdentityDto::fromRequest(req);

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& service = plugin->getApiKeyService();

    auto result = co_await service.activate(identity, id);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}

Task<HttpResponsePtr> ApiKeysController::deleteApiKey(HttpRequestPtr req, std::string id) {
    auto identity = turbo_ledger_identity::dto::UserIdentityDto::fromRequest(req);

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& service = plugin->getApiKeyService();

    auto result = co_await service.deleteApiKey(identity, id);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}
