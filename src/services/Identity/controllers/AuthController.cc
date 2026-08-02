#include "AuthController.h"
#include "dto/BaseApiResponse.h"
#include "plugins/IdentityServicePlugin.h"
#include "dto/SigninDto.h"

using namespace drogon;
using namespace turbo_ledger_identity::plugins;
using namespace turbo_ledger_identity::dto;

Task<HttpResponsePtr> AuthController::signIn(HttpRequestPtr req) {
    auto json = req->getJsonObject();
    BaseApiResponse apiResponse;
    if (!json) {
        apiResponse.success = false;
        apiResponse.message = "Invalid JSON payload";
        auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    SigninDto dto;
    dto.fromJson(*json);

    auto *plugin = app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.validateUserCredentials(dto);

    auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
    resp->setStatusCode(result.success ? k200OK : k401Unauthorized);
    co_return resp;
}


Task<HttpResponsePtr> AuthController::sendOtp(HttpRequestPtr req) {
    BaseApiResponse apiResponse;
    apiResponse.success = false;
    apiResponse.message = "Not implemented";
    auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
    resp->setStatusCode(k501NotImplemented);
    co_return resp;
}

Task<HttpResponsePtr> AuthController::verifyOtp(HttpRequestPtr req) {
    BaseApiResponse apiResponse;
    apiResponse.success = false;
    apiResponse.message = "Not implemented";
    auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
    resp->setStatusCode(k501NotImplemented);
    co_return resp;
}

Task<HttpResponsePtr> AuthController::changeUserPassword(HttpRequestPtr req) {
    BaseApiResponse apiResponse;
    apiResponse.success = false;
    apiResponse.message = "Not implemented";
    auto resp = HttpResponse::newHttpJsonResponse(apiResponse.toJson());
    resp->setStatusCode(k501NotImplemented);
    co_return resp;
}