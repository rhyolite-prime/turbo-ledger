//
// Created by Emmanuel Addo-Odame on 09/08/2026.
//

#ifndef ACCOUNTING_IDENTITYAPI_H
#define ACCOUNTING_IDENTITYAPI_H
#include "dto/BaseApiResponse.h"
#include <drogon/drogon.h>

namespace turbo_ledger_accounting::services {

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

        drogon::Task<ApiCredentialsValidationResult> validateAndCacheApiCredentials(const std::string &clientId, const std::string &clientSecret);
    };

}
#endif //ACCOUNTING_IDENTITYAPI_H
