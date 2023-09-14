#ifndef _VEC_COMMON_IMPL_SIMD_INL_
#define _VEC_COMMON_IMPL_SIMD_INL_

#include "VecCommonImpl.h"
#include "Math/MathLib/Common.h"

#ifdef __ARM_NEON__
#include <arm_neon.h>

template<size_t L, size_t N>
struct ktm::detail::vec_common_implement::elem_move<L, ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    static_assert(L > 0 && L < N);
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            float32x2_t ret = vld1_f32(reinterpret_cast<const float*>(&x));
            ret = __builtin_shufflevector(ret, ret, L, i1);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 3)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            float32x4_t ret = vld1q_f32(reinterpret_cast<const float*>(&x));
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, 3);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 4)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            constexpr size_t i3 = 3 + L < N ? 3 + L : 3 + L - N;  
            float32x4_t ret = vld1q_f32(reinterpret_cast<const float*>(&x));
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, i3);
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t L, size_t N>
struct ktm::detail::vec_common_implement::elem_move<L, ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    static_assert(L > 0 && L < N);
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            int32x2_t ret = vld1_s32(reinterpret_cast<const int*>(&x));
            ret = __builtin_shufflevector(ret, ret, L, i1);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 3)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            int32x4_t ret = vld1q_s32(reinterpret_cast<const int*>(&x));
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, 3);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 4)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            constexpr size_t i3 = 3 + L < N ? 3 + L : 3 + L - N;  
            int32x4_t ret = vld1q_s32(reinterpret_cast<const int*>(&x));
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, i3);
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t L, size_t N>
struct ktm::detail::vec_common_implement::elem_move<L, ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    static_assert(L > 0 && L < N);
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            uint32x2_t ret = vld1_u32(reinterpret_cast<const unsigned int*>(&x));
            ret = __builtin_shufflevector(ret, ret, L, i1);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 3)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            uint32x4_t ret = vld1q_u32(reinterpret_cast<const unsigned int*>(&x));
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, 3);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 4)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            constexpr size_t i3 = 3 + L < N ? 3 + L : 3 + L - N;  
            uint32x4_t ret = vld1q_u32(reinterpret_cast<const unsigned int*>(&x));
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, i3);
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_add<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vaddv_f32(vld1_f32(reinterpret_cast<const float*>(&x)));
        }
        else if constexpr(N == 3)
        {
            float32x4_t tmp = vld1q_f32(reinterpret_cast<const float*>(&x));
            return vaddvq_f32(vsetq_lane_f32(0, tmp, 3)); 
        }
        else
        {
            return vaddvq_f32(vld1q_f32(reinterpret_cast<const float*>(&x))); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_add<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vaddv_s32(vld1_s32(reinterpret_cast<const int*>(&x)));
        }
        else if constexpr(N == 3)
        {
            int32x4_t tmp = vld1q_s32(reinterpret_cast<const int*>(&x));
            return vaddvq_s32(vsetq_lane_s32(0, tmp, 3)); 
        }
        else
        {
            return vaddvq_s32(vld1q_s32(reinterpret_cast<const int*>(&x))); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_add<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE unsigned int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vaddv_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)));
        }
        else if constexpr(N == 3)
        {
            uint32x4_t tmp = vld1q_u32(reinterpret_cast<const unsigned int*>(&x));
            return vaddvq_u32(vsetq_lane_u32(0, tmp, 3)); 
        }
        else
        {
            return vaddvq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x))); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_min<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vminv_f32(vld1_f32(reinterpret_cast<const float*>(&x)));
        }
        else if constexpr(N == 3)
        {
            float32x4_t tmp = vld1q_f32(reinterpret_cast<const float*>(&x));
            return vminvq_f32(vsetq_lane_f32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vminvq_f32(vld1q_f32(reinterpret_cast<const float*>(&x))); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_min<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vminv_s32(vld1_s32(reinterpret_cast<const int*>(&x)));
        }
        else if constexpr(N == 3)
        {
            int32x4_t tmp = vld1q_s32(reinterpret_cast<const int*>(&x));
            return vminvq_s32(vsetq_lane_s32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vminvq_s32(vld1q_s32(reinterpret_cast<const int*>(&x))); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_min<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE unsigned int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vminv_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)));
        }
        else if constexpr(N == 3)
        {
            uint32x4_t tmp = vld1q_u32(reinterpret_cast<const unsigned int*>(&x));
            return vminvq_u32(vsetq_lane_u32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vminvq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x))); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_max<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vmaxv_f32(vld1_f32(reinterpret_cast<const float*>(&x)));
        }
        else if constexpr(N == 3)
        {
            float32x4_t tmp = vld1q_f32(reinterpret_cast<const float*>(&x));
            return vmaxvq_f32(vsetq_lane_f32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vmaxvq_f32(vld1q_f32(reinterpret_cast<const float*>(&x))); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_max<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vmaxv_s32(vld1_s32(reinterpret_cast<const int*>(&x)));
        }
        else if constexpr(N == 3)
        {
            int32x4_t tmp = vld1q_s32(reinterpret_cast<const int*>(&x));
            return vmaxvq_s32(vsetq_lane_s32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vmaxvq_s32(vld1q_s32(reinterpret_cast<const int*>(&x))); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_max<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE unsigned int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vmaxv_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)));
        }
        else if constexpr(N == 3)
        {
            uint32x4_t tmp = vld1q_u32(reinterpret_cast<const unsigned int*>(&x));
            return vmaxvq_u32(vsetq_lane_u32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vmaxvq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x))); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::abs<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t tmp = vld1_f32(reinterpret_cast<const float*>(&x));
            float32x2_t ret = vabs_f32(tmp);
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t tmp = vld1q_f32(reinterpret_cast<const float*>(&x));
            float32x4_t ret = vabsq_f32(tmp);
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::abs<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t tmp = vld1_s32(reinterpret_cast<const int*>(&x));
            int32x2_t ret = vabs_s32(tmp);
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t tmp = vld1q_s32(reinterpret_cast<const int*>(&x));
            int32x4_t ret = vabsq_s32(tmp);
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::min<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmin_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vminq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::min<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmin_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t ret = vminq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::min<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmin_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            uint32x4_t ret = vminq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::max<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmax_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vmaxq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::max<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmax_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t ret = vmaxq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::max<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmax_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            uint32x4_t ret = vmaxq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::clamp<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t tmp = vmax_f32(vld1_f32(reinterpret_cast<const float*>(&v)), vld1_f32(reinterpret_cast<const float*>(&min)));
            float32x2_t ret = vmin_f32(tmp, vld1_f32(reinterpret_cast<const float*>(&max)));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            float32x4_t tmp = vmaxq_f32(vld1q_f32(reinterpret_cast<const float*>(&v)), vld1q_f32(reinterpret_cast<const float*>(&min)));
            float32x4_t ret = vminq_f32(tmp, vld1q_f32(reinterpret_cast<const float*>(&max)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::clamp<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t tmp = vmax_s32(vld1_s32(reinterpret_cast<const int*>(&v)), vld1_s32(reinterpret_cast<const int*>(&min)));
            int32x2_t ret = vmin_s32(tmp, vld1_s32(reinterpret_cast<const int*>(&max)));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            int32x4_t tmp = vmaxq_s32(vld1q_s32(reinterpret_cast<const int*>(&v)), vld1q_s32(reinterpret_cast<const int*>(&min)));
            int32x4_t ret = vminq_s32(tmp, vld1q_s32(reinterpret_cast<const int*>(&max)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::clamp<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t tmp = vmax_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&v)), vld1_u32(reinterpret_cast<const unsigned int*>(&min)));
            uint32x2_t ret = vmin_u32(tmp, vld1_u32(reinterpret_cast<const unsigned int*>(&max)));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            uint32x4_t tmp = vmaxq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&v)), vld1q_u32(reinterpret_cast<const unsigned int*>(&min)));
            uint32x4_t ret = vminq_u32(tmp, vld1q_u32(reinterpret_cast<const unsigned int*>(&max)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::lerp<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y, float t) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t t_x = vld1_f32(reinterpret_cast<const float*>(&x));
            float32x2_t t_y = vld1_f32(reinterpret_cast<const float*>(&y));
            float32x2_t t_t = vdup_n_f32(t);
            float32x2_t ret = vadd_f32(t_x, vmul_f32(t_t, vsub_f32(t_y, t_x)));
            return *reinterpret_cast<V*>(&ret);
        }
        else 
        {
            float32x4_t t_x = vld1q_f32(reinterpret_cast<const float*>(&x));
            float32x4_t t_y = vld1q_f32(reinterpret_cast<const float*>(&y));
            float32x4_t t_t = vdupq_n_f32(t);
            float32x4_t ret = vaddq_f32(t_x, vmulq_f32(t_t, vsubq_f32(t_y, t_x)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::mix<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t t_x = vld1_f32(reinterpret_cast<const float*>(&x));
            float32x2_t t_y = vld1_f32(reinterpret_cast<const float*>(&y));
            float32x2_t t_t = vld1_f32(reinterpret_cast<const float*>(&t));
            float32x2_t ret = vadd_f32(t_x, vmul_f32(t_t, vsub_f32(t_y, t_x)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t t_x = vld1q_f32(reinterpret_cast<const float*>(&x));
            float32x4_t t_y = vld1q_f32(reinterpret_cast<const float*>(&y));
            float32x4_t t_t = vld1q_f32(reinterpret_cast<const float*>(&t));
            float32x4_t ret = vaddq_f32(t_x, vmulq_f32(t_t, vsubq_f32(t_y, t_x)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::recip<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vdiv_f32(vdup_n_f32(one<float>), vld1_f32(reinterpret_cast<const float*>(&x)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vdivq_f32(vdupq_n_f32(one<float>), vld1q_f32(reinterpret_cast<const float*>(&x)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::step<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& edge, const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t cmp = vclt_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&edge)));
            uint32x2_t tmp = vand_u32(vreinterpret_u32_f32(vdup_n_f32(one<float>)), vreinterpret_u32_f32(cmp));
            float32x2_t ret = vreinterpret_f32_u32(tmp);
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t cmp = vcltq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&edge)));
            uint32x4_t tmp = vandq_u32(vreinterpretq_u32_f32(vdupq_n_f32(one<float>)), vreinterpretq_u32_f32(cmp));
            float32x4_t ret = vreinterpretq_f32_u32(tmp);
            return *reinterpret_cast<V*>(&ret);
        } 
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::smoothstep<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t t_edge0 = vld1_f32(reinterpret_cast<const float*>(&edge0));
            float32x2_t t_edge1 = vld1_f32(reinterpret_cast<const float*>(&edge1)); 
            float32x2_t t_x = vld1_f32(reinterpret_cast<const float*>(&x));
            float32x2_t tmp = vdiv_f32(vsub_f32(t_x, t_edge0), vsub_f32(t_edge1, t_edge0));
            tmp = vmax_f32(tmp, vdup_n_f32(zero<float>));
            tmp = vmin_f32(tmp, vdup_n_f32(one<float>));
            float32x2_t ret = vmul_f32(vmul_f32(tmp, tmp), vsub_f32(vdup_n_f32(3.f), vmul_f32(vdup_n_f32(2.f), tmp)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t t_edge0 = vld1q_f32(reinterpret_cast<const float*>(&edge0));
            float32x4_t t_edge1 = vld1q_f32(reinterpret_cast<const float*>(&edge1)); 
            float32x4_t t_x = vld1q_f32(reinterpret_cast<const float*>(&x));
            float32x4_t tmp = vdivq_f32(vsubq_f32(t_x, t_edge0), vsubq_f32(t_edge1, t_edge0));
            tmp = vmaxq_f32(tmp, vdupq_n_f32(zero<float>));
            tmp = vminq_f32(tmp, vdupq_n_f32(one<float>));
            float32x4_t ret = vmulq_f32(vmulq_f32(tmp, tmp), vsubq_f32(vdupq_n_f32(3.f), vmulq_f32(vdupq_n_f32(2.f), tmp)));
            return *reinterpret_cast<V*>(&ret);
        } 
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::fract<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t t_x = vld1_f32(reinterpret_cast<const float*>(&x));
            float32x2_t t_floor = vrndm_f32(t_x);
            float32x2_t ret = vmin_f32(vsub_f32(t_x, t_floor), vdup_n_f32(one<float>));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t t_x = vld1q_f32(reinterpret_cast<const float*>(&x));
            float32x4_t t_floor = vrndmq_f32(t_x);
            float32x4_t ret = vminq_f32(vsubq_f32(t_x, t_floor), vdupq_n_f32(one<float>));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

#endif

#endif