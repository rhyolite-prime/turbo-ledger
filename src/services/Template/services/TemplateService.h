//
// Phase 8 — Template (8 endpoints): CRUD for reusable text templates
// ("UGDs" in Fineract's terminology) plus a merge/render action.
//
// Scope decision (see IMPLEMENTATION_PLAN.md Phase 8 as-built notes): a
// real mapper pulls live field values out of another domain entity (a
// client, a loan, ...) by a declarative key. No inter-service RPC client
// exists in this codebase to fetch that data, so `mergeTemplate` only
// substitutes values the caller supplies directly in the merge request
// body. Rendering uses a minimal "{{mapperKey}}" regex-based substitution
// (no mustache library is vendored in this project) — unresolved
// placeholders are left verbatim in the output so callers can see exactly
// what wasn't supplied.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "turbo/RequestContext.h"

namespace turbo_ledger_template {

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

class TemplateService {
  public:
    drogon::Task<Json::Value> listTemplates(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getTemplate(const turbo::RequestContext &ctx, std::string templateId);
    drogon::Task<Json::Value> createTemplate(const turbo::RequestContext &ctx, Json::Value body);
    drogon::Task<Json::Value> updateTemplate(const turbo::RequestContext &ctx, std::string templateId,
                                             Json::Value body);
    drogon::Task<Json::Value> deleteTemplate(const turbo::RequestContext &ctx, std::string templateId);

    drogon::Task<Json::Value> mergeTemplate(const turbo::RequestContext &ctx, std::string templateId,
                                            Json::Value body);

    drogon::Task<Json::Value> creationTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> editTemplate(const turbo::RequestContext &ctx, std::string templateId);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);
};

}  // namespace turbo_ledger_template
