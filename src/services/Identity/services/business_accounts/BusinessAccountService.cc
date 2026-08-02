//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//
#include "BusinessAccountService.h"
#include "models/BusinessAccounts.h"
#include <drogon/drogon.h>
#include <drogon/orm/CoroMapper.h>
#include "utils/JsonUtils.h"
#include <drogon/orm/Criteria.h>

namespace turbo_ledger_identity::services {

drogon::Task<dto::BaseApiResponse> BusinessAccountService::getAll(int pageNo, int pageSize, const std::string &query) {
    auto dbClient = drogon::app().getDbClient();
    drogon::orm::CoroMapper<drogon_model::TlIdentity::BusinessAccounts> mp(dbClient);

    // 1. Build the search criteria
    drogon::orm::Criteria searchCriteria;
    if (!query.empty()) {
        std::string likeQuery = "%" + query + "%";
        searchCriteria =
            drogon::orm::Criteria(drogon_model::TlIdentity::BusinessAccounts::Cols::_business_name, drogon::orm::CompareOperator::Like, likeQuery) ||
            drogon::orm::Criteria(drogon_model::TlIdentity::BusinessAccounts::Cols::_account_id, drogon::orm::CompareOperator::Like, likeQuery) ||
            drogon::orm::Criteria(drogon_model::TlIdentity::BusinessAccounts::Cols::_contact_person_name, drogon::orm::CompareOperator::Like, likeQuery) ||
            drogon::orm::Criteria(drogon_model::TlIdentity::BusinessAccounts::Cols::_business_email, drogon::orm::CompareOperator::Like, likeQuery);
    }

    dto::BaseApiResponse response;
    try {
        // 2. Get the total count matching the criteria
        size_t totalCount = co_await mp.count(searchCriteria);

        if (totalCount == 0) {
            response.success = true;
            response.result["data"] = Json::arrayValue;
            response.result["totalCount"] = 0;
            response.result["pageNo"] = pageNo;
            response.result["pageSize"] = pageSize;
            response.result["totalPages"] = 0;
            response.result["lowerBound"] = 0;
            response.result["upperBound"] = 0;
            co_return response;
        }

        // 3. Find the paginated data
        int offset = (pageNo - 1) * pageSize;
        auto accounts = co_await mp.limit(pageSize).offset(offset).findBy(searchCriteria);

        auto totalPages = (totalCount + pageSize - 1) / pageSize;

        // 4. Build the final response
        response.success = true;
        response.result["totalCount"] = (Json::UInt64)totalCount;
        response.result["pageNo"] = pageNo;
        response.result["pageSize"] = pageSize;
        response.result["totalPages"] = (int)totalPages;
        response.result["lowerBound"] = pageSize * (pageNo - 1) + 1;
        response.result["upperBound"] = (int)totalPages == pageNo ? (Json::UInt64)totalCount  : (Json::UInt64)(pageNo * pageSize);

        Json::Value data = Json::arrayValue;
        for (const auto &account : accounts) {
            auto json = account.toJson();
            json.removeMember("subscription_model");
            json.removeMember("configuration_data");
            data.append(utils::JsonUtils::convertKeysToCamelCase(json));
        }
        response.result["data"] = data;
        response.message = "Business accounts retrieved successfully";

    } catch (const drogon::orm::DrogonDbException &e) {
        response.success = false;
        response.error["message"] = "Database error while fetching business accounts.";
        response.error["detail"] = e.base().what();
    } catch (const std::exception &e) {
        response.success = false;
        response.message = e.what();
    }
    co_return response;
}

drogon::Task<dto::BaseApiResponse> BusinessAccountService::create(const dto::BusinessAccountDto &dto) {
    dto::BaseApiResponse response;
    try {
        auto dbClient = drogon::app().getDbClient();
        drogon::orm::CoroMapper<drogon_model::TlIdentity::BusinessAccounts> mapper(dbClient);

        drogon_model::TlIdentity::BusinessAccounts account;
        account.setBusinessName(dto.getBusinessName());
        account.setAccountId(dto.getAccountId());
        account.setContactPersonName(dto.getContactPersonName());
        account.setContactPersonEmail(dto.getContactPersonEmail());
        account.setContactPersonPhoneNo(dto.getContactPersonPhoneNo());
        account.setBusinessEmail(dto.getBusinessEmail());
        account.setBusinessPhoneNo(dto.getBusinessPhoneNo());
        account.setStatus(dto.getStatus());
        account.setSubAccountEnabled(dto.isSubAccountEnabled());
        account.setRequireTwoFactorAuth(dto.isRequireTwoFactorAuth());
        account.setCountry(dto.getCountry());
        account.setCurrency(dto.getCurrency());

        if (!dto.getSubscriptionModel().isNull()) {
            Json::FastWriter writer;
            account.setSubscriptionModel(writer.write(dto.getSubscriptionModel()));
        }

        auto newAccount = co_await mapper.insert(account);

        response.success = true;
        response.message = "Business account created successfully";
        response.result = newAccount.toJson();
    } catch (const std::exception &e) {
        response.success = false;
        response.message = e.what();
    }
    co_return response;
}

drogon::Task<dto::BaseApiResponse> BusinessAccountService::update(const dto::BusinessAccountDto &dto, const std::string &id) {
    dto::BaseApiResponse response;
    try {
        auto dbClient = drogon::app().getDbClient();
        drogon::orm::CoroMapper<drogon_model::TlIdentity::BusinessAccounts> mapper(dbClient);

        auto account = co_await mapper.findByPrimaryKey(id);

        account.setBusinessName(dto.getBusinessName());
        account.setContactPersonName(dto.getContactPersonName());
        account.setContactPersonEmail(dto.getContactPersonEmail());
        account.setContactPersonPhoneNo(dto.getContactPersonPhoneNo());
        account.setBusinessEmail(dto.getBusinessEmail());
        account.setBusinessPhoneNo(dto.getBusinessPhoneNo());
        account.setStatus(dto.getStatus());
        account.setSubAccountEnabled(dto.isSubAccountEnabled());
        account.setRequireTwoFactorAuth(dto.isRequireTwoFactorAuth());
        account.setCountry(dto.getCountry());
        account.setCurrency(dto.getCurrency());

        if (!dto.getSubscriptionModel().isNull()) {
            Json::FastWriter writer;
            account.setSubscriptionModel(writer.write(dto.getSubscriptionModel()));
        }

        auto updatedAccount = co_await mapper.update(account);

        response.success = true;
        response.message = "Business account updated successfully";
        response.result = account.toJson();
    } catch (const std::exception &e) {
        response.success = false;
        response.message = e.what();
    }
    co_return response;
}

drogon::Task<dto::BaseApiResponse> BusinessAccountService::updateAccountStatus(const std::string &id, constants::StatusType status) {
    dto::BaseApiResponse response;
    try {
        auto dbClient = drogon::app().getDbClient();
        drogon::orm::CoroMapper<drogon_model::TlIdentity::BusinessAccounts> mapper(dbClient);

        auto account = co_await mapper.findByPrimaryKey(id);
        account.setStatus(static_cast<int32_t>(status));

        co_await mapper.update(account);

        response.success = true;
        response.message = "Business account status updated successfully";
    } catch (const std::exception &e) {
        response.success = false;
        response.message = e.what();
    }
    co_return response;
}

drogon::Task<dto::BaseApiResponse> BusinessAccountService::deleteAccount(const std::string &id) {
    dto::BaseApiResponse response;
    try {
        auto dbClient = drogon::app().getDbClient();
        drogon::orm::CoroMapper<drogon_model::TlIdentity::BusinessAccounts> mapper(dbClient);

        co_await mapper.deleteByPrimaryKey(id);

        response.success = true;
        response.message = "Business account deleted successfully";
    } catch (const std::exception &e) {
        response.success = false;
        response.message = e.what();
    }
    co_return response;
}

}