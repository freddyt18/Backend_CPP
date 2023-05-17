#ifndef Register_H
#define Register_H

#include <string>
#include <map>
#include "crow.h"
#include "../Utilities/html.h"
#include "../Utilities/database.h"
#include "../middlewares/Hashing.h"
#include "Error.h"


using namespace std;


class Register : public Error {
public:
    // Constructor
    Register(){};

    bool validate_input(crow::json::rvalue&& json, map<string,string>* x) {
        // Validate request body to accept username and password only
        if (!json.has("username") || !json.has("password")) {
            return false;
        }

        // Check if the username and password meet the minimum length requirements.
        if (json["username"].size() < 4 || json["password"].size() < 8) {
            return false;
        }

        // Convert the characters to HTML entities to prevent XSS attacks.
        CustomRoutes::HTMLEntities e;

        string username = e.encode(json["username"].s());
        string password = e.encode(json["password"].s());


        // Store the data in the pointer x
        (*x)["username"] = username;
        (*x)["password"] = password;

        return true;
    }

    crow::json::wvalue route_register(crow::SimpleApp& app) {
        try {
            CROW_ROUTE(app, "/register")
            .methods("POST"_method)
            ([&](const crow::request& req) {
                crow::json::wvalue x;

                // Validate request body to accept tyep json only
                if (req.get_header_value("Content-Type") != "application/json") {
                    
                    x["status"] = "error";
                    x["message"] = "Invalid request body type";

                    return x;
                }

                // Get the request body
                auto json = crow::json::load(req.body);
                map<string,string> data;

                // Validate request body to accept username and password only
                // The data will be stored in the pointer data
                if (!json || !validate_input(std::move(json), &data)) {
                    x["status"] = "error";
                    x["message"] = "Invalid request body";

                    return x;
                }

                // Retrive the data from the data map
                string username = data["username"];
                string password = data["password"];

                // Hash the password
                TripleDes& des = TripleDes::getInstance();
                password = des.encrypt(password);

                // Cout the data
                cout << "Username: " << username << endl;
                cout << "Password: " << password << endl;

                // Store the data in the database
                Database::Connector conn;

                string query = "INSERT INTO backend_users (username, password) VALUES ('"+username+"','"+password+"');";

                string status = conn.query_insert(query);

                // Check if the query was successful
                if (status == "Duplicate"){
                    x["status"] = "error";
                    x["message"] = "Username already exists";
                    return x;

                } else if (status != "Success") {
                    x["status"] = "error";
                    x["message"] = status;
                    return x;
                }

                // Return code 200
                x["status"] = "success";
                x["message"] = "User registered successfully";
                
                return x;
            });
        } catch (const std::exception& e) {
            // Return error in json
            return crow::json::wvalue{e.what()};
        }

        // Return internal server error
        return internal_error();
    };

};




#endif