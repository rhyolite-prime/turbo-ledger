//
// Phase 8 — templates (8 endpoints): CRUD for reusable text templates plus
// a merge/render action and create/edit form scaffolding, matching
// Fineract's `v1/templates` ("UGD") API shape.
//
// Routing deviation from the usual explicit-action-suffix convention (e.g.
// GroupsController's "get-all"): PREFIX here has no trailing slash, so the
// bare resource path itself ("/api/v1/templates") is a valid GET/POST
// target without ambiguity — every other route under this prefix adds a
// literal "/template" or "/{id}" segment, so the gateway's prefix match
// (a plain string-prefix check) still routes every sub-path correctly to
// this one service.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TemplatesController : public drogon::HttpController<TemplatesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/templates";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(TemplatesController::creationTemplate, std::string(PREFIX) + "/template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(TemplatesController::editTemplate, std::string(PREFIX) + "/{1}/template", Get,
                     Options, FILTER);

        ADD_METHOD_TO(TemplatesController::getAll, std::string(PREFIX), Get, Options, FILTER);
        ADD_METHOD_TO(TemplatesController::create, std::string(PREFIX), Post, Options, FILTER);

        ADD_METHOD_TO(TemplatesController::getOne, std::string(PREFIX) + "/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(TemplatesController::merge, std::string(PREFIX) + "/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(TemplatesController::update, std::string(PREFIX) + "/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(TemplatesController::remove, std::string(PREFIX) + "/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> creationTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> editTemplate(HttpRequestPtr req, std::string templateId);

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);

    Task<HttpResponsePtr> getOne(HttpRequestPtr req, std::string templateId);
    Task<HttpResponsePtr> merge(HttpRequestPtr req, std::string templateId);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string templateId);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string templateId);
};
