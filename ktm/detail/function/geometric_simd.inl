#ifndef _KTM_GEOMETRIC_SIMD_INL_
#define _KTM_GEOMETRIC_SIMD_INL_

#include "geometric_fwd.h"
#include "../../simd/intrin.h"

#if defined(KTM_SIMD_ARM)

template<>
struct ktm::detail::geometric_implement::dot<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        return vget_lane_f32(arm::geo::fv2_dot1(x.st, y.st), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::dot<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        return vgetq_lane_f32(arm::geo::fv3_dot1(x.st, y.st), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::dot<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        return vgetq_lane_f32(arm::geo::fv4_dot1(x.st, y.st), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::project<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        float32x2_t dot_xy = arm::geo::fv2_dot(x.st, y.st);
        float32x2_t dot_yy = arm::geo::fv2_dot(y.st, y.st);
        ret.st = vmul_f32(arm::ext::div_f32(dot_xy, dot_yy), y.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::project<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        float32x4_t dot_xy = arm::geo::fv3_dot(x.st, y.st);
        float32x4_t dot_yy = arm::geo::fv3_dot(y.st, y.st);
        ret.st = vmulq_f32(arm::ext::divq_f32(dot_xy, dot_yy), y.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::project<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        float32x4_t dot_xy = arm::geo::fv4_dot(x.st, y.st);
        float32x4_t dot_yy = arm::geo::fv4_dot(y.st, y.st);
        ret.st = vmulq_f32(arm::ext::divq_f32(dot_xy, dot_yy), y.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::cross<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        float32x4_t s_x = neon_shuffleq_f32(x.st, x.st, 3, 1, 0, 2);
        float32x4_t s_y = neon_shuffleq_f32(y.st, y.st, 3, 1, 0, 2);
        float32x4_t s_r = vsubq_f32(vmulq_f32(s_x, y.st), vmulq_f32(x.st, s_y));
        ret.st = neon_shuffleq_f32(s_r, s_r, 3, 1, 0, 2);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::normalize<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        float32x2_t dot = arm::geo::fv2_dot(x.st, x.st);
        float32x2_t rsq = arm::ext::rsqrt_f32(dot);
        ret.st = vmul_f32(rsq, x.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::normalize<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        float32x4_t dot = arm::geo::fv3_dot(x.st, x.st);
        float32x4_t rsq = arm::ext::rsqrtq_f32(dot);
        ret.st = vmulq_f32(rsq, x.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::normalize<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        float32x4_t dot = arm::geo::fv4_dot(x.st, x.st);
        float32x4_t rsq = arm::ext::rsqrtq_f32(dot);
        ret.st = vmulq_f32(rsq, x.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::reflect<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x, const V& n) noexcept
    {
        V ret;
        float32x2_t dot = arm::geo::fv2_dot(x.st, n.st);
        float32x2_t mul_0 = vmul_f32(n.st, dot);
        float32x2_t mul_1 = vmul_f32(mul_0, vdup_n_f32(2.0f));
        ret.st = vsub_f32(x.st, mul_1);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::reflect<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& n) noexcept
    {
        V ret;
        float32x4_t dot = arm::geo::fv3_dot(x.st, n.st);
        float32x4_t mul_0 = vmulq_f32(n.st, dot);
        float32x4_t mul_1 = vmulq_f32(mul_0, vdupq_n_f32(2.0f));
        ret.st = vsubq_f32(x.st, mul_1);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::reflect<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x, const V& n) noexcept
    {
        V ret;
        float32x4_t dot = arm::geo::fv4_dot(x.st, n.st);
        float32x4_t mul_0 = vmulq_f32(n.st, dot);
        float32x4_t mul_1 = vmulq_f32(mul_0, vdupq_n_f32(2.0f));
        ret.st = vsubq_f32(x.st, mul_1);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::fast_project<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        float32x2_t dot_xy = arm::geo::fv2_dot(x.st, y.st);
        float32x2_t dot_yy = arm::geo::fv2_dot(y.st, y.st);
        ret.st = vmul_f32(vmul_f32(dot_xy, arm::ext::fast_recip_f32(dot_yy)), y.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::fast_project<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        float32x4_t dot_xy = arm::geo::fv3_dot(x.st, y.st);
        float32x4_t dot_yy = arm::geo::fv3_dot(y.st, y.st);
        ret.st = vmulq_f32(vmulq_f32(dot_xy, arm::ext::fast_recipq_f32(dot_yy)), y.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::fast_project<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        float32x4_t dot_xy = arm::geo::fv4_dot(x.st, y.st);
        float32x4_t dot_yy = arm::geo::fv4_dot(y.st, y.st);
        ret.st = vmulq_f32(vmulq_f32(dot_xy, arm::ext::fast_recipq_f32(dot_yy)), y.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::fast_length<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vget_lane_f32(arm::geo::fv2_fast_length1(x.st), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::fast_length<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vgetq_lane_f32(arm::geo::fv3_fast_length1(x.st), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::fast_length<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vgetq_lane_f32(arm::geo::fv4_fast_length1(x.st), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::fast_distance<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        float32x2_t sub = vsub_f32(x.st, y.st);
        return vget_lane_f32(arm::geo::fv2_fast_length1(sub), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::fast_distance<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        float32x4_t sub = vsubq_f32(x.st, y.st);
        return vgetq_lane_f32(arm::geo::fv3_fast_length1(sub), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::fast_distance<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        float32x4_t sub = vsubq_f32(x.st, y.st);
        return vgetq_lane_f32(arm::geo::fv4_fast_length1(sub), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::fast_normalize<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        float32x2_t dot = arm::geo::fv2_dot(x.st, x.st);
        float32x2_t rsq = arm::ext::fast_rsqrt_f32(dot);
        ret.st = vmul_f32(rsq, x.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::fast_normalize<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        float32x4_t dot = arm::geo::fv3_dot(x.st, x.st);
        float32x4_t rsq = arm::ext::fast_rsqrtq_f32(dot);
        ret.st = vmulq_f32(rsq, x.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::fast_normalize<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        float32x4_t dot = arm::geo::fv4_dot(x.st, x.st);
        float32x4_t rsq = arm::ext::fast_rsqrtq_f32(dot);
        ret.st = vmulq_f32(rsq, x.st);
        return ret;
    }
};

#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG

template<>
struct ktm::detail::geometric_implement::length<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vget_lane_f32(arm::geo::fv2_length1(x.st), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::length<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vgetq_lane_f32(arm::geo::fv3_length1(x.st), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::length<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vgetq_lane_f32(arm::geo::fv4_length1(x.st), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::distance<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        float32x2_t sub = vsub_f32(x.st, y.st);
        return vget_lane_f32(arm::geo::fv2_length1(sub), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::distance<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        float32x4_t sub = vsubq_f32(x.st, y.st);
        return vgetq_lane_f32(arm::geo::fv3_length1(sub), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::distance<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        float32x4_t sub = vsubq_f32(x.st, y.st);
        return vgetq_lane_f32(arm::geo::fv4_length1(sub), 0);
    }
};

template<>
struct ktm::detail::geometric_implement::refract<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x, const V& n, float eta) noexcept
    {
        float32x2_t t_eta = vdup_n_f32(eta);
        float32x2_t one = vdup_n_f32(1.f);
        float32x2_t dot = arm::geo::fv2_dot(n.st, x.st);
        float32x2_t eta2 = vmul_f32(t_eta, t_eta);
        float32x2_t one_minus_cos2 = vsub_f32(one, vmul_f32(dot, dot));
        float32x2_t k = vsub_f32(one, vmul_f32(eta2, one_minus_cos2));
        if(vget_lane_f32(vcge_f32(k, vdup_n_f32(0.f)), 0) == 0)
            return V();
        V ret;
        float32x2_t sqrt_k = vsqrt_f32(k);
        float32x2_t fma = arm::ext::fma_f32(sqrt_k, t_eta, dot);
        ret.st = vsub_f32(vmul_f32(t_eta, x.st), vmul_f32(fma, n.st));
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::refract<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& n, float eta) noexcept
    {
        float32x4_t t_eta = vdupq_n_f32(eta);
        float32x4_t one = vdupq_n_f32(1.f);
        float32x4_t dot = arm::geo::fv3_dot(n.st, x.st);
        float32x4_t eta2 = vmulq_f32(t_eta, t_eta);
        float32x4_t one_minus_cos2 = vsubq_f32(one, vmulq_f32(dot, dot));
        float32x4_t k = vsubq_f32(one, vmulq_f32(eta2, one_minus_cos2));
        if(vgetq_lane_f32(vcgeq_f32(k, vdupq_n_f32(0.f)), 0) == 0)
            return V();
        V ret;
        float32x4_t sqrt_k = vsqrtq_f32(k);
        float32x4_t fma = arm::ext::fmaq_f32(sqrt_k, t_eta, dot);
        ret.st = vsubq_f32(vmulq_f32(t_eta, x.st), vmulq_f32(fma, n.st));
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::refract<4, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& n, float eta) noexcept
    {
        float32x4_t t_eta = vdupq_n_f32(eta);
        float32x4_t one = vdupq_n_f32(1.f);
        float32x4_t dot = arm::geo::fv4_dot(n.st, x.st);
        float32x4_t eta2 = vmulq_f32(t_eta, t_eta);
        float32x4_t one_minus_cos2 = vsubq_f32(one, vmulq_f32(dot, dot));
        float32x4_t k = vsubq_f32(one, vmulq_f32(eta2, one_minus_cos2));
        if(vgetq_lane_f32(vcgeq_f32(k, vdupq_n_f32(0.f)), 0) == 0)
            return V();
        V ret;
        float32x4_t sqrt_k = vsqrtq_f32(k);
        float32x4_t fma = arm::ext::fmaq_f32(sqrt_k, t_eta, dot);
        ret.st = vsubq_f32(vmulq_f32(t_eta, x.st), vmulq_f32(fma, n.st));
        return ret;
    }
};

#endif

#elif defined(KTM_SIMD_X86)

template<>
struct ktm::detail::geometric_implement::dot<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        return _mm_cvtss_f32(x86::geo::fv3_dot1(x.st, y.st));
    }
};

template<>
struct ktm::detail::geometric_implement::dot<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        return _mm_cvtss_f32(x86::geo::fv4_dot1(x.st, y.st));
    }
};

template<>
struct ktm::detail::geometric_implement::project<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        __m128 dot_xy = x86::geo::fv3_dot(x.st, y.st);
        __m128 dot_yy = x86::geo::fv3_dot(y.st, y.st);
        ret.st = _mm_mul_ps(_mm_div_ps(dot_xy, dot_yy), y.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::project<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        __m128 dot_xy = x86::geo::fv4_dot(x.st, y.st);
        __m128 dot_yy = x86::geo::fv4_dot(y.st, y.st);
        ret.st = _mm_mul_ps(_mm_div_ps(dot_xy, dot_yy), y.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::cross<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        __m128 s_x = _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 s_y = _mm_shuffle_ps(y.st, y.st, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 s_r = _mm_sub_ps(_mm_mul_ps(s_x, y.st), _mm_mul_ps(x.st, s_y));
        ret.st = _mm_shuffle_ps(s_r, s_r, _MM_SHUFFLE(3, 1, 0, 2));
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::length<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return _mm_cvtss_f32(x86::geo::fv3_length1(x.st));
    }
};

template<>
struct ktm::detail::geometric_implement::length<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return _mm_cvtss_f32(x86::geo::fv4_length1(x.st));
    }
};

template<>
struct ktm::detail::geometric_implement::distance<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        __m128 sub = _mm_sub_ps(x.st, y.st);
        return _mm_cvtss_f32(x86::geo::fv3_length1(sub));
    }
};

template<>
struct ktm::detail::geometric_implement::distance<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        __m128 sub = _mm_sub_ps(x.st, y.st);
        return _mm_cvtss_f32(x86::geo::fv4_length1(sub));
    }
};

template<>
struct ktm::detail::geometric_implement::normalize<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        __m128 dot = x86::geo::fv3_dot(x.st, x.st);
        __m128 rsq = x86::ext::rsqrt_ps(dot);
        ret.st = _mm_mul_ps(rsq, x.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::normalize<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        __m128 dot = x86::geo::fv4_dot(x.st, x.st);
        __m128 rsq = x86::ext::rsqrt_ps(dot);
        ret.st = _mm_mul_ps(rsq, x.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::reflect<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& n) noexcept
    {
        V ret;
        __m128 dot = x86::geo::fv3_dot(x.st, n.st);
        __m128 mul_0 = _mm_mul_ps(n.st, dot);
        __m128 mul_1 = _mm_mul_ps(mul_0, _mm_set1_ps(2.0f));
        ret.st = _mm_sub_ps(x.st, mul_1);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::reflect<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x, const V& n) noexcept
    {
        V ret;
        __m128 dot = x86::geo::fv4_dot(x.st, n.st);
        __m128 mul_0 = _mm_mul_ps(n.st, dot);
        __m128 mul_1 = _mm_mul_ps(mul_0, _mm_set1_ps(2.0f));
        ret.st = _mm_sub_ps(x.st, mul_1);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::refract<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& n, float eta) noexcept
    {
        __m128 t_eta = _mm_set1_ps(eta);
        __m128 one = _mm_set1_ps(1.f);
        __m128 dot = x86::geo::fv3_dot(n.st, x.st);
        __m128 eta2 = _mm_mul_ps(t_eta, t_eta);
        __m128 one_minus_cos2 = _mm_sub_ps(one, _mm_mul_ps(dot, dot));
        __m128 k = _mm_sub_ps(one, _mm_mul_ps(eta2, one_minus_cos2));
        if(_mm_movemask_ps(_mm_cmpge_ps(k, _mm_setzero_ps())) == 0)
            return V();
        V ret;
        __m128 sqrt_k = _mm_sqrt_ps(k);
        __m128 fma = _mm_add_ps(sqrt_k, _mm_mul_ps(t_eta, dot));
        ret.st = _mm_sub_ps(_mm_mul_ps(t_eta, x.st), _mm_mul_ps(fma, n.st));
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::refract<4, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& n, float eta) noexcept
    {
        __m128 t_eta = _mm_set1_ps(eta);
        __m128 one = _mm_set1_ps(1.f);
        __m128 dot = x86::geo::fv4_dot(n.st, x.st);
        __m128 eta2 = _mm_mul_ps(t_eta, t_eta);
        __m128 one_minus_cos2 = _mm_sub_ps(one, _mm_mul_ps(dot, dot));
        __m128 k = _mm_sub_ps(one, _mm_mul_ps(eta2, one_minus_cos2));
        if(_mm_movemask_ps(_mm_cmpge_ps(k, _mm_setzero_ps())) == 0)
            return V();
        V ret;
        __m128 sqrt_k = _mm_sqrt_ps(k);
        __m128 fma = _mm_add_ps(sqrt_k, _mm_mul_ps(t_eta, dot));
        ret.st = _mm_sub_ps(_mm_mul_ps(t_eta, x.st), _mm_mul_ps(fma, n.st));
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::fast_project<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        __m128 dot_xy = x86::geo::fv3_dot(x.st, y.st);
        __m128 dot_yy = x86::geo::fv3_dot(y.st, y.st);
        ret.st = _mm_mul_ps(_mm_mul_ps(dot_xy, x86::ext::fast_recip_ps(dot_yy)), y.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::fast_project<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        __m128 dot_xy = x86::geo::fv4_dot(x.st, y.st);
        __m128 dot_yy = x86::geo::fv4_dot(y.st, y.st);
        ret.st = _mm_mul_ps(_mm_mul_ps(dot_xy, x86::ext::fast_recip_ps(dot_yy)), y.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::fast_length<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return _mm_cvtss_f32(x86::geo::fv3_fast_length1(x.st));
    }
};

template<>
struct ktm::detail::geometric_implement::fast_length<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return _mm_cvtss_f32(x86::geo::fv4_fast_length1(x.st));
    }
};

template<>
struct ktm::detail::geometric_implement::fast_distance<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        __m128 sub = _mm_sub_ps(x.st, y.st);
        return _mm_cvtss_f32(x86::geo::fv3_fast_length1(sub));
    }
};

template<>
struct ktm::detail::geometric_implement::fast_distance<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x, const V& y) noexcept
    {
        __m128 sub = _mm_sub_ps(x.st, y.st);
        return _mm_cvtss_f32(x86::geo::fv4_fast_length1(sub));
    }
};

template<>
struct ktm::detail::geometric_implement::fast_normalize<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        __m128 dot = x86::geo::fv3_dot(x.st, x.st);
        __m128 rsq = x86::ext::fast_rsqrt_ps(dot);
        ret.st = _mm_mul_ps(rsq, x.st);
        return ret;
    }
};

template<>
struct ktm::detail::geometric_implement::fast_normalize<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        __m128 dot = x86::geo::fv4_dot(x.st, x.st);
        __m128 rsq = x86::ext::fast_rsqrt_ps(dot);
        ret.st = _mm_mul_ps(rsq, x.st);
        return ret;
    }
};

#endif

#endif