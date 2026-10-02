//
// Phase 2 — holidays (7 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class HolidaysController : public drogon::HttpController<HolidaysController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/holidays/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(HolidaysController::getAll,      std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(HolidaysController::getTemplate, std::string(PREFIX) + "template", Get, Options, FILTER);
        ADD_METHOD_TO(HolidaysController::create,      std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(HolidaysController::getDetails,  std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(HolidaysController::update,      std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(HolidaysController::remove,      std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
        ADD_METHOD_TO(HolidaysController::activate,    std::string(PREFIX) + "activate/{1}", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> getTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> activate(HttpRequestPtr req, std::string id);
};
