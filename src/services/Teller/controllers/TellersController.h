//
// Phase 7 — tellers (19 endpoints: teller core CRUD + teller-level
// transaction/journal views + nested cashier management + cashier
// transactions/allocate/settle). Completes Phase 7 alongside the Group
// retrofit and the standalone `cashiers`/`cashiersjournal` top-level
// resources (CashiersController / CashiersJournalController).
//
// Routing uses explicit action-suffix paths (get-all/create/get-detail/
// {id}/update/...), matching every other controller in this codebase
// (ClientsController, GroupsController, ...) rather than Fineract's single
// path + HTTP-verb-overload style.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TellersController : public drogon::HttpController<TellersController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/tellers/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        // ---- tellers: core CRUD ---------------------------------------------
        ADD_METHOD_TO(TellersController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(TellersController::create, std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(TellersController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(TellersController::update, std::string(PREFIX) + "{1}/update", Put, Options, FILTER);
        ADD_METHOD_TO(TellersController::remove, std::string(PREFIX) + "{1}/delete", Delete, Options, FILTER);

        // ---- teller-level views ----------------------------------------------
        ADD_METHOD_TO(TellersController::transactionsGetAll,
                     std::string(PREFIX) + "{1}/transactions/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(TellersController::transactionsGetDetail,
                     std::string(PREFIX) + "{1}/transactions/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(TellersController::journalsGetAll, std::string(PREFIX) + "{1}/journals/get-all", Get,
                     Options, FILTER);

        // ---- cashiers (nested) -------------------------------------------------
        ADD_METHOD_TO(TellersController::cashiersGetAll, std::string(PREFIX) + "{1}/cashiers/get-all", Get,
                     Options, FILTER);
        ADD_METHOD_TO(TellersController::cashiersCreate, std::string(PREFIX) + "{1}/cashiers/create", Post,
                     Options, FILTER);
        ADD_METHOD_TO(TellersController::cashiersTemplate, std::string(PREFIX) + "{1}/cashiers/template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(TellersController::cashiersGetDetail,
                     std::string(PREFIX) + "{1}/cashiers/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(TellersController::cashiersUpdate, std::string(PREFIX) + "{1}/cashiers/{2}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(TellersController::cashiersDelete, std::string(PREFIX) + "{1}/cashiers/{2}/delete",
                     Delete, Options, FILTER);

        // ---- cashier transactions ---------------------------------------------
        ADD_METHOD_TO(TellersController::cashierTransactionsGetAll,
                     std::string(PREFIX) + "{1}/cashiers/{2}/transactions/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(TellersController::cashierTransactionsTemplate,
                     std::string(PREFIX) + "{1}/cashiers/{2}/transactions/template", Get, Options, FILTER);
        ADD_METHOD_TO(TellersController::cashierSummaryAndTransactions,
                     std::string(PREFIX) + "{1}/cashiers/{2}/summaryandtransactions", Get, Options, FILTER);
        ADD_METHOD_TO(TellersController::allocateCashToCashier,
                     std::string(PREFIX) + "{1}/cashiers/{2}/allocate", Post, Options, FILTER);
        ADD_METHOD_TO(TellersController::settleCashToCashier,
                     std::string(PREFIX) + "{1}/cashiers/{2}/settle", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string tellerId);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string tellerId);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string tellerId);

    Task<HttpResponsePtr> transactionsGetAll(HttpRequestPtr req, std::string tellerId);
    Task<HttpResponsePtr> transactionsGetDetail(HttpRequestPtr req, std::string tellerId,
                                                std::string transactionId);
    Task<HttpResponsePtr> journalsGetAll(HttpRequestPtr req, std::string tellerId);

    Task<HttpResponsePtr> cashiersGetAll(HttpRequestPtr req, std::string tellerId);
    Task<HttpResponsePtr> cashiersCreate(HttpRequestPtr req, std::string tellerId);
    Task<HttpResponsePtr> cashiersTemplate(HttpRequestPtr req, std::string tellerId);
    Task<HttpResponsePtr> cashiersGetDetail(HttpRequestPtr req, std::string tellerId, std::string cashierId);
    Task<HttpResponsePtr> cashiersUpdate(HttpRequestPtr req, std::string tellerId, std::string cashierId);
    Task<HttpResponsePtr> cashiersDelete(HttpRequestPtr req, std::string tellerId, std::string cashierId);

    Task<HttpResponsePtr> cashierTransactionsGetAll(HttpRequestPtr req, std::string tellerId,
                                                    std::string cashierId);
    Task<HttpResponsePtr> cashierTransactionsTemplate(HttpRequestPtr req, std::string tellerId,
                                                      std::string cashierId);
    Task<HttpResponsePtr> cashierSummaryAndTransactions(HttpRequestPtr req, std::string tellerId,
                                                        std::string cashierId);
    Task<HttpResponsePtr> allocateCashToCashier(HttpRequestPtr req, std::string tellerId,
                                                std::string cashierId);
    Task<HttpResponsePtr> settleCashToCashier(HttpRequestPtr req, std::string tellerId, std::string cashierId);
};
