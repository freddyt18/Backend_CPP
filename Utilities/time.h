#ifndef Time_H
#define Time_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>


class Time {
    public:
        Time(){};

        /* This is a member function of the `Time` class that takes an integer argument `minutes` and returns a string representation of the time that is `minutes` minutes from the current time. */
        void from_now(int minutes, std::string* formatted_time, std::string* raw_time){
            // Get the current time point in system clock.
            auto now = std::chrono::system_clock::now();
            now += std::chrono::minutes(minutes);

            // Convert the `std::chrono::duration` object to a `std::time_t` value.
            std::time_t time = std::chrono::system_clock::to_time_t(now);

            // Debugging
            // std::cout << "local: " << std::put_time(std::localtime(&time), "%c %Z") << '\n';

            // Converting the `std::time_t` value to a string using std::strftime
            char buffer[80];
            std::strftime(buffer, sizeof(buffer), "%c %Z", std::localtime(&time));

            (*formatted_time) = std::string(buffer);
            (*raw_time) = std::to_string(time);
        }

};


#endif