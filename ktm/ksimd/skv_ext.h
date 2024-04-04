#ifndef _KTM_SKV_EXT_H_
#define _KTM_SKV_EXT_H_

#include "arch_def.h"
#include "intrin_api.h"

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

namespace skv
{

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON)

KTM_FUNC skv64_f32 round_fv2(skv64_f32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
	return _round64_f32(a);
#else
	constexpr union { unsigned int i; float f; } mask1 { 0x80000000 };
	constexpr union { unsigned int i; float f; } mask2 { 0x4b000000 };
	skv64_f32 tmp = _and64_f32(a, _dup64_f32(mask1.f));
	tmp = _or64_f32(tmp, _dup64_f32(mask2.f));
    skv64_f32 ret = _sub64_f32(_add64_f32(a, tmp), tmp);
	return ret;
#endif
}

KTM_FUNC skv64_f32 floor_fv2(skv64_f32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
	return _floor64_f32(a);
#else
	constexpr union { unsigned int i; float f; } mask = { 0x3f800000 };
	skv64_f32 rnd = round_fv2(a);
	skv64_f32 tmp = _cmplt64_f32(a, rnd);
	tmp = _and64_f32(tmp, _dup64_f32(mask.f));
	skv64_f32 ret = _sub64_f32(rnd, tmp);
	return ret;
#endif
}

KTM_FUNC skv64_f32 ceil_fv2(skv64_f32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
	return _ceil64_f32(a);
#else
    constexpr union { unsigned int i; float f; } mask = { 0x3f800000 };
	skv64_f32 rnd = round_fv2(a);
	skv64_f32 tmp = _cmpgt64_f32(a, rnd);
	tmp = _and64_f32(tmp, _dup64_f32(mask.f));
	skv64_f32 ret = _add64_f32(rnd, tmp);
	return ret;
#endif
}

KTM_FUNC float radd_fv2(skv64_f32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
    skv64_f32 add = _padd64_f32(a, a);
#else
    skv64_f32 add = _add64_f32(a, _shuffo64_f32(a, 0, 1));
#endif
    return _cast64to32_f32(add);
}

KTM_FUNC int radd_sv2(skv64_s32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
    skv64_s32 add = _padd64_s32(a, a);
#else
    skv64_s32 add = _add64_s32(a, _cast64_s32_f32(_shuffo64_f32(_cast64_f32_s32(a), 0, 1)));
#endif
    union { float f; int i; } ret {_cast64to32_f32(_cast64_f32_s32(add))};
    return ret.i;
}

#endif

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE)

KTM_FUNC skv128_f32 round_fv4(skv128_f32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64 | KTM_SIMD_SSE4_1)
	return _round128_f32(a);
#else
	constexpr union { unsigned int i; float f; } mask1 { 0x80000000 };
	constexpr union { unsigned int i; float f; } mask2 { 0x4b000000 };
	skv128_f32 tmp = _and128_f32(a, _dup128_f32(mask1.f));
	tmp = _or128_f32(tmp, _dup128_f32(mask2.f));
    skv128_f32 ret = _sub128_f32(_add128_f32(a, tmp), tmp);
	return ret;
#endif
}

KTM_FUNC skv128_f32 floor_fv4(skv128_f32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64 | KTM_SIMD_SSE4_1)
	return _floor128_f32(a);
#else
	constexpr union { unsigned int i; float f; } mask = { 0x3f800000 };
	skv128_f32 rnd = round_fv4(a);
	skv128_f32 tmp = _cmplt128_f32(a, rnd);
	tmp = _and128_f32(tmp, _dup128_f32(mask.f));
	skv128_f32 ret = _sub128_f32(rnd, tmp);
	return ret;
#endif
}

KTM_FUNC skv128_f32 ceil_fv4(skv128_f32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64 | KTM_SIMD_SSE4_1)
	return _ceil128_f32(a);
#else
    constexpr union { unsigned int i; float f; } mask = { 0x3f800000 };
	skv128_f32 rnd = round_fv4(a);
	skv128_f32 tmp = _cmpgt128_f32(a, rnd);
	tmp = _and128_f32(tmp, _dup128_f32(mask.f));
	skv128_f32 ret = _add128_f32(rnd, tmp);
	return ret;
#endif
}

KTM_FUNC float radd_fv3(skv128_f32 a) noexcept
{
    skv128_f32 shuf = _shuffo128_f32(a, 1, 1, 1, 1);
    skv128_f32 add = _add128_f32(a, shuf);
    shuf = _shuffo128_f32(a, 2, 2, 2, 2);
    add = _add128_f32(add, shuf);
    return _cast128to32_f32(add);
}

KTM_FUNC float radd_fv4(skv128_f32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
    return _radd128_f32(a);
#elif KTM_SIMD_ENABLE(KTM_SIMD_SSE3)
    skv128_f32 add = _padd128_f32(a, a);
    add = _padd128_f32(add, add);
    return _cast128to32_f32(add);
#else
    skv128_f32 shuf = _shuffo128_f32(a, 3, 3, 1, 1);
    skv128_f32 add = _add128_f32(a, shuf);
    shuf = _shuffo128_f32(add, 3, 2, 3, 2);
    add = _add128_f32(add, shuf);
    return _cast128to32_f32(add);
#endif
}

KTM_FUNC float rmax_fv4(skv128_f32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
    return _rmax128_f32(a);
#else
    skv128_f32 shuf = _shuffo128_f32(a, 3, 3, 1, 1);
    skv128_f32 max = _max128_f32(a, shuf);
    shuf = _shuffo128_f32(max, 3, 2, 3, 2);
    max = _max128_f32(max, shuf);
    return _cast128to32_f32(max);
#endif
}

KTM_FUNC float rmin_fv4(skv128_f32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
    return _rmin128_f32(a);
#else
    skv128_f32 shuf = _shuffo128_f32(a, 3, 3, 1, 1);
    skv128_f32 min = _min128_f32(a, shuf);
    shuf = _shuffo128_f32(min, 3, 2, 3, 2);
    min = _min128_f32(min, shuf);
    return _cast128to32_f32(min);
#endif
}

#endif

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE2)

KTM_FUNC int radd_sv3(skv128_s32 a) noexcept
{
    skv128_s32 shuf = _cast128_f32_s32(_shuffo128_f32(_cast128_f32_s32(a), 1, 1, 1, 1));
    skv128_s32 add = _add128_s32(a, shuf);
    shuf = _cast128_f32_s32(_shuffo128_f32(_cast128_f32_s32(add), 2, 2, 2, 2));
    add = _add128_s32(add, shuf);
    union { float f; int i; } ret {_cast128to32_f32(_cast128_f32_s32(add))};
    return ret.i;
}

KTM_FUNC int radd_sv4(skv128_s32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
    return _radd128_s32(a);
#elif KTM_SIMD_ENABLE(KTM_SIMD_SSE3)
    skv128_s32 add = _padd128_s32(a, a);
    add = _padd128_s32(add, add);
    union { float f; int i; } ret {_cast128to32_f32(_cast128_f32_s32(add))};
    return ret.i;
#else
    skv128_s32 shuf = _cast128_f32_s32(_shuffo128_f32(_cast128_f32_s32(a), 3, 3, 1, 1));
    skv128_s32 add = _add128_s32(a, shuf);
    shuf = _cast128_f32_s32(_shuffo128_f32(_cast128_f32_s32(add), 3, 2, 3, 2));
    add = _add128_s32(add, shuf);
    union { float f; int i; } ret {_cast128to32_f32(_cast128_f32_s32(add))};
    return ret.i;
#endif
}

#endif

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE4_1)

KTM_FUNC int rmax_sv4(skv128_s32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
    return _rmax128_s32(a);
#else
    skv128_s32 shuf = _cast128_f32_s32(_shuffo128_f32(_cast128_f32_s32(a), 3, 3, 1, 1));
    skv128_s32 max = _max128_s32(a, shuf);
    shuf = _cast128_f32_s32(_shuffo128_f32(_cast128_f32_s32(max), 3, 2, 3, 2));
    max = _max128_s32(max, shuf);
    union { float f; int i; } ret {_cast128to32_f32(_cast128_f32_s32(max))};
    return ret.i;
#endif
}

KTM_FUNC int rmin_sv4(skv128_s32 a) noexcept
{
#if KTM_SIMD_ENABLE(KTM_SIMD_NEON64)
    return _rmin128_s32(a);
#else
    skv128_s32 shuf = _cast128_f32_s32(_shuffo128_f32(_cast128_f32_s32(a), 3, 3, 1, 1));
    skv128_s32 min = _min128_s32(a, shuf);
    shuf = _cast128_f32_s32(_shuffo128_f32(_cast128_f32_s32(min), 3, 2, 3, 2));
    min = _min128_s32(min, shuf);
    union { float f; int i; } ret {_cast128to32_f32(_cast128_f32_s32(min))};
    return ret.i;
#endif
}

#endif

}

#endif