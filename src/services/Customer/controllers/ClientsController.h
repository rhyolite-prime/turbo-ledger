//
// Phase 4 — clients (53 endpoints: 51 implemented + 2 bulk-import stubs
// deferred, matching the downloadtemplate/uploadtemplate precedent set by
// Accounting's GlAccountsController in Phase 3).
//
// Routing uses explicit action-suffix paths (get-all/create/get-detail/
// {id}/update/.../command/{name}) rather than Fineract's single-path +
// HTTP-verb-overload + ?command= query-param style, matching every other
// controller in this codebase (see GlAccountsController, CodesController).
//
// External-id addressing (`external-id/{externalId}/...`) is implemented
// only for the core single-client operations (get-detail, update, delete,
// command, transactions list) — not for nested sub-resources (charges,
// identifiers, familymembers, collaterals), which are addressed by the
// internal clientId only. This is a deliberate scope trim, not an omission.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ClientsController : public drogon::HttpController<ClientsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/clients/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        // ---- core CRUD ----------------------------------------------------
        ADD_METHOD_TO(ClientsController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(ClientsController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(ClientsController::update, std::string(PREFIX) + "{1}/update", Put, Options, FILTER);
        ADD_METHOD_TO(ClientsController::remove, std::string(PREFIX) + "{1}/delete", Delete, Options,
                     FILTER);
        ADD_METHOD_TO(ClientsController::command, std::string(PREFIX) + "{1}/command/{2}", Post, Options,
                     FILTER);
        ADD_METHOD_TO(ClientsController::templateEndpoint, std::string(PREFIX) + "template", Get, Options,
                     FILTER);
        ADD_METHOD_TO(ClientsController::downloadTemplate, std::string(PREFIX) + "downloadtemplate", Get,
                     Options, FILTER);
        ADD_METHOD_TO(ClientsController::uploadTemplate, std::string(PREFIX) + "uploadtemplate", Post,
                     Options, FILTER);
        ADD_METHOD_TO(ClientsController::accountsOverview, std::string(PREFIX) + "{1}/accounts", Get,
                     Options, FILTER);
        ADD_METHOD_TO(ClientsController::obligeeDetails, std::string(PREFIX) + "{1}/obligeedetails", Get,
                     Options, FILTER);
        ADD_METHOD_TO(ClientsController::transferTemplate,
                     std::string(PREFIX) + "{1}/transferproposaldate", Get, Options, FILTER);

        // ---- external-id addressing (core ops only) ------------------------
        ADD_METHOD_TO(ClientsController::getDetailsByExternalId,
                     std::string(PREFIX) + "external-id/{1}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::updateByExternalId,
                     std::string(PREFIX) + "external-id/{1}/update", Put, Options, FILTER);
        ADD_METHOD_TO(ClientsController::removeByExternalId,
                     std::string(PREFIX) + "external-id/{1}/delete", Delete, Options, FILTER);
        ADD_METHOD_TO(ClientsController::commandByExternalId,
                     std::string(PREFIX) + "external-id/{1}/command/{2}", Post, Options, FILTER);
        ADD_METHOD_TO(ClientsController::transactionsByExternalId,
                     std::string(PREFIX) + "external-id/{1}/transactions/get-all", Get, Options, FILTER);

        // ---- charges --------------------------------------------------------
        ADD_METHOD_TO(ClientsController::chargesGetAll, std::string(PREFIX) + "{1}/charges/get-all", Get,
                     Options, FILTER);
        ADD_METHOD_TO(ClientsController::chargesAdd, std::string(PREFIX) + "{1}/charges/add", Post, Options,
                     FILTER);
        ADD_METHOD_TO(ClientsController::chargesGetDetail,
                     std::string(PREFIX) + "{1}/charges/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::chargesDelete, std::string(PREFIX) + "{1}/charges/{2}/delete",
                     Delete, Options, FILTER);
        ADD_METHOD_TO(ClientsController::chargesCommand,
                     std::string(PREFIX) + "{1}/charges/{2}/command/{3}", Post, Options, FILTER);
        ADD_METHOD_TO(ClientsController::chargesTemplate, std::string(PREFIX) + "{1}/charges/template", Get,
                     Options, FILTER);

        // ---- identifiers ------------------------------------------------------
        ADD_METHOD_TO(ClientsController::identifiersGetAll,
                     std::string(PREFIX) + "{1}/identifiers/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::identifiersCreate, std::string(PREFIX) + "{1}/identifiers/create",
                     Post, Options, FILTER);
        ADD_METHOD_TO(ClientsController::identifiersGetDetail,
                     std::string(PREFIX) + "{1}/identifiers/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::identifiersUpdate,
                     std::string(PREFIX) + "{1}/identifiers/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(ClientsController::identifiersDelete,
                     std::string(PREFIX) + "{1}/identifiers/{2}/delete", Delete, Options, FILTER);
        ADD_METHOD_TO(ClientsController::identifiersTemplate,
                     std::string(PREFIX) + "{1}/identifiers/template", Get, Options, FILTER);

        // ---- family members -----------------------------------------------------
        ADD_METHOD_TO(ClientsController::familyMembersGetAll,
                     std::string(PREFIX) + "{1}/familymembers/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::familyMembersCreate,
                     std::string(PREFIX) + "{1}/familymembers/create", Post, Options, FILTER);
        ADD_METHOD_TO(ClientsController::familyMembersGetDetail,
                     std::string(PREFIX) + "{1}/familymembers/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::familyMembersUpdate,
                     std::string(PREFIX) + "{1}/familymembers/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(ClientsController::familyMembersDelete,
                     std::string(PREFIX) + "{1}/familymembers/{2}/delete", Delete, Options, FILTER);
        ADD_METHOD_TO(ClientsController::familyMembersTemplate,
                     std::string(PREFIX) + "{1}/familymembers/template", Get, Options, FILTER);

        // ---- collaterals (client-level pledges) ------------------------------------
        ADD_METHOD_TO(ClientsController::collateralsGetAll,
                     std::string(PREFIX) + "{1}/collaterals/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::collateralsCreate, std::string(PREFIX) + "{1}/collaterals/create",
                     Post, Options, FILTER);
        ADD_METHOD_TO(ClientsController::collateralsGetDetail,
                     std::string(PREFIX) + "{1}/collaterals/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::collateralsUpdate,
                     std::string(PREFIX) + "{1}/collaterals/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(ClientsController::collateralsDelete,
                     std::string(PREFIX) + "{1}/collaterals/{2}/delete", Delete, Options, FILTER);
        ADD_METHOD_TO(ClientsController::collateralsTemplate,
                     std::string(PREFIX) + "{1}/collaterals/template", Get, Options, FILTER);

        // ---- transactions -----------------------------------------------------------
        ADD_METHOD_TO(ClientsController::transactionsGetAll,
                     std::string(PREFIX) + "{1}/transactions/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::transactionsGetDetail,
                     std::string(PREFIX) + "{1}/transactions/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(ClientsController::transactionsUndo,
                     std::string(PREFIX) + "{1}/transactions/{2}/undo", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> command(HttpRequestPtr req, std::string id, std::string cmd);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> downloadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> uploadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> accountsOverview(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> obligeeDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> transferTemplate(HttpRequestPtr req, std::string id);

    Task<HttpResponsePtr> getDetailsByExternalId(HttpRequestPtr req, std::string externalId);
    Task<HttpResponsePtr> updateByExternalId(HttpRequestPtr req, std::string externalId);
    Task<HttpResponsePtr> removeByExternalId(HttpRequestPtr req, std::string externalId);
    Task<HttpResponsePtr> commandByExternalId(HttpRequestPtr req, std::string externalId, std::string cmd);
    Task<HttpResponsePtr> transactionsByExternalId(HttpRequestPtr req, std::string externalId);

    Task<HttpResponsePtr> chargesGetAll(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> chargesAdd(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> chargesGetDetail(HttpRequestPtr req, std::string clientId, std::string chargeId);
    Task<HttpResponsePtr> chargesDelete(HttpRequestPtr req, std::string clientId, std::string chargeId);
    Task<HttpResponsePtr> chargesCommand(HttpRequestPtr req, std::string clientId, std::string chargeId,
                                         std::string cmd);
    Task<HttpResponsePtr> chargesTemplate(HttpRequestPtr req, std::string clientId);

    Task<HttpResponsePtr> identifiersGetAll(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> identifiersCreate(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> identifiersGetDetail(HttpRequestPtr req, std::string clientId,
                                               std::string identifierId);
    Task<HttpResponsePtr> identifiersUpdate(HttpRequestPtr req, std::string clientId,
                                            std::string identifierId);
    Task<HttpResponsePtr> identifiersDelete(HttpRequestPtr req, std::string clientId,
                                            std::string identifierId);
    Task<HttpResponsePtr> identifiersTemplate(HttpRequestPtr req, std::string clientId);

    Task<HttpResponsePtr> familyMembersGetAll(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> familyMembersCreate(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> familyMembersGetDetail(HttpRequestPtr req, std::string clientId,
                                                 std::string familyMemberId);
    Task<HttpResponsePtr> familyMembersUpdate(HttpRequestPtr req, std::string clientId,
                                              std::string familyMemberId);
    Task<HttpResponsePtr> familyMembersDelete(HttpRequestPtr req, std::string clientId,
                                              std::string familyMemberId);
    Task<HttpResponsePtr> familyMembersTemplate(HttpRequestPtr req, std::string clientId);

    Task<HttpResponsePtr> collateralsGetAll(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> collateralsCreate(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> collateralsGetDetail(HttpRequestPtr req, std::string clientId,
                                               std::string collateralId);
    Task<HttpResponsePtr> collateralsUpdate(HttpRequestPtr req, std::string clientId,
                                            std::string collateralId);
    Task<HttpResponsePtr> collateralsDelete(HttpRequestPtr req, std::string clientId,
                                            std::string collateralId);
    Task<HttpResponsePtr> collateralsTemplate(HttpRequestPtr req, std::string clientId);

    Task<HttpResponsePtr> transactionsGetAll(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> transactionsGetDetail(HttpRequestPtr req, std::string clientId,
                                                std::string transactionId);
    Task<HttpResponsePtr> transactionsUndo(HttpRequestPtr req, std::string clientId,
                                           std::string transactionId);
};
