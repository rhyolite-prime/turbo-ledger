//
// Created by Emmanuel Addo-Odame on 07/04/2026.
//

#include "dto/BaseApiResponse.h"
#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include "dto/LoanProductDto.h"

namespace organization::services {

    namespace {
        dto::BaseApiResponse notImplemented(const std::string &operation) {
            dto::BaseApiResponse response;
            response.success = false;
            response.message = "Not implemented yet: " + operation;
            response.error["message"] = response.message;
            return response;
        }
    }  // namespace

    drogon::Task<dto::BaseApiResponse> getAll(int pageNo, int pageSize, const std::string &query) {
        co_return notImplemented("loanproducts.list");
    }

    drogon::Task<dto::BaseApiResponse> createAsync(const dto::LoanProductDto &dto) {
        co_return notImplemented("loanproducts.create");
    }

    drogon::Task<dto::BaseApiResponse> updateAsync(const dto::LoanProductDto &dto, const std::string &id) {
        co_return notImplemented("loanproducts.update");
    }

    drogon::Task<dto::BaseApiResponse> getLoanProductDetails(const std::string &id) {
        co_return notImplemented("loanproducts.get");
    }

    drogon::Task<dto::BaseApiResponse> deleteLoanProduct(const std::string &id) {
        co_return notImplemented("loanproducts.delete");
    }

}
