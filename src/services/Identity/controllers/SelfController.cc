#include "SelfController.h"

#include "dto/BaseApiResponse.h"

Task<HttpResponsePtr> SelfController::signIn(HttpRequestPtr req) {
    turbo_ledger_identity::dto::BaseApiResponse apiResponse;
    apiResponse.success = false;
    apiResponse.message = "Not implemented";
    auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
    resp->setStatusCode(k501NotImplemented);
    co_return resp;
}


Task<HttpResponsePtr> SelfController::getDetails(HttpRequestPtr req) {
    turbo_ledger_identity::dto::BaseApiResponse apiResponse;
    apiResponse.success = false;
    apiResponse.message = "Not implemented";
    auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
    resp->setStatusCode(k501NotImplemented);
    co_return resp;

}

Task<HttpResponsePtr> SelfController::updateDetails(HttpRequestPtr req) {
    turbo_ledger_identity::dto::BaseApiResponse apiResponse;
    apiResponse.success = false;
    apiResponse.message = "Not implemented";
    auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
    resp->setStatusCode(k501NotImplemented);
    co_return resp;

}