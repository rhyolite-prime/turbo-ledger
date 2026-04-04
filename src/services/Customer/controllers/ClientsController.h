#pragma once

#include "filters/JsonBodyFilter.h"
#include <drogon/HttpController.h>

using namespace drogon;

class ClientsController : public drogon::HttpController<ClientsController> {
public:
  static constexpr const char *PREFIX = "/api/v1/clients/";
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(ClientsController::getClients, std::string(PREFIX) + "get-all", Get, Options);
  ADD_METHOD_TO(ClientsController::getClientDetails, std::string(PREFIX) + "{1}", Get, Options);
  ADD_METHOD_TO(ClientsController::createClient, std::string(PREFIX) + "create", Post, Options);
  ADD_METHOD_TO(ClientsController::updateClient, std::string(PREFIX) + "{1}", Put, Options);
  ADD_METHOD_TO(ClientsController::deleteClient, std::string(PREFIX) + "{1}", Delete, Options);
  ADD_METHOD_TO(ClientsController::activateClient, std::string(PREFIX) + "{1}/activate",  Post, Options);
  ADD_METHOD_TO(ClientsController::reactivateClient, std::string(PREFIX) + "{1}/reactivate", Post, Options);
  ADD_METHOD_TO(ClientsController::closeClient,  std::string(PREFIX) + "{1}/close", Post, Options);
  ADD_METHOD_TO(ClientsController::rejectClient,  std::string(PREFIX) + "{1}/reject", Post, Options);
  ADD_METHOD_TO(ClientsController::undoRejectClient, std::string(PREFIX) + "{1}/undo-reject", Post, Options);
  ADD_METHOD_TO(ClientsController::withdrawClient, std::string(PREFIX) + "{1}/withdraw", Post, Options);
  ADD_METHOD_TO(ClientsController::undoWithdrawClient, std::string(PREFIX) + "{1}/undo-withdraw", Post, Options);
  ADD_METHOD_TO(ClientsController::assignStaffToClient, std::string(PREFIX) + "{1}/assign-staff", Post, Options);
  ADD_METHOD_TO(ClientsController::unassignStaffToClient, std::string(PREFIX) + "{1}/unassign-staff", Post, Options);
  ADD_METHOD_TO(ClientsController::updateDefaultSavingsAccount,  std::string(PREFIX) + "{1}/update-savings-account", Post, Options);
  ADD_METHOD_TO(ClientsController::proposeClientTransfer, std::string(PREFIX) + "{1}/propose-transfer", Post, Options);
  ADD_METHOD_TO(ClientsController::withdrawClientTransfer, std::string(PREFIX) + "{1}/withdraw-transfer", Post, Options);
  ADD_METHOD_TO(ClientsController::rejectClientTransfer, std::string(PREFIX) + "{1}/reject-transfer", Post, Options);
  ADD_METHOD_TO(ClientsController::acceptClientTransfer, std::string(PREFIX) + "{1}/accept-transfer", Post, Options);
  ADD_METHOD_TO(ClientsController::proposeAndAcceptClientTransfer, std::string(PREFIX) + "{1}/propose-and-accept-transfer", Put, Options);
  ADD_METHOD_TO(ClientsController::getClientAccountsOverview, std::string(PREFIX) + "{1}/accounts", Get, Options);
  // client addresses
  ADD_METHOD_TO(ClientsController::getClientAddresses, std::string(PREFIX) + "{1}/addresses", Get, Options);
  ADD_METHOD_TO(ClientsController::createClientAddress, std::string(PREFIX) + "{1}/addresses", Post, Options);
  ADD_METHOD_TO(ClientsController::updateClientAddress,  std::string(PREFIX) + "{1}/addresses/{2}", Put, Options);
  ADD_METHOD_TO(ClientsController::deleteClientAddress, std::string(PREFIX) + "{1}/addresses/{2}", Delete, Options);
  // client identifiers
  ADD_METHOD_TO(ClientsController::getClientIdentifiers, std::string(PREFIX) + "{1}/identifiers", Get);
  ADD_METHOD_TO(ClientsController::createClientIdentifier, std::string(PREFIX) + "{1}/identifiers", Post);
  ADD_METHOD_TO(ClientsController::updateClientIdentifier, std::string(PREFIX) + "{1}/identifiers/{2}", Put);
  ADD_METHOD_TO(ClientsController::deleteClientIdentifier,  std::string(PREFIX) + "{1}/identifiers/{2}", Delete);

  // client transactions
  ADD_METHOD_TO(ClientsController::getClientTransactions, std::string(PREFIX) + "{1}/transactions", Get);
  ADD_METHOD_TO(ClientsController::getClientTransactionDetails, std::string(PREFIX) + "{1}/transactions/{2}", Get);
  ADD_METHOD_TO(ClientsController::addClientCharge, std::string(PREFIX) + "{1}/charges", Post);
  ADD_METHOD_TO(ClientsController::getClientCharges, std::string(PREFIX) + "{1}/charges", Get);
  ADD_METHOD_TO(ClientsController::getClientChargeDetails, std::string(PREFIX) + "{1}/charges/{2}", Get);
  ADD_METHOD_TO(ClientsController::deleteClientCharge, std::string(PREFIX) + "{1}/charges/{2}", Delete);
  ADD_METHOD_TO(ClientsController::payClientCharge, std::string(PREFIX) + "{1}/charges/{2}/pay-charge", Post);
  ADD_METHOD_TO(ClientsController::waiveClientCharge,  std::string(PREFIX) + "{1}/charges/{2}/waive", Post);
  ADD_METHOD_TO(ClientsController::undoClientTransaction, std::string(PREFIX) + "{1}/transaction/{2}/undo", Post);
  METHOD_LIST_END


  Task<HttpResponsePtr> getClients(HttpRequestPtr req);

  Task<HttpResponsePtr> getClientDetails(HttpRequestPtr req, std::string id);

  Task<HttpResponsePtr> createClient(HttpRequestPtr req);

  Task<HttpResponsePtr> updateClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> deleteClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> activateClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> reactivateClient(HttpRequestPtr req, std::string id);

  Task<HttpResponsePtr> closeClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> rejectClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> undoRejectClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> withdrawClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> undoWithdrawClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> assignStaffToClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> unassignStaffToClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> updateDefaultSavingsAccount(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> proposeClientTransfer(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> withdrawClientTransfer(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> rejectClientTransfer(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> acceptClientTransfer(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> proposeAndAcceptClientTransfer(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> getClientAccountsOverview(HttpRequestPtr req, std::string id);
  // client addresses
  Task<HttpResponsePtr> getClientAddresses(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> createClientAddress(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> updateClientAddress(HttpRequestPtr req, std::string id, std::string addressId);
  Task<HttpResponsePtr> deleteClientAddress(HttpRequestPtr req, std::string id, std::string addressId);
  Task<HttpResponsePtr> getClientIdentifiers(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> createClientIdentifier(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> updateClientIdentifier(HttpRequestPtr req, std::string id, std::string identifierId);
  Task<HttpResponsePtr> deleteClientIdentifier(HttpRequestPtr req, std::string id, std::string identifierId);
  // client transactions
  Task<HttpResponsePtr> getClientTransactions(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> getClientTransactionDetails(HttpRequestPtr req, std::string id, std::string transactionId);
  Task<HttpResponsePtr> addClientCharge(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> getClientCharges(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> getClientChargeDetails(HttpRequestPtr req, std::string id, std::string chargeId);
  Task<HttpResponsePtr> deleteClientCharge(HttpRequestPtr req, std::string id, std::string chargeId);
  Task<HttpResponsePtr> payClientCharge(HttpRequestPtr req, std::string id, std::string chargeId);
  Task<HttpResponsePtr> waiveClientCharge(HttpRequestPtr req, std::string id, std::string chargeId);
  Task<HttpResponsePtr> undoClientTransaction(HttpRequestPtr req, std::string id, std::string transactionId);
};
