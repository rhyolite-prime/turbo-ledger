

#include "CreateUserDto.h"

void turbo_ledger_identity::dto::CreateUserDto::fromJson(const Json::Value& json) {
    setFirstName(json["firstName"].asString());
    setLastName(json["lastName"].asString());
    setUsername(json["username"].asString());
    setPassword(json["password"].asString());
    setEmail(json["email"].asString());
    setPhoneNumber(json["phoneNumber"].asString());
    // Add any additional fields here
}
