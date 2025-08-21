#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace
{
    const std::string PREFIX = "/api/v1/tenants";
}

class TenantsController : public drogon::HttpController<TenantsController>
{

    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(TenantsController::getTenants, PREFIX + "/get-all", Get);
            ADD_METHOD_TO(TenantsController::activate, PREFIX + "/activate", Get);
            ADD_METHOD_TO(TenantsController::deactivate, PREFIX + "/deactivate", Get);
            ADD_METHOD_TO(TenantsController::updateConnectionString, PREFIX + "/update-connection-string", Post);
            ADD_METHOD_TO(TenantsController::createTenant, PREFIX + "/create", Post);
            ADD_METHOD_TO(TenantsController::updateTenant, PREFIX + "/update", Post);
            ADD_METHOD_TO(TenantsController::deleteTenant, PREFIX + "/delete", Delete);
        METHOD_LIST_END


        //handler methods
        void getTenants(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        void createTenant(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        void updateConnectionString(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        void updateTenant(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        void activate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        void deactivate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        void deleteTenant(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
