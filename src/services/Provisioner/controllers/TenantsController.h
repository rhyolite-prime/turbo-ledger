//
// Provisioner — tenant lifecycle API (Phase 1).
//
// All routes require the gateway-signed TL-Context. Mutations additionally
// require a JWT principal signed in under the host tenant ("default").
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TenantsController : public drogon::HttpController<TenantsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/tenants/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(TenantsController::getAll,       std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(TenantsController::getDetails,   std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(TenantsController::instanceMode, std::string(PREFIX) + "instance-mode", Get, Options, FILTER);
        ADD_METHOD_TO(TenantsController::create,       std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(TenantsController::activate,     std::string(PREFIX) + "activate/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(TenantsController::suspend,      std::string(PREFIX) + "suspend/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(TenantsController::close,        std::string(PREFIX) + "close/{1}", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> instanceMode(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> activate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> suspend(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> close(HttpRequestPtr req, std::string id);
};
