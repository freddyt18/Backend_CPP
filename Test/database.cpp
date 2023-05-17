#include "../Utilities/database.h"
#include <string>
#include <iostream>
#include <map>
#include "../middlewares/dotenv.h"
#include <crow.h>

using namespace std;

// Database Usage
int main(){
    
    Database::Connector conn;
    
    // row - column : value
    map<string, map<string,string>> data;

    conn.query_read("SELECT * FROM backend_users;", &data);

    std::cout << "Testing" << std::endl;
    
    // Cout
    for (auto const& x : data)
    {
        std::cout << "Row number " << x.first << std::endl;

        for (auto const& y : x.second)
        {
            std::cout << y.first  // column
                << ':' 
                << y.second // value
                << std::endl;
        }
    }


    return 0;
}