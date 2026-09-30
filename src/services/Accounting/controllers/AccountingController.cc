#include "AccountingController.h"

#include "dto/BaseApiResponse.h"
#include "plugins/AccountingServicePlugin.h"
#include "turbo/ApiResponse.h"

Task<AccountingController::AuthResult> AccountingController::authenticateRequest(HttpRequestPtr req) {
    AuthResult result;
    auto clientId = req->getHeader("ClientId");
    auto clientSecret = req->getHeader("ClientSecret");

    if (clientId.empty() || clientSecret.empty()) {
        turbo_ledger_accounting::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "ClientId and ClientSecret Headers are absent !";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        result.errorResponse = resp;
        co_return result;
    }

    auto plugin = drogon::app().getPlugin<turbo_ledger_accounting::plugins::AccountingServicePlugin>();
    auto &identityApi = plugin->getIdentityApi();

    auto businessIdentity = co_await identityApi.validateApiCredentials(clientId, clientSecret);

    if (!businessIdentity.isValid) {
        turbo_ledger_accounting::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = businessIdentity.errorMessage.empty() ? "Invalid API credentials" : businessIdentity.errorMessage;
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k401Unauthorized);
        result.errorResponse = resp;
        co_return result;
    }

    result.isValid = true;
    result.businessId = businessIdentity.businessId;
    co_return result;
}

// ---------------------------------------------------------------------------
// NOTE (Phase 0): every handler below MUST co_return a response. The previous
// empty bodies were undefined behaviour (a coroutine falling off the end
// without co_return). Handlers not yet backed by a service implementation
// return a structured 501 until they are wired up in Phase 3 of the
// implementation plan (src/docs/IMPLEMENTATION_PLAN.md).
// ---------------------------------------------------------------------------

namespace {
HttpResponsePtr notImplemented(const std::string &operation) {
    return turbo::ApiResponse::httpNotImplemented("accounting." + operation);
}
}  // namespace

// ---- General ledger accounts ----------------------------------------------

Task<HttpResponsePtr> AccountingController::getAllGlAccounts(HttpRequestPtr req) {
    co_return notImplemented("glaccounts.list");
}

Task<HttpResponsePtr> AccountingController::getGlAccountDetails(HttpRequestPtr req, std::string accountId) {
    co_return notImplemented("glaccounts.get");
}

Task<HttpResponsePtr> AccountingController::createGlAccount(HttpRequestPtr req) {
    co_return notImplemented("glaccounts.create");
}

Task<HttpResponsePtr> AccountingController::updateGlAccount(HttpRequestPtr req, std::string accountId) {
    co_return notImplemented("glaccounts.update");
}

Task<HttpResponsePtr> AccountingController::deleteGlAccount(HttpRequestPtr req, std::string accountId) {
    co_return notImplemented("glaccounts.delete");
}

// ---- GL closures ------------------------------------------------------------

Task<HttpResponsePtr> AccountingController::createAccountingClosure(HttpRequestPtr req) {
    co_return notImplemented("glclosures.create");
}

Task<HttpResponsePtr> AccountingController::listAccountingClosures(HttpRequestPtr req) {
    co_return notImplemented("glclosures.list");
}

// ---- Journal entries ----------------------------------------------------------

Task<HttpResponsePtr> AccountingController::createJournalEntry(HttpRequestPtr req) {
    co_return notImplemented("journalentries.create");
}

Task<HttpResponsePtr> AccountingController::listJournalEntries(HttpRequestPtr req) {
    co_return notImplemented("journalentries.list");
}

Task<HttpResponsePtr> AccountingController::updateRunningBalanceForJournalEntries(HttpRequestPtr req) {
    co_return notImplemented("journalentries.updateRunningBalance");
}

Task<HttpResponsePtr> AccountingController::retrieveSingleEntryDetails(HttpRequestPtr req, std::string entryId) {
    co_return notImplemented("journalentries.get");
}

Task<HttpResponsePtr> AccountingController::retrieveBatchEntryDetails(HttpRequestPtr req, std::string batchId) {
    co_return notImplemented("journalentries.getBatch");
}

Task<HttpResponsePtr> AccountingController::reverseJournalEntries(HttpRequestPtr req, std::string transactionId) {
    co_return notImplemented("journalentries.reverse");
}

// ---- Accounting rules ----------------------------------------------------------

Task<HttpResponsePtr> AccountingController::listAccountingRules(HttpRequestPtr req) {
    co_return notImplemented("accountingrules.list");
}

Task<HttpResponsePtr> AccountingController::getAccountingRuleDetails(HttpRequestPtr req, std::string accountingRuleId) {
    co_return notImplemented("accountingrules.get");
}

Task<HttpResponsePtr> AccountingController::createAccountingRule(HttpRequestPtr req) {
    co_return notImplemented("accountingrules.create");
}

Task<HttpResponsePtr> AccountingController::updateAccountingRule(HttpRequestPtr req, std::string accountingRuleId) {
    co_return notImplemented("accountingrules.update");
}

Task<HttpResponsePtr> AccountingController::deleteAccountingRule(HttpRequestPtr req, std::string accountingRuleId) {
    co_return notImplemented("accountingrules.delete");
}

// ---- Financial activity <-> account mappings ---------------------------------

Task<HttpResponsePtr> AccountingController::listFinancialActivityToAccountMappings(HttpRequestPtr req) {
    co_return notImplemented("financialactivityaccounts.list");
}

Task<HttpResponsePtr> AccountingController::getFinancialActivityToAccountMappingDetails(HttpRequestPtr req, std::string financialActivityAccountId) {
    co_return notImplemented("financialactivityaccounts.get");
}

Task<HttpResponsePtr> AccountingController::createFinancialActivityToAccountMapping(HttpRequestPtr req) {
    co_return notImplemented("financialactivityaccounts.create");
}

Task<HttpResponsePtr> AccountingController::updateFinancialActivityToAccountMapping(HttpRequestPtr req, std::string financialActivityAccountId) {
    co_return notImplemented("financialactivityaccounts.update");
}

Task<HttpResponsePtr> AccountingController::deleteFinancialActivityToAccountMapping(HttpRequestPtr req, std::string financialActivityAccountId) {
    co_return notImplemented("financialactivityaccounts.delete");
}

// ---- Accruals -------------------------------------------------------------------

Task<HttpResponsePtr> AccountingController::executePeriodicAccrualAccounting(HttpRequestPtr req) {
    co_return notImplemented("runaccruals.execute");
}

// ---- Provisioning entries ---------------------------------------------------------

Task<HttpResponsePtr> AccountingController::listProvisioningEntries(HttpRequestPtr req) {
    co_return notImplemented("provisioningentries.list");
}

Task<HttpResponsePtr> AccountingController::getProvisioningEntryDetails(HttpRequestPtr req, std::string entryId) {
    co_return notImplemented("provisioningentries.get");
}

Task<HttpResponsePtr> AccountingController::createProvisioningEntry(HttpRequestPtr req, std::string entryId) {
    co_return notImplemented("provisioningentries.create");
}

Task<HttpResponsePtr> AccountingController::recreateProvisioningEntry(HttpRequestPtr req, std::string privisioningEntryId) {
    co_return notImplemented("provisioningentries.recreate");
}

Task<HttpResponsePtr> AccountingController::addProvisioningJournalEntry(HttpRequestPtr req, std::string privisioningEntryId) {
    co_return notImplemented("provisioningentries.createJournalEntry");
}
