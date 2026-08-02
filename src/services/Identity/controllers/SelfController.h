#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SelfController : public drogon::HttpController<SelfController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/self/";
  METHOD_LIST_BEGIN
    ADD_METHOD_TO(SelfController::signIn, std::string(PREFIX) + "signin", Post, Options);
    ADD_METHOD_TO(SelfController::getDetails, std::string(PREFIX) + "get-details", Get, Options);
    ADD_METHOD_TO(SelfController::updateDetails, std::string(PREFIX) + "update-details", Post, Options);

  METHOD_LIST_END
  Task<HttpResponsePtr> signIn(HttpRequestPtr req);
  Task<HttpResponsePtr> getDetails(HttpRequestPtr req);
  Task<HttpResponsePtr> updateDetails(HttpRequestPtr req);


};
