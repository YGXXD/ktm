#ifndef _MAT_COMMON_IMPL_SIMD_INL_
#define _MAT_COMMON_IMPL_SIMD_INL_

#include "MatCommonImpl.h"
#include "Math/Library/Definition.h"

#if defined(CHTHOLLY_SIMD_NEON)

template<>
struct ktm::detail::mat_common_implement::transpose<3, 3, float>
{
    using M = mat<3, 3, float>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        float32x4_t c_0 = vld1q_f32(&m[0][0]);
        float32x4_t c_1 = vld1q_f32(&m[1][0]);
        float32x4_t c_2 = vld1q_f32(&m[2][0]);

        float32x4_t tmp_0 = _neon_shuffleq_f32(c_0, c_1, 1, 0, 1, 0);
        float32x4_t tmp_1 = _neon_shuffleq_f32(c_0, c_1, 3, 2, 3, 2);

        float32x4_t ret_0 = _neon_shuffleq_f32(tmp_0, c_2, 3, 0, 2, 0);
        float32x4_t ret_1 = _neon_shuffleq_f32(tmp_0, c_2, 3, 1, 3, 1);
        float32x4_t ret_2 = _neon_shuffleq_f32(tmp_1, c_2, 3, 2, 2, 0);

        RetM ret;
        vst1q_f32(&ret[0][0], ret_0);
        vst1q_f32(&ret[1][0], ret_1);
        vst1q_f32(&ret[2][0], ret_2);
        return ret; 
    }
};

template<>
struct ktm::detail::mat_common_implement::transpose<4, 4, float>
{
    using M = mat<4, 4, float>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        float32x4_t c_0 = vld1q_f32(&m[0][0]);
        float32x4_t c_1 = vld1q_f32(&m[1][0]);
        float32x4_t c_2 = vld1q_f32(&m[2][0]);
        float32x4_t c_3 = vld1q_f32(&m[3][0]);

        float32x4_t tmp_0 = _neon_shuffleq_f32(c_0, c_1, 1, 0, 1, 0);
        float32x4_t tmp_2 = _neon_shuffleq_f32(c_0, c_1, 3, 2, 3, 2);
        float32x4_t tmp_1 = _neon_shuffleq_f32(c_2, c_3, 1, 0, 1, 0);
        float32x4_t tmp_3 = _neon_shuffleq_f32(c_2, c_3, 3, 2, 3, 2);

        float32x4_t ret_0 = _neon_shuffleq_f32(tmp_0, tmp_1, 2, 0, 2, 0);
        float32x4_t ret_1 = _neon_shuffleq_f32(tmp_0, tmp_1, 3, 1, 3, 1);
        float32x4_t ret_2 = _neon_shuffleq_f32(tmp_2, tmp_3, 2, 0, 2, 0);
        float32x4_t ret_3 = _neon_shuffleq_f32(tmp_2, tmp_3, 3, 1, 3, 1);

        RetM ret;
        vst1q_f32(&ret[0][0], ret_0);
        vst1q_f32(&ret[1][0], ret_1);
        vst1q_f32(&ret[2][0], ret_2);
        vst1q_f32(&ret[3][0], ret_3);
        return ret;
    }
};

template<>
struct ktm::detail::mat_common_implement::transpose<3, 3, int>
{
    using M = mat<3, 3, int>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        int32x4_t c_0 = vld1q_s32(&m[0][0]);
        int32x4_t c_1 = vld1q_s32(&m[1][0]);
        int32x4_t c_2 = vld1q_s32(&m[2][0]);

        int32x4_t tmp_0 = _neon_shuffleq_s32(c_0, c_1, 1, 0, 1, 0);
        int32x4_t tmp_1 = _neon_shuffleq_s32(c_0, c_1, 3, 2, 3, 2);

        int32x4_t ret_0 = _neon_shuffleq_s32(tmp_0, c_2, 3, 0, 2, 0);
        int32x4_t ret_1 = _neon_shuffleq_s32(tmp_0, c_2, 3, 1, 3, 1);
        int32x4_t ret_2 = _neon_shuffleq_s32(tmp_1, c_2, 3, 2, 2, 0);

        RetM ret;
        vst1q_s32(&ret[0][0], ret_0);
        vst1q_s32(&ret[1][0], ret_1);
        vst1q_s32(&ret[2][0], ret_2);
        return ret; 
    }
};

template<>
struct ktm::detail::mat_common_implement::transpose<4, 4, int>
{
    using M = mat<4, 4, int>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        int32x4_t c_0 = vld1q_s32(&m[0][0]);
        int32x4_t c_1 = vld1q_s32(&m[1][0]);
        int32x4_t c_2 = vld1q_s32(&m[2][0]);
        int32x4_t c_3 = vld1q_s32(&m[3][0]);

        int32x4_t tmp_0 = _neon_shuffleq_s32(c_0, c_1, 1, 0, 1, 0);
        int32x4_t tmp_2 = _neon_shuffleq_s32(c_0, c_1, 3, 2, 3, 2);
        int32x4_t tmp_1 = _neon_shuffleq_s32(c_2, c_3, 1, 0, 1, 0);
        int32x4_t tmp_3 = _neon_shuffleq_s32(c_2, c_3, 3, 2, 3, 2);

        int32x4_t ret_0 = _neon_shuffleq_s32(tmp_0, tmp_1, 2, 0, 2, 0);
        int32x4_t ret_1 = _neon_shuffleq_s32(tmp_0, tmp_1, 3, 1, 3, 1);
        int32x4_t ret_2 = _neon_shuffleq_s32(tmp_2, tmp_3, 2, 0, 2, 0);
        int32x4_t ret_3 = _neon_shuffleq_s32(tmp_2, tmp_3, 3, 1, 3, 1);

        RetM ret;
        vst1q_s32(&ret[0][0], ret_0);
        vst1q_s32(&ret[1][0], ret_1);
        vst1q_s32(&ret[2][0], ret_2);
        vst1q_s32(&ret[3][0], ret_3);
        return ret;
    }
};

template<>
struct ktm::detail::mat_common_implement::determinant<3, float>
{
    using M = mat<3, 3, float>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        float32x4_t c_0 = vld1q_f32(&m[0][0]);
        float32x4_t c_1 = vld1q_f32(&m[1][0]);
        float32x4_t c_2 = vld1q_f32(&m[2][0]);
        float32x4_t mul_00 = vmulq_f32(_neon_shuffleq_f32(c_1, c_1, 3, 0, 2, 1), _neon_shuffleq_f32(c_2, c_2, 3, 1, 0, 2));
        float32x4_t mul_01 = vmulq_f32(_neon_shuffleq_f32(c_1, c_1, 3, 1, 0, 2), _neon_shuffleq_f32(c_2, c_2, 3, 0, 2, 1));
        float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);  
        float32x4_t mul_0 = vmulq_f32(c_0, sub_0);
        return vaddvq_f32(vsetq_lane_f32(zero<float>, mul_0, 3));
    }
};

template<>
struct ktm::detail::mat_common_implement::determinant<4, float>
{
    using M = mat<4, 4, float>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        float32x4_t c_0 = vld1q_f32(&m[0][0]);
        float32x4_t c_1 = vld1q_f32(&m[1][0]);
        float32x4_t c_2 = vld1q_f32(&m[2][0]);
        float32x4_t c_3 = vld1q_f32(&m[3][0]);

        float32x4_t mul_0;
        {
            float32x4_t mul_00 = vmulq_f32(_neon_shuffleq_f32(c_2, c_2, 1, 0, 3, 2), _neon_shuffleq_f32(c_3, c_3, 2, 1, 0, 3));
            float32x4_t mul_01 = vmulq_f32(_neon_shuffleq_f32(c_2, c_2, 2, 1, 0, 3), _neon_shuffleq_f32(c_3, c_3, 1, 0, 3, 2));
            float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);
            mul_0 = vmulq_f32(_neon_shuffleq_f32(c_1, c_1, 0, 3, 2, 1), sub_0);
        }

        float32x4_t mul_1;
        {
            float32x4_t mul_00 = vmulq_f32(_neon_shuffleq_f32(c_2, c_2, 2, 1, 0, 3), _neon_shuffleq_f32(c_3, c_3, 0, 3, 2, 1));
            float32x4_t mul_01 = vmulq_f32(_neon_shuffleq_f32(c_2, c_2, 0, 3, 2, 1), _neon_shuffleq_f32(c_3, c_3, 2, 1, 0, 3));
            float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);
            mul_1 = vmulq_f32(_neon_shuffleq_f32(c_1, c_1, 1, 0, 3, 2), sub_0);
        }

        float32x4_t mul_2;
        {
            float32x4_t mul_00 = vmulq_f32(_neon_shuffleq_f32(c_2, c_2, 0, 3, 2, 1), _neon_shuffleq_f32(c_3, c_3, 1, 0, 3, 2));
            float32x4_t mul_01 = vmulq_f32(_neon_shuffleq_f32(c_2, c_2, 1, 0, 3, 2), _neon_shuffleq_f32(c_3, c_3, 0, 3, 2, 1));
            float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);
            mul_2 = vmulq_f32(_neon_shuffleq_f32(c_1, c_1, 2, 1, 0, 3), sub_0);
        }

        float32x4_t mul_3 = vmulq_f32(c_0, vaddq_f32(vaddq_f32(mul_0, mul_1), mul_2)); 
        mul_3 = _neon_shuffleq_f32(mul_3, mul_3, 3, 1, 2, 0);
        return vaddv_f32(vget_low_f32(mul_3) - vget_high_f32(mul_3));
    }
};

template<>
struct ktm::detail::mat_common_implement::determinant<3, int>
{
    using M = mat<3, 3, int>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        int32x4_t c_0 = vld1q_s32(&m[0][0]);
        int32x4_t c_1 = vld1q_s32(&m[1][0]);
        int32x4_t c_2 = vld1q_s32(&m[2][0]);
        int32x4_t mul_00 = vmulq_s32(_neon_shuffleq_s32(c_1, c_1, 3, 0, 2, 1), _neon_shuffleq_s32(c_2, c_2, 3, 1, 0, 2));
        int32x4_t mul_01 = vmulq_s32(_neon_shuffleq_s32(c_1, c_1, 3, 1, 0, 2), _neon_shuffleq_s32(c_2, c_2, 3, 0, 2, 1));
        int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);  
        int32x4_t mul_0 = vmulq_s32(c_0, sub_0);
        return vaddvq_s32(vsetq_lane_s32(zero<int>, mul_0, 3));
    }
};

template<>
struct ktm::detail::mat_common_implement::determinant<4, int>
{
    using M = mat<4, 4, int>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        int32x4_t c_0 = vld1q_s32(&m[0][0]);
        int32x4_t c_1 = vld1q_s32(&m[1][0]);
        int32x4_t c_2 = vld1q_s32(&m[2][0]);
        int32x4_t c_3 = vld1q_s32(&m[3][0]);  

        int32x4_t mul_0;
        {
            int32x4_t mul_00 = vmulq_s32(_neon_shuffleq_s32(c_2, c_2, 1, 0, 3, 2), _neon_shuffleq_s32(c_3, c_3, 2, 1, 0, 3));
            int32x4_t mul_01 = vmulq_s32(_neon_shuffleq_s32(c_2, c_2, 2, 1, 0, 3), _neon_shuffleq_s32(c_3, c_3, 1, 0, 3, 2));
            int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);
            mul_0 = vmulq_s32(_neon_shuffleq_s32(c_1, c_1, 0, 3, 2, 1), sub_0);
        }

        int32x4_t mul_1;
        {
            int32x4_t mul_00 = vmulq_s32(_neon_shuffleq_s32(c_2, c_2, 2, 1, 0, 3), _neon_shuffleq_s32(c_3, c_3, 0, 3, 2, 1));
            int32x4_t mul_01 = vmulq_s32(_neon_shuffleq_s32(c_2, c_2, 0, 3, 2, 1), _neon_shuffleq_s32(c_3, c_3, 2, 1, 0, 3));
            int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);
            mul_1 = vmulq_s32(_neon_shuffleq_s32(c_1, c_1, 1, 0, 3, 2), sub_0);
        }

        int32x4_t mul_2;
        {
            int32x4_t mul_00 = vmulq_s32(_neon_shuffleq_s32(c_2, c_2, 0, 3, 2, 1), _neon_shuffleq_s32(c_3, c_3, 1, 0, 3, 2));
            int32x4_t mul_01 = vmulq_s32(_neon_shuffleq_s32(c_2, c_2, 1, 0, 3, 2), _neon_shuffleq_s32(c_3, c_3, 0, 3, 2, 1));
            int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);
            mul_2 = vmulq_s32(_neon_shuffleq_s32(c_1, c_1, 2, 1, 0, 3), sub_0);
        }

        int32x4_t mul_3 = vmulq_s32(c_0, vaddq_s32(vaddq_s32(mul_0, mul_1), mul_2)); 
        mul_3 = _neon_shuffleq_s32(mul_3, mul_3, 3, 1, 2, 0);
        return vaddv_s32(vget_low_s32(mul_3) - vget_high_s32(mul_3));
    }
};

template<>
struct ktm::detail::mat_common_implement::inverse<4, float>
{
    using M = mat<4, 4, float>;
    static CHTHOLLY_INLINE M call(const M& m) noexcept
    {
        float32x4_t c_0 = vld1q_f32(&m[0][0]);
        float32x4_t c_1 = vld1q_f32(&m[1][0]);
        float32x4_t c_2 = vld1q_f32(&m[2][0]);
        float32x4_t c_3 = vld1q_f32(&m[3][0]);

        float32x4_t fac_0;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(c_3, c_2, 3, 3, 3, 3);
            float32x4_t swp_0b = _neon_shuffleq_f32(c_3, c_2, 2, 2, 2, 2);

            float32x4_t swp_00 = _neon_shuffleq_f32(c_2, c_1, 2, 2, 2, 2);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(c_2, c_1, 3, 3, 3, 3);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_0 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_1;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(c_3, c_2, 3, 3, 3, 3);
            float32x4_t swp_0b = _neon_shuffleq_f32(c_3, c_2, 1, 1, 1, 1);

            float32x4_t swp_00 = _neon_shuffleq_f32(c_2, c_1, 1, 1, 1, 1);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(c_2, c_1, 3, 3, 3, 3);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_1 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_2;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(c_3, c_2, 2, 2, 2, 2);
            float32x4_t swp_0b = _neon_shuffleq_f32(c_3, c_2, 1, 1, 1, 1);

            float32x4_t swp_00 = _neon_shuffleq_f32(c_2, c_1, 1, 1, 1, 1);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(c_2, c_1, 2, 2, 2, 2);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_2 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_3;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(c_3, c_2, 3, 3, 3, 3);
            float32x4_t swp_0b = _neon_shuffleq_f32(c_3, c_2, 0, 0, 0, 0);

            float32x4_t swp_00 = _neon_shuffleq_f32(c_2, c_1, 0, 0, 0, 0);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(c_2, c_1, 3, 3, 3, 3);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_3 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_4;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(c_3, c_2, 2, 2, 2, 2);
            float32x4_t swp_0b = _neon_shuffleq_f32(c_3, c_2, 0, 0, 0, 0);

            float32x4_t swp_00 = _neon_shuffleq_f32(c_2, c_1, 0, 0, 0, 0);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(c_2, c_1, 2, 2, 2, 2);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_4 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_5;
        {
            float32x4_t swp_0a = _neon_shuffleq_f32(c_3, c_2, 1, 1, 1, 1);
            float32x4_t swp_0b = _neon_shuffleq_f32(c_3, c_2, 0, 0, 0, 0);

            float32x4_t swp_00 = _neon_shuffleq_f32(c_2, c_1, 0, 0, 0, 0);
            float32x4_t swp_01 = _neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = _neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = _neon_shuffleq_f32(c_2, c_1, 1, 1, 1, 1);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_5 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t sign_a = vsetq_lane_f32(-one<float>, vsetq_lane_f32(-one<float>, vdupq_n_f32(one<float>), 0), 2);
        float32x4_t sign_b = vsetq_lane_f32(-one<float>, vsetq_lane_f32(-one<float>, vdupq_n_f32(one<float>), 1), 3);

        // v_0 = { m[1][0], m[0][0], m[0][0], m[0][0] }
        float32x4_t tmp_0 = _neon_shuffleq_f32(c_1, c_0, 0, 0, 0, 0);
        float32x4_t v_0 = _neon_shuffleq_f32(tmp_0, tmp_0, 2, 2, 2, 0);

        // v_0 = { m[1][1], m[0][1], m[0][1], m[0][1] }
        float32x4_t tmp_1 = _neon_shuffleq_f32(c_1, c_0, 1, 1, 1, 1);
        float32x4_t v_1 = _neon_shuffleq_f32(tmp_1, tmp_1, 2, 2, 2, 0);

        // v_0 = { m[1][2], m[0][2], m[0][2], m[0][2] }
        float32x4_t tmp_2 = _neon_shuffleq_f32(c_1, c_0, 2, 2, 2, 2);
        float32x4_t v_2 = _neon_shuffleq_f32(tmp_2, tmp_2, 2, 2, 2, 0);

        // v_0 = { m[1][3], m[0][3], m[0][3], m[0][3] }
        float32x4_t tmp_3 = _neon_shuffleq_f32(c_1, c_0, 3, 3, 3, 3);
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
        float32x4_t i_row_0 = _neon_shuffleq_f32(i_tmp_0, i_tmp_1, 3, 1, 3, 1);
        float32x4_t i_mul_0 = vmulq_f32(c_0, i_row_0);
        float32x4_t i_add_0 = vpaddq_f32(i_mul_0, i_mul_0);
        float32x4_t i_add_1 = vpaddq_f32(i_add_0, i_add_0);
        float32x4_t one_over_det = vdivq_f32(vdupq_n_f32(one<float>), i_add_1);
        
        M ret;

        vst1q_f32(&ret[0][0], vmulq_f32(inv_0, one_over_det)); 
        vst1q_f32(&ret[1][0], vmulq_f32(inv_1, one_over_det)); 
        vst1q_f32(&ret[2][0], vmulq_f32(inv_2, one_over_det)); 
        vst1q_f32(&ret[3][0], vmulq_f32(inv_3, one_over_det)); 

        return ret;
    }
};

#elif defined(CHTHOLLY_SIMD_SSE)

template<>
struct ktm::detail::mat_common_implement::transpose<3, 3, float>
{
    using M = mat<3, 3, float>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        __m128 c_0 = _mm_load_ps(&m[0][0]);
        __m128 c_1 = _mm_load_ps(&m[1][0]);
        __m128 c_2 = _mm_load_ps(&m[2][0]);

        __m128 tmp_0 = _mm_shuffle_ps(c_0, c_1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 tmp_1 = _mm_shuffle_ps(c_0, c_1, _MM_SHUFFLE(3, 2, 3, 2));

        __m128 ret_0 = _mm_shuffle_ps(tmp_0, c_2, _MM_SHUFFLE(3, 0, 2, 0));
        __m128 ret_1 = _mm_shuffle_ps(tmp_0, c_2, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 ret_2 = _mm_shuffle_ps(tmp_1, c_2, _MM_SHUFFLE(3, 2, 2, 0));

        RetM ret;
        _mm_store_ps(&ret[0][0], ret_0);
        _mm_store_ps(&ret[1][0], ret_1);
        _mm_store_ps(&ret[2][0], ret_2);
        return ret; 
    }
};

template<>
struct ktm::detail::mat_common_implement::transpose<4, 4, float>
{
    using M = mat<4, 4, float>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        __m128 c_0 = _mm_load_ps(&m[0][0]);
        __m128 c_1 = _mm_load_ps(&m[1][0]);
        __m128 c_2 = _mm_load_ps(&m[2][0]);
        __m128 c_3 = _mm_load_ps(&m[3][0]);

        __m128 tmp_0 = _mm_shuffle_ps(c_0, c_1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 tmp_2 = _mm_shuffle_ps(c_0, c_1, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 tmp_1 = _mm_shuffle_ps(c_2, c_3, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 tmp_3 = _mm_shuffle_ps(c_2, c_3, _MM_SHUFFLE(3, 2, 3, 2));

        __m128 ret_0 = _mm_shuffle_ps(tmp_0, tmp_1, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 ret_1 = _mm_shuffle_ps(tmp_0, tmp_1, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 ret_2 = _mm_shuffle_ps(tmp_2, tmp_3, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 ret_3 = _mm_shuffle_ps(tmp_2, tmp_3, _MM_SHUFFLE(3, 1, 3, 1));

        RetM ret;
        _mm_store_ps(&ret[0][0], ret_0);
        _mm_store_ps(&ret[1][0], ret_1);
        _mm_store_ps(&ret[2][0], ret_2);
        _mm_store_ps(&ret[3][0], ret_3);
        return ret;
    }
};

template<>
struct ktm::detail::mat_common_implement::transpose<3, 3, int>
{
    using M = mat<3, 3, int>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        __m128 c_0 = _mm_load_ps(reinterpret_cast<const float*>(&m[0][0]));
        __m128 c_1 = _mm_load_ps(reinterpret_cast<const float*>(&m[1][0]));
        __m128 c_2 = _mm_load_ps(reinterpret_cast<const float*>(&m[2][0]));

        __m128 tmp_0 = _mm_shuffle_ps(c_0, c_1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 tmp_1 = _mm_shuffle_ps(c_0, c_1, _MM_SHUFFLE(3, 2, 3, 2));

        __m128 ret_0 = _mm_shuffle_ps(tmp_0, c_2, _MM_SHUFFLE(3, 0, 2, 0));
        __m128 ret_1 = _mm_shuffle_ps(tmp_0, c_2, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 ret_2 = _mm_shuffle_ps(tmp_1, c_2, _MM_SHUFFLE(3, 2, 2, 0));

        RetM ret;
        _mm_store_ps(reinterpret_cast<float*>(&ret[0][0]), ret_0);
        _mm_store_ps(reinterpret_cast<float*>(&ret[1][0]), ret_1);
        _mm_store_ps(reinterpret_cast<float*>(&ret[2][0]), ret_2);
        return ret; 
    }
};

template<>
struct ktm::detail::mat_common_implement::transpose<4, 4, int>
{
    using M = mat<4, 4, int>;
    using RetM = mat_traits_tp_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        __m128 c_0 = _mm_load_ps(reinterpret_cast<const float*>(&m[0][0]));
        __m128 c_1 = _mm_load_ps(reinterpret_cast<const float*>(&m[1][0]));
        __m128 c_2 = _mm_load_ps(reinterpret_cast<const float*>(&m[2][0]));
        __m128 c_3 = _mm_load_ps(reinterpret_cast<const float*>(&m[3][0]));

        __m128 tmp_0 = _mm_shuffle_ps(c_0, c_1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 tmp_2 = _mm_shuffle_ps(c_0, c_1, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 tmp_1 = _mm_shuffle_ps(c_2, c_3, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 tmp_3 = _mm_shuffle_ps(c_2, c_3, _MM_SHUFFLE(3, 2, 3, 2));

        __m128 ret_0 = _mm_shuffle_ps(tmp_0, tmp_1, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 ret_1 = _mm_shuffle_ps(tmp_0, tmp_1, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 ret_2 = _mm_shuffle_ps(tmp_2, tmp_3, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 ret_3 = _mm_shuffle_ps(tmp_2, tmp_3, _MM_SHUFFLE(3, 1, 3, 1));

        RetM ret;
        _mm_store_ps(reinterpret_cast<float*>(&ret[0][0]), ret_0);
        _mm_store_ps(reinterpret_cast<float*>(&ret[1][0]), ret_1);
        _mm_store_ps(reinterpret_cast<float*>(&ret[2][0]), ret_2);
        _mm_store_ps(reinterpret_cast<float*>(&ret[3][0]), ret_3);
        return ret;
    }
};

template<>
struct ktm::detail::mat_common_implement::determinant<3, float>
{
    using M = mat<3, 3, float>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        __m128 c_0 = _mm_load_ps(&m[0][0]);
        __m128 c_1 = _mm_load_ps(&m[1][0]);
        __m128 c_2 = _mm_load_ps(&m[2][0]);
        __m128 mul_00 = _mm_mul_ps(_mm_shuffle_ps(c_1, c_1, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(c_2, c_2, _MM_SHUFFLE(3, 1, 0, 2)));
        __m128 mul_01 = _mm_mul_ps(_mm_shuffle_ps(c_1, c_1, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(c_2, c_2, _MM_SHUFFLE(3, 0, 2, 1)));
        __m128 sub_0 = _mm_sub_ps(mul_00, mul_01);  
        __m128 mul_0 = _mm_mul_ps(c_0, sub_0);

        __m128 sum_0 = _mm_add_ss(mul_0, _mm_shuffle_ps(mul_0, mul_0, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128 sum_1 = _mm_add_ss(sum_0, _mm_shuffle_ps(mul_0, mul_0, _MM_SHUFFLE(1, 0, 3, 2)));
        return *reinterpret_cast<float*>(&sum_1); 
    }
};

template<>
struct ktm::detail::mat_common_implement::determinant<4, float>
{
    using M = mat<4, 4, float>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        __m128 c_0 = _mm_load_ps(&m[0][0]);
        __m128 c_1 = _mm_load_ps(&m[1][0]);
        __m128 c_2 = _mm_load_ps(&m[2][0]);
        __m128 c_3 = _mm_load_ps(&m[3][0]);

        __m128 mul_0;
        {
            __m128 mul_00 = _mm_mul_ps(_mm_shuffle_ps(c_2, c_2, _MM_SHUFFLE(1, 0, 3, 2)), _mm_shuffle_ps(c_3, c_3, _MM_SHUFFLE(2, 1, 0, 3)));
            __m128 mul_01 = _mm_mul_ps(_mm_shuffle_ps(c_2, c_2, _MM_SHUFFLE(2, 1, 0, 3)), _mm_shuffle_ps(c_3, c_3, _MM_SHUFFLE(1, 0, 3, 2)));
            __m128 sub_0 = _mm_sub_ps(mul_00, mul_01);
            mul_0 = _mm_mul_ps(_mm_shuffle_ps(c_1, c_1, _MM_SHUFFLE(0, 3, 2, 1)), sub_0);
        }

        __m128 mul_1;
        {
            __m128 mul_00 = _mm_mul_ps(_mm_shuffle_ps(c_2, c_2, _MM_SHUFFLE(2, 1, 0, 3)), _mm_shuffle_ps(c_3, c_3, _MM_SHUFFLE(0, 3, 2, 1)));
            __m128 mul_01 = _mm_mul_ps(_mm_shuffle_ps(c_2, c_2, _MM_SHUFFLE(0, 3, 2, 1)), _mm_shuffle_ps(c_3, c_3, _MM_SHUFFLE(2, 1, 0, 3)));
            __m128 sub_0 = _mm_sub_ps(mul_00, mul_01);
            mul_1 = _mm_mul_ps(_mm_shuffle_ps(c_1, c_1, _MM_SHUFFLE(1, 0, 3, 2)), sub_0);
        }

        __m128 mul_2;
        {
            __m128 mul_00 = _mm_mul_ps(_mm_shuffle_ps(c_2, c_2, _MM_SHUFFLE(0, 3, 2, 1)), _mm_shuffle_ps(c_3, c_3, _MM_SHUFFLE(1, 0, 3, 2)));
            __m128 mul_01 = _mm_mul_ps(_mm_shuffle_ps(c_2, c_2, _MM_SHUFFLE(1, 0, 3, 2)), _mm_shuffle_ps(c_3, c_3, _MM_SHUFFLE(0, 3, 2, 1)));
            __m128 sub_0 = _mm_sub_ps(mul_00, mul_01);
            mul_2 = _mm_mul_ps(_mm_shuffle_ps(c_1, c_1, _MM_SHUFFLE(2, 1, 0, 3)), sub_0);
        }

        __m128 mul_3 = _mm_mul_ps(c_0, _mm_add_ps(_mm_add_ps(mul_0, mul_1), mul_2)); 
        mul_3 = _mm_shuffle_ps(mul_3, mul_3, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 sub_0 = _mm_sub_ps(mul_3, _mm_shuffle_ps(mul_3, mul_3, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128 sum_0 = _mm_add_ss(sub_0, _mm_shuffle_ps(sub_0, sub_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return *reinterpret_cast<float*>(&sum_0);
    }
};

template<>
struct ktm::detail::mat_common_implement::inverse<4, float>
{
    using M = mat<4, 4, float>;
    static CHTHOLLY_INLINE M call(const M& m) noexcept
    {
        __m128 c_0 = _mm_load_ps(&m[0][0]);
        __m128 c_1 = _mm_load_ps(&m[1][0]);
        __m128 c_2 = _mm_load_ps(&m[2][0]);
        __m128 c_3 = _mm_load_ps(&m[3][0]);

        __m128 fac_0;
        {
            __m128 swp_0a = _mm_shuffle_ps(c_3, c_2, _MM_SHUFFLE(3, 3, 3, 3));
            __m128 swp_0b = _mm_shuffle_ps(c_3, c_2, _MM_SHUFFLE(2, 2, 2, 2));

            __m128 swp_00 = _mm_shuffle_ps(c_2, c_1, _MM_SHUFFLE(2, 2, 2, 2));
            __m128 swp_01 = _mm_shuffle_ps(swp_0a, swp_0a, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_02 = _mm_shuffle_ps(swp_0b, swp_0b, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_03 = _mm_shuffle_ps(c_2, c_1, _MM_SHUFFLE(3, 3, 3, 3));

            __m128 mul_00 = _mm_mul_ps(swp_00, swp_01);
            __m128 mul_01 = _mm_mul_ps(swp_02, swp_03);
            fac_0 = _mm_sub_ps(mul_00, mul_01);
        }

        __m128 fac_1;
        {
            __m128 swp_0a = _mm_shuffle_ps(c_3, c_2, _MM_SHUFFLE(3, 3, 3, 3));
            __m128 swp_0b = _mm_shuffle_ps(c_3, c_2, _MM_SHUFFLE(1, 1, 1, 1));

            __m128 swp_00 = _mm_shuffle_ps(c_2, c_1, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 swp_01 = _mm_shuffle_ps(swp_0a, swp_0a, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_02 = _mm_shuffle_ps(swp_0b, swp_0b, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_03 = _mm_shuffle_ps(c_2, c_1, _MM_SHUFFLE(3, 3, 3, 3));

            __m128 mul_00 = _mm_mul_ps(swp_00, swp_01);
            __m128 mul_01 = _mm_mul_ps(swp_02, swp_03);
            fac_1 = _mm_sub_ps(mul_00, mul_01);
        }

        __m128 fac_2;
        {
            __m128 swp_0a = _mm_shuffle_ps(c_3, c_2, _MM_SHUFFLE(2, 2, 2, 2));
            __m128 swp_0b = _mm_shuffle_ps(c_3, c_2, _MM_SHUFFLE(1, 1, 1, 1));

            __m128 swp_00 = _mm_shuffle_ps(c_2, c_1, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 swp_01 = _mm_shuffle_ps(swp_0a, swp_0a, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_02 = _mm_shuffle_ps(swp_0b, swp_0b, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_03 = _mm_shuffle_ps(c_2, c_1, _MM_SHUFFLE(2, 2, 2, 2));

            __m128 mul_00 = _mm_mul_ps(swp_00, swp_01);
            __m128 mul_01 = _mm_mul_ps(swp_02, swp_03);
            fac_2 = _mm_sub_ps(mul_00, mul_01);
        }

        __m128 fac_3;
        {
            __m128 swp_0a = _mm_shuffle_ps(c_3, c_2, _MM_SHUFFLE(3, 3, 3, 3));
            __m128 swp_0b = _mm_shuffle_ps(c_3, c_2, 0);

            __m128 swp_00 = _mm_shuffle_ps(c_2, c_1, 0);
            __m128 swp_01 = _mm_shuffle_ps(swp_0a, swp_0a, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_02 = _mm_shuffle_ps(swp_0b, swp_0b, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_03 = _mm_shuffle_ps(c_2, c_1, _MM_SHUFFLE(3, 3, 3, 3));

            __m128 mul_00 = _mm_mul_ps(swp_00, swp_01);
            __m128 mul_01 = _mm_mul_ps(swp_02, swp_03);
            fac_3 = _mm_sub_ps(mul_00, mul_01);
        }

        __m128 fac_4;
        {
            __m128 swp_0a = _mm_shuffle_ps(c_3, c_2, _MM_SHUFFLE(2, 2, 2, 2));
            __m128 swp_0b = _mm_shuffle_ps(c_3, c_2, 0);

            __m128 swp_00 = _mm_shuffle_ps(c_2, c_1, 0);
            __m128 swp_01 = _mm_shuffle_ps(swp_0a, swp_0a, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_02 = _mm_shuffle_ps(swp_0b, swp_0b, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_03 = _mm_shuffle_ps(c_2, c_1, _MM_SHUFFLE(2, 2, 2, 2));

            __m128 mul_00 = _mm_mul_ps(swp_00, swp_01);
            __m128 mul_01 = _mm_mul_ps(swp_02, swp_03);
            fac_4 = _mm_sub_ps(mul_00, mul_01);
        }

        __m128 fac_5;
        {
            __m128 swp_0a = _mm_shuffle_ps(c_3, c_2, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 swp_0b = _mm_shuffle_ps(c_3, c_2, 0);

            __m128 swp_00 = _mm_shuffle_ps(c_2, c_1, 0);
            __m128 swp_01 = _mm_shuffle_ps(swp_0a, swp_0a, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_02 = _mm_shuffle_ps(swp_0b, swp_0b, _MM_SHUFFLE(2, 0, 0, 0));
            __m128 swp_03 = _mm_shuffle_ps(c_2, c_1, _MM_SHUFFLE(1, 1, 1, 1));

            __m128 mul_00 = _mm_mul_ps(swp_00, swp_01);
            __m128 mul_01 = _mm_mul_ps(swp_02, swp_03);
            fac_5 = _mm_sub_ps(mul_00, mul_01);
        }

        __m128 sign_a = _mm_set_ps(one<float>, -one<float>, one<float>, -one<float>);
        __m128 sign_b = _mm_set_ps(-one<float>, one<float>, -one<float>, one<float>);

        // v_0 = { m[1][0], m[0][0], m[0][0], m[0][0] }
        __m128 tmp_0 = _mm_shuffle_ps(c_1, c_0, 0);
        __m128 v_0 = _mm_shuffle_ps(tmp_0, tmp_0,  _MM_SHUFFLE(2, 2, 2, 0));

        // v_0 = { m[1][1], m[0][1], m[0][1], m[0][1] }
        __m128 tmp_1 = _mm_shuffle_ps(c_1, c_0, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 v_1 = _mm_shuffle_ps(tmp_1, tmp_1,  _MM_SHUFFLE(2, 2, 2, 0));

        // v_0 = { m[1][2], m[0][2], m[0][2], m[0][2] }
        __m128 tmp_2 = _mm_shuffle_ps(c_1, c_0, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 v_2 = _mm_shuffle_ps(tmp_2, tmp_2,  _MM_SHUFFLE(2, 2, 2, 0));

        // v_0 = { m[1][3], m[0][3], m[0][3], m[0][3] }
        __m128 tmp_3 = _mm_shuffle_ps(c_1, c_0, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 v_3 = _mm_shuffle_ps(tmp_3, tmp_3,  _MM_SHUFFLE(2, 2, 2, 0));

        // inv_0
        // + (v_1[0] * fac_0[0] - v_2[0] * fac_1[0] + v_3[0] * fac_2[0])
        // - (v_1[1] * fac_0[1] - v_2[1] * fac_1[1] + v_3[1] * fac_2[1])
        // + (v_1[2] * fac_0[2] - v_2[2] * fac_1[2] + v_3[2] * fac_2[2])
        // - (v_1[3] * fac_0[3] - v_2[3] * fac_1[3] + v_3[3] * fac_2[3])
        __m128 inv_0; 
        {
            // sign_b * (v_1 * fac_0 - v_2 * fac_1 + v_3 * fac_2)
            __m128 mul_00 = _mm_mul_ps(v_1, fac_0);
            __m128 mul_01 = _mm_mul_ps(v_2, fac_1); 
            __m128 mul_02 = _mm_mul_ps(v_3, fac_2);
            __m128 sum_0 = _mm_add_ps(_mm_sub_ps(mul_00, mul_01), mul_02);
            inv_0 = _mm_mul_ps(sign_b, sum_0);
        }

        // inv_1
        // - (v_0[0] * fac_0[0] - v_2[0] * fac_3[0] + v_3[0] * fac_4[0])
        // + (v_0[0] * fac_0[1] - v_2[1] * fac_3[1] + v_3[1] * fac_4[1])
        // - (v_0[0] * fac_0[2] - v_2[2] * fac_3[2] + v_3[2] * fac_4[2])
        // + (v_0[0] * fac_0[3] - v_2[3] * fac_3[3] + v_3[3] * fac_4[3])
        __m128 inv_1;
        {
            // sign_a * (v_0 * fac_0 - v_2 * fac_3 + v_3 * fac_4)
            __m128 mul_00 = _mm_mul_ps(v_0, fac_0);
            __m128 mul_01 = _mm_mul_ps(v_2, fac_3); 
            __m128 mul_02 = _mm_mul_ps(v_3, fac_4);
            __m128 sum_0 = _mm_add_ps(_mm_sub_ps(mul_00, mul_01), mul_02);
            inv_1 = _mm_mul_ps(sign_a, sum_0);
        }

        // inv_2
        // + (v_0[0] * fac_1[0] - v_1[0] * fac_3[0] + v_3[0] * fac_5[0])
        // - (v_0[0] * fac_1[1] - v_1[1] * fac_3[1] + v_3[1] * fac_5[1])
        // + (v_0[0] * fac_1[2] - v_1[2] * fac_3[2] + v_3[2] * fac_5[2])
        // - (v_0[0] * fac_1[3] - v_1[3] * fac_3[3] + v_3[3] * fac_5[3])
        __m128 inv_2;
        {
            // sign_b * (v_0 * fac_1 - v_1 * fac_3 + v_3 * fac_5)
            __m128 mul_00 = _mm_mul_ps(v_0, fac_1);
            __m128 mul_01 = _mm_mul_ps(v_1, fac_3); 
            __m128 mul_02 = _mm_mul_ps(v_3, fac_5);
            __m128 sum_0 = _mm_add_ps(_mm_sub_ps(mul_00, mul_01), mul_02);
            inv_2 = _mm_mul_ps(sign_b, sum_0);
        }

        // inv_3
        // - (v_0[0] * fac_2[0] - v_1[0] * fac_4[0] + v_2[0] * fac_5[0])
        // + (v_0[0] * fac_2[1] - v_1[1] * fac_4[1] + v_2[1] * fac_5[1])
        // - (v_0[0] * fac_2[2] - v_1[2] * fac_4[2] + v_2[2] * fac_5[2])
        // + (v_0[0] * fac_2[3] - v_1[3] * fac_4[3] + v_2[3] * fac_5[3])
        __m128 inv_3;
        {
            // sign_a * (v_0 * fac_2 - v_1 * fac_4 + v_2 * fac_5)
            __m128 mul_00 = _mm_mul_ps(v_0, fac_2);
            __m128 mul_01 = _mm_mul_ps(v_1, fac_4); 
            __m128 mul_02 = _mm_mul_ps(v_2, fac_5);
            __m128 sum_0 = _mm_add_ps(_mm_sub_ps(mul_00, mul_01), mul_02);
            inv_3 = _mm_mul_ps(sign_a, sum_0);
        }

        // det
        // + m[0][0] * Inverse[0][0]
        // + m[0][1] * Inverse[1][0]
        // + m[0][2] * Inverse[2][0]
        // + m[0][3] * Inverse[3][0];
        __m128 i_tmp_0 = _mm_shuffle_ps(inv_0, inv_1, 0);
        __m128 i_tmp_1 = _mm_shuffle_ps(inv_2, inv_3, 0);
        __m128 i_row_0 = _mm_shuffle_ps(i_tmp_0, i_tmp_1,  _MM_SHUFFLE(3, 1, 3, 1));
        __m128 i_mul_0 = _mm_mul_ps(c_0, i_row_0);

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE3_FLAG
		__m128 i_add_0 = _mm_hadd_ps(i_mul_0, i_mul_0);;
		__m128 i_add_1 = _mm_hadd_ps(i_add_0, i_add_0);;
#else
        __m128 i_add_0 = _mm_add_ps(i_mul_0, _mm_shuffle_ps(i_mul_0, i_mul_0, _MM_SHUFFLE(2, 3, 0, 1)));
		__m128 i_add_1 = _mm_add_ps(i_add_0, _mm_shuffle_ps(i_add_0, i_add_0, _MM_SHUFFLE(0, 1, 2, 3))); 
#endif
        __m128 one_over_det = _mm_div_ps(_mm_set1_ps(one<float>), i_add_1);

        M ret;

        _mm_store_ps(&ret[0][0], _mm_mul_ps(inv_0, one_over_det)); 
        _mm_store_ps(&ret[1][0], _mm_mul_ps(inv_1, one_over_det)); 
        _mm_store_ps(&ret[2][0], _mm_mul_ps(inv_2, one_over_det)); 
        _mm_store_ps(&ret[3][0], _mm_mul_ps(inv_3, one_over_det)); 

        return ret;
    }
};

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

template<>
struct ktm::detail::mat_common_implement::determinant<3, int>
{
    using M = mat<3, 3, int>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        __m128i c_0 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m[0][0]));
        __m128i c_1 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m[1][0]));
        __m128i c_2 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m[2][0]));
        __m128i mul_00 = _mm_mullo_epi32(_mm_shuffle_epi32(c_1, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_epi32(c_2, _MM_SHUFFLE(3, 1, 0, 2)));
        __m128i mul_01 = _mm_mullo_epi32(_mm_shuffle_epi32(c_1, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_epi32(c_2, _MM_SHUFFLE(3, 0, 2, 1)));
        __m128i sub_0 = _mm_sub_epi32(mul_00, mul_01);  
        __m128i mul_0 = _mm_mullo_epi32(c_0, sub_0);

        __m128i sum_0 = _mm_add_epi32(mul_0, _mm_shuffle_epi32(mul_0, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128i sum_1 = _mm_add_epi32(sum_0, _mm_shuffle_epi32(mul_0, _MM_SHUFFLE(1, 0, 3, 2)));
        return *reinterpret_cast<int*>(&sum_1); 
    }
};

template<>
struct ktm::detail::mat_common_implement::determinant<4, int>
{
    using M = mat<4, 4, int>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        __m128i c_0 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m[0][0]));
        __m128i c_1 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m[1][0]));
        __m128i c_2 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m[2][0]));
        __m128i c_3 = _mm_load_si128(reinterpret_cast<const __m128i*>(&m[3][0]));

        __m128i mul_0;
        {
            __m128i mul_00 = _mm_mullo_epi32(_mm_shuffle_epi32(c_2, _MM_SHUFFLE(1, 0, 3, 2)), _mm_shuffle_epi32(c_3, _MM_SHUFFLE(2, 1, 0, 3)));
            __m128i mul_01 = _mm_mullo_epi32(_mm_shuffle_epi32(c_2, _MM_SHUFFLE(2, 1, 0, 3)), _mm_shuffle_epi32(c_3, _MM_SHUFFLE(1, 0, 3, 2)));
            __m128i sub_0 = _mm_sub_epi32(mul_00, mul_01);
            mul_0 = _mm_mullo_epi32(_mm_shuffle_epi32(c_1, _MM_SHUFFLE(0, 3, 2, 1)), sub_0);
        }

        __m128i mul_1;
        {
            __m128i mul_00 = _mm_mullo_epi32(_mm_shuffle_epi32(c_2, _MM_SHUFFLE(2, 1, 0, 3)), _mm_shuffle_epi32(c_3, _MM_SHUFFLE(0, 3, 2, 1)));
            __m128i mul_01 = _mm_mullo_epi32(_mm_shuffle_epi32(c_2, _MM_SHUFFLE(0, 3, 2, 1)), _mm_shuffle_epi32(c_3, _MM_SHUFFLE(2, 1, 0, 3)));
            __m128i sub_0 = _mm_sub_epi32(mul_00, mul_01);
            mul_1 = _mm_mullo_epi32(_mm_shuffle_epi32(c_1, _MM_SHUFFLE(1, 0, 3, 2)), sub_0);
        }

        __m128i mul_2;
        {
            __m128i mul_00 = _mm_mullo_epi32(_mm_shuffle_epi32(c_2, _MM_SHUFFLE(0, 3, 2, 1)), _mm_shuffle_epi32(c_3, _MM_SHUFFLE(1, 0, 3, 2)));
            __m128i mul_01 = _mm_mullo_epi32(_mm_shuffle_epi32(c_2, _MM_SHUFFLE(1, 0, 3, 2)), _mm_shuffle_epi32(c_3, _MM_SHUFFLE(0, 3, 2, 1)));
            __m128i sub_0 = _mm_sub_epi32(mul_00, mul_01);
            mul_2 = _mm_mullo_epi32(_mm_shuffle_epi32(c_1, _MM_SHUFFLE(2, 1, 0, 3)), sub_0);
        }

        __m128i mul_3 = _mm_mullo_epi32(c_0, _mm_add_epi32(_mm_add_epi32(mul_0, mul_1), mul_2)); 
        mul_3 = _mm_shuffle_epi32(mul_3, _MM_SHUFFLE(3, 1, 2, 0));
        __m128i sub_0 = _mm_sub_epi32(mul_3, _mm_shuffle_epi32(mul_3, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128i sum_0 = _mm_add_epi32(sub_0, _mm_shuffle_epi32(sub_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return *reinterpret_cast<int*>(&sum_0);
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG 

#endif

#endif
