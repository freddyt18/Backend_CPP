#ifndef INCLUDE_H
#define INCLUDE_H

#include <string>
#include <crow.h>

class Error{
    public:
        Error(){};

        crow::json::wvalue internal_error(){
            crow::json::wvalue x;

            x["status"] = "error";
            x["message"] = "Internal server error";

            return x;
        }
};


#endif