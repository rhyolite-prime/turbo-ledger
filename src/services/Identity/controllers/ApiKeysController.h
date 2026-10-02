//
// Phase 9 cleanup — tenant-scoped API key management.
// All routes except validate-api-keys require the gateway-signed TL-Context
// (turbo::TrustedContextFilter); validate-api-keys is the machine-to-machine
// credential check itself, so it takes TL-Tenant-Id directly instead.
//
#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ApiKeysController : public drogon::HttpController<ApiKeysController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/api-keys/";
  static constexpr const char *FILTER = "turbo::TrustedContextFilter";

  METHOD_LIST_BEGIN
  ADD_METHOD_TO(ApiKeysController::getAll, std::string(PREFIX) + "get-all", Get, Options, FILTER);
  ADD_METHOD_TO(ApiKeysController::createApiKey, std::string(PREFIX) + "create", Post, Options, FILTER);
  ADD_METHOD_TO(ApiKeysController::validateApiKeys, std::string(PREFIX) + "validate-api-keys", Post, Options);
  ADD_METHOD_TO(ApiKeysController::revokeApiKey, std::string(PREFIX) + "revoke/{1}", Get, Options, FILTER);
  ADD_METHOD_TO(ApiKeysController::activateApiKey, std::string(PREFIX) + "activate/{1}", Get, Options, FILTER);
  ADD_METHOD_TO(ApiKeysController::deleteApiKey, std::string(PREFIX) + "delete/{1}", Delete, Options, FILTER);
  METHOD_LIST_END

  Task<HttpResponsePtr> getAll(HttpRequestPtr req);
  Task<HttpResponsePtr> createApiKey(HttpRequestPtr req);
  Task<HttpResponsePtr> validateApiKeys(HttpRequestPtr req);
  Task<HttpResponsePtr> revokeApiKey(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> activateApiKey(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> deleteApiKey(HttpRequestPtr req, std::string id);
};
