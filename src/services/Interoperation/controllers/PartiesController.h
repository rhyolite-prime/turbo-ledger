//
// Phase 9 — interoperation/parties/* (6 endpoints, local CRUD on
// interop_identifiers — see InteroperationService.h for the scope note).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class PartiesController : public drogon::HttpController<PartiesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/interoperation/parties/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(PartiesController::registerParty, std::string(PREFIX) + "{1}/{2}", Put, Options,
                     FILTER);
        ADD_METHOD_TO(PartiesController::registerPartySub, std::string(PREFIX) + "{1}/{2}/{3}", Put,
                     Options, FILTER);
        ADD_METHOD_TO(PartiesController::getParty, std::string(PREFIX) + "{1}/{2}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(PartiesController::getPartySub, std::string(PREFIX) + "{1}/{2}/{3}", Get, Options,
                     FILTER);
        ADD_METHOD_TO(PartiesController::removeParty, std::string(PREFIX) + "{1}/{2}", Delete, Options,
                     FILTER);
        ADD_METHOD_TO(PartiesController::removePartySub, std::string(PREFIX) + "{1}/{2}/{3}", Delete,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> registerParty(HttpRequestPtr req, std::string idType, std::string idValue);
    Task<HttpResponsePtr> registerPartySub(HttpRequestPtr req, std::string idType, std::string idValue,
                                           std::string subIdOrType);
    Task<HttpResponsePtr> getParty(HttpRequestPtr req, std::string idType, std::string idValue);
    Task<HttpResponsePtr> getPartySub(HttpRequestPtr req, std::string idType, std::string idValue,
                                      std::string subIdOrType);
    Task<HttpResponsePtr> removeParty(HttpRequestPtr req, std::string idType, std::string idValue);
    Task<HttpResponsePtr> removePartySub(HttpRequestPtr req, std::string idType, std::string idValue,
                                         std::string subIdOrType);
};
