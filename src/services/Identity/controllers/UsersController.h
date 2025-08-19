#pragma once

#include "BaseController.h"

using namespace drogon;

namespace
{
    const std::string PREFIX = "/api/v1/users";
}

class UsersController : public BaseController<UsersController>
{
    public:
      METHOD_LIST_BEGIN
          ADD_METHOD_TO(UsersController::getUsers, PREFIX + "/get-all", Get);
          ADD_METHOD_TO(UsersController::generateAuthToken, PREFIX + "/generate-jwt-token", Post);
          ADD_METHOD_TO(UsersController::lockUserAccount, PREFIX + "/lock-account", Get);
          ADD_METHOD_TO(UsersController::unLockUserAccount, PREFIX + "/unlock-account", Get);
          ADD_METHOD_TO(UsersController::activateAccount, PREFIX + "/activate-account", Get);
          ADD_METHOD_TO(UsersController::deActivateAccount, PREFIX + "/deactivate-account", Get);
          ADD_METHOD_TO(UsersController::createUser, PREFIX + "/create", Post);
          ADD_METHOD_TO(UsersController::updateUser, PREFIX + "/update", Post);
          ADD_METHOD_TO(UsersController::deleteUser, PREFIX + "/delete", Delete);
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
