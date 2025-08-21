/**
 *
 *  IdentityServicePlugin.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include "services/users/UserService.h"
#include "services/tenants/TenantService.h"

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
        turbo_ledger_identity::services::UserService& getUserService() { return userService_; }
        turbo_ledger_identity::services::TenantService& getTenantService() { return tenantService_; }

    private:
        turbo_ledger_identity::services::UserService userService_;
        turbo_ledger_identity::services::TenantService tenantService_;
    };

}


