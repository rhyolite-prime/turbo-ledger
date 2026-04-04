#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CollectionSheetController : public drogon::HttpController<CollectionSheetController>
{
  public:
  static constexpr const char *PREFIX = "/api/v1/collection-sheet/";
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(CollectionSheetController::generateIndividualCollectionSheet, std::string(PREFIX) + "generate", Post);
  ADD_METHOD_TO(CollectionSheetController::saveCollectionSheet, std::string(PREFIX) + "create", Post);
  METHOD_LIST_END

  void generateIndividualCollectionSheet(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
  void saveCollectionSheet(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
