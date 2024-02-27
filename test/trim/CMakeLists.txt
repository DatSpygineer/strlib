cmake_minimum_required(VERSION 3.25)

project(test_trim)

add_executable(test_trim main.cpp)
target_link_libraries(test_trim PRIVATE strlib)