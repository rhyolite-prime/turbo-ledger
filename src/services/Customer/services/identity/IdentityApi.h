//
// Created by Emmanuel Addo-Odame on 02/04/2026.
//

#ifndef CUSTOMER_IDENTITYAPI_H
#define CUSTOMER_IDENTITYAPI_H
#include "dto/BaseApiResponse.h"
#include <drogon/drogon.h>

namespace customer::services {

    struct ApiCredentialsValidationResult {
        bool isValid = false;
        std::string accountId;
        std::string businessId;
        std::string errorMessage;
        int errorCode = 0;
    };

    class IdentityApi {

        public:

        drogon::Task<ApiCredentialsValidationResult> validateApiCredentials(const std::string &clientId, const std::string &clientSecret);


    };


}
#endif //CUSTOMER_IDENTITYAPI_H