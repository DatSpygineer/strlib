cmake_minimum_required(VERSION 3.25)

project(test_date)

add_executable(test_date main.cpp)
target_link_libraries(test_date PRIVATE strlib)