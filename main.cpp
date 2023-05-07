#include <crow.h>
#include "Utilities/routes.h"
#include <string>

int main()
{
    crow::SimpleApp app;

    crow::mustache::set_base("templates");

    string type = "user";
    CustomRoutes::Routes r(type);

    r.route_login(app);
    r.route_env(app);

    app.port(18080).multithreaded().run();
}