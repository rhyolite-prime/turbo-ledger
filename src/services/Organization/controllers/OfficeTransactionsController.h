#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class OfficeTransactionsController : public drogon::HttpController<OfficeTransactionsController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/office-transactions/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(OfficeTransactionsController::getOfficeTransactions, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(OfficeTransactionsController::getOfficeTransactions, std::string(PREFIX) + "transfer-money", Post);
    ADD_METHOD_TO(OfficeTransactionsController::getOfficeTransactions, std::string(PREFIX) + "delete-transaction", Delete);
    ADD_METHOD_TO(OfficeTransactionsController::getOfficeTransactions, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(OfficeTransactionsController::getOfficeTransactions, std::string(PREFIX) + "update-via-external-id", Post);
    METHOD_LIST_END

  //handler methods
  void getOfficeTransactions(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
