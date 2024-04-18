cmake_minimum_required(VERSION 3.25)

project(strlib)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(fmt)
add_subdirectory(test)

set(STRLIB_SOURCES ./strlib/string.cpp)

if (NOT DEFINED STRLIB_FILESYS)
	set(STRLIB_FILESYS ON)
endif()

if (STRLIB_FILESYS)
	set(STRLIB_SOURCES ${STRLIB_SOURCES} ./strlib/io.cpp)
endif()

add_library(strlib STATIC ${STRLIB_SOURCES})
target_link_libraries(strlib PUBLIC fmt::fmt)
target_include_directories(strlib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
if (STRLIB_FILESYS)
	target_compile_definitions(strlib PUBLIC STRLIB_FILESYS=1)
else()
	target_compile_definitions(strlib PUBLIC STRLIB_FILESYS=0)
endif()