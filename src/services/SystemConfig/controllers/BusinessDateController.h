//
// Phase 2 — business date (3 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class BusinessDateController : public drogon::HttpController<BusinessDateController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/businessdate/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(BusinessDateController::getAll,     std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(BusinessDateController::update,     std::string(PREFIX) + "update", Post, Options, FILTER);
        ADD_METHOD_TO(BusinessDateController::getDetails, std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> update(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string type);
};
