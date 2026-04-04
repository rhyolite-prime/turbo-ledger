#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class JobsController : public drogon::HttpController<JobsController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/jobs/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(JobsController::getJobs, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(JobsController::retrieveJobDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(JobsController::createJob, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(JobsController::updateJob, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(JobsController::executeJob, std::string(PREFIX) + "{1}/execute", Get);
    ADD_METHOD_TO(JobsController::retrieveJobRunHistory, std::string(PREFIX) + "{1}/run-history", Get);
    METHOD_LIST_END

    void getJobs(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveJobDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createJob(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateJob(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void executeJob(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveJobRunHistory(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
