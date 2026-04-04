#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TaxController : public drogon::HttpController<TaxController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/taxes/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TaxController::getTaxComponent, std::string(PREFIX) + "component/get-all", Get);
    ADD_METHOD_TO(TaxController::createTaxComponent, std::string(PREFIX) + "component/create", Post);
    ADD_METHOD_TO(TaxController::getTaxComponentDetails, std::string(PREFIX) + "component/{1}", Get);
    ADD_METHOD_TO(TaxController::updateTaxComponent, std::string(PREFIX) + "component/{1}", Put);
    ADD_METHOD_TO(TaxController::deleteTaxComponent, std::string(PREFIX) + "component/{1}", Delete);
    //tax group
    ADD_METHOD_TO(TaxController::getTaxGroup, std::string(PREFIX) + "group/get-all", Get);
    ADD_METHOD_TO(TaxController::createTaxGroup, std::string(PREFIX) + "group/create", Post);
    ADD_METHOD_TO(TaxController::getTaxGroupDetails, std::string(PREFIX) + "group/{1}", Get);
    ADD_METHOD_TO(TaxController::updateTaxGroup, std::string(PREFIX) + "group/{1}", Put);
    ADD_METHOD_TO(TaxController::deleteTaxGroup, std::string(PREFIX) + "group/{1}", Delete);

    METHOD_LIST_END

    void getTaxComponent(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createTaxComponent(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getTaxComponentDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateTaxComponent(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteTaxComponent(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getTaxGroup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createTaxGroup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getTaxGroupDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateTaxGroup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteTaxGroup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
