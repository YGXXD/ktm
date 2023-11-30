#ifndef _NEON_EX_H_
#define _NEON_EX_H_

#include "SetupAcsi.h"

#if defined(CHTHOLLY_SIMD_NEON)

#if defined(CHTHOLLY_COMPILER_CLANG)

#define acsi_vshuffle_f32(a, b, s2, s1) __builtin_shufflevector(a, b, s1, (s2) + 2)
#define acsi_vshuffle_s32(a, b, s2, s1) acsi_vshuffle_f32(a, b, s2, s1)
#define acsi_vshuffleq_f32(a, b, s4, s3, s2, s1) __builtin_shufflevector(a, b, s1, s2, (s3) + 4, (s4) + 4)
#define acsi_vshuffleq_s32(a, b, s4, s3, s2, s1) acsi_vshuffleq_f32(a, b, s4, s3, s2, s1)

#elif defined(CHTHOLLY_COMPILER_MSVC) || defined(CHTHOLLY_COMPILER_GCC) 

#define acsi_vshuffle_f32(a, b, s2, s1) vset_lane_f32(vget_lane_f32(b, s2), vmov_n_f32(vget_lane_f32(a, s1)), 1)
#define acsi_vshuffle_s32(a, b, s2, s1) vset_lane_s32(vget_lane_s32(b, s2), vmov_n_s32(vget_lane_s32(a, s1)), 1)
#define acsi_vshuffleq_f32(a, b, s4, s3, s2, s1) vsetq_lane_f32(vgetq_lane_f32(b, s4), vsetq_lane_f32(vgetq_lane_f32(b, s3), vsetq_lane_f32(vgetq_lane_f32(a, s2), vmovq_n_f32(vgetq_lane_f32(a, s1)), 1), 2), 3)
#define acsi_vshuffleq_s32(a, b, s4, s3, s2, s1) vsetq_lane_s32(vgetq_lane_s32(b, s4), vsetq_lane_s32(vgetq_lane_s32(b, s3), vsetq_lane_s32(vgetq_lane_s32(a, s2), vmovq_n_s32(vgetq_lane_s32(a, s1)), 1), 2), 3)

#endif

CHTHOLLY_FUNC float32x2_t acsi_vclamp_f32(float32x2_t x, float32x2_t min, float32x2_t max) noexcept
{
	return vmin_f32(vmax_f32(x, min), max);
}

CHTHOLLY_FUNC float32x4_t acsi_vclampq_f32(float32x4_t x, float32x4_t min, float32x4_t max) noexcept
{
	return vminq_f32(vmaxq_f32(x, min), max);
}

CHTHOLLY_FUNC int32x2_t acsi_vclamp_s32(int32x2_t x, int32x2_t min, int32x2_t max) noexcept
{
	return vmin_s32(vmax_s32(x, min), max);
}

CHTHOLLY_FUNC int32x4_t acsi_vclampq_s32(int32x4_t x, int32x4_t min, int32x4_t max) noexcept
{
	return vminq_s32(vmaxq_s32(x, min), max);
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x2_t acsi_vadd_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vadd_f32(arg, acsi_vadd_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x2_t acsi_vadd_f32_all<float32x2_t>(float32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x2_t acsi_vmul_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmul_f32(arg, acsi_vmul_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x2_t acsi_vmul_f32_all<float32x2_t>(float32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x4_t acsi_vaddq_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vaddq_f32(arg, acsi_vaddq_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x4_t acsi_vaddq_f32_all<float32x4_t>(float32x4_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x4_t acsi_vmulq_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmulq_f32(arg, acsi_vmulq_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x4_t acsi_vmulq_f32_all<float32x4_t>(float32x4_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x2_t acsi_vadd_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vadd_s32(arg, acsi_vadd_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x2_t acsi_vadd_s32_all<int32x2_t>(int32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x2_t acsi_vmul_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmul_s32(arg, acsi_vmul_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x2_t acsi_vmul_s32_all<int32x2_t>(int32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x4_t acsi_vaddq_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vaddq_s32(arg, acsi_vaddq_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x4_t acsi_vaddq_s32_all<int32x4_t>(int32x4_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x4_t acsi_vmulq_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmulq_s32(arg, acsi_vmulq_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x4_t acsi_vmulq_s32_all<int32x4_t>(int32x4_t arg) noexcept
{
	return arg;
}

#endif

#endif