/**
 *
 *  CustomerServicePlugin.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include "services/client/ClientService.h"


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

        customer::services::ClientService &getClientService() { return clientService_; }

    private:
        customer::services::ClientService clientService_;
    };
}

