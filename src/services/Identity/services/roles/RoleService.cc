#include "RoleService.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>
#include "Roles.h"
#include "dto/BaseApiResponse.h"
#include "constants/ErrorCodes.h"

using namespace drogon::orm;


namespace turbo_ledger_identity::services {


    drogon::Task<dto::BaseApiResponse> RoleService::getAllPermissions() {

        dto::BaseApiResponse response;
        try {
            auto customConfig = drogon::app().getCustomConfig();
            if (customConfig.isMember("TenantPermissions")) {
                response.success = true;
                response.result = customConfig["TenantPermissions"];
            } else {
                response.success = false;
                response.error["message"] = "Permissions not found in configuration.";
            }
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Error retrieving permissions.";
            response.error["detail"] = e.what();
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> RoleService::getAll(const std::string &businessId, int pageNo, int pageSize, const std::string &query) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Roles> mapper(dbClient);
            
            auto criteria = Criteria(drogon_model::TlIdentity::Roles::Cols::_business_id, CompareOperator::EQ, businessId);
            
            if (!query.empty()) {
                criteria = criteria && (Criteria(drogon_model::TlIdentity::Roles::Cols::_name, CompareOperator::Like, "%" + query + "%") || 
                                        Criteria(drogon_model::TlIdentity::Roles::Cols::_description, CompareOperator::Like, "%" + query + "%"));
            }

            auto roles = co_await mapper.paginate(pageNo, pageSize).findBy(criteria);
            
            Json::Value rolesJson = Json::arrayValue;
            for (const auto& role : roles) {
                rolesJson.append(role.toJson());
            }

            response.success = true;
            response.result = rolesJson;

        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.error["message"] = "Database error retrieving roles.";
            response.error["detail"] = e.base().what();
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Unknown error retrieving roles.";
            response.error["detail"] = e.what();
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> RoleService::create(const std::string &businessId, const dto::RoleDto &dto) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Roles> mapper(dbClient);
            
            drogon_model::TlIdentity::Roles newRole;
            newRole.setBusinessId(businessId);
            newRole.setName(dto.getName());
            if (!dto.getDescription().empty()) {
                newRole.setDescription(dto.getDescription());
            }
            
            Json::Value permJson(Json::arrayValue);
            for (const auto& p : dto.getPermissions()) {
                permJson.append(p);
            }
            newRole.setPermissions(permJson.toStyledString());

            auto savedRole = co_await mapper.insert(newRole);
            response.success = true;
            response.result = savedRole.toJson();

        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.error["message"] = "Database error creating role.";
            response.error["detail"] = e.base().what();
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Unknown error creating role.";
            response.error["detail"] = e.what();
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> RoleService::update(const std::string &businessId, const dto::RoleDto &dto, const std::string &roleId) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Roles> mapper(dbClient);
            
            auto criteria = Criteria(drogon_model::TlIdentity::Roles::Cols::_id, CompareOperator::EQ, roleId) &&
                            Criteria(drogon_model::TlIdentity::Roles::Cols::_business_id, CompareOperator::EQ, businessId);

            auto roles = co_await mapper.findBy(criteria);
            if (roles.empty()) {
                response.success = false;
                response.error["message"] = "Role not found or you don't have access.";
                co_return response;
            }

            auto role = roles.front();
            
            if (!dto.getName().empty()) {
                role.setName(dto.getName());
            }
            if (!dto.getDescription().empty()) {
                role.setDescription(dto.getDescription());
            }
            
            if (!dto.getPermissions().empty()) {
                Json::Value permJson(Json::arrayValue);
                for (const auto& p : dto.getPermissions()) {
                    permJson.append(p);
                }
                role.setPermissions(permJson.toStyledString());
            }

            auto updatedCount = co_await mapper.update(role);
            if (updatedCount > 0) {
                response.success = true;
                response.result = role.toJson();
            } else {
                response.success = false;
                response.error["message"] = "Failed to update role.";
            }

        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.error["message"] = "Database error updating role.";
            response.error["detail"] = e.base().what();
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Unknown error updating role.";
            response.error["detail"] = e.what();
        }
        co_return response;
    }

    drogon::Task<dto::BaseApiResponse> RoleService::deleteRole(const std::string &businessId, const std::string &roleId) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Roles> mapper(dbClient);
            
            auto criteria = Criteria(drogon_model::TlIdentity::Roles::Cols::_id, CompareOperator::EQ, roleId) &&
                            Criteria(drogon_model::TlIdentity::Roles::Cols::_business_id, CompareOperator::EQ, businessId);

            auto deletedCount = co_await mapper.deleteBy(criteria);
            if (deletedCount > 0) {
                response.success = true;
                response.message = "Role deleted successfully.";
            } else {
                response.success = false;
                response.error["message"] = "Role not found or you don't have access.";
            }

        } catch (const drogon::orm::DrogonDbException &e) {
            response.success = false;
            response.error["message"] = "Database error deleting role. It might be in use.";
            response.error["detail"] = e.base().what();
        } catch (const std::exception &e) {
            response.success = false;
            response.error["message"] = "Unknown error deleting role.";
            response.error["detail"] = e.what();
        }
        co_return response;
    }

}
