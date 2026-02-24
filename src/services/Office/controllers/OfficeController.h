#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class OfficeController : public drogon::HttpController<OfficeController> {
public:
  static constexpr const char *PREFIX = "/api/v1/offices";
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(OfficeController::getOffices, std::string(PREFIX) + "/get-all",
                Get);
  ADD_METHOD_TO(OfficeController::getOffices,
                std::string(PREFIX) + "/retrieve-via-external-id", Get);
  ADD_METHOD_TO(OfficeController::getOfficeDetails,
                std::string(PREFIX) + "/get-details", Get);
  ADD_METHOD_TO(OfficeController::createOffice, std::string(PREFIX) + "/create",
                Post);
  ADD_METHOD_TO(OfficeController::updateOffice, std::string(PREFIX) + "/{1}", Put);
  ADD_METHOD_TO(OfficeController::getOffices,
                std::string(PREFIX) + "/update-via-external-id", Post);

  // templates
  ADD_METHOD_TO(OfficeController::getOffices,
                std::string(PREFIX) + "/upload-template", Post);
  ADD_METHOD_TO(OfficeController::getOffices,
                std::string(PREFIX) + "/download-template", Get);
  ADD_METHOD_TO(OfficeController::retrieveTemplate,
                std::string(PREFIX) + "/retrieve-template",
                Get); // It tells you what values are allowed when creating a
                      // new office. -> allowed Parents is the list of offices
                      // you can attach the new office under. -> The new office
                      // must be created as a child of one of these.

  METHOD_LIST_END

  // handler methods
  void getOffices(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback);
  void createOffice(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
  void updateOffice(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback,
                    std::string officeId);
  void retrieveTemplate(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback);
  void getOfficeDetails(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback);
};
