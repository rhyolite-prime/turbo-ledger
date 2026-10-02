//
// Phase 9 — self/runreports, self/surveys* — disclosed stubs. No
// Reporting/PPI subsystem exists in this build (see IMPLEMENTATION_PLAN.md).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SelfMiscController : public drogon::HttpController<SelfMiscController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/self/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(SelfMiscController::runReport, std::string(PREFIX) + "runreports/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SelfMiscController::surveys, std::string(PREFIX) + "surveys", Get, Options,
                     FILTER);
        ADD_METHOD_TO(SelfMiscController::surveyScorecards,
                     std::string(PREFIX) + "surveys/scorecards/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(SelfMiscController::submitSurveyScorecard,
                     std::string(PREFIX) + "surveys/{1}/scorecards", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> runReport(HttpRequestPtr req, std::string reportName);
    Task<HttpResponsePtr> surveys(HttpRequestPtr req);
    Task<HttpResponsePtr> surveyScorecards(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> submitSurveyScorecard(HttpRequestPtr req, std::string surveyId);
};
