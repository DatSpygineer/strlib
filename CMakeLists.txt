cmake_minimum_required(VERSION 3.25)

project(strlib)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(fmt)
add_subdirectory(examples)

set(STRLIB_SOURCES ./strlib/string.cpp)

if (NOT DEFINED STRLIB_FILESYS)
	set(STRLIB_FILESYS ON)
endif()

if (STRLIB_FILESYS)
	set(STRLIB_SOURCES ${STRLIB_SOURCES} ./strlib/io.cpp)
endif()

if (WIN32)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

if (STRLIB_COMPILE_SHARED)
	add_library(strlib SHARED ${STRLIB_SOURCES})
	target_compile_definitions(strlib PRIVATE STRLIB_EXPORT)
elseif(STRLIB_HEADER_ONLY)
	add_library(strlib INTERFACE ${STRLIB_SOURCES})
	target_compile_definitions(strlib INTERFACE STRLIB_HEADER_ONLY)
else()
	add_library(strlib STATIC ${STRLIB_SOURCES})
	target_compile_definitions(strlib PUBLIC STRLIB_STATIC)
endif()

if (STRLIB_FMT_HEADER_ONLY OR STRLIB_HEADER_ONLY)
	if (STRLIB_HEADER_ONLY)
		target_link_libraries(strlib INTERFACE fmt::fmt-header-only)
	else()
		target_link_libraries(strlib PUBLIC fmt::fmt-header-only)
	endif()
else()
	target_link_libraries(strlib PUBLIC fmt::fmt)
endif()

if (STRLIB_HEADER_ONLY)
	target_include_directories(strlib INTERFACE ${CMAKE_CURRENT_LIST_DIR})

	if (STRLIB_FILESYS)
		target_compile_definitions(strlib INTERFACE STRLIB_FILESYS=1)
	else()
		target_compile_definitions(strlib INTERFACE STRLIB_FILESYS=0)
	endif()
else()
	target_include_directories(strlib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

	if (STRLIB_FILESYS)
		target_compile_definitions(strlib PUBLIC STRLIB_FILESYS=1)
	else()
		target_compile_definitions(strlib PUBLIC STRLIB_FILESYS=0)
	endif()
endif()