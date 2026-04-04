#include "JsonBodyFilter.h"
#include "dto/BaseApiResponse.h"
#include <drogon/HttpResponse.h>

namespace customer::filters
{
void JsonBodyFilter::doFilter(const drogon::HttpRequestPtr &req,
                              drogon::FilterCallback &&fcb,
                              drogon::FilterChainCallback &&fccb)
{
    auto jsonBody = req->getJsonObject();
    if (!jsonBody)
    {
        customer::dto::BaseApiResponse response;
        response.success = false;
        response.error["message"] = "Invalid JSON body";
        auto resp = drogon::HttpResponse::newHttpJsonResponse(response.toJson());
        resp->setStatusCode(drogon::k400BadRequest);
        fcb(resp);
        return;
    }
    fccb();
}
} // namespace customer::filters
