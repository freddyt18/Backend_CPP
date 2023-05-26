#ifndef Database
#define Database

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include <boost/mysql.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/system/system_error.hpp>

#include "../middlewares/dotenv.h"


namespace Database {
    class Connector {
    private:
        const int port = 3306;
        std::string host;
        std::string username;
        std::string password;
        std::string database;

    public:
        Connector() {
            // Get data from .env file and store them in a map
            Data::Dotenv dotenv("../.env");
            dotenv.read();
        
            // Get the database credentials from the map
            host = dotenv.getData()["HOST"];
            username = dotenv.getData()["USERNAME"];
            password = dotenv.getData()["PASSWORD"];

            // Get the database name from the map
            database = dotenv.getData()["DATABASE"];

            
        }

        void setup(){
            try {
                // backend_users
                query_create_table(R"(
                    CREATE TABLE IF NOT EXISTS `backend_users` (
                        `userID` int NOT NULL AUTO_INCREMENT,
                        `username` VARCHAR(255) NULL UNIQUE,
                        `password` VARCHAR(255) NOT NULL,
                        PRIMARY KEY (`userID`)
                    ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
                )");
    
                // backend_user_session
                query_create_table(R"(
                    CREATE TABLE IF NOT EXISTS `backend_user_session` (
                        `sessionID` int NOT NULL AUTO_INCREMENT,
                        `userID` int NOT NULL UNIQUE,
                        `content` VARCHAR(255) NOT NULL,
                        PRIMARY KEY (`sessionID`)
                    ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
                )");
            } catch (std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        auto query_read(std::string query, std::map<std::string, std::map<std::string,std::string>>* result) {
            try {
                // The execution context, required to run I/O operations.
                boost::asio::io_context ctx;

                // The SSL context, required to establish TLS connections.
                // The default SSL options are good enough for us at this point.
                boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);

                // Represents a connection to the MySQL server.
                boost::mysql::tcp_ssl_connection conn(ctx.get_executor(), ssl_ctx);

                // Resolve the hostname to get a collection of endpoints
                boost::asio::ip::tcp::resolver resolver(ctx.get_executor());
                auto endpoints = resolver.resolve(host, boost::mysql::default_port_string);

                // The username, password and database to use
                boost::mysql::handshake_params params(
                    username,                // username
                    password,                // password
                    "for-school"  // database
                );

                // Connect to the server using the first endpoint returned by the resolver
                conn.connect(*endpoints.begin(), params);

                // Testing
                std::cout << "Debug 7.1" << std::endl;

                // Execute a simple query
                boost::mysql::results r;
                conn.query(query, r);

                // Testing
                std::cout << "Debug 7.2" << std::endl;

                // Store the data in a map
                auto r_ = r.rows();

                // Testing
                std::cout << "Debug 7.3" << std::endl;

                // // Cout
                // for(auto Q : r_){
                //     std::cout << Q[0].get_string() << std::endl;
                // }

                // Testing
                std::cout << "Debug 7.4" << std::endl;

                // Store data
                int start = 0;
                int end = r_.size() - 1;
                for(auto row : r_){
                    std::map<std::string,std::string> data;
                    for(int i = 0; i < r_.num_columns(); i++){
                        if(row[i].is_null()){
                            data[std::to_string(i)] = "NULL";
                            continue;
                        }

                        if(row[i].is_string()){
                            data[std::to_string(i)] = row[i].get_string();
                            continue;
                        }

                        if(row[i].is_int64()){
                            data[std::to_string(i)] = std::to_string(row[i].get_int64());
                            continue;
                        }

                        // data[std::to_string(i)] = row[i];
                    }
                    (*result)[std::to_string(start)] = data;
                    start++;
                }

                // Testing
                std::cout << "Debug 7.5" << std::endl;

                conn.close();
                return 0;

            } catch (boost::system::system_error& err) {
                std::cerr << "Error connecting to server: " << err.what() << std::endl;
                return 0;
            }

            return 0;
        }


        // Create new table
        void query_create_table(std::string query){
            // The execution context, required to run I/O operations.
            boost::asio::io_context ctx;

            // The SSL context, required to establish TLS connections.
            // The default SSL options are good enough for us at this point.
            boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);

            // Represents a connection to the MySQL server.
            boost::mysql::tcp_ssl_connection conn(ctx.get_executor(), ssl_ctx);

            // Resolve the hostname to get a collection of endpoints
            boost::asio::ip::tcp::resolver resolver(ctx.get_executor());
            auto endpoints = resolver.resolve(host, boost::mysql::default_port_string);

            // The username, password and database to use
            boost::mysql::handshake_params params(
                username,                // username
                password,                // password
                "for-school"  // database
            );

            // Connect to the server using the first endpoint returned by the resolver
            conn.connect(*endpoints.begin(), params);

            // Execute and commit
            boost::mysql::results r;
            conn.query(query,r);

            conn.close();
        }

        // Insert new data
        std::string query_insert(std::string query){
            // The execution context, required to run I/O operations.
            boost::asio::io_context ctx;

            // The SSL context, required to establish TLS connections.
            // The default SSL options are good enough for us at this point.
            boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);

            // Represents a connection to the MySQL server.
            boost::mysql::tcp_ssl_connection conn(ctx.get_executor(), ssl_ctx);

            // Resolve the hostname to get a collection of endpoints
            boost::asio::ip::tcp::resolver resolver(ctx.get_executor());
            auto endpoints = resolver.resolve(host, boost::mysql::default_port_string);

            // The username, password and database to use
            boost::mysql::handshake_params params(
                username,                // username
                password,                // password
                "for-school"  // database
            );

            // Connect to the server using the first endpoint returned by the resolver
            conn.connect(*endpoints.begin(), params);

            // Execute and commit
            try {
                boost::mysql::results r;
                conn.query(query,r);
            } catch (boost::system::system_error& err) {
                // Convert err what to string
                std::string err_what = err.what();
                // Check if the error is a duplicate entry
                if (err_what.find("er_dup_entry") != std::string::npos) {
                    return "Duplicate";
                }
                
                conn.close();
                return err_what;
            }

            conn.close();
            return "Success";
        }

        std::string get_database() {
            return database;
        }
    };

};



#endif
