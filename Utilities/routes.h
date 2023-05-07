#ifndef CustomRoutes
#define CustomRoutes

#include <string>
#include "crow.h"
#include "../middlewares/User.h"
#include "../middlewares/dotenv.h"

using namespace std;

namespace CustomRoutes {
    class Routes {
        public:
            // Constructor
            Routes(string type){
                this->type = type;
            };

            string getType(){
                return this->type;
            };

            
            // Login API with POST that accepts unique headers
            auto route_login(crow::SimpleApp& app){


                CROW_ROUTE(app, "/login")
                .methods("POST"_method)
                ([&](const crow::request& req){
                    Data::Dotenv dotenv("../.env");
                    dotenv.read();
                    map<string, string> data = dotenv.getData();

                    crow::json::wvalue x;

                    string username = req.get_header_value("username");
                    string password = req.get_header_value("password");


                    if (username == data["USER"] && password == data["PASSWORD"]){
                        // Create a new user
                        U::User user("1", username, password);

                        // Create a new session
                        user.setSession(S::Session("1"));

                        // Creating a json object
                        
                        x["status"] = "success";
                        x["message"] = "Login Successful";
                        x["user"] = user.getUsername();
                        x["session"] = user.getSession().getId();
                        
                    } else {
                        
                        x["status"] = "error";
                        x["message"] = "Login Failed";

                    }

                    return x;
                });
                
            };


            // Retrieve data from .env
            auto route_env(crow::SimpleApp& app){
                CROW_ROUTE(app, "/env")
                .methods("GET"_method)
                ([&](const crow::request& req){

                    // Create a new json object
                    crow::json::wvalue x;

                    // Create a new dotenv object
                    Data::Dotenv dotenv("../.env");

                    // Read data from .env file
                    dotenv.read();

                    // Get data from .env file
                    map<string, string> data = dotenv.getData();

                    // Serialize the map into json using for each
                    for (auto& kv : data) {
                        x[kv.first] = kv.second;
                    }

                    return x;
                });
            };


        private:
            string type;
    };
};



#endif