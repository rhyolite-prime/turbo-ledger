#pragma once

#include <drogon/HttpController.h>

#include "BaseController.h"

using namespace drogon;



class RolesController : public BaseController<RolesController>
{
public:
    static constexpr const char *PREFIX = "/api/v1/tenants";
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RolesController::getRoles, std::string(PREFIX) + "/get-all", Get);
        ADD_METHOD_TO(RolesController::createRole, std::string(PREFIX) + "/create", Post);
        ADD_METHOD_TO(RolesController::updateRole, std::string(PREFIX) + "/update", Post);
        ADD_METHOD_TO(RolesController::deleteRole, std::string(PREFIX) + "/delete", Delete);
    METHOD_LIST_END


    //handler methods
    void getRoles(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createRole(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateRole(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteRole(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};

