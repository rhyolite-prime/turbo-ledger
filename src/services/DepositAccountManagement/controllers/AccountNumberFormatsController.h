//
// Phase 5 — accountnumberformats (6 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AccountNumberFormatsController : public drogon::HttpController<AccountNumberFormatsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/accountnumberformats/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(AccountNumberFormatsController::getAll, std::string(PREFIX) + "get-all", Get,
                     Options, FILTER);
        ADD_METHOD_TO(AccountNumberFormatsController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(AccountNumberFormatsController::getDetails, std::string(PREFIX) + "get-detail/{1}",
                     Get, Options, FILTER);
        ADD_METHOD_TO(AccountNumberFormatsController::update, std::string(PREFIX) + "{1}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(AccountNumberFormatsController::remove, std::string(PREFIX) + "{1}/delete", Delete,
                     Options, FILTER);
        ADD_METHOD_TO(AccountNumberFormatsController::templateEndpoint, std::string(PREFIX) + "template",
                     Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
};
