#include "TenantsController.h"

#include "constants/ErrorCodes.h"
#include "plugins/IdentityServicePlugin.h"

using namespace turbo_ledger_identity::plugins;

Task<HttpResponsePtr> TenantsController::getTenants(HttpRequestPtr req) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    if (!businessId.empty()) {
        turbo_ledger_identity::dto::BaseApiResponse apiResponse;
        apiResponse.success = false;
        apiResponse.message = "Forbidden: Tenant tokens cannot access host endpoints";
        apiResponse.error["code"] = turbo_ledger_identity::constants::ErrorCode::ERR_PERMISSION_DENIED;
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k403Forbidden);
        co_return resp;
    }

    int pageSize = 10;
    int pageNo = 1;

    if (!req->getParameter("pageSize").empty()) {
        try { pageSize = std::max(1, std::min(100, std::stoi(req->getParameter("pageSize")))); } catch (...) {}
    }
    if (!req->getParameter("pageNo").empty()) {
        try { pageNo = std::max(1, std::stoi(req->getParameter("pageNo"))); } catch (...) {}
    }
    std::string query = req->getParameter("query");

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& tenantService = plugin->getBusinessAccountService();

    auto result = co_await tenantService.getAll(pageNo, pageSize, query);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> TenantsController::updateStatus(HttpRequestPtr req, std::string id) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    if (!businessId.empty()) {
        turbo_ledger_identity::dto::BaseApiResponse apiResponse;
        apiResponse.success = false;
        apiResponse.message = "Forbidden: Tenant tokens cannot access host endpoints";
        apiResponse.error["code"] = turbo_ledger_identity::constants::ErrorCode::ERR_PERMISSION_DENIED;
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k403Forbidden);
        co_return resp;
    }

    std::string statusStr = req->getParameter("status");
    turbo_ledger_identity::constants::StatusType status = turbo_ledger_identity::constants::StatusType::Inactive;

    if (statusStr == "ACTIVE") status = turbo_ledger_identity::constants::StatusType::Active;
    else if (statusStr == "SUSPENDED") status = turbo_ledger_identity::constants::StatusType::Suspended;
    else if (statusStr != "INACTIVE") {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Invalid status provided. Must be ACTIVE, INACTIVE, or SUSPENDED";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& tenantService = plugin->getBusinessAccountService();

    auto result = co_await tenantService.updateAccountStatus(id, status);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> TenantsController::createTenant(HttpRequestPtr req) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    if (!businessId.empty()) {
        turbo_ledger_identity::dto::BaseApiResponse apiResponse;
        apiResponse.success = false;
        apiResponse.message = "Forbidden: Tenant tokens cannot access host endpoints";
        apiResponse.error["code"] = turbo_ledger_identity::constants::ErrorCode::ERR_PERMISSION_DENIED;
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k403Forbidden);
        co_return resp;
    }

    auto jsonBody = req->getJsonObject();
    if (!jsonBody) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Invalid JSON body";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    turbo_ledger_identity::dto::BusinessAccountDto tenantDto;
    tenantDto.fromJson(*jsonBody);

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& tenantService = plugin->getBusinessAccountService();

    auto result = co_await tenantService.create(tenantDto);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> TenantsController::updateTenant(HttpRequestPtr req, std::string id) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    if (!businessId.empty()) {
        turbo_ledger_identity::dto::BaseApiResponse apiResponse;
        apiResponse.success = false;
        apiResponse.message = "Forbidden: Tenant tokens cannot access host endpoints";
        apiResponse.error["code"] = turbo_ledger_identity::constants::ErrorCode::ERR_PERMISSION_DENIED;
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k403Forbidden);
        co_return resp;
    }

    auto jsonBody = req->getJsonObject();
    if (!jsonBody) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Invalid JSON body";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    turbo_ledger_identity::dto::BusinessAccountDto tenantDto;
    tenantDto.fromJson(*jsonBody);

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& tenantService = plugin->getBusinessAccountService();

    auto result = co_await tenantService.update(tenantDto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> TenantsController::deleteTenant(HttpRequestPtr req, std::string id) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    if (!businessId.empty()) {
        turbo_ledger_identity::dto::BaseApiResponse apiResponse;
        apiResponse.success = false;
        apiResponse.message = "Forbidden: Tenant tokens cannot access host endpoints";
        apiResponse.error["code"] = turbo_ledger_identity::constants::ErrorCode::ERR_PERMISSION_DENIED;
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k403Forbidden);
        co_return resp;
    }


    if (id.empty()) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing required parameter: id";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& tenantService = plugin->getBusinessAccountService();

    auto result = co_await tenantService.deleteAccount(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}
