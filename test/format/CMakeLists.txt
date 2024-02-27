cmake_minimum_required(VERSION 3.25)

project(test_format)

add_executable(test_format main.cpp)
target_link_libraries(test_format PRIVATE strlib)