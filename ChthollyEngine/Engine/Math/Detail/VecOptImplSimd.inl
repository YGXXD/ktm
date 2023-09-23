#ifndef _VEC_OPT_IMPL_SIMD_INL_
#define _VEC_OPT_IMPL_SIMD_INL_

#include "VecOptImpl.h"
#include <Math/MathType/BaseType.h>

#ifdef __ARM_NEON__
#include <arm_neon.h>

template<size_t N>
struct ktm::detail::vec_opt_implement::add<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vadd_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vadd_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vsub_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vsub_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmul_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmul_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vdiv_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_to_self<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vdiv_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::opposite<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vneg_f32(vld1_f32(reinterpret_cast<const float*>(&x)));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vnegq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vadd_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }

};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vadd_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vsub_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vsub_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmul_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmul_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_scalar<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {   
        if constexpr(N == 2)
        {
            float32x2_t ret = vdiv_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_scalar_to_self<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vdiv_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::equal<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vceq_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return static_cast<bool>(vminv_u32(ret)); 
        }
        else if constexpr(N == 3)
        {
            float32x4_t ret = vceqq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            ret = vsetq_lane_f32(ret[2], ret, 3);
            return static_cast<bool>(vminvq_u32(ret)); 
        }
        else
        {
            float32x4_t ret = vceqq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            uint32x4_t tmp = vreinterpretq_u32_f32(ret);
            return static_cast<bool>(vminvq_u32(ret)); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vadd_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vadd_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vsub_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vsub_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmul_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmul_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::opposite<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vneg_s32(vld1_s32(reinterpret_cast<const int*>(&x)));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            int32x4_t ret = vnegq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vadd_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }

};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vadd_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vsub_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vsub_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmul_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmul_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::equal<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vceq_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            return static_cast<bool>(vmaxv_s32(ret)); 
        }
        else if constexpr(N == 3)
        {
            int32x4_t ret = vceqq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            ret = vsetq_lane_s32(ret[2], ret, 3);
            return static_cast<bool>(vmaxvq_s32(ret)); 
        }
        else
        {
            int32x4_t ret = vceqq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            return static_cast<bool>(vmaxvq_s32(ret)); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vadd_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vadd_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vsub_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vsub_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmul_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmul_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vadd_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }

};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vadd_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vsub_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vsub_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmul_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmul_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::equal<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vceq_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            return static_cast<bool>(vminv_u32(ret)); 
        }
        else if constexpr(N == 3)
        {
            uint32x4_t ret = vceqq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            ret = vsetq_lane_u32(ret[2], ret, 3);
            return static_cast<bool>(vminvq_u32(ret)); 
        }
        else
        {
            uint32x4_t ret = vceqq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            return static_cast<bool>(vminvq_u32(ret)); 
        }
    }
};

#endif

#endif
