//
// Created by Emmanuel Addo-Odame on 07/04/2026.
//

#include "dto/BaseApiResponse.h"
#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include "dto/LoanProductDto.h"

namespace organization::services {


    drogon::Task<dto::BaseApiResponse> getAll(int pageNo, int pageSize,const std::string &query) {



    }


    drogon::Task<dto::BaseApiResponse> createAsync(const dto::LoanProductDto &dto) {



    }

    drogon::Task<dto::BaseApiResponse> updateAsync(const dto::LoanProductDto &dto, const std::string &id) {



    }

    drogon::Task<dto::BaseApiResponse> getLoanProductDetails(const std::string &id) {



    }


    drogon::Task<dto::BaseApiResponse> deleteLoanProduct(const std::string &id) {



    }




}