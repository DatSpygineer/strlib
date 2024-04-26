cmake_minimum_required(VERSION 3.25)

project(test_date.cpp)

add_executable(test_date test_date.cpp main.cpp)
target_link_libraries(test_date PRIVATE strlib)