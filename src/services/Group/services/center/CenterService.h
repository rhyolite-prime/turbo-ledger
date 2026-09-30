//
// Created by Emmanuel Addo-Odame on 17/04/2026.
//

#ifndef GROUP_CENTERSERVICE_H
#define GROUP_CENTERSERVICE_H

#include "dto/BaseApiResponse.h"
#include <drogon/drogon.h>

#include "dto/ActivateCenterDto.h"
#include "dto/CenterAssociationDto.h"
#include "dto/CenterDto.h"
#include "dto/CollectionSheetDto.h"

namespace group::services {

    class CenterService {
    public:

        drogon::Task<dto::BaseApiResponse> getAll(int pageNo, int pageSize,const std::string &query);

        drogon::Task<dto::BaseApiResponse> createCenter(const dto::CenterDto &dto);

        drogon::Task<dto::BaseApiResponse> updateCenter(const dto::CenterDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> deleteCenter(const std::string &id);

        drogon::Task<dto::BaseApiResponse> activateGroup(const dto::ActivateCenterDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> associateCenterToGroup(const dto::CenterAssociationDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> disassociateCenterToGroup(const dto::CenterAssociationDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> getCenterAccountsOverview(const std::string &id);

        drogon::Task<dto::BaseApiResponse> generateCollectionSheet(const dto::CollectionSheetDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> saveCollectionSheet(const dto::CollectionSheetDto &dto, const std::string &id);


    };

}



#endif //GROUP_CENTERSERVICE_H