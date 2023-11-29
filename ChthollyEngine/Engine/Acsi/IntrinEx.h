#ifndef _INTRIN_EX_H_
#define _INTRIN_EX_H_

#include "SetupAcsi.h"

#if defined(CHTHOLLY_SIMD_SSE)

CHTHOLLY_FUNC __m128 acsi_mm_clamp_ps(const __m128& x, const __m128& min, const __m128& max) noexcept
{
	return _mm_min_ps(_mm_max_ps(x, min), max);
}

CHTHOLLY_FUNC __m128 acsi_mm_abs_ps(const __m128& x) noexcept
{
	const union { unsigned int i; float f; } mask = { 0x7fffffff };
	__m128 ret = _mm_and_ps(x, _mm_set1_ps(mask.f));
	return ret;
}

CHTHOLLY_FUNC __m128 acsi_mm_neg_ps(const __m128& x) noexcept
{
	union { unsigned int i; float f; } mask = { 0x80000000 };
	__m128 m_mask = _mm_set1_ps(mask.f);
	__m128 ret = _mm_or_ps(_mm_andnot_ps(x, m_mask), _mm_andnot_ps(m_mask, x));
	return ret;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128 acsi_mm_add_ps_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return _mm_add_ps(arg, acsi_mm_add_ps_all(args...));
}

template<>
CHTHOLLY_FUNC __m128 acsi_mm_add_ps_all<__m128>(const __m128& arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128 acsi_mm_mul_ps_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return _mm_mul_ps(arg, acsi_mm_mul_ps_all(args...));
}

template<>
CHTHOLLY_FUNC __m128 acsi_mm_mul_ps_all<__m128>(const __m128& arg) noexcept
{
	return arg;
}

CHTHOLLY_FUNC __m128 acsi_mm_round_ps(const __m128& x) noexcept
{
#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG
	return _mm_round_ps(x, _MM_FROUND_TO_NEAREST_INT);
#else
	const union { unsigned int i; float f; } mask = { 0x80000000 };
	__m128 tmp = _mm_and_ps(x, _mm_set1_ps(mask.f));
	tmp = _mm_or_ps(tmp, _mm_set_ps1(8388608.f));
    __m128 ret = _mm_sub_ps(_mm_add_ps(x, tmp), tmp);
	return ret;
#endif
}

CHTHOLLY_FUNC __m128 acsi_mm_floor_ps(const __m128& x) noexcept
{
#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG
	return _mm_floor_ps(x);
#else
	__m128 rnd = acsi_mm_round_ps(x);
	__m128 tmp = _mm_cmplt_ps(x, rnd);
	tmp = _mm_and_ps(tmp, _mm_set1_ps(1.f));
	__m128 ret = _mm_sub_ps(rnd, tmp);
	return ret;
#endif
}


CHTHOLLY_FUNC __m128 acsi_mm_ceil_ps(const __m128& x) noexcept
{
#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG
	return _mm_ceil_ps(x);
#else
	__m128 rnd = acsi_mm_round_ps(x);
	__m128 tmp = _mm_cmpgt_ps(x, rnd);
	tmp = _mm_and_ps(tmp, _mm_set1_ps(1.0f));
	__m128 ret = _mm_add_ps(rnd, tmp);
	return ret;
#endif
}

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

CHTHOLLY_FUNC __m128i acsi_mm_neg_epi32(const __m128i& x) noexcept
{
	return _mm_sub_epi32(_mm_set1_epi32(0), x);
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128i acsi_mm_add_epi32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return _mm_add_epi32(arg, acsi_mm_add_epi32_all(args...));
}

template<>
CHTHOLLY_FUNC __m128i acsi_mm_add_epi32_all<__m128i>(const __m128i& arg) noexcept
{
	return arg;
}

CHTHOLLY_FUNC __m128i acsi_mm_abs_epi32(const __m128i& x) noexcept
{
#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE3_FLAG
	return _mm_abs_epi32(x);
#else
	__m128i tmp = _mm_srai_epi32(x, 31);
	__m128i ret = _mm_sub_epi32(_mm_xor_si128(x, tmp), tmp);
	return ret;
#endif
}

#endif

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

CHTHOLLY_FUNC __m128 acsi_mm_clamp_epi32(const __m128i& x, const __m128i& min, const __m128i& max) noexcept
{
	return _mm_min_epi32(_mm_max_epi32(x, min), max);
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128i acsi_mm_mul_epi32_all(const SimdT& arg, const SimdTs&... args) noexcept
{
	return _mm_mul_epi32(arg, acsi_mm_mul_epi32_all(args...));
}

template<>
CHTHOLLY_FUNC __m128i acsi_mm_mul_epi32_all<__m128i>(const __m128i& arg) noexcept
{
	return arg;
}
#endif

#endif

#endif