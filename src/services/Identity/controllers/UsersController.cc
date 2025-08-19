#include "UsersController.h"
#include "dto/CreateUserDto.h"
#include "dto/BaseApiResponse.h"
#include "dto/ErrorCodes.h"
#include "dto/SigninDto.h"
#include "dto/UpdateUserDto.h"
#include "plugins/IdentityServicePlugin.h"


void UsersController::getUsers(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
    int pageSize = 10; // Default page size
    int pageNo = 1;    // Default page number

    if (!req->getParameter("pageSize").empty()) {
        try {
            pageSize = std::stoi(req->getParameter("pageSize"));
            pageSize = std::max(1, std::min(100, pageSize)); // Limit between 1-100
        } catch (...) {
            // Keep default if conversion fails
        }
    }

    if (!req->getParameter("pageNo").empty()) {
        try {
            pageNo = std::stoi(req->getParameter("pageNo"));
            pageNo = std::max(1, pageNo); // Ensure page number is at least 1
        } catch (...) {
            // Keep default if conversion fails
        }
    }

       std::string tenantId;
        try {
            tenantId = getTenantFromRequest(req);
        } catch (const std::runtime_error& e) {
            // Handle error (e.g., return 400 Bad Request)
        }

    std::string query = req->getParameter("query");
    if (query.empty()) {
        query = ""; // Default to empty string if not specified
    }

    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    // Call service and return response
    userService.getUsers(pageNo, pageSize, query, tenantId, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        callback(resp);
    });

}

void UsersController::generateAuthToken(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
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

    turbo_ledger_identity::dto::CreateUserDto userData;

    try {

        userData.fromJson(*jsonBody);

    } catch (const std::exception& e) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing or invalid required fields";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    // Get tenant ID from the request via the helper in BaseController
    std::string tenantId;
    try
    {
        tenantId = getTenantFromRequest(req);
    }
    catch (const std::runtime_error& e)
    {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = e.what();
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

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

    turbo_ledger_identity::dto::UpdateUserDto userData;

    try {

        userData.fromJson(*jsonBody);

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

    userService.updateUser(userData, tenantId, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        resp->setStatusCode(result.success ? k200OK : k500InternalServerError);
        callback(resp);
    });
}

void UsersController::lockUserAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // Extract user ID from the path parameters
    auto userId = req->getParameter("id");

    if (userId.empty()) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "User ID is required";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    // Get tenant ID from the request
    std::string tenantId = getTenantFromRequest(req);

    // Get the user service from the plugin
    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    // Call the service to lock the user account
    userService.lockUserAccount(userId, tenantId, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        resp->setStatusCode(result.success ? k200OK : (result.error.isMember("code") &&
                                                     result.error["code"].asInt() == turbo_ledger_identity::ERR_RESOURCE_NOT_FOUND ?
                                                     k404NotFound : k500InternalServerError));
        callback(resp);
    });
}

void UsersController::unLockUserAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // Extract user ID from the path parameters
    auto userId = req->getParameter("id");

    if (userId.empty()) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "User ID is required";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    // Get tenant ID from the request
    std::string tenantId = getTenantFromRequest(req);

    // Get the user service from the plugin
    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    // Call the service to unlock the user account
    userService.unlockUserAccount(userId, tenantId, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        resp->setStatusCode(result.success ? k200OK : (result.error.isMember("code") &&
                                                     result.error["code"].asInt() == turbo_ledger_identity::ERR_RESOURCE_NOT_FOUND ?
                                                     k404NotFound : k500InternalServerError));
        callback(resp);
    });
}

void UsersController::deleteUser(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // Extract user ID from the path parameters
    auto userId = req->getParameter("id");

    if (userId.empty()) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "User ID is required";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    // Get tenant ID from the request
    std::string tenantId = getTenantFromRequest(req);

    // Get the user service from the plugin
    auto plugin = drogon::app().getPlugin<turbo_ledger_identity::plugins::IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    // Call the service to delete the user
    userService.deleteUser(userId, tenantId, [callback](const turbo_ledger_identity::dto::BaseApiResponse& result) {
        auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
        resp->setStatusCode(result.success ? k200OK : (result.error.isMember("code") &&
                                                     result.error["code"].asInt() == turbo_ledger_identity::ERR_RESOURCE_NOT_FOUND ?
                                                     k404NotFound : k500InternalServerError));
        callback(resp);
    });
}