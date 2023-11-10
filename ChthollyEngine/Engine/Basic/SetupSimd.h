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

CHTHOLLY_FUNC float32x2_t vclamp_f32(const float32x2_t& x, const float32x2_t& min, const float32x2_t& max) noexcept
{
	return vmin_f32(vmax_f32(x, min), max);
}

CHTHOLLY_FUNC float32x4_t vclampq_f32(const float32x4_t& x, const float32x4_t& min, const float32x4_t& max) noexcept
{
	return vminq_f32(vmaxq_f32(x, min), max);
}

CHTHOLLY_FUNC int32x2_t vclamp_s32(const int32x2_t& x, const int32x2_t& min, const int32x2_t& max) noexcept
{
	return vmin_s32(vmax_s32(x, min), max);
}

CHTHOLLY_FUNC int32x4_t vclampq_s32(const int32x4_t& x, const int32x4_t& min, const int32x4_t& max) noexcept
{
	return vminq_s32(vmaxq_s32(x, min), max);
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x2_t vadd_f32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return vadd_f32(arg, vadd_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x2_t vadd_f32_all<float32x2_t>(const float32x2_t& arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x2_t vmul_f32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return vmul_f32(arg, vmul_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x2_t vmul_f32_all<float32x2_t>(const float32x2_t& arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x4_t vaddq_f32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return vaddq_f32(arg, vaddq_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x4_t vaddq_f32_all<float32x4_t>(const float32x4_t& arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x4_t vmulq_f32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return vmulq_f32(arg, vmulq_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x4_t vmulq_f32_all<float32x4_t>(const float32x4_t& arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x2_t vadd_s32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return vadd_s32(arg, vadd_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x2_t vadd_s32_all<int32x2_t>(const int32x2_t& arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x2_t vmul_s32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return vmul_s32(arg, vmul_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x2_t vmul_s32_all<int32x2_t>(const int32x2_t& arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x4_t vaddq_s32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return vaddq_s32(arg, vaddq_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x4_t vaddq_s32_all<int32x4_t>(const int32x4_t& arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x4_t vmulq_s32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return vmulq_s32(arg, vmulq_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x4_t vmulq_s32_all<int32x4_t>(const int32x4_t& arg) noexcept
{
	return arg;
}

#elif defined(CHTHOLLY_SIMD_SSE)

CHTHOLLY_FUNC __m128 _mm_clamp_ps(const __m128& x, const __m128& min, const __m128& max) noexcept
{
	return _mm_min_ps(_mm_max_ps(x, min), max);
}

CHTHOLLY_FUNC __m128 _mm_abs_ps(const __m128& x) noexcept
{
	const union { unsigned int i; float f; } mask = { 0x7fffffff };
	__m128 ret = _mm_and_ps(x, _mm_set1_ps(mask.f));
	return ret;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128 _mm_add_ps_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return _mm_add_ps(arg, _mm_add_ps_all(args...));
}

template<>
CHTHOLLY_FUNC __m128 _mm_add_ps_all<__m128>(const __m128& arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128 _mm_mul_ps_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return _mm_mul_ps(arg, _mm_mul_ps_all(args...));
}

template<>
CHTHOLLY_FUNC __m128 _mm_mul_ps_all<__m128>(const __m128& arg) noexcept
{
	return arg;
}

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128i _mm_add_epi32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return _mm_add_epi32(arg, _mm_add_epi32_all(args...));
}

template<>
CHTHOLLY_FUNC __m128i _mm_add_epi32_all<__m128i>(const __m128i& arg) noexcept
{
	return arg;
}

#endif

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

CHTHOLLY_FUNC __m128 _mm_clamp_epi32(const __m128i& x, const __m128i& min, const __m128i& max) noexcept
{
	return _mm_min_epi32(_mm_max_epi32(x, min), max);
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128i _mm_mul_epi32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return _mm_mul_epi32(arg, _mm_mul_epi32_all(args...));
}

template<>
CHTHOLLY_FUNC __m128i _mm_mul_epi32_all<__m128i>(const __m128i& arg) noexcept
{
	return arg;
}
#endif

#endif

#endif