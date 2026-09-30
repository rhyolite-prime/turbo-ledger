//
// Phase 1 — maker-checker command inbox (Fineract: /makercheckers).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class MakerCheckersController : public drogon::HttpController<MakerCheckersController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/makercheckers/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(MakerCheckersController::getAll,  std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(MakerCheckersController::approve, std::string(PREFIX) + "approve/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(MakerCheckersController::reject,  std::string(PREFIX) + "reject/{1}", Post, Options, FILTER);
        ADD_METHOD_TO(MakerCheckersController::remove,  std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> approve(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> reject(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
};
