#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ProductsController : public drogon::HttpController<ProductsController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/products/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ProductsController::getShareProducts, std::string(PREFIX) + "share", Get);
    ADD_METHOD_TO(ProductsController::createShareProduct, std::string(PREFIX) + "share", Post); // create a share product
    ADD_METHOD_TO(ProductsController::retrieveShareProduct, std::string(PREFIX) + "share/{1}", Get);
    ADD_METHOD_TO(ProductsController::retrieveShareProductTemplate, std::string(PREFIX) + "share/{1}/template", Get);
    ADD_METHOD_TO(ProductsController::updateShareProduct, std::string(PREFIX) + "share/{1}", Put);
    ADD_METHOD_TO(ProductsController::deleteShareProduct, std::string(PREFIX) + "share/{1}", Delete);
    //savings product
    ADD_METHOD_TO(ProductsController::getSavingsProducts, std::string(PREFIX) + "savings", Get);
    ADD_METHOD_TO(ProductsController::getSavingsProductDetails, std::string(PREFIX) + "savings/{1}", Get);
    ADD_METHOD_TO(ProductsController::retrieveSavingsProductTemplate, std::string(PREFIX) + "savings/{1}/template", Get);
    ADD_METHOD_TO(ProductsController::createSavingsProduct, std::string(PREFIX) + "savings", Post);
    ADD_METHOD_TO(ProductsController::updateSavingsProduct, std::string(PREFIX) + "savings/{1}", Post);
    ADD_METHOD_TO(ProductsController::deleteSavingsProduct, std::string(PREFIX) + "savings/{1}", Post);
    //fixed deposit
    ADD_METHOD_TO(ProductsController::getFixedDepositProducts, std::string(PREFIX) + "fixed-deposit", Get);
    ADD_METHOD_TO(ProductsController::retrieveFixedDepositProductDetails, std::string(PREFIX) + "fixed-deposit/{1}", Get);
    ADD_METHOD_TO(ProductsController::retrieveFixedDepositProductTemplate, std::string(PREFIX) + "fixed-deposit/{1}/template", Get);
    ADD_METHOD_TO(ProductsController::createFixedDepositProduct, std::string(PREFIX) + "fixed-deposit", Post);
    ADD_METHOD_TO(ProductsController::updateFixedDepositProduct, std::string(PREFIX) + "fixed-deposit/{1}", Put);
    ADD_METHOD_TO(ProductsController::deleteFixedDepositProduct, std::string(PREFIX) + "fixed-deposit/{1}", Put);
    //recurring deposit
    ADD_METHOD_TO(ProductsController::getRecurringDepositProducts, std::string(PREFIX) + "recurring-deposit", Get);
    ADD_METHOD_TO(ProductsController::retrieveRecurringDepositProductDetails, std::string(PREFIX) + "recurring-deposit/{1}", Get);
    ADD_METHOD_TO(ProductsController::retrieveRecurringDepositProductTemplate, std::string(PREFIX) + "recurring-deposit/{1}/template", Get);
    ADD_METHOD_TO(ProductsController::createRecurringDepositProduct, std::string(PREFIX) + "recurring-deposit", Post);
    ADD_METHOD_TO(ProductsController::updateRecurringDepositProduct, std::string(PREFIX) + "recurring-deposit/{1}", Put);
    ADD_METHOD_TO(ProductsController::deleteRecurringDepositProduct, std::string(PREFIX) + "recurring-deposit/{1}", Put);

    METHOD_LIST_END

    void getShareProducts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createShareProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveShareProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveShareProductTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateShareProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteShareProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //savings product ...
    void getSavingsProducts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsProductDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveSavingsProductTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createSavingsProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateSavingsProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteSavingsProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    // fixed deposit
    void getFixedDepositProducts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveFixedDepositProductDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveFixedDepositProductTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createFixedDepositProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateFixedDepositProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteFixedDepositProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //recurring deposit
    void getRecurringDepositProducts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveRecurringDepositProductDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveRecurringDepositProductTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createRecurringDepositProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateRecurringDepositProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteRecurringDepositProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //




};
