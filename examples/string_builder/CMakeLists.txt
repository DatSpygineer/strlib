cmake_minimum_required(VERSION 3.25)

project(test_string_builder)

add_executable(test_string_builder test_string_builder.cpp main.cpp)
target_link_libraries(test_string_builder PRIVATE strlib)