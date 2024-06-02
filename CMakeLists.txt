cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ktm)

if(KTM_BUILD_WASM AND NOT "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
	add_compile_options(-msimd128)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	add_compile_options(/source-charset:utf-8)
	add_compile_options(/execution-charset:utf-8)
	add_compile_options(/arch:AVX)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
		"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
		"${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
	add_compile_options(-march=native)
endif()

if(KTM_BUILD_TESTING)
	add_subdirectory(test)
endif()

add_executable(ktm ${CMAKE_CURRENT_SOURCE_DIR}/src/ktm.cpp) 

install(DIRECTORY ktm DESTINATION include)

if(NOT TARGET uninstall)
	configure_file(
		"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
		"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
		IMMEDIATE @ONLY)

	add_custom_target(uninstall
		COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
