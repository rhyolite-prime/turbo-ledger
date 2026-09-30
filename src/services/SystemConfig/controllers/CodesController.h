#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CodesController : public drogon::HttpController<CodesController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/codes/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CodesController::getCodes, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(CodesController::createCode, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(CodesController::updateCode, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(CodesController::deleteCode, std::string(PREFIX) + "{1}", Delete);
    ADD_METHOD_TO(CodesController::retrieveCodeValues, std::string(PREFIX) + "{1}/code-values/{2}", Get);
    ADD_METHOD_TO(CodesController::getCodeValues, std::string(PREFIX) + "{1}/code-values", Get);
    ADD_METHOD_TO(CodesController::updateCodeValue, std::string(PREFIX) + "{1}/code-values/{2}", Put);
    ADD_METHOD_TO(CodesController::deleteCodeValue, std::string(PREFIX) + "{1}/code-values/{2}", Delete);
    METHOD_LIST_END

    void getCodes(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createCode(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateCode(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteCode(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void retrieveCodeValues(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getCodeValues(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateCodeValue(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteCodeValue(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
