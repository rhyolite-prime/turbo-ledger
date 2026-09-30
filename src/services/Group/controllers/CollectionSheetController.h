#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CollectionSheetController : public drogon::HttpController<CollectionSheetController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/collection-sheet/";

    METHOD_LIST_BEGIN

    ADD_METHOD_TO(CollectionSheetController::generateCollectionSheet, std::string(PREFIX) + "{1}/generate-collection-sheet", Post);
    ADD_METHOD_TO(CollectionSheetController::saveCollectionSheet, std::string(PREFIX) + "{1}/save-collection-sheet", Post);

    METHOD_LIST_END

    Task<HttpResponsePtr> generateCollectionSheet(HttpRequestPtr req, const std::string &id);

    Task<HttpResponsePtr> saveCollectionSheet(HttpRequestPtr req, const std::string &id);
};
