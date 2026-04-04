#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class FinancialActivityAccountsController : public drogon::HttpController<FinancialActivityAccountsController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/financial-activity-accounts/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(FinancialActivityAccountsController::getFinancialActivitiesToAccountsMappings, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(FinancialActivityAccountsController::retrieveFinancialActivitiesToAccountsMapping, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(FinancialActivityAccountsController::createFinancialActivitiesToAccountsMapping, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(FinancialActivityAccountsController::updateFinancialActivitiesToAccountsMapping, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(FinancialActivityAccountsController::deleteFinancialActivitiesToAccountsMapping, std::string(PREFIX) + "{1}", Delete);
    METHOD_LIST_END

    void getFinancialActivitiesToAccountsMappings(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveFinancialActivitiesToAccountsMapping(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createFinancialActivitiesToAccountsMapping(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateFinancialActivitiesToAccountsMapping(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteFinancialActivitiesToAccountsMapping(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
