#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class GeneralLedgerAccountController : public drogon::HttpController<GeneralLedgerAccountController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/gl-accounts/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(GeneralLedgerAccountController::retrieveTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(GeneralLedgerAccountController::getGlAccounts, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(GeneralLedgerAccountController::getGlAccountDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(GeneralLedgerAccountController::createGlAccount, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(GeneralLedgerAccountController::updateGlAccount, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(GeneralLedgerAccountController::deleteGlAccount, std::string(PREFIX) + "{1}", Delete);
    METHOD_LIST_END

    void retrieveTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getGlAccounts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getGlAccountDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createGlAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateGlAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteGlAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
