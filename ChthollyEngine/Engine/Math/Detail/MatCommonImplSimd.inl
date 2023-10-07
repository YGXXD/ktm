#ifndef _MAT_COMMON_IMPL_SIMD_INL_
#define _MAT_COMMON_IMPL_SIMD_INL_

#include "Math/MathType/BaseType.h"
#include "MatCommonImpl.h"

#if defined(CHTHOLLY_SIMD_NEON)

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

            float32x4_t tmp0 = _neon_shuffleq_f32(c_0, c_1, 1, 0, 1, 0);
            float32x4_t tmp1 = _neon_shuffleq_f32(c_0, c_1, 3, 2, 3, 2);

            float32x4_t ret0 = _neon_shuffleq_f32(tmp0, c_2, 3, 0, 2, 0);
            float32x4_t ret1 = _neon_shuffleq_f32(tmp0, c_2, 3, 1, 3, 1);
            float32x4_t ret2 = _neon_shuffleq_f32(tmp1, c_2, 3, 2, 2, 0);

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

            float32x4_t tmp0 = _neon_shuffleq_f32(c_0, c_1, 1, 0, 1, 0);
            float32x4_t tmp2 = _neon_shuffleq_f32(c_0, c_1, 3, 2, 3, 2);
            float32x4_t tmp1 = _neon_shuffleq_f32(c_2, c_3, 1, 0, 1, 0);
            float32x4_t tmp3 = _neon_shuffleq_f32(c_2, c_3, 3, 2, 3, 2);

            float32x4_t ret0 = _neon_shuffleq_f32(tmp0, tmp1, 2, 0, 2, 0);
            float32x4_t ret1 = _neon_shuffleq_f32(tmp0, tmp1, 3, 1, 3, 1);
            float32x4_t ret2 = _neon_shuffleq_f32(tmp2, tmp3, 2, 0, 2, 0);
            float32x4_t ret3 = _neon_shuffleq_f32(tmp2, tmp3, 3, 1, 3, 1);

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

            int32x4_t tmp0 = _neon_shuffleq_s32(c_0, c_1, 1, 0, 1, 0);
            int32x4_t tmp1 = _neon_shuffleq_s32(c_0, c_1, 3, 2, 3, 2);

            int32x4_t ret0 = _neon_shuffleq_s32(tmp0, c_2, 3, 0, 2, 0);
            int32x4_t ret1 = _neon_shuffleq_s32(tmp0, c_2, 3, 1, 3, 1);
            int32x4_t ret2 = _neon_shuffleq_s32(tmp1, c_2, 3, 2, 2, 0);

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

            int32x4_t tmp0 = _neon_shuffleq_s32(c_0, c_1, 1, 0, 1, 0);
            int32x4_t tmp2 = _neon_shuffleq_s32(c_0, c_1, 3, 2, 3, 2);
            int32x4_t tmp1 = _neon_shuffleq_s32(c_2, c_3, 1, 0, 1, 0);
            int32x4_t tmp3 = _neon_shuffleq_s32(c_2, c_3, 3, 2, 3, 2);

            int32x4_t ret0 = _neon_shuffleq_s32(tmp0, tmp1, 2, 0, 2, 0);
            int32x4_t ret1 = _neon_shuffleq_s32(tmp0, tmp1, 3, 1, 3, 1);
            int32x4_t ret2 = _neon_shuffleq_s32(tmp2, tmp3, 2, 0, 2, 0);
            int32x4_t ret3 = _neon_shuffleq_s32(tmp2, tmp3, 3, 1, 3, 1);

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
            float32x4_t mul_00 = vmulq_f32(_neon_shuffleq_f32(t_col1, t_col1, 3, 0, 2, 1), _neon_shuffleq_f32(t_col2, t_col2, 3, 1, 0, 2));
            float32x4_t mul_01 = vmulq_f32(_neon_shuffleq_f32(t_col1, t_col1, 3, 1, 0, 2), _neon_shuffleq_f32(t_col2, t_col2, 3, 0, 2, 1));
            float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);  
            float32x4_t mul_0 = vmulq_f32(t_col0, sub_0);
            return vaddvq_f32(vsetq_lane_f32(zero<float>, mul_0, 3));
        }
        else 
        {
            float32x4_t t_col0 = vld1q_f32(&m[0][0]);
            float32x4_t t_col1 = vld1q_f32(&m[1][0]);
            float32x4_t t_col2 = vld1q_f32(&m[2][0]);
            float32x4_t t_col3 = vld1q_f32(&m[3][0]);

            float32x4_t mul_0;
            {
                float32x4_t mul_00 = vmulq_f32(_neon_shuffleq_f32(t_col2, t_col2, 1, 0, 3, 2), _neon_shuffleq_f32(t_col3, t_col3, 2, 1, 0, 3));
                float32x4_t mul_01 = vmulq_f32(_neon_shuffleq_f32(t_col2, t_col2, 2, 1, 0, 3), _neon_shuffleq_f32(t_col3, t_col3, 1, 0, 3, 2));
                float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);
                mul_0 = vmulq_f32(_neon_shuffleq_f32(t_col1, t_col1, 0, 3, 2, 1), sub_0);
            }

            float32x4_t mul_1;
            {
                float32x4_t mul_00 = vmulq_f32(_neon_shuffleq_f32(t_col2, t_col2, 2, 1, 0, 3), _neon_shuffleq_f32(t_col3, t_col3, 0, 3, 2, 1));
                float32x4_t mul_01 = vmulq_f32(_neon_shuffleq_f32(t_col2, t_col2, 0, 3, 2, 1), _neon_shuffleq_f32(t_col3, t_col3, 2, 1, 0, 3));
                float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);
                mul_1 = vmulq_f32(_neon_shuffleq_f32(t_col1, t_col1, 1, 0, 3, 2), sub_0);
            }

            float32x4_t mul_2;
            {
                float32x4_t mul_00 = vmulq_f32(_neon_shuffleq_f32(t_col2, t_col2, 0, 3, 2, 1), _neon_shuffleq_f32(t_col3, t_col3, 1, 0, 3, 2));
                float32x4_t mul_01 = vmulq_f32(_neon_shuffleq_f32(t_col2, t_col2, 1, 0, 3, 2), _neon_shuffleq_f32(t_col3, t_col3, 0, 3, 2, 1));
                float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);
                mul_2 = vmulq_f32(_neon_shuffleq_f32(t_col1, t_col1, 2, 1, 0, 3), sub_0);
            }

            float32x4_t mul_3 = vmulq_f32(t_col0, vaddq_f32(vaddq_f32(mul_0, mul_1), mul_2)); 
            mul_3 = _neon_shuffleq_f32(mul_3, mul_3, 3, 1, 2, 0);
            return vaddv_f32(vget_low_f32(mul_3) - vget_high_f32(mul_3));
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
            int32x4_t mul_00 = vmulq_s32(_neon_shuffleq_s32(t_col1, t_col1, 3, 0, 2, 1), _neon_shuffleq_s32(t_col2, t_col2, 3, 1, 0, 2));
            int32x4_t mul_01 = vmulq_s32(_neon_shuffleq_s32(t_col1, t_col1, 3, 1, 0, 2), _neon_shuffleq_s32(t_col2, t_col2, 3, 0, 2, 1));
            int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);  
            int32x4_t mul_0 = vmulq_s32(t_col0, sub_0);
            return vaddvq_s32(vsetq_lane_s32(zero<int>, mul_0, 3));
        }
        else 
        {
            int32x4_t t_col0 = vld1q_s32(&m[0][0]);
            int32x4_t t_col1 = vld1q_s32(&m[1][0]);
            int32x4_t t_col2 = vld1q_s32(&m[2][0]);
            int32x4_t t_col3 = vld1q_s32(&m[3][0]);  

            int32x4_t mul_0;
            {
                int32x4_t mul_00 = vmulq_s32(_neon_shuffleq_s32(t_col2, t_col2, 1, 0, 3, 2), _neon_shuffleq_s32(t_col3, t_col3, 2, 1, 0, 3));
                int32x4_t mul_01 = vmulq_s32(_neon_shuffleq_s32(t_col2, t_col2, 2, 1, 0, 3), _neon_shuffleq_s32(t_col3, t_col3, 1, 0, 3, 2));
                int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);
                mul_0 = vmulq_s32(_neon_shuffleq_s32(t_col1, t_col1, 0, 3, 2, 1), sub_0);
            }

            int32x4_t mul_1;
            {
                int32x4_t mul_00 = vmulq_s32(_neon_shuffleq_s32(t_col2, t_col2, 2, 1, 0, 3), _neon_shuffleq_s32(t_col3, t_col3, 0, 3, 2, 1));
                int32x4_t mul_01 = vmulq_s32(_neon_shuffleq_s32(t_col2, t_col2, 0, 3, 2, 1), _neon_shuffleq_s32(t_col3, t_col3, 2, 1, 0, 3));
                int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);
                mul_1 = vmulq_s32(_neon_shuffleq_s32(t_col1, t_col1, 1, 0, 3, 2), sub_0);
            }

            int32x4_t mul_2;
            {
                int32x4_t mul_00 = vmulq_s32(_neon_shuffleq_s32(t_col2, t_col2, 0, 3, 2, 1), _neon_shuffleq_s32(t_col3, t_col3, 1, 0, 3, 2));
                int32x4_t mul_01 = vmulq_s32(_neon_shuffleq_s32(t_col2, t_col2, 1, 0, 3, 2), _neon_shuffleq_s32(t_col3, t_col3, 0, 3, 2, 1));
                int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);
                mul_2 = vmulq_s32(_neon_shuffleq_s32(t_col1, t_col1, 2, 1, 0, 3), sub_0);
            }

            int32x4_t mul_3 = vmulq_s32(t_col0, vaddq_s32(vaddq_s32(mul_0, mul_1), mul_2)); 
            mul_3 = _neon_shuffleq_s32(mul_3, mul_3, 3, 1, 2, 0);
            return vaddv_s32(vget_low_s32(mul_3) - vget_high_s32(mul_3));
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
            float32x4_t swp_0a = _neon_shuffleq_f32(t_col3, t_col2, 3, 3, 3, 3);
            float32x4_t swp_0b = _neon_shuffleq_f32(t_col3, t_col2, 2, 2, 2, 2);

            float32x4_t swp_00 = _neon_shuffleq_f32(t_col2, t_col1, 2, 2, 2, 2);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(t_col2, t_col1, 3, 3, 3, 3);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_0 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_1;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(t_col3, t_col2, 3, 3, 3, 3);
            float32x4_t swp_0b = _neon_shuffleq_f32(t_col3, t_col2, 1, 1, 1, 1);

            float32x4_t swp_00 = _neon_shuffleq_f32(t_col2, t_col1, 1, 1, 1, 1);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(t_col2, t_col1, 3, 3, 3, 3);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_1 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_2;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(t_col3, t_col2, 2, 2, 2, 2);
            float32x4_t swp_0b = _neon_shuffleq_f32(t_col3, t_col2, 1, 1, 1, 1);

            float32x4_t swp_00 = _neon_shuffleq_f32(t_col2, t_col1, 1, 1, 1, 1);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(t_col2, t_col1, 2, 2, 2, 2);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_2 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_3;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(t_col3, t_col2, 3, 3, 3, 3);
            float32x4_t swp_0b = _neon_shuffleq_f32(t_col3, t_col2, 0, 0, 0, 0);

            float32x4_t swp_00 = _neon_shuffleq_f32(t_col2, t_col1, 0, 0, 0, 0);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(t_col2, t_col1, 3, 3, 3, 3);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_3 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_4;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(t_col3, t_col2, 2, 2, 2, 2);
            float32x4_t swp_0b = _neon_shuffleq_f32(t_col3, t_col2, 0, 0, 0, 0);

            float32x4_t swp_00 = _neon_shuffleq_f32(t_col2, t_col1, 0, 0, 0, 0);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(t_col2, t_col1, 2, 2, 2, 2);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_4 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_5;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(t_col3, t_col2, 1, 1, 1, 1);
            float32x4_t swp_0b = _neon_shuffleq_f32(t_col3, t_col2, 0, 0, 0, 0);

            float32x4_t swp_00 = _neon_shuffleq_f32(t_col2, t_col1, 0, 0, 0, 0);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(t_col2, t_col1, 1, 1, 1, 1);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_5 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t sign_a = vsetq_lane_f32(-one<float>, vsetq_lane_f32(-one<float>, vdupq_n_f32(one<float>), 0), 2);
        float32x4_t sign_b = vsetq_lane_f32(-one<float>, vsetq_lane_f32(-one<float>, vdupq_n_f32(one<float>), 1), 3);

        // v_0 = { m[1][0], m[0][0], m[0][0], m[0][0] }
        float32x4_t tmp_0 = _neon_shuffleq_f32(t_col1, t_col0, 0, 0, 0, 0);
        float32x4_t v_0 = _neon_shuffleq_f32(tmp_0, tmp_0, 2, 2, 2, 0);

        // v_0 = { m[1][1], m[0][1], m[0][1], m[0][1] }
        float32x4_t tmp_1 = _neon_shuffleq_f32(t_col1, t_col0, 1, 1, 1, 1);
        float32x4_t v_1 = _neon_shuffleq_f32(tmp_1, tmp_1, 2, 2, 2, 0);

        // v_0 = { m[1][2], m[0][2], m[0][2], m[0][2] }
        float32x4_t tmp_2 = _neon_shuffleq_f32(t_col1, t_col0, 2, 2, 2, 2);
        float32x4_t v_2 = _neon_shuffleq_f32(tmp_2, tmp_2, 2, 2, 2, 0);

        // v_0 = { m[1][3], m[0][3], m[0][3], m[0][3] }
        float32x4_t tmp_3 = _neon_shuffleq_f32(t_col1, t_col0, 3, 3, 3, 3);
        float32x4_t v_3 = _neon_shuffleq_f32(tmp_3, tmp_3, 2, 2, 2, 0);

        // inv_0
        // + (v_1[0] * fac_0[0] - v_2[0] * fac_1[0] + v_3[0] * fac_2[0])
        // - (v_1[1] * fac_0[1] - v_2[1] * fac_1[1] + v_3[1] * fac_2[1])
        // + (v_1[2] * fac_0[2] - v_2[2] * fac_1[2] + v_3[2] * fac_2[2])
        // - (v_1[3] * fac_0[3] - v_2[3] * fac_1[3] + v_3[3] * fac_2[3])
        float32x4_t inv_0; 
        {
            // sign_b * (v_1 * fac_0 - v_2 * fac_1 + v_3 * fac_2)
            float32x4_t mul_00 = vmulq_f32(v_1, fac_0);
            float32x4_t mul_01 = vmulq_f32(v_2, fac_1); 
            float32x4_t mul_02 = vmulq_f32(v_3, fac_2);
            float32x4_t sum_0 = vaddq_f32(vsubq_f32(mul_00, mul_01), mul_02);
            inv_0 = vmulq_f32(sign_b, sum_0);
        }

        // inv_1
        // - (v_0[0] * fac_0[0] - v_2[0] * fac_3[0] + v_3[0] * fac_4[0])
        // + (v_0[0] * fac_0[1] - v_2[1] * fac_3[1] + v_3[1] * fac_4[1])
        // - (v_0[0] * fac_0[2] - v_2[2] * fac_3[2] + v_3[2] * fac_4[2])
        // + (v_0[0] * fac_0[3] - v_2[3] * fac_3[3] + v_3[3] * fac_4[3])
        float32x4_t inv_1;
        {
            // sign_a * (v_0 * fac_0 - v_2 * fac_3 + v_3 * fac_4)
            float32x4_t mul_00 = vmulq_f32(v_0, fac_0);
            float32x4_t mul_01 = vmulq_f32(v_2, fac_3); 
            float32x4_t mul_02 = vmulq_f32(v_3, fac_4);
            float32x4_t sum_0 = vaddq_f32(vsubq_f32(mul_00, mul_01), mul_02);
            inv_1 = vmulq_f32(sign_a, sum_0);
        }

        // inv_2
        // + (v_0[0] * fac_1[0] - v_1[0] * fac_3[0] + v_3[0] * fac_5[0])
        // - (v_0[0] * fac_1[1] - v_1[1] * fac_3[1] + v_3[1] * fac_5[1])
        // + (v_0[0] * fac_1[2] - v_1[2] * fac_3[2] + v_3[2] * fac_5[2])
        // - (v_0[0] * fac_1[3] - v_1[3] * fac_3[3] + v_3[3] * fac_5[3])
        float32x4_t inv_2;
        {
            // sign_b * (v_0 * fac_1 - v_1 * fac_3 + v_3 * fac_5)
            float32x4_t mul_00 = vmulq_f32(v_0, fac_1);
            float32x4_t mul_01 = vmulq_f32(v_1, fac_3); 
            float32x4_t mul_02 = vmulq_f32(v_3, fac_5);
            float32x4_t sum_0 = vaddq_f32(vsubq_f32(mul_00, mul_01), mul_02);
            inv_2 = vmulq_f32(sign_b, sum_0);
        }

        // inv_3
        // - (v_0[0] * fac_2[0] - v_1[0] * fac_4[0] + v_2[0] * fac_5[0])
        // + (v_0[0] * fac_2[1] - v_1[1] * fac_4[1] + v_2[1] * fac_5[1])
        // - (v_0[0] * fac_2[2] - v_1[2] * fac_4[2] + v_2[2] * fac_5[2])
        // + (v_0[0] * fac_2[3] - v_1[3] * fac_4[3] + v_2[3] * fac_5[3])
        float32x4_t inv_3;
        {
            // sign_a * (v_0 * fac_2 - v_1 * fac_4 + v_2 * fac_5)
            float32x4_t mul_00 = vmulq_f32(v_0, fac_2);
            float32x4_t mul_01 = vmulq_f32(v_1, fac_4); 
            float32x4_t mul_02 = vmulq_f32(v_2, fac_5);
            float32x4_t sum_0 = vaddq_f32(vsubq_f32(mul_00, mul_01), mul_02);
            inv_3 = vmulq_f32(sign_a, sum_0);
        }

        // det
        // + m[0][0] * Inverse[0][0]
        // + m[0][1] * Inverse[1][0]
        // + m[0][2] * Inverse[2][0]
        // + m[0][3] * Inverse[3][0];
        float32x4_t i_tmp_0 = _neon_shuffleq_f32(inv_0, inv_1, 0, 0, 0, 0);
        float32x4_t i_tmp_1 = _neon_shuffleq_f32(inv_2, inv_3, 0, 0, 0, 0);
        float32x4_t i_row0 = _neon_shuffleq_f32(i_tmp_0, i_tmp_1, 3, 1, 3, 1);
        float32x4_t one_over_det = vdupq_n_f32(one<float> / vaddvq_f32(t_col0 * i_row0));

        M ret;

        vst1q_f32(&ret[0][0], vmulq_f32(inv_0, one_over_det)); 
        vst1q_f32(&ret[1][0], vmulq_f32(inv_1, one_over_det)); 
        vst1q_f32(&ret[2][0], vmulq_f32(inv_2, one_over_det)); 
        vst1q_f32(&ret[3][0], vmulq_f32(inv_3, one_over_det)); 

        return ret;
    }
};

#endif

#endif
