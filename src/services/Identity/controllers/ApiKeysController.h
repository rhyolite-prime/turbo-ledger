#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ApiKeysController : public drogon::HttpController<ApiKeysController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/api-keys/";
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(ApiKeysController::getAll, std::string(PREFIX) + "get-all", Get, Options, "JwtAuthFilter");
  ADD_METHOD_TO(ApiKeysController::createApiKey, std::string(PREFIX) + "create", Post, Options, "JwtAuthFilter");
  ADD_METHOD_TO(ApiKeysController::revokeApiKey, std::string(PREFIX) + "revoke/{1}", Get, Options, "JwtAuthFilter");
  ADD_METHOD_TO(ApiKeysController::activateApiKey, std::string(PREFIX) + "activate/{1}", Get, Options, "JwtAuthFilter");
  ADD_METHOD_TO(ApiKeysController::deleteApiKey, std::string(PREFIX) + "delete/{1}", Delete, Options, "JwtAuthFilter");
  METHOD_LIST_END

  Task<HttpResponsePtr> getAll(HttpRequestPtr req);
  Task<HttpResponsePtr> createApiKey(HttpRequestPtr req);
  Task<HttpResponsePtr> revokeApiKey(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> activateApiKey(HttpRequestPtr req, std::string id);
  Task<HttpResponsePtr> deleteApiKey(HttpRequestPtr req, std::string id);
};
