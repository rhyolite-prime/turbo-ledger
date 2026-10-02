#include "ReportingService.h"

#include <drogon/orm/DbClient.h>
#include <drogon/orm/Exception.h>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <regex>
#include <set>

#include "turbo/Outbox.h"
#include "turbo/TenantDb.h"

using drogon::orm::DrogonDbException;
using drogon::orm::Result;

namespace turbo_ledger_reporting {

namespace {

std::string asStringOr(const Json::Value &v, const char *key, const std::string &fallback = "") {
    if (!v.isObject() || !v.isMember(key) || v[key].isNull()) return fallback;
    return v[key].isString() ? v[key].asString() : v[key].toStyledString();
}

bool asBoolOr(const Json::Value &v, const char *key, bool fallback) {
    if (!v.isObject() || !v.isMember(key) || v[key].isNull()) return fallback;
    return v[key].asBool();
}

/// True if `sql` (after trimming leading whitespace/comments) begins with
/// SELECT or WITH — a cheap, defense-in-depth guard on top of the read-only
/// transaction the engine always executes report_sql inside.
bool looksReadOnly(const std::string &sql) {
    size_t i = 0;
    const size_t n = sql.size();
    while (i < n) {
        if (std::isspace(static_cast<unsigned char>(sql[i]))) {
            ++i;
        } else if (i + 1 < n && sql[i] == '-' && sql[i + 1] == '-') {
            while (i < n && sql[i] != '\n') ++i;
        } else if (i + 1 < n && sql[i] == '/' && sql[i + 1] == '*') {
            i += 2;
            while (i + 1 < n && !(sql[i] == '*' && sql[i + 1] == '/')) ++i;
            i = std::min(n, i + 2);
        } else {
            break;
        }
    }
    auto startsWithCi = [&](const char *kw) {
        const size_t len = std::strlen(kw);
        if (i + len > n) return false;
        for (size_t k = 0; k < len; ++k)
            if (std::tolower(static_cast<unsigned char>(sql[i + k])) != kw[k]) return false;
        return true;
    };
    return startsWithCi("select") || startsWithCi("with");
}

/// All distinct ${name} tokens appearing in `sql`, in first-occurrence order.
std::vector<std::string> extractTokens(const std::string &sql) {
    static const std::regex kTokenRe(R"(\$\{([A-Za-z_][A-Za-z0-9_]*)\})");
    std::vector<std::string> tokens;
    std::set<std::string> seen;
    for (auto it = std::sregex_iterator(sql.begin(), sql.end(), kTokenRe); it != std::sregex_iterator();
         ++it) {
        const std::string name = (*it)[1].str();
        if (seen.insert(name).second) tokens.push_back(name);
    }
    return tokens;
}

}  // namespace

drogon::orm::DbClientPtr ReportingService::db() { return drogon::app().getDbClient(); }

void ReportingService::requirePermission(const turbo::RequestContext &ctx, const std::string &code) {
    if (!ctx.hasPermission(code))
        throw ApiError(drogon::k403Forbidden, "Missing permission: " + code,
                       "error.msg.platform.permission.denied");
}

bool ReportingService::isAllowedDataSource(const std::string &dataSource) {
    const auto &allowed = drogon::app().getCustomConfig()["reporting"]["allowed_data_sources"];
    for (const auto &v : allowed)
        if (v.isString() && v.asString() == dataSource) return true;
    return false;
}

drogon::orm::DbClientPtr ReportingService::resolveDataSourceClient(const std::string &dataSource) {
    if (dataSource.empty() || dataSource == "default" || !isAllowedDataSource(dataSource))
        throw ApiError(drogon::k500InternalServerError,
                       "Report definition references a disallowed data source: " + dataSource,
                       "error.msg.reporting.datasource.invalid");
    auto client = drogon::app().getDbClient(dataSource);
    if (!client)
        throw ApiError(drogon::k500InternalServerError,
                       "No db_client configured for data source: " + dataSource,
                       "error.msg.reporting.datasource.unconfigured");
    return client;
}

void ReportingService::validateParamValue(const std::string &type, const std::string &name,
                                          const std::string &value) {
    static const std::regex kDateRe(R"(^\d{4}-\d{2}-\d{2}$)");
    static const std::regex kNumberRe(R"(^-?\d+(\.\d+)?$)");
    if (type == "DATE" && !std::regex_match(value, kDateRe))
        throw ApiError(drogon::k400BadRequest,
                       "Parameter '" + name + "' must be a date in YYYY-MM-DD format",
                       "error.msg.reporting.parameter.invalid");
    if (type == "NUMBER" && !std::regex_match(value, kNumberRe))
        throw ApiError(drogon::k400BadRequest, "Parameter '" + name + "' must be numeric",
                       "error.msg.reporting.parameter.invalid");
    // STRING (and any other declared type): no format restriction — the value is
    // always bound as a real SQL parameter, never interpolated into the SQL text,
    // so there is no injection risk from accepting arbitrary text here.
}

// ---------------------------------------------------------------------------
// report definitions (admin CRUD)
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> ReportingService::definitionRowToJson(Txn txn, const std::string &id,
                                                                 bool includeSql) {
    auto rows = co_await txn->execSqlCoro(
        "SELECT id::text AS id, report_name, report_category, data_source, report_sql, "
        "       description, is_core, is_active, created_at, updated_at "
        "FROM report_definitions WHERE id = $1::uuid",
        id);
    if (rows.size() == 0)
        throw ApiError(drogon::k404NotFound, "Report definition not found: " + id,
                       "error.msg.reporting.report.not.found");
    const auto &r = rows[0];
    Json::Value j;
    j["id"] = r["id"].as<std::string>();
    j["reportName"] = r["report_name"].as<std::string>();
    j["reportCategory"] = r["report_category"].as<std::string>();
    j["dataSource"] = r["data_source"].as<std::string>();
    if (includeSql) j["reportSql"] = r["report_sql"].as<std::string>();
    j["description"] = r["description"].isNull() ? Json::Value() : r["description"].as<std::string>();
    j["isCore"] = r["is_core"].as<bool>();
    j["isActive"] = r["is_active"].as<bool>();
    j["createdAt"] = r["created_at"].isNull() ? Json::Value() : r["created_at"].as<std::string>();
    j["updatedAt"] = r["updated_at"].isNull() ? Json::Value() : r["updated_at"].as<std::string>();

    auto paramRows = co_await txn->execSqlCoro(
        "SELECT parameter_name, parameter_label, parameter_type, is_mandatory, default_value, "
        "       display_order "
        "FROM report_parameters WHERE report_id = $1::uuid ORDER BY display_order, parameter_name",
        id);
    Json::Value params(Json::arrayValue);
    for (const auto &pr : paramRows) {
        Json::Value p;
        p["parameterName"] = pr["parameter_name"].as<std::string>();
        p["parameterLabel"] = pr["parameter_label"].as<std::string>();
        p["parameterType"] = pr["parameter_type"].as<std::string>();
        p["isMandatory"] = pr["is_mandatory"].as<bool>();
        p["defaultValue"] =
            pr["default_value"].isNull() ? Json::Value() : pr["default_value"].as<std::string>();
        p["displayOrder"] = pr["display_order"].as<int>();
        params.append(p);
    }
    j["parameters"] = params;
    co_return j;
}

drogon::Task<void> ReportingService::replaceParameters(Txn txn, const std::string &reportId,
                                                       const Json::Value &parameters) {
    co_await txn->execSqlCoro("DELETE FROM report_parameters WHERE report_id = $1::uuid", reportId);
    if (!parameters.isArray()) co_return;
    int autoOrder = 0;
    for (const auto &p : parameters) {
        const std::string name = asStringOr(p, "parameterName");
        if (name.empty())
            throw ApiError(drogon::k400BadRequest, "Each parameter requires a non-empty parameterName",
                           "error.msg.reporting.parameter.name.required");
        const std::string label = asStringOr(p, "parameterLabel", name);
        const std::string type = asStringOr(p, "parameterType", "STRING");
        // Bound as text + explicit ::boolean cast (rather than a raw C++ bool)
        // to keep every write-path bind value a plain string, consistent with
        // how every ${param} value is bound elsewhere in this service.
        const std::string mandatory = asBoolOr(p, "isMandatory", true) ? "true" : "false";
        const int order = p.isObject() && p.isMember("displayOrder") && p["displayOrder"].isInt()
                              ? p["displayOrder"].asInt()
                              : autoOrder;
        const bool hasDefault = p.isObject() && p.isMember("defaultValue") && !p["defaultValue"].isNull();
        if (hasDefault) {
            co_await txn->execSqlCoro(
                "INSERT INTO report_parameters (report_id, parameter_name, parameter_label, "
                "parameter_type, is_mandatory, default_value, display_order) "
                "VALUES ($1::uuid, $2, $3, $4, $5::boolean, $6, $7)",
                reportId, name, label, type, mandatory, asStringOr(p, "defaultValue"), order);
        } else {
            co_await txn->execSqlCoro(
                "INSERT INTO report_parameters (report_id, parameter_name, parameter_label, "
                "parameter_type, is_mandatory, display_order) "
                "VALUES ($1::uuid, $2, $3, $4, $5::boolean, $6)",
                reportId, name, label, type, mandatory, order);
        }
        ++autoOrder;
    }
    co_return;
}

drogon::Task<Json::Value> ReportingService::listReportDefinitions(const turbo::RequestContext &ctx,
                                                                  const std::string &category) {
    requirePermission(ctx, "READ_REPORT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    Result rows(nullptr);
    if (category.empty()) {
        rows = co_await txn->execSqlCoro(
            "SELECT id::text AS id, report_name, report_category, data_source, description, "
            "       is_core, is_active "
            "FROM report_definitions ORDER BY report_category, report_name");
    } else {
        rows = co_await txn->execSqlCoro(
            "SELECT id::text AS id, report_name, report_category, data_source, description, "
            "       is_core, is_active "
            "FROM report_definitions WHERE report_category = $1 ORDER BY report_name",
            category);
    }
    Json::Value list(Json::arrayValue);
    for (const auto &r : rows) {
        Json::Value j;
        j["id"] = r["id"].as<std::string>();
        j["reportName"] = r["report_name"].as<std::string>();
        j["reportCategory"] = r["report_category"].as<std::string>();
        j["dataSource"] = r["data_source"].as<std::string>();
        j["description"] = r["description"].isNull() ? Json::Value() : r["description"].as<std::string>();
        j["isCore"] = r["is_core"].as<bool>();
        j["isActive"] = r["is_active"].as<bool>();
        list.append(j);
    }
    co_return list;
}

drogon::Task<Json::Value> ReportingService::getReportDefinition(const turbo::RequestContext &ctx,
                                                                const std::string &id) {
    requirePermission(ctx, "READ_REPORT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    co_return co_await definitionRowToJson(txn, id, /*includeSql=*/true);
}

drogon::Task<Json::Value> ReportingService::createReportDefinition(const turbo::RequestContext &ctx,
                                                                   const Json::Value &body) {
    requirePermission(ctx, "CREATE_REPORT");

    const std::string name = asStringOr(body, "reportName");
    const std::string category = asStringOr(body, "reportCategory");
    const std::string dataSource = asStringOr(body, "dataSource");
    const std::string sql = asStringOr(body, "reportSql");
    if (name.empty() || category.empty() || dataSource.empty() || sql.empty())
        throw ApiError(drogon::k400BadRequest,
                       "reportName, reportCategory, dataSource and reportSql are required",
                       "error.msg.reporting.report.invalid");
    if (!isAllowedDataSource(dataSource))
        throw ApiError(drogon::k400BadRequest, "Unknown or disallowed dataSource: " + dataSource,
                       "error.msg.reporting.datasource.invalid");
    if (!looksReadOnly(sql))
        throw ApiError(drogon::k400BadRequest, "reportSql must be a single read-only SELECT/WITH query",
                       "error.msg.reporting.report.not.readonly");

    const auto tokens = extractTokens(sql);
    const Json::Value &parameters = body.isMember("parameters") ? body["parameters"] : Json::Value(Json::arrayValue);
    std::set<std::string> declared;
    if (parameters.isArray())
        for (const auto &p : parameters) declared.insert(asStringOr(p, "parameterName"));
    for (const auto &t : tokens)
        if (!declared.count(t))
            throw ApiError(drogon::k400BadRequest,
                           "reportSql references ${" + t + "} but no matching parameter was declared",
                           "error.msg.reporting.parameter.undeclared");

    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    const std::optional<std::string> actorId =
        ctx.userId.empty() ? std::nullopt : std::optional<std::string>(ctx.userId);
    std::string id;
    try {
        auto rows = co_await txn->execSqlCoro(
            "INSERT INTO report_definitions (report_name, report_category, data_source, report_sql, "
            "description, is_core, created_by, updated_by) "
            "VALUES ($1, $2, $3, $4, $5, false, $6::uuid, $6::uuid) RETURNING id::text AS id",
            name, category, dataSource, sql, asStringOr(body, "description"), actorId);
        id = rows[0]["id"].as<std::string>();
    } catch (const DrogonDbException &) {
        throw ApiError(drogon::k400BadRequest, "A report named '" + name + "' already exists",
                       "error.msg.reporting.report.duplicate");
    }
    co_await replaceParameters(txn, id, parameters);
    co_await turbo::outbox::writeEvent(txn, ctx, "report", id, "report.created", body);
    co_return co_await definitionRowToJson(txn, id, /*includeSql=*/true);
}

drogon::Task<Json::Value> ReportingService::updateReportDefinition(const turbo::RequestContext &ctx,
                                                                   const std::string &id,
                                                                   const Json::Value &body) {
    requirePermission(ctx, "UPDATE_REPORT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    // Ensures the row exists (throws 404 otherwise) before we touch it.
    auto existing = co_await definitionRowToJson(txn, id, /*includeSql=*/true);

    const std::string sql = body.isMember("reportSql") ? asStringOr(body, "reportSql") : existing["reportSql"].asString();
    if (body.isMember("reportSql") && !looksReadOnly(sql))
        throw ApiError(drogon::k400BadRequest, "reportSql must be a single read-only SELECT/WITH query",
                       "error.msg.reporting.report.not.readonly");
    const std::string dataSource =
        body.isMember("dataSource") ? asStringOr(body, "dataSource") : existing["dataSource"].asString();
    if (!isAllowedDataSource(dataSource))
        throw ApiError(drogon::k400BadRequest, "Unknown or disallowed dataSource: " + dataSource,
                       "error.msg.reporting.datasource.invalid");

    const Json::Value &parameters = body.isMember("parameters") ? body["parameters"] : existing["parameters"];
    const auto tokens = extractTokens(sql);
    std::set<std::string> declared;
    if (parameters.isArray())
        for (const auto &p : parameters) declared.insert(asStringOr(p, "parameterName"));
    for (const auto &t : tokens)
        if (!declared.count(t))
            throw ApiError(drogon::k400BadRequest,
                           "reportSql references ${" + t + "} but no matching parameter was declared",
                           "error.msg.reporting.parameter.undeclared");

    const std::optional<std::string> actorId =
        ctx.userId.empty() ? std::nullopt : std::optional<std::string>(ctx.userId);
    const std::string isActiveText =
        (body.isMember("isActive") ? asBoolOr(body, "isActive", true) : existing["isActive"].asBool())
            ? "true"
            : "false";
    co_await txn->execSqlCoro(
        "UPDATE report_definitions SET report_name = $1, report_category = $2, data_source = $3, "
        "report_sql = $4, description = $5, is_active = $6::boolean, updated_by = $7::uuid, "
        "updated_at = now() "
        "WHERE id = $8::uuid",
        body.isMember("reportName") ? asStringOr(body, "reportName") : existing["reportName"].asString(),
        body.isMember("reportCategory") ? asStringOr(body, "reportCategory") : existing["reportCategory"].asString(),
        dataSource, sql,
        body.isMember("description") ? asStringOr(body, "description") : asStringOr(existing, "description"),
        isActiveText, actorId, id);

    if (body.isMember("parameters")) co_await replaceParameters(txn, id, parameters);

    co_await turbo::outbox::writeEvent(txn, ctx, "report", id, "report.updated", body);
    co_return co_await definitionRowToJson(txn, id, /*includeSql=*/true);
}

drogon::Task<void> ReportingService::deleteReportDefinition(const turbo::RequestContext &ctx,
                                                            const std::string &id) {
    requirePermission(ctx, "DELETE_REPORT");
    auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
    auto existing = co_await definitionRowToJson(txn, id, /*includeSql=*/false);
    if (existing["isCore"].asBool())
        throw ApiError(drogon::k400BadRequest,
                       "Core report definitions cannot be deleted; set isActive=false instead",
                       "error.msg.reporting.report.core.immutable");
    co_await txn->execSqlCoro("DELETE FROM report_definitions WHERE id = $1::uuid", id);
    co_await turbo::outbox::writeEvent(txn, ctx, "report", id, "report.deleted",
                                       Json::Value(Json::objectValue));
    co_return;
}

// ---------------------------------------------------------------------------
// execution
// ---------------------------------------------------------------------------

drogon::Task<Json::Value> ReportingService::runReport(
    const turbo::RequestContext &ctx, const std::string &id,
    const std::unordered_map<std::string, std::string> &params) {
    requirePermission(ctx, "READ_REPORT");

    std::string reportName, dataSource, reportSql;
    bool isActive = true;
    {
        auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
        auto rows = co_await txn->execSqlCoro(
            "SELECT report_name, data_source, report_sql, is_active FROM report_definitions "
            "WHERE id = $1::uuid",
            id);
        if (rows.size() == 0)
            throw ApiError(drogon::k404NotFound, "Report not found: " + id,
                           "error.msg.reporting.report.not.found");
        reportName = rows[0]["report_name"].as<std::string>();
        dataSource = rows[0]["data_source"].as<std::string>();
        reportSql = rows[0]["report_sql"].as<std::string>();
        isActive = rows[0]["is_active"].as<bool>();
    }
    if (!isActive)
        throw ApiError(drogon::k400BadRequest, "Report is not active: " + reportName,
                       "error.msg.reporting.report.inactive");

    struct ParamDef {
        std::string name;
        std::string type;
        bool mandatory{true};
        bool hasDefault{false};
        std::string defaultValue;
    };
    std::vector<ParamDef> paramDefs;
    {
        auto txn = co_await turbo::db::beginTenantTxn(db(), ctx);
        auto rows = co_await txn->execSqlCoro(
            "SELECT parameter_name, parameter_type, is_mandatory, default_value "
            "FROM report_parameters WHERE report_id = $1::uuid ORDER BY display_order, parameter_name",
            id);
        for (const auto &r : rows) {
            ParamDef p;
            p.name = r["parameter_name"].as<std::string>();
            p.type = r["parameter_type"].as<std::string>();
            p.mandatory = r["is_mandatory"].as<bool>();
            p.hasDefault = !r["default_value"].isNull();
            if (p.hasDefault) p.defaultValue = r["default_value"].as<std::string>();
            paramDefs.push_back(std::move(p));
        }
    }

    // The coroutine SQL binder (drogon::orm::DbClient::execSqlCoro) requires a
    // compile-time-fixed argument count, same constraint already documented in
    // SystemConfigService::queryDatatable for runtime-defined column lists — so
    // report parameter count is capped and dispatched via a fixed switch below
    // rather than attempting a single dynamic-arity bind.
    constexpr size_t kMaxReportParams = 8;
    if (paramDefs.size() > kMaxReportParams)
        throw ApiError(drogon::k500InternalServerError,
                       "Report '" + reportName + "' declares more than " +
                           std::to_string(kMaxReportParams) + " parameters",
                       "error.msg.reporting.too.many.parameters");

    std::vector<std::optional<std::string>> values;
    values.reserve(paramDefs.size());
    std::unordered_map<std::string, int> indexOf;
    for (size_t i = 0; i < paramDefs.size(); ++i) {
        const auto &p = paramDefs[i];
        indexOf[p.name] = static_cast<int>(i) + 1;  // 1-based positional placeholder index

        std::optional<std::string> value;
        auto it = params.find(p.name);
        if (it != params.end() && !it->second.empty()) {
            value = it->second;
        } else if (p.hasDefault) {
            value = p.defaultValue;
        } else if (p.mandatory) {
            throw ApiError(drogon::k400BadRequest, "Missing required report parameter: " + p.name,
                           "error.msg.reporting.parameter.missing");
        }
        if (value) validateParamValue(p.type, p.name, *value);
        values.push_back(std::move(value));
    }

    // Replace every ${name} occurrence with its bound positional placeholder.
    // Scanning the SQL (rather than looking the name up once) lets the same
    // named parameter appear more than once in a report's SQL.
    static const std::regex kTokenRe(R"(\$\{([A-Za-z_][A-Za-z0-9_]*)\})");
    std::string boundSql;
    boundSql.reserve(reportSql.size());
    size_t lastPos = 0;
    for (auto it = std::sregex_iterator(reportSql.begin(), reportSql.end(), kTokenRe);
         it != std::sregex_iterator(); ++it) {
        const auto &m = *it;
        boundSql.append(reportSql, lastPos, static_cast<size_t>(m.position()) - lastPos);
        const std::string paramName = m[1].str();
        auto idxIt = indexOf.find(paramName);
        if (idxIt == indexOf.end())
            throw ApiError(drogon::k500InternalServerError,
                           "Report '" + reportName + "' references undeclared parameter: " + paramName,
                           "error.msg.reporting.parameter.undeclared");
        boundSql += "$" + std::to_string(idxIt->second);
        lastPos = static_cast<size_t>(m.position()) + static_cast<size_t>(m.length());
    }
    boundSql.append(reportSql, lastPos, std::string::npos);

    auto dsClient = resolveDataSourceClient(dataSource);
    auto dsTxn = co_await turbo::db::beginTenantTxn(dsClient, ctx);
    co_await dsTxn->execSqlCoro("SET LOCAL transaction_read_only = on");
    const int timeoutMs =
        drogon::app().getCustomConfig()["reporting"].get("report_statement_timeout_ms", 20000).asInt();
    co_await dsTxn->execSqlCoro("SET LOCAL statement_timeout = " + std::to_string(timeoutMs));

    Result rows(nullptr);
    switch (values.size()) {
        case 0:
            rows = co_await dsTxn->execSqlCoro(boundSql);
            break;
        case 1:
            rows = co_await dsTxn->execSqlCoro(boundSql, values[0]);
            break;
        case 2:
            rows = co_await dsTxn->execSqlCoro(boundSql, values[0], values[1]);
            break;
        case 3:
            rows = co_await dsTxn->execSqlCoro(boundSql, values[0], values[1], values[2]);
            break;
        case 4:
            rows = co_await dsTxn->execSqlCoro(boundSql, values[0], values[1], values[2], values[3]);
            break;
        case 5:
            rows = co_await dsTxn->execSqlCoro(boundSql, values[0], values[1], values[2], values[3],
                                               values[4]);
            break;
        case 6:
            rows = co_await dsTxn->execSqlCoro(boundSql, values[0], values[1], values[2], values[3],
                                               values[4], values[5]);
            break;
        case 7:
            rows = co_await dsTxn->execSqlCoro(boundSql, values[0], values[1], values[2], values[3],
                                               values[4], values[5], values[6]);
            break;
        case 8:
            rows = co_await dsTxn->execSqlCoro(boundSql, values[0], values[1], values[2], values[3],
                                               values[4], values[5], values[6], values[7]);
            break;
        default:
            // Unreachable: guarded by kMaxReportParams above.
            throw ApiError(drogon::k500InternalServerError, "Unsupported report parameter count");
    }

    Json::Value result;
    result["reportName"] = reportName;
    result["dataSource"] = dataSource;
    Json::Value columnHeaders(Json::arrayValue);
    Json::Value data(Json::arrayValue);
    bool headersCaptured = false;
    for (const auto &row : rows) {
        Json::Value j(Json::objectValue);
        // NOTE: every column is surfaced as a JSON string (or null), matching the
        // existing generic-row convention in SystemConfigService::queryDatatable —
        // report_sql columns are arbitrary/dynamic, so there is no static schema to
        // type them against. Clients parse numeric/boolean/date strings as needed.
        for (size_t i = 0; i < row.size(); ++i) {
            if (!headersCaptured) columnHeaders.append(row[i].name());
            j[row[i].name()] = row[i].isNull() ? Json::Value() : Json::Value(row[i].as<std::string>());
        }
        headersCaptured = true;
        data.append(j);
    }
    result["columnHeaders"] = columnHeaders;
    result["data"] = data;
    result["rowCount"] = static_cast<Json::UInt64>(rows.size());
    co_return result;
}

}  // namespace turbo_ledger_reporting
