#ifndef _SETUP_ACSI_H_
#define _SETUP_ACSI_H_

#include "../setup.h"

// simd config 
#define KTM_SIMD_SSE_FLAG 1
#define KTM_SIMD_SSE2_FLAG 2
#define KTM_SIMD_SSE3_FLAG 4
#define KTM_SIMD_SSE4_1_FLAG 8
#define KTM_SIMD_SSE4_2_FLAG 16

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
	#define KTM_SIMD_NEON
#elif defined(__SSE4_2__)
	#define KTM_SIMD_SSE (KTM_SIMD_SSE4_2_FLAG | KTM_SIMD_SSE4_1_FLAG | KTM_SIMD_SSE3_FLAG | KTM_SIMD_SSE2_FLAG | KTM_SIMD_SSE_FLAG)
#elif defined(__SSE4_1__)
	#define KTM_SIMD_SSE (KTM_SIMD_SSE4_1_FLAG | KTM_SIMD_SSE3_FLAG | KTM_SIMD_SSE2_FLAG | KTM_SIMD_SSE_FLAG)
#elif defined(__SSE3__)
	#define KTM_SIMD_SSE (KTM_SIMD_SSE3_FLAG | KTM_SIMD_SSE2_FLAG | KTM_SIMD_SSE_FLAG)
#elif defined(__SSE2__) || defined(_M_X64) || defined(_M_AMD64)
	#define KTM_SIMD_SSE (KTM_SIMD_SSE2_FLAG | KTM_SIMD_SSE_FLAG)
#elif defined(__SSE__)
	#define KTM_SIMD_SSE (KTM_SIMD_SSE_FLAG)
#endif

// simd include
#if defined(KTM_SIMD_NEON)
	#include <arm_neon.h>
#elif defined(KTM_SIMD_SSE)
	#if KTM_SIMD_SSE & KTM_SIMD_SSE4_2_FLAG 
		#include <nmmintrin.h>
	#elif KTM_SIMD_SSE & KTM_SIMD_SSE4_1_FLAG 
		#include <smmintrin.h>
	#elif  KTM_SIMD_SSE & KTM_SIMD_SSE3_FLAG 
		#include <tmmintrin.h>
		#include <pmmintrin.h>
	#elif  KTM_SIMD_SSE & KTM_SIMD_SSE2_FLAG 
		#include <emmintrin.h>
	#else
		#include <xmmintrin.h>
	#endif
#endif

#endif