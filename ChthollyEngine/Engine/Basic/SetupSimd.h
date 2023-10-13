#ifndef _SETUP_SIMD_H_
#define _SETUP_SIMD_H_

#include "SetupBase.h"

// simd include
#if defined(CHTHOLLY_SIMD_NEON)
	#include <arm_neon.h>
	#if defined(CHTHOLLY_COMPILER_CLANG)
		#define _neon_shuffle_f32(a, b, s2, s1) __builtin_shufflevector(a, b, s1, (s2) + 2)
		#define _neon_shuffle_s32(a, b, s2, s1) _neon_shuffle_f32(a, b, s2, s1)
		#define _neon_shuffleq_f32(a, b, s4, s3, s2, s1) __builtin_shufflevector(a, b, s1, s2, (s3) + 4, (s4) + 4)
		#define _neon_shuffleq_s32(a, b, s4, s3, s2, s1) _neon_shuffleq_f32(a, b, s4, s3, s2, s1)
	#elif defined(CHTHOLLY_COMPILER_MSVC) || defined(CHTHOLLY_COMPILER_GCC) 
		#define _neon_shuffle_f32(a, b, s2, s1) vset_lane_f32(vget_lane_f32(b, s2), vmov_n_f32(vget_lane_f32(a, s1)), 1)
		#define _neon_shuffle_s32(a, b, s2, s1) vset_lane_s32(vget_lane_s32(b, s2), vmov_n_s32(vget_lane_s32(a, s1)), 1)
		#define _neon_shuffleq_f32(a, b, s4, s3, s2, s1) vsetq_lane_f32(vgetq_lane_f32(b, s4), vsetq_lane_f32(vgetq_lane_f32(b, s3), vsetq_lane_f32(vgetq_lane_f32(a, s2), vmovq_n_f32(vgetq_lane_f32(a, s1)), 1), 2), 3)
		#define _neon_shuffleq_s32(a, b, s4, s3, s2, s1) vsetq_lane_s32(vgetq_lane_s32(b, s4), vsetq_lane_s32(vgetq_lane_s32(b, s3), vsetq_lane_s32(vgetq_lane_s32(a, s2), vmovq_n_s32(vgetq_lane_s32(a, s1)), 1), 2), 3)
	#endif
#elif defined(CHTHOLLY_SIMD_SSE)
	#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_2_FLAG 
		#include <nmmintrin.h>
	#elif CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG 
		#include <smmintrin.h>
	#elif  CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE3_FLAG 
		#include <pmmintrin.h>
	#elif  CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG 
		#include <emmintrin.h>
	#else
		#include <xmmintrin.h>
	#endif
#endif

#endif