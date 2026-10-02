//
// Phase 2 — global configuration (5 endpoints). All routes require the
// gateway-signed TL-Context (turbo::TrustedContextFilter).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class GlobalConfigController : public drogon::HttpController<GlobalConfigController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/configurations/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(GlobalConfigController::getAll,        std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(GlobalConfigController::getDetails,    std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(GlobalConfigController::update,        std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(GlobalConfigController::getByName,     std::string(PREFIX) + "name/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(GlobalConfigController::updateByName,  std::string(PREFIX) + "name-update/{1}", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> getByName(HttpRequestPtr req, std::string name);
    Task<HttpResponsePtr> updateByName(HttpRequestPtr req, std::string name);
};
