#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class InterestRateChartsController : public drogon::HttpController<InterestRateChartsController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/interest-rate-charts/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(InterestRateChartsController::getChartTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(InterestRateChartsController::getCharts, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(InterestRateChartsController::getChartDetail, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(InterestRateChartsController::createChart, std::string(PREFIX) + "create", Post); //create or define charge.
    ADD_METHOD_TO(InterestRateChartsController::updateChart, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(InterestRateChartsController::deleteChart, std::string(PREFIX) + "{1}", Delete);
    //slabs
    ADD_METHOD_TO(InterestRateChartsController::createSlab, std::string(PREFIX) + "{1}/chart-slabs", Post);
    ADD_METHOD_TO(InterestRateChartsController::getSlabs, std::string(PREFIX) + "{1}/chart-slabs", Get);
    ADD_METHOD_TO(InterestRateChartsController::getSlabDetails, std::string(PREFIX) + "{1}/chart-slabs/{2}", Get);
    ADD_METHOD_TO(InterestRateChartsController::updateSlab, std::string(PREFIX) + "{1}/chart-slabs/{2}", Put);
    ADD_METHOD_TO(InterestRateChartsController::deleteSlab, std::string(PREFIX) + "{1}/chart-slabs/{2}", Delete);
    METHOD_LIST_END

    void getChartTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getCharts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getChartDetail(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createChart(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateChart(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteChart(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    //slabs
    void createSlab(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSlabs(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getSlabDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateSlab(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteSlab(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
