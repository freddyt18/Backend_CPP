#include <crow.h>
#include <string>

#include "Utilities/routes.h"
#include "Utilities/database.h"


int main()
{
    crow::SimpleApp app;

    // crow::mustache::set_base("templates");

    // Set up database
    Database::Connector conn;
    conn.setup();
    
    CustomRoutes::Routes r;
    r.route_bind(app);

    app.port(18080).multithreaded().run();
}