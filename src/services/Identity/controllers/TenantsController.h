#pragma once

#include <drogon/HttpController.h>

using namespace drogon;


class TenantsController : public drogon::HttpController<TenantsController>
{

    public:
        static constexpr const char *PREFIX = "/api/v1/tenants";
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(TenantsController::getTenants, std::string(PREFIX) + "/get-all", Get);
            ADD_METHOD_TO(TenantsController::activate, std::string(PREFIX) + "/activate", Get);
            ADD_METHOD_TO(TenantsController::deactivate, std::string(PREFIX) + "/deactivate", Get);
            ADD_METHOD_TO(TenantsController::updateConnectionString, std::string(PREFIX) + "/update-connection-string", Post);
            ADD_METHOD_TO(TenantsController::createTenant, std::string(PREFIX) + "/create", Post);
            ADD_METHOD_TO(TenantsController::updateTenant, std::string(PREFIX) + "/update", Post);
            ADD_METHOD_TO(TenantsController::deleteTenant, std::string(PREFIX) + "/delete", Delete);
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
