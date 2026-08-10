/**
 *
 *  IdentityServicePlugin.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include "services/users/UserService.h"
#include "services/business_accounts/BusinessAccountService.h"
#include "services/roles/RoleService.h"
#include "services/api_keys/ApiKeyService.h"
#include "services/redis/RedisCacheManager.h"


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
        services::RedisCacheManager &getRedisCacheManager() { return redisCacheService_; }
        services::BusinessAccountService& getBusinessAccountService() { return businessAccountService_; }
        services::RoleService& getRoleService() { return roleService_; }
        services::ApiKeyService& getApiKeyService() { return apiKeyService_; }


    private:
        services::UserService userService_;
        services::RedisCacheManager redisCacheService_;
        services::BusinessAccountService businessAccountService_;
        services::RoleService roleService_;
        services::ApiKeyService apiKeyService_;
    };

}


