//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//

#ifndef IDENTITY_APIKEYSERVICE_H
#define IDENTITY_APIKEYSERVICE_H

#include <drogon/drogon.h>

#include "dto/ApiKeyDto.h"
#include "dto/BaseApiResponse.h"

namespace turbo_ledger_identity::services {

    struct ApiCredentialsValidationResult {
        bool isValid = false;
        std::string accountId;
        std::string businessId;
        std::string errorMessage;
        int errorCode = 0;
    };

    class ApiKeyService {

    public:
        drogon::Task<dto::BaseApiResponse> getAll(const std::string &businessId, int pageNo, int pageSize, const std::string &query);

        drogon::Task<dto::BaseApiResponse> create(const dto::ApiKeyDto &dto); //generates an API Key for a tenant

        drogon::Task<dto::BaseApiResponse> revoke(const std::string &businessId, const std::string &id);

        drogon::Task<dto::BaseApiResponse> activate(const std::string &businessId, const std::string &id);

        drogon::Task<dto::BaseApiResponse> deleteApiKey(const std::string &businessId, const std::string &id);

        drogon::Task<ApiCredentialsValidationResult> validateApiCredentials(const std::string &clientId, const std::string &clientSecret);
    };

}


#endif //IDENTITY_APIKEYSERVICE_H
