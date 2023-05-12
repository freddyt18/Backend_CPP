#include <crow.h>
#include <string>

#include "Utilities/routes.h"


void add_routes(CustomRoutes::Routes&& r, crow::SimpleApp& app);

int main()
{
    crow::SimpleApp app;

    crow::mustache::set_base("templates");

    string type = "user";
    CustomRoutes::Routes r(type);

    add_routes(std::move(r), app);

    app.port(18080).multithreaded().run();
}

void add_routes(CustomRoutes::Routes&& r, crow::SimpleApp& app){
    r.route_home(app);
    r.route_login(app);
    r.route_env(app);
    r.route_encrypt_message(app);
    r.route_decrypt_message(app);
}