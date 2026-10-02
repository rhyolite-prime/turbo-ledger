//
// Phase 2 — office transactions (4 endpoints, inter-office cash movement).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class OfficeTransactionsController
    : public drogon::HttpController<OfficeTransactionsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/officetransactions/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(OfficeTransactionsController::getAll,      std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(OfficeTransactionsController::getTemplate, std::string(PREFIX) + "template", Get, Options, FILTER);
        ADD_METHOD_TO(OfficeTransactionsController::create,      std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(OfficeTransactionsController::remove,      std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> getTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
