cmake_minimum_required(VERSION 3.20)

project(Chtholly)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

set(CHTHOLLY_ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ChthollyEngine)
file(GLOB_RECURSE CHTHOLLY_ENGINE_SOURCE_FILES ${CHTHOLLY_ENGINE_SOURCE_DIR}/Engine/*.cpp)

set(EXECUTABLE_NAME ChthollySandBox)
set(ENGINE_DLL_NAME ChthollyEngine)

if(APPLE)
	set(CHTHOLLY_PLATFORM CHTHOLLY_PLATFORM_APPLE)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	set(CMAKE_CXX_COMPILER /usr/bin/clang++)
	
	add_compile_options(-x objective-c++)
	#add_compile_options(-fno-elide-constructors)
	#add_compile_options(-fobjc-arc)
	
    # target engine
	file(GLOB_RECURSE CHTHOLLY_PLATFORM_SOURCE_FILES ${CHTHOLLY_ENGINE_SOURCE_DIR}/Platform/Mac/*.mm)
	file(GLOB_RECURSE CHTHOLLY_RENDER_API_SOURCE_FILES ${CHTHOLLY_ENGINE_SOURCE_DIR}/RenderAPI/Metal/*.mm)
    add_library(${ENGINE_DLL_NAME} SHARED ${CHTHOLLY_ENGINE_SOURCE_FILES} ${CHTHOLLY_PLATFORM_SOURCE_FILES} ${CHTHOLLY_RENDER_API_SOURCE_FILES})	
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
	set(CHTHOLLY_PLATFORM CHTHOLLY_PLATFORM_WINDOWS)
	add_compile_options(/source-charset:utf-8)
	add_compile_options(/execution-charset:utf-8)
	
	# target engine
	file(GLOB_RECURSE CHTHOLLY_PLATFORM_SOURCE_FILES ${CHTHOLLY_ENGINE_SOURCE_DIR}/Platform/Windows/*.cpp)
    add_library(${ENGINE_DLL_NAME} SHARED ${CHTHOLLY_ENGINE_SOURCE_FILES} ${CHTHOLLY_PLATFORM_SOURCE_FILES})

elseif(LINUX)
	set(CHTHOLLY_PLATFORM CHTHOLLY_PLATFORM_LINUX)
	add_library(${ENGINE_DLL_NAME} SHARED ${CHTHOLLY_ENGINE_SOURCE_FILES})

elseif(ANDROID)
	set(CHTHOLLY_PLATFORM CHTHOLLY_PLATFORM_ANDROID)
	add_library(${ENGINE_DLL_NAME} SHARED ${CHTHOLLY_ENGINE_SOURCE_FILES})

endif()

target_include_directories(${ENGINE_DLL_NAME} PRIVATE ${CHTHOLLY_ENGINE_SOURCE_DIR}/Platform)
target_include_directories(${ENGINE_DLL_NAME} PRIVATE ${CHTHOLLY_ENGINE_SOURCE_DIR}/RenderAPI)
target_include_directories(${ENGINE_DLL_NAME} PUBLIC ${CHTHOLLY_ENGINE_SOURCE_DIR}/Engine)
target_compile_definitions(${ENGINE_DLL_NAME} PRIVATE ${CHTHOLLY_PLATFORM})
target_compile_definitions(${ENGINE_DLL_NAME} PRIVATE CHTHOLLY_BUILD_DLL)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ChthollySandBox/. CHTHOLLY_SAND_BOX_SOURCE_FILES)
add_executable(${EXECUTABLE_NAME} ${CHTHOLLY_SAND_BOX_SOURCE_FILES}) 
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE ${CHTHOLLY_PLATFORM})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${ENGINE_DLL_NAME}) 

