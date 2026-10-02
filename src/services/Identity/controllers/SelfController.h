//
// Phase 1 — authenticated self-service profile endpoints.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SelfController : public drogon::HttpController<SelfController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/self/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(SelfController::userDetails,    std::string(PREFIX) + "userdetails", Get, Options, FILTER);
        ADD_METHOD_TO(SelfController::changePassword, std::string(PREFIX) + "change-password", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> userDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> changePassword(HttpRequestPtr req);
};
