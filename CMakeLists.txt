cmake_minimum_required(VERSION 3.26)

project(main)

find_package(Crow CONFIG REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC Crow::Crow)