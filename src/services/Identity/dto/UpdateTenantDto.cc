#include "UpdateTenantDto.h"

namespace turbo_ledger_identity::dto {

    UpdateTenantDto::UpdateTenantDto(const Json::Value& json) {
        fromJson(json);
    }

    void UpdateTenantDto::fromJson(const Json::Value& json) {
        // The tenant ID is required for updates
        if (json.isMember("id") && !json["id"].isNull()) {
            id_ = json["id"].asString();
        }

        if (json.isMember("name") && !json["name"].isNull()) {
            name_ = json["name"].asString();
        }

        if (json.isMember("email") && !json["email"].isNull()) {
            email_ = json["email"].asString();
        }

        if (json.isMember("phoneNumber") && !json["phoneNumber"].isNull()) {
            phoneNumber_ = json["phoneNumber"].asString();
        }

        if (json.isMember("isActive") && !json["isActive"].isNull()) {
            isActive_ = json["isActive"].asBool();
        }
    }

}
