//
// Phase 2 — SystemConfig: codes, global configuration, external service
// config, audits, hooks, caches, business date, external events, field
// configuration, the datatables engine, entity-datatable checks, imports and
// generic entity attachments (documents/notes/images/calendars/meetings).
//
// Every operation runs inside the caller's tenant schema (t_<tenantId>) via
// turbo::db::beginTenantTxn. RBAC is enforced entirely from the gateway-signed
// TL-Context (turbo::RequestContext::hasPermission) — see OrganizationService
// for the identical pattern used throughout Phase 2.
//
#pragma once

#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <json/json.h>
#include <stdexcept>
#include <string>

#include "turbo/RequestContext.h"

namespace turbo_ledger_systemconfig {

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

class SystemConfigService {
  public:
    using Txn = std::shared_ptr<drogon::orm::Transaction>;

    // ---- codes / code values (11) --------------------------------------------
    drogon::Task<Json::Value> listCodes(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getCode(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> getCodeByName(const turbo::RequestContext &ctx, const std::string &name);
    drogon::Task<Json::Value> createCode(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateCode(const turbo::RequestContext &ctx, const std::string &id,
                                         const Json::Value &body);
    drogon::Task<void> deleteCode(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> listCodeValues(const turbo::RequestContext &ctx,
                                             const std::string &codeId);
    drogon::Task<Json::Value> getCodeValue(const turbo::RequestContext &ctx, const std::string &codeId,
                                           const std::string &valueId);
    drogon::Task<Json::Value> createCodeValue(const turbo::RequestContext &ctx,
                                              const std::string &codeId, const Json::Value &body);
    drogon::Task<Json::Value> updateCodeValue(const turbo::RequestContext &ctx,
                                              const std::string &codeId, const std::string &valueId,
                                              const Json::Value &body);
    drogon::Task<void> deleteCodeValue(const turbo::RequestContext &ctx, const std::string &codeId,
                                       const std::string &valueId);

    // ---- global configuration (5) ---------------------------------------------
    drogon::Task<Json::Value> listConfigurations(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getConfiguration(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> getConfigurationByName(const turbo::RequestContext &ctx,
                                                     const std::string &name);
    drogon::Task<Json::Value> updateConfiguration(const turbo::RequestContext &ctx,
                                                  const std::string &id, const Json::Value &body);
    drogon::Task<Json::Value> updateConfigurationByName(const turbo::RequestContext &ctx,
                                                        const std::string &name,
                                                        const Json::Value &body);

    // ---- external service (2) --------------------------------------------------
    drogon::Task<Json::Value> getExternalService(const turbo::RequestContext &ctx,
                                                 const std::string &name);
    drogon::Task<Json::Value> updateExternalService(const turbo::RequestContext &ctx,
                                                    const std::string &name, const Json::Value &body);

    // ---- audits (3, reads this service's own outbox as a local audit trail) ---
    drogon::Task<Json::Value> listAudits(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getAudit(const turbo::RequestContext &ctx, const std::string &id);
    Json::Value auditSearchTemplate(const turbo::RequestContext &ctx);

    // ---- hooks (6) ----------------------------------------------------------------
    drogon::Task<Json::Value> listHooks(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getHook(const turbo::RequestContext &ctx, const std::string &id);
    drogon::Task<Json::Value> createHook(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> updateHook(const turbo::RequestContext &ctx, const std::string &id,
                                         const Json::Value &body);
    drogon::Task<void> deleteHook(const turbo::RequestContext &ctx, const std::string &id);
    Json::Value hookTemplate(const turbo::RequestContext &ctx);

    // ---- caches (2) -----------------------------------------------------------------
    drogon::Task<Json::Value> getCacheConfig(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> updateCacheConfig(const turbo::RequestContext &ctx,
                                                const Json::Value &body);

    // ---- business date (3) ----------------------------------------------------------
    drogon::Task<Json::Value> listBusinessDates(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getBusinessDate(const turbo::RequestContext &ctx, const std::string &type);
    drogon::Task<Json::Value> updateBusinessDate(const turbo::RequestContext &ctx,
                                                 const Json::Value &body);

    // ---- external events (2) --------------------------------------------------------
    drogon::Task<Json::Value> listExternalEventConfig(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> updateExternalEventConfig(const turbo::RequestContext &ctx,
                                                        const Json::Value &body);

    // ---- field configuration (1) -----------------------------------------------------
    drogon::Task<Json::Value> getFieldConfiguration(const turbo::RequestContext &ctx,
                                                    const std::string &entity);

    // ---- datatables engine (16) -------------------------------------------------------
    drogon::Task<Json::Value> listDatatables(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getDatatable(const turbo::RequestContext &ctx, const std::string &name);
    drogon::Task<Json::Value> createDatatable(const turbo::RequestContext &ctx, const Json::Value &body);
    drogon::Task<Json::Value> registerDatatable(const turbo::RequestContext &ctx,
                                                const std::string &datatable,
                                                const std::string &apptable);
    drogon::Task<void> deregisterDatatable(const turbo::RequestContext &ctx,
                                           const std::string &datatable);
    drogon::Task<Json::Value> updateDatatable(const turbo::RequestContext &ctx,
                                              const std::string &name, const Json::Value &body);
    drogon::Task<void> deleteDatatable(const turbo::RequestContext &ctx, const std::string &name);
    drogon::Task<Json::Value> queryDatatable(const turbo::RequestContext &ctx,
                                             const std::string &name, const Json::Value &filters);
    drogon::Task<Json::Value> listDatatableEntries(const turbo::RequestContext &ctx,
                                                   const std::string &name,
                                                   const std::string &apptableId);
    drogon::Task<Json::Value> createDatatableEntry(const turbo::RequestContext &ctx,
                                                   const std::string &name,
                                                   const std::string &apptableId,
                                                   const Json::Value &body);
    drogon::Task<Json::Value> updateDatatableEntry(const turbo::RequestContext &ctx,
                                                   const std::string &name,
                                                   const std::string &apptableId,
                                                   const Json::Value &body);
    drogon::Task<void> deleteDatatableEntries(const turbo::RequestContext &ctx,
                                              const std::string &name,
                                              const std::string &apptableId);
    drogon::Task<Json::Value> getDatatableRow(const turbo::RequestContext &ctx,
                                              const std::string &name, const std::string &apptableId,
                                              const std::string &rowId);
    drogon::Task<Json::Value> updateDatatableRow(const turbo::RequestContext &ctx,
                                                 const std::string &name,
                                                 const std::string &apptableId,
                                                 const std::string &rowId, const Json::Value &body);
    drogon::Task<void> deleteDatatableRow(const turbo::RequestContext &ctx, const std::string &name,
                                          const std::string &apptableId, const std::string &rowId);

    // ---- entity-datatable checks (4) -----------------------------------------------------
    drogon::Task<Json::Value> listEntityDatatableChecks(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> createEntityDatatableCheck(const turbo::RequestContext &ctx,
                                                         const Json::Value &body);
    drogon::Task<void> deleteEntityDatatableCheck(const turbo::RequestContext &ctx,
                                                  const std::string &id);
    Json::Value entityDatatableCheckTemplate(const turbo::RequestContext &ctx);

    // ---- imports (3) -----------------------------------------------------------------------
    drogon::Task<Json::Value> listImports(const turbo::RequestContext &ctx,
                                          const std::string &entityType);
    Json::Value importOutputTemplateLocation(const turbo::RequestContext &ctx);

    // ---- generic entity: documents (6) -------------------------------------------------------
    drogon::Task<Json::Value> listDocuments(const turbo::RequestContext &ctx,
                                            const std::string &entityType,
                                            const std::string &entityId);
    drogon::Task<Json::Value> getDocument(const turbo::RequestContext &ctx, const std::string &entityType,
                                          const std::string &entityId, const std::string &documentId);
    drogon::Task<Json::Value> createDocument(const turbo::RequestContext &ctx,
                                             const std::string &entityType,
                                             const std::string &entityId, const Json::Value &body);
    drogon::Task<Json::Value> updateDocument(const turbo::RequestContext &ctx,
                                             const std::string &entityType,
                                             const std::string &entityId,
                                             const std::string &documentId, const Json::Value &body);
    drogon::Task<void> deleteDocument(const turbo::RequestContext &ctx, const std::string &entityType,
                                      const std::string &entityId, const std::string &documentId);
    drogon::Task<Json::Value> getDocumentContent(const turbo::RequestContext &ctx,
                                                 const std::string &entityType,
                                                 const std::string &entityId,
                                                 const std::string &documentId);

    // ---- generic entity: notes (5) -----------------------------------------------------------
    drogon::Task<Json::Value> listNotes(const turbo::RequestContext &ctx,
                                        const std::string &resourceType, const std::string &resourceId);
    drogon::Task<Json::Value> getNote(const turbo::RequestContext &ctx, const std::string &resourceType,
                                      const std::string &resourceId, const std::string &noteId);
    drogon::Task<Json::Value> createNote(const turbo::RequestContext &ctx,
                                         const std::string &resourceType,
                                         const std::string &resourceId, const Json::Value &body);
    drogon::Task<Json::Value> updateNote(const turbo::RequestContext &ctx,
                                         const std::string &resourceType,
                                         const std::string &resourceId, const std::string &noteId,
                                         const Json::Value &body);
    drogon::Task<void> deleteNote(const turbo::RequestContext &ctx, const std::string &resourceType,
                                  const std::string &resourceId, const std::string &noteId);

    // ---- generic entity: images (4, singleton per entity) ---------------------------------------
    drogon::Task<Json::Value> getImage(const turbo::RequestContext &ctx, const std::string &entity,
                                       const std::string &entityId);
    drogon::Task<Json::Value> putImage(const turbo::RequestContext &ctx, const std::string &entity,
                                       const std::string &entityId, const Json::Value &body);
    drogon::Task<void> deleteImage(const turbo::RequestContext &ctx, const std::string &entity,
                                   const std::string &entityId);

    // ---- generic entity: calendars (6) -----------------------------------------------------------
    drogon::Task<Json::Value> listCalendars(const turbo::RequestContext &ctx,
                                            const std::string &entityType,
                                            const std::string &entityId);
    Json::Value calendarTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getCalendar(const turbo::RequestContext &ctx, const std::string &entityType,
                                          const std::string &entityId, const std::string &calendarId);
    drogon::Task<Json::Value> createCalendar(const turbo::RequestContext &ctx,
                                             const std::string &entityType,
                                             const std::string &entityId, const Json::Value &body);
    drogon::Task<Json::Value> updateCalendar(const turbo::RequestContext &ctx,
                                             const std::string &entityType,
                                             const std::string &entityId,
                                             const std::string &calendarId, const Json::Value &body);
    drogon::Task<void> deleteCalendar(const turbo::RequestContext &ctx, const std::string &entityType,
                                      const std::string &entityId, const std::string &calendarId);

    // ---- generic entity: meetings (7) -------------------------------------------------------------
    drogon::Task<Json::Value> listMeetings(const turbo::RequestContext &ctx,
                                           const std::string &entityType, const std::string &entityId);
    Json::Value meetingTemplate(const turbo::RequestContext &ctx);
    drogon::Task<Json::Value> getMeeting(const turbo::RequestContext &ctx, const std::string &entityType,
                                         const std::string &entityId, const std::string &meetingId);
    drogon::Task<Json::Value> createMeeting(const turbo::RequestContext &ctx,
                                            const std::string &entityType,
                                            const std::string &entityId, const Json::Value &body);
    drogon::Task<Json::Value> updateMeeting(const turbo::RequestContext &ctx,
                                            const std::string &entityType,
                                            const std::string &entityId, const std::string &meetingId,
                                            const Json::Value &body);
    drogon::Task<void> deleteMeeting(const turbo::RequestContext &ctx, const std::string &entityType,
                                     const std::string &entityId, const std::string &meetingId);
    drogon::Task<Json::Value> meetingCommand(const turbo::RequestContext &ctx,
                                             const std::string &entityType,
                                             const std::string &entityId, const std::string &meetingId,
                                             const std::string &command, const Json::Value &body);

  private:
    static drogon::orm::DbClientPtr db();
    static void requirePermission(const turbo::RequestContext &ctx, const std::string &code);

    drogon::Task<Json::Value> codeToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> codeValueToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> configurationToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> hookToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> documentToJson(Txn txn, const std::string &id, bool includeContent);
    drogon::Task<Json::Value> noteToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> calendarToJson(Txn txn, const std::string &id);
    drogon::Task<Json::Value> meetingToJson(Txn txn, const std::string &id);

    /// Look up a registered datatable's column list, throwing 404 if unknown.
    drogon::Task<Json::Value> requireDatatableColumns(Txn txn, const std::string &name);
};

}  // namespace turbo_ledger_systemconfig
