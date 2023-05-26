#ifndef LOGIN_H
#define LOGIN_H


#include <string>
#include <crow.h>
#include "../middlewares/Hashing.h"
#include "Error.h"
#include "../Utilities/html.h"
#include "../Utilities/database.h"
#include <map>

#include "../Utilities/time.h"

using namespace std;


class Login : public Error {
    public:
        Login(){};
        
        bool validate_and_process(crow::json::rvalue&& json, crow::json::wvalue* x){
            // Validate inputs to accept username and password only
            if (!json.has("username") || !json.has("password")) {
                
                (*x)["status"] = "error";
                (*x)["message"] = "Invalid request body";

                return false;
            }


            // Convert the characters to HTML entities to prevent XSS attacks.
            HTMLEntities e;

            string username = e.encode(json["username"].s());
            string password = e.encode(json["password"].s());
            

            // Compare password with the one in the database
            Database::Connector conn;

            map<string, map<string,string>> result;
            
            conn.query_read("SELECT password FROM backend_users WHERE username LIKE '" + username + "';", &result);


            // If the username is not found in the database, we'll send a message via the pointer
            if (result.size() == 0) {
                (*x)["status"] = "error";
                (*x)["message"] = "Username not found";

                return false;
            }


            // Store the result in a variable
            string password_from_db = result["0"]["0"];

            // // // Debuggin
            // std::cout << "Password from db: " << password_from_db << std::endl;
            // std::cout << "Testing" << std::endl;            
            // (*x)["testing"] = "testing";
            // return true;

            // Convert the input password to hash
            TripleDes& t = TripleDes::getInstance();
            string password_hash = t.encrypt(password);


            // Compare the password from the database with the input password
            if (password_from_db != password_hash) {
                (*x)["status"] = "error";
                (*x)["message"] = "Incorrect password";

                return false;
            }


            // Register the userID in the session by randomizing the content of the session cookie
            string content = t.encrypt(username + password_hash);


            // Retrieve the userID from the database
            conn.query_read("SELECT userID FROM backend_users WHERE username LIKE '" + username + "';", &result);

            string userID = result["0"]["0"];


            // Retrieve the date and time
            string raw, formatted;
            Time t_;
            t_.from_now(30, &formatted, &raw);


            // Store the userID in the session
            conn.query_insert("INSERT INTO backend_user_session (content, userID, expiration, expiration_raw) VALUES ('" + content + "', '" + userID + "', '" + formatted + "', " + raw + ");");


            // Return the session cookie
            (*x)["status"] = "success";
            (*x)["message"] = "Login successful";
            (*x)["session"] = content;

            return true;

        }

        crow::json::wvalue route_login(crow::SimpleApp& app){
            try {
                CROW_ROUTE(app, "/login")
                .methods("POST"_method)
                ([&](const crow::request& req) {
                    crow::json::wvalue x;

                    // Validate request body to accept tyep json only
                    if (req.get_header_value("Content-Type") != "application/json") {
                        
                        x["status"] = "error";
                        x["message"] = "Invalid request body type";

                        return x;
                    }


                    // Validate the input
                    auto json = crow::json::load(req.body);
                    validate_and_process(move(json), &x);
                    return x;

                });
            } catch (const std::exception& e) {
                // Store the error message in a json object
                crow::json::wvalue x;
                
                x["status"] = "error";
                x["message"] = e.what();

                return x;
            }

            return internal_error();
        }

};

#endif