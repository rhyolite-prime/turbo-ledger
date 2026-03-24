#include "WorkingDaysController.h"

#include "dto/BaseApiResponse.h"

void WorkingDaysController::getWorkingDaysTemplate(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto jsonBody = req->getJsonObject();
    (void)jsonBody;

    turbo_ledger_global_configuration::dto::BaseApiResponse response;
    response.success = true;
    response.message = "Holiday updated successfully";

    Json::Value result;
    result["resourceId"] = 1;

    Json::Value repaymentRescheduleOptions(Json::arrayValue);

    Json::Value option1;
    option1["id"] = 1;
    option1["code"] = "RepaymentRescheduleType.same.day";
    option1["value"] = "same day";
    repaymentRescheduleOptions.append(option1);

    Json::Value option2;
    option2["id"] = 4;
    option2["code"] = "RepaymentRescheduleType.move.to.previous.working.day";
    option2["value"] = "move to previous working day";
    repaymentRescheduleOptions.append(option2);

    Json::Value option3;
    option3["id"] = 3;
    option3["code"] = "RepaymentRescheduleType.move.to.next.repayment.meeting.day";
    option3["value"] = "move to next repayment meeting day";
    repaymentRescheduleOptions.append(option3);

    Json::Value option4;
    option4["id"] = 2;
    option4["code"] = "RepaymentRescheduleType.move.to.next.working.day";
    option4["value"] = "move to next working day";
    repaymentRescheduleOptions.append(option4);

    result["repaymentRescheduleOptions"] = repaymentRescheduleOptions;
    response.result = result;

    auto resp = HttpResponse::newHttpJsonResponse(response.toJson());
    callback(resp);

}
