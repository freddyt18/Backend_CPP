#ifndef User_h
#define User_h

#include <string>
#include "Session.h"

using namespace std;

namespace U {
    class User
    {
        public:
            User(string id, string username, string password) : id(id), username(username), password(password) {};

            // Getters
            string getId(){
                return this->id;
            };

            string getUsername(){
                return this->username;
            };

            S::Session getSession(){
                return this->session;
            };

            // Setters
            void setId(string id){
                this->id = id;
            };

            void setUsername(string username){
                this->username = username;
            };

            void setPassword(string password){
                this->password = password;
            };

            void setSession(S::Session session){
                this->session = session;
            };
        
        private:
            string id;
            string username;
            string password;
            S::Session session;
    };
    
};


#endif