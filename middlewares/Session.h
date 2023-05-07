#ifndef Session_h
#define Session_h

#include <string>

using namespace std;

namespace S {
    class Session
    {
        public:
            Session(string id="x") : id(id) {};

            // Getters and Setters
            void setId(string id){
                this->id = id;
            };

            string getId(){
                return this->id;
            };
        
        private:
            string id;
    };
    
};


#endif