#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AccountingController : public drogon::HttpController<AccountingController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/accounting/";
  METHOD_LIST_BEGIN

  // General Ledger Account
  ADD_METHOD_TO(AccountingController::getAllGlAccounts, std::string(PREFIX) + "gl-accounts/get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::getGlAccountDetails, std::string(PREFIX) + "gl-accounts/get-detail/{1}", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::createGlAccount, std::string(PREFIX) + "gl-accounts/create", Post, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::updateGlAccount, std::string(PREFIX) + "gl-accounts/{1}/update", Put, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::deleteGlAccount, std::string(PREFIX) + "gl-accounts/{1}/delete", Delete, Options, "CompositeAuthFilter");

  // accounting closures
  ADD_METHOD_TO(AccountingController::createAccountingClosure, std::string(PREFIX) + "gl-closures/create", Post, Options);
  ADD_METHOD_TO(AccountingController::listAccountingClosures, std::string(PREFIX) + "gl-closures/get-all", Get, Options);

  // Journal Entries
  ADD_METHOD_TO(AccountingController::createJournalEntry, std::string(PREFIX) + "journal-entries/create", Post, Options);
  ADD_METHOD_TO(AccountingController::listJournalEntries, std::string(PREFIX) + "journal-entries/get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::updateRunningBalanceForJournalEntries, std::string(PREFIX) + "journal-entries/update-running-balance", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::retrieveSingleEntryDetails, std::string(PREFIX) + "journal-entries/{1}", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::retrieveBatchEntryDetails, std::string(PREFIX) + "journal-entries/{1}/batch", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::reverseJournalEntries, std::string(PREFIX) + "journal-entries/{1}/reversal", Get, Options, "CompositeAuthFilter");

  //accounting rules
  ADD_METHOD_TO(AccountingController::listAccountingRules, std::string(PREFIX) + "accounting-rules/get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::getAccountingRuleDetails, std::string(PREFIX) + "accounting-rules/{1}", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::createAccountingRule, std::string(PREFIX) + "accounting-rules/create", Post, Options);
  ADD_METHOD_TO(AccountingController::updateAccountingRule, std::string(PREFIX) + "accounting-rules/{1}/update", Put, Options);
  ADD_METHOD_TO(AccountingController::deleteAccountingRule, std::string(PREFIX) + "accounting-rules/{1}/delete", Delete, Options);

  // mapping financial activity to accounts...
  ADD_METHOD_TO(AccountingController::listFinancialActivityToAccountMappings, std::string(PREFIX) + "financial-activity-accounts/get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::getFinancialActivityToAccountMappingDetails, std::string(PREFIX) + "financial-activity-accounts/{1}", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::createFinancialActivityToAccountMapping, std::string(PREFIX) + "financial-activity-accounts/create", Post, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::updateFinancialActivityToAccountMapping, std::string(PREFIX) + "financial-activity-accounts/{1}/update", Put, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::deleteFinancialActivityToAccountMapping, std::string(PREFIX) + "financial-activity-accounts/{1}/delete", Delete, Options, "CompositeAuthFilter");

  // Periodic Accrual Accounting
  ADD_METHOD_TO(AccountingController::executePeriodicAccrualAccounting, std::string(PREFIX) + "accrual-accounting", Get, Options, "CompositeAuthFilter");

  // Provisioning entries
  ADD_METHOD_TO(AccountingController::listProvisioningEntries, std::string(PREFIX) + "provisioning-entries", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::getProvisioningEntryDetails, std::string(PREFIX) + "provisioning-entries/{1}", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::createProvisioningEntry, std::string(PREFIX) + "provisioning-entries/create", Post, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::recreateProvisioningEntry, std::string(PREFIX) + "provisioning-entries/{1}/recreate-provisioning-entry", Post, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(AccountingController::addProvisioningJournalEntry, std::string(PREFIX) + "provisioning-entries/{1}/create-journal-entry", Post, Options, "CompositeAuthFilter");

  METHOD_LIST_END

  Task<HttpResponsePtr> getAllGlAccounts(HttpRequestPtr req);
  Task<HttpResponsePtr> getGlAccountDetails(HttpRequestPtr req, std::string accountId);
  Task<HttpResponsePtr> createGlAccount(HttpRequestPtr req);
  Task<HttpResponsePtr> updateGlAccount(HttpRequestPtr req, std::string accountId);
  Task<HttpResponsePtr> deleteGlAccount(HttpRequestPtr req, std::string accountId);

  Task<HttpResponsePtr> createAccountingClosure(HttpRequestPtr req);
  Task<HttpResponsePtr> listAccountingClosures(HttpRequestPtr req);

  Task<HttpResponsePtr> createJournalEntry(HttpRequestPtr req);
  Task<HttpResponsePtr> listJournalEntries(HttpRequestPtr req);
  Task<HttpResponsePtr> updateRunningBalanceForJournalEntries(HttpRequestPtr req);
  Task<HttpResponsePtr> retrieveSingleEntryDetails(HttpRequestPtr req, std::string entryId);
  Task<HttpResponsePtr> retrieveBatchEntryDetails(HttpRequestPtr req, std::string batchId);
  Task<HttpResponsePtr> reverseJournalEntries(HttpRequestPtr req, std::string transactionId);

  Task<HttpResponsePtr> listAccountingRules(HttpRequestPtr req);
  Task<HttpResponsePtr> getAccountingRuleDetails(HttpRequestPtr req, std::string accountingRuleId);
  Task<HttpResponsePtr> createAccountingRule(HttpRequestPtr req);
  Task<HttpResponsePtr> updateAccountingRule(HttpRequestPtr req, std::string accountingRuleId);
  Task<HttpResponsePtr> deleteAccountingRule(HttpRequestPtr req, std::string accountingRuleId);

  Task<HttpResponsePtr> listFinancialActivityToAccountMappings(HttpRequestPtr req);
  Task<HttpResponsePtr> getFinancialActivityToAccountMappingDetails(HttpRequestPtr req, std::string financialActivityAccountId);
  Task<HttpResponsePtr> createFinancialActivityToAccountMapping(HttpRequestPtr req);
  Task<HttpResponsePtr> updateFinancialActivityToAccountMapping(HttpRequestPtr req, std::string financialActivityAccountId);
  Task<HttpResponsePtr> deleteFinancialActivityToAccountMapping(HttpRequestPtr req, std::string financialActivityAccountId);

  Task<HttpResponsePtr> executePeriodicAccrualAccounting(HttpRequestPtr req);

  Task<HttpResponsePtr> listProvisioningEntries(HttpRequestPtr req);
  Task<HttpResponsePtr> getProvisioningEntryDetails(HttpRequestPtr req, std::string entryId);
  Task<HttpResponsePtr> createProvisioningEntry(HttpRequestPtr req, std::string entryId);
  Task<HttpResponsePtr> recreateProvisioningEntry(HttpRequestPtr req, std::string privisioningEntryId);
  Task<HttpResponsePtr> addProvisioningJournalEntry(HttpRequestPtr req, std::string privisioningEntryId);

private:
  struct AuthResult {
    bool isValid = false;
    std::string businessId;
    HttpResponsePtr errorResponse;
  };

  Task<AuthResult> authenticateRequest(HttpRequestPtr req);
};
