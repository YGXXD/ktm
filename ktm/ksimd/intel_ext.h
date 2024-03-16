#ifndef _KTM_INTEL_EXT_H_
#define _KTM_INTEL_EXT_H_

#include "arch_def.h"
#include <cstddef>

#if defined(KTM_SIMD_SUPPORT)

namespace ext 
{

#if KTM_SIMD_ENABLE(KTM_SIMD_SSE)

KTM_FUNC __m128 dup128_f32(float a) noexcept
{
  	return _mm_set1_ps(a);
}

KTM_FUNC __m128 setzero128_f32() noexcept
{
	return _mm_setzero_ps();
}

KTM_FUNC __m128 set128_f32(float a, float b, float c, float d) noexcept
{
    return _mm_set_ps(a, b, c, d);
}

template<size_t N3, size_t N2, size_t N1, size_t N0>
KTM_FUNC __m128 shuffle128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_shuffle_ps(a, b, _MM_SHUFFLE(N3, N2, N1, N0));
}

template<size_t N3, size_t N2, size_t N1, size_t N0>
KTM_FUNC __m128 shuffle128_f32(__m128 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_SSE2)
    return _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(a), _MM_SHUFFLE(N3, N2, N1, N0))); 
#else
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(N3, N2, N1, N0));
#endif
}

KTM_FUNC float cast128_to32_f32(__m128 a) noexcept
{
  	return _mm_cvtss_f32(a);
}

KTM_FUNC __m128 and128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_and_ps(a, b); 
}

KTM_FUNC __m128 or128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_or_ps(a, b); 
}

KTM_FUNC __m128 xor128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_xor_ps(a, b); 
}

KTM_FUNC __m128 add128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_add_ps(a, b);
}

KTM_FUNC __m128 sub128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_sub_ps(a, b);
}

KTM_FUNC __m128 mul128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_mul_ps(a, b);
}

KTM_FUNC __m128 div128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_div_ps(a, b);
}

KTM_FUNC __m128 madd128_f32(__m128 a, __m128 b, __m128 c) noexcept
{
    return _mm_add_ps(a, _mm_mul_ps(b, c));
}

KTM_FUNC __m128 neg128_f32(__m128 a) noexcept
{
	constexpr union { unsigned int i; float f; } mask = { 0x80000000 };
	return _mm_xor_ps(x, _mm_set1_ps(mask.f));
}

KTM_FUNC __m128 abs128_f32(__m128 a) noexcept
{
	constexpr union { unsigned int i; float f; } mask = { 0x7fffffff };
	return _mm_and_ps(x, _mm_set1_ps(mask.f));
}

KTM_FUNC float radd128_f32(__m128 a) noexcept
{
    __m128 shuf = shuffle128_f32<3, 3, 1, 1>(a);
    __m128 add = _mm_add_ps(a, shuf);
    shuf = shuffle128_f32<3, 2, 3, 2>(add);
    add = _mm_add_ss(add, shuf);
    return _mm_cvtss_f32(add);
}

KTM_FUNC float rmax128_f32(__m128 a) noexcept
{
    __m128 shuf = shuffle128_f32<3, 3, 1, 1>(a);
    __m128 max = _mm_max_ps(a, shuf);
    shuf = shuffle128_f32<3, 2, 3, 2>(max);
    max = _mm_max_ss(max, shuf);
    return _mm_cvtss_f32(max);
}

KTM_FUNC float rmin128_f32(float32x4_t a) noexcept
{
    __m128 shuf = shuffle128_f32<3, 3, 1, 1>(a);
    __m128 min = _mm_min_ps(a, shuf);
    shuf = shuffle128_f32<3, 2, 3, 2>(min);
    min = _mm_min_ss(min, shuf);
    return _mm_cvtss_f32(min);
}

KTM_FUNC __m128 max128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_max_ps(a, b);
}

KTM_FUNC __m128 min128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_min_ps(a, b);
}

KTM_FUNC __m128 clamp128_f32(__m128 a, __m128 min, __m128 max) noexcept
{
	return _mm_min_ps(_mm_max_ps(a, min), max);
}

KTM_FUNC __m128 cmpeq128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_cmpeq_ps(a, b);
}

KTM_FUNC __m128 cmplt128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_cmplt_ps(a, b);
}

KTM_FUNC __m128 cmpgt128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_cmpgt_ps(a, b);
}

KTM_FUNC __m128 cmple128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_cmple_ps(a, b);
}

KTM_FUNC __m128 cmpge128_f32(__m128 a, __m128 b) noexcept
{
    return _mm_cmpge_ps(a, b);
}

KTM_FUNC __m128 recipl128_f32(__m128 a) noexcept
{
	return _mm_rcp_ps(x);
}

KTM_FUNC __m128 reciph128_f32(__m128 a) noexcept
{
	constexpr union { unsigned int i; float f; } ninf = { 0xff800000 };
	__m128 r = recipl128_f32(x);
	__m128 mask = _mm_cmpeq_ps(x, _mm_setzero_ps());
	__m128 x_sel = _mm_andnot_ps(mask, x);
	__m128 ninf_sel = _mm_and_ps(mask, _mm_set1_ps(ninf.f));
	__m128 mul = _mm_mul_ps(_mm_or_ps(x_sel, ninf_sel), r);
	__m128 sub = _mm_sub_ps(_mm_set1_ps(2.f), mul);
	return _mm_mul_ps(r, sub);
}

KTM_FUNC __m128 rsqrtl128_f32(__m128 a) noexcept
{
	return _mm_rsqrt_ps(a);
}

KTM_FUNC __m128 rsqrth128_f32(__m128 a) noexcept
{
	constexpr union { unsigned int i; float f; } inf = { 0x7f800000 };
	__m128 r = rsqrtl128_f32(x);
	__m128 mask = _mm_cmpeq_ps(r, _mm_set1_ps(inf.f));
	__m128 x_sel = _mm_andnot_ps(mask, x);
	__m128 ninf_sel = _mm_and_ps(mask, _mm_set1_ps(-inf.f));
	__m128 mul = _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(0.5f), _mm_or_ps(x_sel, ninf_sel)), _mm_mul_ps(r, r));
	__m128 sub = _mm_sub_ps(_mm_set1_ps(1.5f), mul);
	return _mm_mul_ps(r, sub);
}

KTM_FUNC __m128 sqrtl128_f32(__m128 a) noexcept
{
	return _mm_rcp_ps(_mm_rsqrt_ps(a));
}

KTM_FUNC __m128 sqrth128_f32(__m128 a) noexcept
{
    return _mm_sqrt_ps(a);
}

KTM_FUNC __m128 round128_f32(__m128 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_SSE4_1)
	return _mm_round_ps(x, _MM_FROUND_TO_NEAREST_INT);
#else
	constexpr union { unsigned int i; float f; } mask1 = { 0x80000000 };
	constexpr union { unsigned int i; float f; } mask2 = { 0x4b000000 };
	__m128 tmp = _mm_and_ps(x, _mm_set1_ps(mask1.f));
	tmp = _mm_or_ps(tmp, _mm_set1_ps(mask2.f));
    __m128 ret = _mm_sub_ps(_mm_add_ps(x, tmp), tmp);
	return ret;
#endif
}

KTM_FUNC __m128 floor128_f32(__m128 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_SSE4_1)
	return _mm_floor_ps(x);
#else
	constexpr union { unsigned int i; float f; } mask = { 0x3f800000 };
	__m128 rnd = round_ps(x);
	__m128 tmp = _mm_cmplt_ps(x, rnd);
	tmp = _mm_and_ps(tmp, _mm_set1_ps(mask.f));
	__m128 ret = _mm_sub_ps(rnd, tmp);
	return ret;
#endif
}

KTM_FUNC __m128 ceil128_f32(__m128 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_SSE4_1)
	return _mm_ceil_ps(x);
#else
	constexpr union { unsigned int i; float f; } mask = { 0x3f800000 };
	__m128 rnd = round_ps(x);
	__m128 tmp = _mm_cmpgt_ps(x, rnd);
	tmp = _mm_and_ps(tmp, _mm_set1_ps(mask.f));
	__m128 ret = _mm_add_ps(rnd, tmp);
	return ret;
#endif
}

#endif

#if KTM_SIMD_ENABLE(KTM_SIMD_SSE2)

KTM_FUNC __m128i dup128_s32(int a) noexcept
{
  	return _mm_set1_epi32(a);
}

KTM_FUNC __m128i set128_s32(int a, int b, int c, int d) noexcept
{
	return _mm_set_epi32(a, b, c, d);
}

KTM_FUNC __m128i add128_s32(__m128i a, __m128i b) noexcept
{
    return _mm_add_epi32(a, b);
}

KTM_FUNC __m128i sub128_s32(__m128i a, __m128i b) noexcept
{
    return _mm_sub_epi32(a, b);
}

KTM_FUNC __m128i neg128_s32(__m128i a) noexcept
{
	return _mm_sub_epi32(_mm_setzero_si128(), a);
}

KTM_FUNC __m128i radd128_s32(__m128i a) noexcept
{
    __m128i shuf = _mm_castps_si128(shuffle128_f32<3, 3, 1, 1>(_mm_castsi128_ps(a)));
    __m128i add = _mm_add_epi32(a, shuf);
    shuf = _mm_castps_si128(shuffle128_f32<3, 2, 3, 2>(_mm_castsi128_ps(add)));
    add = _mm_add_epi32(add, shuf);
    return _mm_cvtsi128_si32(add);
}

KTM_FUNC __m128i cmpeq128_s32(__m128i a, __m128i b) noexcept
{
    return _mm_cmpeq_epi32(a, b);
}

KTM_FUNC __m128i cmplt128_s32(__m128i a, __m128i b) noexcept
{
    return _mm_cmplt_epi32(a, b);
}

KTM_FUNC __m128i cmpgt128_s32(__m128i a, __m128i b) noexcept
{
    return _mm_cmpgt_epi32(a, b);
}

KTM_FUNC __m128i cmple128_s32(__m128i a, __m128i b) noexcept
{
    return _mm_xor_si128(_mm_cmpgt_epi32(a, b), _mm_set1_epi32(0xffffffff));
}

KTM_FUNC __m128i cmpge128_s32(__m128i a, __m128i b) noexcept
{
    return _mm_xor_si128(_mm_cmplt_epi32(a, b), _mm_set1_epi32(0xffffffff));
}

#endif

#if KTM_SIMD_ENABLE(KTM_SIMD_SSSE3)

KTM_FUNC __m128i abs128_s32(__m128i a) noexcept
{
	return _mm_abs_epi32(a);
}

#endif

#if KTM_SIMD_ENABLE(1)
KTM_FUNC int32x4_t mul128_s32(int32x4_t a, int32x4_t b) noexcept
{
    return vmulq_s32(a, b);
}

// KTM_FUNC int32x4_t madd128_s32(int32x4_t a, int32x4_t b, int32x4_t c) noexcept
// {
//   	return vmlaq_s32(a, b, c);
// }

KTM_FUNC int rmax128_s32(int32x4_t a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
	return vmaxvq_s32(a);
#else
  	int32x2_t r = vpmax_s32(vget_low_s32(x), vget_high_s32(x));
  	r = vpmax_s32(r, r);
  	return vget_lane_s32(r, 0);
#endif
}

// KTM_FUNC int rmin128_s32(int32x4_t a) noexcept
// {
// #if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
// 	return vminvq_s32(a);
// #else
//   	int32x2_t r = vpmin_s32(vget_low_s32(x), vget_high_s32(x));
//   	r = vpmin_s32(r, r);
//   	return vget_lane_s32(r, 0);
// #endif
// }

// KTM_FUNC int32x4_t max128_s32(int32x4_t a, int32x4_t b) noexcept
// {
// 	return vmaxq_s32(a, b);
// }

// KTM_FUNC int32x4_t min128_s32(int32x4_t a, int32x4_t b) noexcept
// {
// 	return vminq_s32(a, b);
// }

// KTM_FUNC int32x4_t clamp128_s32(int32x4_t a, int32x4_t min, int32x4_t max) noexcept
// {
// 	return vminq_s32(vmaxq_s32(a, min), max);
// }

#endif

}

#endif

#endif