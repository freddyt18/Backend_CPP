#ifndef CustomRoutes
#define CustomRoutes

#include <string>
#include "crow.h"

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

            auto route_index(crow::SimpleApp& app){
                string type = this->getType();

                CROW_ROUTE(app, "/").methods("GET"_method)([type](){
                    auto page = crow::mustache::load("index.html");
                    
                    return page.render();
                });
            };

            auto route_add(crow::SimpleApp& app){
                string type = this->getType();

                CROW_ROUTE(app, "/add/<int>/<int>").methods("GET"_method)([type](const crow::request& req, int a, int b){
                    crow::json::wvalue x;
                    x["a"] = a;
                    x["b"] = b;
                    x["sum"] = a + b;
                    x["type"] = type;
                    
                    return x;
                });
            };

        private:
            string type;
    };
};



#endif