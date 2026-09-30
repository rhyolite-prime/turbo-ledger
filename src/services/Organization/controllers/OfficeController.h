#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class OfficeController : public drogon::HttpController<OfficeController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/offices/";
    METHOD_LIST_BEGIN
      ADD_METHOD_TO(OfficeController::getOffices, std::string(PREFIX) + "get-all", Get);
      ADD_METHOD_TO(OfficeController::getOfficeDetails, std::string(PREFIX) + "{1}", Get);
      ADD_METHOD_TO(OfficeController::createOffice, std::string(PREFIX) + "create", Post);
      ADD_METHOD_TO(OfficeController::updateOffice, std::string(PREFIX) + "{1}", Put);
      ADD_METHOD_TO(OfficeController::deleteOffice, std::string(PREFIX) + "{1}", Delete);
  METHOD_LIST_END

 // handler methods
 Task<HttpResponsePtr> getOffices(HttpRequestPtr req);
 Task<HttpResponsePtr> createOffice(HttpRequestPtr req);
 Task<HttpResponsePtr> updateOffice(HttpRequestPtr req, std::string id);
 Task<HttpResponsePtr> deleteOffice(HttpRequestPtr req, std::string id);
 Task<HttpResponsePtr> getOfficeDetails(HttpRequestPtr req, std::string id);
};
