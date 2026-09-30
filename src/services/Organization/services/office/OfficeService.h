//
// Created by Emmanuel Addo-Odame on 06/04/2026.
//

#ifndef ORGANIZATION_OFFICESERVICE_H
#define ORGANIZATION_OFFICESERVICE_H
#include "dto/BaseApiResponse.h"
#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>

#include "dto/OfficeDto.h"

namespace organization::services {

    class OfficeService {
    public:
        drogon::Task<dto::BaseApiResponse> getAll(int pageNo, int pageSize,const std::string &query);

        drogon::Task<dto::BaseApiResponse> createAsync(const dto::OfficeDto &dto);

        drogon::Task<dto::BaseApiResponse> updateAsync(const dto::OfficeDto &dto, const std::string &id);

        drogon::Task<dto::BaseApiResponse> getOfficeDetails(const std::string &id);

        drogon::Task<dto::BaseApiResponse> deleteOffice(const std::string &id);

    };
}
#endif //ORGANIZATION_OFFICESERVICE_H