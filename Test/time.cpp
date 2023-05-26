#include <iostream>
#include <string>
#include <map>

#include "../Utilities/time.h"
#include "../Utilities/database.h"

using namespace std;

int main(){

    Time t;
    string raw, formatted;

    t.from_now(5, &formatted, &raw);

    cout << "Raw: " << raw << endl;
    cout << "Formatted: " << formatted << endl;

    Database::Connector conn;
    map<string, map<string,string>> result;

    conn.query_read("SELECT * FROM backend_user_session;", &result);

    for (auto& x: result) {
        cout << x.first << endl;
        for (auto& y: x.second) {
            cout << "\t" << y.first << " - " << y.second << endl;
        }
    }

    return 0;
}