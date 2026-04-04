#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AccountingClosureController : public drogon::HttpController<AccountingClosureController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/gl-closures/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(AccountingClosureController::retrieveTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(AccountingClosureController::getAccountingClosures, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(AccountingClosureController::getAccountingClosureDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(AccountingClosureController::createAccountingClosure, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(AccountingClosureController::updateAccountingClosure, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(AccountingClosureController::deleteAccountingClosure, std::string(PREFIX) + "{1}", Delete);
    METHOD_LIST_END

    void retrieveTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getAccountingClosures(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getAccountingClosureDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createAccountingClosure(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateAccountingClosure(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteAccountingClosure(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
