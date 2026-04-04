#include "ClientsController.h"

#include "dto/BaseApiResponse.h"
#include "dto/ClientDto.h"
#include "dto/WithdrawOrRejectClientTransferDto.h"
#include "plugins/CustomerServicePlugin.h"

Task<HttpResponsePtr> ClientsController::getClients(HttpRequestPtr req) {

    int pageNo = 1;
    int pageSize = 10;

    auto pageNoStr = req->getParameter("pageNo");
    if (!pageNoStr.empty()) {
        pageNo = std::stoi(pageNoStr);
    }

    auto pageSizeStr = req->getParameter("pageSize");
    if (!pageSizeStr.empty()) {
        pageSize = std::stoi(pageSizeStr);
    }

    std::string query = req->getParameter("query");
    if (query.empty()) {
        query = "";
    }

    auto plugin = drogon::app().getPlugin<customer::plugins::CustomerServicePlugin>();
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

Task<HttpResponsePtr> ClientsController::activateClient(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::ActivateClientDto dto;
    dto.fromJson(*jsonBody);

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.activateClient(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::reactivateClient(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::ReactivateClientDto dto;
    dto.fromJson(*jsonBody);

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.reactivateClient(dto,id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::closeClient(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::CloseClientDto dto;
    dto.fromJson(*jsonBody);

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.closeClient(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::rejectClient(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::RejectClientDto dto;
    dto.fromJson(*jsonBody);

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.rejectClient(dto,id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::undoRejectClient(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::UndoRejectOrWithdrawalClientDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.undoRejectClient(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::withdrawClient(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::WithdrawClientDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.withdrawClient(dto,id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::undoWithdrawClient(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::UndoRejectOrWithdrawalClientDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.undoWithdrawClient(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::assignStaffToClient(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::AssignStaffToClientDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.assignStaffToClient(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::unassignStaffToClient(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::AssignStaffToClientDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.unassignStaffToClient(dto,id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::updateDefaultSavingsAccount(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();
    customer::dto::UpdateDefaultSavingsAccountDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.updateDefaultSavingsAccount(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::proposeClientTransfer(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();
    customer::dto::ProposeClientTransferDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.proposeClientTransfer(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::withdrawClientTransfer(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();
    customer::dto::WithdrawOrRejectClientTransferDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.withdrawClientTransfer(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::rejectClientTransfer(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::WithdrawOrRejectClientTransferDto dto;

    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.rejectClientTransfer(dto,id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::acceptClientTransfer(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();
    customer::dto::AcceptClientTransferDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.acceptClientTransfer(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::proposeAndAcceptClientTransfer(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::ProposeAndAcceptClientTransferDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.proposeAndAcceptClientTransfer(dto, id);
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
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.createClientAddress(dto,id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::updateClientAddress(HttpRequestPtr req, std::string id, std::string addressId) {

    auto jsonBody = req->getJsonObject();

    customer::dto::ClientAddressDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.updateClientAddress(dto,id,addressId);
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
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.createClientIdentifier(dto,id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}


Task<HttpResponsePtr> ClientsController::updateClientIdentifier(HttpRequestPtr req, std::string id, std::string identifierId) {

    auto jsonBody = req->getJsonObject();

    customer::dto::ClientIdentifierDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.updateClientIdentifier(dto,id, identifierId);
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

Task<HttpResponsePtr> ClientsController::addClientCharge(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    customer::dto::ClientChargeDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.addClientCharge(dto, id);
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

Task<HttpResponsePtr> ClientsController::payClientCharge(HttpRequestPtr req, std::string id, std::string chargeId) {

    auto jsonBody = req->getJsonObject();

    customer::dto::PayClientChargeDto dto;
    if (jsonBody) {
        dto.fromJson(*jsonBody);
    }

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.payClientCharge(dto, id, chargeId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::waiveClientCharge(HttpRequestPtr req, std::string id, std::string chargeId) {

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.waiveClientCharge(id, chargeId);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> ClientsController::undoClientTransaction(HttpRequestPtr req, std::string id, std::string transactionId) {

    auto plugin = app().getPlugin<customer::plugins::CustomerServicePlugin>();
    auto &clientService = plugin->getClientService();

    auto result = co_await clientService.undoClientTransaction(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}