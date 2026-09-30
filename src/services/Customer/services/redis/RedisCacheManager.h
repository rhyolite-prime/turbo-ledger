//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//

#ifndef CUSTOMER_REDISCACHEMANAGER_H
#define CUSTOMER_REDISCACHEMANAGER_H
#include "dto/BaseApiResponse.h"
#include <drogon/drogon.h>

namespace turbo_ledger_customer::services {

    class RedisCacheManager {

    public:

        drogon::Task<std::string> getValue(std::string key, bool shouldRemove = false);

        drogon::Task<dto::BaseApiResponse> setValue(std::string key, std::string value);

        drogon::Task<dto::BaseApiResponse> setValueWithTtl(std::string key, std::string value, int ttlSeconds);

        drogon::Task<dto::BaseApiResponse> removeValue(std::string key);

    };

}


#endif //CUSTOMER_REDISCACHEMANAGER_H
