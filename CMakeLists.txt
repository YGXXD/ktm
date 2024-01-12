cmake_minimum_required(VERSION 3.20)

project(ktm)
set(CMAKE_BUILD_TYPE Debug)

set(EXECUTABLE_NAME test)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	add_compile_options(/std:c++17)
	add_compile_options(/source-charset:utf-8)
	add_compile_options(/execution-charset:utf-8)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	add_compile_options(-std=gnu++17)
	add_compile_options(-fvisibility=hidden)
	add_compile_options(-march=native)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
	add_compile_options(-std=gnu++17)
	add_compile_options(-Wc++17-extensions)
	add_compile_options(-fvisibility=hidden)
	add_compile_options(-march=native)
endif()

add_executable(${EXECUTABLE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp) 