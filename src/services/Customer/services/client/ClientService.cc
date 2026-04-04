//
// Created by Emmanuel Addo-Odame on 02/04/2026.
//

#include "constants/ErrorCodes.h"
#include "dto/BaseApiResponse.h"
#include "dto/ClientDto.h"
#include "ClientService.h"
#include "Client.h"
#include "ClientAddress.h"
#include "ClientCharge.h"
#include "ClientIdentifier.h"
#include "ClientTransaction.h"
#include "constants/ClientStatus.h"
#include "constants/ReactivateClientDto.h"
#include "dto/ActivateClientDto.h"

using namespace drogon::orm;
namespace customer::services {

  drogon::Task<dto::BaseApiResponse> ClientService::getAll(int pageNo, int pageSize, const std::string &query) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      Criteria searchCriteria;

      if (!query.empty()) {
        std::string likeQuery = "%" + query + "%";
        searchCriteria = Criteria(drogon_model::TlCustomerDb::Client::Cols::_firstname,CompareOperator::Like, likeQuery);
        searchCriteria = Criteria(drogon_model::TlCustomerDb::Client::Cols::_lastname,CompareOperator::Like, likeQuery);
        searchCriteria = Criteria(drogon_model::TlCustomerDb::Client::Cols::_mobile_no,CompareOperator::Like, likeQuery);
        searchCriteria = Criteria(drogon_model::TlCustomerDb::Client::Cols::_account_no,CompareOperator::Like, likeQuery);
      }

      try {
        auto totalCount = co_await mapper.count(searchCriteria);

        if (totalCount == 0) {
          dto::BaseApiResponse response;
          response.success = true;
          response.result["data"] = Json::arrayValue;
          response.result["totalCount"] = 0;
          co_return response;
        }

        int offset = (pageNo - 1) * pageSize;
        auto result =
            co_await mapper.orderBy(drogon_model::TlCustomerDb::Client::Cols::_created_on_utc, SortOrder::DESC)
                .limit(pageSize)
                .offset(offset)
                .findBy(searchCriteria);

        auto totalPages = (totalCount + pageSize - 1) / pageSize;

        dto::BaseApiResponse response;
        response.success = true;
        response.result["totalCount"] = (Json::UInt64)totalCount;
        response.result["pageNo"] = pageNo;
        response.result["pageSize"] = pageSize;
        response.result["totalPages"] = (int)totalPages;
        response.result["lowerBound"] = pageSize * (pageNo - 1) + 1;
        response.result["upperBound"] = (int)totalPages == pageNo ? (Json::UInt64)totalCount : (Json::UInt64)(pageNo * pageSize);

        Json::Value data = Json::arrayValue;
        for (const auto &client : result) {
          Json::Value clientJson;

          clientJson["id"] = client.getValueOfId();
          clientJson["accountNo"] = client.getValueOfAccountNo();
          clientJson["externalId"] = client.getValueOfExternalId();
          clientJson["firstName"] = client.getValueOfFirstname();
          clientJson["lastName"] = client.getValueOfLastname();
          clientJson["mobileNo"] = client.getValueOfMobileNo();
          clientJson["emailAddress"] = client.getValueOfEmailAddress();

          data.append(clientJson);
        }
        response.result["data"] = data;
        co_return response;

      } catch (const drogon::orm::DrogonDbException &e) {
        dto::BaseApiResponse errorResponse;
        errorResponse.success = false;
        errorResponse.error["code"] = constants::ERR_DB_QUERY;
        errorResponse.error["message"] = "Database error while fetching tickets.";
        errorResponse.error["detail"] = e.base().what();
        co_return errorResponse;
      } catch (const std::exception &e) {
        dto::BaseApiResponse errorResponse;
        errorResponse.success = false;
        errorResponse.error["code"] = constants::ERR_INTERNAL;
        errorResponse.error["message"] = "Internal error.";
        errorResponse.error["detail"] = e.what();
        co_return errorResponse;
      }
}

  drogon::Task<dto::BaseApiResponse> ClientService::createAsync(const dto::ClientDto &dto) {

        dto::BaseApiResponse response;
        auto dbClient = drogon::app().getDbClient();
        drogon::orm::CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

        try {
            drogon_model::TlCustomerDb::Client client;
            client.setAccountNo(dto.getAccountNo());
            client.setExternalId(dto.getExternalId());
            client.setStatusEnum(dto.getStatusEnum());
            client.setSubStatus(dto.getSubStatus());

            if (!dto.getActivationDate().empty())
                client.setActivationDate(trantor::Date::fromDbString(dto.getActivationDate()));
            if (!dto.getOfficeJoiningDate().empty())
                client.setOfficeJoiningDate(trantor::Date::fromDbString(dto.getOfficeJoiningDate()));

            client.setOfficeId(dto.getOfficeId());
            client.setTransferToOfficeId(dto.getTransferToOfficeId());
            client.setStaffId(dto.getStaffId());
            client.setFirstname(dto.getFirstname());
            client.setMiddlename(dto.getMiddlename());
            client.setLastname(dto.getLastname());
            client.setFullname(dto.getFullname());
            client.setDisplayName(dto.getDisplayName());
            client.setMobileNo(dto.getMobileNo());
            client.setIsStaff(dto.getIsStaff());
            client.setGenderCvId(dto.getGenderCvId());

            if (!dto.getDateOfBirth().empty())
                client.setDateOfBirth(trantor::Date::fromDbString(dto.getDateOfBirth()));

            client.setLegalFormEnum(dto.getLegalFormEnum());
            client.setEmailAddress(dto.getEmailAddress());

            auto savedClient = co_await mapper.insert(client);

            response.success = true;
            response.result = savedClient.toJson();
            response.message = "Client created successfully";
        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.message = "Database error: " + std::string(e.base().what());
        } catch (const std::exception &e) {
            response.success = false;
            response.message = "An error occurred: " + std::string(e.what());
        }

        co_return response;

    }

  drogon::Task<dto::BaseApiResponse> ClientService::updateAsync(const dto::ClientDto &dto, const std::string &id) {

        dto::BaseApiResponse response;
        auto dbClient = drogon::app().getDbClient();
        drogon::orm::CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

        try {
            // Find existing client. Assuming UpdateClientDto has a getId() method or similar.
            // If the ID is passed separately, you might need to adjust this.
            auto client = co_await mapper.findByPrimaryKey(id);

            client.setAccountNo(dto.getAccountNo());
            client.setExternalId(dto.getExternalId());
            client.setStatusEnum(dto.getStatusEnum());
            client.setSubStatus(dto.getSubStatus());

            if (!dto.getActivationDate().empty())
                client.setActivationDate(trantor::Date::fromDbString(dto.getActivationDate()));
            if (!dto.getOfficeJoiningDate().empty())
                client.setOfficeJoiningDate(trantor::Date::fromDbString(dto.getOfficeJoiningDate()));

            client.setOfficeId(dto.getOfficeId());
            client.setTransferToOfficeId(dto.getTransferToOfficeId());
            client.setStaffId(dto.getStaffId());
            client.setFirstname(dto.getFirstname());
            client.setMiddlename(dto.getMiddlename());
            client.setLastname(dto.getLastname());
            client.setFullname(dto.getFullname());
            client.setDisplayName(dto.getDisplayName());
            client.setMobileNo(dto.getMobileNo());
            client.setIsStaff(dto.getIsStaff());
            client.setGenderCvId(dto.getGenderCvId());

            if (!dto.getDateOfBirth().empty())
                client.setDateOfBirth(trantor::Date::fromDbString(dto.getDateOfBirth()));

            client.setLegalFormEnum(dto.getLegalFormEnum());
            client.setEmailAddress(dto.getEmailAddress());

            auto updatedRows = co_await mapper.update(client);

            if (updatedRows > 0) {
                response.success = true;
                response.result = client.toJson();
                response.message = "Client updated successfully";
            } else {
                response.success = false;
                response.message = "No client found with the provided ID";
            }
        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.message = "Database error: " + std::string(e.base().what());
        } catch (const std::exception &e) {
            response.success = false;
            response.message = "An error occurred: " + std::string(e.what());
        }

        co_return response;


    }

  drogon::Task<dto::BaseApiResponse> ClientService::getClientDetails(const std::string &id) {



  }

  drogon::Task<dto::BaseApiResponse> ClientService::deleteClient(const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto deletedRowCount = co_await mapper.deleteByPrimaryKey(id);

          if (deletedRowCount == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found or already deleted.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.result["message"] = "Color deleted successfully";

          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while deleting color.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }

  }


  drogon::Task<dto::BaseApiResponse> ClientService::closeClient(const dto::CloseClientDto &dto,const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() == constants::ClientStatus::CLOSED) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Client is already closed.";
              co_return errorResponse;
          }

          // Clients can be closed if they do not have any non-closed loans/savingsAccount.
          // check portfolio and other sister services before proceeding

          client.setStatusEnum(constants::ClientStatus::CLOSED);
          client.setClosedonDate(dto.getClosureDate().empty() ? trantor::Date::now() : trantor::Date::fromDbString(dto.getClosureDate()));
          client.setClosureReasonCvId(dto.getClosureReasonCvId());

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found or could not be closed.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client closed successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while closing client.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }

  }

  drogon::Task<dto::BaseApiResponse> ClientService::activateClient(const dto::ActivateClientDto &dto, const std::string &id) {

    auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::PENDING) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Only clients in a pending state can be activated.";
              co_return errorResponse;
          }

          client.setStatusEnum(constants::ClientStatus::ACTIVE);
          client.setActivationDate(dto.getActivationDate().empty() ? trantor::Date::now() : trantor::Date::fromDbString(dto.getActivationDate()));

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found or could not be closed.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client activated successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while activating client.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }

  }

  drogon::Task<dto::BaseApiResponse> ClientService::rejectClient(const dto::RejectClientDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {

          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::PENDING) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Only clients in a pending state can be rejected.";
              co_return errorResponse;
          }

          client.setStatusEnum(constants::ClientStatus::REJECTED);
          client.setClosedonDate(dto.getRejectionDate().empty() ? trantor::Date::now() : trantor::Date::fromDbString(dto.getRejectionDate()));
          client.setClosureReasonCvId(dto.getRejectionCvId());

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found or could not be rejected.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client rejected successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while closing client.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }

  }

  drogon::Task<dto::BaseApiResponse> ClientService::reactivateClient(const dto::ReactivateClientDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::CLOSED) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Only closed clients can be reactivated.";
              co_return errorResponse;
          }

          client.setStatusEnum(constants::ClientStatus::ACTIVE);

          const auto reactivationDate = dto.getReactivationDate().empty()
               ? trantor::Date::now()
               : trantor::Date::fromDbString(dto.getReactivationDate());

          client.setReactivatedOnDate(reactivationDate);
          client.setReopenedOnDate(reactivationDate);

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found or could not be reactivated.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client activated successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while reactivating client.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }

  }

  drogon::Task<dto::BaseApiResponse> ClientService::undoRejectClient(const dto::UndoRejectOrWithdrawalClientDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::CLOSED) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Only closed clients can be reactivated.";
              co_return errorResponse;
          }

          client.setStatusEnum(constants::ClientStatus::ACTIVE);

          const auto reopenedDate = dto.getReopenedDate().empty()
                  ? trantor::Date::now()
                  : trantor::Date::fromDbString(dto.getReopenedDate());

          client.setReopenedOnDate(reopenedDate);
          client.setRejectedonDateToNull();

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found or could not be reactivated.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client activated successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while reactivating client.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }

  }

  drogon::Task<dto::BaseApiResponse> ClientService::withdrawClient(const dto::WithdrawClientDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {

          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::PENDING) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Only clients in a pending state can be rejected.";
              co_return errorResponse;
          }

          client.setStatusEnum(constants::ClientStatus::WITHDRAWN);
          client.setWithdrawnOnDate(dto.getWithdrawalDate().empty() ? trantor::Date::now() : trantor::Date::fromDbString(dto.getWithdrawalDate()));
          client.setWithdrawReasonCvId(dto.getWithdrawalReasonCvId());

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found or could not be rejected.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client rejected successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while closing client.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }


  }

  drogon::Task<dto::BaseApiResponse> ClientService::undoWithdrawClient(const dto::UndoRejectOrWithdrawalClientDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::WITHDRAWN) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Only withdrawn clients can be reactivated via undo-withdraw";
              co_return errorResponse;
          }

          client.setStatusEnum(constants::ClientStatus::ACTIVE);

          const auto reopenedDate = dto.getReopenedDate().empty()
                  ? trantor::Date::now()
                  : trantor::Date::fromDbString(dto.getReopenedDate());

          client.setReopenedOnDate(reopenedDate);
          client.setRejectedonDateToNull();

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found or could not be reactivated.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client activated successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while reactivating client.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }

  }

  drogon::Task<dto::BaseApiResponse> ClientService::assignStaffToClient(const dto::AssignStaffToClientDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          client.setStaffId(dto.getStaffId());

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Staff assigned to client successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while assigning staff to client.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::unassignStaffToClient(const dto::AssignStaffToClientDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          client.setStaffId("");

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Staff unassigned from client successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while unassigning staff from client.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::updateDefaultSavingsAccount(const dto::UpdateDefaultSavingsAccountDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          client.setDefaultSavingsAccount(dto.getSavingsAccountId());

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Default savings account updated successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while updating default savings account.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::proposeClientTransfer(const dto::ProposeClientTransferDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          if (dto.getDestinationOfficeId().empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Destination office ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::ACTIVE) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Only an active client can be transferred.";
              co_return errorResponse;
          }

          const auto transferDate = dto.getTransferDate().empty()
                  ? trantor::Date::now()
                  : trantor::Date::fromDbString(dto.getTransferDate());

          CoroMapper<drogon_model::TlCustomerDb::ClientTransaction> txMapper(dbClient);
          Criteria clientCriteria(drogon_model::TlCustomerDb::ClientTransaction::Cols::_client_id, CompareOperator::EQ, id);
          Criteria dateCriteria(drogon_model::TlCustomerDb::ClientTransaction::Cols::_transaction_date, CompareOperator::GE, transferDate.toDbStringLocal());
          dateCriteria = dateCriteria && Criteria(drogon_model::TlCustomerDb::ClientTransaction::Cols::_transaction_date, CompareOperator::LE, trantor::Date::now().toDbStringLocal());
          
          auto txCount = co_await txMapper.count(clientCriteria && dateCriteria);
          if (txCount > 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Cannot propose transfer: client has transaction(s) between the proposed transfer date and today.";
              co_return errorResponse;
          }

          client.setTransferToOfficeId(dto.getDestinationOfficeId());
          client.setStatusEnum(constants::ClientStatus::TRANSFER_IN_PROGRESS);
          client.setProposedTransferDate(transferDate);

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client transfer proposed successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while proposing client transfer.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::withdrawClientTransfer(const dto::WithdrawOrRejectClientTransferDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::TRANSFER_IN_PROGRESS) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Cannot withdraw transfer: client is not currently awaiting transfer or transfer already accepted.";
              co_return errorResponse;
          }

          client.setTransferToOfficeId("");
          client.setProposedTransferDateToNull();
          client.setStatusEnum(constants::ClientStatus::ACTIVE);

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client transfer withdrawn successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while withdrawing client transfer.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::rejectClientTransfer(const dto::WithdrawOrRejectClientTransferDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::TRANSFER_IN_PROGRESS) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Cannot reject transfer: client is not currently awaiting transfer.";
              co_return errorResponse;
          }

          client.setTransferToOfficeId("");
          client.setProposedTransferDateToNull();
          client.setStatusEnum(constants::ClientStatus::ACTIVE);

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client transfer rejected successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while rejecting client transfer.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::acceptClientTransfer(const dto::AcceptClientTransferDto &dto, const std::string &id) {
      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {
          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::TRANSFER_IN_PROGRESS) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Cannot accept transfer: client is not currently awaiting transfer.";
              co_return errorResponse;
          }

          // Transfer client to the new office
          client.setOfficeId(client.getValueOfTransferToOfficeId());

          // Optional: Assign Staff (Loan Officer)
          if (!dto.getStaffId().empty()) {
              client.setStaffId(dto.getStaffId());
          }

          // Optional: Link to Destination Group & Reschedule Loans
          if (!dto.getDestinationId().empty()) {
              // TODO: Call Group Service API to link this client to the specified group (dto.getDestinationId())
              // TODO: Call Portfolio Service API (Loan Service) to reschedule any existing active JLG loan
              //       of the client to match the meeting frequency of the new group.
          }

          // Clear transfer tracking fields and reactivate
          client.setTransferToOfficeId("");
          client.setProposedTransferDateToNull();
          client.setStatusEnum(constants::ClientStatus::ACTIVE);

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client transfer accepted successfully.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while accepting client transfer.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::proposeAndAcceptClientTransfer(const dto::ProposeAndAcceptClientTransferDto &dto, const std::string &id) {

      auto dbClient = drogon::app().getDbClient();
      CoroMapper<drogon_model::TlCustomerDb::Client> mapper(dbClient);

      try {

          if (id.empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Client ID cannot be empty.";
              co_return errorResponse;
          }

          if (dto.getDestinationOfficeId().empty()) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_VALIDATION;
              errorResponse.error["message"] = "Destination office ID cannot be empty.";
              co_return errorResponse;
          }

          auto client = co_await mapper.findByPrimaryKey(id);

          if (client.getValueOfStatusEnum() != constants::ClientStatus::ACTIVE) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
              errorResponse.error["message"] = "Only an active client can be transferred.";
              co_return errorResponse;
          }

          // Combine propose and accept into one atomic operation
          client.setOfficeId(dto.getDestinationOfficeId());

          if (!dto.getStaffId().empty()) {
              client.setStaffId(dto.getStaffId());
          }

          if (!dto.getDestinationGroupId().empty()) {
              // TODO: Call Group Service API to link this client to the specified group (dto.getDestinationGroupId())
              // TODO: Call Portfolio Service API (Loan Service) to reschedule any existing active JLG loan
              //       of the client to match the meeting frequency of the new group.
          }

          // In case the client had any stale proposed transfer fields, clean them up
          client.setTransferToOfficeId("");
          client.setProposedTransferDateToNull();
          client.setStatusEnum(constants::ClientStatus::ACTIVE);

          auto updatedRows = co_await mapper.update(client);

          if (updatedRows == 0) {
              dto::BaseApiResponse errorResponse;
              errorResponse.success = false;
              errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
              errorResponse.error["message"] = "Client not found.";
              co_return errorResponse;
          }

          dto::BaseApiResponse response;
          response.success = true;
          response.message = "Client transfer successfully proposed and accepted.";
          response.result = client.toJson();
          co_return response;

      } catch (const DrogonDbException &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_DB_QUERY;
          errorResponse.error["message"] = "Database error while processing combined client transfer.";
          errorResponse.error["detail"] = e.base().what();
          co_return errorResponse;
      } catch (const std::exception &e) {
          dto::BaseApiResponse errorResponse;
          errorResponse.success = false;
          errorResponse.error["code"] = constants::ERR_INTERNAL;
          errorResponse.error["message"] = "Internal error.";
          errorResponse.error["detail"] = e.what();
          co_return errorResponse;
      }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::getClientAccountsOverview(const std::string &id) {

      // call portfolio and deposit account management services to return account overview from each service


  }

  drogon::Task<dto::BaseApiResponse> ClientService::getClientAddresses(const std::string &id) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientAddress> mapper(dbClient);

        try {
            if (id.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID cannot be empty.";
                co_return errorResponse;
            }

            drogon::orm::Criteria criteria(drogon_model::TlCustomerDb::ClientAddress::Cols::_client_id, drogon::orm::CompareOperator::EQ, id);
            auto addresses = co_await mapper.findBy(criteria);

            Json::Value jsonArray(Json::arrayValue);
            for (const auto &addr : addresses) {
                Json::Value jsonAddr;
                jsonAddr["id"] = addr.getValueOfId();
                jsonAddr["clientId"] = addr.getValueOfClientId();
                jsonAddr["street"] = addr.getValueOfStreet();
                jsonAddr["addressLine1"] = addr.getValueOfAddressLine1();
                jsonAddr["addressLine2"] = addr.getValueOfAddressLine2();
                jsonAddr["city"] = addr.getValueOfCity();
                jsonAddr["stateOrProvince"] = addr.getValueOfStateOrProvince();
                jsonAddr["country"] = addr.getValueOfCountry();
                jsonAddr["countryCode"] = addr.getValueOfCountryCode();
                jsonAddr["addressTypeId"] = addr.getValueOfAddressTypeId();
                jsonAddr["isActive"] = addr.getValueOfIsActive();
                jsonArray.append(jsonAddr);
            }

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client addresses fetched successfully.";
            response.result = jsonArray;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while retrieving client addresses.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }


  drogon::Task<dto::BaseApiResponse> ClientService::createClientAddress(const dto::ClientAddressDto &dto, const std::string &id) {

        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientAddress> mapper(dbClient);

        try {
            if (id.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID cannot be empty.";
                co_return errorResponse;
            }

            drogon_model::TlCustomerDb::ClientAddress newAddressMapping;
            newAddressMapping.setClientId(id);
            if (!dto.getStreet().empty()) newAddressMapping.setStreet(dto.getStreet());
            if (!dto.getAddressLine1().empty()) newAddressMapping.setAddressLine1(dto.getAddressLine1());
            if (!dto.getAddressLine2().empty()) newAddressMapping.setAddressLine2(dto.getAddressLine2());
            if (!dto.getCity().empty()) newAddressMapping.setCity(dto.getCity());
            if (!dto.getStateOrProvince().empty()) newAddressMapping.setStateOrProvince(dto.getStateOrProvince());
            if (!dto.getCountry().empty()) newAddressMapping.setCountry(dto.getCountry());
            if (!dto.getCountryCode().empty()) newAddressMapping.setCountryCode(dto.getCountryCode());
            if (!dto.getAddressTypeId().empty()) newAddressMapping.setAddressTypeId(dto.getAddressTypeId());
            
            newAddressMapping.setIsActive(true);

            auto insertedRecord = co_await mapper.insert(newAddressMapping);

            Json::Value jsonAddr;
            jsonAddr["id"] = insertedRecord.getValueOfId();
            jsonAddr["clientId"] = insertedRecord.getValueOfClientId();
            jsonAddr["street"] = insertedRecord.getValueOfStreet();
            jsonAddr["addressLine1"] = insertedRecord.getValueOfAddressLine1();
            jsonAddr["addressLine2"] = insertedRecord.getValueOfAddressLine2();
            jsonAddr["city"] = insertedRecord.getValueOfCity();
            jsonAddr["stateOrProvince"] = insertedRecord.getValueOfStateOrProvince();
            jsonAddr["country"] = insertedRecord.getValueOfCountry();
            jsonAddr["countryCode"] = insertedRecord.getValueOfCountryCode();
            jsonAddr["addressTypeId"] = insertedRecord.getValueOfAddressTypeId();
            jsonAddr["isActive"] = insertedRecord.getValueOfIsActive();

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client address successfully created.";
            response.result = jsonAddr;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while creating client address mapping.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::updateClientAddress(const dto::ClientAddressDto &dto, const std::string &id, std::string addressId) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientAddress> mapper(dbClient);

        try {
            if (id.empty() || addressId.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID and Address ID cannot be empty.";
                co_return errorResponse;
            }

            auto existingAddress = co_await mapper.findByPrimaryKey(addressId);
            
            if (existingAddress.getValueOfClientId() != id) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
                errorResponse.error["message"] = "Address does not belong to the specified client.";
                co_return errorResponse;
            }

            if (!dto.getStreet().empty()) existingAddress.setStreet(dto.getStreet());
            if (!dto.getAddressLine1().empty()) existingAddress.setAddressLine1(dto.getAddressLine1());
            if (!dto.getAddressLine2().empty()) existingAddress.setAddressLine2(dto.getAddressLine2());
            if (!dto.getCity().empty()) existingAddress.setCity(dto.getCity());
            if (!dto.getStateOrProvince().empty()) existingAddress.setStateOrProvince(dto.getStateOrProvince());
            if (!dto.getCountry().empty()) existingAddress.setCountry(dto.getCountry());
            if (!dto.getCountryCode().empty()) existingAddress.setCountryCode(dto.getCountryCode());
            if (!dto.getAddressTypeId().empty()) existingAddress.setAddressTypeId(dto.getAddressTypeId());

            auto updatedRows = co_await mapper.update(existingAddress);

            if (updatedRows == 0) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
                errorResponse.error["message"] = "Address update failed or no changes made.";
                co_return errorResponse;
            }

            Json::Value jsonAddr;
            jsonAddr["id"] = existingAddress.getValueOfId();
            jsonAddr["clientId"] = existingAddress.getValueOfClientId();
            jsonAddr["street"] = existingAddress.getValueOfStreet();
            jsonAddr["addressLine1"] = existingAddress.getValueOfAddressLine1();
            jsonAddr["addressLine2"] = existingAddress.getValueOfAddressLine2();
            jsonAddr["city"] = existingAddress.getValueOfCity();
            jsonAddr["stateOrProvince"] = existingAddress.getValueOfStateOrProvince();
            jsonAddr["country"] = existingAddress.getValueOfCountry();
            jsonAddr["countryCode"] = existingAddress.getValueOfCountryCode();
            jsonAddr["addressTypeId"] = existingAddress.getValueOfAddressTypeId();
            jsonAddr["isActive"] = existingAddress.getValueOfIsActive();

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client address successfully updated.";
            response.result = jsonAddr;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while updating client address.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::deleteClientAddress(const std::string &id, std::string addressId) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientAddress> mapper(dbClient);

        try {
            if (id.empty() || addressId.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID and Address ID cannot be empty.";
                co_return errorResponse;
            }

            auto existingAddress = co_await mapper.findByPrimaryKey(addressId);
            
            if (existingAddress.getValueOfClientId() != id) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
                errorResponse.error["message"] = "Address does not belong to the specified client.";
                co_return errorResponse;
            }

            auto deletedRows = co_await mapper.deleteByPrimaryKey(addressId);

            if (deletedRows == 0) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
                errorResponse.error["message"] = "Client address not found or already deleted.";
                co_return errorResponse;
            }

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client address successfully deleted.";
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while deleting client address.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::getClientIdentifiers(const std::string &id) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientIdentifier> mapper(dbClient);

        try {
            if (id.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID cannot be empty.";
                co_return errorResponse;
            }

            drogon::orm::Criteria criteria(drogon_model::TlCustomerDb::ClientIdentifier::Cols::_client_id, drogon::orm::CompareOperator::EQ, id);
            auto identifiers = co_await mapper.findBy(criteria);

            Json::Value jsonArray(Json::arrayValue);
            for (const auto &ident : identifiers) {
                Json::Value jsonIdent;
                jsonIdent["id"] = ident.getValueOfId();
                jsonIdent["clientId"] = ident.getValueOfClientId();
                jsonIdent["documentTypeId"] = ident.getValueOfDocumentTypeId();
                jsonIdent["documentKey"] = ident.getValueOfDocumentKey();
                jsonIdent["status"] = ident.getValueOfStatus();
                jsonIdent["active"] = ident.getValueOfActive();
                jsonIdent["description"] = ident.getValueOfDescription();
                jsonArray.append(jsonIdent);
            }

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client identifiers fetched successfully.";
            response.result = jsonArray;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while retrieving client identifiers.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::createClientIdentifier(const dto::ClientIdentifierDto &dto, const std::string &id) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientIdentifier> mapper(dbClient);

        try {
            if (id.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID cannot be empty.";
                co_return errorResponse;
            }

            drogon_model::TlCustomerDb::ClientIdentifier newIdentifier;
            newIdentifier.setClientId(id);
            
            if (!dto.getDocumentTypeId().empty()) {
                newIdentifier.setDocumentTypeId(dto.getDocumentTypeId());
            }
            if (!dto.getDocumentKey().empty()) {
                newIdentifier.setDocumentKey(dto.getDocumentKey());
            }
            if (!dto.getDescription().empty()) {
                newIdentifier.setDescription(dto.getDescription());
            }
            
            // Set default active flag
            newIdentifier.setActive(true);

            auto insertedRecord = co_await mapper.insert(newIdentifier);

            Json::Value jsonIdent;
            jsonIdent["id"] = insertedRecord.getValueOfId();
            jsonIdent["clientId"] = insertedRecord.getValueOfClientId();
            jsonIdent["documentTypeId"] = insertedRecord.getValueOfDocumentTypeId();
            jsonIdent["documentKey"] = insertedRecord.getValueOfDocumentKey();
            jsonIdent["status"] = insertedRecord.getValueOfStatus();
            jsonIdent["active"] = insertedRecord.getValueOfActive();
            jsonIdent["description"] = insertedRecord.getValueOfDescription();

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client identifier successfully created.";
            response.result = jsonIdent;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while creating client identifier.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::updateClientIdentifier(const dto::ClientIdentifierDto &dto, const std::string &id, std::string identifierId) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientIdentifier> mapper(dbClient);

        try {
            if (id.empty() || identifierId.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID and Identifier ID cannot be empty.";
                co_return errorResponse;
            }

            auto existingIdentifier = co_await mapper.findByPrimaryKey(identifierId);
            
            if (existingIdentifier.getValueOfClientId() != id) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
                errorResponse.error["message"] = "Identifier does not belong to the specified client.";
                co_return errorResponse;
            }

            if (!dto.getDocumentTypeId().empty()) {
                existingIdentifier.setDocumentTypeId(dto.getDocumentTypeId());
            }
            if (!dto.getDocumentKey().empty()) {
                existingIdentifier.setDocumentKey(dto.getDocumentKey());
            }
            if (!dto.getDescription().empty()) {
                existingIdentifier.setDescription(dto.getDescription());
            }

            auto updatedRows = co_await mapper.update(existingIdentifier);

            if (updatedRows == 0) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
                errorResponse.error["message"] = "Identifier update failed or no changes made.";
                co_return errorResponse;
            }

            Json::Value jsonIdent;
            jsonIdent["id"] = existingIdentifier.getValueOfId();
            jsonIdent["clientId"] = existingIdentifier.getValueOfClientId();
            jsonIdent["documentTypeId"] = existingIdentifier.getValueOfDocumentTypeId();
            jsonIdent["documentKey"] = existingIdentifier.getValueOfDocumentKey();
            jsonIdent["status"] = existingIdentifier.getValueOfStatus();
            jsonIdent["active"] = existingIdentifier.getValueOfActive();
            jsonIdent["description"] = existingIdentifier.getValueOfDescription();

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client identifier successfully updated.";
            response.result = jsonIdent;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while updating client identifier.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::deleteClientIdentifier(const std::string &id, std::string identifierId) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientIdentifier> mapper(dbClient);

        try {
            if (id.empty() || identifierId.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID and Identifier ID cannot be empty.";
                co_return errorResponse;
            }

            auto existingIdentifier = co_await mapper.findByPrimaryKey(identifierId);
            
            if (existingIdentifier.getValueOfClientId() != id) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
                errorResponse.error["message"] = "Identifier does not belong to the specified client.";
                co_return errorResponse;
            }

            auto deletedRows = co_await mapper.deleteByPrimaryKey(identifierId);

            if (deletedRows == 0) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
                errorResponse.error["message"] = "Client identifier not found or already deleted.";
                co_return errorResponse;
            }

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client identifier successfully deleted.";
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while deleting client identifier.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::getClientTransactions(const std::string &id) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientTransaction> mapper(dbClient);

        try {
            if (id.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID cannot be empty.";
                co_return errorResponse;
            }

            drogon::orm::Criteria criteria(drogon_model::TlCustomerDb::ClientTransaction::Cols::_client_id, drogon::orm::CompareOperator::EQ, id);
            auto transactions = co_await mapper.findBy(criteria);

            Json::Value jsonArray(Json::arrayValue);
            for (const auto &txn : transactions) {
                Json::Value jsonTxn;
                jsonTxn["id"] = txn.getValueOfId();
                jsonTxn["clientId"] = txn.getValueOfClientId();
                jsonTxn["officeId"] = txn.getValueOfOfficeId();
                jsonTxn["currencyCode"] = txn.getValueOfCurrencyCode();
                jsonTxn["paymentDetailId"] = txn.getValueOfPaymentDetailId();
                jsonTxn["isReversed"] = txn.getValueOfIsReversed();
                jsonTxn["externalId"] = txn.getValueOfExternalId();
                jsonTxn["transactionType"] = txn.getValueOfTransactionTypeEnum();
                
                if (txn.getTransactionDate()) {
                    // Safe string deserialization utilizing trantor library
                    jsonTxn["transactionDate"] = txn.getValueOfTransactionDate().toDbStringLocal();
                } else {
                    jsonTxn["transactionDate"] = Json::nullValue;
                }
                
                if (txn.getSubmittedOnDate()) {
                    jsonTxn["submittedOnDate"] = txn.getValueOfSubmittedOnDate().toDbStringLocal();
                } else {
                    jsonTxn["submittedOnDate"] = Json::nullValue;
                }
                
                jsonTxn["amount"] = txn.getValueOfAmount();
                jsonArray.append(jsonTxn);
            }

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client transactions fetched successfully.";
            response.result = jsonArray;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while retrieving client transactions.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::getClientTransactionDetails(const std::string &id, std::string transactionId) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientTransaction> mapper(dbClient);

        try {
            if (id.empty() || transactionId.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID and Transaction ID cannot be empty.";
                co_return errorResponse;
            }

            auto txn = co_await mapper.findByPrimaryKey(transactionId);

            if (txn.getValueOfClientId() != id) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
                errorResponse.error["message"] = "Transaction does not belong to the specified client.";
                co_return errorResponse;
            }

            Json::Value jsonTxn;
            jsonTxn["id"] = txn.getValueOfId();
            jsonTxn["clientId"] = txn.getValueOfClientId();
            jsonTxn["officeId"] = txn.getValueOfOfficeId();
            jsonTxn["currencyCode"] = txn.getValueOfCurrencyCode();
            jsonTxn["paymentDetailId"] = txn.getValueOfPaymentDetailId();
            jsonTxn["isReversed"] = txn.getValueOfIsReversed();
            jsonTxn["externalId"] = txn.getValueOfExternalId();
            jsonTxn["transactionType"] = txn.getValueOfTransactionTypeEnum();
            jsonTxn["amount"] = txn.getValueOfAmount();

            if (txn.getTransactionDate()) {
                jsonTxn["transactionDate"] = txn.getValueOfTransactionDate().toDbStringLocal();
            } else {
                jsonTxn["transactionDate"] = Json::nullValue;
            }

            if (txn.getSubmittedOnDate()) {
                jsonTxn["submittedOnDate"] = txn.getValueOfSubmittedOnDate().toDbStringLocal();
            } else {
                jsonTxn["submittedOnDate"] = Json::nullValue;
            }

            if (txn.getCreatedDate()) {
                jsonTxn["createdDate"] = txn.getValueOfCreatedDate().toDbStringLocal();
            } else {
                jsonTxn["createdDate"] = Json::nullValue;
            }

            jsonTxn["createdBy"] = txn.getValueOfCreatedBy();
            jsonTxn["lastModifiedBy"] = txn.getValueOfLastModifiedBy();

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client transaction details fetched successfully.";
            response.result = jsonTxn;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while retrieving client transaction details.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::addClientCharge(const dto::ClientChargeDto &dto, const std::string &id) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientCharge> mapper(dbClient);

        try {
            if (id.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID cannot be empty.";
                co_return errorResponse;
            }

            if (dto.getChargeId().empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Charge ID is required."; 
                co_return errorResponse;
            }

            drogon_model::TlCustomerDb::ClientCharge newCharge;
            newCharge.setClientId(id);
            newCharge.setChargeId(dto.getChargeId());

            if (!dto.getAmount().empty()) {
                newCharge.setAmount(dto.getAmount());
            }

            // Set initial derived amounts to zero
            newCharge.setAmountPaidDerived("0");
            newCharge.setAmountWaivedDerived("0");
            newCharge.setAmountWrittenoffDerived("0");
            newCharge.setAmountOutstandingDerived(dto.getAmount().empty() ? "0" : dto.getAmount());

            newCharge.setIsPaidDerived(false);
            newCharge.setWaived(false);
            newCharge.setIsActive(true);

            // TODO: Resolve charge metadata (isPenalty, chargeTimeEnum, chargeCalculationEnum)
            // from the Charge master service using dto.getChargeId() before persisting.

            auto insertedRecord = co_await mapper.insert(newCharge);

            Json::Value jsonCharge;
            jsonCharge["id"] = insertedRecord.getValueOfId();
            jsonCharge["clientId"] = insertedRecord.getValueOfClientId();
            jsonCharge["chargeId"] = insertedRecord.getValueOfChargeId();
            jsonCharge["amount"] = insertedRecord.getValueOfAmount();
            jsonCharge["amountPaid"] = insertedRecord.getValueOfAmountPaidDerived();
            jsonCharge["amountWaived"] = insertedRecord.getValueOfAmountWaivedDerived();
            jsonCharge["amountWrittenOff"] = insertedRecord.getValueOfAmountWrittenoffDerived();
            jsonCharge["amountOutstanding"] = insertedRecord.getValueOfAmountOutstandingDerived();
            jsonCharge["isPaid"] = insertedRecord.getValueOfIsPaidDerived();
            jsonCharge["waived"] = insertedRecord.getValueOfWaived();
            jsonCharge["isActive"] = insertedRecord.getValueOfIsActive();
            jsonCharge["isPenalty"] = insertedRecord.getValueOfIsPenalty();

            if (insertedRecord.getChargeDueDate()) {
                jsonCharge["chargeDueDate"] = insertedRecord.getValueOfChargeDueDate().toDbStringLocal();
            } else {
                jsonCharge["chargeDueDate"] = Json::nullValue;
            }

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client charge successfully added.";
            response.result = jsonCharge;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while adding client charge.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::getClientCharges(const std::string &id) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientCharge> mapper(dbClient);

        try {
            if (id.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID cannot be empty.";
                co_return errorResponse;
            }

            drogon::orm::Criteria criteria(drogon_model::TlCustomerDb::ClientCharge::Cols::_client_id, drogon::orm::CompareOperator::EQ, id);
            auto charges = co_await mapper.findBy(criteria);

            Json::Value jsonArray(Json::arrayValue);
            for (const auto &charge : charges) {
                Json::Value jsonCharge;
                jsonCharge["id"] = charge.getValueOfId();
                jsonCharge["clientId"] = charge.getValueOfClientId();
                jsonCharge["chargeId"] = charge.getValueOfChargeId();
                jsonCharge["amount"] = charge.getValueOfAmount();
                jsonCharge["amountPaid"] = charge.getValueOfAmountPaidDerived();
                jsonCharge["amountWaived"] = charge.getValueOfAmountWaivedDerived();
                jsonCharge["amountWrittenOff"] = charge.getValueOfAmountWrittenoffDerived();
                jsonCharge["amountOutstanding"] = charge.getValueOfAmountOutstandingDerived();
                jsonCharge["isPaid"] = charge.getValueOfIsPaidDerived();
                jsonCharge["waived"] = charge.getValueOfWaived();
                jsonCharge["isActive"] = charge.getValueOfIsActive();
                jsonCharge["isPenalty"] = charge.getValueOfIsPenalty();
                jsonCharge["chargeTime"] = charge.getValueOfChargeTimeEnum();
                jsonCharge["chargeCalculation"] = charge.getValueOfChargeCalculationEnum();

                if (charge.getChargeDueDate()) {
                    jsonCharge["chargeDueDate"] = charge.getValueOfChargeDueDate().toDbStringLocal();
                } else {
                    jsonCharge["chargeDueDate"] = Json::nullValue;
                }

                if (charge.getInactivatedOnDate()) {
                    jsonCharge["inactivatedOnDate"] = charge.getValueOfInactivatedOnDate().toDbStringLocal();
                } else {
                    jsonCharge["inactivatedOnDate"] = Json::nullValue;
                }

                jsonArray.append(jsonCharge);
            }

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client charges fetched successfully.";
            response.result = jsonArray;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while retrieving client charges.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::getClientChargeDetails(const std::string &id, std::string chargeId) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientCharge> mapper(dbClient);

        try {
            if (id.empty() || chargeId.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID and Charge ID cannot be empty.";
                co_return errorResponse;
            }

            auto charge = co_await mapper.findByPrimaryKey(chargeId);

            if (charge.getValueOfClientId() != id) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
                errorResponse.error["message"] = "Charge does not belong to the specified client.";
                co_return errorResponse;
            }

            Json::Value jsonCharge;
            jsonCharge["id"] = charge.getValueOfId();
            jsonCharge["clientId"] = charge.getValueOfClientId();
            jsonCharge["chargeId"] = charge.getValueOfChargeId();
            jsonCharge["amount"] = charge.getValueOfAmount();
            jsonCharge["amountPaid"] = charge.getValueOfAmountPaidDerived();
            jsonCharge["amountWaived"] = charge.getValueOfAmountWaivedDerived();
            jsonCharge["amountWrittenOff"] = charge.getValueOfAmountWrittenoffDerived();
            jsonCharge["amountOutstanding"] = charge.getValueOfAmountOutstandingDerived();
            jsonCharge["isPaid"] = charge.getValueOfIsPaidDerived();
            jsonCharge["waived"] = charge.getValueOfWaived();
            jsonCharge["isActive"] = charge.getValueOfIsActive();
            jsonCharge["isPenalty"] = charge.getValueOfIsPenalty();
            jsonCharge["chargeTime"] = charge.getValueOfChargeTimeEnum();
            jsonCharge["chargeCalculation"] = charge.getValueOfChargeCalculationEnum();

            if (charge.getChargeDueDate()) {
                jsonCharge["chargeDueDate"] = charge.getValueOfChargeDueDate().toDbStringLocal();
            } else {
                jsonCharge["chargeDueDate"] = Json::nullValue;
            }

            if (charge.getInactivatedOnDate()) {
                jsonCharge["inactivatedOnDate"] = charge.getValueOfInactivatedOnDate().toDbStringLocal();
            } else {
                jsonCharge["inactivatedOnDate"] = Json::nullValue;
            }

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client charge details fetched successfully.";
            response.result = jsonCharge;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while retrieving client charge details.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::deleteClientCharge(const std::string &id, std::string chargeId) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientCharge> mapper(dbClient);

        try {
            if (id.empty() || chargeId.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID and Charge ID cannot be empty.";
                co_return errorResponse;
            }

            auto existingCharge = co_await mapper.findByPrimaryKey(chargeId);

            if (existingCharge.getValueOfClientId() != id) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
                errorResponse.error["message"] = "Charge does not belong to the specified client.";
                co_return errorResponse;
            }

            if (existingCharge.getValueOfIsPaidDerived()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_UNSUPPORTED_OPERATION;
                errorResponse.error["message"] = "Cannot delete a charge that has already been paid."; 
                co_return errorResponse;
            }

            auto deletedRows = co_await mapper.deleteByPrimaryKey(chargeId);

            if (deletedRows == 0) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_DB_NOT_FOUND;
                errorResponse.error["message"] = "Client charge not found or already deleted.";
                co_return errorResponse;
            }

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client charge successfully deleted.";
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while deleting client charge.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::payClientCharge(const dto::PayClientChargeDto &dto, std::string id, std::string chargeId) {
        auto dbClient = drogon::app().getDbClient();

        try {
            if (id.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID cannot be empty.";
                co_return errorResponse;
            }

            if (dto.getAmount().empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Payment amount is required.";
                co_return errorResponse;
            }

            // TODO: Delegate to Portfolio/Charge Payment Service to process the actual charge payment.
            // The Portfolio Service should:
            //   1. Record the payment transaction against the client charge.
            //   2. Update amountPaidDerived and amountOutstandingDerived on the ClientCharge record.
            //   3. Set isPaidDerived = true if amountOutstandingDerived reaches zero.
            //   4. Create a ClientTransaction record for audit trail.

            Json::Value result;
            result["clientId"] = id;
            result["amount"] = dto.getAmount();
            result["transactionDate"] = dto.getTransactionDate();
            result["status"] = "pending_service_integration";

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client charge payment submitted. Pending integration with payment processing service.";
            response.result = result;
            co_return response;

        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::waiveClientCharge(const std::string &id, const std::string &chargeId) {
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<drogon_model::TlCustomerDb::ClientCharge> mapper(dbClient);

        try {
            if (id.empty()) {
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = constants::ERR_VALIDATION;
                errorResponse.error["message"] = "Client ID cannot be empty.";
                co_return errorResponse;
            }

            // Note: chargeId is expected to be passed as part of request context.
            // TODO: Retrieve chargeId from route parameter and look up the charge here.
            // The waive operation should:
            //   1. Set waived = true on the ClientCharge record.
            //   2. Move amountOutstandingDerived to amountWaivedDerived.
            //   3. Set isPaidDerived = true (charge is settled via waiver).
            //   4. Set isActive = false and record inactivatedOnDate.

            Json::Value result;
            result["clientId"] = id;
            result["resourceId"] = chargeId;
            result["status"] = "pending_service_integration";

            dto::BaseApiResponse response;
            response.success = true;
            response.message = "Client charge waiver submitted. Pending integration with charge management service.";
            response.result = result;
            co_return response;

        } catch (const DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while waiving client charge.";
            errorResponse.error["detail"] = e.base().what();
            co_return errorResponse;
        } catch (const std::exception &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_INTERNAL;
            errorResponse.error["message"] = "Internal error.";
            errorResponse.error["detail"] = e.what();
            co_return errorResponse;
        }
  }

  drogon::Task<dto::BaseApiResponse> ClientService::undoClientTransaction(const std::string &id, std::string transactionId) {


  }

}