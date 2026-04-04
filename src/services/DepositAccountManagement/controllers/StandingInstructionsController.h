#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class StandingInstructionsController : public drogon::HttpController<StandingInstructionsController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/standing-instructions/";
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(StandingInstructionsController::retrieveTemplate, std::string(PREFIX) + "template", Get);
  ADD_METHOD_TO(StandingInstructionsController::getStandingInstructions, std::string(PREFIX) + "get-all", Get);
  ADD_METHOD_TO(StandingInstructionsController::getStandingInstructionsLogHistory, std::string(PREFIX) + "get-history", Get);
  ADD_METHOD_TO(StandingInstructionsController::retrieveStandingInstruction, std::string(PREFIX) + "{1}", Get);
  ADD_METHOD_TO(StandingInstructionsController::createStandingInstruction, std::string(PREFIX) + "create", Post);
  ADD_METHOD_TO(StandingInstructionsController::updateStandingInstruction, std::string(PREFIX) + "{1}/update", Put);
  ADD_METHOD_TO(StandingInstructionsController::deleteStandingInstruction, std::string(PREFIX) + "{1}/delete", Delete);
  METHOD_LIST_END

  void getStandingInstructions(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getStandingInstructionsLogHistory(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void retrieveTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void retrieveStandingInstruction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void createStandingInstruction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void updateStandingInstruction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void deleteStandingInstruction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
