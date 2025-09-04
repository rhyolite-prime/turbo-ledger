#pragma once

#include <drogon/HttpController.h>

#include "BaseController.h"

using namespace drogon;

namespace
{
    const std::string PREFIX = "/api/v1/roles";
}

class RolesController : public BaseController<RolesController>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RolesController::getRoles, PREFIX + "/get-all", Get);
        ADD_METHOD_TO(RolesController::createRole, PREFIX + "/create", Post);
        ADD_METHOD_TO(RolesController::updateRole, PREFIX + "/update", Post);
        ADD_METHOD_TO(RolesController::deleteRole, PREFIX + "/delete", Delete);
    METHOD_LIST_END


    //handler methods
    void getRoles(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createRole(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateRole(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteRole(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};

