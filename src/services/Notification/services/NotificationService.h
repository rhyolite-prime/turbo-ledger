//
// Phase 8 — Notification (43 endpoints): `notifications` (2, per-user
// inbox), `sms` (6) + `smscampaigns` (8), `email` (20: ad hoc + campaigns +
// SMTP configuration), `reportmailingjobs` (6) + `reportmailingjobrunhistory`
// (1).
//
// Scope decision (see IMPLEMENTATION_PLAN.md Phase 8 as-built notes): real
// SMS/email provider network dispatch is stubbed — creating a message or
// activating a campaign queues a row with status PENDING and writes an
// outbox event; no real network call ever flips it to SENT. This is a
// pluggable-provider-interface placeholder, not a silent lie. Likewise
// `reportmailingjobs` links a report by name/params only and a job "run" is
// the same disclosed no-op pattern HeartBeat's `jobs` uses.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/RequestContext.h"

namespace turbo_ledger_notification {

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

class NotificationService {
  public:
    // ---- notifications: per-user inbox -------------------------------------
    drogon::Task<Json::Value> listNotifications(const turbo::RequestContext &ctx, bool onlyUnread,
                                                int offset, int limit);
    drogon::Task<Json::Value> markNotificationsRead(const turbo::RequestContext &ctx, Json::Value body);

    // ---- sms ----------------------------------------------------------------
    drogon::Task<Json::Value> listSms(const turbo::RequestContext &ctx, const std::string &status,
                                      int offset, int limit);
    drogon::Task<Json::Value> createSms(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> getSms(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> updateSms(const turbo::RequestContext &ctx, std::string id, Json::Value body);
    drogon::Task<Json::Value> deleteSms(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> smsMessagesByStatusForCampaign(const turbo::RequestContext &ctx,
                                                             std::string campaignId,
                                                             const std::string &status);

    // ---- smscampaigns ---------------------------------------------------------
    drogon::Task<Json::Value> listSmsCampaigns(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createSmsCampaign(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> smsCampaignTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getSmsCampaign(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> updateSmsCampaign(const turbo::RequestContext &ctx, std::string id,
                                                Json::Value body);
    drogon::Task<Json::Value> deleteSmsCampaign(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> smsCampaignCommand(const turbo::RequestContext &ctx, std::string id,
                                                 Json::Value body);
    drogon::Task<Json::Value> previewSmsCampaign(const turbo::RequestContext &ctx, Json::Value body);

    // ---- email configuration ----------------------------------------------
    drogon::Task<Json::Value> getEmailConfiguration(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> updateEmailConfiguration(const turbo::RequestContext &ctx, Json::Value body);

    // ---- email campaigns --------------------------------------------------
    drogon::Task<Json::Value> listEmailCampaigns(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createEmailCampaign(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> emailCampaignTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> editEmailCampaignTemplate(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> getEmailCampaign(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> updateEmailCampaign(const turbo::RequestContext &ctx, std::string id,
                                                  Json::Value body);
    drogon::Task<Json::Value> deleteEmailCampaign(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> emailCampaignCommand(const turbo::RequestContext &ctx, std::string id,
                                                   Json::Value body);
    drogon::Task<Json::Value> previewEmailCampaign(const turbo::RequestContext &ctx, Json::Value body);

    // ---- email: ad hoc messages --------------------------------------------
    drogon::Task<Json::Value> listEmails(const turbo::RequestContext &ctx, int offset, int limit);
    drogon::Task<Json::Value> createEmail(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> getEmail(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> updateEmail(const turbo::RequestContext &ctx, std::string id, Json::Value body);
    drogon::Task<Json::Value> deleteEmail(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> failedEmails(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> pendingEmails(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> sentEmails(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> emailsByStatus(const turbo::RequestContext &ctx, const std::string &status);

    // ---- reportmailingjobs / reportmailingjobrunhistory ---------------------
    drogon::Task<Json::Value> listReportMailingJobs(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createReportMailingJob(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> reportMailingJobTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getReportMailingJob(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> updateReportMailingJob(const turbo::RequestContext &ctx, std::string id,
                                                     Json::Value body);
    drogon::Task<Json::Value> deleteReportMailingJob(const turbo::RequestContext &ctx, std::string id);
    drogon::Task<Json::Value> reportMailingJobRunHistory(const turbo::RequestContext &ctx,
                                                         const std::string &jobId, int offset, int limit);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);
};

}  // namespace turbo_ledger_notification
