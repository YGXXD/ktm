#ifndef _KTM_INTRIN_H_
#define _KTM_INTRIN_H_

#include "../setup.h"

#define KTM_SIMD_SSE_FLAG 1
#define KTM_SIMD_SSE2_FLAG 2
#define KTM_SIMD_SSE3_FLAG 4
#define KTM_SIMD_SSE4_1_FLAG 8
#define KTM_SIMD_SSE4_2_FLAG 16

#if defined(KTM_COMPILER_MSVC)
	#if (defined(_M_AMD64) || defined(_M_X64)) || _M_IX86_FP == 2
		#ifndef __SSE2__
			#define __SSE2__
		#endif
	#elif _M_IX86_FP == 1
			#ifndef __SSE__
				#define __SSE__
			#endif
	#endif
#endif

#if defined(__SSE4_2__)
	#define KTM_SIMD_X86 (KTM_SIMD_SSE4_2_FLAG | KTM_SIMD_SSE4_1_FLAG | KTM_SIMD_SSE3_FLAG | KTM_SIMD_SSE2_FLAG | KTM_SIMD_SSE_FLAG)
	#include <nmmintrin.h>
#elif defined(__SSE4_1__)
	#define KTM_SIMD_X86 (KTM_SIMD_SSE4_1_FLAG | KTM_SIMD_SSE3_FLAG | KTM_SIMD_SSE2_FLAG | KTM_SIMD_SSE_FLAG)
	#include <smmintrin.h>	
#elif defined(__SSE3__)
	#define KTM_SIMD_X86 (KTM_SIMD_SSE3_FLAG | KTM_SIMD_SSE2_FLAG | KTM_SIMD_SSE_FLAG)
	#include <tmmintrin.h>
	#include <pmmintrin.h>
#elif defined(__SSE2__) || defined(_M_X64) || defined(_M_AMD64)
	#define KTM_SIMD_X86 (KTM_SIMD_SSE2_FLAG | KTM_SIMD_SSE_FLAG)
	#include <emmintrin.h>
#elif defined(__SSE__)
	#define KTM_SIMD_X86 (KTM_SIMD_SSE_FLAG)
	#include <xmmintrin.h>
#endif

#define KTM_SIMD_ARM_FLAG 1
#define KTM_SIMD_A64_FLAG 2

#if defined(KTM_COMPILER_MSVC)
	#if defined(_M_ARM64) || defined(_M_HYBRID_X86_ARM64) || defined(_M_ARM64EC)
		#define KTM_SIMD_ARM (KTM_SIMD_ARM_FLAG | KTM_SIMD_A64_FLAG)
		#include <arm64_neon.h>
	#elif defined(_M_ARM)
		#define KTM_SIMD_ARM KTM_SIMD_ARM_FLAG
		#include <arm_neon.h>
	#endif
#else 
	#if defined(__ARM_NEON) || defined(__ARM_NEON__)
		#if defined(__aarch64__)
			#define KTM_SIMD_ARM (KTM_SIMD_ARM_FLAG | KTM_SIMD_A64_FLAG)
		#else
			#define KTM_SIMD_ARM KTM_SIMD_ARM_FLAG
		#endif
		#include <arm_neon.h>
	#endif
#endif

#include "arm.h"
#include "x86.h"

#endif