//
// Created by Emmanuel Addo-Odame on 02/04/2026.
//

#ifndef CUSTOMER_CLIENTSERVICE_H
#define CUSTOMER_CLIENTSERVICE_H

#include "dto/BaseApiResponse.h"
#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include "dto/ReactivateClientDto.h"
#include "dto/AcceptClientTransferDto.h"
#include "dto/AccountTransferDto.h"
#include "dto/ActivateClientDto.h"
#include "dto/AssignStaffToClientDto.h"
#include "dto/ClientAddressDto.h"
#include "dto/ClientChargeDto.h"
#include "dto/ClientDto.h"
#include "dto/ClientIdentifierDto.h"
#include "dto/CloseClientDto.h"
#include "dto/PayClientChargeDto.h"
#include "dto/ProposeAndAcceptClientTransferDto.h"
#include "dto/ProposeClientTransferDto.h"
#include "dto/RejectClientDto.h"
#include "dto/StandingInstructionDto.h"
#include "dto/UndoRejectOrWithdrawalClientDto.h"
#include "dto/UpdateDefaultSavingsAccountDto.h"
#include "dto/WithdrawClientDto.h"
#include "dto/WithdrawOrRejectClientTransferDto.h"

namespace turbo_ledger_customer::services {

    class ClientService {
    public:

        drogon::Task<dto::BaseApiResponse> getAll(int pageNo, int pageSize,const std::string &query);

        drogon::Task<dto::BaseApiResponse> createAsync(const dto::ClientDto &dto);

        drogon::Task<dto::BaseApiResponse> updateAsync(const dto::ClientDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> getClientDetails(const std::string &id);

        drogon::Task<dto::BaseApiResponse> deleteClient(const std::string &id);

        drogon::Task<dto::BaseApiResponse> activateClient(const dto::ActivateClientDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> closeClient(const dto::CloseClientDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> reactivateClient(const dto::ReactivateClientDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> rejectClient(const dto::RejectClientDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> undoRejectClient(const dto::UndoRejectOrWithdrawalClientDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> withdrawClient(const dto::WithdrawClientDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> undoWithdrawClient(const dto::UndoRejectOrWithdrawalClientDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> assignStaffToClient(const dto::AssignStaffToClientDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> unassignStaffToClient(const dto::AssignStaffToClientDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> updateDefaultSavingsAccount(const dto::UpdateDefaultSavingsAccountDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> proposeClientTransfer(const dto::ProposeClientTransferDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> withdrawClientTransfer(const dto::WithdrawOrRejectClientTransferDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> rejectClientTransfer(const dto::WithdrawOrRejectClientTransferDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> acceptClientTransfer(const dto::AcceptClientTransferDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> proposeAndAcceptClientTransfer(const dto::ProposeAndAcceptClientTransferDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> getClientAccountsOverview(const std::string &id);

        drogon::Task<dto::BaseApiResponse> getClientAddresses(const std::string &id);

        drogon::Task<dto::BaseApiResponse> createClientAddress(const dto::ClientAddressDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> updateClientAddress(const dto::ClientAddressDto &dto, const std::string &id, std::string addressId);

        drogon::Task<dto::BaseApiResponse> deleteClientAddress(const std::string &id, std::string addressId);

        drogon::Task<dto::BaseApiResponse> getClientIdentifiers(const std::string &id);

        drogon::Task<dto::BaseApiResponse> getClientIdentifierDetails(std::string &clientId, std::string &identifierId);

        drogon::Task<dto::BaseApiResponse> createClientIdentifier(const dto::ClientIdentifierDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> updateClientIdentifier(const dto::ClientIdentifierDto &dto, const std::string &id, std::string identifierId);

        drogon::Task<dto::BaseApiResponse> deleteClientIdentifier(const std::string &id, std::string identifierId);

        drogon::Task<dto::BaseApiResponse> getClientTransactions( const std::string &id);

        drogon::Task<dto::BaseApiResponse> getClientTransactionDetails(const std::string &id, std::string transactionId);

        drogon::Task<dto::BaseApiResponse> addClientCharge(const dto::ClientChargeDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> getClientCharges(const std::string &id);

        drogon::Task<dto::BaseApiResponse> getClientChargeDetails(const std::string &id, std::string chargeId);

        drogon::Task<dto::BaseApiResponse> deleteClientCharge(const std::string &id, std::string chargeId);

        drogon::Task<dto::BaseApiResponse> payClientCharge(const dto::PayClientChargeDto &dto, std::string id, std::string chargeId);

        drogon::Task<dto::BaseApiResponse> waiveClientCharge(const std::string &id, const std::string &chargeId);

        drogon::Task<dto::BaseApiResponse> undoClientTransaction(const std::string &id, std::string transactionId);

        // Standing Instructions ...

        drogon::Task<dto::BaseApiResponse> getStandingInstructions();

        drogon::Task<dto::BaseApiResponse> getStandingInstructionDetails(std::string standingInstructionId);

        drogon::Task<dto::BaseApiResponse> createStandingInstruction(const dto::StandingInstructionDto &dto);

        drogon::Task<dto::BaseApiResponse> updateStandingInstruction(std::string standingInstructionId, const dto::StandingInstructionDto &dto);

        drogon::Task<dto::BaseApiResponse> deleteStandingInstruction(std::string standingInstructionId);

        drogon::Task<dto::BaseApiResponse> runStandingInstructionHistory();

        // Account Transfer

        drogon::Task<dto::BaseApiResponse> getAccountTransfers();

        drogon::Task<dto::BaseApiResponse> createAccountTransfer(const dto::AccountTransferDto &dto);

        drogon::Task<dto::BaseApiResponse> getAccountTransferDetails(std::string accountTransferId);

        drogon::Task<dto::BaseApiResponse> refundByAccountTransfer();


    };

}
#endif //CUSTOMER_CLIENTSERVICE_H