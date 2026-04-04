#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class JournalEntriesController : public drogon::HttpController<JournalEntriesController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/journal-entries/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(JournalEntriesController::retrieveTemplate, std::string(PREFIX) + "template", Get);
    ADD_METHOD_TO(JournalEntriesController::getJournalEntries, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(JournalEntriesController::getJournalEntryDetails, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(JournalEntriesController::createJournalEntry, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(JournalEntriesController::updateRunningBalances, std::string(PREFIX) + "{1}/update-running-balance", Post);
    ADD_METHOD_TO(JournalEntriesController::reverseJournalEntry, std::string(PREFIX) + "{1}/reverse", Get);
    METHOD_LIST_END

    void retrieveTemplate(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getJournalEntries(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getJournalEntryDetails(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createJournalEntry(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void updateRunningBalances(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void reverseJournalEntry(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
