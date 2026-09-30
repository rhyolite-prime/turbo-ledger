#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SelfController : public drogon::HttpController<SelfController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/self/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SelfController::verifyAuth, std::string(PREFIX) + "authentication", Post, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getAuthenticatedUserDetails, std::string(PREFIX) + "user-details", Post, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::updateUser, std::string(PREFIX) + "user", Put, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getAssociatedClients, std::string(PREFIX) + "clients", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getClientDetails, std::string(PREFIX) + "clients/{1}", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getClientAccountsOverview, std::string(PREFIX) + "clients/{1}/accounts", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::retrieveClientImage, std::string(PREFIX) + "clients/{1}/get-image", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getClientCharges, std::string(PREFIX) + "clients/{1}/charges", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getClientChargeDetails, std::string(PREFIX) + "clients/{1}/charges/{2}", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getClientTransactions, std::string(PREFIX) + "clients/{1}/transactions", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getClientTransactionDetails, std::string(PREFIX) + "clients/{1}/transaction/{2}", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::retrieveLoanDetailsTemplate, std::string(PREFIX) + "loans/template", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::retrieveLoanDetailsTemplate, std::string(PREFIX) + "loans/template", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::calculateLoanSchedule, std::string(PREFIX) + "loans/calculate-loan-schedule", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::submitLoanApplication, std::string(PREFIX) + "loans", Post, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getLoanDetails, std::string(PREFIX) + "loans/{1}", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getGuarantors, std::string(PREFIX) + "loans/{1}/guarantors", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::updateLoanApplication, std::string(PREFIX) + "loans/{1}/update", Put, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::withdrawLoanApplication, std::string(PREFIX) + "loans/{1}/withdrawn-by-applicant", Post, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getLoanTransactionDetails, std::string(PREFIX) + "loans/{1}/transactions/{2}", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getLoanCharges, std::string(PREFIX) + "loans/{1}/charges", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getLoanChargeDetails, std::string(PREFIX) + "loans/{1}/charges/{2}", Get, "CompositeAuthFilter");
    //savings
    ADD_METHOD_TO(SelfController::submitSavingsApplication, std::string(PREFIX) + "savings-accounts", Post, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getSavingsAccountDetails, std::string(PREFIX) + "savings-accounts/{1}", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::updateSavingsApplication, std::string(PREFIX) + "savings-accounts/{1}/update", Put, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getSavingsAccountTransactionDetails, std::string(PREFIX) + "savings-accounts/{1}/transactions/{2}", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getSavingsAccountCharges, std::string(PREFIX) + "savings-accounts/{1}/charges", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getSavingsAccountChargeDetail, std::string(PREFIX) + "savings-accounts/{1}/charges/{2}", Get, "CompositeAuthFilter");
    //account transfer
    ADD_METHOD_TO(SelfController::retrieveAccountTransferTemplate, std::string(PREFIX) + "accounts-transfers/template/", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::createAccountTransfer, std::string(PREFIX) + "accounts-transfers", Post, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::retrieveBeneficiaryThirdPartyTransferTemplate, std::string(PREFIX) + "beneficiaries/tpt/template", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::addThirdPartyTransferBeneficiary, std::string(PREFIX) + "beneficiaries/tpt", Post, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getThirdPartyTransferBeneficiaries, std::string(PREFIX) + "beneficiaries/tpt", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::updateThirdPartyTransferBeneficiary, std::string(PREFIX) + "beneficiaries/tpt/{1}", Put, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::deleteThirdPartyTransferBeneficiary, std::string(PREFIX) + "beneficiaries/tpt/{1}", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::retrieveThirdPartyAccountTransferTemplate, std::string(PREFIX) + "accounts-transfers/template/tpt", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::createThirdPartyAccountTransfer, std::string(PREFIX) + "accounts-transfers/tpt", Post, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::retrieveShareAccountTemplate, std::string(PREFIX) + "share-accounts/template", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::submitShareApplication, std::string(PREFIX) + "share-accounts", Post, "CompositeAuthFilter");
    //obligee
    ADD_METHOD_TO(SelfController::getObligees, std::string(PREFIX) + "clients/{1}/obligee-details", Get, "CompositeAuthFilter");
    //client image
    ADD_METHOD_TO(SelfController::uploadClientImage, std::string(PREFIX) + "clients/{1}/upload-image", Post, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::deleteClientImage, std::string(PREFIX) + "clients/{1}/delete-image", Delete, "CompositeAuthFilter");
    //loan products
    ADD_METHOD_TO(SelfController::getLoanProducts, std::string(PREFIX) + "loan-products", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getLoanProductDetails, std::string(PREFIX) + "loan-products/{1}", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getSavingsProduct, std::string(PREFIX) + "savings-products", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getSavingsProductDetails, std::string(PREFIX) + "savings-products/{1}", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getShareProducts, std::string(PREFIX) + "products/share", Get, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::getShareProductDetails, std::string(PREFIX) + "products/share/{1}", Get, "CompositeAuthFilter");
    //reports
    ADD_METHOD_TO(SelfController::runReports, std::string(PREFIX) + "run-reports/{1}", Get, "CompositeAuthFilter");
    //pockets
    ADD_METHOD_TO(SelfController::linkAccountsToPockets, std::string(PREFIX) + "pockets/link-accounts", Post, "CompositeAuthFilter");
    ADD_METHOD_TO(SelfController::delinkAccountsToPockets, std::string(PREFIX) + "pockets/delink-accounts", Post, "CompositeAuthFilter");

    METHOD_LIST_END

    Task<HttpResponsePtr> verifyAuth(HttpRequestPtr req);
    Task<HttpResponsePtr> getAuthenticatedUserDetails(HttpRequestPtr req);
    Task<HttpResponsePtr> updateUser(HttpRequestPtr req);
    Task<HttpResponsePtr> getAssociatedClients(HttpRequestPtr req);
    Task<HttpResponsePtr> getClientDetails(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getClientAccountsOverview(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> retrieveClientImage(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getClientCharges(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getClientChargeDetails(HttpRequestPtr req, const std::string &id, const std::string &chargeId);
    Task<HttpResponsePtr> getClientTransactions(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getClientTransactionDetails(HttpRequestPtr req, const std::string &id, const std::string &transactionId);
    Task<HttpResponsePtr> retrieveLoanDetailsTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> calculateLoanSchedule(HttpRequestPtr req);
    Task<HttpResponsePtr> submitLoanApplication(HttpRequestPtr req);
    Task<HttpResponsePtr> getLoanDetails(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getGuarantors(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> updateLoanApplication(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> withdrawLoanApplication(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getLoanTransactionDetails(HttpRequestPtr req, const std::string &id, const std::string &transactionId);
    Task<HttpResponsePtr> getLoanCharges(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getLoanChargeDetails(HttpRequestPtr req, const std::string &id, const std::string &chargeId);
    //savings
    Task<HttpResponsePtr> submitSavingsApplication(HttpRequestPtr req);
    Task<HttpResponsePtr> getSavingsAccountDetails(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> updateSavingsApplication(HttpRequestPtr req, const std::string &id);

    Task<HttpResponsePtr> getSavingsAccountTransactionDetails(HttpRequestPtr req, const std::string &id, const std::string &transactionId);
    Task<HttpResponsePtr> getSavingsAccountCharges(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getSavingsAccountChargeDetail(HttpRequestPtr req, const std::string &id, const std::string &chargeId);
    //account transfer
    Task<HttpResponsePtr> retrieveAccountTransferTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> createAccountTransfer(HttpRequestPtr req);
    Task<HttpResponsePtr> retrieveBeneficiaryThirdPartyTransferTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> addThirdPartyTransferBeneficiary(HttpRequestPtr req);
    Task<HttpResponsePtr> getThirdPartyTransferBeneficiaries(HttpRequestPtr req);
    Task<HttpResponsePtr> updateThirdPartyTransferBeneficiary(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> deleteThirdPartyTransferBeneficiary(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> retrieveThirdPartyAccountTransferTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> createThirdPartyAccountTransfer(HttpRequestPtr req);
    Task<HttpResponsePtr> retrieveShareAccountTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> submitShareApplication(HttpRequestPtr req);
    Task<HttpResponsePtr> getObligees(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> uploadClientImage(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> deleteClientImage(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getLoanProducts(HttpRequestPtr req);
    Task<HttpResponsePtr> getLoanProductDetails(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getSavingsProduct(HttpRequestPtr req);
    Task<HttpResponsePtr> getSavingsProductDetails(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> getShareProducts(HttpRequestPtr req);
    Task<HttpResponsePtr> getShareProductDetails(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> runReports(HttpRequestPtr req, const std::string &id);
    Task<HttpResponsePtr> linkAccountsToPockets(HttpRequestPtr req);
    Task<HttpResponsePtr> delinkAccountsToPockets(HttpRequestPtr req);


};
