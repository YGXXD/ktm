#ifndef CHTHOLLY_HPP
#define CHTHOLLY_HPP

// os platform
#if defined(CHTHOLLY_PLATFORM_APPLE)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "Chtholly Engine don't support ios simulator!"
	#elif TARGET_OS_IPHONE == 1
		#error "Chtholly Engine don't support ios!"
	#elif TARGET_OS_MAC == 1
		#define CHTHOLLY_RENDER_API_METAL
	#else
		#error "Chtholly Engine don't support unkown apple platform!"
	#endif
#elif defined(CHTHOLLY_PLATFORM_WINDOWS)
	#ifdef _WIN32
		#ifdef _WIN64
			#define CHTHOLLY_RENDER_API_DX12
		#else
			#error "Chtholly Engine don't support windows x86!"
		#endif
	#else
		#error "Chtholly Engine don't support unkown windows platform!"	
	#endif
#elif defined(CHTHOLLY_PLATFORM_LINUX)
	#error "Chtholly Engine don't support linux!"
#elif defined(CHTHOLLY_PLATFORM_ANDROID)
	#error "Chtholly Engine don't support android!"
#else
	#error "Chtholly Engine don't support the unknown platform!"
#endif

// c++ compiler
#if defined(__clang__) || defined(__GNUC__)
	#define CHTHOLLY_INLINE __inline__ __attribute__((always_inline))
	#define CHTHOLLY_NOINLINE __attribute__((noinline))
	#ifdef CHTHOLLY_BUILD_DLL 
		#define CHTHOLLY_API __attribute__ ((visibility("default")))
	#else
		#define CHTHOLLY_API __attribute__ ((visibility("default")))
	#endif
#elif defined(_MSC_VER)
	#define CHTHOLLY_INLINE __forceinline
	#define CHTHOLLY_NOINLINE __declspec(noinline)
	#ifdef CHTHOLLY_BUILD_DLL 
		#define CHTHOLLY_API __declspec(dllexport) 
	#else
		#define CHTHOLLY_API __declspec(dllimport) 
	#endif
#else
	#error "Chtholly Engine don't support unkown c++ compiler, it's only support clang++, g++ and visual c++"
#endif

// simd support
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
	#define CHTHOLLY_SIMD_NEON
#elif defined(__SSE2__) || defined(_M_X64)
	#define CHTHOLLY_SIMD_SSE2
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <memory>

#include <cstdint>
#include <cassert>
#include <cstring>
#include <cmath>

#include "Kutori.h"

#endif
