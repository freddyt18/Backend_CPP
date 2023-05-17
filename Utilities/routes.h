#ifndef CustomRoutes
#define CustomRoutes

#include <string>
#include "crow.h"
#include <unordered_map>


#include "../middlewares/User.h"
#include "../middlewares/dotenv.h"
#include "../middlewares/Hashing.h"
#include "../Routes/Register.h"
#include "../Routes/Login.h"

using namespace std;

namespace CustomRoutes {
    class Routes {
        public:
            // Constructor
            Routes(){};

            // Bind all routes
            void route_bind(crow::SimpleApp& app){
                // Register
                Register registerRoute;
                registerRoute.route_register(app);

                Login loginRoute;
                loginRoute.route_login(app);

                route_home(app);
                route_encrypt_message(app);
                route_decrypt_message(app);
            };

            crow::json::wvalue internal_error(){
                crow::json::wvalue x;

                x["status"] = "error";
                x["message"] = "Internal server error";

                return x;
            }

            crow::json::wvalue route_home(crow::SimpleApp& app){
                try {
                    CROW_ROUTE(app, "/")
                    ([&](const crow::request& req){
                        crow::json::wvalue x;

                        x["status"] = "success";
                        x["message"] = "Welcome to the home page";

                        return x;
                    });
                } catch (const std::exception& e) {
                    // Return error in json
                    return crow::json::wvalue{e.what()};
                }

                // Return internal server error
                return internal_error();
            };


            // Encrypt route
            crow::json::wvalue route_encrypt_message(crow::SimpleApp& app){
                try {
                    CROW_ROUTE(app, "/encrypt/<string>")
                    .methods("GET"_method)
                    ([&](const crow::request& req, string message){
                        // Get a reference to the singleton instance of the TripleDes class
                        TripleDes& des = TripleDes::getInstance();
        
                        // Create a new json object
                        crow::json::wvalue x;
        
                        // Encrypt the message
                        string encrypted = des.encrypt(message);
        
                        // Serialize the map into json using for each
                        x["message"] = message;
                        x["encrypted"] = encrypted;
        
                        return x;
                    });
                } catch (const std::exception& e) {
                    // Return error in json
                    return crow::json::wvalue{e.what()};
                };

                // Return internal server error
                return internal_error();
            };

            
            // Decrypt route
            crow::json::wvalue route_decrypt_message(crow::SimpleApp& app){
                try {
                    CROW_ROUTE(app, "/decrypt/<string>")
                    .methods("GET"_method)
                    ([&](const crow::request& req, string message){
                        // Get a reference to the singleton instance of the TripleDes class
                        TripleDes& des = TripleDes::getInstance();
        
                        // Create a new json object
                        crow::json::wvalue x;
        
                        // Decrypt the message
                        string decrypted = des.decrypt(message);
        
                        // Serialize the map into json using for each
                        x["encrypted"] = message;
                        x["decrypted"] = decrypted;
        
                        return x;
                    });
                } catch (const std::exception& e) {
                    // Return error in json
                    return crow::json::wvalue{e.what()};
                };

                // Return internal server error
                return internal_error();
            };
    };

};



#endif