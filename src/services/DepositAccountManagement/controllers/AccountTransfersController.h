//
// Phase 5 — accounttransfers (6 endpoints: 4 implemented + 2
// refundByTransfer 501 stubs — "Refund of an Active Loan by Transfer" and
// its template require a Portfolio/loans service that does not exist yet in
// this codebase; documented scope trim, see
// DepositAccountManagementService.h's header note).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AccountTransfersController : public drogon::HttpController<AccountTransfersController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/accounttransfers/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(AccountTransfersController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(AccountTransfersController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(AccountTransfersController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(AccountTransfersController::templateEndpoint, std::string(PREFIX) + "template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(AccountTransfersController::refundByTransfer,
                     std::string(PREFIX) + "refund-by-transfer", Post, Options, FILTER);
        ADD_METHOD_TO(AccountTransfersController::refundByTransferTemplate,
                     std::string(PREFIX) + "refund-by-transfer/template", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> refundByTransfer(HttpRequestPtr req);
    Task<HttpResponsePtr> refundByTransferTemplate(HttpRequestPtr req);
};
