#include "AccountingController.h"

#include "dto/BaseApiResponse.h"
#include "plugins/AccountingServicePlugin.h"


Task<AccountingController::AuthResult> AccountingController::authenticateRequest(HttpRequestPtr req) {
    AuthResult result;
    auto clientId = req->getHeader("ClientId");
    auto clientSecret = req->getHeader("ClientSecret");

    if (clientId.empty() || clientSecret.empty()) {
        turbo_ledger_accounting::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "ClientId and ClientSecret Headers are absent !";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        result.errorResponse = resp;
        co_return result;
    }

    auto plugin = drogon::app().getPlugin<turbo_ledger_accounting::plugins::AccountingServicePlugin>();
    auto &identityApi = plugin->getIdentityApi();

    auto businessIdentity = co_await identityApi.validateApiCredentials(clientId, clientSecret);

    if (!businessIdentity.isValid) {
        turbo_ledger_accounting::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = businessIdentity.errorMessage.empty() ? "Invalid API credentials" : businessIdentity.errorMessage;
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k401Unauthorized);
        result.errorResponse = resp;
        co_return result;
    }

    result.isValid = true;
    result.businessId = businessIdentity.businessId;
    co_return result;
}


Task<HttpResponsePtr> AccountingController::getAllGlAccounts(HttpRequestPtr req) {


}

Task<HttpResponsePtr> AccountingController::getGlAccountDetails(HttpRequestPtr req, std::string accountId) {


}


Task<HttpResponsePtr> AccountingController::createGlAccount(HttpRequestPtr req) {


}