cmake_minimum_required(VERSION 3.25)

project(test_printf)

add_executable(test_printf test_printf.cpp main.cpp)
target_link_libraries(test_printf PRIVATE strlib)