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

    void verifyAuth(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getAuthenticatedUserDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getAssociatedClients(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getClientDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getClientAccountsOverview(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveClientImage(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getClientCharges(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getClientChargeDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getClientTransactions(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getClientTransactionDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveLoanDetailsTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void calculateLoanSchedule(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void submitLoanApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getLoanDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getGuarantors(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateLoanApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void withdrawLoanApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getLoanTransactionDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getLoanCharges(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getLoanChargeDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //savings
    void submitSavingsApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsAccountDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateSavingsApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveSavingsAccountTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsAccountTransactionDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsAccountCharges(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsAccountChargeDetail(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //account transfer
    void retrieveAccountTransferTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createAccountTransfer(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveBeneficiaryThirdPartyTransferTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void addThirdPartyTransferBeneficiary(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getThirdPartyTransferBeneficiaries(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateThirdPartyTransferBeneficiary(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteThirdPartyTransferBeneficiary(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveThirdPartyAccountTransferTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createThirdPartyAccountTransfer(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveShareAccountTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void submitShareApplication(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getObligees(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void uploadClientImage(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteClientImage(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getLoanProducts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getLoanProductDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsProductDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getShareProducts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getShareProductDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void runReports(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void linkAccountsToPockets(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void delinkAccountsToPockets(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
