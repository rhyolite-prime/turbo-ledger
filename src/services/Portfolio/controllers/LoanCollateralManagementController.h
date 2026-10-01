//
// Phase 6 — loan-collateral-management (2 endpoints): standalone get/delete
// of a collateral-management record by its own id (independent of which
// loan it is attached to).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class LoanCollateralManagementController
    : public drogon::HttpController<LoanCollateralManagementController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/loan-collateral-management/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(LoanCollateralManagementController::getDetails,
                     std::string(PREFIX) + "get-detail/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(LoanCollateralManagementController::remove, std::string(PREFIX) + "{1}/delete",
                     Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
