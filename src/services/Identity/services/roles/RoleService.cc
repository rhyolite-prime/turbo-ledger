#include "RoleService.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>
#include "Roles.h"
#include "dto/BaseApiResponse.h"
#include "constants/ErrorCodes.h"
#include "services/audit_logs/AuditScope.h"

using namespace drogon::orm;


namespace turbo_ledger_identity::services {


    drogon::Task<dto::BaseApiResponse> RoleService::getTenantPermissions() {

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

    drogon::Task<dto::BaseApiResponse> RoleService::getHostPermissions() {

        dto::BaseApiResponse response;
        try {
            auto customConfig = drogon::app().getCustomConfig();
            if (customConfig.isMember("HostPermissions")) {
                response.success = true;
                response.result = customConfig["HostPermissions"];
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

    drogon::Task<dto::BaseApiResponse> RoleService::getAll(const dto::UserIdentityDto &identity, int pageNo, int pageSize, const std::string &query) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            CoroMapper<drogon_model::TlIdentity::Roles> mapper(dbClient);
            
            auto criteria = Criteria(drogon_model::TlIdentity::Roles::Cols::_business_id, CompareOperator::EQ, identity.business_id);
            
            if (!query.empty()) {
                criteria = criteria && (Criteria(drogon_model::TlIdentity::Roles::Cols::_name, CompareOperator::Like, "%" + query + "%") || 
                                        Criteria(drogon_model::TlIdentity::Roles::Cols::_description, CompareOperator::Like, "%" + query + "%"));
            }

            size_t totalCount = co_await mapper.count(criteria);

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

            int offset = (pageNo - 1) * pageSize;
            auto roles = co_await mapper.limit(pageSize).offset(offset).findBy(criteria);
            auto totalPages = (totalCount + pageSize - 1) / pageSize;

            response.success = true;
            response.result["totalCount"] = (Json::UInt64)totalCount;
            response.result["pageNo"] = pageNo;
            response.result["pageSize"] = pageSize;
            response.result["totalPages"] = (int)totalPages;
            response.result["lowerBound"] = pageSize * (pageNo - 1) + 1;
            response.result["upperBound"] = (int)totalPages == pageNo ? (Json::UInt64)totalCount  : (Json::UInt64)(pageNo * pageSize);

            Json::Value data = Json::arrayValue;
            for (const auto& role : roles) {
                data.append(role.toJson());
            }
            response.result["data"] = data;

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

    drogon::Task<dto::BaseApiResponse> RoleService::create(const dto::UserIdentityDto &identity, const dto::RoleDto &dto) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Roles> mapper(dbClient);
            
            drogon_model::TlIdentity::Roles newRole;
            newRole.setBusinessId(identity.business_id);
            newRole.setName(dto.getName());
            if (!dto.getDescription().empty()) {
                newRole.setDescription(dto.getDescription());
            }
            
            Json::Value permJson(Json::arrayValue);
            for (const auto& p : dto.getPermissions()) {
                permJson.append(p);
            }
            newRole.setPermissions(permJson.toStyledString());

            services::AuditScope auditScope(identity.user_id, identity.business_id, "Role", "", "CREATE");

            auto savedRole = co_await mapper.insert(newRole);
            
            auditScope.setEntityId(savedRole.toJson()["id"].asString());
            auditScope.setNewValues(savedRole.toJson());
            auditScope.commit();

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

    drogon::Task<dto::BaseApiResponse> RoleService::update(const dto::UserIdentityDto &identity, const dto::RoleDto &dto, const std::string &roleId) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Roles> mapper(dbClient);
            
            auto criteria = Criteria(drogon_model::TlIdentity::Roles::Cols::_id, CompareOperator::EQ, roleId) &&
                            Criteria(drogon_model::TlIdentity::Roles::Cols::_business_id, CompareOperator::EQ, identity.business_id);

            auto roles = co_await mapper.findBy(criteria);
            if (roles.empty()) {
                response.success = false;
                response.error["message"] = "Role not found or you don't have access.";
                co_return response;
            }

            auto role = roles.front();
            
            services::AuditScope auditScope(identity.user_id, identity.business_id, "Role", role.toJson()["id"].asString(), "UPDATE");
            auditScope.setOldValues(role.toJson());
            
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
                auditScope.setNewValues(role.toJson());
                auditScope.commit();

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

    drogon::Task<dto::BaseApiResponse> RoleService::deleteRole(const dto::UserIdentityDto &identity, const std::string &roleId) {
        dto::BaseApiResponse response;
        try {
            auto dbClient = drogon::app().getDbClient();
            drogon::orm::CoroMapper<drogon_model::TlIdentity::Roles> mapper(dbClient);
            
            auto criteria = Criteria(drogon_model::TlIdentity::Roles::Cols::_id, CompareOperator::EQ, roleId) &&
                            Criteria(drogon_model::TlIdentity::Roles::Cols::_business_id, CompareOperator::EQ, identity.business_id);
            auto roles = co_await mapper.findBy(criteria);
            if (roles.empty()) {
                response.success = false;
                response.error["message"] = "Role not found or you don't have access.";
                co_return response;
            }
            auto role = roles.front();

            services::AuditScope auditScope(identity.user_id, identity.business_id, "Role", roleId, "DELETE");
            auditScope.setOldValues(role.toJson());

            auto deletedCount = co_await mapper.deleteBy(criteria);
            if (deletedCount > 0) {
                auditScope.commit();
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
