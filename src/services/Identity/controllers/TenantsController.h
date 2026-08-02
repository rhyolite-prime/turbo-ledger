#pragma once

#include <drogon/HttpController.h>

using namespace drogon;


class TenantsController : public drogon::HttpController<TenantsController>
{

    public:
        static constexpr const char *PREFIX = "/api/v1/tenants/";
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(TenantsController::getTenants, std::string(PREFIX) + "get-all", Get, Options);
            ADD_METHOD_TO(TenantsController::updateStatus, std::string(PREFIX) + "update-status/{1}", Get, Options);
            ADD_METHOD_TO(TenantsController::createTenant, std::string(PREFIX) + "create", Post, Options);
            ADD_METHOD_TO(TenantsController::updateTenant, std::string(PREFIX) + "update/{1}", Put, Options);
            ADD_METHOD_TO(TenantsController::deleteTenant, std::string(PREFIX) + "delete", Delete, Options);
        METHOD_LIST_END



    Task<HttpResponsePtr> getTenants(HttpRequestPtr req);
    Task<HttpResponsePtr> updateStatus(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> createTenant(HttpRequestPtr req);
    Task<HttpResponsePtr> updateTenant(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> deleteTenant(HttpRequestPtr req);
};
