#ifndef _MAT_COMMON_IMPL_SIMD_INL_
#define _MAT_COMMON_IMPL_SIMD_INL_

#include "Math/MathType/BaseType.h"
#include "MatCommonImpl.h"

#ifdef __ARM_NEON__
#include <arm_neon.h>

template<size_t N>
struct ktm::detail::mat_common_implement::transpose<ktm::mat<N, N, std::enable_if_t<N == 4, float>>>
{
    using M = mat<N, N, float>;
    using RetM = mat_traits_tp_t<M>;
    using ColT = mat_traits_col_t<M>;
    using RawT = mat_traits_raw_t<M>; 
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        float32x4_t c_0 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[0]));
        float32x4_t c_1 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[1]));
        float32x4_t c_2 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[2]));
        float32x4_t c_3 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[3]));

        float32x4_t tmp0 = __builtin_shufflevector(c_0, c_1, 0, 1, 4, 5);
        float32x4_t tmp2 = __builtin_shufflevector(c_0, c_1, 2, 3, 6, 7);
        float32x4_t tmp1 = __builtin_shufflevector(c_2, c_3, 0, 1, 4, 5);
        float32x4_t tmp3 = __builtin_shufflevector(c_2, c_3, 2, 3, 6, 7);

        float32x4_t ret0 = __builtin_shufflevector(tmp0, tmp1, 0, 2, 4, 6);
        float32x4_t ret1 = __builtin_shufflevector(tmp0, tmp1, 1, 3, 5, 7);
        float32x4_t ret2 = __builtin_shufflevector(tmp2, tmp3, 0, 2, 4, 6);
        float32x4_t ret3 = __builtin_shufflevector(tmp2, tmp3, 1, 3, 5, 7);

        RetM ret;
        vst1q_f32(reinterpret_cast<float*>(&reinterpret_cast<RawT*>(&ret)[0]), ret0);
        vst1q_f32(reinterpret_cast<float*>(&reinterpret_cast<RawT*>(&ret)[1]), ret1);
        vst1q_f32(reinterpret_cast<float*>(&reinterpret_cast<RawT*>(&ret)[2]), ret2);
        vst1q_f32(reinterpret_cast<float*>(&reinterpret_cast<RawT*>(&ret)[3]), ret3);
        return ret;
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
struct ktm::detail::mat_common_implement::determinant<ktm::mat<N, N, std::enable_if_t<N == 3 || N == 4, float>>>
{
    using M = mat<N, N, float>;
    using ColT = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        if constexpr(N == 3)
        {
            float32x4_t t_col0 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[0]));
            float32x4_t t_col1 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[1]));
            float32x4_t t_col2 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[2]));
            float32x4_t tmp = NEON_DET3_SHUFFLE_MUL(t_col0, t_col1, t_col2);
            return vaddvq_f32(tmp);
        }
        else 
        {
            float32x4_t t_col0 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[0]));
            float32x4_t t_col1 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[1]));
            float32x4_t t_col2 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[2]));
            float32x4_t t_col3 = vld1q_f32(reinterpret_cast<const float*>(&reinterpret_cast<const ColT*>(&m)[3]));
            float32x4_t tmp = NEON_DET4_SHUFFLE_MUL(t_col0, t_col1, t_col2, t_col3);
            tmp = __builtin_shufflevector(tmp, tmp, 0, 2, 1, 3);
            return vaddv_f32(vget_low_f32(tmp) - vget_high_f32(tmp));
        }
    }
};

template<size_t N>
struct ktm::detail::mat_common_implement::determinant<ktm::mat<N, N, std::enable_if_t<N == 3 || N == 4, int>>>
{
    using M = mat<N, N, int>;
    using ColT = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        if constexpr(N == 3)
        {
            int32x4_t t_col0 = vld1q_s32(reinterpret_cast<const int*>(&reinterpret_cast<const ColT*>(&m)[0]));
            int32x4_t t_col1 = vld1q_s32(reinterpret_cast<const int*>(&reinterpret_cast<const ColT*>(&m)[1]));
            int32x4_t t_col2 = vld1q_s32(reinterpret_cast<const int*>(&reinterpret_cast<const ColT*>(&m)[2]));
            int32x4_t tmp = NEON_DET3_SHUFFLE_MUL(t_col0, t_col1, t_col2);
            return vaddvq_s32(tmp);
        }
        else 
        {
            int32x4_t t_col0 = vld1q_s32(reinterpret_cast<const int*>(&reinterpret_cast<const ColT*>(&m)[0]));
            int32x4_t t_col1 = vld1q_s32(reinterpret_cast<const int*>(&reinterpret_cast<const ColT*>(&m)[1]));
            int32x4_t t_col2 = vld1q_s32(reinterpret_cast<const int*>(&reinterpret_cast<const ColT*>(&m)[2]));
            int32x4_t t_col3 = vld1q_s32(reinterpret_cast<const int*>(&reinterpret_cast<const ColT*>(&m)[3]));
            int32x4_t tmp = NEON_DET4_SHUFFLE_MUL(t_col0, t_col1, t_col2, t_col3);
            tmp = __builtin_shufflevector(tmp, tmp, 0, 2, 1, 3);
            return vaddv_s32(vget_low_s32(tmp) - vget_high_s32(tmp));
        }
    }
};

template<size_t N>
struct ktm::detail::mat_common_implement::determinant<ktm::mat<N, N, std::enable_if_t<N == 3 || N == 4, unsigned int>>>
{
    using M = mat<N, N, unsigned int>;
    using ColT = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE float call(const M& m) noexcept
    {
        if constexpr(N == 3)
        {
            uint32x4_t t_col0 = vld1q_u32(reinterpret_cast<const unsigned int*>(&reinterpret_cast<const ColT*>(&m)[0]));
            uint32x4_t t_col1 = vld1q_u32(reinterpret_cast<const unsigned int*>(&reinterpret_cast<const ColT*>(&m)[1]));
            uint32x4_t t_col2 = vld1q_u32(reinterpret_cast<const unsigned int*>(&reinterpret_cast<const ColT*>(&m)[2]));
            uint32x4_t tmp = NEON_DET3_SHUFFLE_MUL(t_col0, t_col1, t_col2);
            return vaddvq_u32(tmp);
        }
        else 
        {
            uint32x4_t t_col0 = vld1q_u32(reinterpret_cast<const unsigned int*>(&reinterpret_cast<const ColT*>(&m)[0]));
            uint32x4_t t_col1 = vld1q_u32(reinterpret_cast<const unsigned int*>(&reinterpret_cast<const ColT*>(&m)[1]));
            uint32x4_t t_col2 = vld1q_u32(reinterpret_cast<const unsigned int*>(&reinterpret_cast<const ColT*>(&m)[2]));
            uint32x4_t t_col3 = vld1q_u32(reinterpret_cast<const unsigned int*>(&reinterpret_cast<const ColT*>(&m)[3]));
            uint32x4_t tmp = NEON_DET4_SHUFFLE_MUL(t_col0, t_col1, t_col2, t_col3);
            tmp = __builtin_shufflevector(tmp, tmp, 0, 2, 1, 3);
            return vaddv_u32(vget_low_u32(tmp) - vget_high_u32(tmp));
        }
    }
};

#endif

#endif