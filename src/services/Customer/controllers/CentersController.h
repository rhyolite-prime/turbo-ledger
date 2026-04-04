#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CentersController : public drogon::HttpController<CentersController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/centers/";
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(CentersController::retrieveCenterTemplate, std::string(PREFIX) + "template", Get);
  ADD_METHOD_TO(CentersController::getCenters, std::string(PREFIX) + "get-all", Get);
  ADD_METHOD_TO(CentersController::getCenterDetails, std::string(PREFIX) + "{1}", Get);
  ADD_METHOD_TO(CentersController::createCenter, std::string(PREFIX) + "create", Post);
  ADD_METHOD_TO(CentersController::activateCenter, std::string(PREFIX) + "{1}/activate", Post);
  ADD_METHOD_TO(CentersController::closeCenter, std::string(PREFIX) + "{1}/close", Post);
  ADD_METHOD_TO(CentersController::associateGroupToCenter, std::string(PREFIX) + "{1}/associate-groups", Post);
  ADD_METHOD_TO(CentersController::disassociateGroupToCenter, std::string(PREFIX) + "{1}/disassociate-groups", Post);
  ADD_METHOD_TO(CentersController::getCenterAccountsOverview, std::string(PREFIX) + "{1}/accounts", Get);
  ADD_METHOD_TO(CentersController::generateCollectionSheet, std::string(PREFIX) + "{1}/generate-collection-sheet", Post);
  ADD_METHOD_TO(CentersController::saveCollectionSheet, std::string(PREFIX) + "{1}/save-collection-sheet", Post);
  ADD_METHOD_TO(CentersController::updateCenter, std::string(PREFIX) + "{1}", Put);
  ADD_METHOD_TO(CentersController::deleteCenter, std::string(PREFIX) + "{1}", Delete);
  METHOD_LIST_END

  void retrieveCenterTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getCenters(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getCenterDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void createCenter(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
