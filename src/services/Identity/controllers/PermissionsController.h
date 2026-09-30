//
// Phase 1 — tenant permission catalog (+ per-action maker-checker toggles).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class PermissionsController : public drogon::HttpController<PermissionsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/permissions/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(PermissionsController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(PermissionsController::updateMakerChecker,
                      std::string(PREFIX) + "maker-checker", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> updateMakerChecker(HttpRequestPtr req);
};
