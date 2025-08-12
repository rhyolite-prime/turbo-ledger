#include "UsersController.h"
#include "dto/CreateUserDto.h"
#include "dto/BaseApiResponse.h"
#include "plugins/IdentityServicePlugin.h"

// Constructor implementation for dependency injection
UsersController::UsersController()
{

}

void UsersController::getUsers(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}

void UsersController::generateAuthToken(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}


void UsersController::createUser(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // Parse JSON request body
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

    // Convert JSON to DTO
    turbo_ledger_identity::dto::CreateUserDto userData;
    try {
        userData.setFirstName((*jsonBody)["firstName"].asString());
        userData.setLastName((*jsonBody)["lastName"].asString());
        userData.setUsername((*jsonBody)["username"].asString());
        userData.setPassword((*jsonBody)["password"].asString());
    } catch (const std::exception& e) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing or invalid required fields";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    // Get tenant ID from headers or request
    std::string tenantId = req->getHeader("X-Tenant-ID");
    if (tenantId.empty()) {
        tenantId = "default"; // Default tenant if not specified
    }

    // Call service and return response
    // Access service through plugin
    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    // Call service and return response
    userService.createUser(userData, tenantId, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        resp->setStatusCode(result.success ? k201Created : k500InternalServerError);
        callback(resp);
    });

}

void UsersController::updateUser(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}

void UsersController::lockUserAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}

void UsersController::unLockUserAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}

void UsersController::deleteUser(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}