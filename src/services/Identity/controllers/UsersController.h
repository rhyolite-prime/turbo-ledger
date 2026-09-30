//
// Phase 1 — tenant-scoped user management (RBAC + maker-checker aware).
// All routes require the gateway-signed TL-Context (turbo::TrustedContextFilter).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class UsersController : public drogon::HttpController<UsersController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/users/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(UsersController::getAllUsers,   std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(UsersController::getDetails,    std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(UsersController::createUser,    std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(UsersController::updateUser,    std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(UsersController::deleteUser,    std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
        ADD_METHOD_TO(UsersController::activate,      std::string(PREFIX) + "activate/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(UsersController::deactivate,    std::string(PREFIX) + "deactivate/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(UsersController::lockAccount,   std::string(PREFIX) + "lock/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(UsersController::unlockAccount, std::string(PREFIX) + "unlock/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(UsersController::assignRoles,   std::string(PREFIX) + "assign-roles/{1}", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAllUsers(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> createUser(HttpRequestPtr req);
    Task<HttpResponsePtr> updateUser(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> deleteUser(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> activate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> deactivate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> lockAccount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> unlockAccount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> assignRoles(HttpRequestPtr req, std::string id);
};
