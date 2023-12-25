#ifndef _VECTOR_SIMD_H_
#define _VECTOR_SIMD_H_

#include "VecOptFwd.h"
#include "Math/Library/ArtcBase.h"

#if defined(CHTHOLLY_SIMD_NEON)

template<>
struct ktm::detail::vec_opt_implement::add<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x2_t ret = vadd_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret); 
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x4_t ret = vaddq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::add_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        float32x2_t ret = vadd_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
        vst1_f32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        float32x4_t ret = vaddq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
        vst1q_f32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::minus<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x2_t ret = vsub_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x4_t ret = vsubq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::minus_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        float32x2_t ret = vsub_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
        vst1_f32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        float32x4_t ret = vsubq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
        vst1q_f32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::mul<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x2_t ret = vmul_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret); 
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x4_t ret = vmulq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::mul_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        float32x2_t ret = vmul_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
        vst1_f32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        float32x4_t ret = vmulq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
        vst1q_f32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::div<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x2_t ret = vdiv_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret); 
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x4_t ret = vdivq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::div_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        float32x2_t ret = vdiv_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
        vst1_f32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        float32x4_t ret = vdivq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
        vst1q_f32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::opposite<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        float32x2_t ret = vneg_f32(vld1_f32(&x[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::opposite<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        float32x4_t ret = vnegq_f32(vld1q_f32(&x[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::add_scalar<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        float32x2_t ret = vadd_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }

};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        float32x4_t ret = vaddq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }

};

template<>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        float32x2_t ret = vadd_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
        vst1_f32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        float32x4_t ret = vaddq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
        vst1q_f32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::minus_scalar<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        float32x2_t ret = vsub_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        float32x4_t ret = vsubq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        float32x2_t ret = vsub_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
        vst1_f32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        float32x4_t ret = vsubq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
        vst1q_f32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::mul_scalar<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        float32x2_t ret = vmul_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        float32x4_t ret = vmulq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        float32x2_t ret = vmul_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
        vst1_f32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        float32x4_t ret = vmulq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
        vst1q_f32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::div_scalar<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {   
        float32x2_t ret = vdiv_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {   
        float32x4_t ret = vdivq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::div_scalar_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        float32x2_t ret = vdiv_f32(vld1_f32(&x[0]), vdup_n_f32(scalar));
        vst1_f32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        float32x4_t ret = vdivq_f32(vld1q_f32(&x[0]), vdupq_n_f32(scalar));
        vst1q_f32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::equal<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        float32x2_t ret = vclt_f32(vabs_f32(vsub_f32(vld1_f32(&x[0]), vld1_f32(&y[0]))), vdup_n_f32(epsilon<float>));
        return static_cast<bool>(neon::vandv_f32(ret)); 
    }
};

template<>
struct ktm::detail::vec_opt_implement::equal<3, float>
{
    using V = vec<3, float>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        float32x4_t ret = vcltq_f32(vabsq_f32(vsubq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]))), vdupq_n_f32(epsilon<float>));
        ret = vsetq_lane_f32(vgetq_lane_f32(ret, 2), ret, 3);
        return static_cast<bool>(neon::vandvq_f32(ret));
    }
};

template<>
struct ktm::detail::vec_opt_implement::equal<4, float>
{
    using V = vec<4, float>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        float32x4_t ret = vcltq_f32(vabsq_f32(vsubq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]))), vdupq_n_f32(epsilon<float>));
        return static_cast<bool>(neon::vandvq_f32(ret));
    }
};

template<>
struct ktm::detail::vec_opt_implement::add<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        int32x2_t ret = vadd_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
        return *reinterpret_cast<V*>(&ret); 
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        int32x4_t ret = vaddq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::add_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        int32x2_t ret = vadd_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
        vst1_s32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        int32x4_t ret = vaddq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
        vst1q_s32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::minus<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        int32x2_t ret = vsub_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        int32x4_t ret = vsubq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::minus_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        int32x2_t ret = vsub_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
        vst1_s32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        int32x4_t ret = vsubq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
        vst1q_s32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::mul<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        int32x2_t ret = vmul_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
        return *reinterpret_cast<V*>(&ret); 
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        int32x4_t ret = vmulq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::mul_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        int32x2_t ret = vmul_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
        vst1_s32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        int32x4_t ret = vmulq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
        vst1q_s32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::opposite<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        int32x2_t ret = vneg_s32(vld1_s32(&x[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::opposite<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        int32x4_t ret = vnegq_s32(vld1q_s32(&x[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::add_scalar<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        int32x2_t ret = vadd_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        int32x4_t ret = vaddq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        int32x2_t ret = vadd_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
        vst1_s32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        int32x4_t ret = vaddq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
        vst1q_s32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::minus_scalar<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        int32x2_t ret = vsub_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        int32x4_t ret = vsubq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        int32x2_t ret = vsub_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
        vst1_s32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        int32x4_t ret = vsubq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
        vst1q_s32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::mul_scalar<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        int32x2_t ret = vmul_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        int32x4_t ret = vmulq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        int32x2_t ret = vmul_s32(vld1_s32(&x[0]), vdup_n_s32(scalar));
        vst1_s32(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        int32x4_t ret = vmulq_s32(vld1q_s32(&x[0]), vdupq_n_s32(scalar));
        vst1q_s32(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::equal<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        int32x2_t ret = vceq_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
        return static_cast<bool>(neon::vandv_s32(ret)); 
    }
};

template<>
struct ktm::detail::vec_opt_implement::equal<3, int>
{
    using V = vec<3, int>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        int32x4_t ret = vceqq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
        ret = vsetq_lane_s32(vgetq_lane_s32(ret, 2), ret, 3);
        return static_cast<bool>(neon::vandvq_s32(ret)); 
    }
};

template<>
struct ktm::detail::vec_opt_implement::equal<4, int>
{
    using V = vec<4, int>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        int32x4_t ret = vceqq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
        return static_cast<bool>(neon::vandvq_s32(ret));  
    }
};

#elif defined(CHTHOLLY_SIMD_SSE)

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
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        __m128 ret = _mm_add_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        _mm_store_ps(&x[0], ret);
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
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        __m128 ret = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        _mm_store_ps(&x[0], ret);
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
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        __m128 ret = _mm_mul_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        _mm_store_ps(&x[0], ret);
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
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        __m128 ret = _mm_div_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        _mm_store_ps(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::opposite<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        __m128 t_x = _mm_load_ps(&x[0]);
	    __m128 ret = intrin::_mm_neg_ps(t_x);
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
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        __m128 ret = _mm_add_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        _mm_store_ps(&x[0], ret);
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
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        __m128 ret = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        _mm_store_ps(&x[0], ret);
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
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        __m128 ret = _mm_mul_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        _mm_store_ps(&x[0], ret);
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
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        __m128 ret = _mm_div_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        _mm_store_ps(&x[0], ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::equal<3, float>
{
    using V = vec<3, float>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        __m128 delta = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        __m128 ret = _mm_cmplt_ps(intrin::_mm_abs_ps(delta), _mm_set1_ps(epsilon<float>));     
        __m128 and_0 = _mm_and_ps(ret, _mm_shuffle_ps(ret, ret, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128 and_1 = _mm_and_ps(and_0, _mm_shuffle_ps(ret, ret, _MM_SHUFFLE(1, 0, 3, 2)));
        return static_cast<bool>(_mm_cvtss_f32(and_1));
    }
};

template<>
struct ktm::detail::vec_opt_implement::equal<4, float>
{
    using V = vec<4, float>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        __m128 delta = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_load_ps(&y[0]));
        __m128 ret = _mm_cmplt_ps(intrin::_mm_abs_ps(delta), _mm_set1_ps(epsilon<float>));     
        __m128 and_0 = _mm_and_ps(ret, _mm_shuffle_ps(ret, ret, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128 and_1 = _mm_and_ps(and_0, _mm_shuffle_ps(and_0, and_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return static_cast<bool>(_mm_cvtss_f32(and_1));
    }
};

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

template<size_t N>
struct ktm::detail::vec_opt_implement::add<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i t_y = _mm_load_si128(reinterpret_cast<const __m128i*>(&y[0]));
        __m128i ret = _mm_add_epi32(t_x, t_y);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i t_y = _mm_load_si128(reinterpret_cast<const __m128i*>(&y[0]));
        __m128i ret = _mm_add_epi32(t_x, t_y);
        _mm_store_si128(reinterpret_cast<__m128i*>(&x[0]), ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i t_y = _mm_load_si128(reinterpret_cast<const __m128i*>(&y[0]));
        __m128i ret = _mm_sub_epi32(t_x, t_y);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i t_y = _mm_load_si128(reinterpret_cast<const __m128i*>(&y[0]));
        __m128i ret = _mm_sub_epi32(t_x, t_y);
        _mm_store_si128(reinterpret_cast<__m128i*>(&x[0]), ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::opposite<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i ret = intrin::_mm_neg_epi32(t_x);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i ret = _mm_add_epi32(t_x, _mm_set1_epi32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i ret = _mm_add_epi32(t_x, _mm_set1_epi32(scalar));
        _mm_store_si128(reinterpret_cast<__m128i*>(&x[0]), ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i ret = _mm_sub_epi32(t_x, _mm_set1_epi32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i ret = _mm_sub_epi32(t_x, _mm_set1_epi32(scalar));
        _mm_store_si128(reinterpret_cast<__m128i*>(&x[0]), ret);
    }
};

template<>
struct ktm::detail::vec_opt_implement::equal<3, int>
{
    using V = vec<3, int>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i t_y = _mm_load_si128(reinterpret_cast<const __m128i*>(&y[0]));
        __m128i ret = _mm_cmpeq_epi32(t_x, t_y);   
        __m128i and_0 = _mm_and_si128(ret, _mm_shuffle_epi32(ret, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128i and_1 = _mm_and_si128(and_0, _mm_shuffle_epi32(ret, _MM_SHUFFLE(1, 0, 3, 2)));
        return static_cast<bool>(_mm_cvtsi128_si32(and_1));
    }
};

template<>
struct ktm::detail::vec_opt_implement::equal<4, int>
{
    using V = vec<4, int>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i t_y = _mm_load_si128(reinterpret_cast<const __m128i*>(&y[0]));
        __m128i ret = _mm_cmpeq_epi32(t_x, t_y);
        __m128i and_0 = _mm_and_si128(ret, _mm_shuffle_epi32(ret, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128i and_1 = _mm_and_si128(and_0, _mm_shuffle_epi32(and_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return static_cast<bool>(_mm_cvtsi128_si32(and_1));
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG
template<size_t N>
struct ktm::detail::vec_opt_implement::mul<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i t_y = _mm_load_si128(reinterpret_cast<const __m128i*>(&y[0]));
        __m128i ret = _mm_mullo_epi32(t_x, t_y);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i t_y = _mm_load_si128(reinterpret_cast<const __m128i*>(&y[0]));
        __m128i ret = _mm_mullo_epi32(t_x, t_y);
        _mm_store_si128(reinterpret_cast<__m128i*>(&x[0]), ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i ret = _mm_mullo_epi32(t_x, _mm_set1_epi32(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i ret = _mm_mullo_epi32(t_x, _mm_set1_epi32(scalar));
        _mm_store_si128(reinterpret_cast<__m128i*>(&x[0]), ret);
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

#endif

#endif
