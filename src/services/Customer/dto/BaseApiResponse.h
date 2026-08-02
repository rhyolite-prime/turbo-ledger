//
// Created by Emmanuel Addo-Odame on 02/04/2026.
//

#ifndef CUSTOMER_BASEAPIRESPONSE_H
#define CUSTOMER_BASEAPIRESPONSE_H
#include <json/json.h>
#include <string>

namespace customer::dto {

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


#endif //CUSTOMER_BASEAPIRESPONSE_H