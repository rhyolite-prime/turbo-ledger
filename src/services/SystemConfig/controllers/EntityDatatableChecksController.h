//
// Phase 2 — entity-datatable checks (4 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class EntityDatatableChecksController
    : public drogon::HttpController<EntityDatatableChecksController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/entitydatatablechecks/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(EntityDatatableChecksController::getAll,     std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(EntityDatatableChecksController::create,     std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(EntityDatatableChecksController::getTemplate, std::string(PREFIX) + "template", Get, Options, FILTER);
        ADD_METHOD_TO(EntityDatatableChecksController::remove,     std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
