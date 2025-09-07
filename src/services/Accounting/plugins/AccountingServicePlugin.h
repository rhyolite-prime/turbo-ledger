/**
 *
 *  AccountingServicePlugin.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>


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
    //services::AccountService& getAccountService() { return accountService_; }
    //services::JournalService& getJournalService() { return journalService_; }

private:
    //services::AccountService accountService_;
    //services::JournalService journalService_;

};

