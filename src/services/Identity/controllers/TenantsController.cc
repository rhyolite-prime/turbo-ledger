#include "TenantsController.h"
#include "dto/CreateTenantDto.h"
#include "plugins/IdentityServicePlugin.h"

void TenantsController::getTenants(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{

    int pageSize = 10; // Default page size
    int pageNo = 1;    //  Default page number

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

    std::string query = req->getParameter("query");
    if (query.empty()) {
        query = ""; // Default to empty string if not specified
    }

    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& tenantService = plugin->getTenantService();

    tenantService.getTenants(pageNo, pageSize, query, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        callback(resp);
    });


}


void TenantsController::createTenant(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // Parse JSON from request body
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

    turbo_ledger_identity::dto::CreateTenantDto tenantDto;
    tenantDto.fromJson(*jsonBody);

    // Get tenant service from plugin
    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& tenantService = plugin->getTenantService();

    tenantService.createTenant(tenantDto, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        callback(resp);
    });

}

void TenantsController::updateConnectionString(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // Parse JSON from request body
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

    // Extract id and connectionString from the JSON body
    if (!(*jsonBody).isMember("id") || !(*jsonBody).isMember("connectionString")) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing required fields: id and connectionString";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    std::string id = (*jsonBody)["id"].asString();
    std::string connectionString = (*jsonBody)["connectionString"].asString();

    // Get tenant service from plugin
    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& tenantService = plugin->getTenantService();

    // Call service method to update connection string
    tenantService.updateConnectionString(id, connectionString, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        callback(resp);
    });
}


void TenantsController::updateTenant(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{

    // Parse JSON from request body
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

    // Create DTO and populate it
    turbo_ledger_identity::dto::UpdateTenantDto tenantDto;
    tenantDto.fromJson(*jsonBody);

    // Get tenant service from plugin
    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& tenantService = plugin->getTenantService();

    // Call service method to update tenant
    tenantService.updateTenant(tenantDto, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        callback(resp);
    });
}

void TenantsController::activate(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // Extract the tenant ID from the request parameters
    if (req->getParameter("id").empty()) {
        // Missing tenant ID - return early
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing required parameter: id";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    std::string id = req->getParameter("id");

    // Get tenant service from plugin
    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& tenantService = plugin->getTenantService();

    // Call service method to activate the tenant account
    tenantService.activateTenantAccount(id, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        callback(resp);
    });
}


void TenantsController::deactivate(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // Extract the tenant ID from the request parameters
    if (req->getParameter("id").empty()) {
        // Missing tenant ID - return early
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing required parameter: id";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    std::string id = req->getParameter("id");

    // Get tenant service from plugin
    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& tenantService = plugin->getTenantService();

    // Call service method to deactivate the tenant account
    tenantService.deactivateTenantAccount(id, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        callback(resp);
    });
}


void TenantsController::deleteTenant(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    // Extract the tenant ID from the request parameters
    if (req->getParameter("id").empty()) {
        // Missing tenant ID - return early
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing required parameter: id";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    std::string id = req->getParameter("id");

    // Get tenant service from plugin
    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& tenantService = plugin->getTenantService();

    // Call service method to delete the tenant
    tenantService.deleteTenant(id, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        callback(resp);
    });
}
