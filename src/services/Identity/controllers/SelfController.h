#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SelfController : public drogon::HttpController<SelfController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/self";
  METHOD_LIST_BEGIN
    ADD_METHOD_TO(SelfController::generateAuthToken, std::string(PREFIX) + "/signin", Post);
    ADD_METHOD_TO(SelfController::generateAuthToken, std::string(PREFIX) + "/get-details", Get);
    ADD_METHOD_TO(SelfController::generateAuthToken, std::string(PREFIX) + "/update-details", Post);

  METHOD_LIST_END

  void generateAuthToken(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
