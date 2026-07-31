#pragma once

#include "filters/JsonBodyFilter.h"
#include <drogon/HttpController.h>

using namespace drogon;

class ClientsController : public drogon::HttpController<ClientsController> {
public:
  static constexpr const char *PREFIX = "/api/v1/clients";
  
  METHOD_LIST_BEGIN
  // Base client endpoints
  ADD_METHOD_TO(ClientsController::getClients, PREFIX, Get, Options);
  ADD_METHOD_TO(ClientsController::createClient, PREFIX, Post, Options);
  ADD_METHOD_TO(ClientsController::getClientDetails, std::string(PREFIX) + "/{1}", Get, Options);
  ADD_METHOD_TO(ClientsController::updateClient, std::string(PREFIX) + "/{1}", Put, Options);
  ADD_METHOD_TO(ClientsController::deleteClient, std::string(PREFIX) + "/{1}", Delete, Options);
  
  // Single endpoint for all client commands (activate, close, etc.)
  ADD_METHOD_TO(ClientsController::handleClientCommands, std::string(PREFIX) + "/{1}", Post, Options);

  // client accounts
  ADD_METHOD_TO(ClientsController::getClientAccountsOverview, std::string(PREFIX) + "/{1}/accounts", Get, Options);
  
  // client addresses
  ADD_METHOD_TO(ClientsController::getClientAddresses, std::string(PREFIX) + "/{1}/addresses", Get, Options);
  ADD_METHOD_TO(ClientsController::createClientAddress, std::string(PREFIX) + "/{1}/addresses", Post, Options);
  ADD_METHOD_TO(ClientsController::updateClientAddress, std::string(PREFIX) + "/{1}/addresses/{2}", Put, Options);
  ADD_METHOD_TO(ClientsController::deleteClientAddress, std::string(PREFIX) + "/{1}/addresses/{2}", Delete, Options);
  
  // client identifiers
  ADD_METHOD_TO(ClientsController::getClientIdentifiers, std::string(PREFIX) + "/{1}/identifiers", Get, Options);
  ADD_METHOD_TO(ClientsController::createClientIdentifier, std::string(PREFIX) + "/{1}/identifiers", Post, Options);
  ADD_METHOD_TO(ClientsController::updateClientIdentifier, std::string(PREFIX) + "/{1}/identifiers/{2}", Put, Options);
  ADD_METHOD_TO(ClientsController::deleteClientIdentifier, std::string(PREFIX) + "/{1}/identifiers/{2}", Delete, Options);

  // client transactions
  ADD_METHOD_TO(ClientsController::getClientTransactions, std::string(PREFIX) + "/{1}/transactions", Get, Options);
  ADD_METHOD_TO(ClientsController::getClientTransactionDetails, std::string(PREFIX) + "/{1}/transactions/{2}", Get, Options);
  ADD_METHOD_TO(ClientsController::handleClientTransactionCommands, std::string(PREFIX) + "/{1}/transactions/{2}", Post, Options);

  // client charges
  ADD_METHOD_TO(ClientsController::getClientCharges, std::string(PREFIX) + "/{1}/charges", Get, Options);
  ADD_METHOD_TO(ClientsController::addClientCharge, std::string(PREFIX) + "/{1}/charges", Post, Options);
  ADD_METHOD_TO(ClientsController::getClientChargeDetails, std::string(PREFIX) + "/{1}/charges/{2}", Get, Options);
  ADD_METHOD_TO(ClientsController::deleteClientCharge, std::string(PREFIX) + "/{1}/charges/{2}", Delete, Options);
  ADD_METHOD_TO(ClientsController::handleClientChargeCommands, std::string(PREFIX) + "/{1}/charges/{2}", Post, Options);
  METHOD_LIST_END

  Task<HttpResponsePtr> getClients(HttpRequestPtr req);
  Task<HttpResponsePtr> createClient(HttpRequestPtr req);
  Task<HttpResponsePtr> getClientDetails(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> updateClient(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> deleteClient(HttpRequestPtr req, std::string id);
  
  Task<HttpResponsePtr> handleClientCommands(HttpRequestPtr req, std::string id);
  
  Task<HttpResponsePtr> getClientAccountsOverview(HttpRequestPtr req, std::string id);

  // client addresses
  Task<HttpResponsePtr> getClientAddresses(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> createClientAddress(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> updateClientAddress(HttpRequestPtr req, std::string id, std::string addressId);
  Task<HttpResponsePtr> deleteClientAddress(HttpRequestPtr req, std::string id, std::string addressId);

  // client identifiers
  Task<HttpResponsePtr> getClientIdentifiers(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> createClientIdentifier(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> updateClientIdentifier(HttpRequestPtr req, std::string id, std::string identifierId);
  Task<HttpResponsePtr> deleteClientIdentifier(HttpRequestPtr req, std::string id, std::string identifierId);

  // client transactions
  Task<HttpResponsePtr> getClientTransactions(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> getClientTransactionDetails(HttpRequestPtr req, std::string id, std::string transactionId);
  Task<HttpResponsePtr> handleClientTransactionCommands(HttpRequestPtr req, std::string id, std::string transactionId);

  // client charges
  Task<HttpResponsePtr> getClientCharges(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> addClientCharge(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> getClientChargeDetails(HttpRequestPtr req, std::string id, std::string chargeId);
  Task<HttpResponsePtr> deleteClientCharge(HttpRequestPtr req, std::string id, std::string chargeId);
  Task<HttpResponsePtr> handleClientChargeCommands(HttpRequestPtr req, std::string id, std::string chargeId);



private:
  struct AuthResult {
    bool isValid = false;
    std::string businessId;
    HttpResponsePtr errorResponse;
  };

  Task<AuthResult> authenticateRequest(HttpRequestPtr req);

};


