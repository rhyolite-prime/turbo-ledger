#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SavingsProductController : public drogon::HttpController<SavingsProductController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/savings-products";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SavingsProductController::retrieveTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(SavingsProductController::getSavingsProduct, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(SavingsProductController::createSavingsProduct, std::string(PREFIX) + "create", Post); //create or define charge.
    ADD_METHOD_TO(SavingsProductController::updateSavingsProduct, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(SavingsProductController::deleteSavingsProduct, std::string(PREFIX) + "{1}", Delete);
    METHOD_LIST_END

    void retrieveTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSavingsProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createSavingsProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateSavingsProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteSavingsProduct(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
