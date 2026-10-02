//
// Phase 8 — Reporting: a Fineract-style generic, parameterized SQL report
// engine. Reporting owns a small catalog (report_definitions +
// report_parameters, tenant-schema-scoped like every other service) rather
// than one hand-coded endpoint per report.
//
// Cross-service data access is "direct_multidb": this service opens its own
// additional read-only Drogon db_clients straight into each other service's
// Postgres database (see config.json), using the SAME t_<tenantId> schema
// convention via turbo::db::beginTenantTxn. Each report definition targets
// exactly one data_source — there is no in-engine cross-service join.
//
// Execution safety: report_sql is never string-interpolated. ${param} tokens
// are replaced with positional $N placeholders and bound as real SQL
// parameters; the resolved transaction additionally sets
// `transaction_read_only = on` and a `statement_timeout` before running the
// report query.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "turbo/RequestContext.h"

namespace turbo_ledger_reporting {

/// Error carrying an HTTP status + envelope globalisation code.
class ApiError : public std::runtime_error {
  public:
    ApiError(drogon::HttpStatusCode status, std::string message,
             std::string globalisationCode = "")
        : std::runtime_error(std::move(message)),
          status_(status),
          code_(std::move(globalisationCode)) {}
    drogon::HttpStatusCode status() const { return status_; }
    const std::string &globalisationCode() const { return code_; }

  private:
    drogon::HttpStatusCode status_;
    std::string code_;
};

class ReportingService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- report definitions (admin CRUD) -----------------------------------
    drogon::Task<Json::Value> listReportDefinitions(const turbo::RequestContext &ctx,
                                                    const std::string &category);
    drogon::Task<Json::Value> getReportDefinition(const turbo::RequestContext &ctx,
                                                  const std::string &id);
    drogon::Task<Json::Value> createReportDefinition(const turbo::RequestContext &ctx,
                                                     const Json::Value &body);
    drogon::Task<Json::Value> updateReportDefinition(const turbo::RequestContext &ctx,
                                                     const std::string &id,
                                                     const Json::Value &body);
    drogon::Task<void> deleteReportDefinition(const turbo::RequestContext &ctx,
                                              const std::string &id);

    // ---- execution ----------------------------------------------------------
    /// Runs report `id` with caller-supplied parameter values (query-string
    /// derived, parameter name -> raw text value) and returns
    /// { reportName, dataSource, columnHeaders: [...], data: [...], rowCount }.
    drogon::Task<Json::Value> runReport(const turbo::RequestContext &ctx, const std::string &id,
                                        const std::unordered_map<std::string, std::string> &params);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);
    static bool isAllowedDataSource(const std::string &dataSource);
    static drogon::orm::DbClientPtr resolveDataSourceClient(const std::string &dataSource);
    static void validateParamValue(const std::string &type, const std::string &name,
                                   const std::string &value);

    drogon::Task<Json::Value> definitionRowToJson(Txn txn, const std::string &id, bool includeSql);
    drogon::Task<void> replaceParameters(Txn txn, const std::string &reportId,
                                         const Json::Value &parameters);
};

}  // namespace turbo_ledger_reporting
