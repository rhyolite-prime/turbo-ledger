//
// Phase 1 — tenant-scoped role management.
// All routes require the gateway-signed TL-Context (turbo::TrustedContextFilter).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class RolesController : public drogon::HttpController<RolesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/roles/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RolesController::getRoles,          std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(RolesController::getDetails,        std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(RolesController::createRole,        std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(RolesController::updateRole,        std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(RolesController::deleteRole,        std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
        ADD_METHOD_TO(RolesController::enableRole,        std::string(PREFIX) + "enable/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(RolesController::disableRole,       std::string(PREFIX) + "disable/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(RolesController::updatePermissions, std::string(PREFIX) + "update-permissions/{1}", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getRoles(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> createRole(HttpRequestPtr req);
    Task<HttpResponsePtr> updateRole(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> deleteRole(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> enableRole(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> disableRole(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> updatePermissions(HttpRequestPtr req, std::string id);
};
