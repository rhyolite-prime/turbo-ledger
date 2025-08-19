//
// Created by Emmanuel Addo-Odame on 19/08/2025.
//
// dto/UpdateUserDto.cc
#include "UpdateUserDto.h"

namespace turbo_ledger_identity::dto {

    UpdateUserDto::UpdateUserDto(const Json::Value& json)
    {
        fromJson(json);
    }

    void UpdateUserDto::fromJson(const Json::Value& json)
    {
        if (json.isMember("id")) setId(json["id"].asString());
        if (json.isMember("firstName")) setFirstName(json["firstName"].asString());
        if (json.isMember("lastName")) setLastName(json["lastName"].asString());
        if (json.isMember("phoneNumber")) setPhoneNumber(json["phoneNumber"].asString());
        if (json.isMember("email")) setEmail(json["email"].asString());
        if (json.isMember("password")) setPassword(json["password"].asString());
        if (json.isMember("isActive")) setIsActive(json["isActive"].asBool());
        if (json.isMember("isLockedOut")) setIsLockedOut(json["isLockedOut"].asBool());
    }

}