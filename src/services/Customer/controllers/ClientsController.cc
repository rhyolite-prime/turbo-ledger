#include "ClientsController.h"

#include "dto/AccountTransferDto.h"
#include "dto/BaseApiResponse.h"
#include "dto/ClientDto.h"
#include "dto/WithdrawOrRejectClientTransferDto.h"
#include "plugins/CustomerServicePlugin.h"

Task<ClientsController::AuthResult> ClientsController::authenticateRequest(HttpRequestPtr req) {
    AuthResult result;
    auto clientId = req->getHeader("ClientId");
    auto clientSecret = req->getHeader("ClientSecret");

    if (clientId.empty() || clientSecret.empty()) {
        turbo_ledger_customer::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "ClientId and ClientSecret Headers are absent !";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        result.errorResponse = resp;
        co_return result;
    }

    auto plugin = drogon::app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &identityApi = plugin->getIdentityApi();

    auto businessIdentity = co_await identityApi.validateApiCredentials(clientId, clientSecret);

    if (!businessIdentity.isValid) {
        turbo_ledger_customer::dto::BaseApiResponse response;
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

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getAll(pageNo, pageSize, query);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::createClient(HttpRequestPtr req) {
    auto jsonBody = req->getJsonObject();
    if (!jsonBody) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setContentTypeCode(CT_APPLICATION_JSON);
        resp->setBody("{\"success\":false,\"message\":\"Request body must be valid JSON.\"}");
        co_return resp;
    }
    turbo_ledger_customer::dto::ClientDto clientDto;
    try {
        clientDto.fromJson(*jsonBody);
    } catch (const std::exception &e) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setContentTypeCode(CT_APPLICATION_JSON);
        resp->setBody(std::string("{\"success\":false,\"message\":\"Invalid payload: ") + e.what() + "\"}");
        co_return resp;
    }
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.createAsync(clientDto);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::updateClient(HttpRequestPtr req, std::string clientId) {
    auto jsonBody = req->getJsonObject();
    turbo_ledger_customer::dto::ClientDto clientDto;
    clientDto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.updateAsync(clientDto, clientId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientDetails(HttpRequestPtr req, std::string clientId) {
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientDetails(clientId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::deleteClient(HttpRequestPtr req, std::string clientId) {
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.deleteClient(clientId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::handleClientCommands(HttpRequestPtr req, std::string clientId) {
    std::string command = req->getParameter("command");
    auto jsonBody = req->getJsonObject();
    if (!jsonBody) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    turbo_ledger_customer::dto::BaseApiResponse result;
    if (command == "activate") {
        turbo_ledger_customer::dto::ActivateClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.activateClient(dto, clientId);
    } else if (command == "reactivate") {
        turbo_ledger_customer::dto::ReactivateClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.reactivateClient(dto, clientId);
    } else if (command == "close") {
        turbo_ledger_customer::dto::CloseClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.closeClient(dto, clientId);
    } else if (command == "reject") {
        turbo_ledger_customer::dto::RejectClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.rejectClient(dto, clientId);
    } else if (command == "undoReject") {
        turbo_ledger_customer::dto::UndoRejectOrWithdrawalClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.undoRejectClient(dto, clientId);
    } else if (command == "withdraw") {
        turbo_ledger_customer::dto::WithdrawClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.withdrawClient(dto, clientId);
    } else if (command == "undoWithdraw") {
        turbo_ledger_customer::dto::UndoRejectOrWithdrawalClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.undoWithdrawClient(dto, clientId);
    } else if (command == "assignStaff") {
        turbo_ledger_customer::dto::AssignStaffToClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.assignStaffToClient(dto, clientId);
    } else if (command == "unassignStaff") {
        turbo_ledger_customer::dto::AssignStaffToClientDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.unassignStaffToClient(dto, clientId);
    } else if (command == "updateSavingsAccount") {
        turbo_ledger_customer::dto::UpdateDefaultSavingsAccountDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.updateDefaultSavingsAccount(dto, clientId);
    } else if (command == "proposeTransfer") {
        turbo_ledger_customer::dto::ProposeClientTransferDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.proposeClientTransfer(dto, clientId);
    } else if (command == "withdrawTransfer") {
        turbo_ledger_customer::dto::WithdrawOrRejectClientTransferDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.withdrawClientTransfer(dto, clientId);
    } else if (command == "rejectTransfer") {
        turbo_ledger_customer::dto::WithdrawOrRejectClientTransferDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.rejectClientTransfer(dto, clientId);
    } else if (command == "acceptTransfer") {
        turbo_ledger_customer::dto::AcceptClientTransferDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.acceptClientTransfer(dto, clientId);
    } else if (command == "proposeAndAcceptTransfer") {
        turbo_ledger_customer::dto::ProposeAndAcceptClientTransferDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.proposeAndAcceptClientTransfer(dto, clientId);
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}



Task<HttpResponsePtr> ClientsController::getClientAddresses(HttpRequestPtr req, std::string clientId) {
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientAddresses(clientId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::createClientAddress(HttpRequestPtr req, std::string clientId) {
    auto jsonBody = req->getJsonObject();
    turbo_ledger_customer::dto::ClientAddressDto dto;
    dto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.createClientAddress(dto, clientId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::updateClientAddress(HttpRequestPtr req, std::string clientId, std::string addressId) {
    auto jsonBody = req->getJsonObject();
    turbo_ledger_customer::dto::ClientAddressDto dto;
    dto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.updateClientAddress(dto, clientId, addressId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::deleteClientAddress(HttpRequestPtr req, std::string clientId, std::string addressId) {
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.deleteClientAddress(clientId, addressId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientIdentifiers(HttpRequestPtr req, std::string clientId) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientIdentifiers(clientId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientIdentifierDetails(HttpRequestPtr req, std::string clientId, std::string identifierId) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientIdentifierDetails(clientId, identifierId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}

Task<HttpResponsePtr> ClientsController::createClientIdentifier(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();
    turbo_ledger_customer::dto::ClientIdentifierDto dto;
    dto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.createClientIdentifier(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::updateClientIdentifier(HttpRequestPtr req, std::string id, std::string identifierId) {

    auto jsonBody = req->getJsonObject();
    turbo_ledger_customer::dto::ClientIdentifierDto dto;
    dto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.updateClientIdentifier(dto, id, identifierId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::deleteClientIdentifier(HttpRequestPtr req, std::string id, std::string identifierId) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.deleteClientIdentifier(id, identifierId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}


// Standing Instructions

Task<HttpResponsePtr> ClientsController::listStandingInstructions(HttpRequestPtr req) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.getStandingInstructions();
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}


Task<HttpResponsePtr> ClientsController::getStandingInstructionDetails(HttpRequestPtr req, std::string standingInstructionId) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getStandingInstructionDetails(standingInstructionId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}


Task<HttpResponsePtr> ClientsController::createStandingInstruction(HttpRequestPtr req) {

    auto jsonBody = req->getJsonObject();

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    turbo_ledger_customer::dto::StandingInstructionDto dto;
    dto.fromJson(*jsonBody);

    auto result = co_await clientService.createStandingInstruction(dto);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}


Task<HttpResponsePtr> ClientsController::updateStandingInstruction(HttpRequestPtr req, std::string standingInstructionId) {

    auto jsonBody = req->getJsonObject();

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    turbo_ledger_customer::dto::StandingInstructionDto dto;
    dto.fromJson(*jsonBody);

    auto result = co_await clientService.updateStandingInstruction(standingInstructionId, dto);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;


}


Task<HttpResponsePtr> ClientsController::deleteStandingInstruction(HttpRequestPtr req, std::string standingInstructionId) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.deleteStandingInstruction(standingInstructionId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}


Task<HttpResponsePtr> ClientsController::runStandingInstructionHistory(HttpRequestPtr req) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.runStandingInstructionHistory();
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}


Task<HttpResponsePtr> ClientsController::listAccountTransfers(HttpRequestPtr req) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.getAccountTransfers();
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}


Task<HttpResponsePtr> ClientsController::getAccountTransferDetails(HttpRequestPtr req, std::string accountTransferId) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.getAccountTransferDetails(accountTransferId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}


Task<HttpResponsePtr> ClientsController::createAccountTransfer(HttpRequestPtr req) {

    auto jsonBody = req->getJsonObject();

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    turbo_ledger_customer::dto::AccountTransferDto dto;
    dto.fromJson(*jsonBody);

    auto result = co_await clientService.createAccountTransfer(dto);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}


Task<HttpResponsePtr> ClientsController::refundByAccountTransfer(HttpRequestPtr req) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.refundByAccountTransfer();
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}


Task<HttpResponsePtr> ClientsController::getClientTransactions(HttpRequestPtr req, std::string id) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientTransactions(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientTransactionDetails(HttpRequestPtr req, std::string id, std::string transactionId) {

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientTransactionDetails(id, transactionId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::handleClientTransactionCommands(HttpRequestPtr req, std::string clientId, std::string transactionId) {
    std::string command = req->getParameter("command");
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    turbo_ledger_customer::dto::BaseApiResponse result;
    if (command == "undo") {
        result = co_await clientService.undoClientTransaction(clientId, transactionId);
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientCharges(HttpRequestPtr req, std::string id) {
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientCharges(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::addClientCharge(HttpRequestPtr req, std::string id) {
    auto jsonBody = req->getJsonObject();
    turbo_ledger_customer::dto::ClientChargeDto dto;
    dto.fromJson(*jsonBody);
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.addClientCharge(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::getClientChargeDetails(HttpRequestPtr req, std::string id, std::string chargeId) {
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.getClientChargeDetails(id, chargeId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::deleteClientCharge(HttpRequestPtr req, std::string id, std::string chargeId) {
    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();
    auto result = co_await clientService.deleteClientCharge(id, chargeId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::handleClientChargeCommands(HttpRequestPtr req, std::string clientId, std::string clientChargeId) {
    std::string command = req->getParameter("command");
    auto jsonBody = req->getJsonObject();

    auto plugin = app().getPlugin<turbo_ledger_customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    turbo_ledger_customer::dto::BaseApiResponse result;
    if (command == "pay") {
        if (!jsonBody) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            co_return resp;
        }
        turbo_ledger_customer::dto::PayClientChargeDto dto;
        dto.fromJson(*jsonBody);
        result = co_await clientService.payClientCharge(dto, clientId, clientChargeId);
    } else if (command == "waive") {
        result = co_await clientService.waiveClientCharge(clientId, clientChargeId);
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}


