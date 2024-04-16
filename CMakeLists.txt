cmake_minimum_required(VERSION 3.20)

project(ktm)
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

add_executable(geometry_test ${CMAKE_CURRENT_SOURCE_DIR}/test/geometry_test.cpp) 
add_executable(matrix_test ${CMAKE_CURRENT_SOURCE_DIR}/test/matrix_test.cpp) 
add_executable(quaternion_test ${CMAKE_CURRENT_SOURCE_DIR}/test/quaternion_test.cpp) 
add_executable(vector_test ${CMAKE_CURRENT_SOURCE_DIR}/test/vector_test.cpp) 

enable_testing()

add_test(geometry_test geometry_test)
add_test(matrix_test matrix_test)
add_test(quaternion_test quaternion_test)
add_test(vector_test vector_test)

install(DIRECTORY ktm DESTINATION include)

if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
