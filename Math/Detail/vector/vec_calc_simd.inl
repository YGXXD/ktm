#ifndef _KTM_VEC_CALC_SIMD_INL_
#define _KTM_VEC_CALC_SIMD_INL_

#include "vec_calc_fwd.h"
#include "../../type/basic.h"

#if defined(CHTHOLLY_SIMD_NEON)

template<>
struct ktm::detail::vec_calc_implement::add<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vadd_f32(x.st, y.st);
        return ret; 
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vaddq_f32(x.st, y.st);
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::add_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vadd_f32(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vaddq_f32(x.st, y.st);
    }
};

template<>
struct ktm::detail::vec_calc_implement::minus<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vsub_f32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vsubq_f32(x.st, y.st);
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::minus_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vsub_f32(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vsubq_f32(x.st, y.st);
    }
};

template<>
struct ktm::detail::vec_calc_implement::mul<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vmul_f32(x.st, y.st);
        return ret; 
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vmulq_f32(x.st, y.st);
        return ret; 
    }
};

template<>
struct ktm::detail::vec_calc_implement::mul_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vmul_f32(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vmulq_f32(x.st, y.st);
    }
};

template<>
struct ktm::detail::vec_calc_implement::div<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vdiv_f32(x.st, y.st);
        return ret; 
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::div<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {   
        V ret;
        ret.st = vdivq_f32(x.st, y.st);
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::div_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vdiv_f32(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::div_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vdivq_f32(x.st, y.st);
    }
};

template<>
struct ktm::detail::vec_calc_implement::opposite<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vneg_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::opposite<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vnegq_f32(x.st);
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::add_scalar<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        V ret;
        ret.st = vadd_f32(x.st, vdup_n_f32(scalar));
        return ret;
    }

};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        V ret;
        ret.st = vaddq_f32(x.st, vdupq_n_f32(scalar));
        return ret;
    }

};

template<>
struct ktm::detail::vec_calc_implement::add_scalar_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = vadd_f32(x.st, vdup_n_f32(scalar));
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = vaddq_f32(x.st, vdupq_n_f32(scalar));
    }
};

template<>
struct ktm::detail::vec_calc_implement::minus_scalar<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        V ret;
        ret.st = vsub_f32(x.st, vdup_n_f32(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        V ret;
        ret.st = vsubq_f32(x.st, vdupq_n_f32(scalar));
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::minus_scalar_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = vsub_f32(x.st, vdup_n_f32(scalar));
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = vsubq_f32(x.st, vdupq_n_f32(scalar));
    }
};

template<>
struct ktm::detail::vec_calc_implement::mul_scalar<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        V ret;
        ret.st = vmul_f32(x.st, vdup_n_f32(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        V ret;
        ret.st = vmulq_f32(x.st, vdupq_n_f32(scalar));
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::mul_scalar_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = vmul_f32(x.st, vdup_n_f32(scalar));
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = vmulq_f32(x.st, vdupq_n_f32(scalar));
    }
};

template<>
struct ktm::detail::vec_calc_implement::div_scalar<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {   
        V ret;
        ret.st = vdiv_f32(x.st, vdup_n_f32(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::div_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {  
        V ret;
        ret.st = vdivq_f32(x.st, vdupq_n_f32(scalar));
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::div_scalar_to_self<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = vdiv_f32(x.st, vdup_n_f32(scalar));
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::div_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = vdivq_f32(x.st, vdupq_n_f32(scalar));
    }
};

template<>
struct ktm::detail::vec_calc_implement::add<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vadd_s32(x.st, y.st);
        return ret; 
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vaddq_s32(x.st, y.st);
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::add_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vadd_s32(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vaddq_s32(x.st, y.st);
    }
};

template<>
struct ktm::detail::vec_calc_implement::minus<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vsub_s32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vsubq_s32(x.st, y.st);
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::minus_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vsub_s32(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vsubq_s32(x.st, y.st);
    }
};

template<>
struct ktm::detail::vec_calc_implement::mul<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vmul_s32(x.st, y.st);
        return ret; 
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vmulq_s32(x.st, y.st);
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::mul_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vmul_s32(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = vmulq_s32(x.st, y.st);
    }
};

template<>
struct ktm::detail::vec_calc_implement::opposite<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vneg_s32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::opposite<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vnegq_s32(x.st);
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::add_scalar<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        V ret;
        ret.st = vadd_s32(x.st, vdup_n_s32(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        V ret;
        ret.st = vaddq_s32(x.st, vdupq_n_s32(scalar));
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::add_scalar_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        x.st = vadd_s32(x.st, vdup_n_s32(scalar));
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        x.st = vaddq_s32(x.st, vdupq_n_s32(scalar));
    }
};

template<>
struct ktm::detail::vec_calc_implement::minus_scalar<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        V ret;
        ret.st = vsub_s32(x.st, vdup_n_s32(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        V ret;
        ret.st = vsubq_s32(x.st, vdupq_n_s32(scalar));
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::minus_scalar_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        x.st = vsub_s32(x.st, vdup_n_s32(scalar));
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        x.st = vsubq_s32(x.st, vdupq_n_s32(scalar));
    }
};

template<>
struct ktm::detail::vec_calc_implement::mul_scalar<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        V ret;
        ret.st = vmul_s32(x.st, vdup_n_s32(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        V ret;
        ret.st = vmulq_s32(x.st, vdupq_n_s32(scalar));
        return ret;
    }
};

template<>
struct ktm::detail::vec_calc_implement::mul_scalar_to_self<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        x.st = vmul_s32(x.st, vdup_n_s32(scalar));
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        x.st = vmulq_s32(x.st, vdupq_n_s32(scalar));
    }
};

#elif defined(CHTHOLLY_SIMD_SSE)

template<size_t N>
struct ktm::detail::vec_calc_implement::add<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_add_ps(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = _mm_add_ps(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_sub_ps(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = _mm_sub_ps(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_mul_ps(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = _mm_mul_ps(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::div<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_div_ps(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::div_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = _mm_div_ps(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::opposite<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        V ret;
	    ret.st = intrin::ex::neg_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        V ret;
	    ret.st = _mm_add_ps(x.st, _mm_set1_ps(scalar));
        return ret;
    }

};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = _mm_add_ps(x.st, _mm_set1_ps(scalar));
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        __m128 ret = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        __m128 ret = _mm_sub_ps(_mm_load_ps(&x[0]), _mm_set1_ps(scalar));
        _mm_store_ps(&x[0], ret);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        V ret;
	    ret.st = _mm_mul_ps(x.st, _mm_set1_ps(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = _mm_mul_ps(x.st, _mm_set1_ps(scalar));
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::div_scalar<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {   
        V ret;
	    ret.st = _mm_div_ps(x.st, _mm_set1_ps(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::div_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE void call(V& x, float scalar) noexcept
    {
        x.st = _mm_div_ps(x.st, _mm_set1_ps(scalar));
    }
};

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

template<size_t N>
struct ktm::detail::vec_calc_implement::add<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_add_epi32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = _mm_add_epi32(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_sub_epi32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = _mm_sub_epi32(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::opposite<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = intrin::ex::neg_epi32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        V ret;
        ret.st = _mm_add_epi32(x.st, _mm_set1_epi32(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::add_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        x.st = _mm_add_epi32(x.st, _mm_set1_epi32(scalar));
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        V ret;
        ret.st = _mm_sub_epi32(x.st, _mm_set1_epi32(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::minus_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        x.st = _mm_sub_epi32(x.st, _mm_set1_epi32(scalar));
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG
template<size_t N>
struct ktm::detail::vec_calc_implement::mul<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_mullo_epi32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        x.st = _mm_mullo_epi32(x.st, y.st);
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_scalar<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        V ret;
        ret.st = _mm_mullo_epi32(x.st, _mm_set1_epi32(scalar));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::vec_calc_implement::mul_scalar_to_self<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE void call(V& x, int scalar) noexcept
    {
        x.st = _mm_mullo_epi32(x.st, _mm_set1_epi32(scalar));
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

#endif

#endif