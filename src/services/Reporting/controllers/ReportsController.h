//
// Phase 8 — report definitions admin CRUD (5 endpoints). All routes require
// the gateway-signed TL-Context (turbo::TrustedContextFilter); permission
// checks (READ/CREATE/UPDATE/DELETE_REPORT) happen inside ReportingService.
//
// Follows the repo's RPC-style route convention (literal action segments
// rather than a bare {id} sharing a path level with literal siblings — see
// Organization's OfficeController.h "Conventions" note).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ReportsController : public drogon::HttpController<ReportsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/reports/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ReportsController::getAll,     std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ReportsController::create,     std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(ReportsController::getDetails, std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(ReportsController::update,     std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(ReportsController::remove,     std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
