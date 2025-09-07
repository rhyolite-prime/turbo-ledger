#include "RoleService.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>
#include "Roles.h"
#include "dto/BaseApiResponse.h"
#include "dto/UpdateRoleDto.h"
#include "constants/ErrorCodes.h"

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
                            
                            // Parse permissions from string to JSON object
                            std::string permissionsStr = role.getValueOfPermissions();
                            Json::Value permissionsJson;
                            Json::Reader reader;

                            if (!permissionsStr.empty() && reader.parse(permissionsStr, permissionsJson))
                            {
                                camelCaseRole["permissions"] = permissionsJson;
                            }
                            else
                            {
                                camelCaseRole["permissions"] = Json::arrayValue;
                            }

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
                errorResponse.error["code"] = constants::ERR_DB_QUERY;
                errorResponse.error["message"] = "Database error while fetching users.";
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }


    void RoleService::createRole(
        const dto::CreateRoleDto& roleData,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        Mapper<drogon_model::TurboLedgerIdentity::Roles> mp(dbClient);

        drogon_model::TurboLedgerIdentity::Roles newRole;

        newRole.setName(roleData.getName());
        newRole.setDescription(roleData.getDescription());
        newRole.setPermissions(roleData.getPermissions());
        newRole.setTenantIdentifier(tenantId);

        mp.insert(newRole, [callback](const drogon_model::TurboLedgerIdentity::Roles& role) {
            // 5. Prepare success response
            turbo_ledger_identity::dto::BaseApiResponse successResponse;
            successResponse.success = true;
            successResponse.message = "Role created successfully";
            successResponse.result["id"] = role.getValueOfId();

            callback(successResponse);

        }, [callback](const drogon::orm::DrogonDbException& e) {
            // 6. Handle database errors
            // C++
            turbo_ledger_identity::dto::BaseApiResponse errorResponse;
            errorResponse.success = false;
            errorResponse.message = "Database error while creating role";
            errorResponse.error["code"] = constants::ERR_DB_QUERY;
            callback(errorResponse);

        });
    }


    void RoleService::updateRole(
        const dto::UpdateRoleDto& roleData,
        const std::string& tenantId,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback)
    {
        auto dbClient = drogon::app().getDbClient();
        auto mp = std::make_shared<Mapper<drogon_model::TurboLedgerIdentity::Roles>>(dbClient);

        Criteria criteria = Criteria(drogon_model::TurboLedgerIdentity::Roles::Cols::_id, CompareOperator::EQ, roleData.getId()) &&
                            Criteria(drogon_model::TurboLedgerIdentity::Roles::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);

        mp->findOne(criteria,
            [mp, roleData, callback](drogon_model::TurboLedgerIdentity::Roles role) {
                if (!roleData.getName().empty()) role.setName(roleData.getName());
                if (!roleData.getDescription().empty()) role.setDescription(roleData.getDescription());

                role.setPermissions(roleData.getPermissions());

                mp->update(role, [callback](const size_t count) {
                    turbo_ledger_identity::dto::BaseApiResponse response;
                    response.success = true;
                    response.message = "Role updated successfully";
                    callback(response);
                },
                [callback](const DrogonDbException& e) {
                    turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                    errorResponse.success = false;
                    errorResponse.message = "Failed to update role";
                    errorResponse.error["code"] = constants::ERR_DB_QUERY;
                    errorResponse.error["detail"] = e.base().what();
                    callback(errorResponse);
                });
            },
            [callback](const DrogonDbException& e) {
                turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.message = "Role not found";
                errorResponse.error["code"] = constants::ERR_RESOURCE_NOT_FOUND;
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }


    void RoleService::deleteRole(
            const std::string& roleId,
            const std::string& tenantId,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        ) {

        auto dbClient = drogon::app().getDbClient();
        Mapper<drogon_model::TurboLedgerIdentity::Roles> mp(dbClient);

        // Create criteria to find the user with specified ID in the tenant
        Criteria criteria = Criteria(drogon_model::TurboLedgerIdentity::Roles::Cols::_id, CompareOperator::EQ, roleId) &&
                            Criteria(drogon_model::TurboLedgerIdentity::Roles::Cols::_tenant_identifier, CompareOperator::EQ, tenantId);

        // First verify the user exists
        mp.findOne(criteria,
            [=](const drogon_model::TurboLedgerIdentity::Roles& role) {
                // User found, proceed with deletion
                Mapper<drogon_model::TurboLedgerIdentity::Roles> deleteMp(dbClient);
                deleteMp.deleteBy(criteria,
                    [=](const size_t count) {
                        if (count > 0) {
                            // Successfully deleted
                            turbo_ledger_identity::dto::BaseApiResponse response;
                            response.success = true;
                            response.message = "Role deleted successfully";
                            callback(response);
                        } else {
                            // No rows were deleted (shouldn't happen if we found the user)
                            turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                            errorResponse.success = false;
                            errorResponse.message = "Failed to delete role";
                            errorResponse.error["code"] = constants::ERR_DB_QUERY;
                            callback(errorResponse);
                        }
                    },
                    [=](const DrogonDbException& e) {
                        // Error during deletion
                        turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                        errorResponse.success = false;
                        errorResponse.message = "Failed to delete role";
                        errorResponse.error["code"] = constants::ERR_DB_QUERY;
                        errorResponse.error["detail"] = e.base().what();
                        callback(errorResponse);
                    }
                );
            },
            [=](const DrogonDbException& e) {
                // User not found
                turbo_ledger_identity::dto::BaseApiResponse errorResponse;
                errorResponse.success = false;
                errorResponse.message = "Role not found";
                errorResponse.error["code"] = constants::ERR_RESOURCE_NOT_FOUND;
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }


}
