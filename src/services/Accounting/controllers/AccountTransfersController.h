#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AccountTransfersController : public drogon::HttpController<AccountTransfersController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/account-transfers/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(AccountTransfersController::retrieveTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(AccountTransfersController::getAccountTransfers, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(AccountTransfersController::retrieveAccountTransfer, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(AccountTransfersController::createAccountTransfer, std::string(PREFIX) + "create", Post); // can also be used to refund an active loan by transferring to a savings account.
    METHOD_LIST_END

    void getAccountTransfers(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveAccountTransfer(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createAccountTransfer(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
