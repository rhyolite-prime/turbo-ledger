//
// Phase 6 — CreditBureauConfiguration (12 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CreditBureauConfigurationController
    : public drogon::HttpController<CreditBureauConfigurationController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/CreditBureauConfiguration/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CreditBureauConfigurationController::getAll, std::string(PREFIX) + "get-all", Get,
                     Options, FILTER);

        ADD_METHOD_TO(CreditBureauConfigurationController::orgCreditBureauGetAll,
                     std::string(PREFIX) + "organisation-credit-bureau/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(CreditBureauConfigurationController::orgCreditBureauCreate,
                     std::string(PREFIX) + "organisation-credit-bureau/{1}/create", Post, Options, FILTER);
        ADD_METHOD_TO(CreditBureauConfigurationController::orgCreditBureauUpdate,
                     std::string(PREFIX) + "organisation-credit-bureau/update", Put, Options, FILTER);

        ADD_METHOD_TO(CreditBureauConfigurationController::configGetDetail,
                     std::string(PREFIX) + "config/get-detail/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(CreditBureauConfigurationController::configurationCreate,
                     std::string(PREFIX) + "configuration/{1}/create", Post, Options, FILTER);
        ADD_METHOD_TO(CreditBureauConfigurationController::configurationUpdate,
                     std::string(PREFIX) + "configuration/{1}/update", Put, Options, FILTER);

        ADD_METHOD_TO(CreditBureauConfigurationController::loanProductGetAll,
                     std::string(PREFIX) + "loan-product/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(CreditBureauConfigurationController::loanProductGetDetail,
                     std::string(PREFIX) + "loan-product/get-detail/{1}", Get, Options, FILTER);

        ADD_METHOD_TO(CreditBureauConfigurationController::mappingsGetAll,
                     std::string(PREFIX) + "mappings/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(CreditBureauConfigurationController::mappingsCreate,
                     std::string(PREFIX) + "mappings/{1}/create", Post, Options, FILTER);
        ADD_METHOD_TO(CreditBureauConfigurationController::mappingsUpdate,
                     std::string(PREFIX) + "mappings/update", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);

    Task<HttpResponsePtr> orgCreditBureauGetAll(HttpRequestPtr req);
    Task<HttpResponsePtr> orgCreditBureauCreate(HttpRequestPtr req, std::string creditBureauId);
    Task<HttpResponsePtr> orgCreditBureauUpdate(HttpRequestPtr req);

    Task<HttpResponsePtr> configGetDetail(HttpRequestPtr req, std::string organisationCreditBureauId);
    Task<HttpResponsePtr> configurationCreate(HttpRequestPtr req, std::string creditBureauId);
    Task<HttpResponsePtr> configurationUpdate(HttpRequestPtr req, std::string configurationId);

    Task<HttpResponsePtr> loanProductGetAll(HttpRequestPtr req);
    Task<HttpResponsePtr> loanProductGetDetail(HttpRequestPtr req, std::string loanProductId);

    Task<HttpResponsePtr> mappingsGetAll(HttpRequestPtr req);
    Task<HttpResponsePtr> mappingsCreate(HttpRequestPtr req, std::string organisationCreditBureauId);
    Task<HttpResponsePtr> mappingsUpdate(HttpRequestPtr req);
};
