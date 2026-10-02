//
// Turbo Ledger platform library — canonical API response envelope.
// Replaces the per-service copies of BaseApiResponse.h.
//
#pragma once

#include <drogon/HttpResponse.h>
#include <json/json.h>
#include <string>

namespace turbo {

/**
 * Canonical response envelope used by every Turbo Ledger service.
 *
 *   { "result": {...}, "targetUrl": "", "message": "", "success": true, "error": {...} }
 *
 * Shape is kept identical to the legacy per-service BaseApiResponse so existing
 * clients keep working. Fineract-style error details are carried inside `error`:
 *
 *   "error": {
 *      "developerMessage": "...",
 *      "userMessageGlobalisationCode": "error.msg.x.y",
 *      "errors": [ { "parameterName": "...", "defaultUserMessage": "..." } ]
 *   }
 */
class ApiResponse {
  public:
    Json::Value result;
    std::string targetUrl;
    std::string message;
    bool success{false};
    Json::Value error;

    ApiResponse() = default;

    [[nodiscard]] Json::Value toJson() const {
        Json::Value json;
        json["result"] = result;
        json["targetUrl"] = targetUrl;
        json["message"] = message;
        json["success"] = success;
        json["error"] = error;
        return json;
    }

    // ---- factory helpers -------------------------------------------------

    static ApiResponse ok(Json::Value result = Json::Value(Json::objectValue),
                          std::string message = "") {
        ApiResponse r;
        r.success = true;
        r.result = std::move(result);
        r.message = std::move(message);
        return r;
    }

    static ApiResponse fail(const std::string &developerMessage,
                            const std::string &globalisationCode = "error.msg.platform.unknown") {
        ApiResponse r;
        r.success = false;
        r.message = developerMessage;
        r.error["developerMessage"] = developerMessage;
        r.error["userMessageGlobalisationCode"] = globalisationCode;
        r.error["errors"] = Json::Value(Json::arrayValue);
        return r;
    }

    ApiResponse &withFieldError(const std::string &parameterName,
                                const std::string &defaultUserMessage,
                                const std::string &code = "") {
        Json::Value e;
        e["parameterName"] = parameterName;
        e["defaultUserMessage"] = defaultUserMessage;
        if (!code.empty()) e["userMessageGlobalisationCode"] = code;
        error["errors"].append(e);
        return *this;
    }

    // ---- HTTP helpers ----------------------------------------------------

    [[nodiscard]] drogon::HttpResponsePtr toHttpResponse(
        drogon::HttpStatusCode code = drogon::k200OK) const {
        auto resp = drogon::HttpResponse::newHttpJsonResponse(toJson());
        resp->setStatusCode(code);
        return resp;
    }

    static drogon::HttpResponsePtr httpOk(Json::Value result = Json::Value(Json::objectValue),
                                          std::string message = "") {
        return ok(std::move(result), std::move(message)).toHttpResponse(drogon::k200OK);
    }

    static drogon::HttpResponsePtr httpError(drogon::HttpStatusCode code,
                                             const std::string &developerMessage,
                                             const std::string &globalisationCode =
                                                 "error.msg.platform.unknown") {
        return fail(developerMessage, globalisationCode).toHttpResponse(code);
    }

    static drogon::HttpResponsePtr httpNotImplemented(const std::string &operation) {
        return fail("Operation not implemented yet: " + operation,
                    "error.msg.platform.not.implemented")
            .toHttpResponse(drogon::k501NotImplemented);
    }

    static drogon::HttpResponsePtr httpBadRequest(const std::string &developerMessage) {
        return fail(developerMessage, "error.msg.platform.bad.request")
            .toHttpResponse(drogon::k400BadRequest);
    }

    static drogon::HttpResponsePtr httpUnauthorized(const std::string &developerMessage) {
        return fail(developerMessage, "error.msg.platform.unauthorized")
            .toHttpResponse(drogon::k401Unauthorized);
    }
};

}  // namespace turbo
