//
// Phase 7 (retrofit) — grouplevels (1 endpoint). Read-only: lists the two
// fixed Fineract levels ("Center"/"Group") seeded by
// V003__phase7_group.sql.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class GroupLevelsController : public drogon::HttpController<GroupLevelsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/grouplevels/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(GroupLevelsController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
};
