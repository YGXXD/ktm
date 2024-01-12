#ifndef _KTM_MATRIX_SIMD_INL_
#define _KTM_MATRIX_SIMD_INL_

#include "matrix_fwd.h"
#include "../../simd/intrin.h"
#include "../../type/basic.h"
#include "../../type/mat_fwd.h"

#if defined(KTM_SIMD_NEON)

template<>
struct ktm::detail::matrix_implement::transpose<2, 2, float>
{
    using M = mat<2, 2, float>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        neon::mt::fmt2_tp(&ret[0].st, &m[0].st);
        return ret;
    }
};

template<>
struct ktm::detail::matrix_implement::transpose<3, 3, float>
{
    using M = mat<3, 3, float>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        neon::mt::fmt3_tp(&ret[0].st, &m[0].st);
        return ret;
    }
};

template<>
struct ktm::detail::matrix_implement::transpose<4, 4, float>
{
    using M = mat<4, 4, float>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        neon::mt::fmt4_tp(&ret[0].st, &m[0].st);
        return ret;
    }
};

template<>
struct ktm::detail::matrix_implement::transpose<2, 2, int>
{
    using M = mat<2, 2, int>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        neon::mt::fmt2_tp(reinterpret_cast<float32x2_t*>(&ret[0].st), reinterpret_cast<const float32x2_t*>(&m[0].st));
        return ret;
    }
};

template<>
struct ktm::detail::matrix_implement::transpose<3, 3, int>
{
    using M = mat<3, 3, int>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        neon::mt::fmt3_tp(reinterpret_cast<float32x4_t*>(&ret[0].st), reinterpret_cast<const float32x4_t*>(&m[0].st));
        return ret; 
    }
};

template<>
struct ktm::detail::matrix_implement::transpose<4, 4, int>
{
    using M = mat<4, 4, int>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        neon::mt::fmt4_tp(reinterpret_cast<float32x4_t*>(&ret[0].st), reinterpret_cast<const float32x4_t*>(&m[0].st));
        return ret; 
    }
};

template<>
struct ktm::detail::matrix_implement::determinant<3, float>
{
    using M = mat<3, 3, float>;
    static KTM_INLINE float call(const M& m) noexcept
    {
        const float32x4_t& c_0 = m[0].st;
        const float32x4_t& c_1 = m[1].st;
        const float32x4_t& c_2 = m[2].st;
        float32x4_t mul_00 = vmulq_f32(neon_shuffleq_f32(c_1, c_1, 3, 0, 2, 1), neon_shuffleq_f32(c_2, c_2, 3, 1, 0, 2));
        float32x4_t mul_01 = vmulq_f32(neon_shuffleq_f32(c_1, c_1, 3, 1, 0, 2), neon_shuffleq_f32(c_2, c_2, 3, 0, 2, 1));
        float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);  
        return neon::geo::fv3_dot1(c_0, sub_0);
    }
};

template<>
struct ktm::detail::matrix_implement::determinant<4, float>
{
    using M = mat<4, 4, float>;
    static KTM_INLINE float call(const M& m) noexcept
    {
        const float32x4_t& c_0 = m[0].st;
        const float32x4_t& c_1 = m[1].st;
        const float32x4_t& c_2 = m[2].st;
        const float32x4_t& c_3 = m[3].st;

        float32x4_t mul_0;
        {
            float32x4_t mul_00 = vmulq_f32(neon_shuffleq_f32(c_2, c_2, 1, 0, 3, 2), neon_shuffleq_f32(c_3, c_3, 2, 1, 0, 3));
            float32x4_t mul_01 = vmulq_f32(neon_shuffleq_f32(c_2, c_2, 2, 1, 0, 3), neon_shuffleq_f32(c_3, c_3, 1, 0, 3, 2));
            float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);
            mul_0 = vmulq_f32(neon_shuffleq_f32(c_1, c_1, 0, 3, 2, 1), sub_0);
        }

        float32x4_t mul_1;
        {
            float32x4_t mul_00 = vmulq_f32(neon_shuffleq_f32(c_2, c_2, 2, 1, 0, 3), neon_shuffleq_f32(c_3, c_3, 0, 3, 2, 1));
            float32x4_t mul_01 = vmulq_f32(neon_shuffleq_f32(c_2, c_2, 0, 3, 2, 1), neon_shuffleq_f32(c_3, c_3, 2, 1, 0, 3));
            float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);
            mul_1 = vmulq_f32(neon_shuffleq_f32(c_1, c_1, 1, 0, 3, 2), sub_0);
        }

        float32x4_t mul_2;
        {
            float32x4_t mul_00 = vmulq_f32(neon_shuffleq_f32(c_2, c_2, 0, 3, 2, 1), neon_shuffleq_f32(c_3, c_3, 1, 0, 3, 2));
            float32x4_t mul_01 = vmulq_f32(neon_shuffleq_f32(c_2, c_2, 1, 0, 3, 2), neon_shuffleq_f32(c_3, c_3, 0, 3, 2, 1));
            float32x4_t sub_0 = vsubq_f32(mul_00, mul_01);
            mul_2 = vmulq_f32(neon_shuffleq_f32(c_1, c_1, 2, 1, 0, 3), sub_0);
        }

        float32x4_t mul_3 = vmulq_f32(c_0, vaddq_f32(vaddq_f32(mul_0, mul_1), mul_2)); 
        mul_3 = neon_shuffleq_f32(mul_3, mul_3, 3, 1, 2, 0);
        return vaddv_f32(vsub_f32(vget_low_f32(mul_3), vget_high_f32(mul_3)));
    }
};

template<>
struct ktm::detail::matrix_implement::determinant<3, int>
{
    using M = mat<3, 3, int>;
    static KTM_INLINE float call(const M& m) noexcept
    {
        const int32x4_t& c_0 = m[0].st;
        const int32x4_t& c_1 = m[1].st;
        const int32x4_t& c_2 = m[2].st;
        int32x4_t mul_00 = vmulq_s32(neon_shuffleq_s32(c_1, c_1, 3, 0, 2, 1), neon_shuffleq_s32(c_2, c_2, 3, 1, 0, 2));
        int32x4_t mul_01 = vmulq_s32(neon_shuffleq_s32(c_1, c_1, 3, 1, 0, 2), neon_shuffleq_s32(c_2, c_2, 3, 0, 2, 1));
        int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);  
        return neon::geo::sv3_dot1(c_0, sub_0);
    }
};

template<>
struct ktm::detail::matrix_implement::determinant<4, int>
{
    using M = mat<4, 4, int>;
    static KTM_INLINE float call(const M& m) noexcept
    {
        const int32x4_t& c_0 = m[0].st;
        const int32x4_t& c_1 = m[1].st;
        const int32x4_t& c_2 = m[2].st;
        const int32x4_t& c_3 = m[3].st;

        int32x4_t mul_0;
        {
            int32x4_t mul_00 = vmulq_s32(neon_shuffleq_s32(c_2, c_2, 1, 0, 3, 2), neon_shuffleq_s32(c_3, c_3, 2, 1, 0, 3));
            int32x4_t mul_01 = vmulq_s32(neon_shuffleq_s32(c_2, c_2, 2, 1, 0, 3), neon_shuffleq_s32(c_3, c_3, 1, 0, 3, 2));
            int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);
            mul_0 = vmulq_s32(neon_shuffleq_s32(c_1, c_1, 0, 3, 2, 1), sub_0);
        }

        int32x4_t mul_1;
        {
            int32x4_t mul_00 = vmulq_s32(neon_shuffleq_s32(c_2, c_2, 2, 1, 0, 3), neon_shuffleq_s32(c_3, c_3, 0, 3, 2, 1));
            int32x4_t mul_01 = vmulq_s32(neon_shuffleq_s32(c_2, c_2, 0, 3, 2, 1), neon_shuffleq_s32(c_3, c_3, 2, 1, 0, 3));
            int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);
            mul_1 = vmulq_s32(neon_shuffleq_s32(c_1, c_1, 1, 0, 3, 2), sub_0);
        }

        int32x4_t mul_2;
        {
            int32x4_t mul_00 = vmulq_s32(neon_shuffleq_s32(c_2, c_2, 0, 3, 2, 1), neon_shuffleq_s32(c_3, c_3, 1, 0, 3, 2));
            int32x4_t mul_01 = vmulq_s32(neon_shuffleq_s32(c_2, c_2, 1, 0, 3, 2), neon_shuffleq_s32(c_3, c_3, 0, 3, 2, 1));
            int32x4_t sub_0 = vsubq_s32(mul_00, mul_01);
            mul_2 = vmulq_s32(neon_shuffleq_s32(c_1, c_1, 2, 1, 0, 3), sub_0);
        }

        int32x4_t mul_3 = vmulq_s32(c_0, vaddq_s32(vaddq_s32(mul_0, mul_1), mul_2)); 
        mul_3 = neon_shuffleq_s32(mul_3, mul_3, 3, 1, 2, 0);
        return vaddv_s32(vsub_s32(vget_low_s32(mul_3), vget_high_s32(mul_3)));
    }
};

template<>
struct ktm::detail::matrix_implement::inverse<4, float>
{
    using M = mat<4, 4, float>;
    static KTM_INLINE M call(const M& m) noexcept
    {
        const float32x4_t& c_0 = m[0].st;
        const float32x4_t& c_1 = m[1].st;
        const float32x4_t& c_2 = m[2].st;
        const float32x4_t& c_3 = m[3].st;

        float32x4_t fac_0;
        {
            float32x4_t swp_0a = neon_shuffleq_f32(c_3, c_2, 3, 3, 3, 3);
            float32x4_t swp_0b = neon_shuffleq_f32(c_3, c_2, 2, 2, 2, 2);

            float32x4_t swp_00 = neon_shuffleq_f32(c_2, c_1, 2, 2, 2, 2);
            float32x4_t swp_01 = neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = neon_shuffleq_f32(c_2, c_1, 3, 3, 3, 3);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_0 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_1;
        {
            float32x4_t swp_0a = neon_shuffleq_f32(c_3, c_2, 3, 3, 3, 3);
            float32x4_t swp_0b = neon_shuffleq_f32(c_3, c_2, 1, 1, 1, 1);

            float32x4_t swp_00 = neon_shuffleq_f32(c_2, c_1, 1, 1, 1, 1);
            float32x4_t swp_01 = neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = neon_shuffleq_f32(c_2, c_1, 3, 3, 3, 3);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_1 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_2;
        {
            float32x4_t swp_0a = neon_shuffleq_f32(c_3, c_2, 2, 2, 2, 2);
            float32x4_t swp_0b = neon_shuffleq_f32(c_3, c_2, 1, 1, 1, 1);

            float32x4_t swp_00 = neon_shuffleq_f32(c_2, c_1, 1, 1, 1, 1);
            float32x4_t swp_01 = neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = neon_shuffleq_f32(c_2, c_1, 2, 2, 2, 2);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_2 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_3;
        {
            float32x4_t swp_0a = neon_shuffleq_f32(c_3, c_2, 3, 3, 3, 3);
            float32x4_t swp_0b = neon_shuffleq_f32(c_3, c_2, 0, 0, 0, 0);

            float32x4_t swp_00 = neon_shuffleq_f32(c_2, c_1, 0, 0, 0, 0);
            float32x4_t swp_01 = neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = neon_shuffleq_f32(c_2, c_1, 3, 3, 3, 3);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_3 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_4;
        {
            float32x4_t swp_0a = neon_shuffleq_f32(c_3, c_2, 2, 2, 2, 2);
            float32x4_t swp_0b = neon_shuffleq_f32(c_3, c_2, 0, 0, 0, 0);

            float32x4_t swp_00 = neon_shuffleq_f32(c_2, c_1, 0, 0, 0, 0);
            float32x4_t swp_01 = neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = neon_shuffleq_f32(c_2, c_1, 2, 2, 2, 2);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_4 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t fac_5;
        {
            float32x4_t swp_0a = neon_shuffleq_f32(c_3, c_2, 1, 1, 1, 1);
            float32x4_t swp_0b = neon_shuffleq_f32(c_3, c_2, 0, 0, 0, 0);

            float32x4_t swp_00 = neon_shuffleq_f32(c_2, c_1, 0, 0, 0, 0);
            float32x4_t swp_01 = neon_shuffleq_f32(swp_0a, swp_0a, 2, 0, 0, 0);
            float32x4_t swp_02 = neon_shuffleq_f32(swp_0b, swp_0b, 2, 0, 0, 0);
            float32x4_t swp_03 = neon_shuffleq_f32(c_2, c_1, 1, 1, 1, 1);

            float32x4_t mul_00 = vmulq_f32(swp_00, swp_01);
            float32x4_t mul_01 = vmulq_f32(swp_02, swp_03);
            fac_5 = vsubq_f32(mul_00, mul_01);
        }

        float32x4_t sign_a = vsetq_lane_f32(-one<float>, vsetq_lane_f32(-one<float>, vdupq_n_f32(one<float>), 0), 2);
        float32x4_t sign_b = vsetq_lane_f32(-one<float>, vsetq_lane_f32(-one<float>, vdupq_n_f32(one<float>), 1), 3);

        // v_0 = { m[1][0], m[0][0], m[0][0], m[0][0] }
        float32x4_t tmp_0 = neon_shuffleq_f32(c_1, c_0, 0, 0, 0, 0);
        float32x4_t v_0 = neon_shuffleq_f32(tmp_0, tmp_0, 2, 2, 2, 0);

        // v_0 = { m[1][1], m[0][1], m[0][1], m[0][1] }
        float32x4_t tmp_1 = neon_shuffleq_f32(c_1, c_0, 1, 1, 1, 1);
        float32x4_t v_1 = neon_shuffleq_f32(tmp_1, tmp_1, 2, 2, 2, 0);

        // v_0 = { m[1][2], m[0][2], m[0][2], m[0][2] }
        float32x4_t tmp_2 = neon_shuffleq_f32(c_1, c_0, 2, 2, 2, 2);
        float32x4_t v_2 = neon_shuffleq_f32(tmp_2, tmp_2, 2, 2, 2, 0);

        // v_0 = { m[1][3], m[0][3], m[0][3], m[0][3] }
        float32x4_t tmp_3 = neon_shuffleq_f32(c_1, c_0, 3, 3, 3, 3);
        float32x4_t v_3 = neon_shuffleq_f32(tmp_3, tmp_3, 2, 2, 2, 0);

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
        float32x4_t i_tmp_0 = neon_shuffleq_f32(inv_0, inv_1, 0, 0, 0, 0);
        float32x4_t i_tmp_1 = neon_shuffleq_f32(inv_2, inv_3, 0, 0, 0, 0);
        float32x4_t i_row_0 = neon_shuffleq_f32(i_tmp_0, i_tmp_1, 3, 1, 3, 1);
        float32x4_t i_dot_0 = neon::geo::fv4_dot(c_0, i_row_0);
        float32x4_t one_over_det = vdivq_f32(vdupq_n_f32(one<float>), i_dot_0);
        
        M ret;
        ret[0].st = vmulq_f32(inv_0, one_over_det);
        ret[1].st = vmulq_f32(inv_1, one_over_det);
        ret[2].st = vmulq_f32(inv_2, one_over_det);
        ret[3].st = vmulq_f32(inv_3, one_over_det);
        return ret;
    }
};

#elif defined(KTM_SIMD_SSE)

template<>
struct ktm::detail::matrix_implement::transpose<2, 2, float>
{
    using M = mat<2, 2, float>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        intrin::mt::fmt2_tp(&ret[0].st, &m[0].st);
        return ret;
    }
};

template<>
struct ktm::detail::matrix_implement::transpose<3, 3, float>
{
    using M = mat<3, 3, float>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        intrin::mt::fmt3_tp(&ret[0].st, &m[0].st); 
        return ret;
    }
};

template<>
struct ktm::detail::matrix_implement::transpose<4, 4, float>
{
    using M = mat<4, 4, float>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        intrin::mt::fmt4_tp(&ret[0].st, &m[0].st); 
        return ret;
    }
};

template<>
struct ktm::detail::matrix_implement::transpose<2, 2, int>
{
    using M = mat<2, 2, int>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        intrin::mt::fmt2_tp(&ret[0].st, &m[0].st);
        return ret;
    }
};

template<>
struct ktm::detail::matrix_implement::transpose<3, 3, int>
{
    using M = mat<3, 3, int>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        intrin::mt::fmt3_tp(reinterpret_cast<__m128*>(&ret[0].st), reinterpret_cast<const __m128*>(&m[0].st));
        return ret; 
    }
};

template<>
struct ktm::detail::matrix_implement::transpose<4, 4, int>
{
    using M = mat<4, 4, int>;
    using RetM = M;
    static KTM_INLINE RetM call(const M& m) noexcept
    {
        RetM ret;
        intrin::mt::fmt4_tp(reinterpret_cast<__m128*>(&ret[0].st), reinterpret_cast<const __m128*>(&m[0].st));
        return ret; 
    }
};

template<>
struct ktm::detail::matrix_implement::determinant<3, float>
{
    using M = mat<3, 3, float>;
    static KTM_INLINE float call(const M& m) noexcept
    {
        const __m128& c_0 = m[0].st;
        const __m128& c_1 = m[1].st;
        const __m128& c_2 = m[2].st;
        __m128 mul_00 = _mm_mul_ps(_mm_shuffle_ps(c_1, c_1, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(c_2, c_2, _MM_SHUFFLE(3, 1, 0, 2)));
        __m128 mul_01 = _mm_mul_ps(_mm_shuffle_ps(c_1, c_1, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(c_2, c_2, _MM_SHUFFLE(3, 0, 2, 1)));
        __m128 sub_0 = _mm_sub_ps(mul_00, mul_01);  
        
        return intrin::geo::fv3_dot1(c_0, sub_0); 
    }
};

template<>
struct ktm::detail::matrix_implement::determinant<4, float>
{
    using M = mat<4, 4, float>;
    static KTM_INLINE float call(const M& m) noexcept
    {
        const __m128& c_0 = m[0].st;
        const __m128& c_1 = m[1].st;
        const __m128& c_2 = m[2].st;
        const __m128& c_3 = m[3].st;

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
        return _mm_cvtss_f32(sum_0);
    }
};

template<>
struct ktm::detail::matrix_implement::inverse<4, float>
{
    using M = mat<4, 4, float>;
    static KTM_INLINE M call(const M& m) noexcept
    {
        const __m128& c_0 = m[0].st;
        const __m128& c_1 = m[1].st;
        const __m128& c_2 = m[2].st;
        const __m128& c_3 = m[3].st;

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

        __m128 tmp_0 = _mm_shuffle_ps(c_1, c_0, 0);
        __m128 v_0 = _mm_shuffle_ps(tmp_0, tmp_0,  _MM_SHUFFLE(2, 2, 2, 0));

        __m128 tmp_1 = _mm_shuffle_ps(c_1, c_0, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 v_1 = _mm_shuffle_ps(tmp_1, tmp_1,  _MM_SHUFFLE(2, 2, 2, 0));

        __m128 tmp_2 = _mm_shuffle_ps(c_1, c_0, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 v_2 = _mm_shuffle_ps(tmp_2, tmp_2,  _MM_SHUFFLE(2, 2, 2, 0));

        __m128 tmp_3 = _mm_shuffle_ps(c_1, c_0, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 v_3 = _mm_shuffle_ps(tmp_3, tmp_3,  _MM_SHUFFLE(2, 2, 2, 0));

        __m128 inv_0; 
        {
            __m128 mul_00 = _mm_mul_ps(v_1, fac_0);
            __m128 mul_01 = _mm_mul_ps(v_2, fac_1); 
            __m128 mul_02 = _mm_mul_ps(v_3, fac_2);
            __m128 sum_0 = _mm_add_ps(_mm_sub_ps(mul_00, mul_01), mul_02);
            inv_0 = _mm_mul_ps(sign_b, sum_0);
        }

        __m128 inv_1;
        {
            __m128 mul_00 = _mm_mul_ps(v_0, fac_0);
            __m128 mul_01 = _mm_mul_ps(v_2, fac_3); 
            __m128 mul_02 = _mm_mul_ps(v_3, fac_4);
            __m128 sum_0 = _mm_add_ps(_mm_sub_ps(mul_00, mul_01), mul_02);
            inv_1 = _mm_mul_ps(sign_a, sum_0);
        }

        __m128 inv_2;
        {
            __m128 mul_00 = _mm_mul_ps(v_0, fac_1);
            __m128 mul_01 = _mm_mul_ps(v_1, fac_3); 
            __m128 mul_02 = _mm_mul_ps(v_3, fac_5);
            __m128 sum_0 = _mm_add_ps(_mm_sub_ps(mul_00, mul_01), mul_02);
            inv_2 = _mm_mul_ps(sign_b, sum_0);
        }

        __m128 inv_3;
        {
            __m128 mul_00 = _mm_mul_ps(v_0, fac_2);
            __m128 mul_01 = _mm_mul_ps(v_1, fac_4); 
            __m128 mul_02 = _mm_mul_ps(v_2, fac_5);
            __m128 sum_0 = _mm_add_ps(_mm_sub_ps(mul_00, mul_01), mul_02);
            inv_3 = _mm_mul_ps(sign_a, sum_0);
        }

        __m128 i_tmp_0 = _mm_shuffle_ps(inv_0, inv_1, 0);
        __m128 i_tmp_1 = _mm_shuffle_ps(inv_2, inv_3, 0);
        __m128 i_row_0 = _mm_shuffle_ps(i_tmp_0, i_tmp_1,  _MM_SHUFFLE(3, 1, 3, 1));
        __m128 i_dot = intrin::geo::fv4_dot(c_0, i_row_0);
        __m128 one_over_det = _mm_div_ps(_mm_set1_ps(one<float>), i_dot);

        M ret;
        ret[0].st = _mm_mul_ps(inv_0, one_over_det);
        ret[1].st = _mm_mul_ps(inv_1, one_over_det);
        ret[2].st = _mm_mul_ps(inv_2, one_over_det);
        ret[3].st = _mm_mul_ps(inv_3, one_over_det);
        return ret;
    }
};

#if KTM_SIMD_SSE & KTM_SIMD_SSE4_1_FLAG

template<>
struct ktm::detail::matrix_implement::determinant<3, int>
{
    using M = mat<3, 3, int>;
    static KTM_INLINE float call(const M& m) noexcept
    {
        const __m128i& c_0 = m[0].st;
        const __m128i& c_1 = m[1].st;
        const __m128i& c_2 = m[2].st;
        __m128i mul_00 = _mm_mullo_epi32(_mm_shuffle_epi32(c_1, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_epi32(c_2, _MM_SHUFFLE(3, 1, 0, 2)));
        __m128i mul_01 = _mm_mullo_epi32(_mm_shuffle_epi32(c_1, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_epi32(c_2, _MM_SHUFFLE(3, 0, 2, 1)));
        __m128i sub_0 = _mm_sub_epi32(mul_00, mul_01);  
        return intrin::geo::sv3_dot1(c_0, sub_0); 
    }
};

template<>
struct ktm::detail::matrix_implement::determinant<4, int>
{
    using M = mat<4, 4, int>;
    static KTM_INLINE float call(const M& m) noexcept
    {
        const __m128i& c_0 = m[0].st;
        const __m128i& c_1 = m[1].st;
        const __m128i& c_2 = m[2].st;
        const __m128i& c_3 = m[3].st;

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
        return _mm_cvtsi128_si32(sum_0);
    }
};

#endif // KTM_SIMD_SSE & KTM_SIMD_SSE2_FLAG 

#endif

#endif
