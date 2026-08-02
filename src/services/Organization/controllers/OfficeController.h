#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class OfficeController : public drogon::HttpController<OfficeController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/offices/";
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(OfficeController::getOffices, std::string(PREFIX) + "get-all", Get);
  ADD_METHOD_TO(OfficeController::getOffices, std::string(PREFIX) + "retrieve-via-external-id", Get);
  ADD_METHOD_TO(OfficeController::getOfficeDetails, std::string(PREFIX) + "get-details", Get);
  ADD_METHOD_TO(OfficeController::createOffice, std::string(PREFIX) + "create", Post);
  ADD_METHOD_TO(OfficeController::updateOffice, std::string(PREFIX) + "{1}", Put);
  ADD_METHOD_TO(OfficeController::getOffices, std::string(PREFIX) + "update-via-external-id", Post);

  // templates
  ADD_METHOD_TO(OfficeController::getOffices, std::string(PREFIX) + "upload-template", Post);
  ADD_METHOD_TO(OfficeController::getOffices, std::string(PREFIX) + "download-template", Get);
  ADD_METHOD_TO(OfficeController::retrieveTemplate, std::string(PREFIX) + "retrieve-template", Get);

  METHOD_LIST_END

 // handler methods
 drogon::Task<HttpResponsePtr> getOffices(HttpRequestPtr req);
 drogon::Task<HttpResponsePtr> createOffice(HttpRequestPtr req);
 drogon::Task<HttpResponsePtr> updateOffice(HttpRequestPtr req);
 drogon::Task<HttpResponsePtr> retrieveTemplate(HttpRequestPtr req);
 drogon::Task<HttpResponsePtr> getOfficeDetails(HttpRequestPtr req);
};
