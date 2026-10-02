//
// Phase 8 — reportmailingjobs (6 endpoints) + reportmailingjobrunhistory
// (1 endpoint): scheduled report-to-email jobs. Links a report by name/
// params only (the Reporting service's `runreports` executor comes later
// in this phase) and a job "run" would be the same disclosed no-op pattern
// HeartBeat's `jobs` uses — no run-now action exists yet for this
// resource since nothing in this slice actually executes a report.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ReportMailingJobsController : public drogon::HttpController<ReportMailingJobsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/reportmailingjobs";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ReportMailingJobsController::creationTemplate, std::string(PREFIX) + "/template", Get,
                     Options, FILTER);

        ADD_METHOD_TO(ReportMailingJobsController::getAll, std::string(PREFIX), Get, Options, FILTER);
        ADD_METHOD_TO(ReportMailingJobsController::create, std::string(PREFIX), Post, Options, FILTER);

        ADD_METHOD_TO(ReportMailingJobsController::getOne, std::string(PREFIX) + "/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(ReportMailingJobsController::update, std::string(PREFIX) + "/{1}", Put, Options,
                     FILTER);
        ADD_METHOD_TO(ReportMailingJobsController::remove, std::string(PREFIX) + "/{1}", Delete, Options,
                     FILTER);

        ADD_METHOD_TO(ReportMailingJobsController::runHistory, "/api/v1/reportmailingjobrunhistory", Get,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> creationTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getOne(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> runHistory(HttpRequestPtr req);
};
