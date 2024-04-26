cmake_minimum_required(VERSION 3.25)

project(test_string_reader)

add_executable(test_string_reader test_string_reader.cpp main.cpp)
target_link_libraries(test_string_reader PRIVATE strlib)