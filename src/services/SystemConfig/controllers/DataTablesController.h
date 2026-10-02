//
// Phase 2 — datatables engine (16 endpoints). Dynamic per-tenant custom
// tables attached to entities. See SystemConfigService for the dynamic-DDL
// design (physical tables named dt_<name>, registry table
// tl_datatable_registry, column allowlist enforced server-side).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class DataTablesController : public drogon::HttpController<DataTablesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/datatables/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(DataTablesController::getAll,        std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::create,        std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::getDetails,    std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::update,        std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::remove,        std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::registerTable, std::string(PREFIX) + "register/{1}/{2}", Post, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::deregister,    std::string(PREFIX) + "deregister/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::queryGet,      std::string(PREFIX) + "query/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::queryPost,     std::string(PREFIX) + "query/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::listEntries,   std::string(PREFIX) + "entries/{1}/{2}", Get, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::createEntry,   std::string(PREFIX) + "entries/{1}/{2}", Post, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::updateEntry,   std::string(PREFIX) + "entries/{1}/{2}", Put, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::deleteEntries, std::string(PREFIX) + "entries/{1}/{2}", Delete, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::getEntry,      std::string(PREFIX) + "entry/{1}/{2}/{3}", Get, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::updateEntryRow, std::string(PREFIX) + "entry/{1}/{2}/{3}", Put, Options, FILTER);
        ADD_METHOD_TO(DataTablesController::deleteEntryRow, std::string(PREFIX) + "entry/{1}/{2}/{3}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string name);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string name);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string name);
    Task<HttpResponsePtr> registerTable(HttpRequestPtr req, std::string name, std::string apptable);
    Task<HttpResponsePtr> deregister(HttpRequestPtr req, std::string name);
    Task<HttpResponsePtr> queryGet(HttpRequestPtr req, std::string name);
    Task<HttpResponsePtr> queryPost(HttpRequestPtr req, std::string name);
    Task<HttpResponsePtr> listEntries(HttpRequestPtr req, std::string name, std::string apptableId);
    Task<HttpResponsePtr> createEntry(HttpRequestPtr req, std::string name, std::string apptableId);
    Task<HttpResponsePtr> updateEntry(HttpRequestPtr req, std::string name, std::string apptableId);
    Task<HttpResponsePtr> deleteEntries(HttpRequestPtr req, std::string name, std::string apptableId);
    Task<HttpResponsePtr> getEntry(HttpRequestPtr req, std::string name, std::string apptableId,
                                   std::string rowId);
    Task<HttpResponsePtr> updateEntryRow(HttpRequestPtr req, std::string name, std::string apptableId,
                                         std::string rowId);
    Task<HttpResponsePtr> deleteEntryRow(HttpRequestPtr req, std::string name, std::string apptableId,
                                         std::string rowId);
};
