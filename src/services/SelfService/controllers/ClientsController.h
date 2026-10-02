//
// Phase 9 — self/clients* (9 endpoints): list/detail, accounts overview,
// obligee details, charges, transactions, profile image (local blob).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SelfClientsController : public drogon::HttpController<SelfClientsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/self/clients";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(SelfClientsController::listClients, std::string(PREFIX), Get, Options, FILTER);
        ADD_METHOD_TO(SelfClientsController::getClient, std::string(PREFIX) + "/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(SelfClientsController::accountsOverview,
                     std::string(PREFIX) + "/{1}/accounts", Get, Options, FILTER);
        ADD_METHOD_TO(SelfClientsController::obligeeDetails,
                     std::string(PREFIX) + "/{1}/obligeedetails", Get, Options, FILTER);
        ADD_METHOD_TO(SelfClientsController::chargesAll, std::string(PREFIX) + "/{1}/charges", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SelfClientsController::chargeDetail,
                     std::string(PREFIX) + "/{1}/charges/{2}", Get, Options, FILTER);
        ADD_METHOD_TO(SelfClientsController::transactionsAll,
                     std::string(PREFIX) + "/{1}/transactions", Get, Options, FILTER);
        ADD_METHOD_TO(SelfClientsController::transactionDetail,
                     std::string(PREFIX) + "/{1}/transactions/{2}", Get, Options, FILTER);
        ADD_METHOD_TO(SelfClientsController::getImage, std::string(PREFIX) + "/{1}/images", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SelfClientsController::putImage, std::string(PREFIX) + "/{1}/images", Put,
                     Options, FILTER);
        ADD_METHOD_TO(SelfClientsController::deleteImage, std::string(PREFIX) + "/{1}/images", Delete,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> listClients(HttpRequestPtr req);
    Task<HttpResponsePtr> getClient(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> accountsOverview(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> obligeeDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> chargesAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> chargeDetail(HttpRequestPtr req, std::string id, std::string chargeId);
    Task<HttpResponsePtr> transactionsAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> transactionDetail(HttpRequestPtr req, std::string id,
                                            std::string transactionId);
    Task<HttpResponsePtr> getImage(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> putImage(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> deleteImage(HttpRequestPtr req, std::string id);
};
