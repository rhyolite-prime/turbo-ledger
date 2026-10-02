//
// Phase 5 — standinginstructions (5) + standinginstructionrunhistory (1) =
// 6 endpoints in one controller (the run-history resource is a trivial
// read-only sibling of standinginstructions, matching Fineract's own API
// grouping). `update` also serves Fineract's "delete via PUT command=delete"
// convention — see updateStandingInstruction's doc comment in the service
// header for why there is no destructive DELETE route.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class StandingInstructionsController
    : public drogon::HttpController<StandingInstructionsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/standinginstructions/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(StandingInstructionsController::getAll, std::string(PREFIX) + "get-all", Get,
                     Options, FILTER);
        ADD_METHOD_TO(StandingInstructionsController::create, std::string(PREFIX) + "create", Post,
                     Options, FILTER);
        ADD_METHOD_TO(StandingInstructionsController::getDetails,
                     std::string(PREFIX) + "get-detail/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(StandingInstructionsController::update, std::string(PREFIX) + "{1}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(StandingInstructionsController::templateEndpoint,
                     std::string(PREFIX) + "template", Get, Options, FILTER);
        ADD_METHOD_TO(StandingInstructionsController::runHistory,
                     "/api/v1/standinginstructionrunhistory/get-all", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> runHistory(HttpRequestPtr req);
};
