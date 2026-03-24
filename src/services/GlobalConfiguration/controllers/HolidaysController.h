#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class HolidaysController : public drogon::HttpController<HolidaysController>
{
public:
    static constexpr const char *PREFIX = "/api/v1/holidays/";
    METHOD_LIST_BEGIN
      ADD_METHOD_TO(HolidaysController::getHolidays, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(HolidaysController::activateHoliday, std::string(PREFIX) + "{1}/activate", Get);
    ADD_METHOD_TO(HolidaysController::retrieveHoliday, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(HolidaysController::createHoliday, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(HolidaysController::updateHoliday, std::string(PREFIX) + "{1}", Put);
    ADD_METHOD_TO(HolidaysController::deleteHoliday, std::string(PREFIX) + "{1}", Delete);

    METHOD_LIST_END

    void getHolidays(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void activateHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string holidayId);
    void retrieveHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string holidayId);
    void createHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string holidayId);
    void deleteHoliday(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string holidayId);
};