#include "UsersController.h"
#include "dto/BaseApiResponse.h"
#include "dto/SigninDto.h"
#include "dto/UserDto.h"
#include "plugins/IdentityServicePlugin.h"

using namespace turbo_ledger_identity::plugins;


Task<HttpResponsePtr> UsersController::getAllUsers(HttpRequestPtr req) {
    int pageSize = 10;
    int pageNo = 1;

    if (!req->getParameter("pageSize").empty()) {
        try { pageSize = std::max(1, std::min(100, std::stoi(req->getParameter("pageSize")))); } catch (...) {}
    }
    if (!req->getParameter("pageNo").empty()) {
        try { pageNo = std::max(1, std::stoi(req->getParameter("pageNo"))); } catch (...) {}
    }

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    std::string query = req->getParameter("query");

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.getAll(businessId, pageNo, pageSize, query);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> UsersController::getDetails(HttpRequestPtr req, std::string id) {
    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.getDetails(businessId, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}


Task<HttpResponsePtr> UsersController::signIn(HttpRequestPtr req) {

    auto jsonBody = req->getJsonObject();
    if (!jsonBody) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Invalid JSON body";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }


    turbo_ledger_identity::dto::SigninDto signin_dto;
    try {
        signin_dto.fromJson(*jsonBody);
    } catch (const std::exception& e) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing or invalid required fields";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.validateUserCredentials(signin_dto);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k500InternalServerError);
    co_return resp;
}

Task<HttpResponsePtr> UsersController::lockUserAccount(HttpRequestPtr req, std::string id) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.lockUserAccount(businessId, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> UsersController::unLockUserAccount(HttpRequestPtr req, std::string id) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.unlockUserAccount(businessId, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> UsersController::activateAccount(HttpRequestPtr req, std::string id) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.activateUserAccount(businessId, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> UsersController::deActivateAccount(HttpRequestPtr req, std::string id) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.deactivateUserAccount(businessId, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> UsersController::createUser(HttpRequestPtr req) {
    auto jsonBody = req->getJsonObject();
    if (!jsonBody) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Invalid JSON body";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    turbo_ledger_identity::dto::UserDto userData;
    try {
        userData.fromJson(*jsonBody);
    } catch (const std::exception& e) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing or invalid required fields";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.create(businessId, userData);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k201Created : k500InternalServerError);
    co_return resp;
}

Task<HttpResponsePtr> UsersController::updateUser(HttpRequestPtr req, std::string id) {
    auto jsonBody = req->getJsonObject();
    if (!jsonBody) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Invalid JSON body";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    turbo_ledger_identity::dto::UserDto userData;
    try {
        userData.fromJson(*jsonBody);
    } catch (const std::exception& e) {
        turbo_ledger_identity::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Missing or invalid required fields";
        auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.update(businessId, userData, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    resp->setStatusCode(result.success ? k200OK : k500InternalServerError);
    co_return resp;
}

Task<HttpResponsePtr> UsersController::deleteUser(HttpRequestPtr req, std::string id) {

    std::string businessId;
    try { businessId = req->attributes()->get<std::string>("businessId"); } catch (...) {}

    auto plugin = drogon::app().getPlugin<IdentityServicePlugin>();
    auto& userService = plugin->getUserService();

    auto result = co_await userService.deleteUser(businessId, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}