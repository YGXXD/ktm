#ifndef _KTM_ARM_H_ 
#define _KTM_ARM_H_

#include "intrin.h"
#include <cstddef>

#if defined(KTM_SIMD_ARM)

#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG

#define neon_copy_lane_f32(dst, dst_lane, src, src_lane) vcopy_lane_f32(dst, dst_lane, src, src_lane)
#define neon_copy_laneq_f32(dst, dst_lane, src, src_lane) vcopy_laneq_f32(dst, dst_lane, src, src_lane)
#define neon_copyq_lane_f32(dst, dst_lane, src, src_lane) vcopyq_lane_f32(dst, dst_lane, src, src_lane)
#define neon_copyq_laneq_f32(dst, dst_lane, src, src_lane) vcopyq_laneq_f32(dst, dst_lane, src, src_lane)
#define neon_copy_lane_s32(dst, dst_lane, src, src_lane) vcopy_lane_s32(dst, dst_lane, src, src_lane)
#define neon_copy_laneq_s32(dst, dst_lane, src, src_lane) vcopy_laneq_s32(dst, dst_lane, src, src_lane)
#define neon_copyq_lane_s32(dst, dst_lane, src, src_lane) vcopyq_lane_s32(dst, dst_lane, src, src_lane)
#define neon_copyq_laneq_s32(dst, dst_lane, src, src_lane) vcopyq_laneq_s32(dst, dst_lane, src, src_lane)
#define neon_dup_lane_f32(a, lane) vdup_lane_f32(a, lane)
#define neon_dupq_lane_f32(a, lane) vdupq_lane_f32(a, lane)
#define neon_dup_laneq_f32(a, lane) vdup_laneq_f32(a, lane)
#define neon_dupq_laneq_f32(a, lane) vdupq_laneq_f32(a, lane)
#define neon_dup_lane_s32(a, lane) vdup_lane_s32(a, lane)
#define neon_dupq_lane_s32(a, lane) vdupq_lane_s32(a, lane)
#define neon_dup_laneq_s32(a, lane) vdup_laneq_s32(a, lane)
#define neon_dupq_laneq_s32(a, lane) vdupq_laneq_s32(a, lane)

#else

#define neon_copy_lane_f32(dst, dst_lane, src, src_lane) vset_lane_f32(vget_lane_f32(src, src_lane), dst, dst_lane)
#define neon_copy_laneq_f32(dst, dst_lane, src, src_lane) vset_lane_f32(vgetq_lane_f32(src, src_lane), dst, dst_lane)
#define neon_copyq_lane_f32(dst, dst_lane, src, src_lane) vsetq_lane_f32(vget_lane_f32(src, src_lane), dst, dst_lane)
#define neon_copyq_laneq_f32(dst, dst_lane, src, src_lane) vsetq_lane_f32(vgetq_lane_f32(src, src_lane), dst, dst_lane)
#define neon_copy_lane_s32(dst, dst_lane, src, src_lane) vset_lane_s32(vget_lane_s32(src, src_lane), dst, dst_lane)
#define neon_copy_laneq_s32(dst, dst_lane, src, src_lane) vset_lane_s32(vgetq_lane_s32(src, src_lane), dst, dst_lane)
#define neon_copyq_lane_s32(dst, dst_lane, src, src_lane) vsetq_lane_s32(vget_lane_s32(src, src_lane), dst, dst_lane)
#define neon_copyq_laneq_s32(dst, dst_lane, src, src_lane) vsetq_lane_s32(vgetq_lane_s32(src, src_lane), dst, dst_lane)
#define neon_dup_lane_f32(a, lane) vdup_n_f32(vget_lane_f32(a, lane))
#define neon_dupq_lane_f32(a, lane) vdupq_n_f32(vget_lane_f32(a, lane))
#define neon_dup_laneq_f32(a, lane) vdup_n_f32(vgetq_lane_f32(a, lane))
#define neon_dupq_laneq_f32(a, lane) vdupq_n_f32(vgetq_lane_f32(a, lane))
#define neon_dup_lane_s32(a, lane) vdup_n_s32(vget_lane_s32(a, lane))
#define neon_dupq_lane_s32(a, lane) vdupq_n_s32(vget_lane_s32(a, lane))
#define neon_dup_laneq_s32(a, lane) vdup_n_s32(vgetq_lane_s32(a, lane))
#define neon_dupq_laneq_s32(a, lane) vdupq_n_s32(vgetq_lane_s32(a, lane))

#endif

#if defined(KTM_COMPILER_CLANG) & 0

#if defined(__ORDER_LITTLE_ENDIAN__)

#define neon_shuffle_s32(a, b, s1, s0) neon_shuffle_f32(a, b, s1, s0)
#define neon_shuffleq_s32(a, b, s3, s2, s1, s0) neon_shuffleq_f32(a, b, s3, s2, s1, s0)
#define neon_shuffle_f32(a, b, s1, s0) __builtin_shufflevector(a, b, s0, (s1) + 2)
#define neon_shuffleq_f32(a, b, s3, s2, s1, s0) __builtin_shufflevector(a, b, s0, s1, (s2) + 4, (s3) + 4)

#else

#define neon_shuffle_s32(a, b, s1, s0) neon_shuffle_f32(a, b, s1, s0)
#define neon_shuffleq_s32(a, b, s3, s2, s1, s0) neon_shuffleq_f32(a, b, s3, s2, s1, s0)
#define neon_shuffle_f32(a, b, s1, s0) __builtin_shufflevector(b, a, 1 - (s1), 3 - (s0))
#define neon_shuffleq_f32(a, b, s3, s2, s1, s0) __builtin_shufflevector(b, a, 3 - (s3), 3 - (s2), 7 - (s1), 7 - (s0))

#endif

#elif defined(KTM_COMPILER_GCC)

#if defined(__ORDER_LITTLE_ENDIAN__)

#define neon_shuffle_s32(a, b, s1, s0) neon_shuffle_f32(a, b, s1, s0)
#define neon_shuffleq_s32(a, b, s3, s2, s1, s0) neon_shuffleq_f32(a, b, s3, s2, s1, s0)
#define neon_shuffle_f32(a, b, s1, s0) __builtin_shuffle(a, b, uint32x2_t{ s0, (s1) + 2 })
#define neon_shuffleq_f32(a, b, s3, s2, s1, s0) __builtin_shuffle(a, b, uint32x4_t{ s0, s1, (s2) + 4, (s3) + 4 })

#else

#define neon_shuffle_s32(a, b, s1, s0) neon_shuffle_f32(a, b, s1, s0)
#define neon_shuffleq_s32(a, b, s3, s2, s1, s0) neon_shuffleq_f32(a, b, s3, s2, s1, s0)
#define neon_shuffle_f32(a, b, s1, s0) __builtin_shuffle(b, a, uint32x2_t{ 1 - (s1), 3 - (s0) })
#define neon_shuffleq_f32(a, b, s3, s2, s1, s0) __builtin_shuffle(b, a, uint32x4_t{ 3 - (s3), 3 - (s2), 7 - (s1), 7 - (s0) })

#endif

#else 

#define neon_shuffle_s32(a, b, s1, s0) neon_copy_lane_s32(vmov_n_s32(vget_lane_s32(a, s0)), 1, b, s1)
#define neon_shuffleq_s32(a, b, s3, s2, s1, s0) neon_copyq_laneq_s32(neon_copyq_laneq_s32(neon_copyq_laneq_s32(vmovq_n_s32(vgetq_lane_s32(a, s0)), 1, a, s1), 2, b, s2), 3, b, s3)
#define neon_shuffle_f32(a, b, s1, s0) neon_copy_lane_f32(vmov_n_f32(vget_lane_f32(a, s0)), 1, b, s1)
#define neon_shuffleq_f32(a, b, s3, s2, s1, s0) neon_copyq_laneq_f32(neon_copyq_laneq_f32(neon_copyq_laneq_f32(vmovq_n_f32(vgetq_lane_f32(a, s0)), 1, a, s1), 2, b, s2), 3, b, s3)

#endif

namespace arm
{
namespace ext 
{

KTM_FUNC int32x2_t clamp_s32(int32x2_t x, int32x2_t min, int32x2_t max) noexcept
{
	return vmin_s32(vmax_s32(x, min), max);
}

KTM_FUNC int32x4_t clampq_s32(int32x4_t x, int32x4_t min, int32x4_t max) noexcept
{
	return vminq_s32(vmaxq_s32(x, min), max);
}

KTM_FUNC float32x2_t min_f32(float32x2_t x, float32x2_t y) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vminnm_f32(x, y);
#else
	return vmin_f32(x, y);
#endif
}

KTM_FUNC float32x4_t minq_f32(float32x4_t x, float32x4_t y) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vminnmq_f32(x, y);
#else
	return vminq_f32(x, y);
#endif
}

KTM_FUNC float32x2_t max_f32(float32x2_t x, float32x2_t y) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vmaxnm_f32(x, y);
#else
	return vmax_f32(x, y);
#endif
}

KTM_FUNC float32x4_t maxq_f32(float32x4_t x, float32x4_t y) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vmaxnmq_f32(x, y);
#else
	return vmaxq_f32(x, y);
#endif
}

KTM_FUNC float32x2_t clamp_f32(float32x2_t x, float32x2_t min, float32x2_t max) noexcept
{
	return min_f32(max_f32(x, min), max);
}

KTM_FUNC float32x4_t clampq_f32(float32x4_t x, float32x4_t min, float32x4_t max) noexcept
{
	return minq_f32(maxq_f32(x, min), max);
}

KTM_FUNC float32x2_t fast_rsqrt_f32(float32x2_t x) noexcept
{
	return vrsqrte_f32(x);
}

KTM_FUNC float32x4_t fast_rsqrtq_f32(float32x4_t x) noexcept
{
  	return vrsqrteq_f32(x);
}

KTM_FUNC float32x2_t rsqrt_f32(float32x2_t x) noexcept
{
	float32x2_t r = fast_rsqrt_f32(x);
	r = vmul_f32(r, vrsqrts_f32(x, vmul_f32(r,r)));
	r = vmul_f32(r, vrsqrts_f32(x, vmul_f32(r,r)));
	return r;
}

KTM_FUNC float32x4_t rsqrtq_f32(float32x4_t x) noexcept
{
	float32x4_t r = fast_rsqrtq_f32(x);
	r = vmulq_f32(r, vrsqrtsq_f32(x, vmulq_f32(r,r)));
	r = vmulq_f32(r, vrsqrtsq_f32(x, vmulq_f32(r,r)));
	return r;
}

KTM_FUNC float32x2_t fast_recip_f32(float32x2_t x) noexcept
{
  	return vrecpe_f32(x);
}

KTM_FUNC float32x4_t fast_recipq_f32(float32x4_t x) noexcept
{
  	return vrecpeq_f32(x);
}

KTM_FUNC float32x2_t recip_f32(float32x2_t x) noexcept
{
	float32x2_t r = fast_recip_f32(x);
	r = vmul_f32(r, vrecps_f32(x, r));
	r = vmul_f32(r, vrecps_f32(x, r));
  	return r;
}

KTM_FUNC float32x4_t recipq_f32(float32x4_t x) noexcept
{
	float32x4_t r = fast_recipq_f32(x);
	r = vmulq_f32(r, vrecpsq_f32(x, r));
	r = vmulq_f32(r, vrecpsq_f32(x, r));
	return r;
}

KTM_FUNC float32x2_t round_f32(float32x2_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vrndi_f32(x);
#else
	uint32x2_t tmp = vand_u32(vreinterpret_u32_f32(x), vdup_n_u32(0x80000000));
	tmp = vorr_u32(tmp, vdup_n_u32(0x4b000000));
	float32x2_t f_tmp = vreinterpret_f32_u32(tmp);
    float32x2_t ret = vsub_f32(vadd_f32(x, f_tmp), f_tmp);
	return ret;
#endif
}

KTM_FUNC float32x4_t roundq_f32(float32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vrndiq_f32(x);
#else
	uint32x4_t tmp = vandq_u32(vreinterpretq_u32_f32(x), vdupq_n_u32(0x80000000));
	tmp = vorrq_u32(tmp, vdupq_n_u32(0x4b000000));
	float32x4_t f_tmp = vreinterpretq_f32_u32(tmp);
    float32x4_t ret = vsubq_f32(vaddq_f32(x, f_tmp), f_tmp);
	return ret;
#endif
}

KTM_FUNC float32x2_t floor_f32(float32x2_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vrndm_f32(x);
#else
	float32x2_t rnd = round_f32(x);
	uint32x2_t tmp = vclt_f32(x, rnd);
	tmp = vand_u32(tmp, vdup_n_u32(0x3f800000));
	float32x2_t ret = vsub_f32(rnd, vreinterpret_f32_u32(tmp));
	return ret;
#endif
}

KTM_FUNC float32x4_t floorq_f32(float32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vrndmq_f32(x);
#else
	float32x4_t rnd = roundq_f32(x);
	uint32x4_t tmp = vcltq_f32(x, rnd);
	tmp = vandq_u32(tmp, vdupq_n_u32(0x3f800000));
	float32x4_t ret = vsubq_f32(rnd, vreinterpretq_f32_u32(tmp));
	return ret;
#endif
}

KTM_FUNC float32x2_t ceil_f32(float32x2_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vrndp_f32(x);
#else
	float32x2_t rnd = round_f32(x);
	uint32x2_t tmp = vcgt_f32(x, rnd);
	tmp = vand_u32(tmp, vdup_n_u32(0x3f800000));
	float32x2_t ret = vadd_f32(rnd, vreinterpret_f32_u32(tmp));
	return ret;
#endif
}

KTM_FUNC float32x4_t ceilq_f32(float32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vrndpq_f32(x);
#else
	float32x4_t rnd = roundq_f32(x);
	uint32x4_t tmp = vcgtq_f32(x, rnd);
	tmp = vandq_u32(tmp, vdupq_n_u32(0x3f800000));
	float32x4_t ret = vaddq_f32(rnd, vreinterpretq_f32_u32(tmp));
	return ret;
#endif
}

KTM_FUNC float32x2_t div_f32(float32x2_t x, float32x2_t y) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vdiv_f32(x, y);
#else
	return vmul_f32(x, recip_f32(y));
#endif
}

KTM_FUNC float32x4_t divq_f32(float32x4_t x, float32x4_t y) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vdivq_f32(x, y);
#else
	return vmulq_f32(x, recipq_f32(y));	
#endif	
}

KTM_FUNC float32x2_t fma_f32(float32x2_t a, float32x2_t x, float32x2_t y) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vfma_f32(a, x, y);
#else
  	return vmla_f32(a, x, y);
#endif
}

KTM_FUNC float32x4_t fmaq_f32(float32x4_t a, float32x4_t x, float32x4_t y) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vfmaq_f32(a, x, y);
#else
  	return vmlaq_f32(a, x, y);
#endif
}

}

namespace rdc
{

KTM_FUNC int sv2_radd(int32x2_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vaddv_s32(x);
#else
	int32x2_t r = vadd_s32(x, vrev64_s32(x));
	return vget_lane_s32(r, 0);
#endif
}

KTM_FUNC int sv3_radd(int32x4_t x)noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	int32x4_t ret = vaddq_s32(vdupq_laneq_s32(x, 1), x);
	ret = vaddq_s32(vdupq_laneq_s32(x, 2), ret);	
#else
	int32x4_t ret = vaddq_s32(vmovq_n_s32(vgetq_lane_s32(x, 1)), x);
	ret = vaddq_s32(vmovq_n_s32(vgetq_lane_s32(x, 2)), ret);
#endif
	return vgetq_lane_s32(ret, 0); 
}

KTM_FUNC int sv4_radd(int32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vaddvq_s32(x);
#else
	int32x4_t r = vaddq_s32(x, vrev64q_s32(x));
  	r = vaddq_s32(r, vextq_s32(r, r, 2));
  	return vgetq_lane_s32(r, 0);
#endif
}

KTM_FUNC int sv2_rmin(int32x2_t x) noexcept
{	
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vminv_s32(x);
#else
  	int32x2_t r = vpmin_s32(x, x);
  	return vget_lane_s32(r, 0);
#endif
}

KTM_FUNC int sv3_rmin(int32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	int32x4_t ret = vminq_s32(vdupq_laneq_s32(x, 1), x);
	ret = vminq_s32(vdupq_laneq_s32(x, 2), ret); 
#else
	int32x4_t ret = vminq_s32(vmovq_n_s32(vgetq_lane_s32(x, 1)), x);
	ret = vminq_s32(vmovq_n_s32(vgetq_lane_s32(x, 2)), ret);
#endif
	return vgetq_lane_s32(ret, 0);
}

KTM_FUNC int sv4_rmin(int32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vminvq_s32(x);
#else
  	int32x2_t r = vpmin_s32(vget_low_s32(x), vget_high_s32(x));
  	r = vpmin_s32(r, r);
  	return vget_lane_s32(r, 0);
#endif
}

KTM_FUNC int sv2_rmax(int32x2_t x) noexcept
{	
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vmaxv_s32(x);
#else
  	int32x2_t r = vpmax_s32(x, x);
  	return vget_lane_s32(r, 0);
#endif
}

KTM_FUNC int sv3_rmax(int32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	int32x4_t ret = vmaxq_s32(vdupq_laneq_s32(x, 1), x);
	ret = vmaxq_s32(vdupq_laneq_s32(x, 2), ret); 
#else
	int32x4_t ret = vmaxq_s32(vmovq_n_s32(vgetq_lane_s32(x, 1)), x);
	ret = vmaxq_s32(vmovq_n_s32(vgetq_lane_s32(x, 2)), ret);
#endif
	return vgetq_lane_s32(ret, 0);
}

KTM_FUNC int sv4_rmax(int32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vmaxvq_s32(x);
#else
  	int32x2_t r = vpmax_s32(vget_low_s32(x), vget_high_s32(x));
  	r = vpmax_s32(r, r);
  	return vget_lane_s32(r, 0);
#endif
}

KTM_FUNC float fv2_radd(float32x2_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vaddv_f32(x);
#else
	float32x2_t r = vadd_f32(x, vrev64_f32(x));
	return vget_lane_f32(r, 0);
#endif
}

KTM_FUNC float fv3_radd(float32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	float32x4_t ret = vaddq_f32(vdupq_laneq_f32(x, 1), x);
	ret = vaddq_f32(vdupq_laneq_f32(x, 2), ret); 
#else
	float32x4_t ret = vaddq_f32(vmovq_n_f32(vgetq_lane_f32(x, 1)), x);
	ret = vaddq_f32(vmovq_n_f32(vgetq_lane_f32(x, 2)), ret); 
#endif
	return vgetq_lane_f32(ret, 0);
}

KTM_FUNC float fv4_radd(float32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vaddvq_f32(x);
#else
	float32x4_t r = vaddq_f32(x, vrev64q_f32(x));
  	r = vaddq_f32(r, vextq_f32(r, r, 2));
  	return vgetq_lane_f32(r, 0);
#endif
}

KTM_FUNC float fv2_rmin(float32x2_t x) noexcept
{	
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vminv_f32(x);
#else
  	float32x2_t r = vpmin_f32(x, x);
  	return vget_lane_f32(r, 0);
#endif
}

KTM_FUNC float fv3_rmin(float32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG	
	float32x4_t ret = vminnmq_f32(vdupq_laneq_f32(x, 1), x);
	ret = vminnmq_f32(vdupq_laneq_f32(x, 2), ret); 
#else
	float32x4_t ret = vminq_f32(vmovq_n_f32(vgetq_lane_f32(x, 1)), x);
	ret = vminq_f32(vmovq_n_f32(vgetq_lane_f32(x, 2)), ret); 
#endif
	return vgetq_lane_f32(ret, 0);
}

KTM_FUNC float fv4_rmin(float32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vminvq_f32(x);
#else
  	float32x2_t r = vpmin_f32(vget_low_f32(x), vget_high_f32(x));
  	r = vpmin_f32(r, r);
  	return vget_lane_f32(r, 0);
#endif
}

KTM_FUNC float fv2_rmax(float32x2_t x) noexcept
{	
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vmaxv_f32(x);
#else
  	float32x2_t r = vpmax_f32(x, x);
  	return vget_lane_f32(r, 0);
#endif
}

KTM_FUNC float fv3_rmax(float32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	float32x4_t ret = vmaxnmq_f32(vdupq_laneq_f32(x, 1), x);
	ret = vmaxnmq_f32(vdupq_laneq_f32(x, 2), ret); 
#else
	float32x4_t ret = vmaxq_f32(vmovq_n_f32(vgetq_lane_f32(x, 1)), x);
	ret = vmaxq_f32(vmovq_n_f32(vgetq_lane_f32(x, 2)), ret); 
#endif
	return vgetq_lane_f32(ret, 0);
}

KTM_FUNC float fv4_rmax(float32x4_t x) noexcept
{
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vmaxvq_f32(x);
#else
  	float32x2_t r = vpmax_f32(vget_low_f32(x), vget_high_f32(x));
  	r = vpmax_f32(r, r);
  	return vget_lane_f32(r, 0);
#endif
}

}

namespace geo
{

KTM_FUNC float32x2_t fv2_dot(float32x2_t x, float32x2_t y) noexcept
{
	float32x2_t mul = vmul_f32(x, y);
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	return vpadd_f32(mul, mul);
#else
	return vadd_f32(mul, vrev64_f32(mul));
#endif
}

KTM_FUNC float32x4_t fv3_dot(float32x4_t x, float32x4_t y) noexcept
{
	float32x4_t mul = vmulq_f32(x, y);
	float32x4_t add_0 = vaddq_f32(neon_dupq_laneq_f32(mul, 0), neon_dupq_laneq_f32(mul, 1));
	float32x4_t add_1 = vaddq_f32(add_0, neon_dupq_laneq_f32(mul, 2));
	return add_1;
}

KTM_FUNC float32x4_t fv4_dot(float32x4_t x, float32x4_t y) noexcept
{
	float32x4_t mul = vmulq_f32(x, y);   
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	float32x4_t add_0 = vpaddq_f32(mul, mul);
    float32x4_t add_1 = vpaddq_f32(add_0, add_0);
#else
	float32x4_t add_0 = vaddq_f32(mul, vrev64q_f32(mul));
  	float32x4_t add_1 = vaddq_f32(add_0, vextq_f32(add_0, add_0, 2));
#endif
	return add_1;
}

KTM_FUNC float32x2_t fv2_dot1(float32x2_t x, float32x2_t y) noexcept
{
	return fv2_dot(x, y);
}

KTM_FUNC float32x4_t fv3_dot1(float32x4_t x, float32x4_t y) noexcept
{
	float32x4_t mul = vmulq_f32(x, y);
#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG
	float32x4_t ret = vaddq_f32(vdupq_laneq_f32(mul, 1), mul);
	ret = vaddq_f32(vdupq_laneq_f32(mul, 2), ret); 
#else
	float32x4_t ret = vaddq_f32(vmovq_n_f32(vgetq_lane_f32(mul, 1)), mul);
	ret = vaddq_f32(vmovq_n_f32(vgetq_lane_f32(mul, 2)), ret); 
#endif
	return ret;
}

KTM_FUNC float32x4_t fv4_dot1(float32x4_t x, float32x4_t y) noexcept
{
	return fv4_dot(x, y);
}

KTM_FUNC float32x2_t fv2_fast_length1(float32x2_t x) noexcept
{
	float32x2_t dot = fv2_dot1(x, x);
    return vrecpe_f32(vrsqrte_f32(dot));;
}

KTM_FUNC float32x4_t fv3_fast_length1(float32x4_t x) noexcept
{
	float32x4_t dot = fv3_dot1(x, x);
    return vrecpeq_f32(vrsqrteq_f32(dot));;
}

KTM_FUNC float32x4_t fv4_fast_length1(float32x4_t x) noexcept
{
	float32x4_t dot = fv4_dot1(x, x);
    return vrecpeq_f32(vrsqrteq_f32(dot));
}

#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG

KTM_FUNC float32x2_t fv2_length1(float32x2_t x) noexcept
{
	float32x2_t dot = fv2_dot1(x, x);
    return vsqrt_f32(dot);;
}

KTM_FUNC float32x4_t fv3_length1(float32x4_t x) noexcept
{
	float32x4_t dot = fv3_dot1(x, x);
    return vsqrtq_f32(dot);
}

KTM_FUNC float32x4_t fv4_length1(float32x4_t x) noexcept
{
	float32x4_t dot = fv4_dot1(x, x);
    return vsqrtq_f32(dot);
}

#endif

}

namespace mt
{

KTM_FUNC void fmt2_tp(float32x2_t out[2], const float32x2_t in[2]) noexcept
{
	float32x4_t tmp = vcombine_f32(in[0], in[1]);
	tmp = neon_shuffleq_f32(tmp, tmp, 3, 1, 2, 0);
	out[0] = vget_low_f32(tmp);
	out[1] = vget_high_f32(tmp);
}

KTM_FUNC void fmt3_tp(float32x4_t out[3], const float32x4_t in[3]) noexcept
{
	float32x4_t tmp_0 = neon_shuffleq_f32(in[0], in[1], 1, 0, 1, 0);
	float32x4_t tmp_1 = neon_shuffleq_f32(in[0], in[1], 3, 2, 3, 2);

	out[0] = neon_shuffleq_f32(tmp_0, in[2], 3, 0, 2, 0);
	out[1] = neon_shuffleq_f32(tmp_0, in[2], 3, 1, 3, 1);
	out[2] = neon_shuffleq_f32(tmp_1, in[2], 3, 2, 2, 0);
}

KTM_FUNC void fmt4_tp(float32x4_t out[4], const float32x4_t in[4]) noexcept
{
	float32x4_t tmp_0 = neon_shuffleq_f32(in[0], in[1], 1, 0, 1, 0);
	float32x4_t tmp_2 = neon_shuffleq_f32(in[0], in[1], 3, 2, 3, 2);
	float32x4_t tmp_1 = neon_shuffleq_f32(in[2], in[3], 1, 0, 1, 0);
	float32x4_t tmp_3 = neon_shuffleq_f32(in[2], in[3], 3, 2, 3, 2);

	out[0] = neon_shuffleq_f32(tmp_0, tmp_1, 2, 0, 2, 0);
	out[1] = neon_shuffleq_f32(tmp_0, tmp_1, 3, 1, 3, 1);
	out[2] = neon_shuffleq_f32(tmp_2, tmp_3, 2, 0, 2, 0);
	out[3] = neon_shuffleq_f32(tmp_2, tmp_3, 3, 1, 3, 1);
}
}

namespace qt
{

KTM_FUNC float32x4_t fv3_mul_fq(float32x4_t v, float32x4_t q) noexcept
{
    float32x4_t q_opp = vnegq_f32(q);

    float32x4_t tmp_0 = neon_shuffleq_f32(q, q_opp, 2, 2, 3, 3);
    float32x4_t tmp_1 = neon_shuffleq_f32(q, q_opp, 1, 0, 1, 0); 

    float32x4_t mul_x = neon_shuffleq_f32(tmp_0, tmp_1, 2, 1, 3, 0); 
    float32x4_t mul_y = neon_shuffleq_f32(q, q_opp, 1, 0, 3, 2); 
    float32x4_t mul_z = neon_shuffleq_f32(tmp_1, tmp_0, 2, 1, 0, 3);

    float32x4_t add_0 = vmulq_f32(neon_dupq_laneq_f32(v, 0), mul_x); 
    float32x4_t add_1 = vmulq_f32(neon_dupq_laneq_f32(v, 1), mul_y); 
    float32x4_t add_2 = vmulq_f32(neon_dupq_laneq_f32(v, 2), mul_z); 

    return vaddq_f32(add_0, vaddq_f32(add_1, add_2)); 
}

KTM_FUNC float32x4_t fq_mul_fq(float32x4_t x, float32x4_t y) noexcept
{
    float32x4_t add_012 = fv3_mul_fq(x, y);
    float32x4_t add_3 = vmulq_f32(neon_dupq_laneq_f32(x, 3), y); 
    return vaddq_f32(add_012, add_3);
}

}

}

#endif

#endif