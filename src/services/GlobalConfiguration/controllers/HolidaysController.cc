#include "HolidaysController.h"

#include "dto/BaseApiResponse.h"

void HolidaysController::getHolidays(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here

    auto officeId = req->getParameter("officeId");
    Json::Value holidays(Json::arrayValue);

    Json::Value holiday;
    holiday["id"] = 1;
    holiday["name"] = "Good Friday";

    holiday["fromDate"] = Json::arrayValue;
    holiday["fromDate"].append(2013);
    holiday["fromDate"].append(10);
    holiday["fromDate"].append(25);

    holiday["toDate"] = Json::arrayValue;
    holiday["toDate"].append(2013);
    holiday["toDate"].append(10);
    holiday["toDate"].append(25);

    holiday["repaymentsScheduleTo"] = Json::arrayValue;
    holiday["repaymentsScheduleTo"].append(2013);
    holiday["repaymentsScheduleTo"].append(10);
    holiday["repaymentsScheduleTo"].append(26);

    Json::Value status;
    status["id"] = 100;
    status["code"] = "holidayStatusType.pending.for.activation";
    status["value"] = "Pending for activation";
    holiday["status"] = status;

    holidays.append(holiday);

    auto response = HttpResponse::newHttpJsonResponse(holidays);
    callback(response);

}


void HolidaysController::createHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {


    turbo_ledger_global_configuration::dto::BaseApiResponse response;
    response.success = true;

    Json::Value result;
    result["resourceId"] = 1;

    response.result = result;
    response.message = "Holiday created successfully";

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    callback(resp);

}

void HolidaysController::activateHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string holidayId) {

    turbo_ledger_global_configuration::dto::BaseApiResponse response;
    response.success = true;

    Json::Value result;
    result["resourceId"] = holidayId;

    response.result = result;
    response.message = "Holiday activated successfully";

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    callback(resp);

}

void HolidaysController::retrieveHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string holidayId) {

    Json::Value holiday;
    holiday["id"] = holidayId;
    holiday["name"] = "Good Friday";

    holiday["fromDate"] = Json::Value(Json::arrayValue);
    holiday["fromDate"].append(2013);
    holiday["fromDate"].append(10);
    holiday["fromDate"].append(25);

    holiday["toDate"] = Json::Value(Json::arrayValue);
    holiday["toDate"].append(2013);
    holiday["toDate"].append(10);
    holiday["toDate"].append(25);

    holiday["repaymentsRescheduledTo"] = Json::Value(Json::arrayValue);
    holiday["repaymentsRescheduledTo"].append(2013);
    holiday["repaymentsRescheduledTo"].append(10);
    holiday["repaymentsRescheduledTo"].append(26);

    Json::Value status;
    status["id"] = 100;
    status["code"] = "holidayStatusType.active";
    status["value"] = "Active";
    holiday["status"] = status;

    auto resp = HttpResponse::newHttpJsonResponse(holiday);
    callback(resp);

}

void HolidaysController::updateHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string holidayId) {

    auto jsonBody = req->getJsonObject();

    turbo_ledger_global_configuration::dto::BaseApiResponse response;
    response.success = true;

    Json::Value result;
    result["resourceId"] = holidayId;

    if (jsonBody && jsonBody->isMember("resourceId")) {
        result["resourceId"] = (*jsonBody)["resourceId"];
    }

    response.result = result;
    response.message = "Holiday updated successfully";

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    callback(resp);


}

void HolidaysController::deleteHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string holidayId) {


    turbo_ledger_global_configuration::dto::BaseApiResponse response;
    response.success = true;

    Json::Value result;
    result["resourceId"] = 1;

    response.result = result;
    response.message = "Holiday deleted successfully";

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    callback(resp);

}