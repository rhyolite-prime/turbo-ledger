//
// Phase 5 — recurringdepositproducts (6 endpoints). Backed by the shared
// savings_product table (deposit_type=RECURRING_DEPOSIT) — see
// DepositAccountManagementService.h's table-family design note.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class RecurringDepositProductsController : public drogon::HttpController<RecurringDepositProductsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/recurringdepositproducts/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RecurringDepositProductsController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(RecurringDepositProductsController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(RecurringDepositProductsController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(RecurringDepositProductsController::update, std::string(PREFIX) + "{1}/update", Put, Options,
                     FILTER);
        ADD_METHOD_TO(RecurringDepositProductsController::remove, std::string(PREFIX) + "{1}/delete", Delete, Options,
                     FILTER);
        ADD_METHOD_TO(RecurringDepositProductsController::templateEndpoint, std::string(PREFIX) + "template", Get,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
};
