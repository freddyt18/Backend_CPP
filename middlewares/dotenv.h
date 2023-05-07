#ifndef dotenv_h
#define dotenv_h

#include <string>
#include <fstream>
#include <sstream>
#include <map>


using namespace std;

namespace Data {
    class Dotenv
    {
        public:
            Dotenv(string path){
                this->path = path;
            };


            // Getters 
            string getPath(){
                return this->path;
            };

            map<string, string> getData(){
                return this->data;
            };


            // Setters
            void setPath(string path){
                this->path = path;
            };

            void setData(map<string, string> data){
                this->data = data;
            };
            

            // Read data from .env file line by line then convert them into key-value pairs
            void read(){
                ifstream file(this->path);
                string line;
                while (getline(file, line))
                {
                    if (line.empty() || line[0] == '#') continue;
                    istringstream iss(line);
                    string key, value;
                    if (getline(iss, key, '=') && getline(iss, value))
                    {
                        this->data[key] = value;
                    }
                }
            };


        private:
            string path;
            map<string, string> data;
    };
    
};


#endif