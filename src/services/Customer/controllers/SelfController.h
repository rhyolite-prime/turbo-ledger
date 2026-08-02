#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SelfController : public drogon::HttpController<SelfController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/self/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SelfController::verifyAuth, std::string(PREFIX) + "authentication", Post);
    ADD_METHOD_TO(SelfController::getAuthenticatedUserDetails, std::string(PREFIX) + "user-details", Post);
    ADD_METHOD_TO(SelfController::updateUser, std::string(PREFIX) + "user", Put);
    ADD_METHOD_TO(SelfController::getAssociatedClients, std::string(PREFIX) + "clients", Get);
    ADD_METHOD_TO(SelfController::getClientDetails, std::string(PREFIX) + "clients/{1}", Get);
    ADD_METHOD_TO(SelfController::getClientAccountsOverview, std::string(PREFIX) + "clients/{1}/accounts", Get);
    ADD_METHOD_TO(SelfController::retrieveClientImage, std::string(PREFIX) + "clients/{1}/images", Get);
    ADD_METHOD_TO(SelfController::getClientCharges, std::string(PREFIX) + "clients/{1}/charges", Get);
    ADD_METHOD_TO(SelfController::getClientChargeDetails, std::string(PREFIX) + "clients/{1}/charges/{2}", Get);
    ADD_METHOD_TO(SelfController::getClientTransactions, std::string(PREFIX) + "clients/{1}/transactions", Get);
    ADD_METHOD_TO(SelfController::getClientTransactionDetails, std::string(PREFIX) + "clients/{1}/transaction/{2}", Get);
    ADD_METHOD_TO(SelfController::retrieveLoanDetailsTemplate, std::string(PREFIX) + "loans/template", Get);
    ADD_METHOD_TO(SelfController::calculateLoanSchedule, std::string(PREFIX) + "loans/calculate-loan-schedule", Get);
    ADD_METHOD_TO(SelfController::submitLoanApplication, std::string(PREFIX) + "loans", Post);
    ADD_METHOD_TO(SelfController::getLoanDetails, std::string(PREFIX) + "loans/{1}", Get);
    ADD_METHOD_TO(SelfController::getGuarantors, std::string(PREFIX) + "loans/{1}/guarantors", Get);
    ADD_METHOD_TO(SelfController::updateLoanApplication, std::string(PREFIX) + "loans/{1}", Put);
    ADD_METHOD_TO(SelfController::withdrawLoanApplication, std::string(PREFIX) + "loans/{1}/withdrawn-by-applicant", Post);
    ADD_METHOD_TO(SelfController::getLoanTransactionDetails, std::string(PREFIX) + "loans/{1}/transactions/{2}", Get);
    ADD_METHOD_TO(SelfController::getLoanCharges, std::string(PREFIX) + "loans/{1}/charges", Get);
    ADD_METHOD_TO(SelfController::getLoanChargeDetails, std::string(PREFIX) + "loans/{1}/charges/{2}", Get);
    //savings
    ADD_METHOD_TO(SelfController::submitSavingsApplication, std::string(PREFIX) + "savings-accounts", Post);
    ADD_METHOD_TO(SelfController::getSavingsAccountDetails, std::string(PREFIX) + "savings-accounts/{1}", Get);
    ADD_METHOD_TO(SelfController::updateSavingsApplication, std::string(PREFIX) + "savings-accounts/{1}", Put);
    ADD_METHOD_TO(SelfController::retrieveSavingsAccountTemplate, std::string(PREFIX) + "savings-accounts/template/{1}", Get);
    ADD_METHOD_TO(SelfController::getSavingsAccountTransactionDetails, std::string(PREFIX) + "savings-accounts/{1}/transactions/{2}", Get);
    ADD_METHOD_TO(SelfController::getSavingsAccountCharges, std::string(PREFIX) + "savings-accounts/{1}/charges", Get);
    ADD_METHOD_TO(SelfController::getSavingsAccountChargeDetail, std::string(PREFIX) + "savings-accounts/{1}/charges/{2}", Get);
    //account transfer
    ADD_METHOD_TO(SelfController::retrieveAccountTransferTemplate, std::string(PREFIX) + "accounts-transfers/template/", Get);
    ADD_METHOD_TO(SelfController::createAccountTransfer, std::string(PREFIX) + "accounts-transfers", Post);
    ADD_METHOD_TO(SelfController::retrieveBeneficiaryThirdPartyTransferTemplate, std::string(PREFIX) + "beneficiaries/tpt/template", Get);
    ADD_METHOD_TO(SelfController::addThirdPartyTransferBeneficiary, std::string(PREFIX) + "beneficiaries/tpt", Post);
    ADD_METHOD_TO(SelfController::getThirdPartyTransferBeneficiaries, std::string(PREFIX) + "beneficiaries/tpt", Get);
    ADD_METHOD_TO(SelfController::updateThirdPartyTransferBeneficiary, std::string(PREFIX) + "beneficiaries/tpt/{1}", Put);
    ADD_METHOD_TO(SelfController::deleteThirdPartyTransferBeneficiary, std::string(PREFIX) + "beneficiaries/tpt/{1}", Get);
    ADD_METHOD_TO(SelfController::retrieveThirdPartyAccountTransferTemplate, std::string(PREFIX) + "accounts-transfers/template/tpt", Get);
    ADD_METHOD_TO(SelfController::createThirdPartyAccountTransfer, std::string(PREFIX) + "accounts-transfers/tpt", Post);
    ADD_METHOD_TO(SelfController::retrieveShareAccountTemplate, std::string(PREFIX) + "share-accounts/template", Get);
    ADD_METHOD_TO(SelfController::submitShareApplication, std::string(PREFIX) + "share-accounts", Post);
    //obligee
    ADD_METHOD_TO(SelfController::getObligees, std::string(PREFIX) + "clients/{1}/obligee-details", Get);
    //client image
    ADD_METHOD_TO(SelfController::uploadClientImage, std::string(PREFIX) + "clients/{1}/images", Post);
    ADD_METHOD_TO(SelfController::deleteClientImage, std::string(PREFIX) + "clients/{1}/images", Delete);
    //loan products
    ADD_METHOD_TO(SelfController::getLoanProducts, std::string(PREFIX) + "loan-products", Get);
    ADD_METHOD_TO(SelfController::getLoanProductDetails, std::string(PREFIX) + "loan-products/{1}", Get);
    ADD_METHOD_TO(SelfController::getSavingsProduct, std::string(PREFIX) + "savings-products", Get);
    ADD_METHOD_TO(SelfController::getSavingsProductDetails, std::string(PREFIX) + "savings-products/{1}", Get);
    ADD_METHOD_TO(SelfController::getShareProducts, std::string(PREFIX) + "products/share", Get);
    ADD_METHOD_TO(SelfController::getShareProductDetails, std::string(PREFIX) + "products/share/{1}", Get);
    //reports
    ADD_METHOD_TO(SelfController::runReports, std::string(PREFIX) + "run-reports/{1}", Get);
    //pockets
    ADD_METHOD_TO(SelfController::linkAccountsToPockets, std::string(PREFIX) + "pockets/link-accounts", Post);
    ADD_METHOD_TO(SelfController::delinkAccountsToPockets, std::string(PREFIX) + "pockets/delink-accounts", Post);

    METHOD_LIST_END

    Task<HttpResponsePtr> verifyAuth(HttpRequestPtr req);
    Task<HttpResponsePtr> getAuthenticatedUserDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> updateUser(HttpRequestPtr req);
    Task<HttpResponsePtr> getAssociatedClients(HttpRequestPtr req);
    Task<HttpResponsePtr> getClientDetails(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getClientAccountsOverview(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> retrieveClientImage(HttpRequestPtr req);
    Task<HttpResponsePtr> getClientCharges(HttpRequestPtr req);
    Task<HttpResponsePtr> getClientChargeDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> getClientTransactions(HttpRequestPtr req);
    Task<HttpResponsePtr> getClientTransactionDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> retrieveLoanDetailsTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> calculateLoanSchedule(HttpRequestPtr req);
    Task<HttpResponsePtr> submitLoanApplication(HttpRequestPtr req);
    Task<HttpResponsePtr> getLoanDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> getGuarantors(HttpRequestPtr req);
    Task<HttpResponsePtr> updateLoanApplication(HttpRequestPtr req);
    Task<HttpResponsePtr> withdrawLoanApplication(HttpRequestPtr req);
    Task<HttpResponsePtr> getLoanTransactionDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> getLoanCharges(HttpRequestPtr req);
    Task<HttpResponsePtr> getLoanChargeDetails(HttpRequestPtr req);
    //savings
    Task<HttpResponsePtr> submitSavingsApplication(HttpRequestPtr req);
    Task<HttpResponsePtr> getSavingsAccountDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> updateSavingsApplication(HttpRequestPtr req);
    Task<HttpResponsePtr> retrieveSavingsAccountTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> getSavingsAccountTransactionDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> getSavingsAccountCharges(HttpRequestPtr req);
    Task<HttpResponsePtr> getSavingsAccountChargeDetail(HttpRequestPtr req);
    //account transfer
    Task<HttpResponsePtr> retrieveAccountTransferTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> createAccountTransfer(HttpRequestPtr req);
    Task<HttpResponsePtr> retrieveBeneficiaryThirdPartyTransferTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> addThirdPartyTransferBeneficiary(HttpRequestPtr req);
    Task<HttpResponsePtr> getThirdPartyTransferBeneficiaries(HttpRequestPtr req);
    Task<HttpResponsePtr> updateThirdPartyTransferBeneficiary(HttpRequestPtr req);
    Task<HttpResponsePtr> deleteThirdPartyTransferBeneficiary(HttpRequestPtr req);
    Task<HttpResponsePtr> retrieveThirdPartyAccountTransferTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> createThirdPartyAccountTransfer(HttpRequestPtr req);
    Task<HttpResponsePtr> retrieveShareAccountTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> submitShareApplication(HttpRequestPtr req);
    Task<HttpResponsePtr> getObligees(HttpRequestPtr req);
    Task<HttpResponsePtr> uploadClientImage(HttpRequestPtr req);
    Task<HttpResponsePtr> deleteClientImage(HttpRequestPtr req);
    Task<HttpResponsePtr> getLoanProducts(HttpRequestPtr req);
    Task<HttpResponsePtr> getLoanProductDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> getSavingsProduct(HttpRequestPtr req);
    Task<HttpResponsePtr> getSavingsProductDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> getShareProducts(HttpRequestPtr req);
    Task<HttpResponsePtr> getShareProductDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> runReports(HttpRequestPtr req);
    Task<HttpResponsePtr> linkAccountsToPockets(HttpRequestPtr req);
    Task<HttpResponsePtr> delinkAccountsToPockets(HttpRequestPtr req);


};
