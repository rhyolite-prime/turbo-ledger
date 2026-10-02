//
// Phase 4 — clients (v2) (1 endpoint): text search.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ClientsV2Controller : public drogon::HttpController<ClientsV2Controller> {
  public:
    static constexpr const char *PREFIX = "/api/v2/clients/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ClientsV2Controller::search, std::string(PREFIX) + "search", Post, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> search(HttpRequestPtr req);
};
