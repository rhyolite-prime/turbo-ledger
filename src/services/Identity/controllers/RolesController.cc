#include "RolesController.h"
#include "dto/UpdateRoleDto.h"
#include "dto/BaseApiResponse.h"
#include "plugins/IdentityServicePlugin.h"




void RolesController::getRoles(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{

    // write your application logic here
    int pageSize = 10; // Default page size
    int pageNo = 1;    // Default page number

    if (!req->getParameter("pageSize").empty()) {
        try {
            pageSize = std::stoi(req->getParameter("pageSize"));
            pageSize = std::max(1, std::min(100, pageSize)); // Limit between 1-100
        } catch (...) {
            // Keep default if conversion fails
        }
    }

    if (!req->getParameter("pageNo").empty()) {
        try {
            pageNo = std::stoi(req->getParameter("pageNo"));
            pageNo = std::max(1, pageNo); // Ensure page number is at least 1
        } catch (...) {
            // Keep default if conversion fails
        }
    }

    std::string tenantId;
    try {
        tenantId = getTenantFromRequest(req);
    } catch (const std::runtime_error& e) {
        // Handle error (e.g., return 400 Bad Request)
    }

    std::string query = req->getParameter("query");
    if (query.empty()) {
        query = ""; // Default to empty string if not specified
    }

    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& roleService = plugin->getRoleService();


    roleService.getRoles(pageNo, pageSize, query, tenantId, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        callback(resp);
    });

}


void RolesController::createRole(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto jsonBody = req->getJsonObject();

    if (!jsonBody) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Invalid JSON body";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    turbo_ledger_identity::dto::CreateRoleDto roleData;

    try {

        roleData.fromJson(*jsonBody);

    } catch (const std::exception& e) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing or invalid required fields";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    // Get tenant ID from the request via the helper in BaseController
    std::string tenantId;
    try
    {
        tenantId = getTenantFromRequest(req);
    }
    catch (const std::runtime_error& e)
    {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = e.what();
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& roleService = plugin->getRoleService();

    roleService.createRole(roleData, tenantId, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        resp->setStatusCode(result.success ? k201Created : k500InternalServerError);
        callback(resp);
    });
}

void RolesController::updateRole(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto jsonBody = req->getJsonObject();
    if (!jsonBody) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Invalid JSON body";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    std::string tenantId = getTenantFromRequest(req);

    turbo_ledger_identity::dto::UpdateRoleDto roleData;

    try {

        roleData.fromJson(*jsonBody);

    } catch (const std::exception& e) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing or invalid required fields";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& roleService = plugin->getRoleService();

    roleService.updateRole(roleData, tenantId, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        resp->setStatusCode(result.success ? k200OK : k500InternalServerError);
        callback(resp);
    });
}

void RolesController::deleteRole(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}