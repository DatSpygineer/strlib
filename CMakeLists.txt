cmake_minimum_required(VERSION 3.25)

project(strlib)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(fmt)
add_subdirectory(test)

add_library(strlib STATIC ./strlib/io.cpp ./strlib/string.cpp)
target_link_libraries(strlib PUBLIC fmt::fmt)
target_include_directories(strlib PUBLIC ${CMAKE_CURRENT_LIST_DIR})