//
// Phase 9 — interoperation/quotes*, interoperation/requesttopay* (4
// endpoints, local genuinely-computed workflow state).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class QuotesController : public drogon::HttpController<QuotesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/interoperation/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(QuotesController::createQuote, std::string(PREFIX) + "quotes", Post, Options,
                     FILTER);
        ADD_METHOD_TO(QuotesController::getQuote, std::string(PREFIX) + "quotes/{1}/{2}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(QuotesController::createRequest, std::string(PREFIX) + "requesttopay", Post,
                     Options, FILTER);
        ADD_METHOD_TO(QuotesController::getRequest, std::string(PREFIX) + "requesttopay/{1}/{2}", Get,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> createQuote(HttpRequestPtr req);
    Task<HttpResponsePtr> getQuote(HttpRequestPtr req, std::string transactionCode, std::string quoteCode);
    Task<HttpResponsePtr> createRequest(HttpRequestPtr req);
    Task<HttpResponsePtr> getRequest(HttpRequestPtr req, std::string transactionCode,
                                     std::string requestCode);
};
