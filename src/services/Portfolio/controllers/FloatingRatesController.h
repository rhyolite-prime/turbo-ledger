#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class FloatingRatesController : public drogon::HttpController<FloatingRatesController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/floating-rates/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(FloatingRatesController::getFloatingRate, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(FloatingRatesController::getFloatingRateDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(FloatingRatesController::createFloatingRate, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(FloatingRatesController::updateFloatingRate, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(FloatingRatesController::deleteFloatingRate, std::string(PREFIX) + "{1}", Delete);
    METHOD_LIST_END

    void getFloatingRate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getFloatingRateDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createFloatingRate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateFloatingRate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteFloatingRate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
