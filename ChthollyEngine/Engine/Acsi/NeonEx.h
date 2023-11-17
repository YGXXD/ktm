#ifndef _NEON_EX_H_
#define _NEON_EX_H_

#include "SetupAcsi.h"

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

#endif

#endif