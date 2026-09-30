/**
 *
 *  GroupServicePlugin.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>

#include "services/center/CenterService.h"
#include "services/collection_sheet/CollectionSheetService.h"
#include "services/group/GroupService.h"

namespace gnp::plugins {

    class GroupServicePlugin : public drogon::Plugin<GroupServicePlugin>
    {
    public:
        GroupServicePlugin() = default;
        ~GroupServicePlugin() override = default;
        /// This method must be called by drogon to initialize and start the plugin.
        /// It must be implemented by the user.
        void initAndStart(const Json::Value &config) override;

        /// This method must be called by drogon to shutdown the plugin.
        /// It must be implemented by the user.
        void shutdown() override;

        group::services::CenterService &getCenterService() { return centerService_; }
        group::services::CollectionSheetService &getCollectionService() { return collection_sheet_service_; }
        group::services::GroupService &getGroupService() { return group_service_; }


        private:
        group::services::CenterService centerService_;
        group::services::CollectionSheetService collection_sheet_service_;
        group::services::GroupService group_service_;
    };
}
