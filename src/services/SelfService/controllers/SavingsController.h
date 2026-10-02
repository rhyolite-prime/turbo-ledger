//
// Phase 9 — self/savingsproducts, self/savingsaccounts*, self/accounttransfers*
// (composes DepositAccountManagement).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SelfSavingsController : public drogon::HttpController<SelfSavingsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/self/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(SelfSavingsController::productsAll, std::string(PREFIX) + "savingsproducts", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SelfSavingsController::productDetail,
                     std::string(PREFIX) + "savingsproducts/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(SelfSavingsController::accountsTemplate,
                     std::string(PREFIX) + "savingsaccounts/template", Get, Options, FILTER);
        ADD_METHOD_TO(SelfSavingsController::getAccount, std::string(PREFIX) + "savingsaccounts/{1}",
                     Get, Options, FILTER);
        ADD_METHOD_TO(SelfSavingsController::updateAccount, std::string(PREFIX) + "savingsaccounts/{1}",
                     Put, Options, FILTER);
        ADD_METHOD_TO(SelfSavingsController::createAccount, std::string(PREFIX) + "savingsaccounts",
                     Post, Options, FILTER);
        ADD_METHOD_TO(SelfSavingsController::chargesAll,
                     std::string(PREFIX) + "savingsaccounts/{1}/charges", Get, Options, FILTER);
        ADD_METHOD_TO(SelfSavingsController::chargeDetail,
                     std::string(PREFIX) + "savingsaccounts/{1}/charges/{2}", Get, Options, FILTER);
        ADD_METHOD_TO(SelfSavingsController::transactionDetail,
                     std::string(PREFIX) + "savingsaccounts/{1}/transactions/{2}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(SelfSavingsController::transfersTemplate,
                     std::string(PREFIX) + "accounttransfers/template", Get, Options, FILTER);
        ADD_METHOD_TO(SelfSavingsController::createTransfer, std::string(PREFIX) + "accounttransfers",
                     Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> productsAll(HttpRequestPtr req);
    Task<HttpResponsePtr> productDetail(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> accountsTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> getAccount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> updateAccount(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> createAccount(HttpRequestPtr req);
    Task<HttpResponsePtr> chargesAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> chargeDetail(HttpRequestPtr req, std::string id, std::string chargeId);
    Task<HttpResponsePtr> transactionDetail(HttpRequestPtr req, std::string id,
                                            std::string transactionId);
    Task<HttpResponsePtr> transfersTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> createTransfer(HttpRequestPtr req);
};
