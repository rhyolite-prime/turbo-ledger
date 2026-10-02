//
// Phase 6 — shareproduct (5 endpoints): dividend declaration/management.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ShareProductDividendsController
    : public drogon::HttpController<ShareProductDividendsController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/shareproduct/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ShareProductDividendsController::getAll,
                     std::string(PREFIX) + "{1}/dividend/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(ShareProductDividendsController::create, std::string(PREFIX) + "{1}/dividend/create",
                     Post, Options, FILTER);
        ADD_METHOD_TO(ShareProductDividendsController::getDetails,
                     std::string(PREFIX) + "{1}/dividend/get-detail/{2}", Get, Options, FILTER);
        ADD_METHOD_TO(ShareProductDividendsController::update,
                     std::string(PREFIX) + "{1}/dividend/{2}/update", Put, Options, FILTER);
        ADD_METHOD_TO(ShareProductDividendsController::remove,
                     std::string(PREFIX) + "{1}/dividend/{2}/delete", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req, std::string productId);
    Task<HttpResponsePtr> create(HttpRequestPtr req, std::string productId);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string productId, std::string dividendId);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string productId, std::string dividendId);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string productId, std::string dividendId);
};
