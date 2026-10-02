//
// Phase 5 — fixeddepositaccounts (17 endpoints: 13 implemented + 4
// bulk-import template download/upload 501 stubs — see
// SavingsAccountsController's header note for the same precedent). Backed
// by the shared savings_account table (deposit_type=FIXED_DEPOSIT) plus the
// 1:1 deposit_account_term_and_preclosure table for term/pre-closure terms.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class FixedDepositAccountsController
    : public drogon::HttpController<FixedDepositAccountsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/fixeddepositaccounts/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(FixedDepositAccountsController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::getDetails,
                     std::string(PREFIX) + "get-detail/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::update, std::string(PREFIX) + "{1}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::remove, std::string(PREFIX) + "{1}/delete", Delete,
                     Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::command, std::string(PREFIX) + "{1}/command/{2}",
                     Post, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::closureTemplate,
                     std::string(PREFIX) + "{1}/closure-template", Get, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::templateEndpoint, std::string(PREFIX) + "template",
                     Get, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::downloadTemplate,
                     std::string(PREFIX) + "downloadtemplate", Get, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::uploadTemplate,
                     std::string(PREFIX) + "uploadtemplate", Post, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::transactionDownloadTemplate,
                     std::string(PREFIX) + "transaction/downloadtemplate", Get, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::transactionUploadTemplate,
                     std::string(PREFIX) + "transaction/uploadtemplate", Post, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::calculateInterest,
                     std::string(PREFIX) + "calculate-fd-interest", Get, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::transactionsTemplate,
                     std::string(PREFIX) + "{1}/transactions/template", Get, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::transactionsGetDetail,
                     std::string(PREFIX) + "{1}/transactions/get-detail/{2}", Get, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::transactionsCommand,
                     std::string(PREFIX) + "{1}/transactions/{2}/command/{3}", Post, Options, FILTER);
        ADD_METHOD_TO(FixedDepositAccountsController::transactionsCreate,
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
    Task<HttpResponsePtr> transactionDownloadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> transactionUploadTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> calculateInterest(HttpRequestPtr req);
    Task<HttpResponsePtr> transactionsTemplate(HttpRequestPtr req, std::string accountId);
    Task<HttpResponsePtr> transactionsGetDetail(HttpRequestPtr req, std::string accountId,
                                                std::string transactionId);
    Task<HttpResponsePtr> transactionsCommand(HttpRequestPtr req, std::string accountId,
                                              std::string transactionId, std::string cmd);
    Task<HttpResponsePtr> transactionsCreate(HttpRequestPtr req, std::string accountId);
};
