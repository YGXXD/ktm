#ifndef _KTM_X86_H_
#define _KTM_X86_H_

#include "intrin.h"
#include <cstddef>

#if defined(KTM_SIMD_SSE)

namespace x86
{
namespace ext
{
KTM_FUNC __m128 clamp_ps(__m128 x, __m128 min, __m128 max) noexcept
{
	return _mm_min_ps(_mm_max_ps(x, min), max);
}

KTM_FUNC __m128 abs_ps(__m128 x) noexcept
{
	constexpr union { unsigned int i; float f; } mask = { 0x7fffffff };
	__m128 ret = _mm_and_ps(x, _mm_set1_ps(mask.f));
	return ret;
}

KTM_FUNC __m128 neg_ps(__m128 x) noexcept
{
	constexpr union { unsigned int i; float f; } mask = { 0x80000000 };
	__m128 m_mask = _mm_set1_ps(mask.f);
	__m128 ret = _mm_or_ps(_mm_andnot_ps(x, m_mask), _mm_andnot_ps(m_mask, x));
	return ret;
}

template<typename SimdT, typename ...SimdTs>
KTM_FUNC __m128 add_ps_all(SimdT arg, SimdTs... args) noexcept
{
	return _mm_add_ps(arg, add_ps_all(args...));
}

template<>
KTM_FUNC __m128 add_ps_all<__m128>(__m128 arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
KTM_FUNC __m128 mul_ps_all(SimdT arg, SimdTs... args) noexcept
{
	return _mm_mul_ps(arg, mul_ps_all(args...));
}

template<>
KTM_FUNC __m128 mul_ps_all<__m128>(__m128 arg) noexcept
{
	return arg;
}

KTM_FUNC __m128 fast_rsqrt_ps(__m128 x) noexcept
{
	return _mm_rsqrt_ps(x);
}

KTM_FUNC __m128 rsqrt_ps(__m128 x) noexcept
{
	__m128 r = fast_rsqrt_ps(x);
	__m128 mask = _mm_cmpeq_ps(r, _mm_set1_ps(1e50f));
	__m128 x_mask = _mm_andnot_ps(mask, x);
	__m128 neg_inf_mask = _mm_and_ps(mask, _mm_set1_ps(-1e50f));
	mask = _mm_or_ps(x_mask, neg_inf_mask);
	__m128 mul = mul_ps_all(_mm_set1_ps(0.5f), mask, r, r);
	__m128 sub = _mm_sub_ps(_mm_set1_ps(1.5f), mul);
	return _mm_mul_ps(r, sub);
}

KTM_FUNC __m128 fast_recip_ps(__m128 x) noexcept
{
	return _mm_rcp_ps(x);
}

KTM_FUNC __m128 recip_ps(__m128 x) noexcept
{
	__m128 r = fast_recip_ps(x);
	__m128 mask = _mm_cmpeq_ps(x, _mm_setzero_ps());
	__m128 x_mask = _mm_andnot_ps(mask, x);
	__m128 neg_inf_mask = _mm_and_ps(mask, _mm_set1_ps(-1e50f));
	mask = _mm_or_ps(x_mask, neg_inf_mask);
	__m128 mul = _mm_mul_ps(mask, r);
	__m128 sub = _mm_sub_ps(_mm_set1_ps(2.f), mul);
	return _mm_mul_ps(r, sub);
}

KTM_FUNC __m128 round_ps(__m128 x) noexcept
{
#if KTM_SIMD_X86 & KTM_SIMD_SSE4_1_FLAG
	return _mm_round_ps(x, _MM_FROUND_TO_NEAREST_INT);
#else
	constexpr union { unsigned int i; float f; } mask = { 0x80000000 };
	__m128 tmp = _mm_and_ps(x, _mm_set1_ps(mask.f));
	tmp = _mm_or_ps(tmp, _mm_set_ps1(8388608.f));
    __m128 ret = _mm_sub_ps(_mm_add_ps(x, tmp), tmp);
	return ret;
#endif
}

KTM_FUNC __m128 floor_ps(__m128 x) noexcept
{
#if KTM_SIMD_X86 & KTM_SIMD_SSE4_1_FLAG
	return _mm_floor_ps(x);
#else
	__m128 rnd = round_ps(x);
	__m128 tmp = _mm_cmplt_ps(x, rnd);
	tmp = _mm_and_ps(tmp, _mm_set1_ps(1.f));
	__m128 ret = _mm_sub_ps(rnd, tmp);
	return ret;
#endif
}

KTM_FUNC __m128 ceil_ps(__m128 x) noexcept
{
#if KTM_SIMD_X86 & KTM_SIMD_SSE4_1_FLAG
	return _mm_ceil_ps(x);
#else
	__m128 rnd = round_ps(x);
	__m128 tmp = _mm_cmpgt_ps(x, rnd);
	tmp = _mm_and_ps(tmp, _mm_set1_ps(1.0f));
	__m128 ret = _mm_add_ps(rnd, tmp);
	return ret;
#endif
}

#if KTM_SIMD_X86 & KTM_SIMD_SSE2_FLAG

KTM_FUNC __m128i neg_epi32(__m128i x) noexcept
{
	return _mm_sub_epi32(_mm_setzero_si128(), x);
}

template<typename SimdT, typename ...SimdTs>
KTM_FUNC __m128i add_epi32_all(SimdT arg, SimdTs... args) noexcept
{
	return _mm_add_epi32(arg, add_epi32_all(args...));
}

template<>
KTM_FUNC __m128i add_epi32_all<__m128i>(__m128i arg) noexcept
{
	return arg;
}

KTM_FUNC __m128i abs_epi32(__m128i x) noexcept
{
#if KTM_SIMD_X86 & KTM_SIMD_SSE3_FLAG
	return _mm_abs_epi32(x);
#else
	__m128i tmp = _mm_srai_epi32(x, 31);
	__m128i ret = _mm_sub_epi32(_mm_xor_si128(x, tmp), tmp);
	return ret;
#endif
}

#endif

#if KTM_SIMD_X86 & KTM_SIMD_SSE4_1_FLAG

KTM_FUNC __m128i clamp_epi32(__m128i x, __m128i min, __m128i max) noexcept
{
	return _mm_min_epi32(_mm_max_epi32(x, min), max);
}

template<typename SimdT, typename ...SimdTs>
KTM_FUNC __m128i mullo_epi32_all(SimdT arg, SimdTs... args) noexcept
{
	return _mm_mullo_epi32(arg, mullo_epi32_all(args...));
}

template<>
KTM_FUNC __m128i mullo_epi32_all<__m128i>(__m128i arg) noexcept
{
	return arg;
}

#endif	
}

namespace geo
{
KTM_FUNC __m128 fv4_dot(__m128 x, __m128 y) noexcept
{
	__m128 mul = _mm_mul_ps(x, y);
#if KTM_SIMD_X86 & KTM_SIMD_SSE3_FLAG
	__m128 add_0 = _mm_hadd_ps(mul, mul);;
	__m128 add_1 = _mm_hadd_ps(add_0, add_0);;
#else
	__m128 add_0 = _mm_add_ps(mul, _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1)));
	__m128 add_1 = _mm_add_ps(add_0, _mm_shuffle_ps(add_0, add_0, _MM_SHUFFLE(0, 1, 2, 3))); 
#endif
	return add_1;
}

KTM_FUNC float fv3_dot1(__m128 x, __m128 y) noexcept
{
	__m128 mul = _mm_mul_ps(x, y);
	__m128 sum_0 = _mm_add_ss(mul, _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(0, 3, 2, 1)));
	__m128 sum_1 = _mm_add_ss(sum_0, _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(1, 0, 3, 2)));
	return _mm_cvtss_f32(sum_1); 
}

KTM_FUNC float fv4_dot1(__m128 x, __m128 y) noexcept
{
	return _mm_cvtss_f32(fv4_dot(x, y)); 
}

#if KTM_SIMD_X86 & KTM_SIMD_SSE4_1_FLAG

KTM_FUNC __m128i sv4_dot(__m128i x, __m128i y) noexcept
{
	__m128i mul = _mm_mullo_epi32(x, y);
	__m128i add_0 = _mm_hadd_epi32(mul, mul);;
	__m128i add_1 = _mm_hadd_epi32(add_0, add_0);;
	return add_1;
}

KTM_FUNC int sv3_dot1(__m128i x, __m128i y) noexcept
{
	__m128i mul = _mm_mullo_epi32(x, y);
	__m128i sum_0 = _mm_add_epi32(mul, _mm_shuffle_epi32(mul, _MM_SHUFFLE(0, 3, 2, 1)));
	__m128i sum_1 = _mm_add_epi32(sum_0, _mm_shuffle_epi32(mul, _MM_SHUFFLE(1, 0, 3, 2)));
	return _mm_cvtsi128_si32(sum_1); 
}

KTM_FUNC int sv4_dot1(__m128i x, __m128i y) noexcept
{
	return _mm_cvtsi128_si32(sv4_dot(x, y)); 
}

#endif
}

namespace mt
{
KTM_FUNC void fmt2_tp(__m64 out[2], const __m64 in[2]) noexcept
{
	out[0] = _mm_unpacklo_pi32(in[0], in[1]);
	out[1] = _mm_unpackhi_pi32(in[0], in[1]); 
}

KTM_FUNC void fmt3_tp(__m128 out[3], const __m128 in[3]) noexcept
{
	__m128 tmp_0 = _mm_shuffle_ps(in[0], in[1], _MM_SHUFFLE(1, 0, 1, 0));
	__m128 tmp_1 = _mm_shuffle_ps(in[0], in[1], _MM_SHUFFLE(3, 2, 3, 2));

	out[0] = _mm_shuffle_ps(tmp_0, in[2], _MM_SHUFFLE(3, 0, 2, 0));
	out[1] = _mm_shuffle_ps(tmp_0, in[2], _MM_SHUFFLE(3, 1, 3, 1));
	out[2] = _mm_shuffle_ps(tmp_1, in[2], _MM_SHUFFLE(3, 2, 2, 0));
}

KTM_FUNC void fmt4_tp(__m128 out[4], const __m128 in[4]) noexcept
{
	__m128 tmp_0 = _mm_shuffle_ps(in[0], in[1], _MM_SHUFFLE(1, 0, 1, 0));
	__m128 tmp_2 = _mm_shuffle_ps(in[0], in[1], _MM_SHUFFLE(3, 2, 3, 2));
	__m128 tmp_1 = _mm_shuffle_ps(in[2], in[3], _MM_SHUFFLE(1, 0, 1, 0));
	__m128 tmp_3 = _mm_shuffle_ps(in[2], in[3], _MM_SHUFFLE(3, 2, 3, 2));

	out[0] = _mm_shuffle_ps(tmp_0, tmp_1, _MM_SHUFFLE(2, 0, 2, 0));
	out[1] = _mm_shuffle_ps(tmp_0, tmp_1, _MM_SHUFFLE(3, 1, 3, 1));
	out[2] = _mm_shuffle_ps(tmp_2, tmp_3, _MM_SHUFFLE(2, 0, 2, 0));
	out[3] = _mm_shuffle_ps(tmp_2, tmp_3, _MM_SHUFFLE(3, 1, 3, 1));
}
}

namespace qt
{
KTM_FUNC __m128 fv3_mul_fq(__m128 v, __m128 q) noexcept
{
    __m128 q_opp = ext::neg_ps(q);

    __m128 tmp_0 = _mm_shuffle_ps(q, q_opp, _MM_SHUFFLE(2, 2, 3, 3));
    __m128 tmp_1 = _mm_shuffle_ps(q, q_opp, _MM_SHUFFLE(1, 0, 1, 0)); 

    __m128 mul_x = _mm_shuffle_ps(tmp_0, tmp_1, _MM_SHUFFLE(2, 1, 3, 0)); 
    __m128 mul_y = _mm_shuffle_ps(q, q_opp, _MM_SHUFFLE(1, 0, 3, 2)); 
    __m128 mul_z = _mm_shuffle_ps(tmp_1, tmp_0, _MM_SHUFFLE(2, 1, 0, 3));

    __m128 add_0 = _mm_mul_ps(_mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0)), mul_x); 
    __m128 add_1 = _mm_mul_ps(_mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1)), mul_y); 
    __m128 add_2 = _mm_mul_ps(_mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2)), mul_z); 

    return x86::ext::add_ps_all(add_0, add_1, add_2);
}

KTM_FUNC __m128 fq_mul_fq(__m128 x, __m128 y) noexcept
{
    __m128 add_012 = fv3_mul_fq(x, y);
    __m128 add_3 = _mm_mul_ps(_mm_shuffle_ps(x, x, _MM_SHUFFLE(3, 3, 3, 3)), y); 
    return _mm_add_ps(add_012, add_3);
}
}

} 

#endif

#endif