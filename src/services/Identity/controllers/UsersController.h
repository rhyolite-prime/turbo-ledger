#pragma once

#include <drogon/HttpController.h>

using namespace drogon;


class UsersController : public drogon::HttpController<UsersController>
{
    public:
    static constexpr const char *PREFIX = "/api/v1/users/";
      METHOD_LIST_BEGIN
          ADD_METHOD_TO(UsersController::getAllUsers, std::string(PREFIX) + "get-all", Get, Options, "JwtAuthFilter");
          ADD_METHOD_TO(UsersController::getDetails, std::string(PREFIX) + "get-details/{1}", Get, Options, "JwtAuthFilter");
          ADD_METHOD_TO(UsersController::signIn, std::string(PREFIX) + "sign-in", Post, Options, "JwtAuthFilter");
          ADD_METHOD_TO(UsersController::lockUserAccount, std::string(PREFIX) + "lock-account/{1}", Get, Options, "JwtAuthFilter");
          ADD_METHOD_TO(UsersController::unLockUserAccount, std::string(PREFIX) + "unlock-account/{1}", Get, Options, "JwtAuthFilter");
          ADD_METHOD_TO(UsersController::activateAccount, std::string(PREFIX) + "activate-account/{1}", Get, Options, "JwtAuthFilter");
          ADD_METHOD_TO(UsersController::deActivateAccount, std::string(PREFIX) + "deactivate-account/{1}", Get, Options, "JwtAuthFilter");
          ADD_METHOD_TO(UsersController::createUser, std::string(PREFIX) + "create", Post, Options, "JwtAuthFilter");
          ADD_METHOD_TO(UsersController::updateUser, std::string(PREFIX) + "update/{1}", Put, Options, "JwtAuthFilter");
          ADD_METHOD_TO(UsersController::deleteUser, std::string(PREFIX) + "delete/{1}", Delete, Options, "JwtAuthFilter");
      METHOD_LIST_END

    //handler methods
    Task<HttpResponsePtr> getAllUsers(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> signIn(HttpRequestPtr req);
    Task<HttpResponsePtr> lockUserAccount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> unLockUserAccount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> activateAccount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> deActivateAccount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> createUser(HttpRequestPtr req);
    Task<HttpResponsePtr> updateUser(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> deleteUser(HttpRequestPtr req, std::string id);



};
