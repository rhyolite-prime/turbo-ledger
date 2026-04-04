#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AccountingRulesController : public drogon::HttpController<AccountingRulesController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/accounting-rules/";
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(AccountingRulesController::getAccountingRuleTemplate, std::string(PREFIX) + "template", Get);
  ADD_METHOD_TO(AccountingRulesController::getAccountingRules, std::string(PREFIX) + "get-all", Get);
  ADD_METHOD_TO(AccountingRulesController::getAccountingRuleDetails, std::string(PREFIX) + "{1}", Get);
  ADD_METHOD_TO(AccountingRulesController::createAccountingRule, std::string(PREFIX) + "create", Post);
  ADD_METHOD_TO(AccountingRulesController::updateAccountingRule, std::string(PREFIX) + "{1}", Put);
  ADD_METHOD_TO(AccountingRulesController::deleteAccountingRule, std::string(PREFIX) + "{1}", Delete);
  METHOD_LIST_END

  void getAccountingRuleTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getAccountingRules(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getAccountingRuleDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void createAccountingRule(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void updateAccountingRule(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void deleteAccountingRule(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
