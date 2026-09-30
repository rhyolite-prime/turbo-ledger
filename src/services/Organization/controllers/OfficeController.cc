#include "OfficeController.h"

#include "plugins/OrganizationServicePlugin.h"


Task<HttpResponsePtr> OfficeController::getOffices(HttpRequestPtr req) {

    int pageNo = 1;
    int pageSize = 10;

    auto pageNoStr = req->getParameter("pageNo");
    if (!pageNoStr.empty()) {
        pageNo = std::stoi(pageNoStr);
    }

    auto pageSizeStr = req->getParameter("pageSize");
    if (!pageSizeStr.empty()) {
        pageSize = std::stoi(pageSizeStr);
    }

    std::string query = req->getParameter("query");
    if (query.empty()) {
        query = "";
    }

    auto plugin = drogon::app().getPlugin<organization::plugins::OrganizationServicePlugin>();
    auto &officeService = plugin->getOfficeService();

    auto result = co_await officeService.getAll(pageNo, pageSize, query);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}

Task<HttpResponsePtr> OfficeController::createOffice(HttpRequestPtr req) {

    auto jsonBody = req->getJsonObject();

    organization::dto::OfficeDto dto;
    dto.fromJson(*jsonBody);

    auto plugin = app().getPlugin<organization::plugins::OrganizationServicePlugin>();
    auto &clientService = plugin->getOfficeService();

    auto result = co_await clientService.createAsync(dto);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> OfficeController::getOfficeDetails(HttpRequestPtr req, std::string id) {

    auto jsonBody = req->getJsonObject();

    organization::dto::OfficeDto dto;
    dto.fromJson(*jsonBody);

    auto plugin = app().getPlugin<organization::plugins::OrganizationServicePlugin>();
    auto &clientService = plugin->getOfficeService();

    auto result = co_await clientService.updateAsync(dto, id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;

}

Task<HttpResponsePtr> OfficeController::updateOffice(HttpRequestPtr req, std::string id) {

    auto plugin = app().getPlugin<organization::plugins::OrganizationServicePlugin>();
    auto &clientService = plugin->getOfficeService();

    auto result = co_await clientService.getOfficeDetails(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}

Task<HttpResponsePtr> OfficeController::deleteOffice(HttpRequestPtr req, std::string id) {

    auto plugin = app().getPlugin<organization::plugins::OrganizationServicePlugin>();
    auto &clientService = plugin->getOfficeService();

    auto result = co_await clientService.deleteOffice(id);
    auto resp = HttpResponse::newHttpJsonResponse(result.toJson());
    co_return resp;
}
