#ifndef _MAT_COMMON_IMPL_SIMD_INL_
#define _MAT_COMMON_IMPL_SIMD_INL_

#include "Math/MathType/BaseType.h"
#include "MatCommonImpl.h"

#ifdef __ARM_NEON__
#include <arm_neon.h>

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