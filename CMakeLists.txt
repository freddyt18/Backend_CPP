cmake_minimum_required(VERSION 3.26)

project(main)

find_package(Crow CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
find_package(mailio CONFIG REQUIRED)


# # Set the target architecture to x64
# set(CMAKE_GENERATOR_PLATFORM x64)

# add_executable(main ./Test/database.cpp) 
add_executable(main main.cpp) 

target_link_libraries(main PUBLIC OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(main PUBLIC Crow::Crow)
target_link_libraries(main PUBLIC Boost::headers Threads::Threads OpenSSL::Crypto OpenSSL::SSL)
target_link_libraries(main PRIVATE mailio)
