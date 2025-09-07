/**
 *
 *  AccountingServicePlugin.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include "services/accounts/GlAccountService.h"
#include "services/journal/JournalService.h"


namespace turbo_ledger_accounting::plugins {

    class AccountingServicePlugin : public drogon::Plugin<AccountingServicePlugin>
    {
    public:
        AccountingServicePlugin() {}
        /// This method must be called by drogon to initialize and start the plugin.
        /// It must be implemented by the user.
        void initAndStart(const Json::Value &config) override;

        /// This method must be called by drogon to shutdown the plugin.
        /// It must be implemented by the user.
        void shutdown() override;

        // Provide access to the service
        services::GlAccountService& getGlAccountService() { return glAccountService_; }
        services::JournalService& getJournalService() { return journalService_; }

    private:
        services::GlAccountService glAccountService_;
        services::JournalService journalService_;

    };

}


