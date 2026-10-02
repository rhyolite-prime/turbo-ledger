//
// Phase 9 — self/products/share*, self/shareaccounts* (composes Portfolio).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SelfSharesController : public drogon::HttpController<SelfSharesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/self/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(SelfSharesController::productsAll, std::string(PREFIX) + "products/share", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SelfSharesController::productDetail,
                     std::string(PREFIX) + "products/share/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(SelfSharesController::accountsTemplate,
                     std::string(PREFIX) + "shareaccounts/template", Get, Options, FILTER);
        ADD_METHOD_TO(SelfSharesController::getAccount, std::string(PREFIX) + "shareaccounts/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SelfSharesController::createAccount, std::string(PREFIX) + "shareaccounts", Post,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> productsAll(HttpRequestPtr req);
    Task<HttpResponsePtr> productDetail(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> accountsTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> getAccount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> createAccount(HttpRequestPtr req);
};
