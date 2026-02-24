#include <drogon/drogon.h>


namespace turbo_ledger_identity::filters {
    class TenantFilter;
}

int main() {
    //Set HTTP listener address and port
    //drogon::app().addListener("0.0.0.0", 5555);
    //Load config file

    //drogon::app().loadConfigFile("config.json");
    drogon::app().loadConfigFile("../config.json");

    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
