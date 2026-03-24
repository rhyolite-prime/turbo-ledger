#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class WorkingDaysController : public drogon::HttpController<WorkingDaysController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/working-days/";
    METHOD_LIST_BEGIN
      ADD_METHOD_TO(WorkingDaysController::getWorkingDaysTemplate, std::string(PREFIX) + "template", Get);


    METHOD_LIST_END

  void getWorkingDaysTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
