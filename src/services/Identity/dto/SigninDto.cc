#include "SigninDto.h"

namespace turbo_ledger_identity::dto {

SigninDto::SigninDto(const Json::Value& json) {
    fromJson(json);
}

void SigninDto::fromJson(const Json::Value& json) {
    setUsernameOrEmail(json["usernameOrEmail"].asString());
    setPassword(json["password"].asString());
}

}