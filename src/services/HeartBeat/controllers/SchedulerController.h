#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SchedulerController : public drogon::HttpController<SchedulerController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/scheduler/";

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SchedulerController::checkStatus, std::string(PREFIX) + "check-status", Get);
    ADD_METHOD_TO(SchedulerController::activateScheduleEngine, std::string(PREFIX) + "activate", Get); //Activates the scheduler job service.
    ADD_METHOD_TO(SchedulerController::suspendScheduleEngine, std::string(PREFIX) + "suspend", Get); //Suspends the scheduler job service.
    METHOD_LIST_END

    void checkStatus(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void activateScheduleEngine(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void suspendScheduleEngine(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
