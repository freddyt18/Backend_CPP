cmake_minimum_required(VERSION 3.26)

project(main)

find_package(Crow CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(main PUBLIC Crow::Crow)