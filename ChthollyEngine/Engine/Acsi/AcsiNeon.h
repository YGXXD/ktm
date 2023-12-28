#ifndef _ACSI_NEON_H_ 
#define _ACSI_NEON_H_

#include "SetupAcsi.h"
#include <cstddef>

#if defined(CHTHOLLY_SIMD_NEON)

#if defined(CHTHOLLY_COMPILER_CLANG)

#define neon_shuffle_s32(a, b, s1, s0) neon_shuffle_f32(a, b, s1, s0)
#define neon_shuffleq_s32(a, b, s3, s2, s1, s0) neon_shuffleq_f32(a, b, s3, s2, s1, s0)
#define neon_shuffle_f32(a, b, s1, s0) __builtin_shufflevector(a, b, s0, (s1) + 2)
#define neon_shuffleq_f32(a, b, s3, s2, s1, s0) __builtin_shufflevector(a, b, s0, s1, (s2) + 4, (s3) + 4)

#else

#define neon_shuffle_s32(a, b, s1, s0) vcopy_lane_s32(vmov_n_s32(vget_lane_s32(a, s0)), 1, b, s1)
#define neon_shuffleq_s32(a, b, s3, s2, s1, s0) vcopyq_laneq_s32(vcopyq_laneq_s32(vcopyq_laneq_s32(vmovq_n_s32(vgetq_lane_s32(a, s0)), 1, a, s1), 2, b, s2), 3, b, s3)
#define neon_shuffle_f32(a, b, s1, s0) vcopy_lane_f32(vmov_n_f32(vget_lane_f32(a, s0)), 1, b, s1)
#define neon_shuffleq_f32(a, b, s3, s2, s1, s0) vcopyq_laneq_f32(vcopyq_laneq_f32(vcopyq_laneq_f32(vmovq_n_f32(vgetq_lane_f32(a, s0)), 1, a, s1), 2, b, s2), 3, b, s3)

#endif

namespace neon
{
namespace ex 
{
CHTHOLLY_FUNC int andv_s32(int32x2_t x) noexcept
{
	return vget_lane_s32(x, 0) & vget_lane_s32(x, 1);
}

CHTHOLLY_FUNC int andvq_s32(int32x4_t x) noexcept
{
	return andv_s32(vand_s32(vget_low_s32(x), vget_high_s32(x)));
}

CHTHOLLY_FUNC int32x2_t clamp_s32(int32x2_t x, int32x2_t min, int32x2_t max) noexcept
{
	return vmin_s32(vmax_s32(x, min), max);
}

CHTHOLLY_FUNC int32x4_t clampq_s32(int32x4_t x, int32x4_t min, int32x4_t max) noexcept
{
	return vminq_s32(vmaxq_s32(x, min), max);
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x2_t add_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vadd_s32(arg, add_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x2_t add_s32_all<int32x2_t>(int32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x2_t mul_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmul_s32(arg, mul_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x2_t mul_s32_all<int32x2_t>(int32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x4_t addq_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vaddq_s32(arg, addq_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x4_t addq_s32_all<int32x4_t>(int32x4_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x4_t mulq_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmulq_s32(arg, mulq_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x4_t mulq_s32_all<int32x4_t>(int32x4_t arg) noexcept
{
	return arg;
}

CHTHOLLY_FUNC float andv_f32(float32x2_t x) noexcept
{
	const union { int i; float f; } ret = { andv_s32(vreinterpret_s32_f32(x)) };
	return ret.f;
}

CHTHOLLY_FUNC float andvq_f32(float32x4_t x) noexcept
{
	const union { int i; float f; } ret = { andvq_s32(vreinterpretq_s32_f32(x)) };
	return ret.f;
}

CHTHOLLY_FUNC float32x2_t clamp_f32(float32x2_t x, float32x2_t min, float32x2_t max) noexcept
{
	return vmin_f32(vmax_f32(x, min), max);
}

CHTHOLLY_FUNC float32x4_t clampq_f32(float32x4_t x, float32x4_t min, float32x4_t max) noexcept
{
	return vminq_f32(vmaxq_f32(x, min), max);
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x2_t add_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vadd_f32(arg, add_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x2_t add_f32_all<float32x2_t>(float32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x2_t mul_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmul_f32(arg, mul_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x2_t mul_f32_all<float32x2_t>(float32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x4_t addq_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vaddq_f32(arg, addq_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x4_t addq_f32_all<float32x4_t>(float32x4_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x4_t mulq_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmulq_f32(arg, mulq_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x4_t mulq_f32_all<float32x4_t>(float32x4_t arg) noexcept
{
	return arg;
}
}

namespace geo
{
CHTHOLLY_FUNC int32x2_t sv2_dot2(int32x2_t x, int32x2_t y) noexcept
{
	int32x2_t mul = vmul_s32(x, y);
	return vpadd_s32(mul, mul);
}

CHTHOLLY_FUNC int32x4_t sv4_dot4(int32x4_t x, int32x4_t y) noexcept
{
	int32x4_t mul = vmulq_s32(x, y);
    int32x4_t add_0 = vpaddq_s32(mul, mul);
    int32x4_t add_1 = vpaddq_s32(add_0, add_0);
	return add_1;
}

CHTHOLLY_FUNC int sv2_dot1(int32x2_t x, int32x2_t y) noexcept
{
	return vaddv_s32(vmul_s32(x, y));
}

template<size_t N>
CHTHOLLY_FUNC int sv4_dot1(int32x4_t x, int32x4_t y) noexcept;

template<>
CHTHOLLY_FUNC int sv4_dot1<3>(int32x4_t x, int32x4_t y) noexcept
{
	int32x4_t mul = vmulq_s32(x, y);
	return vaddvq_s32(vsetq_lane_s32(0, mul, 3));	
}

template<>
CHTHOLLY_FUNC int sv4_dot1<4>(int32x4_t x, int32x4_t y) noexcept
{
	return vaddvq_s32(vmulq_s32(x, y));	
}

CHTHOLLY_FUNC float32x2_t fv2_dot2(float32x2_t x, float32x2_t y) noexcept
{
	float32x2_t mul = vmul_f32(x, y);
	return vpadd_f32(mul, mul);
}

CHTHOLLY_FUNC float32x4_t fv4_dot4(float32x4_t x, float32x4_t y) noexcept
{
	float32x4_t mul = vmulq_f32(x, y);
    float32x4_t add_0 = vpaddq_f32(mul, mul);
    float32x4_t add_1 = vpaddq_f32(add_0, add_0);
	return add_1;
}

CHTHOLLY_FUNC float fv2_dot1(float32x2_t x, float32x2_t y) noexcept
{
	return vaddv_f32(vmul_f32(x, y));
}

template<size_t N>
CHTHOLLY_FUNC float fv4_dot1(float32x4_t x, float32x4_t y) noexcept;

template<>
CHTHOLLY_FUNC float fv4_dot1<3>(float32x4_t x, float32x4_t y) noexcept
{
	float32x4_t mul = vmulq_f32(x, y);
	return vaddvq_f32(vsetq_lane_f32(0.f, mul, 3));	
}

template<>
CHTHOLLY_FUNC float fv4_dot1<4>(float32x4_t x, float32x4_t y) noexcept
{
	return vaddvq_f32(vmulq_f32(x, y));	
}
}

namespace mt
{
CHTHOLLY_FUNC void fmt3_tp(float32x4_t out[3], const float32x4_t in[3]) noexcept
{
	float32x4_t tmp_0 = neon_shuffleq_f32(in[0], in[1], 1, 0, 1, 0);
	float32x4_t tmp_1 = neon_shuffleq_f32(in[0], in[1], 3, 2, 3, 2);

	out[0] = neon_shuffleq_f32(tmp_0, in[2], 3, 0, 2, 0);
	out[1] = neon_shuffleq_f32(tmp_0, in[2], 3, 1, 3, 1);
	out[2] = neon_shuffleq_f32(tmp_1, in[2], 3, 2, 2, 0);
}

CHTHOLLY_FUNC void fmt4_tp(float32x4_t out[4], const float32x4_t in[4]) noexcept
{
	int32x4_t tmp_0 = neon_shuffleq_s32(in[0], in[1], 1, 0, 1, 0);
	int32x4_t tmp_2 = neon_shuffleq_s32(in[0], in[1], 3, 2, 3, 2);
	int32x4_t tmp_1 = neon_shuffleq_s32(in[2], in[3], 1, 0, 1, 0);
	int32x4_t tmp_3 = neon_shuffleq_s32(in[2], in[3], 3, 2, 3, 2);

	out[0] = neon_shuffleq_s32(tmp_0, tmp_1, 2, 0, 2, 0);
	out[1] = neon_shuffleq_s32(tmp_0, tmp_1, 3, 1, 3, 1);
	out[2] = neon_shuffleq_s32(tmp_2, tmp_3, 2, 0, 2, 0);
	out[3] = neon_shuffleq_s32(tmp_2, tmp_3, 3, 1, 3, 1);
}
}

namespace qt
{
CHTHOLLY_FUNC float32x4_t fv3_mul_fq(float32x4_t v, float32x4_t q) noexcept
{
    float32x4_t q_opp = vnegq_f32(q);

    float32x4_t tmp_0 = neon_shuffleq_f32(q, q_opp, 2, 2, 3, 3);
    float32x4_t tmp_1 = neon_shuffleq_f32(q, q_opp, 1, 0, 1, 0); 

    float32x4_t mul_x = neon_shuffleq_f32(tmp_0, tmp_1, 2, 1, 3, 0); 
    float32x4_t mul_y = neon_shuffleq_f32(q, q_opp, 1, 0, 3, 2); 
    float32x4_t mul_z = neon_shuffleq_f32(tmp_1, tmp_0, 2, 1, 0, 3);

    float32x4_t add_0 = vmulq_f32(vdupq_laneq_f32(v, 0), mul_x); 
    float32x4_t add_1 = vmulq_f32(vdupq_laneq_f32(v, 1), mul_y); 
    float32x4_t add_2 = vmulq_f32(vdupq_laneq_f32(v, 2), mul_z); 

    return neon::ex::addq_f32_all(add_0, add_1, add_2); 
}

CHTHOLLY_FUNC float32x4_t fq_mul_fq(float32x4_t x, float32x4_t y) noexcept
{
    float32x4_t add_012 = fv3_mul_fq(x, y);
    float32x4_t add_3 = vmulq_f32(vdupq_laneq_f32(x, 3), y); 
    return vaddq_f32(add_012, add_3);
}
}
}

#endif

#endif