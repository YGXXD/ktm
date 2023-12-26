#ifndef _ACSI_INTRIN_H_
#define _ACSI_INTRIN_H_

#include "SetupAcsi.h"
#include <cstddef>

#if defined(CHTHOLLY_SIMD_SSE)

namespace intrin
{
namespace ex
{
CHTHOLLY_FUNC __m128 clamp_ps(__m128 x, __m128 min, __m128 max) noexcept
{
	return _mm_min_ps(_mm_max_ps(x, min), max);
}

CHTHOLLY_FUNC __m128 abs_ps(__m128 x) noexcept
{
	const union { unsigned int i; float f; } mask = { 0x7fffffff };
	__m128 ret = _mm_and_ps(x, _mm_set1_ps(mask.f));
	return ret;
}

CHTHOLLY_FUNC __m128 neg_ps(__m128 x) noexcept
{
	union { unsigned int i; float f; } mask = { 0x80000000 };
	__m128 m_mask = _mm_set1_ps(mask.f);
	__m128 ret = _mm_or_ps(_mm_andnot_ps(x, m_mask), _mm_andnot_ps(m_mask, x));
	return ret;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128 add_ps_all(SimdT arg, SimdTs... args) noexcept
{
	return _mm_add_ps(arg, add_ps_all(args...));
}

template<>
CHTHOLLY_FUNC __m128 add_ps_all<__m128>(__m128 arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128 mul_ps_all(SimdT arg, SimdTs... args) noexcept
{
	return _mm_mul_ps(arg, mul_ps_all(args...));
}

template<>
CHTHOLLY_FUNC __m128 mul_ps_all<__m128>(__m128 arg) noexcept
{
	return arg;
}

CHTHOLLY_FUNC __m128 round_ps(__m128 x) noexcept
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

CHTHOLLY_FUNC __m128 floor_ps(__m128 x) noexcept
{
#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG
	return _mm_floor_ps(x);
#else
	__m128 rnd = round_ps(x);
	__m128 tmp = _mm_cmplt_ps(x, rnd);
	tmp = _mm_and_ps(tmp, _mm_set1_ps(1.f));
	__m128 ret = _mm_sub_ps(rnd, tmp);
	return ret;
#endif
}


CHTHOLLY_FUNC __m128 ceil_ps(__m128 x) noexcept
{
#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG
	return _mm_ceil_ps(x);
#else
	__m128 rnd = round_ps(x);
	__m128 tmp = _mm_cmpgt_ps(x, rnd);
	tmp = _mm_and_ps(tmp, _mm_set1_ps(1.0f));
	__m128 ret = _mm_add_ps(rnd, tmp);
	return ret;
#endif
}

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

CHTHOLLY_FUNC __m128i neg_epi32(__m128i x) noexcept
{
	return _mm_sub_epi32(_mm_set1_epi32(0), x);
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128i add_epi32_all(SimdT arg, SimdTs... args) noexcept
{
	return _mm_add_epi32(arg, add_epi32_all(args...));
}

template<>
CHTHOLLY_FUNC __m128i add_epi32_all<__m128i>(__m128i arg) noexcept
{
	return arg;
}

CHTHOLLY_FUNC __m128i abs_epi32(__m128i x) noexcept
{
#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE3_FLAG
	return abs_epi32(x);
#else
	__m128i tmp = _mm_srai_epi32(x, 31);
	__m128i ret = _mm_sub_epi32(_mm_xor_si128(x, tmp), tmp);
	return ret;
#endif
}

#endif

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

CHTHOLLY_FUNC __m128i clamp_epi32(__m128i x, __m128i min, __m128i max) noexcept
{
	return _mm_min_epi32(_mm_max_epi32(x, min), max);
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC __m128i mullo_epi32_all(SimdT arg, SimdTs... args) noexcept
{
	return _mm_mullo_epi32(arg, mullo_epi32_all(args...));
}

template<>
CHTHOLLY_FUNC __m128i mullo_epi32_all<__m128i>(__m128i arg) noexcept
{
	return arg;
}

#endif	
}

namespace geo
{
CHTHOLLY_FUNC __m128 fv4_dot4(__m128 x, __m128 y) noexcept
{
	__m128 mul = _mm_mul_ps(x, y);
#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE3_FLAG
	__m128 add_0 = _mm_hadd_ps(mul, mul);;
	__m128 add_1 = _mm_hadd_ps(add_0, add_0);;
#else
	__m128 add_0 = _mm_add_ps(mul, _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1)));
	__m128 add_1 = _mm_add_ps(add_0, _mm_shuffle_ps(add_0, add_0, _MM_SHUFFLE(0, 1, 2, 3))); 
#endif
	return add_1;
}

template<size_t N>
CHTHOLLY_FUNC float fv4_dot1(__m128 x, __m128 y) noexcept;

template<>
CHTHOLLY_FUNC float fv4_dot1<3>(__m128 x, __m128 y) noexcept
{
	__m128 mul = _mm_mul_ps(x, y);
	__m128 sum_0 = _mm_add_ss(mul, _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(0, 3, 2, 1)));
	__m128 sum_1 = _mm_add_ss(sum_0, _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(1, 0, 3, 2)));
	return _mm_cvtss_f32(sum_1); 
}

template<>
CHTHOLLY_FUNC float fv4_dot1<4>(__m128 x, __m128 y) noexcept
{
	__m128 mul = _mm_mul_ps(x, y);
	__m128 sum_0 = _mm_add_ps(mul, _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(1, 0, 3, 2)));
	__m128 sum_1 = _mm_add_ss(sum_0, _mm_shuffle_ps(sum_0, sum_0, _MM_SHUFFLE(0, 3, 2, 1)));
	return _mm_cvtss_f32(sum_1); 
}

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

CHTHOLLY_FUNC __m128i sv4_dot4(__m128i x, __m128i y) noexcept
{
	__m128i mul = _mm_mullo_epi32(x, y);
	__m128i add_0 = _mm_hadd_epi32(mul, mul);;
	__m128i add_1 = _mm_hadd_epi32(add_0, add_0);;
	return add_1;
}

template<size_t N>
CHTHOLLY_FUNC int sv4_dot1(__m128i x, __m128i y) noexcept;

template<>
CHTHOLLY_FUNC int sv4_dot1<3>(__m128i x, __m128i y) noexcept
{
	__m128i mul = _mm_mullo_epi32(x, y);
	__m128i sum_0 = _mm_add_epi32(mul, _mm_shuffle_epi32(mul, _MM_SHUFFLE(0, 3, 2, 1)));
	__m128i sum_1 = _mm_add_epi32(sum_0, _mm_shuffle_epi32(mul, _MM_SHUFFLE(1, 0, 3, 2)));
	return _mm_cvtsi128_si32(sum_1); 
}

template<>
CHTHOLLY_FUNC int sv4_dot1<4>(__m128i x, __m128i y) noexcept
{
	__m128i mul = _mm_mullo_epi32(x, y);
	__m128i sum_0 = _mm_add_epi32(mul, _mm_shuffle_epi32(mul, _MM_SHUFFLE(1, 0, 3, 2)));
	__m128i sum_1 = _mm_add_epi32(sum_0, _mm_shuffle_epi32(sum_0, _MM_SHUFFLE(0, 3, 2, 1)));
	return _mm_cvtsi128_si32(sum_1); 
}

#endif
}
} 

#endif

#endif