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
#if defined(__clang__) && defined(__GNUC__)
	#define CHTHOLLY_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__MINGW32__)
	#define CHTHOLLY_COMPILER_GCC
#elif defined(_MSC_VER)
	#define CHTHOLLY_COMPILER_MSVC
#endif

#if defined(CHTHOLLY_COMPILER_CLANG) || defined(CHTHOLLY_COMPILER_GCC)
	#define CHTHOLLY_INLINE __inline__ __attribute__((always_inline))
	#define CHTHOLLY_NOINLINE __attribute__((noinline))
	#ifdef CHTHOLLY_BUILD_DLL 
		#define CHTHOLLY_API __attribute__ ((visibility("default")))
	#else
		#define CHTHOLLY_API __attribute__ ((visibility("default")))
	#endif
#elif defined(CHTHOLLY_COMPILER_MSVC)
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
#define CHTHOLLY_SIMD_SSE_FLAG 1
#define CHTHOLLY_SIMD_SSE2_FLAG 2
#define CHTHOLLY_SIMD_SSE3_FLAG 4
#define CHTHOLLY_SIMD_SSE4_1_FLAG 8
#define CHTHOLLY_SIMD_SSE4_2_FLAG 16s

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
	#define CHTHOLLY_SIMD_NEON
	#include <arm_neon.h>
	#if defined(CHTHOLLY_COMPILER_CLANG)
		#define _neon_shuffle_f32(a, b, s2, s1) __builtin_shufflevector(a, b, s1, s2 + 2)
		#define _neon_shuffle_s32(a, b, s2, s1) _neon_shuffle_f32(a, b, s2, s1)
		#define _neon_shuffleq_f32(a, b, s4, s3, s2, s1) __builtin_shufflevector(a, b, s1, s2, s3 + 4, s4 + 4)
		#define _neon_shuffleq_s32(a, b, s4, s3, s2, s1) _neon_shuffleq_f32(a, b, s4, s3, s2, s1)

	#elif defined(CHTHOLLY_COMPILER_GCC)
		#define _neon_shuffle_f32(a, b, s2, s1) __extension__({ \
			float32x2_t ret; \
			ret = vmov_n_f32(vget_lane_f32(a, s1)); \
			ret = vset_lane_f32(vget_lane_f32(b, s2), ret, 1); \
			ret; \
		})
		#define _neon_shuffle_s32(a, b, s2, s1) __extension__({ \
			int32x2_t ret; \
			ret = vmov_n_s32(vget_lane_s32(a, s1)); \
			ret = vset_lane_s32(vget_lane_s32(b, s2), ret, 1); \
			ret; \
		})
		#define _neon_shuffleq_f32(a, b, s4, s3, s2, s1) __extension__({ \
			float32x4_t ret; \
			ret = vmovq_n_f32(vgetq_lane_f32(a, s1)); \
			ret = vsetq_lane_f32(vgetq_lane_f32(a, s2), ret, 1); \
			ret = vsetq_lane_f32(vgetq_lane_f32(b, s3), ret, 2); \
			ret = vsetq_lane_f32(vgetq_lane_f32(b, s4), ret, 3); \
			ret; \
		})
		#define _neon_shuffleq_s32(a, b, s4, s3, s2, s1) __extension__({ \
			int32x4_t ret; \
			ret = vmovq_n_s32(vgetq_lane_s32(a, s1)); \
			ret = vsetq_lane_s32(vgetq_lane_s32(a, s2), ret, 1); \
			ret = vsetq_lane_s32(vgetq_lane_s32(b, s3), ret, 2); \
			ret = vsetq_lane_s32(vgetq_lane_s32(b, s4), ret, 3); \
			ret; \
		})
	#elif defined(CHTHOLLY_COMPILER_MSVC)
		#define _neon_shuffle_f32(a, b, s2, s1) vset_lane_f32(vget_lane_f32(b, s2), vmov_n_f32(vget_lane_f32(a, s1)), 1)
		#define _neon_shuffle_s32(a, b, s2, s1) vset_lane_s32(vget_lane_s32(b, s2), vmov_n_s32(vget_lane_s32(a, s1)), 1)
		#define _neon_shuffleq_f32(a, b, s4, s3, s2, s1) vsetq_lane_f32(vgetq_lane_f32(b, s4), vsetq_lane_f32(vgetq_lane_f32(b, s3), vsetq_lane_f32(vgetq_lane_f32(a, s2), vmovq_n_f32(vgetq_lane_f32(a, s1)), 1), 2), 3)
		#define _neon_shuffleq_s32(a, b, s4, s3, s2, s1) vsetq_lane_s32(vgetq_lane_s32(b, s4), vsetq_lane_s32(vgetq_lane_s32(b, s3), vsetq_lane_s32(vgetq_lane_s32(a, s2), vmovq_n_s32(vgetq_lane_s32(a, s1)), 1), 2), 3)
	#endif

#elif defined(__SSE4_2__)
	#define CHTHOLLY_SIMD_SSE (CHTHOLLY_SIMD_SSE4_2_FLAG | CHTHOLLY_SIMD_SSE4_1_FLAG | CHTHOLLY_SIMD_SSE3_FLAG | CHTHOLLY_SIMD_SSE2_FLAG | CHTHOLLY_SIMD_SSE_FLAG)
	#include <nmmintrin.h>
#elif defined(__SSE4_1__)
	#define CHTHOLLY_SIMD_SSE (CHTHOLLY_SIMD_SSE4_1_FLAG | CHTHOLLY_SIMD_SSE3_FLAG | CHTHOLLY_SIMD_SSE2_FLAG | CHTHOLLY_SIMD_SSE_FLAG)
	#include <smmintrin.h>
#elif defined(__SSE3__)
	#define CHTHOLLY_SIMD_SSE (CHTHOLLY_SIMD_SSE3_FLAG | CHTHOLLY_SIMD_SSE2_FLAG | CHTHOLLY_SIMD_SSE_FLAG)
	#include <pmmintrin.h>
#elif defined(__SSE2__) || defined(_M_X64)
	#define CHTHOLLY_SIMD_SSE (CHTHOLLY_SIMD_SSE2_FLAG | CHTHOLLY_SIMD_SSE_FLAG)
	#include <emmintrin.h>
#elif defined(__SSE__)
	#define CHTHOLLY_SIMD_SSE (CHTHOLLY_SIMD_SSE_FLAG)
	#include <xmmintrin.h>
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
