/**
 *
 *  CustomerServicePlugin.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include "services/client/ClientService.h"
#include "services/identity/IdentityApi.h"


namespace customer::plugins {

    class CustomerServicePlugin : public drogon::Plugin<CustomerServicePlugin>
    {
    public:
        CustomerServicePlugin() = default;
        ~CustomerServicePlugin() override = default;
        /// This method must be called by drogon to initialize and start the plugin.
        /// It must be implemented by the user.
        void initAndStart(const Json::Value &config) override;

        /// This method must be called by drogon to shutdown the plugin.
        /// It must be implemented by the user.
        void shutdown() override;

        services::ClientService &getClientService() { return clientService_; }
        services::IdentityApi &getIdentityApi() { return identityApi_; }

    private:
        services::ClientService clientService_;
        services::IdentityApi identityApi_;
    };
}

