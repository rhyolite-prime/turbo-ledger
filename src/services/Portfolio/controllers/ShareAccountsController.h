//
// Phase 6 — accounts (8 endpoints in the inventory; the 2 CSV
// template-download/upload endpoints are out of scope, consistent with the
// same omission elsewhere — 5 wired here, `:type` kept for path-shape
// fidelity, see ShareProductsController's header note).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ShareAccountsController : public drogon::HttpController<ShareAccountsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/accounts/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ShareAccountsController::getAll, std::string(PREFIX) + "{1}/get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(ShareAccountsController::create, std::string(PREFIX) + "{1}/create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(ShareAccountsController::getDetails, std::string(PREFIX) + "{1}/get-detail/{2}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(ShareAccountsController::update, std::string(PREFIX) + "{1}/{2}/update", Put, Options,
                     FILTER);
        ADD_METHOD_TO(ShareAccountsController::templateEndpoint, std::string(PREFIX) + "{1}/template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(ShareAccountsController::command, std::string(PREFIX) + "{1}/{2}/command/{3}", Post,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req, std::string type);
    Task<HttpResponsePtr> create(HttpRequestPtr req, std::string type);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string type, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string type, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req, std::string type);
    Task<HttpResponsePtr> command(HttpRequestPtr req, std::string type, std::string id, std::string cmd);
};
