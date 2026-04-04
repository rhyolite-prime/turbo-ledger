#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AccountsController : public drogon::HttpController<AccountsController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/accounts/";
    METHOD_LIST_BEGIN
    //shares accounts
    ADD_METHOD_TO(AccountsController::retrieveShareAccountTemplate, std::string(PREFIX) + "share/template/{1}/{2}", Get);
    ADD_METHOD_TO(AccountsController::getShareAccounts, std::string(PREFIX) + "share", Get);
    ADD_METHOD_TO(AccountsController::createShareApplication, std::string(PREFIX) + "share/submit-application", Post); // Minimal request: accountNo auto generated, remaining details inherited from savings product.
    ADD_METHOD_TO(AccountsController::approveShareApplication, std::string(PREFIX) + "share/{1}/approve-application", Post);
    ADD_METHOD_TO(AccountsController::undoApproveShareApplication, std::string(PREFIX) + "share/{1}/undo-application-approval", Post);
    ADD_METHOD_TO(AccountsController::rejectShareApplication, std::string(PREFIX) + "share/{1}/reject-application", Post);
    ADD_METHOD_TO(AccountsController::activateShareAccount, std::string(PREFIX) + "share/{1}/activate-account", Post);
    ADD_METHOD_TO(AccountsController::closeShareAccount, std::string(PREFIX) + "share/{1}/close-account", Post);
    ADD_METHOD_TO(AccountsController::applyAdditionalShares, std::string(PREFIX) + "share/{1}/apply-additional-shares", Post);
    ADD_METHOD_TO(AccountsController::approveAdditionalShares, std::string(PREFIX) + "share/{1}/approve-additional-shares", Post);
    ADD_METHOD_TO(AccountsController::rejectAdditionalShares, std::string(PREFIX) + "share/{1}/reject-additional-shares", Post);
    ADD_METHOD_TO(AccountsController::redeemShares, std::string(PREFIX) + "share/{1}/redeem", Post);
    ADD_METHOD_TO(AccountsController::getShareAccountDetails, std::string(PREFIX) + "share/{1}", Get);
    ADD_METHOD_TO(AccountsController::updateShareAccountApplication, std::string(PREFIX) + "share/{1}", Put);
    //savings accounts
    ADD_METHOD_TO(AccountsController::retrieveSavingsAccountTemplate, std::string(PREFIX) + "savings/template/{1}/{2}", Get);
    ADD_METHOD_TO(AccountsController::retrieveSavingsAccountDetails, std::string(PREFIX) + "savings/{1}", Get);
    ADD_METHOD_TO(AccountsController::getSavingsAccounts, std::string(PREFIX) + "savings", Get);
    ADD_METHOD_TO(AccountsController::createSavingsAccountApplication, std::string(PREFIX) + "savings/submit-application", Post); // Minimal request: accountNo auto generated, remaining details inherited from savings product.
    ADD_METHOD_TO(AccountsController::updateSavingsAccountApplication, std::string(PREFIX) + "savings/update", Put);
    ADD_METHOD_TO(AccountsController::modifySavingsAccountWithHoldTaxApplicability, std::string(PREFIX) + "savings/update", Put);
    ADD_METHOD_TO(AccountsController::approveSavingsAccountApplication, std::string(PREFIX) + "savings/{1}/approve-application", Post);
    ADD_METHOD_TO(AccountsController::assignSavingsOfficer, std::string(PREFIX) + "savings/{1}/assign-officer", Post); // Allows you to assign Savings Officer for existing Savings Account.
    ADD_METHOD_TO(AccountsController::unassignSavingsOfficer, std::string(PREFIX) + "savings/{1}/unassign-officer", Post);
    ADD_METHOD_TO(AccountsController::undoApproveSavingsAccountApplication, std::string(PREFIX) + "savings/{1}/undo-application-approval", Post);
    ADD_METHOD_TO(AccountsController::rejectSavingsAccountApplication, std::string(PREFIX) + "savings/{1}/reject-application", Post);
    ADD_METHOD_TO(AccountsController::withdrawSavingsAccountApplication, std::string(PREFIX) + "savings/{1}/withdraw-application", Post);
    ADD_METHOD_TO(AccountsController::activateSavingsAccountAccount, std::string(PREFIX) + "savings/{1}/activate-account", Post);
    ADD_METHOD_TO(AccountsController::closeSavingsAccount, std::string(PREFIX) + "savings/{1}/close-account", Post);
    ADD_METHOD_TO(AccountsController::deleteSavingsAccount, std::string(PREFIX) + "savings/{1}/delete", Post);
    ADD_METHOD_TO(AccountsController::calculateInterestOnSavingsAccount, std::string(PREFIX) + "savings/{1}/calculate-interest", Post);
    ADD_METHOD_TO(AccountsController::postInterestOnSavingsAccount, std::string(PREFIX) + "savings/{1}/post-interest", Post);
    ADD_METHOD_TO(AccountsController::blockInterestOnSavingsAccount, std::string(PREFIX) + "savings/{1}/block", Post);
    ADD_METHOD_TO(AccountsController::unblockInterestOnSavingsAccount, std::string(PREFIX) + "savings/{1}/unblock", Post);
    ADD_METHOD_TO(AccountsController::blockSavingsAccountCreditTransactions, std::string(PREFIX) + "savings/{1}/block-credit-transactions", Post); // Savings account will be blocked from all types of credit transactions.
    ADD_METHOD_TO(AccountsController::unblockSavingsAccountCreditTransactions, std::string(PREFIX) + "savings/{1}/block-credit-transactions", Post); // Savings account will be blocked from all types of credit transactions.
    ADD_METHOD_TO(AccountsController::blockSavingsAccountDebitTransactions, std::string(PREFIX) + "savings/{1}/block-credit-transactions", Post); // Savings account will be blocked from all types of credit transactions.
    ADD_METHOD_TO(AccountsController::unblockSavingsAccountDebitTransactions, std::string(PREFIX) + "savings/{1}/block-credit-transactions", Post); // Savings account will be blocked from all types of credit transactions.
    //GSIM
    ADD_METHOD_TO(AccountsController::submitNewGsim, std::string(PREFIX) + "savings/gsim", Post);
    ADD_METHOD_TO(AccountsController::approveGsimApplication, std::string(PREFIX) + "savings/gsim/{1}/approve", Post);
    ADD_METHOD_TO(AccountsController::undoApproveGsimApplication, std::string(PREFIX) + "savings/gsim/{1}/undo-approval", Post);
    ADD_METHOD_TO(AccountsController::rejectGsimApplication, std::string(PREFIX) + "savings/gsim/{1}/reject", Post);
    ADD_METHOD_TO(AccountsController::withdrawGsimApplication, std::string(PREFIX) + "savings/gsim/{1}/withdraw-by-applicant", Post);
    ADD_METHOD_TO(AccountsController::activateGsimApplication, std::string(PREFIX) + "savings/gsim/{1}/activate", Post);
    ADD_METHOD_TO(AccountsController::closeGsimApplication, std::string(PREFIX) + "savings/gsim/{1}/close", Post);
    //savings account transactions
    ADD_METHOD_TO(AccountsController::getSavingsAccountTransactionsTemplate, std::string(PREFIX) + "savings/{1}/transactions/template", Get);
    ADD_METHOD_TO(AccountsController::getSavingsAccountTransactionDetails, std::string(PREFIX) + "savings/{1}/transactions/{2}", Get);
    ADD_METHOD_TO(AccountsController::savingsAccountDepositTransaction, std::string(PREFIX) + "savings/{1}/transactions/deposit", Post);
    ADD_METHOD_TO(AccountsController::gsimDepositTransaction, std::string(PREFIX) + "savings/{1}/transactions/gsim-deposit", Post);
    ADD_METHOD_TO(AccountsController::savingsAccountWithdrawalTransaction, std::string(PREFIX) + "savings/{1}/transactions/withdrawal", Post);
    ADD_METHOD_TO(AccountsController::adjustSavingsAccountTransaction, std::string(PREFIX) + "savings/{1}/transactions/{2}/modify", Post);
    ADD_METHOD_TO(AccountsController::undoSavingsAccountTransaction, std::string(PREFIX) + "savings/{1}/transactions/{2}/undo", Post);
    ADD_METHOD_TO(AccountsController::holdAmountOnSavingsAccount, std::string(PREFIX) + "savings/{1}/transactions/hold-amount", Post);
    ADD_METHOD_TO(AccountsController::releaseAmountOnSavingsAccount, std::string(PREFIX) + "savings/{1}/transactions/release-amount", Post);
    //savings charges
    ADD_METHOD_TO(AccountsController::getSavingsCharges, std::string(PREFIX) + "savings/{1}/charges", Get);
    ADD_METHOD_TO(AccountsController::getSavingsAccountChargeDetails, std::string(PREFIX) + "savings/{1}/charges/{2}", Get);
    ADD_METHOD_TO(AccountsController::getSavingsAccountChargesTemplate, std::string(PREFIX) + "savings/{1}/charges/template", Get);
    ADD_METHOD_TO(AccountsController::createSavingsAccountCharge, std::string(PREFIX) + "savings/{1}/charges", Post);
    ADD_METHOD_TO(AccountsController::updateSavingsAccountCharge, std::string(PREFIX) + "savings/{1}/charges/{2}", Put);
    ADD_METHOD_TO(AccountsController::deleteSavingsAccountCharge, std::string(PREFIX) + "savings/{1}/charges/{2}", Delete);
    ADD_METHOD_TO(AccountsController::paySavingsAccountCharge, std::string(PREFIX) + "savings/{1}/charges/{2}/pay", Post);
    ADD_METHOD_TO(AccountsController::waiveSavingsAccountCharge, std::string(PREFIX) + "savings/{1}/charges/{2}/waive", Post);
    ADD_METHOD_TO(AccountsController::inactivateSavingsAccountCharge, std::string(PREFIX) + "savings/{1}/charges/{2}/inactivate", Post);
    ADD_METHOD_TO(AccountsController::inactivateSavingsAccountCharge, std::string(PREFIX) + "savings/{1}/charges/{2}/inactivate", Post);
    //fixed deposit account
    ADD_METHOD_TO(AccountsController::retrieveFixedDepositAccountTemplate, std::string(PREFIX) + "fixed-deposit/template", Get);
    ADD_METHOD_TO(AccountsController::getFixedDepositAccounts, std::string(PREFIX) + "fixed-deposit", Get);
    ADD_METHOD_TO(AccountsController::getFixedDepositAccountDetails, std::string(PREFIX) + "fixed-deposit/{1}", Get);
    ADD_METHOD_TO(AccountsController::createFixedDepositAccountApplication, std::string(PREFIX) + "fixed-deposit", Post);
    ADD_METHOD_TO(AccountsController::approveFixedDepositAccountApplication, std::string(PREFIX) + "fixed-deposit/{1}/approve", Post);
    ADD_METHOD_TO(AccountsController::undoApproveFixedDepositAccountApplication, std::string(PREFIX) + "fixed-deposit/{1}/undo-application-approval", Post);
    ADD_METHOD_TO(AccountsController::updateFixedDepositAccountApplication, std::string(PREFIX) + "fixed-deposit/{1}", Put);
    ADD_METHOD_TO(AccountsController::deleteFixedDepositAccountApplication, std::string(PREFIX) + "fixed-deposit/{1}", Delete);
    ADD_METHOD_TO(AccountsController::rejectFixedDepositAccountApplication, std::string(PREFIX) + "fixed-deposit/{1}/reject-application", Post);
    ADD_METHOD_TO(AccountsController::withdrawFixedDepositAccountApplication, std::string(PREFIX) + "fixed-deposit/{1}/withdraw-by-applicant", Post);
    ADD_METHOD_TO(AccountsController::activateFixedDepositAccount, std::string(PREFIX) + "fixed-deposit/{1}/activate", Post);
    ADD_METHOD_TO(AccountsController::closeFixedDepositAccount, std::string(PREFIX) + "fixed-deposit/{1}/close", Post);
    ADD_METHOD_TO(AccountsController::calculatePrematureAmountOnFixedDepositAccount, std::string(PREFIX) + "fixed-deposit/{1}/calculate-premature-amount", Post);
    ADD_METHOD_TO(AccountsController::prematureCloseFixedDepositAccount, std::string(PREFIX) + "fixed-deposit/{1}/premature-close", Post);
    ADD_METHOD_TO(AccountsController::calculateInterestOnFixedDepositAccount, std::string(PREFIX) + "fixed-deposit/{1}/calculate-interest", Post);
    ADD_METHOD_TO(AccountsController::postInterestOnFixedDepositAccount, std::string(PREFIX) + "fixed-deposit/{1}/post-interest", Post);
    //recurring deposit account
    ADD_METHOD_TO(AccountsController::retrieveRecurringDepositAccountTemplate, std::string(PREFIX) + "recurring-deposit/template", Get);
    ADD_METHOD_TO(AccountsController::getRecurringDepositAccounts, std::string(PREFIX) + "recurring-deposit", Get);
    ADD_METHOD_TO(AccountsController::getRecurringDepositAccountDetails, std::string(PREFIX) + "recurring-deposit/{1}", Get);
    ADD_METHOD_TO(AccountsController::createRecurringDepositAccountApplication, std::string(PREFIX) + "recurring-deposit", Post);
    ADD_METHOD_TO(AccountsController::approveRecurringDepositAccountApplication, std::string(PREFIX) + "recurring-deposit/{1}/approve", Post);
    ADD_METHOD_TO(AccountsController::undoApproveRecurringDepositAccountApplication, std::string(PREFIX) + "recurring-deposit/{1}/undo-application-approval", Post);
    ADD_METHOD_TO(AccountsController::updateRecurringDepositAccountApplication, std::string(PREFIX) + "recurring-deposit/{1}", Put);
    ADD_METHOD_TO(AccountsController::deleteRecurringDepositAccountApplication, std::string(PREFIX) + "recurring-deposit/{1}", Delete);
    ADD_METHOD_TO(AccountsController::rejectRecurringDepositAccountApplication, std::string(PREFIX) + "recurring-deposit/{1}/reject-application", Post);
    ADD_METHOD_TO(AccountsController::withdrawRecurringDepositAccountApplication, std::string(PREFIX) + "recurring-deposit/{1}/withdraw-by-applicant", Post);
    ADD_METHOD_TO(AccountsController::activateRecurringDepositAccount, std::string(PREFIX) + "recurring-deposit/{1}/activate", Post);
    ADD_METHOD_TO(AccountsController::updateRecurringDepositRecommendedAmount, std::string(PREFIX) + "recurring-deposit/{1}/update-deposit-amount", Post);
    ADD_METHOD_TO(AccountsController::closeRecurringDepositAccount, std::string(PREFIX) + "recurring-deposit/{1}/close", Post);
    ADD_METHOD_TO(AccountsController::calculatePrematureAmountOnRecurringDepositAccount, std::string(PREFIX) + "recurring-deposit/{1}/calculate-premature-amount", Post);
    ADD_METHOD_TO(AccountsController::prematureCloseRecurringDepositAccount, std::string(PREFIX) + "recurring-deposit/{1}/premature-close", Post);
    ADD_METHOD_TO(AccountsController::calculateInterestOnRecurringDepositAccount, std::string(PREFIX) + "recurring-deposit/{1}/calculate-interest", Post);
    ADD_METHOD_TO(AccountsController::postInterestOnRecurringDepositAccount, std::string(PREFIX) + "recurring-deposit/{1}/post-interest", Post);
    //recurring deposit account transactions
    ADD_METHOD_TO(AccountsController::getRecurringDepositAccountTransactionsTemplate, std::string(PREFIX) + "recurring-deposit/{1}/transactions/template", Get);
    ADD_METHOD_TO(AccountsController::getRecurringDepositAccountTransactionDetails, std::string(PREFIX) + "recurring-deposit/{1}/transactions/{2}", Get);
    ADD_METHOD_TO(AccountsController::recurringDepositAccountDepositAccount, std::string(PREFIX) + "recurring-deposit/{1}/transactions/deposit", Post);
    ADD_METHOD_TO(AccountsController::recurringDepositAccountWithdrawalTransaction, std::string(PREFIX) + "recurring-deposit/{1}/transactions/withdrawal", Post);
    ADD_METHOD_TO(AccountsController::adjustRecurringDepositAccountTransaction, std::string(PREFIX) + "recurring-deposit/{1}/transactions/{2}/modify", Post);
    ADD_METHOD_TO(AccountsController::undoRecurringDepositAccountTransaction, std::string(PREFIX) + "recurring-deposit/{1}/transactions/{2}/undo", Post);
    ADD_METHOD_TO(AccountsController::holdAmountOnRecurringDepositAccount, std::string(PREFIX) + "recurring-deposit/{1}/transactions/hold-amount", Post);
    ADD_METHOD_TO(AccountsController::releaseAmountOnRecurringDepositAccount, std::string(PREFIX) + "recurring-deposit/{1}/transactions/release-amount", Post);


    METHOD_LIST_END

    void retrieveShareAccountTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getShareAccounts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createShareApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void approveShareApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void undoApproveShareApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void rejectShareApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void activateShareAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void closeShareAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void applyAdditionalShares(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void approveAdditionalShares(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void rejectAdditionalShares(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void redeemShares(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getShareAccountDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    /*
    Share application can only be modified when in 'Submitted and pending approval' state. Once the application is approved, the details cannot be changed using this method. Specific api endpoints will be created to allow change of interest detail such as rate, compounding period, posting period etc
     */
    void updateShareAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    //savings accounts...
    void retrieveSavingsAccountTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveSavingsAccountDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsAccounts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createSavingsAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateSavingsAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void modifySavingsAccountWithHoldTaxApplicability(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void approveSavingsAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void assignSavingsOfficer(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void unassignSavingsOfficer(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void undoApproveSavingsAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void rejectSavingsAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void withdrawSavingsAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void activateSavingsAccountAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void closeSavingsAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteSavingsAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void calculateInterestOnSavingsAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void postInterestOnSavingsAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void blockInterestOnSavingsAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void unblockInterestOnSavingsAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void blockSavingsAccountCreditTransactions(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void unblockSavingsAccountCreditTransactions(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void blockSavingsAccountDebitTransactions(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void unblockSavingsAccountDebitTransactions(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //GSIM
    void submitNewGsim(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void approveGsimApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void undoApproveGsimApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void rejectGsimApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void withdrawGsimApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void activateGsimApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void closeGsimApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //savings account transactions
    void getSavingsAccountTransactionsTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsAccountTransactionDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void savingsAccountDepositTransaction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void gsimDepositTransaction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void savingsAccountWithdrawalTransaction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void adjustSavingsAccountTransaction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void undoSavingsAccountTransaction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void holdAmountOnSavingsAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void releaseAmountOnSavingsAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //savings charges
    void getSavingsCharges(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsAccountChargeDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsAccountChargesTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createSavingsAccountCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateSavingsAccountCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteSavingsAccountCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void paySavingsAccountCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void waiveSavingsAccountCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void inactivateSavingsAccountCharge(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //fixed deposit account
    void retrieveFixedDepositAccountTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getFixedDepositAccounts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getFixedDepositAccountDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createFixedDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void approveFixedDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void undoApproveFixedDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void rejectFixedDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void withdrawFixedDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void activateFixedDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void closeFixedDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void calculatePrematureAmountOnFixedDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void prematureCloseFixedDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void calculateInterestOnFixedDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void postInterestOnFixedDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateFixedDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteFixedDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //recurring deposit account
    void retrieveRecurringDepositAccountTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getRecurringDepositAccounts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getRecurringDepositAccountDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createRecurringDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void approveRecurringDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void undoApproveRecurringDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void rejectRecurringDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void withdrawRecurringDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void activateRecurringDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void closeRecurringDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateRecurringDepositRecommendedAmount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateRecurringDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteRecurringDepositAccountApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void calculatePrematureAmountOnRecurringDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void prematureCloseRecurringDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void calculateInterestOnRecurringDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void postInterestOnRecurringDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //recurring deposit account transactions
    void getRecurringDepositAccountTransactionsTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getRecurringDepositAccountTransactionDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void recurringDepositAccountDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void recurringDepositAccountWithdrawalTransaction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void adjustRecurringDepositAccountTransaction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void undoRecurringDepositAccountTransaction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void holdAmountOnRecurringDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void releaseAmountOnRecurringDepositAccount(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //




};
