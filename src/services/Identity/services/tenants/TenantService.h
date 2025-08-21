#pragma once
#include "dto/BaseApiResponse.h"
#include "dto/UpdateTenantDto.h"
#include "dto/CreateTenantDto.h"

#ifndef TENANTSERVICE_H
#define TENANTSERVICE_H


namespace turbo_ledger_identity::services {

    class TenantService {

    public:

        /**
         * @param pageNo The page number (0-based).
         * @param pageSize The number of users per page.
         * @param query Optional search query to filter users.
         * @param callback The callback function to handle the response.
         */
        void getTenants(
            int pageNo,
            int pageSize,
            const std::string& query,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void createTenant(
           const dto::CreateTenantDto& tenantData,
           const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
       );

        void updateTenant(
            const dto::UpdateTenantDto& tenantData,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void updateConnectionString(
            const std::string& id,
            const std::string& connectionString,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void activateTenantAccount(
            const std::string& id,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void deactivateTenantAccount(
            const std::string& id,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );

        void deleteTenant(
            const std::string& id,
            const std::function<void(const turbo_ledger_identity::dto::BaseApiResponse&)>& callback
        );



    };

}


#endif //TENANTSERVICE_H
