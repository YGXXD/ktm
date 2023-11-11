#ifndef _SETUP_BASE_H_
#define _SETUP_BASE_H_

// os platform config, only support 64-bit os
#if defined(__APPLE__)
	#if defined(__LP64__)
		#define CHTHOLLY_PLATFORM_APPLE
		#include <TargetConditionals.h>
		#if TARGET_IPHONE_SIMULATOR == 1
			#error "Chtholly Engine don't support ios simulator!"
		#elif TARGET_OS_IPHONE == 1
			#error "Chtholly Engine don't support ios!"
		#elif TARGET_OS_MAC == 1
			#define CHTHOLLY_RENDER_API_METAL
			#define CHTHOLLY_RENDER_API_VULKAN
		#else
			#error "Chtholly Engine don't support unkown apple platform!"
		#endif
	#else 
		#error "Chtholly Engine don't support apple 32-bit platform!"	
	#endif
#elif defined(_WIN32)
	#if defined(_WIN64)
		#define CHTHOLLY_PLATFORM_WINDOWS
		#define CHTHOLLY_RENDER_API_DX12
		#define CHTHOLLY_RENDER_API_VULKAN
	#else
		#error "Chtholly Engine don't support windows 32-bit platform!"
	#endif
#elif defined(__linux__)
	#define CHTHOLLY_PLATFORM_LINUX
	#error "Chtholly Engine don't support linux!"
#elif defined(__ANDROID__)
	#define CHTHOLLY_PLATFORM_ANDROID
	#error "Chtholly Engine don't support android!"
#else
	#error "Chtholly Engine don't support the unknown platform!"
#endif

// debug state
#ifndef NDEBUG
	#define CHTHOLLY_DEBUG_ENABLE
#endif

// c++ compiler config
#if defined(__clang__) && defined(__GNUC__)
	#define CHTHOLLY_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__MINGW32__)
	#define CHTHOLLY_COMPILER_GCC
#elif defined(_MSC_VER)
	#define CHTHOLLY_COMPILER_MSVC
#else
	#error "Chtholly Engine don't support unkown c++ compiler, it's only support clang++, g++ and visual c++"
#endif

// function Function config
#if defined(CHTHOLLY_COMPILER_CLANG) || defined(CHTHOLLY_COMPILER_GCC)
	#define CHTHOLLY_INLINE __inline__ __attribute__((always_inline))
	#define CHTHOLLY_NOINLINE __attribute__((noinline))
	#define CHTHOLLY_NOTHROW __attribute__((nothrow))
	#define CHTHOLLY_NODEBUG __attribute__((nodebug))
#elif defined(CHTHOLLY_COMPILER_MSVC)
	#define CHTHOLLY_INLINE __forceinline
	#define CHTHOLLY_NOINLINE __declspec(noinline)
	#define CHTHOLLY_NOTHROW __declspec(nothrow)
	#define CHTHOLLY_NODEBUG 
#endif

#define CHTHOLLY_FUNC CHTHOLLY_INLINE CHTHOLLY_NODEBUG CHTHOLLY_NOTHROW

// build engine config
#if defined(CHTHOLLY_COMPILER_CLANG)
	#define CHTHOLLY_ENGINE_API __attribute__ ((visibility("default")))
#elif defined(CHTHOLLY_COMPILER_GCC)
	#if defined(CHTHOLLY_PLATFORM_WINDOWS)
		#ifdef CHTHOLLY_BUILD_DLL 
			#define CHTHOLLY_ENGINE_API __attribute__((dllexport))
		#else
			#define CHTHOLLY_ENGINE_API __attribute__((dllimport))
		#endif	
	#else
		#define CHTHOLLY_ENGINE_API __attribute__ ((visibility("default")))	
	#endif
#elif defined(CHTHOLLY_COMPILER_MSVC)
	#ifdef CHTHOLLY_BUILD_DLL 
		#define CHTHOLLY_ENGINE_API __declspec(dllexport) 
	#else
		#define CHTHOLLY_ENGINE_API __declspec(dllimport) 
	#endif
#endif

#endif
