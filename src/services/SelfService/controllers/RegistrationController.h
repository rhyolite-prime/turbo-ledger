//
// Phase 9 — self/registration, self/registration/user, self/authentication,
// self/userdetails, self/user (6 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class RegistrationController : public drogon::HttpController<RegistrationController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/self/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RegistrationController::submitRegistration, std::string(PREFIX) + "registration",
                     Post, Options, FILTER);
        ADD_METHOD_TO(RegistrationController::createRegistrationUser,
                     std::string(PREFIX) + "registration/user", Post, Options, FILTER);
        ADD_METHOD_TO(RegistrationController::authenticate, std::string(PREFIX) + "authentication", Post,
                     Options, FILTER);
        ADD_METHOD_TO(RegistrationController::userDetails, std::string(PREFIX) + "userdetails", Get,
                     Options, FILTER);
        ADD_METHOD_TO(RegistrationController::updateUser, std::string(PREFIX) + "user", Put, Options,
                     FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> submitRegistration(HttpRequestPtr req);
    Task<HttpResponsePtr> createRegistrationUser(HttpRequestPtr req);
    Task<HttpResponsePtr> authenticate(HttpRequestPtr req);
    Task<HttpResponsePtr> userDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> updateUser(HttpRequestPtr req);
};
