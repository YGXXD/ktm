#ifndef _VEC_OPT_IMPL_SIMD_INL_
#define _VEC_OPT_IMPL_SIMD_INL_

#include "VecOptImpl.h"
#include <Math/MathType/BaseType.h>

#if defined(CHTHOLLY_SIMD_NEON)
#include <arm_neon.h>

template<size_t N>
struct ktm::detail::vec_opt_implement::add<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vadd_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
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
            float32x2_t ret = vadd_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
            vst1_f32(&x[0], ret);
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
            vst1q_f32(&x[0], ret);
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
            float32x2_t ret = vsub_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
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
            float32x2_t ret = vsub_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
            vst1_f32(&x[0], ret);
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
            vst1q_f32(&x[0], ret);
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
            float32x2_t ret = vmul_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
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
            float32x2_t ret = vmul_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
            vst1_f32(&x[0], ret);
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
            vst1q_f32(&x[0], ret);
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
            float32x2_t ret = vdiv_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
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
            float32x2_t ret = vdiv_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
            vst1_f32(&x[0], ret);
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
            vst1q_f32(&x[0], ret);
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
            float32x2_t ret = vneg_f32(vld1_f32(&x[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vnegq_f32(vld1q_f32(&x[0]));
            return *reinterpret_cast<V*>(&ret);
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
            float32x2_t ret = vadd_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
            return *reinterpret_cast<V*>(&ret);
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
            float32x2_t ret = vadd_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
            vst1_f32(&x[0], ret);
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
            vst1q_f32(&x[0], ret);
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
            float32x2_t ret = vsub_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
            return *reinterpret_cast<V*>(&ret);
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
            float32x2_t ret = vsub_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
            vst1_f32(&x[0], ret);
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
            vst1q_f32(&x[0], ret);
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
            float32x2_t ret = vmul_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
            return *reinterpret_cast<V*>(&ret);
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
            float32x2_t ret = vmul_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
            vst1_f32(&x[0], ret);
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
            vst1q_f32(&x[0], ret);
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
            float32x2_t ret = vdiv_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
            return *reinterpret_cast<V*>(&ret);
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
            float32x2_t ret = vdiv_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
            vst1_f32(&x[0], ret);
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
            vst1q_f32(&x[0], ret);
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
            float32x2_t ret = vceq_f32(vabs_f32(vsub_f32(vld1_f32(&x[0]), vld1_f32(&y[0]))), vdup_n_f32(std::numeric_limits<float>::epsilon()));
            return static_cast<bool>(vminv_u32(ret)); 
        }
        else if constexpr(N == 3)
        {
            float32x4_t ret = vceqq_f32(vabsq_f32(vsubq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]))), vdupq_n_f32(std::numeric_limits<float>::epsilon()));
            ret = vsetq_lane_f32(ret[2], ret, 3);
            return static_cast<bool>(vminvq_u32(ret)); 
        }
        else
        {
            float32x4_t ret = vceqq_f32(vabsq_f32(vsubq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]))), vdupq_n_f32(std::numeric_limits<float>::epsilon()));
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
            int32x2_t ret = vadd_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
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
            int32x2_t ret = vadd_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
            vst1_s32(&x[0], ret);
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
            vst1q_s32(&x[0], ret);
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
            int32x2_t ret = vsub_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
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
            int32x2_t ret = vsub_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
            vst1_s32(&x[0], ret);
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
            vst1q_s32(&x[0], ret);
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
            int32x2_t ret = vmul_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
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
            int32x2_t ret = vmul_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
            vst1_s32(&x[0], ret);
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
            vst1q_s32(&x[0], ret);
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
            int32x2_t ret = vneg_s32(vld1_s32(&x[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t ret = vnegq_s32(vld1q_s32(&x[0]));
            return *reinterpret_cast<V*>(&ret);
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
            int32x2_t ret = vadd_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
            return *reinterpret_cast<V*>(&ret);
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
            int32x2_t ret = vadd_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
            vst1_s32(&x[0], ret);
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
            vst1q_s32(&x[0], ret);
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
            int32x2_t ret = vsub_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
            return *reinterpret_cast<V*>(&ret);
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
            int32x2_t ret = vsub_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
            vst1_s32(&x[0], ret);
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
            vst1q_s32(&x[0], ret);
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
            int32x2_t ret = vmul_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
            return *reinterpret_cast<V*>(&ret);
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
            int32x2_t ret = vmul_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
            vst1_s32(&x[0], ret);
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
            vst1q_s32(&x[0], ret);
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
            int32x2_t ret = vceq_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
            return static_cast<bool>(vmaxv_s32(ret)); 
        }
        else if constexpr(N == 3)
        {
            int32x4_t ret = vceqq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
            ret = vsetq_lane_s32(ret[2], ret, 3);
            return static_cast<bool>(vmaxvq_s32(ret)); 
        }
        else
        {
            int32x4_t ret = vceqq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
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
            uint32x2_t ret = vadd_u32(vld1_u32(&x[0]), vld1_u32(&y[0]));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(&x[0]), vld1q_u32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
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
            uint32x2_t ret = vadd_u32(vld1_u32(&x[0]), vld1_u32(&y[0]));
            vst1_u32(&x[0], ret);
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(&x[0]), vld1q_u32(&y[0]));
            vst1q_u32(&x[0], ret);
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
            uint32x2_t ret = vsub_u32(vld1_u32(&x[0]), vld1_u32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(&x[0]), vld1q_u32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
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
            uint32x2_t ret = vsub_u32(vld1_u32(&x[0]), vld1_u32(&y[0]));
            vst1_u32(&x[0], ret);
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(&x[0]), vld1q_u32(&y[0]));
            vst1q_u32(&x[0], ret);
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
            uint32x2_t ret = vmul_u32(vld1_u32(&x[0]), vld1_u32(&y[0]));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(&x[0]), vld1q_u32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
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
            uint32x2_t ret = vmul_u32(vld1_u32(&x[0]), vld1_u32(&y[0]));
            vst1_u32(&x[0], ret);
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(&x[0]), vld1q_u32(&y[0]));
            vst1q_u32(&x[0], ret);
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
            uint32x2_t ret = vadd_u32(vld1_u32(&x[0]), vdup_n_u32(scalar));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(&x[0]), vdupq_n_u32(scalar));
            return *reinterpret_cast<V*>(&ret);
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
            uint32x2_t ret = vadd_u32(vld1_u32(&x[0]), vdup_n_u32(scalar));
            vst1_u32(&x[0], ret);
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(&x[0]), vdupq_n_u32(scalar));
            vst1q_u32(&x[0], ret);
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
            uint32x2_t ret = vsub_u32(vld1_u32(&x[0]), vdup_n_u32(scalar));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(&x[0]), vdupq_n_u32(scalar));
            return *reinterpret_cast<V*>(&ret);
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
            uint32x2_t ret = vsub_u32(vld1_u32(&x[0]), vdup_n_u32(scalar));
            vst1_u32(&x[0], ret);
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(&x[0]), vdupq_n_u32(scalar));
            vst1q_u32(&x[0], ret);
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
            uint32x2_t ret = vmul_u32(vld1_u32(&x[0]), vdup_n_u32(scalar));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(&x[0]), vdupq_n_u32(scalar));
            return *reinterpret_cast<V*>(&ret);
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
            uint32x2_t ret = vmul_u32(vld1_u32(&x[0]), vdup_n_u32(scalar));
            vst1_u32(&x[0], ret);
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(&x[0]), vdupq_n_u32(scalar));
            vst1q_u32(&x[0], ret);
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
            uint32x2_t ret = vceq_u32(vld1_u32(&x[0]), vld1_u32(&y[0]));
            return static_cast<bool>(vminv_u32(ret)); 
        }
        else if constexpr(N == 3)
        {
            uint32x4_t ret = vceqq_u32(vld1q_u32(&x[0]), vld1q_u32(&y[0]));
            ret = vsetq_lane_u32(ret[2], ret, 3);
            return static_cast<bool>(vminvq_u32(ret)); 
        }
        else
        {
            uint32x4_t ret = vceqq_u32(vld1q_u32(&x[0]), vld1q_u32(&y[0]));
            return static_cast<bool>(vminvq_u32(ret)); 
        }
    }
};

#elif defined(CHTHOLLY_SIMD_SSE2)
#include <emmintrin.h>

template<size_t N>
struct ktm::detail::vec_opt_implement::add<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128 ret = _mm_add_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        __m128 ret = _mm_add_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        _mm_store_ps(&x[0], ret);
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128 ret = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        __m128 ret = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        _mm_store_ps(&x[0], ret);
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128 ret = _mm_mul_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        __m128 ret = _mm_mul_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        _mm_store_ps(&x[0], ret);
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128 ret = _mm_div_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        __m128 ret = _mm_div_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        _mm_store_ps(&x[0], ret);
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::opposite<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        __m128 t_x = _mm_load_ps(&x[0]);
        __m128 ret = _mm_or_ps(_mm_andnot_ps(t_x, _mm_castsi128_ps(_mm_set1_epi32(0x80000000))), _mm_andnot_ps(_mm_castsi128_ps(_mm_set1_epi32(0x80000000)), t_x));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        __m128 ret = _mm_add_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        return *reinterpret_cast<V*>(&ret);
    }

};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        __m128 ret = _mm_add_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        _mm_store_ps(&x[0], ret);
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        __m128 ret = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        __m128 ret = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        _mm_store_ps(&x[0], ret);
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        __m128 ret = _mm_mul_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        __m128 ret = _mm_mul_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        _mm_store_ps(&x[0], ret);
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {   
        __m128 ret = _mm_div_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        __m128 ret = _mm_div_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        _mm_store_ps(&x[0], ret);
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::equal<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 3)
        {
            __m128 delta = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
            __m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x7fffffff));
            __m128 ret = _mm_cmplt_ps(_mm_and_ps(delta, mask), _mm_set1_ps(std::numeric_limits<float>::epsilon()));     
            __m128 and1 = _mm_and_ps(ret, _mm_shuffle_ps(ret, ret, _MM_SHUFFLE(2, 3, 1, 0)));
            __m128 and2 = _mm_and_ps(and1, _mm_shuffle_ps(ret, ret, _MM_SHUFFLE(1, 3, 2, 0)));
            return *reinterpret_cast<unsigned int*>(&and2);
        }
        else 
        {
            __m128 delta = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
            __m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x7fffffff));
            __m128 ret = _mm_cmplt_ps(_mm_and_ps(delta, mask), _mm_set1_ps(std::numeric_limits<float>::epsilon()));     
            __m128 and1 = _mm_and_ps(ret, _mm_shuffle_ps(ret, ret, _MM_SHUFFLE(1, 0, 3, 2)));
            __m128 and2 = _mm_and_ps(and1, _mm_shuffle_ps(and1, and1, _MM_SHUFFLE(2, 3, 1, 0)));
            return *reinterpret_cast<unsigned int*>(&and2);
        }
    }
};

#endif

#endif
