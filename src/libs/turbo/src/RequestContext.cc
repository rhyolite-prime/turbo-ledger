#include "turbo/RequestContext.h"

#include <algorithm>
#include <cctype>
#include <memory>

namespace turbo {

bool RequestContext::isValidTenantId(const std::string &id) {
    if (id.empty() || id.size() > 40) return false;
    if (!std::islower(static_cast<unsigned char>(id.front())) &&
        !std::isdigit(static_cast<unsigned char>(id.front())))
        return false;
    return std::all_of(id.begin(), id.end(), [](unsigned char c) {
        return std::islower(c) || std::isdigit(c) || c == '_';
    });
}

bool RequestContext::hasPermission(const std::string &permission) const {
    return std::find(permissions.begin(), permissions.end(), permission) != permissions.end() ||
           std::find(permissions.begin(), permissions.end(), "ALL_FUNCTIONS") != permissions.end();
}

Json::Value RequestContext::toJson() const {
    Json::Value j;
    j["tid"] = tenantId;
    j["uid"] = userId;
    j["unm"] = username;
    j["sch"] = authScheme;
    j["rid"] = requestId;
    j["iat"] = static_cast<Json::Int64>(issuedAtEpoch);
    j["exp"] = static_cast<Json::Int64>(expiresAtEpoch);
    Json::Value perms(Json::arrayValue);
    for (const auto &p : permissions) perms.append(p);
    j["prm"] = perms;
    return j;
}

std::optional<RequestContext> RequestContext::fromJson(const Json::Value &json) {
    if (!json.isObject()) return std::nullopt;
    RequestContext ctx;
    ctx.tenantId = json.get("tid", "").asString();
    ctx.userId = json.get("uid", "").asString();
    ctx.username = json.get("unm", "").asString();
    ctx.authScheme = json.get("sch", "").asString();
    ctx.requestId = json.get("rid", "").asString();
    ctx.issuedAtEpoch = json.get("iat", 0).asInt64();
    ctx.expiresAtEpoch = json.get("exp", 0).asInt64();
    if (json.isMember("prm") && json["prm"].isArray()) {
        for (const auto &p : json["prm"]) ctx.permissions.push_back(p.asString());
    }
    if (!isValidTenantId(ctx.tenantId)) return std::nullopt;
    return ctx;
}

void RequestContext::attachTo(const drogon::HttpRequestPtr &req) const {
    req->getAttributes()->insert(kAttributeKey, std::make_shared<RequestContext>(*this));
}

std::optional<RequestContext> RequestContext::from(const drogon::HttpRequestPtr &req) {
    const auto &attrs = req->getAttributes();
    if (!attrs->find(kAttributeKey)) return std::nullopt;
    auto ptr = attrs->get<std::shared_ptr<RequestContext>>(kAttributeKey);
    if (!ptr) return std::nullopt;
    return *ptr;
}

}  // namespace turbo
