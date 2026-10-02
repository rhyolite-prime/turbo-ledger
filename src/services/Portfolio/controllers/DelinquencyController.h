//
// Phase 6 — delinquency (10 endpoints): buckets (5) + ranges (5).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class DelinquencyController : public drogon::HttpController<DelinquencyController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/delinquency/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        // ---- buckets ------------------------------------------------------
        ADD_METHOD_TO(DelinquencyController::bucketsGetAll, std::string(PREFIX) + "buckets/get-all", Get,
                     Options, FILTER);
        ADD_METHOD_TO(DelinquencyController::bucketsCreate, std::string(PREFIX) + "buckets/create", Post,
                     Options, FILTER);
        ADD_METHOD_TO(DelinquencyController::bucketsGetDetail,
                     std::string(PREFIX) + "buckets/get-detail/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(DelinquencyController::bucketsUpdate, std::string(PREFIX) + "buckets/{1}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(DelinquencyController::bucketsDelete, std::string(PREFIX) + "buckets/{1}/delete",
                     Delete, Options, FILTER);
        // ---- ranges ---------------------------------------------------------
        ADD_METHOD_TO(DelinquencyController::rangesGetAll, std::string(PREFIX) + "ranges/get-all", Get,
                     Options, FILTER);
        ADD_METHOD_TO(DelinquencyController::rangesCreate, std::string(PREFIX) + "ranges/create", Post,
                     Options, FILTER);
        ADD_METHOD_TO(DelinquencyController::rangesGetDetail,
                     std::string(PREFIX) + "ranges/get-detail/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(DelinquencyController::rangesUpdate, std::string(PREFIX) + "ranges/{1}/update", Put,
                     Options, FILTER);
        ADD_METHOD_TO(DelinquencyController::rangesDelete, std::string(PREFIX) + "ranges/{1}/delete", Delete,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> bucketsGetAll(HttpRequestPtr req);
    Task<HttpResponsePtr> bucketsCreate(HttpRequestPtr req);
    Task<HttpResponsePtr> bucketsGetDetail(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> bucketsUpdate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> bucketsDelete(HttpRequestPtr req, std::string id);

    Task<HttpResponsePtr> rangesGetAll(HttpRequestPtr req);
    Task<HttpResponsePtr> rangesCreate(HttpRequestPtr req);
    Task<HttpResponsePtr> rangesGetDetail(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> rangesUpdate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> rangesDelete(HttpRequestPtr req, std::string id);
};
