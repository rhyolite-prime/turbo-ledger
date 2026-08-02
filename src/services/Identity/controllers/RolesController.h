#pragma once

#include <drogon/HttpController.h>


using namespace drogon;



class RolesController : public drogon::HttpController<RolesController>
{
public:
    static constexpr const char *PREFIX = "/api/v1/roles/";
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RolesController::getRoles, std::string(PREFIX) + "get-all", Get);
        ADD_METHOD_TO(RolesController::createRole, std::string(PREFIX) + "create", Post);
        ADD_METHOD_TO(RolesController::updateRole, std::string(PREFIX) + "update/{1}", Put);
        ADD_METHOD_TO(RolesController::deleteRole, std::string(PREFIX) + "delete/{1}", Delete);
    METHOD_LIST_END


    //handler methods
    Task<HttpResponsePtr> getRoles(HttpRequestPtr req);
    Task<HttpResponsePtr> createRole(HttpRequestPtr req);
    Task<HttpResponsePtr> updateRole(HttpRequestPtr req);
    Task<HttpResponsePtr> deleteRole(HttpRequestPtr req);

};

