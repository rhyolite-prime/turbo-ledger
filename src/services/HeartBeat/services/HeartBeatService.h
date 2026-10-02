//
// Phase 8 — HeartBeat (Scheduler): `jobs` (14) + `scheduler` (2) = 16
// endpoints.
//
// Durable, Postgres-backed admin API for Fineract's "Scheduler" module: a
// catalog of named background jobs, their run history, a configurable
// business-step pipeline per job, and a global scheduler on/off switch.
//
// Scope decision (see IMPLEMENTATION_PLAN.md Phase 8 as-built notes):
// "running" a job here (manual, inline, or — in a real deployment — cron-
// triggered) records a `job_run_history` row documenting the attempt; it
// does not perform real cross-service business work (interest posting,
// accrual, delinquency classification, ...) since no inter-service RPC
// client exists in this codebase to call into the owning services. This is
// an honest no-op completion, not a silent lie — every run is logged with
// `trigger_type` and a `COMPLETED` status plus a note explaining the
// limitation, so operators can see exactly what did (and didn't) happen.
// A real cron engine / leader election is likewise out of scope for this
// sandbox (no long-running scheduler process is started) — the `scheduler`
// on/off switch and every job's `cron_expression`/`is_active` are stored
// and reported accurately, ready for a future scheduler process to read.
//
// Every operation runs inside the caller's tenant schema
// (turbo::db::beginTenantTxn). RBAC is enforced entirely from the
// gateway-signed TL-Context, matching every other service in this
// codebase.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/RequestContext.h"

namespace turbo_ledger_heartbeat {

/// Error carrying an HTTP status + envelope globalisation code.
class ApiError : public std::runtime_error {
  public:
    ApiError(drogon::HttpStatusCode status, std::string message, std::string globalisationCode = "")
        : std::runtime_error(std::move(message)), status_(status), code_(std::move(globalisationCode)) {}
    drogon::HttpStatusCode status() const { return status_; }
    const std::string &globalisationCode() const { return code_; }

  private:
    drogon::HttpStatusCode status_;
    std::string code_;
};

class HeartBeatService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- jobs: registry ----------------------------------------------------
    drogon::Task<Json::Value> listJobs(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> listJobNames(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getJobByShortName(const turbo::RequestContext &ctx, const std::string &shortName);
    drogon::Task<Json::Value> getJobById(const turbo::RequestContext &ctx, const std::string &jobId);
    drogon::Task<Json::Value> updateJobByShortName(const turbo::RequestContext &ctx, const std::string &shortName,
                                                   const Json::Value &body);
    drogon::Task<Json::Value> updateJobById(const turbo::RequestContext &ctx, const std::string &jobId,
                                            const Json::Value &body);

    // ---- jobs: execution (see class-level scope note) -----------------------
    drogon::Task<Json::Value> runJobByShortName(const turbo::RequestContext &ctx, const std::string &shortName);
    drogon::Task<Json::Value> runJobById(const turbo::RequestContext &ctx, const std::string &jobId);
    drogon::Task<Json::Value> runInlineJob(const turbo::RequestContext &ctx, const std::string &jobName,
                                           const Json::Value &body);

    // ---- jobs: run history ---------------------------------------------------
    drogon::Task<Json::Value> jobRunHistoryByShortName(const turbo::RequestContext &ctx,
                                                       const std::string &shortName, int offset, int limit);
    drogon::Task<Json::Value> jobRunHistoryById(const turbo::RequestContext &ctx, const std::string &jobId,
                                                int offset, int limit);

    // ---- jobs: business-step pipeline -----------------------------------------
    drogon::Task<Json::Value> availableSteps(const turbo::RequestContext &ctx, const std::string &jobName);
    drogon::Task<Json::Value> getSteps(const turbo::RequestContext &ctx, const std::string &jobName);
    drogon::Task<Json::Value> updateSteps(const turbo::RequestContext &ctx, const std::string &jobName,
                                          const Json::Value &body);

    // ---- scheduler: global on/off switch ---------------------------------------
    drogon::Task<Json::Value> getSchedulerStatus(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> updateSchedulerStatus(const turbo::RequestContext &ctx, const Json::Value &body);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);
};

}  // namespace turbo_ledger_heartbeat
