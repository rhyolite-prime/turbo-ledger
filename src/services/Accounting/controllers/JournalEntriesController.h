//
// Phase 3 — journalentries (8 endpoints: create, search/list, get-detail,
// openingbalance, provisioning, template, reverse, recalculate-running-
// balance). Bulk downloadtemplate/uploadtemplate are deferred to Phase 8
// (same precedent as Organization/SystemConfig); reverse and running-balance
// recalculation replace them here since the Phase 3 exit criteria requires
// working reversal and reconciliation, which matter far more than bulk
// import for a ledger.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class JournalEntriesController : public drogon::HttpController<JournalEntriesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/journalentries/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(JournalEntriesController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(JournalEntriesController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(JournalEntriesController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(JournalEntriesController::openingBalance, std::string(PREFIX) + "openingbalance",
                     Get, Options, FILTER);
        ADD_METHOD_TO(JournalEntriesController::provisioning, std::string(PREFIX) + "provisioning", Get,
                     Options, FILTER);
        ADD_METHOD_TO(JournalEntriesController::templateEndpoint, std::string(PREFIX) + "template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(JournalEntriesController::reverse, std::string(PREFIX) + "{1}/reverse", Post,
                     Options, FILTER);
        ADD_METHOD_TO(JournalEntriesController::recalculateRunningBalance,
                     std::string(PREFIX) + "{1}/recalculate-running-balance", Post, Options, FILTER);
        ADD_METHOD_TO(JournalEntriesController::downloadTemplate,
                     std::string(PREFIX) + "downloadtemplate", Get, Options, FILTER);
        ADD_METHOD_TO(JournalEntriesController::uploadTemplate, std::string(PREFIX) + "uploadtemplate",
                     Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> openingBalance(HttpRequestPtr req);
    Task<HttpResponsePtr> provisioning(HttpRequestPtr req);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> reverse(HttpRequestPtr req, std::string transactionId);
    Task<HttpResponsePtr> recalculateRunningBalance(HttpRequestPtr req, std::string transactionId);
    Task<HttpResponsePtr> downloadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> uploadTemplate(HttpRequestPtr req);
};
