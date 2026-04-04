#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AccountNumberFormatsController : public drogon::HttpController<AccountNumberFormatsController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/account-number-formats/";

  METHOD_LIST_BEGIN
  ADD_METHOD_TO(AccountNumberFormatsController::getAnf, std::string(PREFIX) + "get-all", Get);
  ADD_METHOD_TO(AccountNumberFormatsController::retrieveAnfTemplate, std::string(PREFIX) + "template", Get);
  ADD_METHOD_TO(AccountNumberFormatsController::retrieveAnfDetails, std::string(PREFIX) + "{1}", Get);
  ADD_METHOD_TO(AccountNumberFormatsController::createAnf, std::string(PREFIX) + "create", Post);
  ADD_METHOD_TO(AccountNumberFormatsController::updateAnf, std::string(PREFIX) + "{1}", Put);
  ADD_METHOD_TO(AccountNumberFormatsController::deleteAnf, std::string(PREFIX) + "{1}", Delete);
  METHOD_LIST_END

  void getAnf(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void retrieveAnfTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void retrieveAnfDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void createAnf(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void updateAnf(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void deleteAnf(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
