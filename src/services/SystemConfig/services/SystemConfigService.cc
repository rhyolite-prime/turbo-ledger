#include "SystemConfigService.h"

#include <drogon/orm/DbClient.h>

#include <sstream>

#include "turbo/Outbox.h"
#include "turbo/TenantDb.h"

using drogon::orm::DrogonDbException;

namespace turbo_ledger_systemconfig {

namespace {

std::string asStringOr(const Json::Value &v, const char *key, const std::string &fallback = "") {
    return v.isMember(key) && !v[key].isNull() ? v[key].asString() : fallback;
}

bool asBoolOr(const Json::Value &v, const char *key, bool fallback) {
    return v.isMember(key) && v[key].isBool() ? v[key].asBool() : fallback;
}

int asIntOr(const Json::Value &v, const char *key, int fallback) {
    return v.isMember(key) && v[key].isInt() ? v[key].asInt() : fallback;
}

Json::Value parseJsonOrEmpty(const std::string &text, Json::ValueType fallbackType) {
    Json::Value out(fallbackType);
    if (text.empty()) return out;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream stream(text);
    Json::Value parsed;
    if (Json::parseFromStream(builder, stream, &parsed, &errs)) return parsed;
    return out;
}

std::string jsonCompact(const Json::Value &v) {
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    return Json::writeString(builder, v);
}

/// Postgres cast suffix for a datatable column's declared logical type.
std::string columnCastSuffix(const std::string &type) {
    if (type == "Number" || type == "Decimal") return "::numeric";
    if (type == "Date") return "::date";
    if (type == "Datetime") return "::timestamptz";
    if (type == "Boolean") return "::boolean";
    return "";  // String / Text — bind as-is
}

/// Postgres column type for a datatable column's declared logical type.
std::string columnSqlType(const std::string &type) {
    if (type == "Number" || type == "Decimal") return "numeric(19,6)";
    if (type == "Date") return "date";
    if (type == "Datetime") return "timestamptz";
    if (type == "Boolean") return "boolean";
    if (type == "Text") return "text";
    return "varchar(500)";  // String / default
}

/// Physical dt_<name> table identifier for a registered datatable. Validates
/// that datatableName only contains identifier-safe characters.
std::string physicalTableIdent(const std::string &datatableName) {
    return turbo::db::quoteIdentifier("dt_" + datatableName);
}

}  // namespace

drogon::orm::DbClientPtr SystemConfigService::db() { return drogon::app().getDbClient(); }

void SystemConfigService::requirePermission(const turbo::RequestContext &ctx,
                                            const std::string &code) {
    if (!ctx.hasPermission(code))
        throw ApiError(drogon::k403Forbidden, "Missing permission: " + code,
                       "error.msg.platform.permission.denied");
}

// ---------------------------------------------------------------------------
// codes / code values
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::codeToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, code_name, is_system_defined FROM code WHERE id::text = $1", id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Code not found", "error.msg.systemconfig.code.not.found");
    Json::Value j;
    j["id"] = rows[0]["id"].as<std::string>();
    j["name"] = rows[0]["code_name"].isNull() ? "" : rows[0]["code_name"].as<std::string>();
    j["systemDefined"] = rows[0]["is_system_defined"].as<bool>();
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::listCodes(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CODE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, code_name, is_system_defined FROM code ORDER BY code_name");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["name"] = r["code_name"].isNull() ? "" : r["code_name"].as<std::string>();
        j["systemDefined"] = r["is_system_defined"].as<bool>();
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getCode(const turbo::RequestContext &ctx,
                                                       const std::string &id) {
    requirePermission(ctx, "READ_CODE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await codeToJson(txn, id);
}

drogon::Task<Json::Value> SystemConfigService::getCodeByName(const turbo::RequestContext &ctx,
                                                             const std::string &name) {
    requirePermission(ctx, "READ_CODE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro("SELECT id::text AS id FROM code WHERE code_name = $1", name);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Code not found", "error.msg.systemconfig.code.not.found");
    co_return co_await codeToJson(txn, rows[0]["id"].as<std::string>());
}

drogon::Task<Json::Value> SystemConfigService::createCode(const turbo::RequestContext &ctx,
                                                          const Json::Value &body) {
    requirePermission(ctx, "CREATE_CODE");
    const std::string name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "'name' is required",
                       "error.msg.systemconfig.code.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO code (code_name, is_system_defined) VALUES ($1, false) "
            "RETURNING id::text AS id",
            name);
        const std::string id = rows[0]["id"].as<std::string>();
        co_await turbo::outbox::writeEvent(txn, ctx, "code", id, "code.created", body);
        co_return co_await codeToJson(txn, id);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "A code with this name already exists",
                       "error.msg.systemconfig.code.duplicate");
    }
}

drogon::Task<Json::Value> SystemConfigService::updateCode(const turbo::RequestContext &ctx,
                                                          const std::string &id,
                                                          const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CODE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "UPDATE code SET code_name = COALESCE(NULLIF($2, ''), code_name) "
        "WHERE id::text = $1 AND NOT is_system_defined RETURNING id::text AS id",
        id, asStringOr(body, "name"));
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Code not found or is system-defined",
                       "error.msg.systemconfig.code.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "code", id, "code.updated", body);
    co_return co_await codeToJson(txn, id);
}

drogon::Task<void> SystemConfigService::deleteCode(const turbo::RequestContext &ctx,
                                                   const std::string &id) {
    requirePermission(ctx, "DELETE_CODE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto row = co_await txn->execSqlCoro("SELECT is_system_defined FROM code WHERE id::text = $1", id);
    if (row.size() == 0)
        throw ApiError(drogon::k404NotFound, "Code not found", "error.msg.systemconfig.code.not.found");
    if (row[0]["is_system_defined"].as<bool>())
        throw ApiError(drogon::k403Forbidden, "System-defined codes cannot be deleted",
                       "error.msg.systemconfig.code.protected");
    co_await txn->execSqlCoro("DELETE FROM code_value WHERE code_id::text = $1", id);
    co_await txn->execSqlCoro("DELETE FROM code WHERE id::text = $1", id);
    co_await turbo::outbox::writeEvent(txn, ctx, "code", id, "code.deleted", Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> SystemConfigService::codeValueToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, code_id::text AS code_id, code_value, code_description, "
        "  order_position, code_score, is_active, is_mandatory FROM code_value WHERE id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Code value not found",
                       "error.msg.systemconfig.codevalue.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["codeId"] = r["code_id"].as<std::string>();
    j["name"] = r["code_value"].isNull() ? "" : r["code_value"].as<std::string>();
    j["description"] = r["code_description"].isNull() ? "" : r["code_description"].as<std::string>();
    j["position"] = r["order_position"].as<int>();
    j["isActive"] = r["is_active"].as<bool>();
    j["isMandatory"] = r["is_mandatory"].as<bool>();
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::listCodeValues(const turbo::RequestContext &ctx,
                                                              const std::string &codeId) {
    requirePermission(ctx, "READ_CODEVALUE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, code_id::text AS code_id, code_value, code_description, "
        "  order_position, code_score, is_active, is_mandatory FROM code_value "
        "WHERE code_id::text = $1 ORDER BY order_position, code_value",
        codeId);
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["codeId"] = r["code_id"].as<std::string>();
        j["name"] = r["code_value"].isNull() ? "" : r["code_value"].as<std::string>();
        j["description"] = r["code_description"].isNull() ? "" : r["code_description"].as<std::string>();
        j["position"] = r["order_position"].as<int>();
        j["isActive"] = r["is_active"].as<bool>();
        j["isMandatory"] = r["is_mandatory"].as<bool>();
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getCodeValue(const turbo::RequestContext &ctx,
                                                            const std::string &codeId,
                                                            const std::string &valueId) {
    requirePermission(ctx, "READ_CODEVALUE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    (void)codeId;
    co_return co_await codeValueToJson(txn, valueId);
}

drogon::Task<Json::Value> SystemConfigService::createCodeValue(const turbo::RequestContext &ctx,
                                                               const std::string &codeId,
                                                               const Json::Value &body) {
    requirePermission(ctx, "CREATE_CODEVALUE");
    const std::string name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "'name' is required",
                       "error.msg.systemconfig.codevalue.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto code = co_await txn->execSqlCoro("SELECT 1 FROM code WHERE id::text = $1", codeId);
    if (code.size() == 0)
        throw ApiError(drogon::k400BadRequest, "Unknown codeId: " + codeId,
                       "error.msg.systemconfig.code.not.found");
    try {
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO code_value (code_id, code_value, code_description, order_position, "
            "  is_active, is_mandatory) "
            "VALUES ($1::uuid, $2, NULLIF($3, ''), $4, $5, $6) RETURNING id::text AS id",
            codeId, name, asStringOr(body, "description"), asIntOr(body, "position", 0),
            asBoolOr(body, "isActive", true), asBoolOr(body, "isMandatory", false));
        const std::string id = rows[0]["id"].as<std::string>();
        co_await turbo::outbox::writeEvent(txn, ctx, "codevalue", id, "codevalue.created", body);
        co_return co_await codeValueToJson(txn, id);
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "This code already has a value with that name",
                       "error.msg.systemconfig.codevalue.duplicate");
    }
}

drogon::Task<Json::Value> SystemConfigService::updateCodeValue(const turbo::RequestContext &ctx,
                                                               const std::string &codeId,
                                                               const std::string &valueId,
                                                               const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CODEVALUE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    (void)codeId;
    auto current = co_await txn->execSqlCoro(
        "SELECT is_active, is_mandatory FROM code_value WHERE id::text = $1", valueId);
    if (current.size() == 0)
        throw ApiError(drogon::k404NotFound, "Code value not found",
                       "error.msg.systemconfig.codevalue.not.found");
    const bool isActive =
        body.isMember("isActive") ? asBoolOr(body, "isActive", true) : current[0]["is_active"].as<bool>();
    const bool isMandatory = body.isMember("isMandatory") ? asBoolOr(body, "isMandatory", false)
                                                          : current[0]["is_mandatory"].as<bool>();
    auto rows = co_await txn->execSqlCoro(
        "UPDATE code_value SET code_value = COALESCE(NULLIF($2, ''), code_value), "
        "  code_description = COALESCE(NULLIF($3, ''), code_description), "
        "  order_position = COALESCE(NULLIF($4, 0), order_position), "
        "  is_active = $5, is_mandatory = $6 "
        "WHERE id::text = $1 RETURNING id::text AS id",
        valueId, asStringOr(body, "name"), asStringOr(body, "description"),
        asIntOr(body, "position", 0), isActive, isMandatory);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Code value not found",
                       "error.msg.systemconfig.codevalue.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "codevalue", valueId, "codevalue.updated", body);
    co_return co_await codeValueToJson(txn, valueId);
}

drogon::Task<void> SystemConfigService::deleteCodeValue(const turbo::RequestContext &ctx,
                                                        const std::string &codeId,
                                                        const std::string &valueId) {
    requirePermission(ctx, "DELETE_CODEVALUE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    (void)codeId;
    auto rows =
        co_await txn->execSqlCoro("DELETE FROM code_value WHERE id::text = $1 RETURNING id", valueId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Code value not found",
                       "error.msg.systemconfig.codevalue.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "codevalue", valueId, "codevalue.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// global configuration
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::configurationToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name, value, date_value::text AS date_value, is_enabled, description "
        "FROM configuration WHERE id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Configuration not found",
                       "error.msg.systemconfig.configuration.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["name"] = r["name"].as<std::string>();
    j["value"] = r["value"].isNull() ? "" : r["value"].as<std::string>();
    j["dateValue"] = r["date_value"].isNull() ? "" : r["date_value"].as<std::string>();
    j["enabled"] = r["is_enabled"].as<bool>();
    j["description"] = r["description"].isNull() ? "" : r["description"].as<std::string>();
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::listConfigurations(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name, value, date_value::text AS date_value, is_enabled, description "
        "FROM configuration ORDER BY name");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["name"] = r["name"].as<std::string>();
        j["value"] = r["value"].isNull() ? "" : r["value"].as<std::string>();
        j["dateValue"] = r["date_value"].isNull() ? "" : r["date_value"].as<std::string>();
        j["enabled"] = r["is_enabled"].as<bool>();
        j["description"] = r["description"].isNull() ? "" : r["description"].as<std::string>();
        list.append(j);
    }
    Json::Value out;
    out["globalConfiguration"] = list;
    co_return out;
}

drogon::Task<Json::Value> SystemConfigService::getConfiguration(const turbo::RequestContext &ctx,
                                                                const std::string &id) {
    requirePermission(ctx, "READ_CONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await configurationToJson(txn, id);
}

drogon::Task<Json::Value> SystemConfigService::getConfigurationByName(const turbo::RequestContext &ctx,
                                                                     const std::string &name) {
    requirePermission(ctx, "READ_CONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows =
        co_await txn->execSqlCoro("SELECT id::text AS id FROM configuration WHERE name = $1", name);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Configuration not found",
                       "error.msg.systemconfig.configuration.not.found");
    co_return co_await configurationToJson(txn, rows[0]["id"].as<std::string>());
}

drogon::Task<Json::Value> SystemConfigService::updateConfiguration(const turbo::RequestContext &ctx,
                                                                  const std::string &id,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto current = co_await txn->execSqlCoro("SELECT is_enabled FROM configuration WHERE id::text = $1", id);
    if (current.size() == 0)
        throw ApiError(drogon::k404NotFound, "Configuration not found",
                       "error.msg.systemconfig.configuration.not.found");
    const bool enabled =
        body.isMember("enabled") ? asBoolOr(body, "enabled", false) : current[0]["is_enabled"].as<bool>();
    auto rows = co_await txn->execSqlCoro(
        "UPDATE configuration SET value = COALESCE(NULLIF($2, ''), value), "
        "  date_value = COALESCE(NULLIF($3, '')::date, date_value), is_enabled = $4, "
        "  modified_at = now() WHERE id::text = $1 RETURNING id::text AS id",
        id, asStringOr(body, "value"), asStringOr(body, "dateValue"), enabled);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Configuration not found",
                       "error.msg.systemconfig.configuration.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "configuration", id, "configuration.updated", body);
    co_return co_await configurationToJson(txn, id);
}

drogon::Task<Json::Value> SystemConfigService::updateConfigurationByName(
    const turbo::RequestContext &ctx, const std::string &name, const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows =
        co_await txn->execSqlCoro("SELECT id::text AS id FROM configuration WHERE name = $1", name);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Configuration not found",
                       "error.msg.systemconfig.configuration.not.found");
    co_return co_await updateConfiguration(ctx, rows[0]["id"].as<std::string>(), body);
}

// ---------------------------------------------------------------------------
// external service configuration
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::getExternalService(const turbo::RequestContext &ctx,
                                                                  const std::string &name) {
    requirePermission(ctx, "READ_EXTERNALSERVICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT service_name, config::text AS config FROM external_service WHERE service_name = $1",
        name);
    Json::Value out;
    out["name"] = name;
    out["config"] = rows.size() > 0 ? parseJsonOrEmpty(rows[0]["config"].as<std::string>(),
                                                       Json::objectValue)
                                    : Json::Value(Json::objectValue);
    co_return out;
}

drogon::Task<Json::Value> SystemConfigService::updateExternalService(const turbo::RequestContext &ctx,
                                                                    const std::string &name,
                                                                    const Json::Value &body) {
    requirePermission(ctx, "UPDATE_EXTERNALSERVICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    const std::string configJson = jsonCompact(body);
    co_await txn->execSqlCoro(
        "INSERT INTO external_service (service_name, config, modified_at) "
        "VALUES ($1, $2::jsonb, now()) "
        "ON CONFLICT (service_name) DO UPDATE SET config = EXCLUDED.config, modified_at = now()",
        name, configJson);
    co_await turbo::outbox::writeEvent(txn, ctx, "externalservice", name, "externalservice.updated",
                                       body);
    co_return co_await getExternalService(ctx, name);
}

// ---------------------------------------------------------------------------
// audits — reads this service's own transactional outbox as a local audit
// trail (platform-wide command audit is future EventHub-aggregator scope).
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listAudits(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_AUDIT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, aggregate_type, aggregate_id, event_type, actor_user_id, "
        "  occurred_at::text AS occurred_at FROM tl_outbox ORDER BY occurred_at DESC LIMIT 200");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["resourceType"] = r["aggregate_type"].as<std::string>();
        j["resourceId"] = r["aggregate_id"].as<std::string>();
        j["actionName"] = r["event_type"].as<std::string>();
        j["maker"] = r["actor_user_id"].isNull() ? "" : r["actor_user_id"].as<std::string>();
        j["madeOnDate"] = r["occurred_at"].as<std::string>();
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getAudit(const turbo::RequestContext &ctx,
                                                        const std::string &id) {
    requirePermission(ctx, "READ_AUDIT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, aggregate_type, aggregate_id, event_type, payload::text AS payload, "
        "  actor_user_id, request_id, occurred_at::text AS occurred_at "
        "FROM tl_outbox WHERE id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Audit entry not found",
                       "error.msg.systemconfig.audit.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["resourceType"] = r["aggregate_type"].as<std::string>();
    j["resourceId"] = r["aggregate_id"].as<std::string>();
    j["actionName"] = r["event_type"].as<std::string>();
    j["commandAsJson"] = parseJsonOrEmpty(r["payload"].as<std::string>(), Json::objectValue);
    j["maker"] = r["actor_user_id"].isNull() ? "" : r["actor_user_id"].as<std::string>();
    j["requestId"] = r["request_id"].isNull() ? "" : r["request_id"].as<std::string>();
    j["madeOnDate"] = r["occurred_at"].as<std::string>();
    co_return j;
}

Json::Value SystemConfigService::auditSearchTemplate(const turbo::RequestContext &) {
    Json::Value out;
    out["actionNames"] = Json::Value(Json::arrayValue);
    out["entityNames"] = Json::Value(Json::arrayValue);
    out["processingResults"] = Json::Value(Json::arrayValue);
    return out;
}

// ---------------------------------------------------------------------------
// hooks
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::hookToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name, display_name, is_active, config::text AS config, "
        "  events::text AS events FROM hook WHERE id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Hook not found", "error.msg.systemconfig.hook.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["name"] = r["name"].as<std::string>();
    j["displayName"] = r["display_name"].as<std::string>();
    j["isActive"] = r["is_active"].as<bool>();
    j["config"] = parseJsonOrEmpty(r["config"].as<std::string>(), Json::objectValue);
    j["events"] = parseJsonOrEmpty(r["events"].as<std::string>(), Json::arrayValue);
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::listHooks(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_HOOK");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, name, display_name, is_active FROM hook ORDER BY display_name");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["name"] = r["name"].as<std::string>();
        j["displayName"] = r["display_name"].as<std::string>();
        j["isActive"] = r["is_active"].as<bool>();
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getHook(const turbo::RequestContext &ctx,
                                                       const std::string &id) {
    requirePermission(ctx, "READ_HOOK");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await hookToJson(txn, id);
}

drogon::Task<Json::Value> SystemConfigService::createHook(const turbo::RequestContext &ctx,
                                                          const Json::Value &body) {
    requirePermission(ctx, "CREATE_HOOK");
    const std::string name = asStringOr(body, "name");
    const std::string displayName = asStringOr(body, "displayName", name);
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "'name' is required",
                       "error.msg.systemconfig.hook.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO hook (name, display_name, is_active, config, events) "
        "VALUES ($1, $2, $3, $4::jsonb, $5::jsonb) RETURNING id::text AS id",
        name, displayName, asBoolOr(body, "isActive", true),
        jsonCompact(body.isMember("config") ? body["config"] : Json::Value(Json::objectValue)),
        jsonCompact(body.isMember("events") ? body["events"] : Json::Value(Json::arrayValue)));
    const std::string id = rows[0]["id"].as<std::string>();
    co_await turbo::outbox::writeEvent(txn, ctx, "hook", id, "hook.created", body);
    co_return co_await hookToJson(txn, id);
}

drogon::Task<Json::Value> SystemConfigService::updateHook(const turbo::RequestContext &ctx,
                                                          const std::string &id,
                                                          const Json::Value &body) {
    requirePermission(ctx, "UPDATE_HOOK");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto current = co_await txn->execSqlCoro(
        "SELECT is_active, config::text AS config, events::text AS events FROM hook WHERE id::text = $1",
        id);
    if (current.size() == 0)
        throw ApiError(drogon::k404NotFound, "Hook not found", "error.msg.systemconfig.hook.not.found");
    const bool isActive =
        body.isMember("isActive") ? asBoolOr(body, "isActive", true) : current[0]["is_active"].as<bool>();
    const std::string config = body.isMember("config") ? jsonCompact(body["config"])
                                                        : current[0]["config"].as<std::string>();
    const std::string events = body.isMember("events") ? jsonCompact(body["events"])
                                                        : current[0]["events"].as<std::string>();
    auto rows = co_await txn->execSqlCoro(
        "UPDATE hook SET display_name = COALESCE(NULLIF($2, ''), display_name), is_active = $3, "
        "  config = $4::jsonb, events = $5::jsonb, modified_at = now() "
        "WHERE id::text = $1 RETURNING id::text AS id",
        id, asStringOr(body, "displayName"), isActive, config, events);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Hook not found", "error.msg.systemconfig.hook.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "hook", id, "hook.updated", body);
    co_return co_await hookToJson(txn, id);
}

drogon::Task<void> SystemConfigService::deleteHook(const turbo::RequestContext &ctx,
                                                   const std::string &id) {
    requirePermission(ctx, "DELETE_HOOK");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro("DELETE FROM hook WHERE id::text = $1 RETURNING id", id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Hook not found", "error.msg.systemconfig.hook.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "hook", id, "hook.deleted", Json::Value(Json::objectValue));
    co_return;
}

Json::Value SystemConfigService::hookTemplate(const turbo::RequestContext &) {
    Json::Value out;
    Json::Value templates(Json::arrayValue);
    templates.append("Web");
    out["templates"] = templates;
    return out;
}

// ---------------------------------------------------------------------------
// caches
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::getCacheConfig(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CACHE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro("SELECT cache_type FROM cache_config WHERE id = 1");
    Json::Value out;
    out["cacheType"] = rows.size() > 0 ? rows[0]["cache_type"].as<std::string>() : "NO_CACHE";
    co_return out;
}

drogon::Task<Json::Value> SystemConfigService::updateCacheConfig(const turbo::RequestContext &ctx,
                                                                 const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CACHE");
    const std::string cacheType = asStringOr(body, "cacheType", "NO_CACHE");
    if (cacheType != "NO_CACHE" && cacheType != "SINGLE_NODE" && cacheType != "DISTRIBUTED")
        throw ApiError(drogon::k400BadRequest, "Unknown cacheType: " + cacheType,
                       "error.msg.systemconfig.cache.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await txn->execSqlCoro(
        "UPDATE cache_config SET cache_type = $1, modified_at = now() WHERE id = 1", cacheType);
    co_await turbo::outbox::writeEvent(txn, ctx, "cache", "1", "cache.updated", body);
    co_return co_await getCacheConfig(ctx);
}

// ---------------------------------------------------------------------------
// business date
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listBusinessDates(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_BUSINESSDATE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows =
        co_await txn->execSqlCoro("SELECT type, date_value::text AS date_value FROM business_date");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["type"] = r["type"].as<std::string>();
        j["date"] = r["date_value"].as<std::string>();
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getBusinessDate(const turbo::RequestContext &ctx,
                                                               const std::string &type) {
    requirePermission(ctx, "READ_BUSINESSDATE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT type, date_value::text AS date_value FROM business_date WHERE type = $1", type);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Business date type not found",
                       "error.msg.systemconfig.businessdate.not.found");
    Json::Value j;
    j["type"] = rows[0]["type"].as<std::string>();
    j["date"] = rows[0]["date_value"].as<std::string>();
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::updateBusinessDate(const turbo::RequestContext &ctx,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "UPDATE_BUSINESSDATE");
    const std::string type = asStringOr(body, "type", "BUSINESS_DATE");
    const std::string date = asStringOr(body, "date");
    if (date.empty())
        throw ApiError(drogon::k400BadRequest, "'date' is required",
                       "error.msg.systemconfig.businessdate.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await txn->execSqlCoro(
        "INSERT INTO business_date (type, date_value, modified_at) VALUES ($1, $2::date, now()) "
        "ON CONFLICT (type) DO UPDATE SET date_value = EXCLUDED.date_value, modified_at = now()",
        type, date);
    co_await turbo::outbox::writeEvent(txn, ctx, "businessdate", type, "businessdate.updated", body);
    co_return co_await getBusinessDate(ctx, type);
}

// ---------------------------------------------------------------------------
// external events posting configuration
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listExternalEventConfig(
    const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_EXTERNALEVENTS");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows =
        co_await txn->execSqlCoro("SELECT category, is_enabled FROM external_event_configuration "
                                  "ORDER BY category");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["category"] = r["category"].as<std::string>();
        j["enabled"] = r["is_enabled"].as<bool>();
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::updateExternalEventConfig(
    const turbo::RequestContext &ctx, const Json::Value &body) {
    requirePermission(ctx, "UPDATE_EXTERNALEVENTS");
    const std::string category = asStringOr(body, "category", "ALL");
    const bool enabled = asBoolOr(body, "enabled", false);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await txn->execSqlCoro(
        "INSERT INTO external_event_configuration (category, is_enabled, modified_at) "
        "VALUES ($1, $2, now()) "
        "ON CONFLICT (category) DO UPDATE SET is_enabled = EXCLUDED.is_enabled, modified_at = now()",
        category, enabled);
    co_await turbo::outbox::writeEvent(txn, ctx, "externalevents", category,
                                       "externalevents.updated", body);
    co_return co_await listExternalEventConfig(ctx);
}

// ---------------------------------------------------------------------------
// field configuration
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::getFieldConfiguration(const turbo::RequestContext &ctx,
                                                                    const std::string &entity) {
    requirePermission(ctx, "READ_FIELDCONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT field_name, is_enabled, is_mandatory, validation_regex FROM field_configuration "
        "WHERE entity = $1 ORDER BY field_name",
        entity);
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["fieldName"] = r["field_name"].as<std::string>();
        j["isEnabled"] = r["is_enabled"].as<bool>();
        j["isMandatory"] = r["is_mandatory"].as<bool>();
        j["validationRegex"] =
            r["validation_regex"].isNull() ? "" : r["validation_regex"].as<std::string>();
        list.append(j);
    }
    co_return list;
}

// ---------------------------------------------------------------------------
// datatables engine
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listDatatables(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_DATATABLE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT datatable_name, apptable_name, category, is_multi_row, columns::text AS columns "
        "FROM tl_datatable_registry ORDER BY datatable_name");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["registeredTableName"] = r["datatable_name"].as<std::string>();
        j["applicationTableName"] = r["apptable_name"].as<std::string>();
        j["category"] = r["category"].as<int>();
        j["multiRow"] = r["is_multi_row"].as<bool>();
        j["columnHeaderData"] = parseJsonOrEmpty(r["columns"].as<std::string>(), Json::arrayValue);
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getDatatable(const turbo::RequestContext &ctx,
                                                            const std::string &name) {
    requirePermission(ctx, "READ_DATATABLE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT datatable_name, apptable_name, category, is_multi_row, columns::text AS columns "
        "FROM tl_datatable_registry WHERE datatable_name = $1",
        name);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Datatable not found",
                       "error.msg.systemconfig.datatable.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["registeredTableName"] = r["datatable_name"].as<std::string>();
    j["applicationTableName"] = r["apptable_name"].as<std::string>();
    j["category"] = r["category"].as<int>();
    j["multiRow"] = r["is_multi_row"].as<bool>();
    j["columnHeaderData"] = parseJsonOrEmpty(r["columns"].as<std::string>(), Json::arrayValue);
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::createDatatable(const turbo::RequestContext &ctx,
                                                               const Json::Value &body) {
    requirePermission(ctx, "CREATE_DATATABLE");
    const std::string name = asStringOr(body, "datatableName");
    const std::string apptable = asStringOr(body, "apptableName");
    if (name.empty() || apptable.empty() || !body.isMember("columns") || !body["columns"].isArray())
        throw ApiError(drogon::k400BadRequest,
                       "'datatableName', 'apptableName' and a 'columns' array are required",
                       "error.msg.systemconfig.datatable.validation");
    const std::string tableIdent = physicalTableIdent(name);  // validates identifier safety

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto existing =
        co_await txn->execSqlCoro("SELECT 1 FROM tl_datatable_registry WHERE datatable_name = $1", name);
    if (existing.size() > 0)
        throw ApiError(drogon::k409Conflict, "A datatable with this name already exists",
                       "error.msg.systemconfig.datatable.duplicate");

    std::string ddl = "CREATE TABLE " + tableIdent +
                      " (id uuid DEFAULT gen_random_uuid() NOT NULL PRIMARY KEY, "
                      "apptable_id varchar(80) NOT NULL";
    for (const auto &col : body["columns"]) {
        const std::string colName = asStringOr(col, "name");
        const std::string colType = asStringOr(col, "type", "String");
        if (colName.empty())
            throw ApiError(drogon::k400BadRequest, "Each column requires a 'name'",
                           "error.msg.systemconfig.datatable.validation");
        const bool mandatory = asBoolOr(col, "mandatory", false);
        ddl += ", " + turbo::db::quoteIdentifier(colName) + " " + columnSqlType(colType) +
               (mandatory ? " NOT NULL" : "");
    }
    ddl += ")";

    co_await txn->execSqlCoro(ddl);
    co_await txn->execSqlCoro("CREATE INDEX ON " + tableIdent + " (apptable_id)");
    co_await txn->execSqlCoro(
        "INSERT INTO tl_datatable_registry (datatable_name, apptable_name, category, is_multi_row, "
        "  columns) VALUES ($1, $2, $3, $4, $5::jsonb)",
        name, apptable, asIntOr(body, "category", 0), asBoolOr(body, "multiRow", true),
        jsonCompact(body["columns"]));
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable", name, "datatable.created", body);
    co_return co_await getDatatable(ctx, name);
}

drogon::Task<Json::Value> SystemConfigService::registerDatatable(const turbo::RequestContext &ctx,
                                                                 const std::string &datatable,
                                                                 const std::string &apptable) {
    requirePermission(ctx, "CREATE_DATATABLE");
    const std::string tableIdent = physicalTableIdent(datatable);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto exists = co_await txn->execSqlCoro(
        "SELECT 1 FROM information_schema.tables WHERE table_schema = current_schema() "
        "AND table_name = $1",
        "dt_" + datatable);
    if (exists.size() == 0)
        throw ApiError(drogon::k400BadRequest,
                       "No physical table exists for '" + datatable + "' — use create instead",
                       "error.msg.systemconfig.datatable.not.found");
    auto columns = co_await txn->execSqlCoro(
        "SELECT column_name, data_type FROM information_schema.columns "
        "WHERE table_schema = current_schema() AND table_name = $1 "
        "AND column_name NOT IN ('id', 'apptable_id') ORDER BY ordinal_position",
        "dt_" + datatable);
    Json::Value cols(Json::arrayValue);
    for (const auto &c : columns) {
        Json::Value cj;
        cj["name"] = c["column_name"].as<std::string>();
        cj["type"] = c["data_type"].as<std::string>();
        cols.append(cj);
    }
    (void)tableIdent;
    co_await txn->execSqlCoro(
        "INSERT INTO tl_datatable_registry (datatable_name, apptable_name, columns) "
        "VALUES ($1, $2, $3::jsonb) ON CONFLICT (datatable_name) DO UPDATE SET "
        "  apptable_name = EXCLUDED.apptable_name, columns = EXCLUDED.columns",
        datatable, apptable, jsonCompact(cols));
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable", datatable, "datatable.registered",
                                       Json::Value(Json::objectValue));
    co_return co_await getDatatable(ctx, datatable);
}

drogon::Task<void> SystemConfigService::deregisterDatatable(const turbo::RequestContext &ctx,
                                                            const std::string &datatable) {
    requirePermission(ctx, "DELETE_DATATABLE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "DELETE FROM tl_datatable_registry WHERE datatable_name = $1 RETURNING datatable_name",
        datatable);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Datatable not found",
                       "error.msg.systemconfig.datatable.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable", datatable, "datatable.deregistered",
                                       Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> SystemConfigService::updateDatatable(const turbo::RequestContext &ctx,
                                                               const std::string &name,
                                                               const Json::Value &body) {
    requirePermission(ctx, "UPDATE_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto reg = co_await txn->execSqlCoro(
        "SELECT columns::text AS columns FROM tl_datatable_registry WHERE datatable_name = $1", name);
    if (reg.size() == 0)
        throw ApiError(drogon::k404NotFound, "Datatable not found",
                       "error.msg.systemconfig.datatable.not.found");
    Json::Value columns = parseJsonOrEmpty(reg[0]["columns"].as<std::string>(), Json::arrayValue);

    if (body.isMember("addColumns") && body["addColumns"].isArray()) {
        for (const auto &col : body["addColumns"]) {
            const std::string colName = asStringOr(col, "name");
            const std::string colType = asStringOr(col, "type", "String");
            if (colName.empty()) continue;
            co_await txn->execSqlCoro("ALTER TABLE " + tableIdent + " ADD COLUMN " +
                                      turbo::db::quoteIdentifier(colName) + " " + columnSqlType(colType));
            columns.append(col);
        }
    }
    if (body.isMember("dropColumns") && body["dropColumns"].isArray()) {
        for (const auto &colName : body["dropColumns"]) {
            const std::string name2 = colName.asString();
            if (name2.empty()) continue;
            co_await txn->execSqlCoro("ALTER TABLE " + tableIdent + " DROP COLUMN IF EXISTS " +
                                      turbo::db::quoteIdentifier(name2));
            Json::Value kept(Json::arrayValue);
            for (const auto &c : columns)
                if (asStringOr(c, "name") != name2) kept.append(c);
            columns = kept;
        }
    }
    co_await txn->execSqlCoro(
        "UPDATE tl_datatable_registry SET columns = $2::jsonb WHERE datatable_name = $1", name,
        jsonCompact(columns));
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable", name, "datatable.updated", body);
    co_return co_await getDatatable(ctx, name);
}

drogon::Task<void> SystemConfigService::deleteDatatable(const turbo::RequestContext &ctx,
                                                        const std::string &name) {
    requirePermission(ctx, "DELETE_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "DELETE FROM tl_datatable_registry WHERE datatable_name = $1 RETURNING datatable_name", name);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Datatable not found",
                       "error.msg.systemconfig.datatable.not.found");
    co_await txn->execSqlCoro("DROP TABLE IF EXISTS " + tableIdent);
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable", name, "datatable.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> SystemConfigService::requireDatatableColumns(Txn txn,
                                                                       const std::string &name) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT apptable_name, is_multi_row, columns::text AS columns FROM tl_datatable_registry "
        "WHERE datatable_name = $1",
        name);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Datatable not found",
                       "error.msg.systemconfig.datatable.not.found");
    Json::Value out;
    out["apptableName"] = rows[0]["apptable_name"].as<std::string>();
    out["multiRow"] = rows[0]["is_multi_row"].as<bool>();
    out["columns"] = parseJsonOrEmpty(rows[0]["columns"].as<std::string>(), Json::arrayValue);
    co_return out;
}

drogon::Task<Json::Value> SystemConfigService::queryDatatable(const turbo::RequestContext &ctx,
                                                              const std::string &name,
                                                              const Json::Value &filters) {
    // NOTE: filters are applied client-side (post-fetch) rather than folded into a
    // dynamic SQL WHERE clause. Drogon's SqlBinder streaming interface (used to bind a
    // runtime-determined number of parameters) is callback-based only and is not
    // co_await-able, so a single query with N dynamically-bound predicates cannot be
    // expressed through the coroutine execSqlCoro API (which requires the parameter
    // count to be known at compile time). Datatables are tenant-scoped, small,
    // custom-attribute tables, so an in-process filter over the full result set is an
    // acceptable, injection-safe simplification for this ad-hoc query endpoint.
    requirePermission(ctx, "READ_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto reg = co_await requireDatatableColumns(txn, name);

    auto rows = co_await txn->execSqlCoro("SELECT * FROM " + tableIdent);
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        for (size_t i = 0; i < r.size(); ++i) j[r.columnName(i)] = r[i].isNull() ? Json::Value() : r[i].as<std::string>();

        bool matches = true;
        if (filters.isObject()) {
            for (const auto &colName : filters.getMemberNames()) {
                bool known = colName == "apptable_id";
                for (const auto &c : reg["columns"])
                    if (asStringOr(c, "name") == colName) known = true;
                if (!known) continue;
                if (j[colName].asString() != filters[colName].asString()) {
                    matches = false;
                    break;
                }
            }
        }
        if (matches) list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::listDatatableEntries(const turbo::RequestContext &ctx,
                                                                    const std::string &name,
                                                                    const std::string &apptableId) {
    requirePermission(ctx, "READ_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await requireDatatableColumns(txn, name);
    auto rows =
        co_await txn->execSqlCoro("SELECT * FROM " + tableIdent + " WHERE apptable_id = $1", apptableId);
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        for (size_t i = 0; i < r.size(); ++i) j[r.columnName(i)] = r[i].isNull() ? Json::Value() : r[i].as<std::string>();
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::createDatatableEntry(const turbo::RequestContext &ctx,
                                                                    const std::string &name,
                                                                    const std::string &apptableId,
                                                                    const Json::Value &body) {
    requirePermission(ctx, "CREATE_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto reg = co_await requireDatatableColumns(txn, name);

    // Insert the row skeleton first (fixed 1-parameter statement), then set each
    // provided, allowlisted column with its own fixed-arity single-column UPDATE.
    // See queryDatatable() for why a single dynamic-arity INSERT isn't used: Drogon's
    // execSqlCoro requires the parameter count to be known at compile time.
    auto insertRows = co_await txn->execSqlCoro(
        "INSERT INTO " + tableIdent + " (apptable_id) VALUES ($1) RETURNING id::text AS id", apptableId);
    const std::string id = insertRows[0]["id"].as<std::string>();
    for (const auto &c : reg["columns"]) {
        const std::string colName = asStringOr(c, "name");
        if (colName.empty() || !body.isMember(colName)) continue;
        const std::string value =
            body[colName].isString() ? body[colName].asString() : jsonCompact(body[colName]);
        co_await txn->execSqlCoro("UPDATE " + tableIdent + " SET " + turbo::db::quoteIdentifier(colName) +
                                  " = $2" + columnCastSuffix(asStringOr(c, "type", "String")) +
                                  " WHERE id::text = $1",
                                  id, value);
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable." + name, id, "datatableentry.created", body);
    Json::Value out;
    out["resourceId"] = apptableId;
    out["officeId"] = id;
    co_return out;
}

drogon::Task<Json::Value> SystemConfigService::updateDatatableEntry(const turbo::RequestContext &ctx,
                                                                    const std::string &name,
                                                                    const std::string &apptableId,
                                                                    const Json::Value &body) {
    requirePermission(ctx, "UPDATE_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto reg = co_await requireDatatableColumns(txn, name);
    if (reg["multiRow"].asBool())
        throw ApiError(drogon::k400BadRequest,
                       "This datatable is multi-row; update a specific row via its id instead",
                       "error.msg.systemconfig.datatable.multirow");

    // One fixed-arity (2-parameter) single-column UPDATE per provided, allowlisted
    // column — see queryDatatable() for why a single dynamic-arity UPDATE isn't used.
    for (const auto &c : reg["columns"]) {
        const std::string colName = asStringOr(c, "name");
        if (colName.empty() || !body.isMember(colName)) continue;
        const std::string value =
            body[colName].isString() ? body[colName].asString() : jsonCompact(body[colName]);
        co_await txn->execSqlCoro("UPDATE " + tableIdent + " SET " + turbo::db::quoteIdentifier(colName) +
                                  " = $2" + columnCastSuffix(asStringOr(c, "type", "String")) +
                                  " WHERE apptable_id = $1",
                                  apptableId, value);
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable." + name, apptableId,
                                       "datatableentry.updated", body);
    Json::Value out;
    out["resourceId"] = apptableId;
    co_return out;
}

drogon::Task<void> SystemConfigService::deleteDatatableEntries(const turbo::RequestContext &ctx,
                                                               const std::string &name,
                                                               const std::string &apptableId) {
    requirePermission(ctx, "DELETE_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await requireDatatableColumns(txn, name);
    co_await txn->execSqlCoro("DELETE FROM " + tableIdent + " WHERE apptable_id = $1", apptableId);
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable." + name, apptableId,
                                       "datatableentry.deleted", Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> SystemConfigService::getDatatableRow(const turbo::RequestContext &ctx,
                                                               const std::string &name,
                                                               const std::string &apptableId,
                                                               const std::string &rowId) {
    requirePermission(ctx, "READ_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await requireDatatableColumns(txn, name);
    auto rows = co_await txn->execSqlCoro(
        "SELECT * FROM " + tableIdent + " WHERE apptable_id = $1 AND id::text = $2", apptableId, rowId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Datatable row not found",
                       "error.msg.systemconfig.datatable.row.not.found");
    const auto &r = rows[0];
    Json::Value j;
    for (size_t i = 0; i < r.size(); ++i) j[r.columnName(i)] = r[i].isNull() ? Json::Value() : r[i].as<std::string>();
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::updateDatatableRow(const turbo::RequestContext &ctx,
                                                                  const std::string &name,
                                                                  const std::string &apptableId,
                                                                  const std::string &rowId,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "UPDATE_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto reg = co_await requireDatatableColumns(txn, name);

    // One fixed-arity (3-parameter) single-column UPDATE per provided, allowlisted
    // column — see queryDatatable() for why a single dynamic-arity UPDATE isn't used.
    for (const auto &c : reg["columns"]) {
        const std::string colName = asStringOr(c, "name");
        if (colName.empty() || !body.isMember(colName)) continue;
        const std::string value =
            body[colName].isString() ? body[colName].asString() : jsonCompact(body[colName]);
        co_await txn->execSqlCoro("UPDATE " + tableIdent + " SET " + turbo::db::quoteIdentifier(colName) +
                                  " = $3" + columnCastSuffix(asStringOr(c, "type", "String")) +
                                  " WHERE apptable_id = $1 AND id::text = $2",
                                  apptableId, rowId, value);
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable." + name, rowId, "datatableentry.updated",
                                       body);
    co_return co_await getDatatableRow(ctx, name, apptableId, rowId);
}

drogon::Task<void> SystemConfigService::deleteDatatableRow(const turbo::RequestContext &ctx,
                                                           const std::string &name,
                                                           const std::string &apptableId,
                                                           const std::string &rowId) {
    requirePermission(ctx, "DELETE_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await requireDatatableColumns(txn, name);
    auto rows = co_await txn->execSqlCoro(
        "DELETE FROM " + tableIdent + " WHERE apptable_id = $1 AND id::text = $2 RETURNING id",
        apptableId, rowId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Datatable row not found",
                       "error.msg.systemconfig.datatable.row.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable." + name, rowId, "datatableentry.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// entity-datatable checks
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listEntityDatatableChecks(
    const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_ENTITYDATATABLECHECK");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, entity, status_code, datatable_name, product_id "
        "FROM tl_entity_datatable_check ORDER BY entity, status_code");
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["entity"] = r["entity"].as<std::string>();
        j["status"] = r["status_code"].as<std::string>();
        j["datatableName"] = r["datatable_name"].as<std::string>();
        j["productId"] = r["product_id"].isNull() ? "" : r["product_id"].as<std::string>();
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::createEntityDatatableCheck(
    const turbo::RequestContext &ctx, const Json::Value &body) {
    requirePermission(ctx, "CREATE_ENTITYDATATABLECHECK");
    const std::string entity = asStringOr(body, "entity");
    const std::string status = asStringOr(body, "status");
    const std::string datatableName = asStringOr(body, "datatableName");
    if (entity.empty() || status.empty() || datatableName.empty())
        throw ApiError(drogon::k400BadRequest,
                       "'entity', 'status' and 'datatableName' are required",
                       "error.msg.systemconfig.entitydatatablecheck.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO tl_entity_datatable_check (entity, status_code, datatable_name, product_id) "
            "VALUES ($1, $2, $3, NULLIF($4, '')) RETURNING id::text AS id",
            entity, status, datatableName, asStringOr(body, "productId"));
        const std::string id = rows[0]["id"].as<std::string>();
        co_await turbo::outbox::writeEvent(txn, ctx, "entitydatatablecheck", id,
                                           "entitydatatablecheck.created", body);
        Json::Value out;
        out["resourceId"] = id;
        co_return out;
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k409Conflict, "This entity-datatable check already exists",
                       "error.msg.systemconfig.entitydatatablecheck.duplicate");
    }
}

drogon::Task<void> SystemConfigService::deleteEntityDatatableCheck(const turbo::RequestContext &ctx,
                                                                   const std::string &id) {
    requirePermission(ctx, "DELETE_ENTITYDATATABLECHECK");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "DELETE FROM tl_entity_datatable_check WHERE id::text = $1 RETURNING id", id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Entity-datatable check not found",
                       "error.msg.systemconfig.entitydatatablecheck.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "entitydatatablecheck", id,
                                       "entitydatatablecheck.deleted", Json::Value(Json::objectValue));
    co_return;
}

Json::Value SystemConfigService::entityDatatableCheckTemplate(const turbo::RequestContext &) {
    Json::Value out;
    out["entities"] = Json::Value(Json::arrayValue);
    out["statuses"] = Json::Value(Json::arrayValue);
    return out;
}

// ---------------------------------------------------------------------------
// imports
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listImports(const turbo::RequestContext &ctx,
                                                           const std::string &entityType) {
    requirePermission(ctx, "READ_IMPORT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    std::string sql =
        "SELECT id::text AS id, entity_type, file_name, import_time::text AS import_time, "
        "  end_time::text AS end_time, total_records, successful_count, failed_count, status "
        "FROM tl_import_document";
    Json::Value list(Json::arrayValue);
    if (entityType.empty()) {
        auto r = co_await txn->execSqlCoro(sql + " ORDER BY import_time DESC");
        for (const auto &row : r) {
            Json::Value j;
            j["id"] = row["id"].as<std::string>();
            j["entityType"] = row["entity_type"].as<std::string>();
            j["fileName"] = row["file_name"].as<std::string>();
            j["importTime"] = row["import_time"].as<std::string>();
            j["endTime"] = row["end_time"].isNull() ? "" : row["end_time"].as<std::string>();
            j["totalRecords"] = row["total_records"].as<int>();
            j["successCount"] = row["successful_count"].as<int>();
            j["failureCount"] = row["failed_count"].as<int>();
            j["status"] = row["status"].as<std::string>();
            list.append(j);
        }
        co_return list;
    }
    auto r = co_await txn->execSqlCoro(sql + " WHERE entity_type = $1 ORDER BY import_time DESC",
                                       entityType);
    for (const auto &row : r) {
        Json::Value j;
        j["id"] = row["id"].as<std::string>();
        j["entityType"] = row["entity_type"].as<std::string>();
        j["fileName"] = row["file_name"].as<std::string>();
        j["importTime"] = row["import_time"].as<std::string>();
        j["endTime"] = row["end_time"].isNull() ? "" : row["end_time"].as<std::string>();
        j["totalRecords"] = row["total_records"].as<int>();
        j["successCount"] = row["successful_count"].as<int>();
        j["failureCount"] = row["failed_count"].as<int>();
        j["status"] = row["status"].as<std::string>();
        list.append(j);
    }
    co_return list;
}

Json::Value SystemConfigService::importOutputTemplateLocation(const turbo::RequestContext &) {
    Json::Value out;
    out["outputTemplateLocation"] = "not-implemented";
    return out;
}

// ---------------------------------------------------------------------------
// generic entity: documents
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::documentToJson(Txn txn, const std::string &id,
                                                              bool includeContent) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, entity_type, entity_id, name, file_name, content_type, description, "
        "  size_bytes, encode(content, 'base64') AS content_b64, created_by, "
        "  created_at::text AS created_at "
        "FROM tl_document WHERE id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Document not found",
                       "error.msg.systemconfig.document.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["parentEntityType"] = r["entity_type"].as<std::string>();
    j["parentEntityId"] = r["entity_id"].as<std::string>();
    j["name"] = r["name"].as<std::string>();
    j["fileName"] = r["file_name"].as<std::string>();
    j["type"] = r["content_type"].isNull() ? "" : r["content_type"].as<std::string>();
    j["description"] = r["description"].isNull() ? "" : r["description"].as<std::string>();
    j["size"] = r["size_bytes"].as<int64_t>();
    if (includeContent) j["content"] = r["content_b64"].isNull() ? "" : r["content_b64"].as<std::string>();
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::listDocuments(const turbo::RequestContext &ctx,
                                                             const std::string &entityType,
                                                             const std::string &entityId) {
    requirePermission(ctx, "READ_DOCUMENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id FROM tl_document WHERE entity_type = $1 AND entity_id = $2 "
        "ORDER BY created_at",
        entityType, entityId);
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(co_await documentToJson(txn, r["id"].as<std::string>(), false));
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getDocument(const turbo::RequestContext &ctx,
                                                           const std::string &entityType,
                                                           const std::string &entityId,
                                                           const std::string &documentId) {
    requirePermission(ctx, "READ_DOCUMENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    (void)entityType;
    (void)entityId;
    co_return co_await documentToJson(txn, documentId, false);
}

drogon::Task<Json::Value> SystemConfigService::createDocument(const turbo::RequestContext &ctx,
                                                              const std::string &entityType,
                                                              const std::string &entityId,
                                                              const Json::Value &body) {
    requirePermission(ctx, "CREATE_DOCUMENT");
    const std::string fileName = asStringOr(body, "fileName");
    if (fileName.empty())
        throw ApiError(drogon::k400BadRequest, "'fileName' is required",
                       "error.msg.systemconfig.document.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO tl_document (entity_type, entity_id, name, file_name, content_type, description, "
        "  size_bytes, content, created_by) "
        "VALUES ($1, $2, $3, $4, NULLIF($5, ''), NULLIF($6, ''), $7, decode(NULLIF($8, ''), 'base64'), "
        "  $9) RETURNING id::text AS id",
        entityType, entityId, asStringOr(body, "name", fileName), fileName,
        asStringOr(body, "contentType"), asStringOr(body, "description"),
        static_cast<int64_t>(asStringOr(body, "content").size() / 4 * 3), asStringOr(body, "content"),
        ctx.username);
    const std::string id = rows[0]["id"].as<std::string>();
    co_await turbo::outbox::writeEvent(txn, ctx, "document", id, "document.created", body);
    co_return co_await documentToJson(txn, id, false);
}

drogon::Task<Json::Value> SystemConfigService::updateDocument(const turbo::RequestContext &ctx,
                                                              const std::string &entityType,
                                                              const std::string &entityId,
                                                              const std::string &documentId,
                                                              const Json::Value &body) {
    requirePermission(ctx, "UPDATE_DOCUMENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await documentToJson(txn, documentId, false);
    (void)entityType;
    (void)entityId;
    if (body.isMember("content")) {
        co_await txn->execSqlCoro(
            "UPDATE tl_document SET name = COALESCE(NULLIF($2, ''), name), "
            "  file_name = COALESCE(NULLIF($3, ''), file_name), "
            "  content_type = COALESCE(NULLIF($4, ''), content_type), "
            "  description = COALESCE(NULLIF($5, ''), description), "
            "  content = decode($6, 'base64') WHERE id::text = $1",
            documentId, asStringOr(body, "name"), asStringOr(body, "fileName"),
            asStringOr(body, "contentType"), asStringOr(body, "description"),
            asStringOr(body, "content"));
    } else {
        co_await txn->execSqlCoro(
            "UPDATE tl_document SET name = COALESCE(NULLIF($2, ''), name), "
            "  description = COALESCE(NULLIF($3, ''), description) WHERE id::text = $1",
            documentId, asStringOr(body, "name"), asStringOr(body, "description"));
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "document", documentId, "document.updated", body);
    co_return co_await documentToJson(txn, documentId, false);
}

drogon::Task<void> SystemConfigService::deleteDocument(const turbo::RequestContext &ctx,
                                                       const std::string &entityType,
                                                       const std::string &entityId,
                                                       const std::string &documentId) {
    requirePermission(ctx, "DELETE_DOCUMENT");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows =
        co_await txn->execSqlCoro("DELETE FROM tl_document WHERE id::text = $1 RETURNING id", documentId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Document not found",
                       "error.msg.systemconfig.document.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "document", documentId, "document.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> SystemConfigService::getDocumentContent(const turbo::RequestContext &ctx,
                                                                  const std::string &entityType,
                                                                  const std::string &entityId,
                                                                  const std::string &documentId) {
    requirePermission(ctx, "READ_DOCUMENT");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await documentToJson(txn, documentId, true);
}

// ---------------------------------------------------------------------------
// generic entity: notes
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::noteToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, resource_type, resource_id, note, created_by, "
        "  created_at::text AS created_at FROM tl_note WHERE id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Note not found", "error.msg.systemconfig.note.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["resourceType"] = r["resource_type"].as<std::string>();
    j["resourceId"] = r["resource_id"].as<std::string>();
    j["note"] = r["note"].as<std::string>();
    j["createdByUsername"] = r["created_by"].isNull() ? "" : r["created_by"].as<std::string>();
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::listNotes(const turbo::RequestContext &ctx,
                                                         const std::string &resourceType,
                                                         const std::string &resourceId) {
    requirePermission(ctx, "READ_NOTE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id FROM tl_note WHERE resource_type = $1 AND resource_id = $2 "
        "ORDER BY created_at DESC",
        resourceType, resourceId);
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(co_await noteToJson(txn, r["id"].as<std::string>()));
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getNote(const turbo::RequestContext &ctx,
                                                       const std::string &resourceType,
                                                       const std::string &resourceId,
                                                       const std::string &noteId) {
    requirePermission(ctx, "READ_NOTE");
    (void)resourceType;
    (void)resourceId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await noteToJson(txn, noteId);
}

drogon::Task<Json::Value> SystemConfigService::createNote(const turbo::RequestContext &ctx,
                                                          const std::string &resourceType,
                                                          const std::string &resourceId,
                                                          const Json::Value &body) {
    requirePermission(ctx, "CREATE_NOTE");
    const std::string note = asStringOr(body, "note");
    if (note.empty())
        throw ApiError(drogon::k400BadRequest, "'note' is required",
                       "error.msg.systemconfig.note.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO tl_note (resource_type, resource_id, note, created_by) VALUES ($1, $2, $3, $4) "
        "RETURNING id::text AS id",
        resourceType, resourceId, note, ctx.username);
    const std::string id = rows[0]["id"].as<std::string>();
    co_await turbo::outbox::writeEvent(txn, ctx, "note", id, "note.created", body);
    co_return co_await noteToJson(txn, id);
}

drogon::Task<Json::Value> SystemConfigService::updateNote(const turbo::RequestContext &ctx,
                                                          const std::string &resourceType,
                                                          const std::string &resourceId,
                                                          const std::string &noteId,
                                                          const Json::Value &body) {
    requirePermission(ctx, "UPDATE_NOTE");
    (void)resourceType;
    (void)resourceId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await noteToJson(txn, noteId);
    co_await txn->execSqlCoro(
        "UPDATE tl_note SET note = $2, modified_at = now() WHERE id::text = $1", noteId,
        asStringOr(body, "note"));
    co_await turbo::outbox::writeEvent(txn, ctx, "note", noteId, "note.updated", body);
    co_return co_await noteToJson(txn, noteId);
}

drogon::Task<void> SystemConfigService::deleteNote(const turbo::RequestContext &ctx,
                                                  const std::string &resourceType,
                                                  const std::string &resourceId,
                                                  const std::string &noteId) {
    requirePermission(ctx, "DELETE_NOTE");
    (void)resourceType;
    (void)resourceId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro("DELETE FROM tl_note WHERE id::text = $1 RETURNING id", noteId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Note not found", "error.msg.systemconfig.note.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "note", noteId, "note.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// generic entity: images (singleton per entity)
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::getImage(const turbo::RequestContext &ctx,
                                                        const std::string &entity,
                                                        const std::string &entityId) {
    requirePermission(ctx, "READ_IMAGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT content_type, encode(content, 'base64') AS content_b64, modified_at::text AS modified_at "
        "FROM tl_image WHERE entity_type = $1 AND entity_id = $2",
        entity, entityId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Image not found", "error.msg.systemconfig.image.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["entityType"] = entity;
    j["entityId"] = entityId;
    j["contentType"] = r["content_type"].isNull() ? "" : r["content_type"].as<std::string>();
    j["content"] = r["content_b64"].isNull() ? "" : r["content_b64"].as<std::string>();
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::putImage(const turbo::RequestContext &ctx,
                                                        const std::string &entity,
                                                        const std::string &entityId,
                                                        const Json::Value &body) {
    requirePermission(ctx, "CREATE_IMAGE");
    const std::string content = asStringOr(body, "content");
    if (content.empty())
        throw ApiError(drogon::k400BadRequest, "'content' (base64) is required",
                       "error.msg.systemconfig.image.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await txn->execSqlCoro(
        "INSERT INTO tl_image (entity_type, entity_id, content_type, content, modified_at) "
        "VALUES ($1, $2, NULLIF($3, ''), decode($4, 'base64'), now()) "
        "ON CONFLICT (entity_type, entity_id) DO UPDATE SET "
        "  content_type = EXCLUDED.content_type, content = EXCLUDED.content, modified_at = now()",
        entity, entityId, asStringOr(body, "contentType"), content);
    co_await turbo::outbox::writeEvent(txn, ctx, "image", entity + ":" + entityId, "image.updated",
                                       Json::Value(Json::objectValue));
    Json::Value out;
    out["resourceId"] = entityId;
    co_return out;
}

drogon::Task<void> SystemConfigService::deleteImage(const turbo::RequestContext &ctx,
                                                   const std::string &entity,
                                                   const std::string &entityId) {
    requirePermission(ctx, "DELETE_IMAGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "DELETE FROM tl_image WHERE entity_type = $1 AND entity_id = $2 RETURNING entity_id", entity,
        entityId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Image not found", "error.msg.systemconfig.image.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "image", entity + ":" + entityId, "image.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// generic entity: calendars
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::calendarToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, entity_type, entity_id, title, description, location, "
        "  start_date::text AS start_date, end_date::text AS end_date, calendar_type, recurrence, "
        "  remind_by_days FROM tl_calendar WHERE id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Calendar not found",
                       "error.msg.systemconfig.calendar.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["entityType"] = r["entity_type"].as<std::string>();
    j["entityId"] = r["entity_id"].as<std::string>();
    j["title"] = r["title"].as<std::string>();
    j["description"] = r["description"].isNull() ? "" : r["description"].as<std::string>();
    j["location"] = r["location"].isNull() ? "" : r["location"].as<std::string>();
    j["startDate"] = r["start_date"].as<std::string>();
    j["endDate"] = r["end_date"].isNull() ? "" : r["end_date"].as<std::string>();
    j["calendarType"] = r["calendar_type"].as<std::string>();
    j["recurrence"] = r["recurrence"].isNull() ? "" : r["recurrence"].as<std::string>();
    j["remindByDays"] = r["remind_by_days"].isNull() ? 0 : r["remind_by_days"].as<int>();
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::listCalendars(const turbo::RequestContext &ctx,
                                                             const std::string &entityType,
                                                             const std::string &entityId) {
    requirePermission(ctx, "READ_CALENDAR");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id FROM tl_calendar WHERE entity_type = $1 AND entity_id = $2 "
        "ORDER BY start_date",
        entityType, entityId);
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(co_await calendarToJson(txn, r["id"].as<std::string>()));
    co_return list;
}

Json::Value SystemConfigService::calendarTemplate(const turbo::RequestContext &) {
    Json::Value out;
    out["calendarTypeOptions"] = Json::Value(Json::arrayValue);
    return out;
}

drogon::Task<Json::Value> SystemConfigService::getCalendar(const turbo::RequestContext &ctx,
                                                           const std::string &entityType,
                                                           const std::string &entityId,
                                                           const std::string &calendarId) {
    requirePermission(ctx, "READ_CALENDAR");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await calendarToJson(txn, calendarId);
}

drogon::Task<Json::Value> SystemConfigService::createCalendar(const turbo::RequestContext &ctx,
                                                              const std::string &entityType,
                                                              const std::string &entityId,
                                                              const Json::Value &body) {
    requirePermission(ctx, "CREATE_CALENDAR");
    const std::string title = asStringOr(body, "title");
    const std::string startDate = asStringOr(body, "startDate");
    if (title.empty() || startDate.empty())
        throw ApiError(drogon::k400BadRequest, "'title' and 'startDate' are required",
                       "error.msg.systemconfig.calendar.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO tl_calendar (entity_type, entity_id, title, description, location, start_date, "
        "  end_date, calendar_type, recurrence, remind_by_days) "
        "VALUES ($1, $2, $3, NULLIF($4, ''), NULLIF($5, ''), $6::date, NULLIF($7, '')::date, "
        "  COALESCE(NULLIF($8, ''), 'COLLECTION'), NULLIF($9, ''), NULLIF($10, '')::int) "
        "RETURNING id::text AS id",
        entityType, entityId, title, asStringOr(body, "description"), asStringOr(body, "location"),
        startDate, asStringOr(body, "endDate"), asStringOr(body, "calendarType"),
        asStringOr(body, "recurrence"), asStringOr(body, "remindByDays"));
    const std::string id = rows[0]["id"].as<std::string>();
    co_await turbo::outbox::writeEvent(txn, ctx, "calendar", id, "calendar.created", body);
    co_return co_await calendarToJson(txn, id);
}

drogon::Task<Json::Value> SystemConfigService::updateCalendar(const turbo::RequestContext &ctx,
                                                              const std::string &entityType,
                                                              const std::string &entityId,
                                                              const std::string &calendarId,
                                                              const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CALENDAR");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await calendarToJson(txn, calendarId);
    co_await txn->execSqlCoro(
        "UPDATE tl_calendar SET title = COALESCE(NULLIF($2, ''), title), "
        "  description = COALESCE(NULLIF($3, ''), description), "
        "  location = COALESCE(NULLIF($4, ''), location), "
        "  start_date = COALESCE(NULLIF($5, '')::date, start_date), "
        "  end_date = COALESCE(NULLIF($6, '')::date, end_date), "
        "  calendar_type = COALESCE(NULLIF($7, ''), calendar_type), "
        "  recurrence = COALESCE(NULLIF($8, ''), recurrence), "
        "  remind_by_days = COALESCE(NULLIF($9, '')::int, remind_by_days), modified_at = now() "
        "WHERE id::text = $1",
        calendarId, asStringOr(body, "title"), asStringOr(body, "description"),
        asStringOr(body, "location"), asStringOr(body, "startDate"), asStringOr(body, "endDate"),
        asStringOr(body, "calendarType"), asStringOr(body, "recurrence"),
        asStringOr(body, "remindByDays"));
    co_await turbo::outbox::writeEvent(txn, ctx, "calendar", calendarId, "calendar.updated", body);
    co_return co_await calendarToJson(txn, calendarId);
}

drogon::Task<void> SystemConfigService::deleteCalendar(const turbo::RequestContext &ctx,
                                                      const std::string &entityType,
                                                      const std::string &entityId,
                                                      const std::string &calendarId) {
    requirePermission(ctx, "DELETE_CALENDAR");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro("DELETE FROM tl_calendar WHERE id::text = $1 RETURNING id",
                                          calendarId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Calendar not found",
                       "error.msg.systemconfig.calendar.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "calendar", calendarId, "calendar.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// generic entity: meetings
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::meetingToJson(Txn txn, const std::string &id) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, entity_type, entity_id, calendar_id::text AS calendar_id, "
        "  meeting_date::text AS meeting_date, notes, status FROM tl_meeting WHERE id::text = $1",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Meeting not found",
                       "error.msg.systemconfig.meeting.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["entityType"] = r["entity_type"].as<std::string>();
    j["entityId"] = r["entity_id"].as<std::string>();
    j["calendarId"] = r["calendar_id"].isNull() ? "" : r["calendar_id"].as<std::string>();
    j["meetingDate"] = r["meeting_date"].as<std::string>();
    j["notes"] = r["notes"].isNull() ? "" : r["notes"].as<std::string>();
    j["status"] = r["status"].as<std::string>();
    co_return j;
}

drogon::Task<Json::Value> SystemConfigService::listMeetings(const turbo::RequestContext &ctx,
                                                            const std::string &entityType,
                                                            const std::string &entityId) {
    requirePermission(ctx, "READ_MEETING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id FROM tl_meeting WHERE entity_type = $1 AND entity_id = $2 "
        "ORDER BY meeting_date DESC",
        entityType, entityId);
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(co_await meetingToJson(txn, r["id"].as<std::string>()));
    co_return list;
}

Json::Value SystemConfigService::meetingTemplate(const turbo::RequestContext &) {
    Json::Value out;
    out["statusOptions"] = Json::Value(Json::arrayValue);
    return out;
}

drogon::Task<Json::Value> SystemConfigService::getMeeting(const turbo::RequestContext &ctx,
                                                          const std::string &entityType,
                                                          const std::string &entityId,
                                                          const std::string &meetingId) {
    requirePermission(ctx, "READ_MEETING");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await meetingToJson(txn, meetingId);
}

drogon::Task<Json::Value> SystemConfigService::createMeeting(const turbo::RequestContext &ctx,
                                                             const std::string &entityType,
                                                             const std::string &entityId,
                                                             const Json::Value &body) {
    requirePermission(ctx, "CREATE_MEETING");
    const std::string meetingDate = asStringOr(body, "meetingDate");
    if (meetingDate.empty())
        throw ApiError(drogon::k400BadRequest, "'meetingDate' is required",
                       "error.msg.systemconfig.meeting.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await txn->execSqlCoro(
        "INSERT INTO tl_meeting (entity_type, entity_id, calendar_id, meeting_date, notes, status) "
        "VALUES ($1, $2, NULLIF($3, '')::uuid, $4::date, NULLIF($5, ''), "
        "  COALESCE(NULLIF($6, ''), 'SCHEDULED')) RETURNING id::text AS id",
        entityType, entityId, asStringOr(body, "calendarId"), meetingDate, asStringOr(body, "notes"),
        asStringOr(body, "status"));
    const std::string id = rows[0]["id"].as<std::string>();
    co_await turbo::outbox::writeEvent(txn, ctx, "meeting", id, "meeting.created", body);
    co_return co_await meetingToJson(txn, id);
}

drogon::Task<Json::Value> SystemConfigService::updateMeeting(const turbo::RequestContext &ctx,
                                                             const std::string &entityType,
                                                             const std::string &entityId,
                                                             const std::string &meetingId,
                                                             const Json::Value &body) {
    requirePermission(ctx, "UPDATE_MEETING");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await meetingToJson(txn, meetingId);
    co_await txn->execSqlCoro(
        "UPDATE tl_meeting SET meeting_date = COALESCE(NULLIF($2, '')::date, meeting_date), "
        "  notes = COALESCE(NULLIF($3, ''), notes), status = COALESCE(NULLIF($4, ''), status), "
        "  modified_at = now() WHERE id::text = $1",
        meetingId, asStringOr(body, "meetingDate"), asStringOr(body, "notes"),
        asStringOr(body, "status"));
    co_await turbo::outbox::writeEvent(txn, ctx, "meeting", meetingId, "meeting.updated", body);
    co_return co_await meetingToJson(txn, meetingId);
}

drogon::Task<void> SystemConfigService::deleteMeeting(const turbo::RequestContext &ctx,
                                                     const std::string &entityType,
                                                     const std::string &entityId,
                                                     const std::string &meetingId) {
    requirePermission(ctx, "DELETE_MEETING");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows =
        co_await txn->execSqlCoro("DELETE FROM tl_meeting WHERE id::text = $1 RETURNING id", meetingId);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Meeting not found",
                       "error.msg.systemconfig.meeting.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "meeting", meetingId, "meeting.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> SystemConfigService::meetingCommand(const turbo::RequestContext &ctx,
                                                              const std::string &entityType,
                                                              const std::string &entityId,
                                                              const std::string &meetingId,
                                                              const std::string &command,
                                                              const Json::Value &body) {
    requirePermission(ctx, "UPDATE_MEETING");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_await meetingToJson(txn, meetingId);
    std::string newStatus;
    if (command == "held" || command == "close")
        newStatus = "HELD";
    else if (command == "cancel" || command == "cancelled")
        newStatus = "CANCELLED";
    else if (command == "reschedule" || command == "schedule")
        newStatus = "SCHEDULED";
    else
        throw ApiError(drogon::k400BadRequest, "Unsupported meeting command: " + command,
                       "error.msg.systemconfig.meeting.command.unsupported");
    co_await txn->execSqlCoro("UPDATE tl_meeting SET status = $2, modified_at = now() WHERE id::text = $1",
                              meetingId, newStatus);
    co_await turbo::outbox::writeEvent(txn, ctx, "meeting", meetingId, "meeting." + command, body);
    co_return co_await meetingToJson(txn, meetingId);
}

}  // namespace turbo_ledger_systemconfig
