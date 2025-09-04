#include "RolesController.h"
#include "plugins/IdentityServicePlugin.h"

namespace turbo_ledger_identity::dto {
    class BaseApiResponse;
}


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
    // write your application logic here
}

void RolesController::updateRole(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}

void RolesController::deleteRole(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}