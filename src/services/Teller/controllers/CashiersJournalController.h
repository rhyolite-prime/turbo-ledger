//
// Phase 7 — standalone `cashiersjournal` global view (1 endpoint): `GET
// /api/v1/cashiersjournal` lists cashier cash-movement transactions across
// every teller/cashier, filterable by cashierId/tellerId/currencyCode/
// fromDate/toDate.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CashiersJournalController : public drogon::HttpController<CashiersJournalController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/cashiersjournal/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CashiersJournalController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
};
