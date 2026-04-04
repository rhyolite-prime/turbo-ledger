#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class PaymentTypesController : public drogon::HttpController<PaymentTypesController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/payment-types/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(PaymentTypesController::getPaymentTypes, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(PaymentTypesController::createPaymentType, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(PaymentTypesController::getPaymentTypeDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(PaymentTypesController::updatePaymentType, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(PaymentTypesController::deletePaymentType, std::string(PREFIX) + "{1}", Delete);
    METHOD_LIST_END

    void getPaymentTypes(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createPaymentType(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getPaymentTypeDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updatePaymentType(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deletePaymentType(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
