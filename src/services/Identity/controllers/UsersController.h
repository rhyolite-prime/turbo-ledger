#pragma once

#include "BaseController.h"

using namespace drogon;


class UsersController : public BaseController<UsersController>
{
    public:
    static constexpr const char *PREFIX = "/api/v1/users";
      METHOD_LIST_BEGIN
          ADD_METHOD_TO(UsersController::getUsers, std::string(PREFIX) + "/get-all", Get);
          ADD_METHOD_TO(UsersController::getUsers, std::string(PREFIX) + "/get-details", Get);
          ADD_METHOD_TO(UsersController::getUsers, std::string(PREFIX) + "/get-permissions", Get);
          ADD_METHOD_TO(UsersController::generateAuthToken, std::string(PREFIX) + "/generate-jwt-token", Post);
          ADD_METHOD_TO(UsersController::lockUserAccount, std::string(PREFIX) + "/lock-account", Get);
          ADD_METHOD_TO(UsersController::unLockUserAccount, std::string(PREFIX) + "/unlock-account", Get);
          ADD_METHOD_TO(UsersController::activateAccount, std::string(PREFIX) + "/activate-account", Get);
          ADD_METHOD_TO(UsersController::deActivateAccount, std::string(PREFIX) + "/deactivate-account", Get);
          ADD_METHOD_TO(UsersController::createUser, std::string(PREFIX) + "/create", Post);
          ADD_METHOD_TO(UsersController::updateUser, std::string(PREFIX) + "/update", Post);
          ADD_METHOD_TO(UsersController::deleteUser, std::string(PREFIX) + "/delete", Delete);
      METHOD_LIST_END

    //handler methods
    void getUsers(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void generateAuthToken(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void lockUserAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void unLockUserAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void activateAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deActivateAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);



};
