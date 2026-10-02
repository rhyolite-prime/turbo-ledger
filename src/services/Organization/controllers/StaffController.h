//
// Phase 2 — staff (6 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class StaffController : public drogon::HttpController<StaffController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/staff/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(StaffController::getAll,             std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(StaffController::downloadTemplate,   std::string(PREFIX) + "downloadtemplate", Get, Options, FILTER);
        ADD_METHOD_TO(StaffController::uploadTemplate,     std::string(PREFIX) + "uploadtemplate", Post, Options, FILTER);
        ADD_METHOD_TO(StaffController::create,             std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(StaffController::getDetails,         std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(StaffController::update,             std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> downloadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> uploadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
};
