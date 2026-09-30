//
// Created by Emmanuel Addo-Odame on 17/04/2026.
//

#ifndef GROUP_COLLECTIONSHEETSERVICE_H
#define GROUP_COLLECTIONSHEETSERVICE_H

#include "dto/BaseApiResponse.h"
#include <drogon/drogon.h>

#include "dto/CollectionSheetDto.h"
#include "dto/IndividualCollectionSheetDto.h"

namespace group::services {

    class CollectionSheetService {
    public:

        drogon::Task<dto::BaseApiResponse> generateCollectionSheet(const dto::IndividualCollectionSheetDto &dto);

        drogon::Task<dto::BaseApiResponse> saveCollectionSheet(const dto::CollectionSheetDto &dto);

    };

}


#endif //GROUP_COLLECTIONSHEETSERVICE_H