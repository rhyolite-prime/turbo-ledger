#include <drogon/drogon.h>
class AuthFilter;
class TenantFilter;

int main() {
    //Set HTTP listener address and port
    //drogon::app().addListener("0.0.0.0", 5555);
    //Load config file
    drogon::app().loadConfigFile("../config.json");

    // Option 1: Apply filters to specific paths using regex patterns
    //drogon::app().registerFilter<AuthFilter>("/api/*");  // Apply to all API endpoints
    //drogon::app().registerFilter<TenantFilter>("/api/*"); // Apply to all API endpoints

    // Option 2: Apply filters to specific path and HTTP methods
    // drogon::app().registerFilter<AuthFilter>("/admin/*", {drogon::Get, drogon::Post});
    // drogon::app().registerFilter<TenantFilter>("/api/v1/*", {drogon::Get, drogon::Post, drogon::Delete});

    // Option 3: Apply to all paths
    // drogon::app().registerFilter<AuthFilter>("/*");


    //drogon::app().loadConfigFile("../config.yaml");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
