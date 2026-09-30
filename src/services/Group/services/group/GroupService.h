//
// Created by Emmanuel Addo-Odame on 17/04/2026.
//

#ifndef GROUP_GROUPSERVICE_H
#define GROUP_GROUPSERVICE_H

#include "dto/BaseApiResponse.h"
#include <drogon/drogon.h>
#include "dto/ActivateGroupDto.h"
#include "dto/AssignRoleDto.h"
#include "dto/AssignStaffDto.h"
#include "dto/AssociateClientsDto.h"
#include "dto/CloseGroupDto.h"
#include "dto/CollectionSheetDto.h"
#include "dto/GroupDto.h"
#include "dto/TransferClientsDto.h"

namespace group::services {

    class GroupService {
    public:

        drogon::Task<dto::BaseApiResponse> getAll(int pageNo, int pageSize,const std::string &query);

        drogon::Task<dto::BaseApiResponse> createGroup(const dto::GroupDto &dto);

        drogon::Task<dto::BaseApiResponse> activateGroup(const dto::ActivateGroupDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> associateClientToGroup(const dto::AssociateClientsDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> disassociateClientToGroup(const dto::AssociateClientsDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> transferClientAcrossGroups(const dto::TransferClientsDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> generateCollectionSheet(const dto::CollectionSheetDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> saveCollectionSheet(const dto::CollectionSheetDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> assignStaff(const dto::AssignStaffDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> unassignStaff(const dto::AssignStaffDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> closeGroup(const dto::CloseGroupDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> assignRole(const dto::AssignRoleDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> unassignRole(const dto::AssignRoleDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> updateRole(const dto::AssignRoleDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> getGroupDetails(const std::string &id);

        drogon::Task<dto::BaseApiResponse> getGroupAccountsOverview(const std::string &id);

        drogon::Task<dto::BaseApiResponse> updateGroup(const dto::GroupDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> deleteGroup(const std::string &id);

        drogon::Task<dto::BaseApiResponse> getGsimApplications(const std::string &id);

        drogon::Task<dto::BaseApiResponse> getGlimApplications(const std::string &id);

    };

}


#endif //GROUP_GROUPSERVICE_H