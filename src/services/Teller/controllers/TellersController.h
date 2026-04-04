#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TellersController : public drogon::HttpController<TellersController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/tellers/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TellersController::getTellers, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(TellersController::createTeller, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(TellersController::retrieveTellerDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(TellersController::updateTeller, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(TellersController::deleteTeller, std::string(PREFIX) + "{1}", Delete);
    //cashiers
    ADD_METHOD_TO(TellersController::getCashiers, std::string(PREFIX) + "{1}/cashiers", Get);
    ADD_METHOD_TO(TellersController::createCashier, std::string(PREFIX) + "{1}/cashiers", Post);
    ADD_METHOD_TO(TellersController::updateCashier, std::string(PREFIX) + "{1}/cashiers/{2}", Put);
    ADD_METHOD_TO(TellersController::getCashierDetails, std::string(PREFIX) + "{1}/cashiers/{2}", Get);
    ADD_METHOD_TO(TellersController::getCashierTransactions, std::string(PREFIX) + "{1}/cashiers/{2}/transactions", Get);
    ADD_METHOD_TO(TellersController::retrieveCashierTransactionTemplate, std::string(PREFIX) + "{1}/cashiers/{2}/transactions/template", Get);
    ADD_METHOD_TO(TellersController::getCashierTransactionsWithSummary, std::string(PREFIX) + "{1}/cashiers/{2}/summary-and-transactions", Get);
    ADD_METHOD_TO(TellersController::allocateCashToCashier, std::string(PREFIX) + "{1}/cashiers/{2}/allocate", Post);
    ADD_METHOD_TO(TellersController::settleCashToCashier, std::string(PREFIX) + "{1}/cashiers/{2}/settle", Post);
    ADD_METHOD_TO(TellersController::deleteCashier, std::string(PREFIX) + "{1}/cashiers/{2}", Delete);
    //
    METHOD_LIST_END

    void getTellers(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createTeller(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveTellerDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateTeller(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteTeller(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getCashiers(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createCashier(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateCashier(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getCashierDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getCashierTransactions(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveCashierTransactionTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getCashierTransactionsWithSummary(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void allocateCashToCashier(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void settleCashToCashier(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteCashier(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
