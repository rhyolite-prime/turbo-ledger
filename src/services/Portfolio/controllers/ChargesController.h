#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ChargesController : public drogon::HttpController<ChargesController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/charges/";
  METHOD_LIST_BEGIN
    ADD_METHOD_TO(ChargesController::retrieveTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(ChargesController::getCharges, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(ChargesController::createCharge, std::string(PREFIX) + "create", Post); //create or define charge.
    ADD_METHOD_TO(ChargesController::updateCharge, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(ChargesController::deleteCharge, std::string(PREFIX) + "{1}", Delete);
  METHOD_LIST_END

  void retrieveTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getCharges(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void createCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void updateCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void deleteCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);


};
