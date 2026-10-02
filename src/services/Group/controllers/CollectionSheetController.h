//
// Phase 7 (retrofit) — top-level `collectionsheet` (1 endpoint): bulk
// field-collection submission across an office's groups/centers for a
// transaction date. 501 — see GroupService.h's header note (needs
// Portfolio repayment schedules + DepositAccountManagement savings-due
// amounts + attendance/calendar data this phase doesn't own).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CollectionSheetController : public drogon::HttpController<CollectionSheetController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/collectionsheet/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CollectionSheetController::submit, std::string(PREFIX) + "submit", Post, Options,
                     FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> submit(HttpRequestPtr req);
};
