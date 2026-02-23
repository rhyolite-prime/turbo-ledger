#pragma once


#include "BaseController.h"


using namespace drogon;


class AuthController : public BaseController<AuthController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/auth";
  METHOD_LIST_BEGIN
    ADD_METHOD_TO(AuthController::generateAuthToken, std::string(PREFIX) + "/tenant-signin", Post);
    ADD_METHOD_TO(AuthController::generateAuthToken, std::string(PREFIX) + "/host-signin", Post);
    //2 factor
    // after logging in username and password: a token is generated for the user which is used to send and verify the otp
    ADD_METHOD_TO(AuthController::generateAuthToken, std::string(PREFIX) + "/send-otp", Get);
    ADD_METHOD_TO(AuthController::generateAuthToken, std::string(PREFIX) + "/verify-otp", Post);  // returns with a token
    ADD_METHOD_TO(AuthController::generateAuthToken, std::string(PREFIX) + "/get-otp-delivery-methods", Get);  // returns with a token
    ADD_METHOD_TO(AuthController::generateAuthToken, std::string(PREFIX) + "/configure-twofactor", Post);
  METHOD_LIST_END

  void generateAuthToken(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
