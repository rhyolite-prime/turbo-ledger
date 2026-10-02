//
// Phase 6 — creditBureauIntegration (5 endpoints). Backed by a pluggable
// CreditBureauProvider; ships with a deterministic "sandbox" provider only
// (see PortfolioService.cc header note) — there is no real external credit
// bureau integration wired up.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CreditBureauIntegrationController
    : public drogon::HttpController<CreditBureauIntegrationController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/creditBureauIntegration/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CreditBureauIntegrationController::addCreditReport,
                     std::string(PREFIX) + "addCreditReport", Post, Options, FILTER);
        ADD_METHOD_TO(CreditBureauIntegrationController::fetchCreditReport,
                     std::string(PREFIX) + "creditReport", Post, Options, FILTER);
        ADD_METHOD_TO(CreditBureauIntegrationController::getSavedCreditReport,
                     std::string(PREFIX) + "creditReport/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(CreditBureauIntegrationController::saveCreditReport,
                     std::string(PREFIX) + "saveCreditReport", Post, Options, FILTER);
        ADD_METHOD_TO(CreditBureauIntegrationController::deleteCreditReport,
                     std::string(PREFIX) + "deleteCreditReport/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> addCreditReport(HttpRequestPtr req);
    Task<HttpResponsePtr> fetchCreditReport(HttpRequestPtr req);
    Task<HttpResponsePtr> getSavedCreditReport(HttpRequestPtr req, std::string creditBureauId);
    Task<HttpResponsePtr> saveCreditReport(HttpRequestPtr req);
    Task<HttpResponsePtr> deleteCreditReport(HttpRequestPtr req, std::string creditBureauId);
};
