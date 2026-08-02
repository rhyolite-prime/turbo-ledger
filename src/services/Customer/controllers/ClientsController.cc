#include "ClientsController.h"

#include "dto/BaseApiResponse.h"
#include "dto/ClientDto.h"
#include "dto/WithdrawOrRejectClientTransferDto.h"
#include "plugins/CustomerServicePlugin.h"

Task<ClientsController::AuthResult> ClientsController::authenticateRequest(HttpRequestPtr req) {
    AuthResult result;
    auto clientId = req->getHeader("ClientId");
    auto clientSecret = req->getHeader("ClientSecret");

    if (clientId.empty() || clientSecret.empty()) {
        BaseApiResponse response;
        response.success = false;
        response.error["message"] = "ClientId and ClientSecret Headers are absent !";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        result.errorResponse = resp;
        co_return result;
    }

    auto plugin = drogon::app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &identityApi = plugin->getIdentityApi();

    auto businessIdentity = co_await identityApi.validateApiCredentials(clientId, clientSecret);

    if (!businessIdentity.isValid) {
        data_support::dto::BaseApiResponse response;
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

Task<HttpResponsePtr> ClientsController::getClients(HttpRequestPtr req) {
    int pageNo = 1;
    int pageSize = 10;
    auto pageNoStr = req->getParameter("pageNo");
    if (!pageNoStr.empty()) pageNo = std::stoi(pageNoStr);
    auto pageSizeStr = req->getParameter("pageSize");
    if (!pageSizeStr.empty()) pageSize = std::stoi(pageSizeStr);
    std::string query = req->getParameter("query");

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getAll(pageNo, pageSize, query);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::createClient(HttpRequestPtr req) {
    auto jsonBody = req->getJsonObject();
    customer::dto::ClientDto clientDto;
    clientDto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.createAsync(clientDto);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::updateClient(HttpRequestPtr req, std::string id) {
    auto jsonBody = req->getJsonObject();
    customer::dto::ClientDto clientDto;
    clientDto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.updateAsync(clientDto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientDetails(HttpRequestPtr req, std::string id) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientDetails(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::deleteClient(HttpRequestPtr req, std::string id) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.deleteClient(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::handleClientCommands(HttpRequestPtr req, std::string id) {
    std::string command = req->getParameter("command");
    auto jsonBody = req->getJsonObject();
    if (!jsonBody) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    customer::dto::BaseApiResponse result;
    if (command == "activate") {
        customer::dto::ActivateClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.activateClient(dto, id);
    } else if (command == "reactivate") {
        customer::dto::ReactivateClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.reactivateClient(dto, id);
    } else if (command == "close") {
        customer::dto::CloseClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.closeClient(dto, id);
    } else if (command == "reject") {
        customer::dto::RejectClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.rejectClient(dto, id);
    } else if (command == "undoReject") {
        customer::dto::UndoRejectOrWithdrawalClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.undoRejectClient(dto, id);
    } else if (command == "withdraw") {
        customer::dto::WithdrawClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.withdrawClient(dto, id);
    } else if (command == "undoWithdraw") {
        customer::dto::UndoRejectOrWithdrawalClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.undoWithdrawClient(dto, id);
    } else if (command == "assignStaff") {
        customer::dto::AssignStaffToClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.assignStaffToClient(dto, id);
    } else if (command == "unassignStaff") {
        customer::dto::AssignStaffToClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.unassignStaffToClient(dto, id);
    } else if (command == "updateSavingsAccount") {
        customer::dto::UpdateDefaultSavingsAccountDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.updateDefaultSavingsAccount(dto, id);
    } else if (command == "proposeTransfer") {
        customer::dto::ProposeClientTransferDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.proposeClientTransfer(dto, id);
    } else if (command == "withdrawTransfer") {
        customer::dto::WithdrawOrRejectClientTransferDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.withdrawClientTransfer(dto, id);
    } else if (command == "rejectTransfer") {
        customer::dto::WithdrawOrRejectClientTransferDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.rejectClientTransfer(dto, id);
    } else if (command == "acceptTransfer") {
        customer::dto::AcceptClientTransferDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.acceptClientTransfer(dto, id);
    } else if (command == "proposeAndAcceptTransfer") {
        customer::dto::ProposeAndAcceptClientTransferDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.proposeAndAcceptClientTransfer(dto, id);
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientAccountsOverview(HttpRequestPtr req, std::string id) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientAccountsOverview(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientAddresses(HttpRequestPtr req, std::string id) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientAddresses(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::createClientAddress(HttpRequestPtr req, std::string id) {
    auto jsonBody = req->getJsonObject();
    customer::dto::ClientAddressDto dto;
    dto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.createClientAddress(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::updateClientAddress(HttpRequestPtr req, std::string id, std::string addressId) {
    auto jsonBody = req->getJsonObject();
    customer::dto::ClientAddressDto dto;
    dto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.updateClientAddress(dto, id, addressId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::deleteClientAddress(HttpRequestPtr req, std::string id, std::string addressId) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.deleteClientAddress(id, addressId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientIdentifiers(HttpRequestPtr req, std::string id) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientIdentifiers(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::createClientIdentifier(HttpRequestPtr req, std::string id) {
    auto jsonBody = req->getJsonObject();
    customer::dto::ClientIdentifierDto dto;
    dto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.createClientIdentifier(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::updateClientIdentifier(HttpRequestPtr req, std::string id, std::string identifierId) {
    auto jsonBody = req->getJsonObject();
    customer::dto::ClientIdentifierDto dto;
    dto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.updateClientIdentifier(dto, id, identifierId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::deleteClientIdentifier(HttpRequestPtr req, std::string id, std::string identifierId) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.deleteClientIdentifier(id, identifierId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientTransactions(HttpRequestPtr req, std::string id) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientTransactions(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientTransactionDetails(HttpRequestPtr req, std::string id, std::string transactionId) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientTransactionDetails(id, transactionId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::handleClientTransactionCommands(HttpRequestPtr req, std::string id, std::string transactionId) {
    std::string command = req->getParameter("command");
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    customer::dto::BaseApiResponse result;
    if (command == "undo") {
        result = co_await clientService.undoClientTransaction(id, transactionId);
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientCharges(HttpRequestPtr req, std::string id) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientCharges(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::addClientCharge(HttpRequestPtr req, std::string id) {
    auto jsonBody = req->getJsonObject();
    customer::dto::ClientChargeDto dto;
    dto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.addClientCharge(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientChargeDetails(HttpRequestPtr req, std::string id, std::string chargeId) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientChargeDetails(id, chargeId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::deleteClientCharge(HttpRequestPtr req, std::string id, std::string chargeId) {
    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.deleteClientCharge(id, chargeId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::handleClientChargeCommands(HttpRequestPtr req, std::string id, std::string chargeId) {
    std::string command = req->getParameter("command");
    auto jsonBody = req->getJsonObject();

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    customer::dto::BaseApiResponse result;
    if (command == "pay") {
        if (!jsonBody) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            co_return resp;
        }
        customer::dto::PayClientChargeDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.payClientCharge(dto, id, chargeId);
    } else if (command == "waive") {
        result = co_await clientService.waiveClientCharge(id, chargeId);
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}


