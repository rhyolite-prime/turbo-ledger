
#include "CreateTenantDto.h"



void turbo_ledger_identity::dto::CreateTenantDto::fromJson(const Json::Value& json)
{
    if (json.isMember("identifier") && json["identifier"].isString()) {
        identifier_ = json["identifier"].asString();
    }

    if (json.isMember("name") && json["name"].isString()) {
        name_ = json["name"].asString();
    }

    if (json.isMember("email") && json["email"].isString()) {
        email_ = json["email"].asString();
    }

    if (json.isMember("phoneNumber") && json["phoneNumber"].isString()) {
        phoneNumber_ = json["phoneNumber"].asString();
    }

    if (json.isMember("connectionString") && json["connectionString"].isString()) {
        connectionString_ = json["connectionString"].asString();
    }

    if (json.isMember("isActive") && json["isActive"].isBool()) {
        isActive_ = json["isActive"].asBool();
    }
}
