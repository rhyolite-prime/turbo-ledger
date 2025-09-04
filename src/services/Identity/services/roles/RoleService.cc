#include "RoleService.h"

#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>
#include "Roles.h"
#include "dto/BaseApiResponse.h"
#include "dto/ErrorCodes.h"

using namespace drogon::orm;


namespace turbo_ledger_identity::services {


    void RoleService::getRoles(
        int pageNo,
        int pageSize,
        const std::string& query,
        const std::string& tenantId,
        const std::function<void(const dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        auto mp = std::make_shared<Mapper<drogon_model::TurboLedgerIdentity::Roles>>(dbClient);

        // 1. Build the search criteria
        Criteria criteria(drogon_model::TurboLedgerIdentity::Roles::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);
        if (!query.empty())
        {
            std::string likeQuery = "%" + query + "%";

            Criteria searchCriteria =
                Criteria(drogon_model::TurboLedgerIdentity::Roles::Cols::_name, CompareOperator::Like, likeQuery) ||
                Criteria(drogon_model::TurboLedgerIdentity::Roles::Cols::_description, CompareOperator::Like, likeQuery);

            criteria = criteria && searchCriteria;
        }

        // 2. Asynchronously get the total count matching the criteria
        mp->count(criteria,
            [=](const size_t totalCount) {
                if (totalCount == 0)
                {
                    dto::BaseApiResponse response;
                    response.success = true;
                    response.result["data"] = Json::arrayValue;
                    response.result["totalCount"] = 0;
                    callback(response);
                    return;
                }

                // 3. Asynchronously find the paginated data
                int offset = (pageNo - 1) * pageSize;
                mp->limit(pageSize).offset(offset).findBy(criteria,
                    [=](const std::vector<drogon_model::TurboLedgerIdentity::Roles>& roles) {
                        // 4. Build the final response inside the callback
                        dto::BaseApiResponse response;
                        response.success = true;
                        response.result["totalCount"] = (Json::UInt64)totalCount;
                        response.result["pageNo"] = pageNo;
                        response.result["pageSize"] = pageSize;
                        response.result["totalPages"] = (int)((totalCount + pageSize - 1) / pageSize);

                        Json::Value data = Json::arrayValue;
                        for (const auto& role : roles)
                        {
                            Json::Value roleJson = role.toJson();

                            // Convert snake_case to camelCase
                            Json::Value camelCaseRole;
                            camelCaseRole["id"] = roleJson["id"];
                            camelCaseRole["name"] = roleJson["name"];
                            camelCaseRole["description"] = roleJson["description"];
                            camelCaseRole["tenantIdentifier"] = roleJson["tenant_identifier"];
                            camelCaseRole["createdAt"] = roleJson["created_at"];
                            camelCaseRole["updatedAt"] = roleJson["updated_at"];
                            camelCaseRole["permissions"] = roleJson["permissions"];

                            data.append(camelCaseRole);
                        }
                        response.result["data"] = data;
                        callback(response);
                    },
                    [callback](const DrogonDbException& e) {
                        // Handle find error
                        dto::BaseApiResponse errorResponse;
                        errorResponse.success = false;
                        errorResponse.error["message"] = "Database error while fetching users.";
                        errorResponse.error["detail"] = e.base().what();
                        callback(errorResponse);
                    }
                );
            },
            [callback](const DrogonDbException& e) {
                // Handle count error
                dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.error["code"] = ERR_DB_QUERY;
                errorResponse.error["message"] = "Database error while fetching users.";
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }



}
