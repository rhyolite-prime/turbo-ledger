#pragma once


#include "BaseController.h"


using namespace drogon;

namespace
{
  const std::string PREFIX = "/api/v1/token-auth";
}

class TokenAuthController : public BaseController<TokenAuthController>
{
  public:
  METHOD_LIST_BEGIN
    ADD_METHOD_TO(TokenAuthController::generateAuthToken, PREFIX + "/user-signin", Post);
  METHOD_LIST_END

  void generateAuthToken(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
