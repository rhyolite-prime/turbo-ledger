//
// Phase 6 — products (6 endpoints). Fineract's `:type` path segment is kept
// (always "share" in practice — Fineract generalized the resource family but
// only ever registered the share-product handler under it) for path-shape
// fidelity with the inventory; the value itself is not branched on.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ShareProductsController : public drogon::HttpController<ShareProductsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/products/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ShareProductsController::getAll, std::string(PREFIX) + "{1}/get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(ShareProductsController::create, std::string(PREFIX) + "{1}/create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(ShareProductsController::getDetails, std::string(PREFIX) + "{1}/get-detail/{2}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(ShareProductsController::update, std::string(PREFIX) + "{1}/{2}/update", Put, Options,
                     FILTER);
        ADD_METHOD_TO(ShareProductsController::templateEndpoint, std::string(PREFIX) + "{1}/template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(ShareProductsController::command, std::string(PREFIX) + "{1}/{2}/command/{3}", Post,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req, std::string type);
    Task<HttpResponsePtr> create(HttpRequestPtr req, std::string type);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string type, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string type, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req, std::string type);
    Task<HttpResponsePtr> command(HttpRequestPtr req, std::string type, std::string id, std::string cmd);
};
