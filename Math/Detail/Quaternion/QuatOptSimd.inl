#ifndef _QUAT_OPT_SIMD_INL_
#define _QUAT_OPT_SIMD_INL_

#include "QuatOptFwd.h"
#include "../../type/basic.h"

#if defined(CHTHOLLY_SIMD_NEON)

template<>
struct ktm::detail::quat_opt_implement::mul<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE Q call(const Q& x, const Q& y) noexcept
    {
        Q ret;
        ret.vector.st = neon::qt::fq_mul_fq(x.vector.st, y.vector.st);
        return ret;
    }
};

template<>
struct ktm::detail::quat_opt_implement::mul_to_self<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE void call(Q& x, const Q& y) noexcept
    {
        x.vector.st = neon::qt::fq_mul_fq(x.vector.st, y.vector.st);
    }
};

template<>
struct ktm::detail::quat_opt_implement::act<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE vec<3, float> call(const Q& q, const vec<3, float>& v) noexcept
    {
        // |q| = 1 => q-1 <==> qc
        // q * quat(v,0) * qc
        vec<3, float> ret;
        float32x4_t qi = vmulq_f32(q.vector.st, vsetq_lane_f32(one<float>, vdupq_n_f32(-one<float>), 3));
        ret.st = neon::qt::fq_mul_fq(q.vector.st, neon::qt::fv3_mul_fq(v.st, qi));
        return ret;
    }
};

#elif defined(CHTHOLLY_SIMD_SSE) 

template<>
struct ktm::detail::quat_opt_implement::mul<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE Q call(const Q& x, const Q& y) noexcept
    {
        Q ret;
        ret.vector.st = intrin::qt::fq_mul_fq(x.vector.st, y.vector.st);
        return ret;
    }
};

template<>
struct ktm::detail::quat_opt_implement::mul_to_self<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE void call(Q& x, const Q& y) noexcept
    {
        x.vector.st = intrin::qt::fq_mul_fq(x.vector.st, y.vector.st);
    }
};

template<>
struct ktm::detail::quat_opt_implement::act<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE vec<3, float> call(const Q& q, const vec<3, float>& v) noexcept
    {
        vec<3, float> ret;
        __m128 qi = _mm_mul_ps(q.vector.st, _mm_set_ps(one<float>, -one<float>, -one<float>, -one<float>));
        ret.st = intrin::qt::fq_mul_fq(q.vector.st, intrin::qt::fv3_mul_fq(v.st, qi));
        return ret;
    }
};

#endif

#endif