#ifndef _MAT_COMMON_IMPL_SIMD_INL_
#define _MAT_COMMON_IMPL_SIMD_INL_

#include "Math/MathType/BaseType.h"
#include "MatCommonImpl.h"

#ifdef __ARM_NEON__
#include <arm_neon.h>

template<size_t N>
struct ktm::detail::mat_common_implement::transpose<N, N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using M = mat<N, N, float>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        if constexpr(N == 3)
        {
            float32x4_t c_0 = vld1q_f32(&m[0][0]);
            float32x4_t c_1 = vld1q_f32(&m[1][0]);
            float32x4_t c_2 = vld1q_f32(&m[2][0]);

            float32x4_t tmp0 = __builtin_shufflevector(c_0, c_1, 0, 1, 4, 5);
            float32x4_t tmp1 = __builtin_shufflevector(c_0, c_1, 2, 3, 6, 7);

            float32x4_t ret0 = __builtin_shufflevector(tmp0, c_2, 0, 2, 4, 7);
            float32x4_t ret1 = __builtin_shufflevector(tmp0, c_2, 1, 3, 5, 7);
            float32x4_t ret2 = __builtin_shufflevector(tmp1, c_2, 0, 2, 6, 7);

            RetM ret;
            vst1q_f32(&ret[0][0], ret0);
            vst1q_f32(&ret[1][0], ret1);
            vst1q_f32(&ret[2][0], ret2);
            return ret; 
        }
        else
        {
            float32x4_t c_0 = vld1q_f32(&m[0][0]);
            float32x4_t c_1 = vld1q_f32(&m[1][0]);
            float32x4_t c_2 = vld1q_f32(&m[2][0]);
            float32x4_t c_3 = vld1q_f32(&m[3][0]);

            float32x4_t tmp0 = __builtin_shufflevector(c_0, c_1, 0, 1, 4, 5);
            float32x4_t tmp2 = __builtin_shufflevector(c_0, c_1, 2, 3, 6, 7);
            float32x4_t tmp1 = __builtin_shufflevector(c_2, c_3, 0, 1, 4, 5);
            float32x4_t tmp3 = __builtin_shufflevector(c_2, c_3, 2, 3, 6, 7);

            float32x4_t ret0 = __builtin_shufflevector(tmp0, tmp1, 0, 2, 4, 6);
            float32x4_t ret1 = __builtin_shufflevector(tmp0, tmp1, 1, 3, 5, 7);
            float32x4_t ret2 = __builtin_shufflevector(tmp2, tmp3, 0, 2, 4, 6);
            float32x4_t ret3 = __builtin_shufflevector(tmp2, tmp3, 1, 3, 5, 7);

            RetM ret;
            vst1q_f32(&ret[0][0], ret0);
            vst1q_f32(&ret[1][0], ret1);
            vst1q_f32(&ret[2][0], ret2);
            vst1q_f32(&ret[3][0], ret3);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::mat_common_implement::transpose<N, N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using M = mat<N, N, int>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        if constexpr(N == 3)
        {
            int32x4_t c_0 = vld1q_s32(&m[0][0]);
            int32x4_t c_1 = vld1q_s32(&m[1][0]);
            int32x4_t c_2 = vld1q_s32(&m[2][0]);

            int32x4_t tmp0 = __builtin_shufflevector(c_0, c_1, 0, 1, 4, 5);
            int32x4_t tmp1 = __builtin_shufflevector(c_0, c_1, 2, 3, 6, 7);

            int32x4_t ret0 = __builtin_shufflevector(tmp0, c_2, 0, 2, 4, 7);
            int32x4_t ret1 = __builtin_shufflevector(tmp0, c_2, 1, 3, 5, 7);
            int32x4_t ret2 = __builtin_shufflevector(tmp1, c_2, 0, 2, 6, 7);

            RetM ret;
            vst1q_s32(&ret[0][0], ret0);
            vst1q_s32(&ret[1][0], ret1);
            vst1q_s32(&ret[2][0], ret2);
            return ret; 
        }
        else
        {
            int32x4_t c_0 = vld1q_s32(&m[0][0]);
            int32x4_t c_1 = vld1q_s32(&m[1][0]);
            int32x4_t c_2 = vld1q_s32(&m[2][0]);
            int32x4_t c_3 = vld1q_s32(&m[3][0]);

            int32x4_t tmp0 = __builtin_shufflevector(c_0, c_1, 0, 1, 4, 5);
            int32x4_t tmp2 = __builtin_shufflevector(c_0, c_1, 2, 3, 6, 7);
            int32x4_t tmp1 = __builtin_shufflevector(c_2, c_3, 0, 1, 4, 5);
            int32x4_t tmp3 = __builtin_shufflevector(c_2, c_3, 2, 3, 6, 7);

            int32x4_t ret0 = __builtin_shufflevector(tmp0, tmp1, 0, 2, 4, 6);
            int32x4_t ret1 = __builtin_shufflevector(tmp0, tmp1, 1, 3, 5, 7);
            int32x4_t ret2 = __builtin_shufflevector(tmp2, tmp3, 0, 2, 4, 6);
            int32x4_t ret3 = __builtin_shufflevector(tmp2, tmp3, 1, 3, 5, 7);

            RetM ret;
            vst1q_s32(&ret[0][0], ret0);
            vst1q_s32(&ret[1][0], ret1);
            vst1q_s32(&ret[2][0], ret2);
            vst1q_s32(&ret[3][0], ret3);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::mat_common_implement::transpose<N, N, std::enable_if_t<N == 3 || N == 4, unsigned int>>
{
    using M = mat<N, N, unsigned int>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        if constexpr(N == 3)
        {
            uint32x4_t c_0 = vld1q_u32(&m[0][0]);
            uint32x4_t c_1 = vld1q_u32(&m[1][0]);
            uint32x4_t c_2 = vld1q_u32(&m[2][0]);

            uint32x4_t tmp0 = __builtin_shufflevector(c_0, c_1, 0, 1, 4, 5);
            uint32x4_t tmp1 = __builtin_shufflevector(c_0, c_1, 2, 3, 6, 7);

            uint32x4_t ret0 = __builtin_shufflevector(tmp0, c_2, 0, 2, 4, 7);
            uint32x4_t ret1 = __builtin_shufflevector(tmp0, c_2, 1, 3, 5, 7);
            uint32x4_t ret2 = __builtin_shufflevector(tmp1, c_2, 0, 2, 6, 7);

            RetM ret;
            vst1q_u32(&ret[0][0], ret0);
            vst1q_u32(&ret[1][0], ret1);
            vst1q_u32(&ret[2][0], ret2);
            return ret; 
        }
        else
        {
            uint32x4_t c_0 = vld1q_u32(&m[0][0]);
            uint32x4_t c_1 = vld1q_u32(&m[1][0]);
            uint32x4_t c_2 = vld1q_u32(&m[2][0]);
            uint32x4_t c_3 = vld1q_u32(&m[3][0]);

            uint32x4_t tmp0 = __builtin_shufflevector(c_0, c_1, 0, 1, 4, 5);
            uint32x4_t tmp2 = __builtin_shufflevector(c_0, c_1, 2, 3, 6, 7);
            uint32x4_t tmp1 = __builtin_shufflevector(c_2, c_3, 0, 1, 4, 5);
            uint32x4_t tmp3 = __builtin_shufflevector(c_2, c_3, 2, 3, 6, 7);

            uint32x4_t ret0 = __builtin_shufflevector(tmp0, tmp1, 0, 2, 4, 6);
            uint32x4_t ret1 = __builtin_shufflevector(tmp0, tmp1, 1, 3, 5, 7);
            uint32x4_t ret2 = __builtin_shufflevector(tmp2, tmp3, 0, 2, 4, 6);
            uint32x4_t ret3 = __builtin_shufflevector(tmp2, tmp3, 1, 3, 5, 7);

            RetM ret;
            vst1q_u32(&ret[0][0], ret0);
            vst1q_u32(&ret[1][0], ret1);
            vst1q_u32(&ret[2][0], ret2);
            vst1q_u32(&ret[3][0], ret3);
            return ret;
        }
    }
};

#define NEON_DET3_SHUFFLE_MUL(col0, col1, col2) col0 * \
(__builtin_shufflevector(col1, col1, 1, 2, 0, 3) * \
 __builtin_shufflevector(col2, col2, 2, 0, 1, 3) - \
 __builtin_shufflevector(col1, col1, 2, 0, 1, 3) * \
 __builtin_shufflevector(col2, col2, 1, 2, 0, 3))

#define NEON_DET4_SHUFFLE_MUL(col0, col1, col2, col3) col0 * \
(__builtin_shufflevector(col1, col1, 1, 2, 3, 0) * \
(__builtin_shufflevector(col2, col2, 2, 3, 0, 1) * \
 __builtin_shufflevector(col3, col3, 3, 0, 1, 2) - \
 __builtin_shufflevector(col2, col2, 3, 0, 1, 2) * \
 __builtin_shufflevector(col3, col3, 2, 3, 0, 1)) \
 + \
 __builtin_shufflevector(col1, col1, 2, 3, 0, 1) * \
(__builtin_shufflevector(col2, col2, 3, 0, 1, 2) * \
 __builtin_shufflevector(col3, col3, 1, 2, 3, 0) - \
 __builtin_shufflevector(col2, col2, 1, 2, 3, 0) * \
 __builtin_shufflevector(col3, col3, 3, 0, 1, 2)) \
 + \
 __builtin_shufflevector(col1, col1, 3, 0, 1, 2) * \
(__builtin_shufflevector(col2, col2, 1, 2, 3, 0) * \
 __builtin_shufflevector(col3, col3, 2, 3, 0, 1) - \
 __builtin_shufflevector(col2, col2, 2, 3, 0, 1) * \
 __builtin_shufflevector(col3, col3, 1, 2, 3, 0)))

template<size_t N>
struct ktm::detail::mat_common_implement::determinant<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using M = mat<N, N, float>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        if constexpr(N == 3)
        {
            float32x4_t t_col0 = vld1q_f32(&m[0][0]);
            float32x4_t t_col1 = vld1q_f32(&m[1][0]);
            float32x4_t t_col2 = vld1q_f32(&m[2][0]);
            float32x4_t tmp = NEON_DET3_SHUFFLE_MUL(t_col0, t_col1, t_col2);
            return vaddvq_f32(vsetq_lane_f32(zero<float>, tmp, 3));
        }
        else 
        {
            float32x4_t t_col0 = vld1q_f32(&m[0][0]);
            float32x4_t t_col1 = vld1q_f32(&m[1][0]);
            float32x4_t t_col2 = vld1q_f32(&m[2][0]);
            float32x4_t t_col3 = vld1q_f32(&m[3][0]);
            float32x4_t tmp = NEON_DET4_SHUFFLE_MUL(t_col0, t_col1, t_col2, t_col3);
            tmp = __builtin_shufflevector(tmp, tmp, 0, 2, 1, 3);
            return vaddv_f32(vget_low_f32(tmp) - vget_high_f32(tmp));
        }
    }
};

template<size_t N>
struct ktm::detail::mat_common_implement::determinant<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using M = mat<N, N, int>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        if constexpr(N == 3)
        {
            int32x4_t t_col0 = vld1q_s32(&m[0][0]);
            int32x4_t t_col1 = vld1q_s32(&m[1][0]);
            int32x4_t t_col2 = vld1q_s32(&m[2][0]);
            int32x4_t tmp = NEON_DET3_SHUFFLE_MUL(t_col0, t_col1, t_col2);
            return vaddvq_s32(vsetq_lane_s32(zero<int>, tmp, 3));
        }
        else 
        {
            int32x4_t t_col0 = vld1q_s32(&m[0][0]);
            int32x4_t t_col1 = vld1q_s32(&m[1][0]);
            int32x4_t t_col2 = vld1q_s32(&m[2][0]);
            int32x4_t t_col3 = vld1q_s32(&m[3][0]);
            int32x4_t tmp = NEON_DET4_SHUFFLE_MUL(t_col0, t_col1, t_col2, t_col3);
            tmp = __builtin_shufflevector(tmp, tmp, 0, 2, 1, 3);
            return vaddv_s32(vget_low_s32(tmp) - vget_high_s32(tmp));
        }
    }
};

template<size_t N>
struct ktm::detail::mat_common_implement::determinant<N, std::enable_if_t<N == 3 || N == 4, unsigned int>>
{
    using M = mat<N, N, unsigned int>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        if constexpr(N == 3)
        {
            uint32x4_t t_col0 = vld1q_u32(&m[0][0]);
            uint32x4_t t_col1 = vld1q_u32(&m[1][0]);
            uint32x4_t t_col2 = vld1q_u32(&m[2][0]);
            uint32x4_t tmp = NEON_DET3_SHUFFLE_MUL(t_col0, t_col1, t_col2);
            return vaddvq_u32(vsetq_lane_u32(zero<unsigned int>, tmp, 3));
        }
        else 
        {
            uint32x4_t t_col0 = vld1q_u32(&m[0][0]);
            uint32x4_t t_col1 = vld1q_u32(&m[1][0]);
            uint32x4_t t_col2 = vld1q_u32(&m[2][0]);
            uint32x4_t t_col3 = vld1q_u32(&m[3][0]);
            uint32x4_t tmp = NEON_DET4_SHUFFLE_MUL(t_col0, t_col1, t_col2, t_col3);
            tmp = __builtin_shufflevector(tmp, tmp, 0, 2, 1, 3);
            return vaddv_u32(vget_low_u32(tmp) - vget_high_u32(tmp));
        }
    }
};

template<size_t N>
struct ktm::detail::mat_common_implement::inverse<N, std::enable_if_t<N == 4, float>>
{
    using M = mat<N, N, float>;
    static CHTHOLLY_INLINE M call(const M& m) noexcept
    {
        float32x4_t t_col0 = vld1q_f32(&m[0][0]);
        float32x4_t t_col1 = vld1q_f32(&m[1][0]);
        float32x4_t t_col2 = vld1q_f32(&m[2][0]);
        float32x4_t t_col3 = vld1q_f32(&m[3][0]);

        float32x4_t fac_0;
        {
            float32x4_t swp_0a = __builtin_shufflevector(t_col3, t_col2, 3, 3, 7, 7);
            float32x4_t swp_0b = __builtin_shufflevector(t_col3, t_col2, 2, 2, 6, 6);

            float32x4_t swp_00 = __builtin_shufflevector(t_col2, t_col1, 2, 2, 6, 6);
            float32x4_t swp_01 = __builtin_shufflevector(swp_0a, swp_0a, 0, 0, 0, 2);
            float32x4_t swp_02 = __builtin_shufflevector(swp_0b, swp_0b, 0, 0, 0, 2);
            float32x4_t swp_03 = __builtin_shufflevector(t_col2, t_col1, 3, 3, 7, 7);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_0 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_1;
        {
            float32x4_t swp_0a = __builtin_shufflevector(t_col3, t_col2, 3, 3, 7, 7);
            float32x4_t swp_0b = __builtin_shufflevector(t_col3, t_col2, 1, 1, 5, 5);

            float32x4_t swp_00 = __builtin_shufflevector(t_col2, t_col1, 1, 1, 5, 5);
            float32x4_t swp_01 = __builtin_shufflevector(swp_0a, swp_0a, 0, 0, 0, 2);
            float32x4_t swp_02 = __builtin_shufflevector(swp_0b, swp_0b, 0, 0, 0, 2);
            float32x4_t swp_03 = __builtin_shufflevector(t_col2, t_col1, 3, 3, 7, 7);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_1 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_2;
        {
            float32x4_t swp_0a = __builtin_shufflevector(t_col3, t_col2, 2, 2, 6, 6);
            float32x4_t swp_0b = __builtin_shufflevector(t_col3, t_col2, 1, 1, 5, 5);

            float32x4_t swp_00 = __builtin_shufflevector(t_col2, t_col1, 1, 1, 5, 5);
            float32x4_t swp_01 = __builtin_shufflevector(swp_0a, swp_0a, 0, 0, 0, 2);
            float32x4_t swp_02 = __builtin_shufflevector(swp_0b, swp_0b, 0, 0, 0, 2);
            float32x4_t swp_03 = __builtin_shufflevector(t_col2, t_col1, 2, 2, 6, 6);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_2 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_3;
        {
            float32x4_t swp_0a = __builtin_shufflevector(t_col3, t_col2, 3, 3, 7, 7);
            float32x4_t swp_0b = __builtin_shufflevector(t_col3, t_col2, 0, 0, 4, 4);

            float32x4_t swp_00 = __builtin_shufflevector(t_col2, t_col1, 0, 0, 4, 4);
            float32x4_t swp_01 = __builtin_shufflevector(swp_0a, swp_0a, 0, 0, 0, 2);
            float32x4_t swp_02 = __builtin_shufflevector(swp_0b, swp_0b, 0, 0, 0, 2);
            float32x4_t swp_03 = __builtin_shufflevector(t_col2, t_col1, 3, 3, 7, 7);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_3 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_4;
        {
            float32x4_t swp_0a = __builtin_shufflevector(t_col3, t_col2, 2, 2, 6, 6);
            float32x4_t swp_0b = __builtin_shufflevector(t_col3, t_col2, 0, 0, 4, 4);

            float32x4_t swp_00 = __builtin_shufflevector(t_col2, t_col1, 0, 0, 4, 4);
            float32x4_t swp_01 = __builtin_shufflevector(swp_0a, swp_0a, 0, 0, 0, 2);
            float32x4_t swp_02 = __builtin_shufflevector(swp_0b, swp_0b, 0, 0, 0, 2);
            float32x4_t swp_03 = __builtin_shufflevector(t_col2, t_col1, 2, 2, 6, 6);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_4 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_5;
        {
            float32x4_t swp_0a = __builtin_shufflevector(t_col3, t_col2, 1, 1, 5, 5);
            float32x4_t swp_0b = __builtin_shufflevector(t_col3, t_col2, 0, 0, 4, 4);

            float32x4_t swp_00 = __builtin_shufflevector(t_col2, t_col1, 0, 0, 4, 4);
            float32x4_t swp_01 = __builtin_shufflevector(swp_0a, swp_0a, 0, 0, 0, 2);
            float32x4_t swp_02 = __builtin_shufflevector(swp_0b, swp_0b, 0, 0, 0, 2);
            float32x4_t swp_03 = __builtin_shufflevector(t_col2, t_col1, 1, 1, 5, 5);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_5 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t sign_a = vsetq_lane_f32(-one<float>, vsetq_lane_f32(-one<float>, vdupq_n_f32(one<float>), 0), 2);
        float32x4_t sign_b = vsetq_lane_f32(-one<float>, vsetq_lane_f32(-one<float>, vdupq_n_f32(one<float>), 1), 3);

        // v_0 = { m[1][0], m[0][0], m[0][0], m[0][0] }
        float32x4_t tmp_0 = __builtin_shufflevector(t_col1, t_col0, 0, 0, 4, 4);
        float32x4_t v_0 = __builtin_shufflevector(tmp_0, tmp_0, 0, 2, 2, 2);

        // v_0 = { m[1][1], m[0][1], m[0][1], m[0][1] }
        float32x4_t tmp_1 = __builtin_shufflevector(t_col1, t_col0, 1, 1, 5, 5);
        float32x4_t v_1 = __builtin_shufflevector(tmp_1, tmp_1, 0, 2, 2, 2);

        // v_0 = { m[1][2], m[0][2], m[0][2], m[0][2] }
        float32x4_t tmp_2 = __builtin_shufflevector(t_col1, t_col0, 2, 2, 6, 6);
        float32x4_t v_2 = __builtin_shufflevector(tmp_2, tmp_2, 0, 2, 2, 2);

        // v_0 = { m[1][3], m[0][3], m[0][3], m[0][3] }
        float32x4_t tmp_3 = __builtin_shufflevector(t_col1, t_col0, 3, 3, 7, 7);
        float32x4_t v_3 = __builtin_shufflevector(tmp_3, tmp_3, 0, 2, 2, 2);

        // inv_0
        // + (v_1[0] * fac_0[0] - v_2[0] * fac_1[0] + v_3[0] * fac_2[0])
        // - (v_1[1] * fac_0[1] - v_2[1] * fac_1[1] + v_3[1] * fac_2[1])
        // + (v_1[2] * fac_0[2] - v_2[2] * fac_1[2] + v_3[2] * fac_2[2])
        // - (v_1[3] * fac_0[3] - v_2[3] * fac_1[3] + v_3[3] * fac_2[3])
        float32x4_t inv_0 = sign_b * (v_1 * fac_0 - v_2 * fac_1 + v_3 * fac_2);

        // inv_1
        // - (v_0[0] * fac_0[0] - v_2[0] * fac_3[0] + v_3[0] * fac_4[0])
        // + (v_0[0] * fac_0[1] - v_2[1] * fac_3[1] + v_3[1] * fac_4[1])
        // - (v_0[0] * fac_0[2] - v_2[2] * fac_3[2] + v_3[2] * fac_4[2])
        // + (v_0[0] * fac_0[3] - v_2[3] * fac_3[3] + v_3[3] * fac_4[3])
        float32x4_t inv_1 = sign_a * (v_0 * fac_0 - v_2 * fac_3 + v_3 * fac_4);

        // inv_2
        // + (v_0[0] * fac_1[0] - v_1[0] * fac_3[0] + v_3[0] * fac_5[0])
        // - (v_0[0] * fac_1[1] - v_1[1] * fac_3[1] + v_3[1] * fac_5[1])
        // + (v_0[0] * fac_1[2] - v_1[2] * fac_3[2] + v_3[2] * fac_5[2])
        // - (v_0[0] * fac_1[3] - v_1[3] * fac_3[3] + v_3[3] * fac_5[3])
        float32x4_t inv_2 = sign_b * (v_0 * fac_1 - v_1 * fac_3 + v_3 * fac_5);

        // inv_3
        // - (v_0[0] * fac_2[0] - v_1[0] * fac_4[0] + v_2[0] * fac_5[0])
        // + (v_0[0] * fac_2[1] - v_1[1] * fac_4[1] + v_2[1] * fac_5[1])
        // - (v_0[0] * fac_2[2] - v_1[2] * fac_4[2] + v_2[2] * fac_5[2])
        // + (v_0[0] * fac_2[3] - v_1[3] * fac_4[3] + v_2[3] * fac_5[3])
        float32x4_t inv_3 = sign_a * (v_0 * fac_2 - v_1 * fac_4 + v_2 * fac_5);

        // det
        // + m[0][0] * Inverse[0][0]
        // + m[0][1] * Inverse[1][0]
        // + m[0][2] * Inverse[2][0]
        // + m[0][3] * Inverse[3][0];
        float32x4_t i_tmp_0 = __builtin_shufflevector(inv_0, inv_1, 0, 0, 4, 4);
        float32x4_t i_tmp_1 = __builtin_shufflevector(inv_2, inv_3, 0, 0, 4, 4);
        float32x4_t i_row0 = __builtin_shufflevector(i_tmp_0, i_tmp_1, 1, 3, 5, 7);
        float one_over_det = one<float> / vaddvq_f32(t_col0 * i_row0);

        M ret;

        vst1q_f32(&ret[0][0], inv_0 * one_over_det); 
        vst1q_f32(&ret[1][0], inv_1 * one_over_det); 
        vst1q_f32(&ret[2][0], inv_2 * one_over_det); 
        vst1q_f32(&ret[3][0], inv_3 * one_over_det); 

        return ret;
    }
};

#endif

#endif
