#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CurrencyController : public drogon::HttpController<CurrencyController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/currency/";
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(CurrencyController::getCurrencies, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(CurrencyController::updateCurrency, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(CurrencyController::createCurrency, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(CurrencyController::deleteCurrency, std::string(PREFIX) + "{1}", Delete);

    METHOD_LIST_END

    void getCurrencies(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateCurrency(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createCurrency(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteCurrency(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
