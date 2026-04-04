#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class LoanProductsController : public drogon::HttpController<LoanProductsController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/loan-products/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(LoanProductsController::getLoanProducts, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(LoanProductsController::getLoanProductMix, std::string(PREFIX) + "get-mix", Get);
    ADD_METHOD_TO(LoanProductsController::getLoanProductMixTemplate, std::string(PREFIX) + "get-mix-template", Get);
    ADD_METHOD_TO(LoanProductsController::getLoanProductDetails, std::string(PREFIX) + "get-details", Get);
    ADD_METHOD_TO(LoanProductsController::getLoanProductTemplate, std::string(PREFIX) + "get-template", Get);
    ADD_METHOD_TO(LoanProductsController::createLoanProduct, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(LoanProductsController::updateLoanProduct, std::string(PREFIX) + "{1}" , Put);
    ADD_METHOD_TO(LoanProductsController::retrieveLoanProductMix, std::string(PREFIX) + "{1}/product-mix" , Get);
    ADD_METHOD_TO(LoanProductsController::createLoanProductMix, std::string(PREFIX) + "{1}/product-mix" , Post);
    ADD_METHOD_TO(LoanProductsController::updateLoanProductMix, std::string(PREFIX) + "{1}/product-mix" , Put);
    ADD_METHOD_TO(LoanProductsController::deleteLoanProductMix, std::string(PREFIX) + "{1}/product-mix" , Delete);

    METHOD_LIST_END

    // handler methods
  void getLoanProducts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getLoanProductMix(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getLoanProductMixTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getLoanProductDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getLoanProductTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void createLoanProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

  void updateLoanProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string loanProductId);
  void retrieveLoanProductMix(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string loanProductId);

  void createLoanProductMix(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string loanProductId);
  void updateLoanProductMix(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string loanProductId);
  void deleteLoanProductMix(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string loanProductId);

};
