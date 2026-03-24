//
// Created by Emmanuel Addo-Odame on 22/03/2026.
//

#ifndef GLOBALCONFIGURATION_BASEAPIRESPONSE_H
#define GLOBALCONFIGURATION_BASEAPIRESPONSE_H

#include <json/json.h>
#include <string>

namespace turbo_ledger_global_configuration::dto {

    class BaseApiResponse {
    public:
        Json::Value result;
        std::string targetUrl;
        std::string message;
        bool success;
        Json::Value error;

        BaseApiResponse() : success(false) {}

        [[nodiscard]]
        Json::Value toJson() const {
            Json::Value json;
            json["result"] = result;
            json["targetUrl"] = targetUrl;
            json["message"] = message;
            json["success"] = success;
            json["error"] = error;
            return json;
        }
    };

}


#endif //GLOBALCONFIGURATION_BASEAPIRESPONSE_H