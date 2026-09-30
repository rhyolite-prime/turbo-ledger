#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ClientsController : public drogon::HttpController<ClientsController> {
public:
  static constexpr const char *PREFIX = "/api/v1/clients/";
  
  METHOD_LIST_BEGIN
  // Base client endpoints
  ADD_METHOD_TO(ClientsController::getClients, std::string(PREFIX) + "get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::createClient, std::string(PREFIX) + "create", Post, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::getClientDetails, std::string(PREFIX) + "{1}/get-details", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::updateClient, std::string(PREFIX) + "{1}/update", Put, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::deleteClient, std::string(PREFIX) + "{1}/delete", Delete, Options, "CompositeAuthFilter");
  
  // Single endpoint for all client commands (activate, close, etc.)
  ADD_METHOD_TO(ClientsController::handleClientCommands, std::string(PREFIX) + "{1}", Post, Options, "CompositeAuthFilter");

  // client addresses
  ADD_METHOD_TO(ClientsController::getClientAddresses, std::string(PREFIX) + "{1}/addresses/get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::createClientAddress, std::string(PREFIX) + "{1}/addresses/create", Post, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::updateClientAddress, std::string(PREFIX) + "{1}/addresses/{2}/update", Put, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::deleteClientAddress, std::string(PREFIX) + "{1}/addresses/{2}/delete", Delete, Options, "CompositeAuthFilter");
  
  // client identifiers
  ADD_METHOD_TO(ClientsController::getClientIdentifiers, std::string(PREFIX) + "{1}/identifiers/get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::getClientIdentifierDetails, std::string(PREFIX) + "{1}/identifiers/{2}", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::createClientIdentifier, std::string(PREFIX) + "{1}/identifiers/create", Post, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::updateClientIdentifier, std::string(PREFIX) + "{1}/identifiers/{2}/update", Put, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::deleteClientIdentifier, std::string(PREFIX) + "{1}/identifiers/{2}/delete", Delete, Options, "CompositeAuthFilter");

  // Standing Instructions
  ADD_METHOD_TO(ClientsController::listStandingInstructions, std::string(PREFIX) + "standing-instructions/get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::getStandingInstructionDetails, std::string(PREFIX) + "standing-instructions/{1}/get-details", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::createStandingInstruction, std::string(PREFIX) + "standing-instructions/create", Post, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::updateStandingInstruction, std::string(PREFIX) + "standing-instructions/{1}/update", Put, Options, "CompositeAuthFilter"); // status change
  ADD_METHOD_TO(ClientsController::deleteStandingInstruction, std::string(PREFIX) + "standing-instructions/{1}/delete", Delete, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::runStandingInstructionHistory, std::string(PREFIX) + "standing-instructions/run-history", Get, Options, "CompositeAuthFilter");




  // Account Transfer
  ADD_METHOD_TO(ClientsController::listAccountTransfers, std::string(PREFIX) + "account-transfers/get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::getAccountTransferDetails, std::string(PREFIX) + "account-transfers/{1}/get-details", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::createAccountTransfer, std::string(PREFIX) + "account-transfers/create", Post, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::refundByAccountTransfer, std::string(PREFIX) + "account-transfers/refund-by-transfer", Post, Options, "CompositeAuthFilter"); //Ability to refund an active loan by transferring to a savings account.

  // client charges
  ADD_METHOD_TO(ClientsController::getClientCharges, std::string(PREFIX) + "{1}/charges/get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::addClientCharge, std::string(PREFIX) + "{1}/charges/add", Post, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::getClientChargeDetails, std::string(PREFIX) + "{1}/charges/{2}/get-details", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::deleteClientCharge, std::string(PREFIX) + "{1}/charges/{2}/delete", Delete, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::handleClientChargeCommands, std::string(PREFIX) + "{1}/charges/{2}/handle-command", Post, Options, "CompositeAuthFilter");

  // client transactions
  ADD_METHOD_TO(ClientsController::getClientTransactions, std::string(PREFIX) + "{1}/transactions/get-all", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::getClientTransactionDetails, std::string(PREFIX) + "{1}/transactions/{2}", Get, Options, "CompositeAuthFilter");
  ADD_METHOD_TO(ClientsController::handleClientTransactionCommands, std::string(PREFIX) + "{1}/transactions/{2}/handle-command", Post, Options, "CompositeAuthFilter");

  METHOD_LIST_END

  Task<HttpResponsePtr> getClients(HttpRequestPtr req);
  Task<HttpResponsePtr> createClient(HttpRequestPtr req);
  Task<HttpResponsePtr> getClientDetails(HttpRequestPtr req, std::string clientId);
  Task<HttpResponsePtr> updateClient(HttpRequestPtr req, std::string clientId);
  Task<HttpResponsePtr> deleteClient(HttpRequestPtr req, std::string clientId);
  
  Task<HttpResponsePtr> handleClientCommands(HttpRequestPtr req, std::string id);

  // client addresses
  Task<HttpResponsePtr> getClientAddresses(HttpRequestPtr req, std::string clientId);
  Task<HttpResponsePtr> createClientAddress(HttpRequestPtr req, std::string clientId);
  Task<HttpResponsePtr> updateClientAddress(HttpRequestPtr req, std::string clientId, std::string addressId);
  Task<HttpResponsePtr> deleteClientAddress(HttpRequestPtr req, std::string clientId, std::string addressId);

  // client identifiers
  Task<HttpResponsePtr> getClientIdentifiers(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> getClientIdentifierDetails(HttpRequestPtr req, std::string clientId, std::string identifierId);
  Task<HttpResponsePtr> createClientIdentifier(HttpRequestPtr req, std::string clientId);
  Task<HttpResponsePtr> updateClientIdentifier(HttpRequestPtr req, std::string clientId, std::string identifierId);
  Task<HttpResponsePtr> deleteClientIdentifier(HttpRequestPtr req, std::string clientId, std::string identifierId);


  // Standing Instructions
  Task<HttpResponsePtr> listStandingInstructions(HttpRequestPtr req);
  Task<HttpResponsePtr> getStandingInstructionDetails(HttpRequestPtr req, std::string standingInstructionId);
  Task<HttpResponsePtr> createStandingInstruction(HttpRequestPtr req);
  Task<HttpResponsePtr> updateStandingInstruction(HttpRequestPtr req, std::string standingInstructionId);
  Task<HttpResponsePtr> deleteStandingInstruction(HttpRequestPtr req, std::string standingInstructionId);
  Task<HttpResponsePtr> runStandingInstructionHistory(HttpRequestPtr req);


  // Account Transfer
  Task<HttpResponsePtr> listAccountTransfers(HttpRequestPtr req);
  Task<HttpResponsePtr> getAccountTransferDetails(HttpRequestPtr req, std::string accountTransferId);
  Task<HttpResponsePtr> createAccountTransfer(HttpRequestPtr req);
  Task<HttpResponsePtr> refundByAccountTransfer(HttpRequestPtr req);


  // client charges
  Task<HttpResponsePtr> getClientCharges(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> addClientCharge(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> getClientChargeDetails(HttpRequestPtr req, std::string id, std::string chargeId);
  Task<HttpResponsePtr> deleteClientCharge(HttpRequestPtr req, std::string id, std::string chargeId);
  Task<HttpResponsePtr> handleClientChargeCommands(HttpRequestPtr req, std::string id, std::string chargeId);

  // client transactions
  Task<HttpResponsePtr> getClientTransactions(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> getClientTransactionDetails(HttpRequestPtr req, std::string id, std::string transactionId);
  Task<HttpResponsePtr> handleClientTransactionCommands(HttpRequestPtr req, std::string id, std::string transactionId);

private:
  struct AuthResult {
    bool isValid = false;
    std::string businessId;
    HttpResponsePtr errorResponse;
  };

  Task<AuthResult> authenticateRequest(HttpRequestPtr req);

};


