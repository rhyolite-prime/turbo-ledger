//
// Phase 9 — self/loanproducts, self/loans* (composes Portfolio).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SelfLoansController : public drogon::HttpController<SelfLoansController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/self/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(SelfLoansController::loanProductsAll, std::string(PREFIX) + "loanproducts", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SelfLoansController::loanProductDetail,
                     std::string(PREFIX) + "loanproducts/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(SelfLoansController::loansTemplate, std::string(PREFIX) + "loans/template", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SelfLoansController::getLoan, std::string(PREFIX) + "loans/{1}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(SelfLoansController::createLoan, std::string(PREFIX) + "loans", Post, Options,
                     FILTER);
        ADD_METHOD_TO(SelfLoansController::loanCommand, std::string(PREFIX) + "loans/{1}", Post, Options,
                     FILTER);
        ADD_METHOD_TO(SelfLoansController::chargesAll, std::string(PREFIX) + "loans/{1}/charges", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SelfLoansController::chargeDetail,
                     std::string(PREFIX) + "loans/{1}/charges/{2}", Get, Options, FILTER);
        ADD_METHOD_TO(SelfLoansController::guarantors, std::string(PREFIX) + "loans/{1}/guarantors", Get,
                     Options, FILTER);
        ADD_METHOD_TO(SelfLoansController::transactionDetail,
                     std::string(PREFIX) + "loans/{1}/transactions/{2}", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> loanProductsAll(HttpRequestPtr req);
    Task<HttpResponsePtr> loanProductDetail(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> loansTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> getLoan(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> createLoan(HttpRequestPtr req);
    Task<HttpResponsePtr> loanCommand(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> chargesAll(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> chargeDetail(HttpRequestPtr req, std::string id, std::string chargeId);
    Task<HttpResponsePtr> guarantors(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> transactionDetail(HttpRequestPtr req, std::string id,
                                            std::string transactionId);
};
