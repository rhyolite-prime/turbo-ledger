#include <drogon/HttpAppFramework.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>
#include "TenantService.h"
#include "Tenants.h"
#include "dto/BaseApiResponse.h"
#include "dto/CreateTenantDto.h"
#include "dto/ErrorCodes.h"

using namespace drogon::orm;

namespace turbo_ledger_identity::services {
    void TenantService::getTenants(
        int pageNo,
        int pageSize,
        const std::string& query,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
    ) {
        auto dbClient = drogon::app().getDbClient();
        auto mp = std::make_shared<Mapper<drogon_model::TurboLedgerIdentity::Tenants>>(dbClient);

        // Initialize search criteria
        Criteria searchCriteria;

        // Build the search criteria if a query is provided
        if (!query.empty()) {
            std::string likeQuery = "%" + query + "%";

            searchCriteria =
                Criteria(drogon_model::TurboLedgerIdentity::Tenants::Cols::_name, CompareOperator::Like, likeQuery) ||
                Criteria(drogon_model::TurboLedgerIdentity::Tenants::Cols::_identifier, CompareOperator::Like, likeQuery) ||
                Criteria(drogon_model::TurboLedgerIdentity::Tenants::Cols::_email, CompareOperator::Like, likeQuery) ||
                Criteria(drogon_model::TurboLedgerIdentity::Tenants::Cols::_phone_number, CompareOperator::Like, likeQuery);
        }

        // Count total records matching the criteria
        mp->count(searchCriteria,
            [=](const size_t totalCount) {
                if (totalCount == 0) {
                    dto::BaseApiResponse response;
                    response.success = true;
                    response.result["data"] = Json::arrayValue;
                    response.result["totalCount"] = 0;
                    callback(response);
                    return;
                }

                // Asynchronously find the paginated data
                int offset = (pageNo - 1) * pageSize;
                mp->limit(pageSize).offset(offset).findBy(searchCriteria,
                    [=](const std::vector<drogon_model::TurboLedgerIdentity::Tenants>& tenants) {
                        // Build the final response inside the callback
                        dto::BaseApiResponse response;
                        response.success = true;
                        response.result["totalCount"] = (Json::UInt64)totalCount;
                        response.result["pageNo"] = pageNo;
                        response.result["pageSize"] = pageSize;
                        response.result["totalPages"] = (int)((totalCount + pageSize - 1) / pageSize);

                        Json::Value data = Json::arrayValue;
                        for (const auto& tenant : tenants) {
                            Json::Value tenantJson = tenant.toJson();

                            // Convert snake_case to camelCase
                            Json::Value camelCaseTenant;
                            camelCaseTenant["id"] = tenantJson["id"];
                            camelCaseTenant["identifier"] = tenantJson["identifier"];
                            camelCaseTenant["name"] = tenantJson["name"];
                            camelCaseTenant["email"] = tenantJson["email"];
                            camelCaseTenant["phoneNumber"] = tenantJson["phone_number"];
                            camelCaseTenant["connectionString"] = tenantJson["connection_string"];
                            camelCaseTenant["isActive"] = tenantJson["is_active"];
                            camelCaseTenant["createdAt"] = tenantJson["created_at"];
                            camelCaseTenant["updatedAt"] = tenantJson["updated_at"];

                            data.append(camelCaseTenant);
                        }
                        response.result["data"] = data;
                        callback(response);
                    },
                    [callback](const DrogonDbException& e) {
                        // Handle find error
                        dto::BaseApiResponse errorResponse;
                        errorResponse.success = false;
                        errorResponse.error["message"] = "Database error while fetching tenants.";
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
                errorResponse.error["message"] = "Database error while fetching tenants.";
                errorResponse.error["detail"] = e.base().what();
                callback(errorResponse);
            }
        );
    }


    void TenantService::createTenant(
           const dto::CreateTenantDto& tenantData,
           const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
       ) {
        // Get database client
        auto dbClient = drogon::app().getDbClient();
        auto tenantMapper = std::make_shared<Mapper<drogon_model::TurboLedgerIdentity::Tenants>>(dbClient);

        // First check if a tenant with the same identifier already exists
        Criteria criteria(drogon_model::TurboLedgerIdentity::Tenants::Cols::_identifier,CompareOperator::EQ,tenantData.getIdentifier());

        tenantMapper->findBy(criteria,
            [=](const std::vector<drogon_model::TurboLedgerIdentity::Tenants>& tenants) {
                if (!tenants.empty()) {
                    // Tenant with this identifier already exists
                    dto::BaseApiResponse response;
                    response.success = false;
                    response.error["code"] = ERR_DUPLICATE_RESOURCE;
                    response.error["message"] = "A tenant with this identifier already exists.";
                    callback(response);
                    return;
                }

                // Create a new tenant object
                drogon_model::TurboLedgerIdentity::Tenants newTenant;
                newTenant.setIdentifier(tenantData.getIdentifier());
                newTenant.setName(tenantData.getName());
                newTenant.setEmail(tenantData.getEmail());
                newTenant.setPhoneNumber(tenantData.getPhoneNumber());
                newTenant.setConnectionString(tenantData.getConnectionString());
                newTenant.setIsActive(tenantData.isActive());

                // Insert the new tenant into the database
                tenantMapper->insert(newTenant,
                    [=](const drogon_model::TurboLedgerIdentity::Tenants& tenant) {
                        // Tenant created successfully
                        dto::BaseApiResponse response;
                        response.success = true;
                        response.message = "Tenant created successfully.";
                        response.result["id"] = tenant.getValueOfId(); // Include the generated
                        callback(response);
                    },
                    [=](const DrogonDbException& e) {
                        // Error inserting tenant
                        dto::BaseApiResponse response;
                        response.success = false;
                        response.error["code"] = ERR_DB_QUERY;
                        response.error["message"] = "Error creating tenant.";
                        response.error["detail"] = e.base().what();
                        callback(response);
                    }
                );
            },
            [=](const DrogonDbException& e) {
                // Error checking for existing tenant
                dto::BaseApiResponse response;
                response.success = false;
                response.error["code"] = ERR_DB_QUERY;
                response.error["message"] = "Error checking for existing tenant.";
                response.error["detail"] = e.base().what();
                callback(response);
            }
        );
    }


    void TenantService::updateTenant(
        const dto::UpdateTenantDto& tenantData,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
    ) {
        // Get database client
        auto dbClient = drogon::app().getDbClient();
        auto tenantMapper = std::make_shared<Mapper<drogon_model::TurboLedgerIdentity::Tenants>>(dbClient);

        // First, check if the tenant exists
        tenantMapper->findByPrimaryKey(tenantData.getId(),
            [=](const drogon_model::TurboLedgerIdentity::Tenants& tenant) {
                // Tenant found, update its properties
                auto updatedTenant = tenant;

                updatedTenant.setName(tenantData.getName());
                updatedTenant.setEmail(tenantData.getEmail());
                updatedTenant.setPhoneNumber(tenantData.getPhoneNumber());
                updatedTenant.setIsActive(tenantData.isActive());

                // Update the tenant in the database
                tenantMapper->update(updatedTenant,
                    [=](const size_t count) {
                        // Tenant updated successfully
                        dto::BaseApiResponse response;
                        response.success = true;
                        response.message = "Tenant updated successfully.";
                        callback(response);
                    },
                    [=](const DrogonDbException& e) {
                        // Error updating tenant
                        dto::BaseApiResponse response;
                        response.success = false;
                        response.error["code"] = ERR_DB_QUERY;
                        response.error["message"] = "Error updating tenant.";
                        response.error["detail"] = e.base().what();
                        callback(response);
                    }
                );
            },
            [=](const DrogonDbException& e) {
                // Error finding tenant
                dto::BaseApiResponse response;
                response.success = false;
                response.error["code"] = ERR_RESOURCE_NOT_FOUND;
                response.error["message"] = "Tenant not found.";
                response.error["detail"] = e.base().what();
                callback(response);
            }
        );
    }

    void TenantService::updateConnectionString(
        const std::string& id,
        const std::string& connectionString,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
    ) {
        // Get database client
        auto dbClient = drogon::app().getDbClient();
        auto tenantMapper = std::make_shared<Mapper<drogon_model::TurboLedgerIdentity::Tenants>>(dbClient);

        // First, check if the tenant exists
        tenantMapper->findByPrimaryKey(id,
            [=](const drogon_model::TurboLedgerIdentity::Tenants& tenant) {
                // Tenant found, update its connection string
                auto updatedTenant = tenant;
                updatedTenant.setConnectionString(connectionString);

                // Update the tenant in the database
                tenantMapper->update(updatedTenant,
                    [=](const size_t count) {
                        // Tenant updated successfully
                        dto::BaseApiResponse response;
                        response.success = true;
                        response.message = "Connection string updated successfully.";
                        callback(response);
                    },
                    [=](const DrogonDbException& e) {
                        // Error updating tenant
                        dto::BaseApiResponse response;
                        response.success = false;
                        response.error["code"] = ERR_DB_QUERY;
                        response.error["message"] = "Error updating connection string.";
                        response.error["detail"] = e.base().what();
                        callback(response);
                    }
                );
            },
            [=](const DrogonDbException& e) {
                // Error finding tenant
                dto::BaseApiResponse response;
                response.success = false;
                response.error["code"] = ERR_RESOURCE_NOT_FOUND;
                response.error["message"] = "Tenant not found.";
                response.error["detail"] = e.base().what();
                callback(response);
            }
        );
    }

    void TenantService::activateTenantAccount(
        const std::string& id,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
    ) {
        // Get database client
        auto dbClient = drogon::app().getDbClient();
        auto tenantMapper = std::make_shared<Mapper<drogon_model::TurboLedgerIdentity::Tenants>>(dbClient);

        // First, check if the tenant exists
        tenantMapper->findByPrimaryKey(id,
            [=](const drogon_model::TurboLedgerIdentity::Tenants& tenant) {
                // Tenant found, check if it's already active
                if (tenant.getValueOfIsActive()) {
                    // Tenant is already active
                    dto::BaseApiResponse response;
                    response.success = true;
                    response.message = "Tenant account is already active.";
                    callback(response);
                    return;
                }

                // Update tenant to set is_active to true
                auto updatedTenant = tenant;
                updatedTenant.setIsActive(true);

                // Update the tenant in the database
                tenantMapper->update(updatedTenant,
                    [=](const size_t count) {
                        // Tenant activated successfully
                        dto::BaseApiResponse response;
                        response.success = true;
                        response.message = "Tenant account activated successfully.";
                        callback(response);
                    },
                    [=](const DrogonDbException& e) {
                        // Error updating tenant
                        dto::BaseApiResponse response;
                        response.success = false;
                        response.error["code"] = ERR_DB_QUERY;
                        response.error["message"] = "Error activating tenant account.";
                        response.error["detail"] = e.base().what();
                        callback(response);
                    }
                );
            },
            [=](const DrogonDbException& e) {
                // Error finding tenant
                dto::BaseApiResponse response;
                response.success = false;
                response.error["code"] = ERR_RESOURCE_NOT_FOUND;
                response.error["message"] = "Tenant not found.";
                response.error["detail"] = e.base().what();
                callback(response);
            }
        );
    }

    void TenantService::deactivateTenantAccount(
        const std::string& id,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
    ) {
        // Get database client
        auto dbClient = drogon::app().getDbClient();
        auto tenantMapper = std::make_shared<Mapper<drogon_model::TurboLedgerIdentity::Tenants>>(dbClient);

        // First, check if the tenant exists
        tenantMapper->findByPrimaryKey(id,
            [=](const drogon_model::TurboLedgerIdentity::Tenants& tenant) {
                // Tenant found, check if it's already inactive
                if (!tenant.getValueOfIsActive()) {
                    // Tenant is already inactive
                    dto::BaseApiResponse response;
                    response.success = true;
                    response.message = "Tenant account is already inactive.";
                    callback(response);
                    return;
                }

                // Update tenant to set is_active to false
                auto updatedTenant = tenant;
                updatedTenant.setIsActive(false);

                // Update the tenant in the database
                tenantMapper->update(updatedTenant,
                    [=](const size_t count) {
                        // Tenant deactivated successfully
                        dto::BaseApiResponse response;
                        response.success = true;
                        response.message = "Tenant account deactivated successfully.";
                        callback(response);
                    },
                    [=](const DrogonDbException& e) {
                        // Error updating tenant
                        dto::BaseApiResponse response;
                        response.success = false;
                        response.error["code"] = ERR_DB_QUERY;
                        response.error["message"] = "Error deactivating tenant account.";
                        response.error["detail"] = e.base().what();
                        callback(response);
                    }
                );
            },
            [=](const DrogonDbException& e) {
                // Error finding tenant
                dto::BaseApiResponse response;
                response.success = false;
                response.error["code"] = ERR_RESOURCE_NOT_FOUND;
                response.error["message"] = "Tenant not found.";
                response.error["detail"] = e.base().what();
                callback(response);
            }
        );
    }

    void TenantService::deleteTenant(
        const std::string& id,
        const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
    ) {
        // Get database client
        auto dbClient = drogon::app().getDbClient();
        auto tenantMapper = std::make_shared<Mapper<drogon_model::TurboLedgerIdentity::Tenants>>(dbClient);

        // First, check if the tenant exists
        tenantMapper->findByPrimaryKey(id,
            [=](const drogon_model::TurboLedgerIdentity::Tenants& tenant) {
                // Tenant found, proceed with deletion
                tenantMapper->deleteByPrimaryKey(id,
                    [=](const size_t count) {
                        if (count > 0) {
                            // Tenant deleted successfully
                            dto::BaseApiResponse response;
                            response.success = true;
                            response.message = "Tenant deleted successfully.";
                            callback(response);
                        } else {
                            // No tenant was deleted (should not happen if tenant was found)
                            dto::BaseApiResponse response;
                            response.success = false;
                            response.error["code"] = ERR_DB_QUERY;
                            response.error["message"] = "Failed to delete tenant.";
                            callback(response);
                        }
                    },
                    [=](const DrogonDbException& e) {
                        // Error deleting tenant
                        dto::BaseApiResponse response;
                        response.success = false;
                        response.error["code"] = ERR_DB_QUERY;
                        response.error["message"] = "Error deleting tenant.";
                        response.error["detail"] = e.base().what();
                        callback(response);
                    }
                );
            },
            [=](const DrogonDbException& e) {
                // Error finding tenant or tenant doesn't exist
                dto::BaseApiResponse response;
                response.success = false;
                response.error["code"] = ERR_RESOURCE_NOT_FOUND;
                response.error["message"] = "Tenant not found.";
                response.error["detail"] = e.base().what();
                callback(response);
            }
        );
    }
}

