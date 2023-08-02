cmake_minimum_required(VERSION 3.20)

set(-DCMAKE_CXX_COMPILE "clang++")

project(XXd)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(XXD_ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/XXdEngine)
file(GLOB_RECURSE XXD_ENGINE_SOURCE_FILES ${XXD_ENGINE_SOURCE_DIR}/*.cpp ${XXD_ENGINE_SOURCE_DIR}/*.mm)

set(EXECUTABLE_NAME XXdSandBox)
set(ENGINE_DLL_NAME XXdEngine)

if(APPLE)
	set(XXD_PLATFORM XXD_PLATFORM_APPLE)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	set(CMAKE_CXX_COMPILER /usr/bin/clang++)
	
	add_compile_options(-x objective-c++)
	add_compile_options(-fobjc-arc)

    # target engine
    add_library(${ENGINE_DLL_NAME} SHARED ${XXD_ENGINE_SOURCE_FILES})	
    set_target_properties(${ENGINE_DLL_NAME} PROPERTIES
        FRAMEWORK TRUE
    	FRAMEWORK_VERSION C
    	MACOSX_FRAMEWORK_IDENTIFIER YGXXD.${ENGINE_DLL_NAME} 
    	XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER YGXXD.${ENGINE_DLL_NAME}
    )
    target_link_libraries(${ENGINE_DLL_NAME} PUBLIC 
		"-framework Metal" 
		"-framework Foundation" 
		"-framework QuartzCore" 
		"-framework AppKit"
	)

elseif(WIN32)
	set(XXD_PLATFORM XXD_PLATFORM_WINDOWS)
    add_library(${ENGINE_DLL_NAME} SHARED ${XXD_ENGINE_SOURCE_FILES})	

elseif(LINUX)
	set(XXD_PLATFORM XXD_PLATFORM_LINUX)
	add_library(${ENGINE_DLL_NAME} SHARED ${XXD_ENGINE_SOURCE_FILES})

elseif(ANDROID)
	set(XXD_PLATFORM XXD_PLATFORM_ANDROID)
	add_library(${ENGINE_DLL_NAME} SHARED ${XXD_ENGINE_SOURCE_FILES})

endif()

target_include_directories(${ENGINE_DLL_NAME} PRIVATE ${XXD_ENGINE_SOURCE_DIR}/Platform)
target_include_directories(${ENGINE_DLL_NAME} PUBLIC ${XXD_ENGINE_SOURCE_DIR}/Engine)
target_compile_definitions(${ENGINE_DLL_NAME} PRIVATE ${XXD_PLATFORM})
target_compile_definitions(${ENGINE_DLL_NAME} PRIVATE XXD_BUILD_DLL)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/XXdSandBox/. XXD_SAND_BOX_SOURCE_FILES)
add_executable(${EXECUTABLE_NAME} ${XXD_SAND_BOX_SOURCE_FILES}) 
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE ${XXD_PLATFORM})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${ENGINE_DLL_NAME}) 

