//
// Phase 6 — external-asset-owners (12 endpoints in the inventory; 2 are
// external-id-mirror variants of "transfer request" that are skipped per the
// same external-id-mirror scope trim as LoansController — 10 wired here).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ExternalAssetOwnersController
    : public drogon::HttpController<ExternalAssetOwnersController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/external-asset-owners/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ExternalAssetOwnersController::transfersGetAll,
                     std::string(PREFIX) + "transfers/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ExternalAssetOwnersController::transfersSearch, std::string(PREFIX) + "transfers/search",
                     Post, Options, FILTER);
        ADD_METHOD_TO(ExternalAssetOwnersController::activeTransfer,
                     std::string(PREFIX) + "transfers/active-transfer", Get, Options, FILTER);
        ADD_METHOD_TO(ExternalAssetOwnersController::createTransfer,
                     std::string(PREFIX) + "transfers/loans/{1}/create", Post, Options, FILTER);
        ADD_METHOD_TO(ExternalAssetOwnersController::transferCommand,
                     std::string(PREFIX) + "transfers/{1}/command/{2}", Post, Options, FILTER);
        ADD_METHOD_TO(ExternalAssetOwnersController::transferJournalEntries,
                     std::string(PREFIX) + "transfers/{1}/journal-entries", Get, Options, FILTER);
        ADD_METHOD_TO(ExternalAssetOwnersController::ownerJournalEntries,
                     std::string(PREFIX) + "owners/{1}/journal-entries", Get, Options, FILTER);
        ADD_METHOD_TO(ExternalAssetOwnersController::loanProductAttrsGetAll,
                     std::string(PREFIX) + "loan-product/{1}/attributes/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ExternalAssetOwnersController::loanProductAttrsCreate,
                     std::string(PREFIX) + "loan-product/{1}/attributes/create", Post, Options, FILTER);
        ADD_METHOD_TO(ExternalAssetOwnersController::loanProductAttrsUpdate,
                     std::string(PREFIX) + "loan-product/{1}/attributes/{2}/update", Put, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> transfersGetAll(HttpRequestPtr req);
    Task<HttpResponsePtr> transfersSearch(HttpRequestPtr req);
    Task<HttpResponsePtr> activeTransfer(HttpRequestPtr req);
    Task<HttpResponsePtr> createTransfer(HttpRequestPtr req, std::string loanId);
    Task<HttpResponsePtr> transferCommand(HttpRequestPtr req, std::string transferId, std::string cmd);
    Task<HttpResponsePtr> transferJournalEntries(HttpRequestPtr req, std::string transferId);
    Task<HttpResponsePtr> ownerJournalEntries(HttpRequestPtr req, std::string ownerExternalId);
    Task<HttpResponsePtr> loanProductAttrsGetAll(HttpRequestPtr req, std::string loanProductId);
    Task<HttpResponsePtr> loanProductAttrsCreate(HttpRequestPtr req, std::string loanProductId);
    Task<HttpResponsePtr> loanProductAttrsUpdate(HttpRequestPtr req, std::string loanProductId,
                                                std::string id);
};
