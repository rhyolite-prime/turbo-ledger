/**
 *
 *  OrganizationServicePlugin.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>

#include "services/office/OfficeService.h"

namespace organization::plugins {

    class OrganizationServicePlugin : public drogon::Plugin<OrganizationServicePlugin>
    {
    public:
        OrganizationServicePlugin() = default;
        ~OrganizationServicePlugin() override = default;
        /// This method must be called by drogon to initialize and start the plugin.
        /// It must be implemented by the user.
        void initAndStart(const Json::Value &config) override;

        /// This method must be called by drogon to shutdown the plugin.
        /// It must be implemented by the user.
        void shutdown() override;

        organization::services::OfficeService &getOfficeService() { return officeService_; }

    private:
        organization::services::OfficeService officeService_;
    };
}

