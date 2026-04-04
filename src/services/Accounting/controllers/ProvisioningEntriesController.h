#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ProvisioningEntriesController : public drogon::HttpController<ProvisioningEntriesController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/provisioning-entries";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(ProvisioningEntriesController::getProvisioningEntries, std::string(PREFIX) + "get-all", Get);
    ADD_METHOD_TO(ProvisioningEntriesController::getProvisioningEntryDetail, std::string(PREFIX) + "{1}", Get);
    ADD_METHOD_TO(ProvisioningEntriesController::createProvisioningEntry, std::string(PREFIX) + "create", Post);
    ADD_METHOD_TO(ProvisioningEntriesController::recreateProvisioningEntry, std::string(PREFIX) + "{1}/recreate-provisioning-entry", Post);
    ADD_METHOD_TO(ProvisioningEntriesController::createJournalEntries, std::string(PREFIX) + "{1}/create-journal-entry", Post);
    METHOD_LIST_END

    void getProvisioningEntries(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getProvisioningEntryDetail(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createProvisioningEntry(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void recreateProvisioningEntry(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void createJournalEntries(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
