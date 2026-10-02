//
// Phase 3 — glaccounts (8 endpoints: 6 implemented + 2 bulk-import stubs
// deferred to Phase 8, matching the precedent set by Organization/
// SystemConfig's downloadtemplate/uploadtemplate endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class GlAccountsController : public drogon::HttpController<GlAccountsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/glaccounts/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(GlAccountsController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(GlAccountsController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(GlAccountsController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(GlAccountsController::update, std::string(PREFIX) + "{1}/update", Put, Options,
                     FILTER);
        ADD_METHOD_TO(GlAccountsController::remove, std::string(PREFIX) + "{1}/delete", Delete, Options,
                     FILTER);
        ADD_METHOD_TO(GlAccountsController::templateEndpoint, std::string(PREFIX) + "template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(GlAccountsController::downloadTemplate, std::string(PREFIX) + "downloadtemplate",
                     Get, Options, FILTER);
        ADD_METHOD_TO(GlAccountsController::uploadTemplate, std::string(PREFIX) + "uploadtemplate", Post,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> downloadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> uploadTemplate(HttpRequestPtr req);
};
