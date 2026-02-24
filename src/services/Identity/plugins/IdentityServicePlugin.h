/**
 *
 *  IdentityServicePlugin.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include "services/users/UserService.h"
#include "services/tenants/TenantService.h"
#include "services/roles/RoleService.h"


namespace turbo_ledger_identity::plugins {

    class IdentityServicePlugin : public drogon::Plugin<IdentityServicePlugin>
    {
    public:
        IdentityServicePlugin() = default;
        /// This method must be called by drogon to initialize and start the plugin.
        /// It must be implemented by the user.
        void initAndStart(const Json::Value &config) override;

        /// This method must be called by drogon to shutdown the plugin.
        /// It must be implemented by the user.
        void shutdown() override;

        // Provide access to the service
        services::UserService& getUserService() { return userService_; }
        services::TenantService& getTenantService() { return tenantService_; }
        services::RoleService& getRoleService() { return roleService_; }


    private:
        services::UserService userService_;
        services::TenantService tenantService_;
        services::RoleService roleService_;
    };

}


