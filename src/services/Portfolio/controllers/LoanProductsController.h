//
// Phase 6 — loanproducts (11 endpoints: 7 core + 4 productmix). External-id
// mirror for loan products is wired since the service already resolves it
// cheaply (getLoanProductByExternalId/updateLoanProductByExternalId).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class LoanProductsController : public drogon::HttpController<LoanProductsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/loanproducts/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(LoanProductsController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(LoanProductsController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(LoanProductsController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(LoanProductsController::update, std::string(PREFIX) + "{1}/update", Put, Options,
                     FILTER);
        ADD_METHOD_TO(LoanProductsController::templateEndpoint, std::string(PREFIX) + "template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(LoanProductsController::getDetailsByExternalId,
                     std::string(PREFIX) + "external-id/{1}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(LoanProductsController::updateByExternalId,
                     std::string(PREFIX) + "external-id/{1}/update", Put, Options, FILTER);

        ADD_METHOD_TO(LoanProductsController::productMixGetAll,
                     std::string(PREFIX) + "{1}/productmix/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(LoanProductsController::productMixCreate,
                     std::string(PREFIX) + "{1}/productmix/create", Post, Options, FILTER);
        ADD_METHOD_TO(LoanProductsController::productMixUpdate,
                     std::string(PREFIX) + "{1}/productmix/update", Put, Options, FILTER);
        ADD_METHOD_TO(LoanProductsController::productMixDelete,
                     std::string(PREFIX) + "{1}/productmix/delete", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetailsByExternalId(HttpRequestPtr req, std::string externalId);
    Task<HttpResponsePtr> updateByExternalId(HttpRequestPtr req, std::string externalId);

    Task<HttpResponsePtr> productMixGetAll(HttpRequestPtr req, std::string productId);
    Task<HttpResponsePtr> productMixCreate(HttpRequestPtr req, std::string productId);
    Task<HttpResponsePtr> productMixUpdate(HttpRequestPtr req, std::string productId);
    Task<HttpResponsePtr> productMixDelete(HttpRequestPtr req, std::string productId);
};
