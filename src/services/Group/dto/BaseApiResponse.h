//
// Created by Emmanuel Addo-Odame on 19/04/2026.
//

#ifndef GROUP_BASEAPIRESPONSE_H
#define GROUP_BASEAPIRESPONSE_H

#include <json/json.h>
#include <string>

namespace group::dto {

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


#endif //GROUP_BASEAPIRESPONSE_H