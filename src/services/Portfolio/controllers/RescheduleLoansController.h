#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class RescheduleLoansController : public drogon::HttpController<RescheduleLoansController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/reschedule-loans/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RescheduleLoansController::retrieveTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(RescheduleLoansController::getLoanRescheduleRequest, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(RescheduleLoansController::createLoanRescheduleRequest, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(RescheduleLoansController::previewLoanRepaymentSchedule, std::string(PREFIX) + "{1}/preview-loan-reschedule", Get);
    ADD_METHOD_TO(RescheduleLoansController::rejectLoanRescheduleRequest, std::string(PREFIX) + "{1}/reject", Post);
    ADD_METHOD_TO(RescheduleLoansController::approveLoanRescheduleRequest, std::string(PREFIX) + "{1}/approve", Post);
    METHOD_LIST_END

    void retrieveTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getLoanRescheduleRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createLoanRescheduleRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void previewLoanRepaymentSchedule(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void rejectLoanRescheduleRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void approveLoanRescheduleRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
