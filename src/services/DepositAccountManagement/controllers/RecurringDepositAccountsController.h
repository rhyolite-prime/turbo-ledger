//
// Phase 5 — recurringdepositaccounts (16 endpoints: 12 implemented + 4
// bulk-import template download/upload 501 stubs — see
// SavingsAccountsController's header note for the same precedent). Backed
// by the shared savings_account table (deposit_type=RECURRING_DEPOSIT) plus the
// 1:1 deposit_account_term_and_preclosure table for term/pre-closure terms.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class RecurringDepositAccountsController
    : public drogon::HttpController<RecurringDepositAccountsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/recurringdepositaccounts/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(RecurringDepositAccountsController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::getDetails,
                     std::string(PREFIX) + "get-detail/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::update, std::string(PREFIX) + "{1}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::remove, std::string(PREFIX) + "{1}/delete", Delete,
                     Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::command, std::string(PREFIX) + "{1}/command/{2}",
                     Post, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::closureTemplate,
                     std::string(PREFIX) + "{1}/closure-template", Get, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::templateEndpoint, std::string(PREFIX) + "template",
                     Get, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::downloadTemplate,
                     std::string(PREFIX) + "downloadtemplate", Get, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::uploadTemplate,
                     std::string(PREFIX) + "uploadtemplate", Post, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::transactionsDownloadTemplate,
                     std::string(PREFIX) + "transactions/downloadtemplate", Get, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::transactionsUploadTemplate,
                     std::string(PREFIX) + "transactions/uploadtemplate", Post, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::transactionsTemplate,
                     std::string(PREFIX) + "{1}/transactions/template", Get, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::transactionsGetDetail,
                     std::string(PREFIX) + "{1}/transactions/get-detail/{2}", Get, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::transactionsCommand,
                     std::string(PREFIX) + "{1}/transactions/{2}/command/{3}", Post, Options, FILTER);
        ADD_METHOD_TO(RecurringDepositAccountsController::transactionsCreate,
                     std::string(PREFIX) + "{1}/transactions/create", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> command(HttpRequestPtr req, std::string id, std::string cmd);
    Task<HttpResponsePtr> closureTemplate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> downloadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> uploadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> transactionsDownloadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> transactionsUploadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> transactionsTemplate(HttpRequestPtr req, std::string accountId);
    Task<HttpResponsePtr> transactionsGetDetail(HttpRequestPtr req, std::string accountId,
                                                std::string transactionId);
    Task<HttpResponsePtr> transactionsCommand(HttpRequestPtr req, std::string accountId,
                                              std::string transactionId, std::string cmd);
    Task<HttpResponsePtr> transactionsCreate(HttpRequestPtr req, std::string accountId);
};
