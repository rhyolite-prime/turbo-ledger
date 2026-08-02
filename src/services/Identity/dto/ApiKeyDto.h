//
// Created by Emmanuel Addo-Odame on 31/07/2026.
//

#ifndef IDENTITY_APIKEYDTO_H
#define IDENTITY_APIKEYDTO_H
#include <json/json.h>
#include <string>
#include <vector>

namespace turbo_ledger_identity::dto {

    class ApiKeyDto {
    public:
        ApiKeyDto() = default;

        void fromJson(const Json::Value &json);

        // Getters
        [[nodiscard]] const std::string &getBusinessId() const { return business_id_; }
        [[nodiscard]] const std::string &getLabel() const { return label_; }
        [[nodiscard]] const std::string &getBusinessName() const { return business_name_; }
        [[nodiscard]] const std::vector<std::string> &getScopes() const { return scopes_; }
        [[nodiscard]] const std::vector<std::string> &getAllowedIps() const { return allowed_ips_; }

        // Setters
        void setBusinessId(const std::string &value) { business_id_ = value; }
        void setLabel(const std::string &value) { label_ = value; }
        void setBusinessName(const std::string &value) { business_name_ = value; }
        void setScopes(const std::vector<std::string> &value) { scopes_ = value; }
        void setAllowedIps(const std::vector<std::string> &value) { allowed_ips_ = value; }

    private:
        std::string business_id_;
        std::string label_;
        std::string business_name_;
        std::vector<std::string> scopes_;
        std::vector<std::string> allowed_ips_;
    };

    inline void ApiKeyDto::fromJson(const Json::Value &json) {

        if (json.isMember("businessId") && !json["businessId"].isNull()) {
            setBusinessId(json["businessId"].asString());
        }

        if (json.isMember("label") && !json["label"].isNull()) {
            setLabel(json["label"].asString());
        }

        if (json.isMember("businessName") && !json["businessName"].isNull()) {
            setBusinessName(json["businessName"].asString());
        }

        if (json.isMember("scopes") && json["scopes"].isArray()) {

            for (const auto &scope : json["scopes"]) {
                scopes_.push_back(scope.asString());
            }
        }

        if (json.isMember("allowedIps") && json["allowedIps"].isArray()) {
            for (const auto &ip : json["allowedIps"]) {
                allowed_ips_.push_back(ip.asString());
            }
        }
    }

}


#endif //IDENTITY_APIKEYDTO_H
