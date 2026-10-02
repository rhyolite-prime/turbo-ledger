//
// Phase 7 — standalone `cashiers` global view (1 endpoint): `GET
// /api/v1/cashiers` lists cashiers across every teller/office, filterable
// by officeId/staffId/tellerId/date. Distinct from TellersController's
// nested `{tellerId}/cashiers/*` routes, which scope to one teller.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CashiersController : public drogon::HttpController<CashiersController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/cashiers/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CashiersController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
};
