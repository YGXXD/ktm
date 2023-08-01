#ifndef XXD_HPP
#define XXD_HPP

#if defined(XXD_PLATFORM_APPLE)
	#include <TargetConditionals.h>
	
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "XXdEngine don't support ios simulator!"
	#elif TARGET_OS_IPHONE == 1
		#error "XXdEngine don't support ios!"
	#elif TARGET_OS_MAC == 1
		
	#else
		#error "XXdEngine don't support unkown apple platform!"
	#endif

	#ifdef XXD_BUILD_DLL
		#define XXD_API __attribute__ ((visibility("default")))
	#else
		#define XXD_API __attribute__ ((visibility("default")))
	#endif

#elif defined(XXD_PLATFORM_WINDOWS)
	#ifdef _WIN32
		#ifdef _WIN64

		#else
			#error "XXdEngine don't support windows x86!"
		#endif
	#endif

	#ifdef XXD_BUILD_DLL 
		#define XXD_API __declspec(dllexport) 
	#else
		#define XXD_API __declspec(dllimport) 
	#endif

#elif defined(XXD_PLATFORM_LINUX)
	#error XXdEngine don't support linux!

#elif difined(XXD_PLATFORM_ANDROID)
	#error XXdEngine don't support android!

#else
	#error XXdEngine don't support the unknown platform!

#endif


#endif
