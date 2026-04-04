#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TemplatesController : public drogon::HttpController<TemplatesController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/templates/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TemplatesController::retrieveUgdTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(TemplatesController::getUgd, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(TemplatesController::getUgdDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(TemplatesController::createUgd, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(TemplatesController::updateUgd, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(TemplatesController::deleteUgd, std::string(PREFIX) + "{1}", Delete);
    METHOD_LIST_END

    void retrieveUgdTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getUgd(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getUgdDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createUgd(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateUgd(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void deleteUgd(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
