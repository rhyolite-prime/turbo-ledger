//
// Phase 5 — charges (6 endpoints): the deposits-side charge catalog shared by
// savings/FD/RD products and accounts.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ChargesController : public drogon::HttpController<ChargesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/charges/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ChargesController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ChargesController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(ChargesController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(ChargesController::update, std::string(PREFIX) + "{1}/update", Put, Options, FILTER);
        ADD_METHOD_TO(ChargesController::remove, std::string(PREFIX) + "{1}/delete", Delete, Options,
                     FILTER);
        ADD_METHOD_TO(ChargesController::templateEndpoint, std::string(PREFIX) + "template", Get, Options,
                     FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
};
