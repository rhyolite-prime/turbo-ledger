//
// Phase 5 — interestratecharts (12 endpoints: 6 chart CRUD + 6 nested
// chartslabs CRUD).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class InterestRateChartsController : public drogon::HttpController<InterestRateChartsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/interestratecharts/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(InterestRateChartsController::getAll, std::string(PREFIX) + "get-all", Get, Options,
                     FILTER);
        ADD_METHOD_TO(InterestRateChartsController::create, std::string(PREFIX) + "create", Post, Options,
                     FILTER);
        ADD_METHOD_TO(InterestRateChartsController::getDetails, std::string(PREFIX) + "get-detail/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(InterestRateChartsController::update, std::string(PREFIX) + "{1}/update", Put, Options,
                     FILTER);
        ADD_METHOD_TO(InterestRateChartsController::remove, std::string(PREFIX) + "{1}/delete", Delete,
                     Options, FILTER);
        ADD_METHOD_TO(InterestRateChartsController::templateEndpoint, std::string(PREFIX) + "template", Get,
                     Options, FILTER);

        ADD_METHOD_TO(InterestRateChartsController::slabsGetAll,
                     std::string(PREFIX) + "{1}/chartslabs/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(InterestRateChartsController::slabsCreate, std::string(PREFIX) + "{1}/chartslabs/create",
                     Post, Options, FILTER);
        ADD_METHOD_TO(InterestRateChartsController::slabsGetDetail,
                     std::string(PREFIX) + "{1}/chartslabs/{2}/get-detail", Get, Options, FILTER);
        ADD_METHOD_TO(InterestRateChartsController::slabsUpdate,
                     std::string(PREFIX) + "{1}/chartslabs/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(InterestRateChartsController::slabsDelete,
                     std::string(PREFIX) + "{1}/chartslabs/{2}/delete", Delete, Options, FILTER);
        ADD_METHOD_TO(InterestRateChartsController::slabsTemplate,
                     std::string(PREFIX) + "{1}/chartslabs/template", Get, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);

    Task<HttpResponsePtr> slabsGetAll(HttpRequestPtr req, std::string chartId);
    Task<HttpResponsePtr> slabsCreate(HttpRequestPtr req, std::string chartId);
    Task<HttpResponsePtr> slabsGetDetail(HttpRequestPtr req, std::string chartId, std::string slabId);
    Task<HttpResponsePtr> slabsUpdate(HttpRequestPtr req, std::string chartId, std::string slabId);
    Task<HttpResponsePtr> slabsDelete(HttpRequestPtr req, std::string chartId, std::string slabId);
    Task<HttpResponsePtr> slabsTemplate(HttpRequestPtr req, std::string chartId);
};
