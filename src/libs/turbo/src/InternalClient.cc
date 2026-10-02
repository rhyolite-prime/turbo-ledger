#include "turbo/InternalClient.h"

#include <json/json.h>
#include <trantor/utils/Logger.h>

#include "turbo/ContextCodec.h"

namespace turbo {

InternalClient::InternalClient(std::string baseUrl, std::string contextSecret)
    : baseUrl_(std::move(baseUrl)), contextSecret_(std::move(contextSecret)) {}

drogon::HttpClientPtr InternalClient::clientPtr() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!client_) client_ = drogon::HttpClient::newHttpClient(baseUrl_);
    return client_;
}

drogon::Task<InternalClient::Result> InternalClient::call(const RequestContext &ctx,
                                                           drogon::HttpMethod method,
                                                           std::string path, Json::Value jsonBody,
                                                           double timeoutSeconds) const {
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(method);
    req->setPath(path);
    req->setPathEncode(false);
    if (method == drogon::Post || method == drogon::Put) {
        Json::StreamWriterBuilder builder;
        builder["indentation"] = "";
        req->setBody(Json::writeString(builder, jsonBody));
        req->setContentTypeString("application/json");
    }
    req->addHeader(RequestContext::kTenantHeaderName, ctx.tenantId);
    req->addHeader(RequestContext::kRequestIdHeaderName, ctx.requestId);
    req->addHeader(RequestContext::kHeaderName, ContextCodec::encode(ctx, contextSecret_));

    Result result;
    try {
        auto resp = co_await clientPtr()->sendRequestCoro(req, timeoutSeconds);
        result.status = resp->getStatusCode();
        if (!resp->getBody().empty()) {
            Json::CharReaderBuilder rb;
            std::string errs;
            std::istringstream is{std::string(resp->getBody())};
            if (!Json::parseFromStream(rb, is, &result.body, &errs)) {
                result.body = Json::Value(Json::objectValue);
            }
        }
    } catch (const std::exception &e) {
        LOG_ERROR << "InternalClient call to " << baseUrl_ << path << " failed: " << e.what();
        result.status = drogon::k502BadGateway;
        result.body = Json::Value(Json::objectValue);
        result.body["message"] = std::string("Internal service unavailable: ") + e.what();
    }
    co_return result;
}

}  // namespace turbo
