#include "OfficeController.h"
#include "dto/BaseApiResponse.h"

void OfficeController::getOffices(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {

  turbo_ledger_office::dto::BaseApiResponse response;
  response.success = true;

  Json::Value office;
  office["id"] = 1;
  office["name"] = "Head Office";
  office["nameDecorated"] = "Head Office";
  office["externalId"] = "1";

  office["openingDate"] = "23-02-2026";

  office["hierarchy"] = ".";

  Json::Value offices(Json::arrayValue);
  offices.append(office);

  response.result = offices;
  response.message = "Offices retrieved successfully";

  auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
  callback(resp);
}

void OfficeController::createOffice(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {

  turbo_ledger_office::dto::BaseApiResponse response;
  response.success = true;

  Json::Value result;
  result["officeId"] = 3;
  result["resourceId"] = 3;

  response.result = result;
  response.message = "Office created successfully";

  auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
  callback(resp);
}

void OfficeController::retrieveTemplate(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
  turbo_ledger_office::dto::BaseApiResponse response;
  response.success = true;

  Json::Value result;
  result["openingDate"] = "02-02-2026";

  Json::Value parent;
  parent["id"] = 1;
  parent["name"] = "Head Office";
  parent["nameDecorated"] = "Head Office";

  Json::Value allowedParents(Json::arrayValue);
  allowedParents.append(parent);

  result["allowedParents"] = allowedParents;

  response.result = result;
  response.message = "Template retrieved successfully";

  auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
  callback(resp);
}

void OfficeController::getOfficeDetails(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
  turbo_ledger_office::dto::BaseApiResponse response;
  response.success = true;

  Json::Value office;
  office["id"] = 1;
  office["name"] = "Head Office";
  office["nameDecorated"] = "Head Office";
  office["externalId"] = "1";

  office["openingDate"] = "02-02-2026";

  office["hierarchy"] = ".";

  response.result = office;
  response.message = "Office details retrieved successfully";

  auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
  callback(resp);
}

void OfficeController::updateOffice(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string officeId) {

  turbo_ledger_office::dto::BaseApiResponse response;
  response.success = true;

  Json::Value result;
  result["officeId"] = officeId;
  result["resourceId"] = officeId;

  Json::Value changes;
  changes["name"] = "Name is updated";

  result["changes"] = changes;

  response.result = result;
  response.message = "Office updated successfully";

  auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
  callback(resp);
}
