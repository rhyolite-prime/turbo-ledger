//
// Phase 2 — payment types (5 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class PaymentTypesController : public drogon::HttpController<PaymentTypesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/paymenttypes/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(PaymentTypesController::getAll,     std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(PaymentTypesController::create,     std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(PaymentTypesController::getDetails, std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(PaymentTypesController::update,     std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(PaymentTypesController::remove,     std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
