//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//

#ifndef IDENTITY_JSONUTILS_H
#define IDENTITY_JSONUTILS_H
#include <json/json.h>
#include <string>
#include <cctype>

namespace turbo_ledger_identity::utils {

    class JsonUtils {
    public:
        static std::string toCamelCase(const std::string& snakeCaseStr) {
            std::string camelKey;
            bool nextUpper = false;
            for (char c : snakeCaseStr) {
                if (c == '_') {
                    nextUpper = true;
                } else {
                    if (nextUpper) {
                        camelKey += static_cast<char>(std::toupper(c));
                        nextUpper = false;
                    } else {
                        camelKey += c;
                    }
                }
            }
            return camelKey;
        }

        static Json::Value convertKeysToCamelCase(const Json::Value& json) {
            if (!json.isObject()) {
                return json;
            }

            Json::Value camelJson;
            for (auto const& id : json.getMemberNames()) {
                camelJson[toCamelCase(id)] = json[id];
            }
            return camelJson;
        }
    };

}
#endif //IDENTITY_JSONUTILS_H
