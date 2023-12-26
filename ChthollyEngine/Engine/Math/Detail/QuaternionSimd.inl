#ifndef _QUATERNION_SIMD_INL_
#define _QUATERNION_SIMD_INL_

#include "QuatOptFwd.h"
#include "Math/Library/ArtcBase.h"

#if defined(CHTHOLLY_SIMD_NEON)

namespace ktm
{
namespace detail
{
namespace quat_opt_implement
{
CHTHOLLY_FUNC float32x4_t mul_vq(float32x4_t v, float32x4_t q) noexcept
{
    float32x4_t q_opp = vnegq_f32(q);

    float32x4_t tmp_0 = neon_shuffleq_f32(q, q_opp, 2, 2, 3, 3);
    float32x4_t tmp_1 = neon_shuffleq_f32(q, q_opp, 1, 0, 1, 0); 

    float32x4_t mul_x = neon_shuffleq_f32(tmp_0, tmp_1, 2, 1, 3, 0); 
    float32x4_t mul_y = neon_shuffleq_f32(q, q_opp, 1, 0, 3, 2); 
    float32x4_t mul_z = neon_shuffleq_f32(tmp_1, tmp_0, 2, 1, 0, 3);

    float32x4_t add_0 = vmulq_f32(vdupq_laneq_f32(v, 0), mul_x); 
    float32x4_t add_1 = vmulq_f32(vdupq_laneq_f32(v, 1), mul_y); 
    float32x4_t add_2 = vmulq_f32(vdupq_laneq_f32(v, 2), mul_z); 

    return neon::addq_f32_all(add_0, add_1, add_2); 
}

CHTHOLLY_FUNC float32x4_t mul_qq(float32x4_t x, float32x4_t y) noexcept
{
    float32x4_t add_012 = mul_vq(x, y);
    float32x4_t add_3 = vmulq_f32(vdupq_laneq_f32(x, 3), y); 
    return vaddq_f32(add_012, add_3);
}
}
}
}

template<>
struct ktm::detail::quat_opt_implement::mul<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE Q call(const Q& x, const Q& y) noexcept
    {
        float32x4_t t_x = vld1q_f32(&x[0]);
        float32x4_t t_y = vld1q_f32(&y[0]);
        float32x4_t ret = mul_qq(t_x, t_y);
        return *reinterpret_cast<Q*>(&ret);
    }
};

template<>
struct ktm::detail::quat_opt_implement::mul_to_self<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE void call(Q& x, const Q& y) noexcept
    {
        float32x4_t t_x = vld1q_f32(&x[0]);
        float32x4_t t_y = vld1q_f32(&y[0]);
        float32x4_t ret = mul_qq(t_x, t_y);
        vst1q_f32(&x[0], ret);
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
        float32x4_t t_q = vld1q_f32(&q[0]);
        float32x4_t t_qi = vmulq_f32(t_q, vsetq_lane_f32(one<float>, vdupq_n_f32(-one<float>), 3));
        float32x4_t t_v = vld1q_f32(&v[0]);
        float32x4_t ret = mul_qq(t_q, mul_vq(t_v, t_qi));
        return *reinterpret_cast<vec<3, float>*>(&ret);
    }
};

#elif defined(CHTHOLLY_SIMD_SSE) 

namespace ktm
{
namespace detail
{
namespace quat_opt_implement
{
CHTHOLLY_FUNC __m128 mul_vq(__m128 v, __m128 q) noexcept
{
    __m128 q_opp = intrin::neg_ps(q);

    __m128 tmp_0 = _mm_shuffle_ps(q, q_opp, _MM_SHUFFLE(2, 2, 3, 3));
    __m128 tmp_1 = _mm_shuffle_ps(q, q_opp, _MM_SHUFFLE(1, 0, 1, 0)); 

    __m128 mul_x = _mm_shuffle_ps(tmp_0, tmp_1, _MM_SHUFFLE(2, 1, 3, 0)); 
    __m128 mul_y = _mm_shuffle_ps(q, q_opp, _MM_SHUFFLE(1, 0, 3, 2)); 
    __m128 mul_z = _mm_shuffle_ps(tmp_1, tmp_0, _MM_SHUFFLE(2, 1, 0, 3));

    __m128 add_0 = _mm_mul_ps(_mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0)), mul_x); 
    __m128 add_1 = _mm_mul_ps(_mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1)), mul_y); 
    __m128 add_2 = _mm_mul_ps(_mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2)), mul_z); 

    return intrin::add_ps_all(add_0, add_1, add_2);
}

CHTHOLLY_FUNC __m128 mul_qq(__m128 x, __m128 y) noexcept
{
    __m128 add_012 = mul_vq(x, y);
    __m128 add_3 = _mm_mul_ps(_mm_shuffle_ps(x, x, _MM_SHUFFLE(3, 3, 3, 3)), y); 
    return _mm_add_ps(add_012, add_3);
}
}
}
}

template<>
struct ktm::detail::quat_opt_implement::mul<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE Q call(const Q& x, const Q& y) noexcept
    {
        __m128 t_x = _mm_load_ps(&x[0]); 
        __m128 t_y = _mm_load_ps(&y[0]);
        __m128 ret = mul_qq(t_x, t_y);
        return *reinterpret_cast<Q*>(&ret);
    }
};

template<>
struct ktm::detail::quat_opt_implement::mul_to_self<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE void call(Q& x, const Q& y) noexcept
    {
        __m128 t_x = _mm_load_ps(&x[0]); 
        __m128 t_y = _mm_load_ps(&y[0]);
        __m128 ret = mul_qq(t_x, t_y);
        _mm_store_ps(&x[0], ret);
    }
};

template<>
struct ktm::detail::quat_opt_implement::act<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE vec<3, float> call(const Q& q, const vec<3, float>& v) noexcept
    {
        __m128 t_q = _mm_load_ps(&q[0]);
        __m128 t_qi = _mm_mul_ps(t_q, _mm_set_ps(one<float>, -one<float>, -one<float>, -one<float>));
        __m128 t_v = _mm_load_ps(&v[0]);
        __m128 ret = mul_qq(t_q, mul_vq(t_v, t_qi));
        return *reinterpret_cast<vec<3, float>*>(&ret);
    }
};

#endif

#endif