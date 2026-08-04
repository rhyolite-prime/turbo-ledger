//
// Created by Emmanuel Addo-Odame on 02/08/2026.
//

#ifndef IDENTITY_REDISCACHEMANAGER_H
#define IDENTITY_REDISCACHEMANAGER_H
#include <drogon/drogon.h>
#include "dto/BaseApiResponse.h"


namespace turbo_ledger_identity::services {

    class RedisCacheManager {

    public:

        drogon::Task<std::string> getValue(std::string key, bool shouldRemove = false);

        drogon::Task<dto::BaseApiResponse> setValue(std::string key, std::string value);

        drogon::Task<dto::BaseApiResponse> setValueWithTtl(std::string key, std::string value, int ttlSeconds);

        drogon::Task<dto::BaseApiResponse> removeValue(std::string key);

    };

}
#endif //IDENTITY_REDISCACHEMANAGER_H
