#include "SystemConfigService.h"

#include <drogon/orm/CoroMapper.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Exception.h>

#include <sstream>

#include "turbo/Outbox.h"
#include "turbo/TenantDb.h"

#include "models/BusinessDate.h"
#include "models/CacheConfig.h"
#include "models/Code.h"
#include "models/CodeValue.h"
#include "models/Configuration.h"
#include "models/ExternalEventConfiguration.h"
#include "models/ExternalService.h"
#include "models/FieldConfiguration.h"
#include "models/Hook.h"
#include "models/TlCalendar.h"
#include "models/TlDatatableRegistry.h"
#include "models/TlDocument.h"
#include "models/TlEntityDatatableCheck.h"
#include "models/TlImage.h"
#include "models/TlImportDocument.h"
#include "models/TlMeeting.h"
#include "models/TlNote.h"
#include "models/TlOutbox.h"

using drogon::orm::CompareOperator;
using drogon::orm::Criteria;
using drogon::orm::DrogonDbException;
using drogon::orm::UnexpectedRows;
using trantor::Date;

namespace m = drogon_model::TlSystemConfigDb;
template <typename T>
using Mapper = drogon::orm::CoroMapper<T>;

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

/// Parse a "YYYY-MM-DD" (or full timestamp) string into a trantor::Date, or
/// return `fallback` if the string is empty / unparsable.
Date dateOr(const std::string &text, const Date &fallback) {
    if (text.empty()) return fallback;
    try {
        return Date::fromDbStringLocal(text);
    } catch (...) {
        return fallback;
    }
}

/// Render a trantor::Date as a plain "YYYY-MM-DD" / "YYYY-MM-DD HH:MM:SS" string.
std::string dateStr(const Date &d) { return d.toDbStringLocal(); }

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

// ---------------------------------------------------------------------------
// <Model> -> API-shaped Json::Value mapping helpers.
//
// These are plain, synchronous functions (no DB access): drogon_ctl's own
// Model::toJson() emits raw snake_case column names, which isn't the
// camelCase shape this API has always returned, so we keep small explicit
// mappers here instead of using it directly.
// ---------------------------------------------------------------------------

Json::Value codeJson(const m::Code &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["name"] = r.getValueOfCodeName();
    j["systemDefined"] = r.getValueOfIsSystemDefined();
    return j;
}

Json::Value codeValueJson(const m::CodeValue &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["codeId"] = r.getValueOfCodeId();
    j["name"] = r.getValueOfCodeValue();
    j["description"] = r.getValueOfCodeDescription();
    j["position"] = r.getValueOfOrderPosition();
    j["isActive"] = r.getValueOfIsActive();
    j["isMandatory"] = r.getValueOfIsMandatory();
    return j;
}

Json::Value configurationJson(const m::Configuration &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["name"] = r.getValueOfName();
    j["value"] = r.getValueOfValue();
    j["dateValue"] = r.getDateValue() ? dateStr(r.getValueOfDateValue()) : "";
    j["enabled"] = r.getValueOfIsEnabled();
    j["description"] = r.getValueOfDescription();
    return j;
}

Json::Value hookJson(const m::Hook &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["name"] = r.getValueOfName();
    j["displayName"] = r.getValueOfDisplayName();
    j["isActive"] = r.getValueOfIsActive();
    j["config"] = parseJsonOrEmpty(r.getValueOfConfig(), Json::objectValue);
    j["events"] = parseJsonOrEmpty(r.getValueOfEvents(), Json::arrayValue);
    return j;
}

Json::Value datatableJson(const m::TlDatatableRegistry &r) {
    Json::Value j;
    j["registeredTableName"] = r.getValueOfDatatableName();
    j["applicationTableName"] = r.getValueOfApptableName();
    j["category"] = r.getValueOfCategory();
    j["multiRow"] = r.getValueOfIsMultiRow();
    j["columnHeaderData"] = parseJsonOrEmpty(r.getValueOfColumns(), Json::arrayValue);
    return j;
}

Json::Value entityDatatableCheckJson(const m::TlEntityDatatableCheck &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["entity"] = r.getValueOfEntity();
    j["status"] = r.getValueOfStatusCode();
    j["datatableName"] = r.getValueOfDatatableName();
    j["productId"] = r.getProductId() ? r.getValueOfProductId() : "";
    return j;
}

Json::Value importJson(const m::TlImportDocument &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["entityType"] = r.getValueOfEntityType();
    j["fileName"] = r.getValueOfFileName();
    j["importTime"] = dateStr(r.getValueOfImportTime());
    j["endTime"] = r.getEndTime() ? dateStr(r.getValueOfEndTime()) : "";
    j["totalRecords"] = r.getValueOfTotalRecords();
    j["successCount"] = r.getValueOfSuccessfulCount();
    j["failureCount"] = r.getValueOfFailedCount();
    j["status"] = r.getValueOfStatus();
    return j;
}

Json::Value documentJson(const m::TlDocument &r, bool includeContent) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["parentEntityType"] = r.getValueOfEntityType();
    j["parentEntityId"] = r.getValueOfEntityId();
    j["name"] = r.getValueOfName();
    j["fileName"] = r.getValueOfFileName();
    j["type"] = r.getContentType() ? r.getValueOfContentType() : "";
    j["description"] = r.getDescription() ? r.getValueOfDescription() : "";
    j["size"] = static_cast<Json::Int64>(r.getValueOfSizeBytes());
    if (includeContent) {
        const auto &bytes = r.getValueOfContent();
        j["content"] = drogon::utils::base64Encode(
            reinterpret_cast<const unsigned char *>(bytes.data()), bytes.size());
    }
    return j;
}

Json::Value noteJson(const m::TlNote &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["resourceType"] = r.getValueOfResourceType();
    j["resourceId"] = r.getValueOfResourceId();
    j["note"] = r.getValueOfNote();
    j["createdByUsername"] = r.getCreatedBy() ? r.getValueOfCreatedBy() : "";
    return j;
}

Json::Value calendarJson(const m::TlCalendar &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["entityType"] = r.getValueOfEntityType();
    j["entityId"] = r.getValueOfEntityId();
    j["title"] = r.getValueOfTitle();
    j["description"] = r.getDescription() ? r.getValueOfDescription() : "";
    j["location"] = r.getLocation() ? r.getValueOfLocation() : "";
    j["startDate"] = dateStr(r.getValueOfStartDate());
    j["endDate"] = r.getEndDate() ? dateStr(r.getValueOfEndDate()) : "";
    j["calendarType"] = r.getValueOfCalendarType();
    j["recurrence"] = r.getRecurrence() ? r.getValueOfRecurrence() : "";
    j["remindByDays"] = r.getRemindByDays() ? r.getValueOfRemindByDays() : 0;
    return j;
}

Json::Value meetingJson(const m::TlMeeting &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["entityType"] = r.getValueOfEntityType();
    j["entityId"] = r.getValueOfEntityId();
    j["calendarId"] = r.getCalendarId() ? r.getValueOfCalendarId() : "";
    j["meetingDate"] = dateStr(r.getValueOfMeetingDate());
    j["notes"] = r.getNotes() ? r.getValueOfNotes() : "";
    j["status"] = r.getValueOfStatus();
    return j;
}

Json::Value auditJson(const m::TlOutbox &r) {
    Json::Value j;
    j["id"] = r.getValueOfId();
    j["resourceType"] = r.getValueOfAggregateType();
    j["resourceId"] = r.getValueOfAggregateId();
    j["actionName"] = r.getValueOfEventType();
    j["maker"] = r.getActorUserId() ? r.getValueOfActorUserId() : "";
    j["madeOnDate"] = dateStr(r.getValueOfOccurredAt());
    return j;
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

drogon::Task<Json::Value> SystemConfigService::listCodes(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CODE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Code>(txn).orderBy(m::Code::Cols::_code_name).findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(codeJson(r));
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getCode(const turbo::RequestContext &ctx,
                                                       const std::string &id) {
    requirePermission(ctx, "READ_CODE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return codeJson(co_await Mapper<m::Code>(txn).findByPrimaryKey(id));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Code not found", "error.msg.systemconfig.code.not.found");
    }
}

drogon::Task<Json::Value> SystemConfigService::getCodeByName(const turbo::RequestContext &ctx,
                                                             const std::string &name) {
    requirePermission(ctx, "READ_CODE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto row = co_await Mapper<m::Code>(txn).findOne(Criteria(m::Code::Cols::_code_name, name));
        co_return codeJson(row);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Code not found", "error.msg.systemconfig.code.not.found");
    }
}

drogon::Task<Json::Value> SystemConfigService::createCode(const turbo::RequestContext &ctx,
                                                          const Json::Value &body) {
    requirePermission(ctx, "CREATE_CODE");
    const std::string name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "'name' is required",
                       "error.msg.systemconfig.code.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::Code row;
    row.setCodeName(name);
    row.setIsSystemDefined(false);
    try {
        auto inserted = co_await Mapper<m::Code>(txn).insert(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "code", inserted.getValueOfId(), "code.created",
                                           body);
        co_return codeJson(inserted);
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
    Mapper<m::Code> mapper(txn);
    m::Code row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Code not found or is system-defined",
                       "error.msg.systemconfig.code.not.found");
    }
    if (row.getValueOfIsSystemDefined())
        throw ApiError(drogon::k404NotFound, "Code not found or is system-defined",
                       "error.msg.systemconfig.code.not.found");
    if (!asStringOr(body, "name").empty()) row.setCodeName(asStringOr(body, "name"));
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "code", id, "code.updated", body);
    co_return codeJson(row);
}

drogon::Task<void> SystemConfigService::deleteCode(const turbo::RequestContext &ctx,
                                                   const std::string &id) {
    requirePermission(ctx, "DELETE_CODE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Code> mapper(txn);
    m::Code row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Code not found", "error.msg.systemconfig.code.not.found");
    }
    if (row.getValueOfIsSystemDefined())
        throw ApiError(drogon::k403Forbidden, "System-defined codes cannot be deleted",
                       "error.msg.systemconfig.code.protected");
    co_await Mapper<m::CodeValue>(txn).deleteBy(Criteria(m::CodeValue::Cols::_code_id, id));
    co_await mapper.deleteOne(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "code", id, "code.deleted", Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> SystemConfigService::listCodeValues(const turbo::RequestContext &ctx,
                                                              const std::string &codeId) {
    requirePermission(ctx, "READ_CODEVALUE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::CodeValue>(txn)
                    .orderBy(m::CodeValue::Cols::_order_position)
                    .orderBy(m::CodeValue::Cols::_code_value)
                    .findBy(Criteria(m::CodeValue::Cols::_code_id, codeId));
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(codeValueJson(r));
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getCodeValue(const turbo::RequestContext &ctx,
                                                            const std::string &codeId,
                                                            const std::string &valueId) {
    requirePermission(ctx, "READ_CODEVALUE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    (void)codeId;
    try {
        co_return codeValueJson(co_await Mapper<m::CodeValue>(txn).findByPrimaryKey(valueId));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Code value not found",
                       "error.msg.systemconfig.codevalue.not.found");
    }
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
    try {
        co_await Mapper<m::Code>(txn).findByPrimaryKey(codeId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k400BadRequest, "Unknown codeId: " + codeId,
                       "error.msg.systemconfig.code.not.found");
    }
    m::CodeValue row;
    row.setCodeId(codeId);
    row.setCodeValue(name);
    row.setCodeDescription(asStringOr(body, "description"));
    row.setOrderPosition(asIntOr(body, "position", 0));
    row.setIsActive(asBoolOr(body, "isActive", true));
    row.setIsMandatory(asBoolOr(body, "isMandatory", false));
    try {
        auto inserted = co_await Mapper<m::CodeValue>(txn).insert(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "codevalue", inserted.getValueOfId(),
                                           "codevalue.created", body);
        co_return codeValueJson(inserted);
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
    Mapper<m::CodeValue> mapper(txn);
    m::CodeValue row;
    try {
        row = co_await mapper.findByPrimaryKey(valueId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Code value not found",
                       "error.msg.systemconfig.codevalue.not.found");
    }
    if (!asStringOr(body, "name").empty()) row.setCodeValue(asStringOr(body, "name"));
    if (!asStringOr(body, "description").empty()) row.setCodeDescription(asStringOr(body, "description"));
    if (asIntOr(body, "position", 0) != 0) row.setOrderPosition(asIntOr(body, "position", 0));
    if (body.isMember("isActive")) row.setIsActive(asBoolOr(body, "isActive", true));
    if (body.isMember("isMandatory")) row.setIsMandatory(asBoolOr(body, "isMandatory", false));
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "codevalue", valueId, "codevalue.updated", body);
    co_return codeValueJson(row);
}

drogon::Task<void> SystemConfigService::deleteCodeValue(const turbo::RequestContext &ctx,
                                                        const std::string &codeId,
                                                        const std::string &valueId) {
    requirePermission(ctx, "DELETE_CODEVALUE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    (void)codeId;
    auto affected = co_await Mapper<m::CodeValue>(txn).deleteByPrimaryKey(valueId);
    if (affected == 0)
        throw ApiError(drogon::k404NotFound, "Code value not found",
                       "error.msg.systemconfig.codevalue.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "codevalue", valueId, "codevalue.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// global configuration
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listConfigurations(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_CONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Configuration>(txn).orderBy(m::Configuration::Cols::_name).findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(configurationJson(r));
    Json::Value out;
    out["globalConfiguration"] = list;
    co_return out;
}

drogon::Task<Json::Value> SystemConfigService::getConfiguration(const turbo::RequestContext &ctx,
                                                                const std::string &id) {
    requirePermission(ctx, "READ_CONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return configurationJson(co_await Mapper<m::Configuration>(txn).findByPrimaryKey(id));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Configuration not found",
                       "error.msg.systemconfig.configuration.not.found");
    }
}

drogon::Task<Json::Value> SystemConfigService::getConfigurationByName(const turbo::RequestContext &ctx,
                                                                     const std::string &name) {
    requirePermission(ctx, "READ_CONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto row = co_await Mapper<m::Configuration>(txn).findOne(
            Criteria(m::Configuration::Cols::_name, name));
        co_return configurationJson(row);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Configuration not found",
                       "error.msg.systemconfig.configuration.not.found");
    }
}

drogon::Task<Json::Value> SystemConfigService::updateConfiguration(const turbo::RequestContext &ctx,
                                                                  const std::string &id,
                                                                  const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Configuration> mapper(txn);
    m::Configuration row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Configuration not found",
                       "error.msg.systemconfig.configuration.not.found");
    }
    if (!asStringOr(body, "value").empty()) row.setValue(asStringOr(body, "value"));
    if (!asStringOr(body, "dateValue").empty())
        row.setDateValue(dateOr(asStringOr(body, "dateValue"), Date()));
    if (body.isMember("enabled")) row.setIsEnabled(asBoolOr(body, "enabled", false));
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "configuration", id, "configuration.updated", body);
    co_return configurationJson(row);
}

drogon::Task<Json::Value> SystemConfigService::updateConfigurationByName(
    const turbo::RequestContext &ctx, const std::string &name, const Json::Value &body) {
    requirePermission(ctx, "UPDATE_CONFIGURATION");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto row = co_await Mapper<m::Configuration>(txn).findOne(
            Criteria(m::Configuration::Cols::_name, name));
        co_return co_await updateConfiguration(ctx, row.getValueOfId(), body);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Configuration not found",
                       "error.msg.systemconfig.configuration.not.found");
    }
}

// ---------------------------------------------------------------------------
// external service configuration
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::getExternalService(const turbo::RequestContext &ctx,
                                                                  const std::string &name) {
    requirePermission(ctx, "READ_EXTERNALSERVICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Json::Value out;
    out["name"] = name;
    try {
        auto row = co_await Mapper<m::ExternalService>(txn).findByPrimaryKey(name);
        out["config"] = parseJsonOrEmpty(row.getValueOfConfig(), Json::objectValue);
    } catch (const UnexpectedRows &) {
        out["config"] = Json::Value(Json::objectValue);
    }
    co_return out;
}

drogon::Task<Json::Value> SystemConfigService::updateExternalService(const turbo::RequestContext &ctx,
                                                                    const std::string &name,
                                                                    const Json::Value &body) {
    requirePermission(ctx, "UPDATE_EXTERNALSERVICE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::ExternalService> mapper(txn);
    m::ExternalService row;
    row.setServiceName(name);
    row.setConfig(jsonCompact(body));
    row.setModifiedAt(Date::now());
    try {
        co_await mapper.findByPrimaryKey(name);
        co_await mapper.update(row);
    } catch (const UnexpectedRows &) {
        co_await mapper.insert(row);
    }
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
    auto rows = co_await Mapper<m::TlOutbox>(txn)
                    .orderBy(m::TlOutbox::Cols::_occurred_at, drogon::orm::SortOrder::DESC)
                    .limit(200)
                    .findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(auditJson(r));
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getAudit(const turbo::RequestContext &ctx,
                                                        const std::string &id) {
    requirePermission(ctx, "READ_AUDIT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::TlOutbox row;
    try {
        row = co_await Mapper<m::TlOutbox>(txn).findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Audit entry not found",
                       "error.msg.systemconfig.audit.not.found");
    }
    Json::Value j = auditJson(row);
    j["commandAsJson"] = parseJsonOrEmpty(row.getValueOfPayload(), Json::objectValue);
    j["requestId"] = row.getRequestId() ? row.getValueOfRequestId() : "";
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

drogon::Task<Json::Value> SystemConfigService::listHooks(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_HOOK");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::Hook>(txn).orderBy(m::Hook::Cols::_display_name).findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(hookJson(r));
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getHook(const turbo::RequestContext &ctx,
                                                       const std::string &id) {
    requirePermission(ctx, "READ_HOOK");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return hookJson(co_await Mapper<m::Hook>(txn).findByPrimaryKey(id));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Hook not found", "error.msg.systemconfig.hook.not.found");
    }
}

drogon::Task<Json::Value> SystemConfigService::createHook(const turbo::RequestContext &ctx,
                                                          const Json::Value &body) {
    requirePermission(ctx, "CREATE_HOOK");
    const std::string name = asStringOr(body, "name");
    if (name.empty())
        throw ApiError(drogon::k400BadRequest, "'name' is required",
                       "error.msg.systemconfig.hook.validation");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::Hook row;
    row.setName(name);
    row.setDisplayName(asStringOr(body, "displayName", name));
    row.setIsActive(asBoolOr(body, "isActive", true));
    row.setConfig(jsonCompact(body.isMember("config") ? body["config"] : Json::Value(Json::objectValue)));
    row.setEvents(jsonCompact(body.isMember("events") ? body["events"] : Json::Value(Json::arrayValue)));
    auto inserted = co_await Mapper<m::Hook>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "hook", inserted.getValueOfId(), "hook.created", body);
    co_return hookJson(inserted);
}

drogon::Task<Json::Value> SystemConfigService::updateHook(const turbo::RequestContext &ctx,
                                                          const std::string &id,
                                                          const Json::Value &body) {
    requirePermission(ctx, "UPDATE_HOOK");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::Hook> mapper(txn);
    m::Hook row;
    try {
        row = co_await mapper.findByPrimaryKey(id);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Hook not found", "error.msg.systemconfig.hook.not.found");
    }
    if (!asStringOr(body, "displayName").empty()) row.setDisplayName(asStringOr(body, "displayName"));
    if (body.isMember("isActive")) row.setIsActive(asBoolOr(body, "isActive", true));
    if (body.isMember("config")) row.setConfig(jsonCompact(body["config"]));
    if (body.isMember("events")) row.setEvents(jsonCompact(body["events"]));
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "hook", id, "hook.updated", body);
    co_return hookJson(row);
}

drogon::Task<void> SystemConfigService::deleteHook(const turbo::RequestContext &ctx,
                                                   const std::string &id) {
    requirePermission(ctx, "DELETE_HOOK");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto affected = co_await Mapper<m::Hook>(txn).deleteByPrimaryKey(id);
    if (affected == 0)
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
    Json::Value out;
    try {
        auto row = co_await Mapper<m::CacheConfig>(txn).findByPrimaryKey(1);
        out["cacheType"] = row.getValueOfCacheType();
    } catch (const UnexpectedRows &) {
        out["cacheType"] = "NO_CACHE";
    }
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
    Mapper<m::CacheConfig> mapper(txn);
    m::CacheConfig row;
    row.setId(1);
    row.setCacheType(cacheType);
    row.setModifiedAt(Date::now());
    try {
        co_await mapper.findByPrimaryKey(1);
        co_await mapper.update(row);
    } catch (const UnexpectedRows &) {
        co_await mapper.insert(row);
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "cache", "1", "cache.updated", body);
    co_return co_await getCacheConfig(ctx);
}

// ---------------------------------------------------------------------------
// business date
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listBusinessDates(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_BUSINESSDATE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::BusinessDate>(txn).findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["type"] = r.getValueOfType();
        j["date"] = dateStr(r.getValueOfDateValue());
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getBusinessDate(const turbo::RequestContext &ctx,
                                                               const std::string &type) {
    requirePermission(ctx, "READ_BUSINESSDATE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto row = co_await Mapper<m::BusinessDate>(txn).findByPrimaryKey(type);
        Json::Value j;
        j["type"] = row.getValueOfType();
        j["date"] = dateStr(row.getValueOfDateValue());
        co_return j;
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Business date type not found",
                       "error.msg.systemconfig.businessdate.not.found");
    }
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
    Mapper<m::BusinessDate> mapper(txn);
    m::BusinessDate row;
    row.setType(type);
    row.setDateValue(dateOr(date, Date::now()));
    row.setModifiedAt(Date::now());
    try {
        co_await mapper.findByPrimaryKey(type);
        co_await mapper.update(row);
    } catch (const UnexpectedRows &) {
        co_await mapper.insert(row);
    }
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
        co_await Mapper<m::ExternalEventConfiguration>(txn)
            .orderBy(m::ExternalEventConfiguration::Cols::_category)
            .findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["category"] = r.getValueOfCategory();
        j["enabled"] = r.getValueOfIsEnabled();
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
    Mapper<m::ExternalEventConfiguration> mapper(txn);
    m::ExternalEventConfiguration row;
    row.setCategory(category);
    row.setIsEnabled(enabled);
    row.setModifiedAt(Date::now());
    try {
        co_await mapper.findByPrimaryKey(category);
        co_await mapper.update(row);
    } catch (const UnexpectedRows &) {
        co_await mapper.insert(row);
    }
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
    auto rows = co_await Mapper<m::FieldConfiguration>(txn)
                    .orderBy(m::FieldConfiguration::Cols::_field_name)
                    .findBy(Criteria(m::FieldConfiguration::Cols::_entity, entity));
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["fieldName"] = r.getValueOfFieldName();
        j["isEnabled"] = r.getValueOfIsEnabled();
        j["isMandatory"] = r.getValueOfIsMandatory();
        j["validationRegex"] = r.getValidationRegex() ? r.getValueOfValidationRegex() : "";
        list.append(j);
    }
    co_return list;
}

// ---------------------------------------------------------------------------
// datatables engine
//
// The registry (tl_datatable_registry) is a regular table and goes through
// CoroMapper<TlDatatableRegistry> like everything else. The *physical*
// per-datatable tables (dt_<name>) cannot have a generated Model — their
// column set is only known at runtime — so DDL/DML against them still goes
// through turbo::db-scoped raw execSqlCoro, same as before.
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listDatatables(const turbo::RequestContext &ctx) {
    requirePermission(ctx, "READ_DATATABLE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::TlDatatableRegistry>(txn)
                    .orderBy(m::TlDatatableRegistry::Cols::_datatable_name)
                    .findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(datatableJson(r));
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getDatatable(const turbo::RequestContext &ctx,
                                                            const std::string &name) {
    requirePermission(ctx, "READ_DATATABLE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return datatableJson(co_await Mapper<m::TlDatatableRegistry>(txn).findByPrimaryKey(name));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Datatable not found",
                       "error.msg.systemconfig.datatable.not.found");
    }
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
    Mapper<m::TlDatatableRegistry> registry(txn);
    if (co_await registry.count(Criteria(m::TlDatatableRegistry::Cols::_datatable_name, name)) > 0)
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

    m::TlDatatableRegistry row;
    row.setDatatableName(name);
    row.setApptableName(apptable);
    row.setCategory(asIntOr(body, "category", 0));
    row.setIsMultiRow(asBoolOr(body, "multiRow", true));
    row.setColumns(jsonCompact(body["columns"]));
    co_await registry.insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable", name, "datatable.created", body);
    co_return co_await getDatatable(ctx, name);
}

drogon::Task<Json::Value> SystemConfigService::registerDatatable(const turbo::RequestContext &ctx,
                                                                 const std::string &datatable,
                                                                 const std::string &apptable) {
    requirePermission(ctx, "CREATE_DATATABLE");
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

    Mapper<m::TlDatatableRegistry> registry(txn);
    m::TlDatatableRegistry row;
    row.setDatatableName(datatable);
    row.setApptableName(apptable);
    row.setColumns(jsonCompact(cols));
    try {
        co_await registry.findByPrimaryKey(datatable);
        co_await registry.update(row);
    } catch (const UnexpectedRows &) {
        co_await registry.insert(row);
    }
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable", datatable, "datatable.registered",
                                       Json::Value(Json::objectValue));
    co_return co_await getDatatable(ctx, datatable);
}

drogon::Task<void> SystemConfigService::deregisterDatatable(const turbo::RequestContext &ctx,
                                                            const std::string &datatable) {
    requirePermission(ctx, "DELETE_DATATABLE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto affected =
        co_await Mapper<m::TlDatatableRegistry>(txn).deleteByPrimaryKey(datatable);
    if (affected == 0)
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
    Mapper<m::TlDatatableRegistry> registry(txn);
    m::TlDatatableRegistry reg;
    try {
        reg = co_await registry.findByPrimaryKey(name);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Datatable not found",
                       "error.msg.systemconfig.datatable.not.found");
    }
    Json::Value columns = parseJsonOrEmpty(reg.getValueOfColumns(), Json::arrayValue);

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
    reg.setColumns(jsonCompact(columns));
    co_await registry.update(reg);
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable", name, "datatable.updated", body);
    co_return co_await getDatatable(ctx, name);
}

drogon::Task<void> SystemConfigService::deleteDatatable(const turbo::RequestContext &ctx,
                                                        const std::string &name) {
    requirePermission(ctx, "DELETE_DATATABLE");
    const std::string tableIdent = physicalTableIdent(name);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto affected = co_await Mapper<m::TlDatatableRegistry>(txn).deleteByPrimaryKey(name);
    if (affected == 0)
        throw ApiError(drogon::k404NotFound, "Datatable not found",
                       "error.msg.systemconfig.datatable.not.found");
    co_await txn->execSqlCoro("DROP TABLE IF EXISTS " + tableIdent);
    co_await turbo::outbox::writeEvent(txn, ctx, "datatable", name, "datatable.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

drogon::Task<Json::Value> SystemConfigService::requireDatatableColumns(Txn txn,
                                                                       const std::string &name) {
    m::TlDatatableRegistry reg;
    try {
        reg = co_await Mapper<m::TlDatatableRegistry>(txn).findByPrimaryKey(name);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Datatable not found",
                       "error.msg.systemconfig.datatable.not.found");
    }
    Json::Value out;
    out["apptableName"] = reg.getValueOfApptableName();
    out["multiRow"] = reg.getValueOfIsMultiRow();
    out["columns"] = parseJsonOrEmpty(reg.getValueOfColumns(), Json::arrayValue);
    co_return out;
}

drogon::Task<Json::Value> SystemConfigService::queryDatatable(const turbo::RequestContext &ctx,
                                                              const std::string &name,
                                                              const Json::Value &filters) {
    // NOTE: filters are applied client-side (post-fetch) rather than folded into a
    // dynamic SQL WHERE clause. Drogon's coroutine SQL API (execSqlCoro, and the
    // CoroMapper built on top of it) requires the bound-parameter count to be known
    // at compile time, so a single query with N dynamically-bound predicates can't be
    // expressed for these runtime-defined dt_<name> tables. Datatables are
    // tenant-scoped, small, custom-attribute tables, so an in-process filter over the
    // full result set is an acceptable, injection-safe simplification here.
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
    // See queryDatatable() for why a single dynamic-arity INSERT isn't used.
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
    auto rows = co_await Mapper<m::TlEntityDatatableCheck>(txn)
                    .orderBy(m::TlEntityDatatableCheck::Cols::_entity)
                    .orderBy(m::TlEntityDatatableCheck::Cols::_status_code)
                    .findAll();
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(entityDatatableCheckJson(r));
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
    m::TlEntityDatatableCheck row;
    row.setEntity(entity);
    row.setStatusCode(status);
    row.setDatatableName(datatableName);
    if (!asStringOr(body, "productId").empty()) row.setProductId(asStringOr(body, "productId"));
    try {
        auto inserted = co_await Mapper<m::TlEntityDatatableCheck>(txn).insert(row);
        co_await turbo::outbox::writeEvent(txn, ctx, "entitydatatablecheck", inserted.getValueOfId(),
                                           "entitydatatablecheck.created", body);
        Json::Value out;
        out["resourceId"] = inserted.getValueOfId();
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
    auto affected = co_await Mapper<m::TlEntityDatatableCheck>(txn).deleteByPrimaryKey(id);
    if (affected == 0)
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
    Mapper<m::TlImportDocument> mapper(txn);
    mapper.orderBy(m::TlImportDocument::Cols::_import_time, drogon::orm::SortOrder::DESC);
    auto rows = entityType.empty()
                    ? co_await mapper.findAll()
                    : co_await mapper.findBy(
                          Criteria(m::TlImportDocument::Cols::_entity_type, entityType));
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(importJson(r));
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

drogon::Task<Json::Value> SystemConfigService::listDocuments(const turbo::RequestContext &ctx,
                                                             const std::string &entityType,
                                                             const std::string &entityId) {
    requirePermission(ctx, "READ_DOCUMENT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::TlDocument>(txn)
                    .orderBy(m::TlDocument::Cols::_created_at)
                    .findBy(Criteria(m::TlDocument::Cols::_entity_type, entityType) &&
                            Criteria(m::TlDocument::Cols::_entity_id, entityId));
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(documentJson(r, false));
    co_return list;
}

drogon::Task<Json::Value> SystemConfigService::getDocument(const turbo::RequestContext &ctx,
                                                           const std::string &entityType,
                                                           const std::string &entityId,
                                                           const std::string &documentId) {
    requirePermission(ctx, "READ_DOCUMENT");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        co_return documentJson(co_await Mapper<m::TlDocument>(txn).findByPrimaryKey(documentId), false);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Document not found",
                       "error.msg.systemconfig.document.not.found");
    }
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
    const std::string contentB64 = asStringOr(body, "content");
    std::vector<char> bytes =
        contentB64.empty() ? std::vector<char>() : drogon::utils::base64DecodeToVector(contentB64);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    m::TlDocument row;
    row.setEntityType(entityType);
    row.setEntityId(entityId);
    row.setName(asStringOr(body, "name", fileName));
    row.setFileName(fileName);
    if (!asStringOr(body, "contentType").empty()) row.setContentType(asStringOr(body, "contentType"));
    if (!asStringOr(body, "description").empty()) row.setDescription(asStringOr(body, "description"));
    row.setSizeBytes(static_cast<int64_t>(bytes.size()));
    row.setContent(bytes);
    row.setCreatedBy(ctx.username);
    auto inserted = co_await Mapper<m::TlDocument>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "document", inserted.getValueOfId(), "document.created",
                                       body);
    co_return documentJson(inserted, false);
}

drogon::Task<Json::Value> SystemConfigService::updateDocument(const turbo::RequestContext &ctx,
                                                              const std::string &entityType,
                                                              const std::string &entityId,
                                                              const std::string &documentId,
                                                              const Json::Value &body) {
    requirePermission(ctx, "UPDATE_DOCUMENT");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::TlDocument> mapper(txn);
    m::TlDocument row;
    try {
        row = co_await mapper.findByPrimaryKey(documentId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Document not found",
                       "error.msg.systemconfig.document.not.found");
    }
    if (!asStringOr(body, "name").empty()) row.setName(asStringOr(body, "name"));
    if (!asStringOr(body, "description").empty()) row.setDescription(asStringOr(body, "description"));
    if (body.isMember("content")) {
        if (!asStringOr(body, "fileName").empty()) row.setFileName(asStringOr(body, "fileName"));
        if (!asStringOr(body, "contentType").empty()) row.setContentType(asStringOr(body, "contentType"));
        auto bytes = drogon::utils::base64DecodeToVector(asStringOr(body, "content"));
        row.setSizeBytes(static_cast<int64_t>(bytes.size()));
        row.setContent(bytes);
    }
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "document", documentId, "document.updated", body);
    co_return documentJson(row, false);
}

drogon::Task<void> SystemConfigService::deleteDocument(const turbo::RequestContext &ctx,
                                                       const std::string &entityType,
                                                       const std::string &entityId,
                                                       const std::string &documentId) {
    requirePermission(ctx, "DELETE_DOCUMENT");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto affected = co_await Mapper<m::TlDocument>(txn).deleteByPrimaryKey(documentId);
    if (affected == 0)
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
    try {
        co_return documentJson(co_await Mapper<m::TlDocument>(txn).findByPrimaryKey(documentId), true);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Document not found",
                       "error.msg.systemconfig.document.not.found");
    }
}

// ---------------------------------------------------------------------------
// generic entity: notes
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listNotes(const turbo::RequestContext &ctx,
                                                         const std::string &resourceType,
                                                         const std::string &resourceId) {
    requirePermission(ctx, "READ_NOTE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::TlNote>(txn)
                    .orderBy(m::TlNote::Cols::_created_at, drogon::orm::SortOrder::DESC)
                    .findBy(Criteria(m::TlNote::Cols::_resource_type, resourceType) &&
                            Criteria(m::TlNote::Cols::_resource_id, resourceId));
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(noteJson(r));
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
    try {
        co_return noteJson(co_await Mapper<m::TlNote>(txn).findByPrimaryKey(noteId));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Note not found", "error.msg.systemconfig.note.not.found");
    }
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
    m::TlNote row;
    row.setResourceType(resourceType);
    row.setResourceId(resourceId);
    row.setNote(note);
    row.setCreatedBy(ctx.username);
    auto inserted = co_await Mapper<m::TlNote>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "note", inserted.getValueOfId(), "note.created", body);
    co_return noteJson(inserted);
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
    Mapper<m::TlNote> mapper(txn);
    m::TlNote row;
    try {
        row = co_await mapper.findByPrimaryKey(noteId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Note not found", "error.msg.systemconfig.note.not.found");
    }
    row.setNote(asStringOr(body, "note"));
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "note", noteId, "note.updated", body);
    co_return noteJson(row);
}

drogon::Task<void> SystemConfigService::deleteNote(const turbo::RequestContext &ctx,
                                                  const std::string &resourceType,
                                                  const std::string &resourceId,
                                                  const std::string &noteId) {
    requirePermission(ctx, "DELETE_NOTE");
    (void)resourceType;
    (void)resourceId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto affected = co_await Mapper<m::TlNote>(txn).deleteByPrimaryKey(noteId);
    if (affected == 0)
        throw ApiError(drogon::k404NotFound, "Note not found", "error.msg.systemconfig.note.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "note", noteId, "note.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// generic entity: images (singleton per entity, composite primary key)
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::getImage(const turbo::RequestContext &ctx,
                                                        const std::string &entity,
                                                        const std::string &entityId) {
    requirePermission(ctx, "READ_IMAGE");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    try {
        auto row = co_await Mapper<m::TlImage>(txn).findOne(
            Criteria(m::TlImage::Cols::_entity_type, entity) &&
            Criteria(m::TlImage::Cols::_entity_id, entityId));
        Json::Value j;
        j["entityType"] = entity;
        j["entityId"] = entityId;
        j["contentType"] = row.getContentType() ? row.getValueOfContentType() : "";
        const auto &bytes = row.getValueOfContent();
        j["content"] = drogon::utils::base64Encode(
            reinterpret_cast<const unsigned char *>(bytes.data()), bytes.size());
        co_return j;
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Image not found", "error.msg.systemconfig.image.not.found");
    }
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
    auto bytes = drogon::utils::base64DecodeToVector(content);
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Mapper<m::TlImage> mapper(txn);
    m::TlImage row;
    row.setEntityType(entity);
    row.setEntityId(entityId);
    if (!asStringOr(body, "contentType").empty()) row.setContentType(asStringOr(body, "contentType"));
    row.setContent(bytes);
    row.setModifiedAt(Date::now());
    try {
        co_await mapper.findOne(Criteria(m::TlImage::Cols::_entity_type, entity) &&
                                Criteria(m::TlImage::Cols::_entity_id, entityId));
        co_await mapper.update(row);
    } catch (const UnexpectedRows &) {
        co_await mapper.insert(row);
    }
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
    auto affected =
        co_await Mapper<m::TlImage>(txn).deleteBy(Criteria(m::TlImage::Cols::_entity_type, entity) &&
                                                  Criteria(m::TlImage::Cols::_entity_id, entityId));
    if (affected == 0)
        throw ApiError(drogon::k404NotFound, "Image not found", "error.msg.systemconfig.image.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "image", entity + ":" + entityId, "image.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// generic entity: calendars
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listCalendars(const turbo::RequestContext &ctx,
                                                             const std::string &entityType,
                                                             const std::string &entityId) {
    requirePermission(ctx, "READ_CALENDAR");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::TlCalendar>(txn)
                    .orderBy(m::TlCalendar::Cols::_start_date)
                    .findBy(Criteria(m::TlCalendar::Cols::_entity_type, entityType) &&
                            Criteria(m::TlCalendar::Cols::_entity_id, entityId));
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(calendarJson(r));
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
    try {
        co_return calendarJson(co_await Mapper<m::TlCalendar>(txn).findByPrimaryKey(calendarId));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Calendar not found",
                       "error.msg.systemconfig.calendar.not.found");
    }
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
    m::TlCalendar row;
    row.setEntityType(entityType);
    row.setEntityId(entityId);
    row.setTitle(title);
    if (!asStringOr(body, "description").empty()) row.setDescription(asStringOr(body, "description"));
    if (!asStringOr(body, "location").empty()) row.setLocation(asStringOr(body, "location"));
    row.setStartDate(dateOr(startDate, Date::now()));
    if (!asStringOr(body, "endDate").empty()) row.setEndDate(dateOr(asStringOr(body, "endDate"), Date()));
    row.setCalendarType(asStringOr(body, "calendarType", "COLLECTION"));
    if (!asStringOr(body, "recurrence").empty()) row.setRecurrence(asStringOr(body, "recurrence"));
    if (asIntOr(body, "remindByDays", 0) != 0) row.setRemindByDays(asIntOr(body, "remindByDays", 0));
    auto inserted = co_await Mapper<m::TlCalendar>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "calendar", inserted.getValueOfId(), "calendar.created",
                                       body);
    co_return calendarJson(inserted);
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
    Mapper<m::TlCalendar> mapper(txn);
    m::TlCalendar row;
    try {
        row = co_await mapper.findByPrimaryKey(calendarId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Calendar not found",
                       "error.msg.systemconfig.calendar.not.found");
    }
    if (!asStringOr(body, "title").empty()) row.setTitle(asStringOr(body, "title"));
    if (!asStringOr(body, "description").empty()) row.setDescription(asStringOr(body, "description"));
    if (!asStringOr(body, "location").empty()) row.setLocation(asStringOr(body, "location"));
    if (!asStringOr(body, "startDate").empty())
        row.setStartDate(dateOr(asStringOr(body, "startDate"), Date::now()));
    if (!asStringOr(body, "endDate").empty()) row.setEndDate(dateOr(asStringOr(body, "endDate"), Date()));
    if (!asStringOr(body, "calendarType").empty()) row.setCalendarType(asStringOr(body, "calendarType"));
    if (!asStringOr(body, "recurrence").empty()) row.setRecurrence(asStringOr(body, "recurrence"));
    if (asIntOr(body, "remindByDays", 0) != 0) row.setRemindByDays(asIntOr(body, "remindByDays", 0));
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "calendar", calendarId, "calendar.updated", body);
    co_return calendarJson(row);
}

drogon::Task<void> SystemConfigService::deleteCalendar(const turbo::RequestContext &ctx,
                                                      const std::string &entityType,
                                                      const std::string &entityId,
                                                      const std::string &calendarId) {
    requirePermission(ctx, "DELETE_CALENDAR");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto affected = co_await Mapper<m::TlCalendar>(txn).deleteByPrimaryKey(calendarId);
    if (affected == 0)
        throw ApiError(drogon::k404NotFound, "Calendar not found",
                       "error.msg.systemconfig.calendar.not.found");
    co_await turbo::outbox::writeEvent(txn, ctx, "calendar", calendarId, "calendar.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// generic entity: meetings
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> SystemConfigService::listMeetings(const turbo::RequestContext &ctx,
                                                            const std::string &entityType,
                                                            const std::string &entityId) {
    requirePermission(ctx, "READ_MEETING");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto rows = co_await Mapper<m::TlMeeting>(txn)
                    .orderBy(m::TlMeeting::Cols::_meeting_date, drogon::orm::SortOrder::DESC)
                    .findBy(Criteria(m::TlMeeting::Cols::_entity_type, entityType) &&
                            Criteria(m::TlMeeting::Cols::_entity_id, entityId));
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) list.append(meetingJson(r));
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
    try {
        co_return meetingJson(co_await Mapper<m::TlMeeting>(txn).findByPrimaryKey(meetingId));
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Meeting not found",
                       "error.msg.systemconfig.meeting.not.found");
    }
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
    m::TlMeeting row;
    row.setEntityType(entityType);
    row.setEntityId(entityId);
    if (!asStringOr(body, "calendarId").empty()) row.setCalendarId(asStringOr(body, "calendarId"));
    row.setMeetingDate(dateOr(meetingDate, Date::now()));
    if (!asStringOr(body, "notes").empty()) row.setNotes(asStringOr(body, "notes"));
    row.setStatus(asStringOr(body, "status", "SCHEDULED"));
    auto inserted = co_await Mapper<m::TlMeeting>(txn).insert(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "meeting", inserted.getValueOfId(), "meeting.created",
                                       body);
    co_return meetingJson(inserted);
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
    Mapper<m::TlMeeting> mapper(txn);
    m::TlMeeting row;
    try {
        row = co_await mapper.findByPrimaryKey(meetingId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Meeting not found",
                       "error.msg.systemconfig.meeting.not.found");
    }
    if (!asStringOr(body, "meetingDate").empty())
        row.setMeetingDate(dateOr(asStringOr(body, "meetingDate"), Date::now()));
    if (!asStringOr(body, "notes").empty()) row.setNotes(asStringOr(body, "notes"));
    if (!asStringOr(body, "status").empty()) row.setStatus(asStringOr(body, "status"));
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "meeting", meetingId, "meeting.updated", body);
    co_return meetingJson(row);
}

drogon::Task<void> SystemConfigService::deleteMeeting(const turbo::RequestContext &ctx,
                                                     const std::string &entityType,
                                                     const std::string &entityId,
                                                     const std::string &meetingId) {
    requirePermission(ctx, "DELETE_MEETING");
    (void)entityType;
    (void)entityId;
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto affected = co_await Mapper<m::TlMeeting>(txn).deleteByPrimaryKey(meetingId);
    if (affected == 0)
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
    Mapper<m::TlMeeting> mapper(txn);
    m::TlMeeting row;
    try {
        row = co_await mapper.findByPrimaryKey(meetingId);
    } catch (const UnexpectedRows &) {
        throw ApiError(drogon::k404NotFound, "Meeting not found",
                       "error.msg.systemconfig.meeting.not.found");
    }
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
    row.setStatus(newStatus);
    row.setModifiedAt(Date::now());
    co_await mapper.update(row);
    co_await turbo::outbox::writeEvent(txn, ctx, "meeting", meetingId, "meeting." + command, body);
    co_return meetingJson(row);
}

}  // namespace turbo_ledger_systemconfig
