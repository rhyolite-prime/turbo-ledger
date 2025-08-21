#include "TokenAuthController.h"

#include "dto/BaseApiResponse.h"
#include "dto/SigninDto.h"
#include "plugins/IdentityServicePlugin.h"



void TokenAuthController::generateAuthToken(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{

    auto jsonBody = req->getJsonObject();

    if (!jsonBody) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Invalid JSON body";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    std::string tenantId = getTenantFromRequest(req);

    turbo_ledger_identity::dto::SigninDto signin_dto;

    try {

        signin_dto.fromJson(*jsonBody);

    } catch (const std::exception& e) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing or invalid required fields";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    userService.validateUserCredentials(signin_dto, tenantId, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
       auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
       resp->setStatusCode(result.success ? k200OK : k500InternalServerError);
       callback(resp);
   });




}
