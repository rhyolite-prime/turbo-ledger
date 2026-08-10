/**
 *
 *  AccountingServicePlugin.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include "services/accounts/GlAccountService.h"
#include "services/identity/IdentityApi.h"
#include "services/journal/JournalService.h"
#include "services/redis/RedisCacheManager.h"


namespace turbo_ledger_accounting::plugins {

    class AccountingServicePlugin : public drogon::Plugin<AccountingServicePlugin>
    {
    public:
        AccountingServicePlugin() = default;
        /// This method must be called by drogon to initialize and start the plugin.
        /// It must be implemented by the user.
        void initAndStart(const Json::Value &config) override;

        /// This method must be called by drogon to shutdown the plugin.
        /// It must be implemented by the user.
        void shutdown() override;

        // Provide access to the service
        services::RedisCacheManager& getRedisCacheManager() { return redisCacheManager_; }
        services::GlAccountService& getGlAccountService() { return glAccountService_; }
        services::JournalService& getJournalService() { return journalService_; }
        services::IdentityApi& getIdentityApi() { return identityApi_; }

    private:
        services::RedisCacheManager redisCacheManager_;
        services::GlAccountService glAccountService_;
        services::JournalService journalService_;
        services::IdentityApi identityApi_;

    };

}


