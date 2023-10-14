#ifndef _SETUP_SIMD_H_
#define _SETUP_SIMD_H_

#include "SetupBase.h"

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
#elif defined(__SSE2__) || defined(_M_X64)
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
		#include <pmmintrin.h>
	#elif  CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG 
		#include <emmintrin.h>
	#else
		#include <xmmintrin.h>
	#endif
#endif

#include "TraitsEx.h"

#if defined(CHTHOLLY_SIMD_NEON)
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

CHTHOLLY_INLINE float32x2_t vadd_f32_all(const float32x2_t& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE float32x2_t vadd_f32_all(const SimdT& arg, const SimdTs&... args)
{
	return vadd_f32(arg, vadd_f32_all(args...));
}

CHTHOLLY_INLINE float32x2_t vmul_f32_all(const float32x2_t& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE float32x2_t vmul_f32_all(const SimdT& arg, const SimdTs&... args)
{
	return vmul_f32(arg, vmul_f32_all(args...));
}

CHTHOLLY_INLINE float32x4_t vaddq_f32_all(const float32x4_t& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE float32x4_t vaddq_f32_all(const SimdT& arg, const SimdTs&... args)
{
	return vaddq_f32(arg, vaddq_f32_all(args...));
}

CHTHOLLY_INLINE float32x4_t vmulq_f32_all(const float32x4_t& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE float32x4_t vmulq_f32_all(const SimdT& arg, const SimdTs&... args)
{
	return vmulq_f32(arg, vmulq_f32_all(args...));
}

CHTHOLLY_INLINE int32x2_t vadd_s32_all(const int32x2_t& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE int32x2_t vadd_s32_all(const SimdT& arg, const SimdTs&... args)
{
	return vadd_s32(arg, vadd_s32_all(args...));
}

CHTHOLLY_INLINE int32x2_t vmul_s32_all(const int32x2_t& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE int32x2_t vmul_s32_all(const SimdT& arg, const SimdTs&... args)
{
	return vmul_s32(arg, vmul_s32_all(args...));
}

CHTHOLLY_INLINE int32x4_t vaddq_s32_all(const int32x4_t& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE int32x4_t vaddq_s32_all(const SimdT& arg, const SimdTs&... args)
{
	return vaddq_s32(arg, vaddq_s32_all(args...));
}

CHTHOLLY_INLINE int32x4_t vmulq_s32_all(const int32x4_t& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE int32x4_t vmulq_s32_all(const SimdT& arg, const SimdTs&... args)
{
	return vmulq_s32(arg, vmulq_s32_all(args...));
}

#elif defined(CHTHOLLY_SIMD_SSE)

CHTHOLLY_INLINE __m128 _mm_add_ps_all(const __m128& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE __m128 _mm_add_ps_all(const SimdT& arg, const SimdTs&... args)
{
	return _mm_add_ps(arg, _mm_add_ps_all(args...));
}

CHTHOLLY_INLINE __m128 _mm_mul_ps_all(const __m128& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE __m128 _mm_mul_ps_all(const SimdT& arg, const SimdTs&... args)
{
	return _mm_mul_ps(arg, _mm_mul_ps_all(args...));
}

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

CHTHOLLY_INLINE __m128i _mm_add_epi32_all(const __m128i& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE __m128i _mm_add_epi32_all(const SimdT& arg, const SimdTs&... args)
{
	return _mm_add_epi32(arg, _mm_add_epi32_all(args...));
}

#endif

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

CHTHOLLY_INLINE __m128i _mm_mul_epi32_all(const __m128i& arg)
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_INLINE __m128i _mm_mul_epi32_all(const SimdT& arg, const SimdTs&... args)
{
	return _mm_mul_epi32(arg, _mm_mul_epi32_all(args...));
}

#endif

#endif

#endif