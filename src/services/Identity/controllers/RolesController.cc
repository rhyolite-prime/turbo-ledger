#include "RolesController.h"
#include "constants/ErrorCodes.h"
#include "dto/BaseApiResponse.h"
#include "plugins/IdentityServicePlugin.h"
#include "dto/RoleDto.h"

using namespace drogon;
using namespace turbo_ledger_identity::plugins;
using namespace turbo_ledger_identity::dto;

Task<HttpResponsePtr> RolesController::getRoles(HttpRequestPtr req) {

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

    auto plugin = app().getPlugin<IdentityServicePlugin>();
    auto& roleService = plugin->getRoleService();

    auto response = co_await roleService.getAll(businessId, pageNo, pageSize, query);

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    resp->setStatusCode(response.success ? k200OK : k400BadRequest);
    co_return resp;
}


Task<HttpResponsePtr> RolesController::getTenantPermissions(HttpRequestPtr req) {

    auto plugin = app().getPlugin<IdentityServicePlugin>();
    auto& roleService = plugin->getRoleService();

    auto response = co_await roleService.getTenantPermissions();

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    resp->setStatusCode(response.success ? k200OK : k400BadRequest);
    co_return resp;

}


Task<HttpResponsePtr> RolesController::getHostPermissions(HttpRequestPtr req) {
    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}


    if (!businessId.empty()) {
        BaseApiResponse apiResponse;
        apiResponse.success = false;
        apiResponse.message = "Forbidden: Tenant tokens cannot access host endpoints";
        apiResponse.error["code"] = turbo_ledger_identity::constants::ERR_PERMISSION_DENIED;
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k403Forbidden);
        co_return resp;
    }

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& roleService = plugin->getRoleService();

    auto response = co_await roleService.getHostPermissions();

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    resp->setStatusCode(response.success ? k200OK : k400BadRequest);
    co_return resp;
}


Task<HttpResponsePtr> RolesController::createRole(HttpRequestPtr req) {
    BaseApiResponse apiResponse;
    auto json = req->getJsonObject();
    if (!json) {
        apiResponse.success = false;
        apiResponse.message = "Invalid JSON payload";
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }
    
    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    RoleDto dto;
    dto.fromJson(*json);

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& roleService = plugin->getRoleService();

    auto result = co_await roleService.create(businessId, dto);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}


Task<HttpResponsePtr> RolesController::updateRole(HttpRequestPtr req, std::string roleId) {
    BaseApiResponse apiResponse;
    auto json = req->getJsonObject();
    if (!json) {
        apiResponse.success = false;
        apiResponse.message = "Invalid JSON payload";
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }
    
    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    RoleDto dto;
    dto.fromJson(*json);

    auto plugin = app().getPlugin<IdentityServicePlugin>();
    auto& roleService = plugin->getRoleService();

    auto result = co_await roleService.update(businessId, dto, roleId);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}

Task<HttpResponsePtr> RolesController::deleteRole(HttpRequestPtr req, std::string roleId) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    auto plugin = app().getPlugin<IdentityServicePlugin>();
    auto& roleService = plugin->getRoleService();

    auto result = co_await roleService.deleteRole(businessId, roleId);

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k400BadRequest);
    co_return resp;
}