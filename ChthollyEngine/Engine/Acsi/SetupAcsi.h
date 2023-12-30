#ifndef _SETUP_ACSI_H_
#define _SETUP_ACSI_H_

#include "Basic/SetupBasic.h"

// simd config 
#define CHTHOLLY_SIMD_SSE_FLAG 1
#define CHTHOLLY_SIMD_SSE2_FLAG 2
#define CHTHOLLY_SIMD_SSE3_FLAG 4
#define CHTHOLLY_SIMD_SSE4_1_FLAG 8
#define CHTHOLLY_SIMD_SSE4_2_FLAG 16

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
	#define CHTHOLLY_SIMD_NEON
#elif defined(__SSE4_2__)
	#define CHTHOLLY_SIMD_SSE (CHTHOLLY_SIMD_SSE4_2_FLAG | CHTHOLLY_SIMD_SSE4_1_FLAG | CHTHOLLY_SIMD_SSE3_FLAG | CHTHOLLY_SIMD_SSE2_FLAG | CHTHOLLY_SIMD_SSE_FLAG)
#elif defined(__SSE4_1__)
	#define CHTHOLLY_SIMD_SSE (CHTHOLLY_SIMD_SSE4_1_FLAG | CHTHOLLY_SIMD_SSE3_FLAG | CHTHOLLY_SIMD_SSE2_FLAG | CHTHOLLY_SIMD_SSE_FLAG)
#elif defined(__SSE3__)
	#define CHTHOLLY_SIMD_SSE (CHTHOLLY_SIMD_SSE3_FLAG | CHTHOLLY_SIMD_SSE2_FLAG | CHTHOLLY_SIMD_SSE_FLAG)
#elif defined(__SSE2__) || defined(_M_X64) || defined(_M_AMD64)
	#define CHTHOLLY_SIMD_SSE (CHTHOLLY_SIMD_SSE2_FLAG | CHTHOLLY_SIMD_SSE_FLAG)
#elif defined(__SSE__)
	#define CHTHOLLY_SIMD_SSE (CHTHOLLY_SIMD_SSE_FLAG)
#endif

// simd include
#if defined(CHTHOLLY_SIMD_NEON)
	#include <arm_neon.h>
#elif defined(CHTHOLLY_SIMD_SSE)
	#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_2_FLAG 
		#include <nmmintrin.h>
	#elif CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG 
		#include <smmintrin.h>
	#elif  CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE3_FLAG 
		#include <tmmintrin.h>
		#include <pmmintrin.h>
	#elif  CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG 
		#include <emmintrin.h>
	#else
		#include <xmmintrin.h>
	#endif
#endif

#endif