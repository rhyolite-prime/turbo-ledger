#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SearchController : public drogon::HttpController<SearchController>
{
  public:
    static constexpr const char *PREFIX = "/api/v1/search/";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SearchController::runSearch, std::string(PREFIX) + "", Get);
    ADD_METHOD_TO(SearchController::runAdvancedSearch, std::string(PREFIX) + "advance", Get);
    METHOD_LIST_END

    void runSearch(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void runAdvancedSearch(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
