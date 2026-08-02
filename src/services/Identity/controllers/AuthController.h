#pragma once

#include <drogon/HttpController.h>

using namespace drogon;


class AuthController : public drogon::HttpController<AuthController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/auth/";
  METHOD_LIST_BEGIN
    ADD_METHOD_TO(AuthController::signIn, std::string(PREFIX) + "signin", Post, Options);
    //2 factor
    // after logging in username and password: a token is generated for the user which is used to send and verify the otp
    ADD_METHOD_TO(AuthController::sendOtp, std::string(PREFIX) + "send-otp", Get, Options);
    ADD_METHOD_TO(AuthController::verifyOtp, std::string(PREFIX) + "verify-otp", Post, Options);  // returns with a token
  ADD_METHOD_TO(AuthController::changeUserPassword, std::string(PREFIX) + "change-user-password", Post, Options, "JwtAuthFilter");
  METHOD_LIST_END

  Task<HttpResponsePtr> signIn(HttpRequestPtr req);
  Task<HttpResponsePtr> sendOtp(HttpRequestPtr req);
  Task<HttpResponsePtr> verifyOtp(HttpRequestPtr req);
  Task<HttpResponsePtr> changeUserPassword(HttpRequestPtr req);

};
