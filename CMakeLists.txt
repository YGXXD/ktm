cmake_minimum_required(VERSION 3.20)

project(XXd)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

set(XXD_ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/XXdEngine)
file(GLOB XXD_ENGINE_SOURCE_FILES ${XXD_ENGINE_SOURCE_DIR}/**/*.cpp)

set(EXECUTABLE_NAME XXdSandBox)
set(ENGINE_DLL_NAME XXdEngine)

if(APPLE)
	set(XXD_PLATFORM XXD_PLATFORM_APPLE)
	set(CMAKE_CXX_COMPILER /usr/bin/clang++)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	# add_compile_options(-fobjc-arc)
	# add_compile_options(-x objective-c++)

    # target engine
    add_library(${ENGINE_DLL_NAME} SHARED ${XXD_ENGINE_SOURCE_FILES})	
    set_target_properties(${ENGINE_DLL_NAME} PROPERTIES
        FRAMEWORK TRUE
    	FRAMEWORK_VERSION C
    	MACOSX_FRAMEWORK_IDENTIFIER YGXXD.${ENGINE_DLL_NAME} 
    	XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER YGXXD.${ENGINE_DLL_NAME}
    )
    target_link_libraries(${ENGINE_DLL_NAME} PUBLIC "-framework Metal" "-framework Foundation" "-framework QuartzCore")
    target_include_directories(${ENGINE_DLL_NAME} PUBLIC ${XXD_ENGINE_SOURCE_DIR})

elseif(WIN32)
	set(XXD_PLATFORM XXD_PLATFORM_WINDOWS)
    add_library(${ENGINE_DLL_NAME} SHARED ${XXD_ENGINE_SOURCE_FILES})	

endif()

target_compile_definitions(${ENGINE_DLL_NAME} PRIVATE ${XXD_PLATFORM})
target_compile_definitions(${ENGINE_DLL_NAME} PRIVATE XXD_BUILD_DLL)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/XXdSandBox/. XXD_SAND_BOX_SOURCE_FILES)
add_executable(${EXECUTABLE_NAME} ${XXD_SAND_BOX_SOURCE_FILES}) 
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE ${XXD_PLATFORM})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${ENGINE_DLL_NAME}) 

