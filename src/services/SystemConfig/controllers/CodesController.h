//
// Phase 2 — codes & code values (11 endpoints). All routes require the
// gateway-signed TL-Context (turbo::TrustedContextFilter).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CodesController : public drogon::HttpController<CodesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/codes/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CodesController::getAll,          std::string(PREFIX) + "get-all", Get, Options, FILTER);
        ADD_METHOD_TO(CodesController::create,          std::string(PREFIX) + "create", Post, Options, FILTER);
        ADD_METHOD_TO(CodesController::getByName,       std::string(PREFIX) + "name/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(CodesController::getDetails,      std::string(PREFIX) + "get-details/{1}", Get, Options, FILTER);
        ADD_METHOD_TO(CodesController::update,          std::string(PREFIX) + "update/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(CodesController::remove,          std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
        ADD_METHOD_TO(CodesController::getValues,       std::string(PREFIX) + "{1}/codevalues/get-all", Get, Options, FILTER);
        ADD_METHOD_TO(CodesController::createValue,     std::string(PREFIX) + "{1}/codevalues/create", Post, Options, FILTER);
        ADD_METHOD_TO(CodesController::getValueDetails, std::string(PREFIX) + "{1}/codevalues/get-details/{2}", Get, Options, FILTER);
        ADD_METHOD_TO(CodesController::updateValue,     std::string(PREFIX) + "{1}/codevalues/update/{2}", Put, Options, FILTER);
        ADD_METHOD_TO(CodesController::removeValue,     std::string(PREFIX) + "{1}/codevalues/delete/{2}", Delete, Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> getAll(HttpRequestPtr req);
    Task<HttpResponsePtr> create(HttpRequestPtr req);
    Task<HttpResponsePtr> getByName(HttpRequestPtr req, std::string name);
    Task<HttpResponsePtr> getDetails(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> update(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> remove(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> getValues(HttpRequestPtr req, std::string codeId);
    Task<HttpResponsePtr> createValue(HttpRequestPtr req, std::string codeId);
    Task<HttpResponsePtr> getValueDetails(HttpRequestPtr req, std::string codeId, std::string valueId);
    Task<HttpResponsePtr> updateValue(HttpRequestPtr req, std::string codeId, std::string valueId);
    Task<HttpResponsePtr> removeValue(HttpRequestPtr req, std::string codeId, std::string valueId);
};
