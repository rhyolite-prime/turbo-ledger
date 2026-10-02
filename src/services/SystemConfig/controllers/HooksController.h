//
// Phase 2 — hooks (6 endpoints, config only — firing comes with EventHub).
// All routes require the gateway-signed TL-Context (turbo::TrustedContextFilter).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class HooksController : public drogon::HttpController<HooksController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/hooks/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(HooksController::getAll,  std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(HooksController::getTemplate, std::string(PREFIX) + "template", Get, Options, FILTER);
        ADD_METHOD_TO(HooksController::create,     std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(HooksController::getDetails, std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(HooksController::update,     std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(HooksController::remove,     std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> getTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
