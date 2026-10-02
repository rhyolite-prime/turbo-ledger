//
// Phase 4 — client (addresses) (4 endpoints).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ClientAddressesController : public drogon::HttpController<ClientAddressesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/client/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(ClientAddressesController::templateEndpoint,
                     std::string(PREFIX) + "addresses/template", Get, Options, FILTER);
        ADD_METHOD_TO(ClientAddressesController::getAll, std::string(PREFIX) + "{1}/addresses", Get,
                     Options, FILTER);
        ADD_METHOD_TO(ClientAddressesController::create, std::string(PREFIX) + "{1}/addresses", Post,
                     Options, FILTER);
        ADD_METHOD_TO(ClientAddressesController::update, std::string(PREFIX) + "{1}/addresses", Put,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> templateEndpoint(HttpRequestPtr req);
    Task<HttpResponsePtr> getAll(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> create(HttpRequestPtr req, std::string clientId);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string clientId);
};
