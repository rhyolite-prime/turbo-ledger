#include "SelfController.h"

#include "plugins/CustomerServicePlugin.h"

Task<HttpResponsePtr> SelfController::verifyAuth(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getAuthenticatedUserDetails(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::updateUser(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getAssociatedClients(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getClientDetails(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getClientAccountsOverview(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::retrieveClientImage(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getClientCharges(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getClientChargeDetails(HttpRequestPtr req, const std::string &id, const std::string &chargeId) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getClientTransactions(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getClientTransactionDetails(HttpRequestPtr req, const std::string &id, const std::string &transactionId) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::retrieveLoanDetailsTemplate(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::calculateLoanSchedule(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::submitLoanApplication(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getLoanDetails(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getGuarantors(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::updateLoanApplication(HttpRequestPtr req,const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::withdrawLoanApplication(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getLoanTransactionDetails(HttpRequestPtr req, const std::string &id, const std::string &transactionId) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getLoanCharges(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getLoanChargeDetails(HttpRequestPtr req, const std::string &id, const std::string &chargeId) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::submitSavingsApplication(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getSavingsAccountDetails(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::updateSavingsApplication(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getSavingsAccountTransactionDetails(HttpRequestPtr req, const std::string &id, const std::string &transactionId) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getSavingsAccountCharges(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getSavingsAccountChargeDetail(HttpRequestPtr req, const std::string &id, const std::string &transactionId) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::retrieveAccountTransferTemplate(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::createAccountTransfer(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::retrieveBeneficiaryThirdPartyTransferTemplate(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::addThirdPartyTransferBeneficiary(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getThirdPartyTransferBeneficiaries(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::updateThirdPartyTransferBeneficiary(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::deleteThirdPartyTransferBeneficiary(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::retrieveThirdPartyAccountTransferTemplate(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::createThirdPartyAccountTransfer(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::retrieveShareAccountTemplate(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::submitShareApplication(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getObligees(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::uploadClientImage(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::deleteClientImage(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getLoanProducts(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getLoanProductDetails(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getSavingsProduct(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getSavingsProductDetails(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getShareProducts(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::getShareProductDetails(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::runReports(HttpRequestPtr req, const std::string &id) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::linkAccountsToPockets(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
Task<HttpResponsePtr> SelfController::delinkAccountsToPockets(HttpRequestPtr req) { co_return HttpResponse::newHttpResponse(); }
