cmake_minimum_required(VERSION 3.25)

project(test_conversion)

add_executable(test_conversion test_conversion.cpp main.cpp)
target_link_libraries(test_conversion PRIVATE strlib)