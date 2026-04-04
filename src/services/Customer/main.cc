#include <drogon/drogon.h>

#include "dto/BaseApiResponse.h"

int main() {

    // Apply JsonBodyFilter logic centrally for all POST requests
    drogon::app().registerPreHandlingAdvice(
        [](const drogon::HttpRequestPtr &req,
           drogon::AdviceCallback &&acb,
           drogon::AdviceChainCallback &&accb) {
            if (req->method() == drogon::Post) {
                auto jsonBody = req->getJsonObject();
                if (!jsonBody) {
                    customer::dto::BaseApiResponse response;
                    response.success = false;
                    response.error["message"] = "Invalid JSON body";
                    auto resp = drogon::HttpResponse::newHttpJsonResponse(response.toJson());
                    resp->setStatusCode(drogon::k400BadRequest);
                    acb(resp);
                    return;
                }
            }
            accb();
        });

    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", 5555);
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //drogon::app().loadConfigFile("../config.yaml");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
