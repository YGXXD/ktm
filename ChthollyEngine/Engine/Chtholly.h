#ifndef CHTHOLLY_HPP
#define CHTHOLLY_HPP

#if defined(CHTHOLLY_PLATFORM_APPLE)
	#include <TargetConditionals.h>
	
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "XXdEngine don't support ios simulator!"
	#elif TARGET_OS_IPHONE == 1
		#error "XXdEngine don't support ios!"
	#elif TARGET_OS_MAC == 1
		#define CHTHOLLY_RENDER_API_METAL	
	#else
		#error "XXdEngine don't support unkown apple platform!"
	#endif

	#ifdef CHTHOLLY_BUILD_DLL
		#define CHTHOLLY_API __attribute__ ((visibility("default")))
	#else
		#define CHTHOLLY_API __attribute__ ((visibility("default")))
	#endif

#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
	#ifdef _WIN32
		#ifdef _WIN64
			#define CHTHOLLY_RENDER_API_DX12
		#else
			#error "XXdEngine don't support windows x86!"
		#endif
	#endif

	#ifdef CHTHOLLY_BUILD_DLL 
		#define CHTHOLLY_API __declspec(dllexport) 
	#else
		#define CHTHOLLY_API __declspec(dllimport) 
	#endif

#elif defined(CHTHOLLY_PLATFORM_LINUX)
	#error XXdEngine don't support linux!

#elif difined(CHTHOLLY_PLATFORM_ANDROID)
	#error XXdEngine don't support android!

#else
	#error XXdEngine don't support the unknown platform!

#endif

#include <iostream>
#include <memory>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>

#endif
