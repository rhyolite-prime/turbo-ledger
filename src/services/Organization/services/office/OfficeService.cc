//
// Created by Emmanuel Addo-Odame on 06/04/2026.
//

#include "OfficeService.h"

#include "models/Office.h"
#include "constants/ErrorCodes.h"
#include "dto/BaseApiResponse.h"
#include "utils/DateUtils.h"
#include <string>

using namespace drogon::orm;
using Office = drogon_model::TlOrganizationDb::Office;
using DateUtils = organization::utils::DateUtils;

namespace organization::services {

    drogon::Task<dto::BaseApiResponse> OfficeService::getAll(int pageNo, int pageSize, const std::string &query) {

        auto dbClient = drogon::app().getDbClient();
        CoroMapper<Office> mapper(dbClient);

        Criteria searchCriteria;

        if (!query.empty()) {
            std::string likeQuery = "%" + query + "%";
            searchCriteria = (Criteria(Office::Cols::_name, CompareOperator::Like, likeQuery) ||
                             Criteria(Office::Cols::_external_id, CompareOperator::Like, likeQuery));
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
            auto result = co_await mapper.orderBy(Office::Cols::_opening_date, SortOrder::DESC)
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
            response.result["lowerBound"] = (Json::UInt64)(pageSize * (pageNo - 1) + 1);
            response.result["upperBound"] = (int)totalPages == pageNo ? (Json::UInt64)totalCount : (Json::UInt64)(pageNo * pageSize);

            Json::Value data = Json::arrayValue;
            for (const auto &office : result) {
                Json::Value officeJson;

                officeJson["id"] = office.getValueOfId();
                officeJson["parentId"] = office.getValueOfParentId();
                officeJson["externalId"] = office.getValueOfExternalId();
                officeJson["name"] = office.getValueOfName();
                officeJson["openingDate"] = office.getValueOfOpeningDate().toDbStringLocal().substr(0, 10); // Format as YYYY-MM-DD

                data.append(officeJson);
            }
            response.result["data"] = data;
            co_return response;

        } catch (const drogon::orm::DrogonDbException &e) {
            dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            errorResponse.error["message"] = "Database error while fetching offices.";
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

    drogon::Task<dto::BaseApiResponse> OfficeService::createAsync(const dto::OfficeDto &dto) {

        dto::BaseApiResponse response;
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<Office> mapper(dbClient);

        try {
            Office office;
            if (!dto.getParentId().empty()) {
                office.setParentId(dto.getParentId());
            }
            office.setExternalId(dto.getExternalId());
            office.setName(dto.getName());
            office.setOpeningDate(DateUtils::stringToDate(dto.getOpeningDate()));

            auto savedOffice = co_await mapper.insert(office);

            response.success = true;
            response.result = savedOffice.toJson();
            response.message = "Office created successfully";
        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.message = "Database error: " + std::string(e.base().what());
        } catch (const std::exception &e) {
            response.success = false;
            response.message = "An error occurred: " + std::string(e.what());
        }

        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> OfficeService::updateAsync(const dto::OfficeDto &dto, const std::string &id) {

        dto::BaseApiResponse response;
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<Office> mapper(dbClient);

        try {
            auto office = co_await mapper.findByPrimaryKey(id);
            
            office.setParentId(dto.getParentId());
            
            office.setExternalId(dto.getExternalId());
            office.setName(dto.getName());
            office.setOpeningDate(DateUtils::stringToDate(dto.getOpeningDate()));

            co_await mapper.update(office);

            response.success = true;
            response.message = "Office updated successfully";
            response.result = office.toJson();
        } catch (const drogon::orm::UnexpectedRows &e) {
            response.success = false;
            response.message = "Office not found";
        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.message = "Database error: " + std::string(e.base().what());
        } catch (const std::exception &e) {
            response.success = false;
            response.message = "An error occurred: " + std::string(e.what());
        }

        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> OfficeService::getOfficeDetails(const std::string &id) {
        dto::BaseApiResponse response;
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<Office> mapper(dbClient);

        try {
            auto office = co_await mapper.findByPrimaryKey(id);
            response.success = true;
            response.result = office.toJson();
        } catch (const drogon::orm::UnexpectedRows &e) {
            response.success = false;
            response.message = "Office not found";
        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.message = "Database error: " + std::string(e.base().what());
        } catch (const std::exception &e) {
            response.success = false;
            response.message = "An error occurred: " + std::string(e.what());
        }

        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> OfficeService::deleteOffice(const std::string &id) {
        dto::BaseApiResponse response;
        auto dbClient = drogon::app().getDbClient();
        CoroMapper<Office> mapper(dbClient);

        try {
            co_await mapper.deleteByPrimaryKey(id);
            response.success = true;
            response.message = "Office deleted successfully";
        } catch (const drogon::orm::UnexpectedRows &e) {
            response.success = false;
            response.message = "Office not found";
        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.message = "Database error: " + std::string(e.base().what());
        } catch (const std::exception &e) {
            response.success = false;
            response.message = "An error occurred: " + std::string(e.what());
        }

        co_return response;
    }


}


