//
// Phase 5 — savingsaccounts (32 endpoints: 29 implemented + 3 GSIM thin 501
// stubs — see DepositAccountManagementService.h's header comment for why —
// and 4 bulk-import/template-download 501 stubs matching the
// downloadtemplate/uploadtemplate precedent from Accounting's
// GlAccountsController in Phase 3). Backed by the shared savings_account
// table (deposit_type=SAVINGS).
//
// Routing uses explicit action-suffix paths (get-all/create/get-detail/
// {id}/update/.../command/{name}) rather than Fineract's single-path +
// HTTP-verb-overload + ?command= query-param style, matching every other
// controller in this codebase (see GlAccountsController, ClientsController).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SavingsAccountsController : public drogon::HttpController<SavingsAccountsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/savingsaccounts/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        // ---- core CRUD + lifecycle --------------------------------------------
        ADD_METHOD_TO(SavingsAccountsController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(SavingsAccountsController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(SavingsAccountsController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::update, std::string(PREFIX) + "{1}/update", Put, Options,
                     FILTER);
        ADD_METHOD_TO(SavingsAccountsController::remove, std::string(PREFIX) + "{1}/delete", Delete, Options,
                     FILTER);
        ADD_METHOD_TO(SavingsAccountsController::command, std::string(PREFIX) + "{1}/command/{2}", Post,
                     Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::templateEndpoint, std::string(PREFIX) + "template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::downloadTemplate, std::string(PREFIX) + "downloadtemplate",
                     Get, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::uploadTemplate, std::string(PREFIX) + "uploadtemplate",
                     Post, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::transactionsDownloadTemplate,
                     std::string(PREFIX) + "transactions/downloadtemplate", Get, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::transactionsUploadTemplate,
                     std::string(PREFIX) + "transactions/uploadtemplate", Post, Options, FILTER);

        // ---- external-id addressing --------------------------------------------
        ADD_METHOD_TO(SavingsAccountsController::getDetailsByExternalId,
                     std::string(PREFIX) + "external-id/{1}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::updateByExternalId,
                     std::string(PREFIX) + "external-id/{1}/update", Put, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::removeByExternalId,
                     std::string(PREFIX) + "external-id/{1}/delete", Delete, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::commandByExternalId,
                     std::string(PREFIX) + "external-id/{1}/command/{2}", Post, Options, FILTER);

        // ---- GSIM (thin 501 stubs — see header note) ---------------------------
        ADD_METHOD_TO(SavingsAccountsController::gsimCreate, std::string(PREFIX) + "gsim/create", Post,
                     Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::gsimUpdate, std::string(PREFIX) + "gsim/{1}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::gsimCommand, std::string(PREFIX) + "gsimcommands/{1}", Post,
                     Options, FILTER);

        // ---- charges sub-resource -----------------------------------------------
        ADD_METHOD_TO(SavingsAccountsController::chargesGetAll, std::string(PREFIX) + "{1}/charges/get-all",
                     Get, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::chargesCreate, std::string(PREFIX) + "{1}/charges/create",
                     Post, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::chargesGetDetail,
                     std::string(PREFIX) + "{1}/charges/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::chargesUpdate,
                     std::string(PREFIX) + "{1}/charges/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::chargesDelete,
                     std::string(PREFIX) + "{1}/charges/{2}/delete", Delete, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::chargesCommand,
                     std::string(PREFIX) + "{1}/charges/{2}/command/{3}", Post, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::chargesTemplate,
                     std::string(PREFIX) + "{1}/charges/template", Get, Options, FILTER);

        // ---- transactions sub-resource --------------------------------------------
        ADD_METHOD_TO(SavingsAccountsController::transactionsCreate,
                     std::string(PREFIX) + "{1}/transactions/command/{2}", Post, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::transactionsGetAll,
                     std::string(PREFIX) + "{1}/transactions/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::transactionsSearch,
                     std::string(PREFIX) + "{1}/transactions/search", Get, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::transactionsQuery,
                     std::string(PREFIX) + "{1}/transactions/query", Post, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::transactionsTemplate,
                     std::string(PREFIX) + "{1}/transactions/template", Get, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::transactionsGetDetail,
                     std::string(PREFIX) + "{1}/transactions/get-detail/{2}", Get, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::transactionsCommand,
                     std::string(PREFIX) + "{1}/transactions/{2}/command/{3}", Post, Options, FILTER);
        ADD_METHOD_TO(SavingsAccountsController::onHoldTransactions,
                     std::string(PREFIX) + "{1}/onholdtransactions/get-all", Get, Options, FILTER);
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
    Task<HttpResponsePtr> transactionsDownloadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> transactionsUploadTemplate(HttpRequestPtr req);

    Task<HttpResponsePtr> getDetailsByExternalId(HttpRequestPtr req, std::string externalId);
    Task<HttpResponsePtr> updateByExternalId(HttpRequestPtr req, std::string externalId);
    Task<HttpResponsePtr> removeByExternalId(HttpRequestPtr req, std::string externalId);
    Task<HttpResponsePtr> commandByExternalId(HttpRequestPtr req, std::string externalId, std::string cmd);

    Task<HttpResponsePtr> gsimCreate(HttpRequestPtr req);
    Task<HttpResponsePtr> gsimUpdate(HttpRequestPtr req, std::string parentAccountId);
    Task<HttpResponsePtr> gsimCommand(HttpRequestPtr req, std::string parentAccountId);

    Task<HttpResponsePtr> chargesGetAll(HttpRequestPtr req, std::string accountId);
    Task<HttpResponsePtr> chargesCreate(HttpRequestPtr req, std::string accountId);
    Task<HttpResponsePtr> chargesGetDetail(HttpRequestPtr req, std::string accountId, std::string chargeId);
    Task<HttpResponsePtr> chargesUpdate(HttpRequestPtr req, std::string accountId, std::string chargeId);
    Task<HttpResponsePtr> chargesDelete(HttpRequestPtr req, std::string accountId, std::string chargeId);
    Task<HttpResponsePtr> chargesCommand(HttpRequestPtr req, std::string accountId, std::string chargeId,
                                         std::string cmd);
    Task<HttpResponsePtr> chargesTemplate(HttpRequestPtr req, std::string accountId);

    Task<HttpResponsePtr> transactionsCreate(HttpRequestPtr req, std::string accountId, std::string cmd);
    Task<HttpResponsePtr> transactionsGetAll(HttpRequestPtr req, std::string accountId);
    Task<HttpResponsePtr> transactionsSearch(HttpRequestPtr req, std::string accountId);
    Task<HttpResponsePtr> transactionsQuery(HttpRequestPtr req, std::string accountId);
    Task<HttpResponsePtr> transactionsTemplate(HttpRequestPtr req, std::string accountId);
    Task<HttpResponsePtr> transactionsGetDetail(HttpRequestPtr req, std::string accountId,
                                                std::string transactionId);
    Task<HttpResponsePtr> transactionsCommand(HttpRequestPtr req, std::string accountId,
                                              std::string transactionId, std::string cmd);
    Task<HttpResponsePtr> onHoldTransactions(HttpRequestPtr req, std::string accountId);
};
