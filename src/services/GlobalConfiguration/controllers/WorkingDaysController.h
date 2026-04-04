#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class WorkingDaysController : public drogon::HttpController<WorkingDaysController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/working-days/";
    METHOD_LIST_BEGIN

      ADD_METHOD_TO(WorkingDaysController::getWorkingDaysTemplate, std::string(PREFIX) + "template", Get);
      ADD_METHOD_TO(WorkingDaysController::getWorkingDays, std::string(PREFIX) + "get-all", Get);
      ADD_METHOD_TO(WorkingDaysController::createWorkingDay, std::string(PREFIX) + "create", Post);
      ADD_METHOD_TO(WorkingDaysController::updateWorkingDay, std::string(PREFIX) + "{1}", Put);

    METHOD_LIST_END

  void getWorkingDaysTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getWorkingDays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void createWorkingDay(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void updateWorkingDay(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
