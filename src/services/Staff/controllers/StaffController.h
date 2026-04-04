#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class StaffController : public drogon::HttpController<StaffController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/staff/";

  METHOD_LIST_BEGIN
  ADD_METHOD_TO(StaffController::getStaff, std::string(PREFIX) + "get-all", Get);
  ADD_METHOD_TO(StaffController::getStaffDetails, std::string(PREFIX) + "{1}", Get);
  ADD_METHOD_TO(StaffController::createStaff, std::string(PREFIX) + "create", Post);
  ADD_METHOD_TO(StaffController::updateStaff, std::string(PREFIX) + "{1}", Put);
  ADD_METHOD_TO(StaffController::deleteStaff, std::string(PREFIX) + "{1}", Delete);
  METHOD_LIST_END

  void getStaff(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void getStaffDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void createStaff(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void updateStaff(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void deleteStaff(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
