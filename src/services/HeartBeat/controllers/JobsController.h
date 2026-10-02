//
// Phase 8 — jobs (14 endpoints: job registry CRUD/read, manual/inline
// execution, run history, business-step pipeline). Addressable both by
// `shortName` (Fineract's newer style) and by `jobId` (legacy style),
// backed by the same HeartBeatService methods.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class JobsController : public drogon::HttpController<JobsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/jobs/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(JobsController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(JobsController::names, std::string(PREFIX) + "names", Get, Options, FILTER);

        ADD_METHOD_TO(JobsController::getByShortName, std::string(PREFIX) + "short-name/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(JobsController::runByShortName, std::string(PREFIX) + "short-name/{1}", Post, Options,
                     FILTER);
        ADD_METHOD_TO(JobsController::updateByShortName, std::string(PREFIX) + "short-name/{1}", Put, Options,
                     FILTER);
        ADD_METHOD_TO(JobsController::runHistoryByShortName,
                     std::string(PREFIX) + "short-name/{1}/runhistory", Get, Options, FILTER);

        ADD_METHOD_TO(JobsController::availableSteps, std::string(PREFIX) + "{1}/available-steps", Get,
                     Options, FILTER);
        ADD_METHOD_TO(JobsController::runInline, std::string(PREFIX) + "{1}/inline", Post, Options, FILTER);
        ADD_METHOD_TO(JobsController::getSteps, std::string(PREFIX) + "{1}/steps", Get, Options, FILTER);
        ADD_METHOD_TO(JobsController::updateSteps, std::string(PREFIX) + "{1}/steps", Put, Options, FILTER);
        ADD_METHOD_TO(JobsController::runHistoryById, std::string(PREFIX) + "{1}/runhistory", Get, Options,
                     FILTER);

        ADD_METHOD_TO(JobsController::getById, std::string(PREFIX) + "{1}", Get, Options, FILTER);
        ADD_METHOD_TO(JobsController::runById, std::string(PREFIX) + "{1}", Post, Options, FILTER);
        ADD_METHOD_TO(JobsController::updateById, std::string(PREFIX) + "{1}", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> names(HttpRequestPtr req);

    Task<HttpResponsePtr> getByShortName(HttpRequestPtr req, std::string shortName);
    Task<HttpResponsePtr> runByShortName(HttpRequestPtr req, std::string shortName);
    Task<HttpResponsePtr> updateByShortName(HttpRequestPtr req, std::string shortName);
    Task<HttpResponsePtr> runHistoryByShortName(HttpRequestPtr req, std::string shortName);

    Task<HttpResponsePtr> availableSteps(HttpRequestPtr req, std::string jobName);
    Task<HttpResponsePtr> runInline(HttpRequestPtr req, std::string jobName);
    Task<HttpResponsePtr> getSteps(HttpRequestPtr req, std::string jobName);
    Task<HttpResponsePtr> updateSteps(HttpRequestPtr req, std::string jobName);
    Task<HttpResponsePtr> runHistoryById(HttpRequestPtr req, std::string jobId);

    Task<HttpResponsePtr> getById(HttpRequestPtr req, std::string jobId);
    Task<HttpResponsePtr> runById(HttpRequestPtr req, std::string jobId);
    Task<HttpResponsePtr> updateById(HttpRequestPtr req, std::string jobId);
};
