//
// Created by Emmanuel Addo-Odame on 11/08/2025.
//

// dtos/BaseApiResponse.h
#ifndef BASE_API_RESPONSE_H
#define BASE_API_RESPONSE_H

#include <json/json.h>
#include <string>

namespace turbo_ledger_identity::dto {
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


#endif // BASE_API_RESPONSE_H