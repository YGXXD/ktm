#ifndef _KTM_INTRIN_API_H_
#define _KTM_INTRIN_API_H_

#include "arch_def.h"
#include "arm_ext.h"
#include "intel_ext.h"

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON)

#define _dup64_f32(a) ::ext::dup64_f32(a)
#define _setzero64_f32() ::ext::setzero64_f32()
#define _set64_f32(a, b) ::ext::set64_f32(a, b)
#define _shuff64_two_f32(a, b, n1, n0) ::ext::shuffle64_f32<n1, n0>(a, b)
#define _shuff64_one_f32(a, n1, n0) ::ext::shuffle64_f32<n1, n0>(a)
#define _cast64to32_f32(a) ::ext::cast64to32_f32(a)
#define _and64_f32(a, b) ::ext::and64_f32(a, b)
#define _or64_f32(a, b) ::ext::or64_f32(a, b)
#define _xor64_f32(a, b) ::ext::xor64_f32(a, b)
#define _add64_f32(a, b) ::ext::add64_f32(a, b)
#define _sub64_f32(a, b) ::ext::sub64_f32(a, b)
#define _mul64_f32(a, b) ::ext::mul64_f32(a, b)
#define _div64_f32(a, b) ::ext::div64_f32(a, b)
#define _madd64_f32(a, b, c) ::ext::madd64_f32(a, b, c)
#define _neg64_f32(a) ::ext::neg64_f32(a)
#define _abs64_f32(a) ::ext::abs64_f32(a)
#define _max64_f32(a, b) ::ext::max64_f32(a, b)
#define _min64_f32(a, b) ::ext::min64_f32(a, b)
#define _clamp64_f32(a, min, max) _min64_f32(_max64_f32(a, min), max)
#define _cmpeq64_f32(a, b) ::ext::cmpeq64_f32(a, b)
#define _cmplt64_f32(a, b) ::ext::cmplt64_f32(a, b)
#define _cmpgt64_f32(a, b) ::ext::cmpgt64_f32(a, b)
#define _cmple64_f32(a, b) ::ext::cmple64_f32(a, b)
#define _cmpge64_f32(a, b) ::ext::cmpge64_f32(a, b)
#define _recipl64_f32(a) ::ext::recipl64_f32(a)
#define _reciph64_f32(a) ::ext::reciph64_f32(a) 
#define _rsqrtl64_f32(a) ::ext::rsqrtl64_f32(a)
#define _rsqrth64_f32(a) ::ext::rsqrth64_f32(a)
#define _sqrtl64_f32(a) ::ext::sqrtl64_f32(a)
#define _sqrth64_f32(a) ::ext::sqrth64_f32(a) 

#define _dup64_s32(a) ::ext::dup64_s32(a)
#define _set64_s32(a, b) ::ext::set64_s32(a, b)
#define _add64_s32(a, b) ::ext::add64_s32(a, b)
#define _sub64_s32(a, b) ::ext::sub64_s32(a, b)
#define _mul64_s32(a, b) ::ext::mul64_s32(a, b)
#define _madd64_s32(a, b, c) ::ext::madd64_s32(a, b, c)
#define _neg64_s32(a) ::ext::neg64_s32(a)
#define _abs64_s32(a) ::ext::abs64_s32(a)
#define _max64_s32(a, b) ::ext::max64_s32(a, b)
#define _min64_s32(a, b) ::ext::min64_s32(a, b)
#define _clamp64_s32(a, min, max) _min64_s32(_max64_s32(a, min), max)
#define _cmpeq64_s32(a, b) ::ext::cmpeq64_s32(a, b)
#define _cmplt64_s32(a, b) ::ext::cmplt64_s32(a, b)
#define _cmpgt64_s32(a, b) ::ext::cmpgt64_s32(a, b)
#define _cmple64_s32(a, b) ::ext::cmple64_s32(a, b)
#define _cmpge64_s32(a, b) ::ext::cmpge64_s32(a, b)

#define _dup128_f32(a) ::ext::dup128_f32(a)
#define _setzero128_f32() ::ext::setzero128_f32()
#define _set128_f32(a, b) ::ext::set128_f32(a, b)
#define _shuff128_two_f32(a, b, n3, n2, n1, n0) ::ext::shuffle128_f32<n3, n2, n1, n0>(a, b)
#define _shuff128_one_f32(a, n3, n2, n1, n0) ::ext::shuffle128_f32<n3, n2, n1, n0>(a)
#define _cast128to32_f32(a) ::ext::cast128to32_f32(a)
#define _cast128to64_f32(a) ::ext::cast128to64_f32(a)
#define _and128_f32(a, b) ::ext::and128_f32(a, b)
#define _or128_f32(a, b) ::ext::or128_f32(a, b)
#define _xor128_f32(a, b) ::ext::xor128_f32(a, b)
#define _add128_f32(a, b) ::ext::add128_f32(a, b)
#define _sub128_f32(a, b) ::ext::sub128_f32(a, b)
#define _mul128_f32(a, b) ::ext::mul128_f32(a, b)
#define _div128_f32(a, b) ::ext::div128_f32(a, b)
#define _madd128_f32(a, b, c) ::ext::madd128_f32(a, b, c)
#define _neg128_f32(a) ::ext::neg128_f32(a)
#define _abs128_f32(a) ::ext::abs128_f32(a)
#define _max128_f32(a, b) ::ext::max128_f32(a, b)
#define _min128_f32(a, b) ::ext::min128_f32(a, b)
#define _clamp128_f32(a, min, max) _min128_f32(_max128_f32(a, min), max)
#define _cmpeq128_f32(a, b) ::ext::cmpeq128_f32(a, b)
#define _cmplt128_f32(a, b) ::ext::cmplt128_f32(a, b)
#define _cmpgt128_f32(a, b) ::ext::cmpgt128_f32(a, b)
#define _cmple128_f32(a, b) ::ext::cmple128_f32(a, b)
#define _cmpge128_f32(a, b) ::ext::cmpge128_f32(a, b)
#define _recipl128_f32(a) ::ext::recipl128_f32(a)
#define _reciph128_f32(a) ::ext::reciph128_f32(a) 
#define _rsqrtl128_f32(a) ::ext::rsqrtl128_f32(a)
#define _rsqrth128_f32(a) ::ext::rsqrth128_f32(a)
#define _sqrtl128_f32(a) ::ext::sqrtl128_f32(a)
#define _sqrth128_f32(a) ::ext::sqrth128_f32(a) 

#define _dup128_s32(a) ::ext::dup128_s32(a)
#define _set128_s32(a, b) ::ext::set128_s32(a, b)
#define _add128_s32(a, b) ::ext::add128_s32(a, b)
#define _sub128_s32(a, b) ::ext::sub128_s32(a, b)
#define _mul128_s32(a, b) ::ext::mul128_s32(a, b)
#define _madd128_s32(a, b, c) ::ext::madd128_s32(a, b, c)
#define _neg128_s32(a) ::ext::neg128_s32(a)
#define _abs128_s32(a) ::ext::abs128_s32(a)
#define _max128_s32(a, b) ::ext::max128_s32(a, b)
#define _min128_s32(a, b) ::ext::min128_s32(a, b)
#define _clamp128_s32(a, min, max) _min128_s32(_max128_s32(a, min), max)
#define _cmpeq128_s32(a, b) ::ext::cmpeq128_s32(a, b)
#define _cmplt128_s32(a, b) ::ext::cmplt128_s32(a, b)
#define _cmpgt128_s32(a, b) ::ext::cmpgt128_s32(a, b)
#define _cmple128_s32(a, b) ::ext::cmple128_s32(a, b)
#define _cmpge128_s32(a, b) ::ext::cmpge128_s32(a, b)

#endif

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)

#define _padd64_f32(a, b) ::ext::padd64_f32(a, b)
#define _radd64_f32(a) ::ext::radd64_f32(a)
#define _rmax64_f32(a) ::ext::rmax64_f32(a)
#define _rmin64_f32(a) ::ext::rmin64_f32(a)
#define _round64_f32(a) ::ext::round64_f32(a) 
#define _floor64_f32(a) ::ext::floor64_f32(a)
#define _ceil64_f32(a) ::ext::ceil64_f32(a)

#define _padd64_s32(a, b) ::ext::padd64_s32(a, b)
#define _radd64_s32(a) ::ext::radd64_s32(a)
#define _rmax64_s32(a) ::ext::rmax64_s32(a)
#define _rmin64_s32(a) ::ext::rmin64_s32(a)

#define _padd128_f32(a, b) ::ext::padd128_f32(a, b)
#define _radd128_f32(a) ::ext::radd128_f32(a)
#define _rmax128_f32(a) ::ext::rmax128_f32(a)
#define _rmin128_f32(a) ::ext::rmin128_f32(a)
#define _round128_f32(a) ::ext::round128_f32(a) 
#define _floor128_f32(a) ::ext::floor128_f32(a)
#define _ceil128_f32(a) ::ext::ceil128_f32(a)

#define _padd128_s32(a, b) ::ext::padd128_s32(a, b)
#define _radd128_s32(a) ::ext::radd128_s32(a)
#define _rmax128_s32(a) ::ext::rmax128_s32(a)
#define _rmin128_s32(a) ::ext::rmin128_s32(a)

#endif

// skv_ext

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON)
    typedef float32x2_t skv64_f32;
    typedef int32x2_t skv64_s32; 
    typedef float32x4_t skv128_f32;
    typedef int32x4_t skv128_s32;
#elif KTM_SIMD_ENABLE(KTM_SIMD_SSE)
    typedef __m64 skv64_f32;
    typedef __m64 skv64_s32;
    typedef __m128 skv128_f32;
    #if KTM_SIMD_ENABLE(KTM_SIMD_SSE2)
       typedef __m128i skv128_s32; 
    #endif
#endif

// KTM_FUNC float radd128_f32(__m128 a) noexcept
// {
//     __m128 shuf = shuffle128_f32<3, 3, 1, 1>(a);
//     __m128 add = _mm_add_ps(a, shuf);
//     shuf = shuffle128_f32<3, 2, 3, 2>(add);
//     add = _mm_add_ss(add, shuf);
//     return _mm_cvtss_f32(add);
// }

// KTM_FUNC float rmax128_f32(__m128 a) noexcept
// {
//     __m128 shuf = shuffle128_f32<3, 3, 1, 1>(a);
//     __m128 max = _mm_max_ps(a, shuf);
//     shuf = shuffle128_f32<3, 2, 3, 2>(max);
//     max = _mm_max_ss(max, shuf);
//     return _mm_cvtss_f32(max);
// }

// KTM_FUNC float rmin128_f32(__m128 a) noexcept
// {
//     __m128 shuf = shuffle128_f32<3, 3, 1, 1>(a);
//     __m128 min = _mm_min_ps(a, shuf);
//     shuf = shuffle128_f32<3, 2, 3, 2>(min);
//     min = _mm_min_ss(min, shuf);
//     return _mm_cvtss_f32(min);
// }

// KTM_FUNC int radd128_s32(__m128i a) noexcept
// {
//     __m128i shuf = _mm_castps_si128(shuffle128_f32<3, 3, 1, 1>(_mm_castsi128_ps(a)));
//     __m128i add = _mm_add_epi32(a, shuf);
//     shuf = _mm_castps_si128(shuffle128_f32<3, 2, 3, 2>(_mm_castsi128_ps(add)));
//     add = _mm_add_epi32(add, shuf);
//     return _mm_cvtsi128_si32(add);
// }

// KTM_FUNC int rmax128_s32(__m128i a) noexcept
// {
// 	__m128i shuf = _mm_castps_si128(shuffle128_f32<3, 3, 1, 1>(_mm_castsi128_ps(a)));
//     __m128i max = _mm_max_epi32(a, shuf);
//     shuf = _mm_castps_si128(shuffle128_f32<3, 2, 3, 2>(_mm_castsi128_ps(max)));
//     max = _mm_max_epi32(max, shuf);
//     return _mm_cvtsi128_si32(max);
// }

// KTM_FUNC int rmin128_s32(__m128i a) noexcept
// {
// 	__m128i shuf = _mm_castps_si128(shuffle128_f32<3, 3, 1, 1>(_mm_castsi128_ps(a)));
//     __m128i min = _mm_min_epi32(a, shuf);
//     shuf = _mm_castps_si128(shuffle128_f32<3, 2, 3, 2>(_mm_castsi128_ps(min)));
//     min = _mm_min_epi32(min, shuf);
//     return _mm_cvtsi128_si32(min);
// }

#endif