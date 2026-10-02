//
// Phase 9 — self/beneficiaries/tpt*, self/device*, self/pockets (local CRUD,
// no composition target — see SelfServiceService.h).
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class BeneficiariesController : public drogon::HttpController<BeneficiariesController> {
  public:
    static constexpr const char *PREFIX = "/api/v1/self/";
    static constexpr const char *FILTER = "turbo::TrustedContextFilter";

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(BeneficiariesController::tptTemplate,
                     std::string(PREFIX) + "beneficiaries/tpt/template", Get, Options, FILTER);
        ADD_METHOD_TO(BeneficiariesController::tptList, std::string(PREFIX) + "beneficiaries/tpt", Get,
                     Options, FILTER);
        ADD_METHOD_TO(BeneficiariesController::tptCreate, std::string(PREFIX) + "beneficiaries/tpt",
                     Post, Options, FILTER);
        ADD_METHOD_TO(BeneficiariesController::tptUpdate,
                     std::string(PREFIX) + "beneficiaries/tpt/{1}", Put, Options, FILTER);
        ADD_METHOD_TO(BeneficiariesController::tptDelete,
                     std::string(PREFIX) + "beneficiaries/tpt/{1}", Delete, Options, FILTER);

        ADD_METHOD_TO(BeneficiariesController::deviceList, std::string(PREFIX) + "device", Get, Options,
                     FILTER);
        ADD_METHOD_TO(BeneficiariesController::deviceCreate, std::string(PREFIX) + "device", Post,
                     Options, FILTER);
        ADD_METHOD_TO(BeneficiariesController::deviceGet, std::string(PREFIX) + "device/{1}", Get,
                     Options, FILTER);
        ADD_METHOD_TO(BeneficiariesController::deviceUpdate, std::string(PREFIX) + "device/{1}", Put,
                     Options, FILTER);
        ADD_METHOD_TO(BeneficiariesController::deviceDelete, std::string(PREFIX) + "device/{1}", Delete,
                     Options, FILTER);

        ADD_METHOD_TO(BeneficiariesController::pocketsList, std::string(PREFIX) + "pockets", Get,
                     Options, FILTER);
        ADD_METHOD_TO(BeneficiariesController::pocketsCreate, std::string(PREFIX) + "pockets", Post,
                     Options, FILTER);
    METHOD_LIST_END

    Task<HttpResponsePtr> tptTemplate(HttpRequestPtr req);
    Task<HttpResponsePtr> tptList(HttpRequestPtr req);
    Task<HttpResponsePtr> tptCreate(HttpRequestPtr req);
    Task<HttpResponsePtr> tptUpdate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> tptDelete(HttpRequestPtr req, std::string id);

    Task<HttpResponsePtr> deviceList(HttpRequestPtr req);
    Task<HttpResponsePtr> deviceCreate(HttpRequestPtr req);
    Task<HttpResponsePtr> deviceGet(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> deviceUpdate(HttpRequestPtr req, std::string id);
    Task<HttpResponsePtr> deviceDelete(HttpRequestPtr req, std::string id);

    Task<HttpResponsePtr> pocketsList(HttpRequestPtr req);
    Task<HttpResponsePtr> pocketsCreate(HttpRequestPtr req);
};
