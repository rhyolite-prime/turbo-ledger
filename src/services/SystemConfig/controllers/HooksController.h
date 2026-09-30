#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class HooksController : public drogon::HttpController<HooksController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/hooks/";
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(HooksController::getTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(HooksController::getHooks, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(HooksController::createHook, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(HooksController::updateHook, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(HooksController::deleteHook, std::string(PREFIX) + "{1}", Delete);

    METHOD_LIST_END

    void getTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getHooks(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createHook(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateHook(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteHook(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
