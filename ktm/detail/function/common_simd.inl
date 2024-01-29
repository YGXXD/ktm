#ifndef _KTM_COMMON_SIMD_INL_
#define _KTM_COMMON_SIMD_INL_

#include "common_fwd.h"
#include "../../simd/intrin.h"

#if defined(KTM_SIMD_ARM)

template<size_t L>
struct ktm::detail::common_implement::elem_move<L, 2, float>
{
    static_assert(L == 1);
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = neon_shuffle_f32(x.st, x.st, 0, L);
        return ret;
    }
};

template<size_t L>
struct ktm::detail::common_implement::elem_move<L, 3, float>
{
    static_assert(L > 0 && L < 3);
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        constexpr size_t i1 = 1 + L < 3 ? 1 + L : L - 2;
        constexpr size_t i2 = 2 + L < 3 ? 2 + L : L - 1; 
        ret.st = neon_shuffleq_f32(x.st, x.st, 3, i2, i1, L);
        return ret;
    }
};

template<size_t L>
struct ktm::detail::common_implement::elem_move<L, 4, float>
{
    static_assert(L > 0 && L < 4);
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        constexpr size_t i1 = 1 + L < 4 ? 1 + L : L - 3;
        constexpr size_t i2 = 2 + L < 4 ? 2 + L : L - 2; 
        constexpr size_t i3 = 3 + L < 4 ? 3 + L : L - 1;  
        ret.st = neon_shuffleq_f32(x.st, x.st, i3, i2, i1, L);
        return ret;
    }
};

template<size_t L>
struct ktm::detail::common_implement::elem_move<L, 2, int>
{
    static_assert(L == 1);
    using V = vec<2, int>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = neon_shuffle_s32(x.st, x.st, 0, L);
        return ret;
    }
};

template<size_t L>
struct ktm::detail::common_implement::elem_move<L, 3, int>
{
    static_assert(L > 0 && L < 3);
    using V = vec<3, int>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        constexpr size_t i1 = 1 + L < 3 ? 1 + L : L - 2;
        constexpr size_t i2 = 2 + L < 3 ? 2 + L : L - 1; 
        ret.st = neon_shuffleq_s32(x.st, x.st, 3, i2, i1, L);
        return ret;
    }
};

template<size_t L>
struct ktm::detail::common_implement::elem_move<L, 4, int>
{
    static_assert(L > 0 && L < 3);
    using V = vec<3, int>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        constexpr size_t i1 = 1 + L < 4 ? 1 + L : L - 3;
        constexpr size_t i2 = 2 + L < 4 ? 2 + L : L - 2; 
        constexpr size_t i3 = 3 + L < 4 ? 3 + L : L - 1;  
        ret.st = neon_shuffleq_s32(x.st, x.st, i3, i2, i1, L);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return arm::geo::fv2_radd(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return arm::geo::fv3_radd(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return arm::geo::fv4_radd(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<2, int>
{
    using V = vec<2, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return arm::geo::sv2_radd(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return arm::geo::sv3_radd(x.st); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return arm::geo::sv4_radd(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return arm::geo::fv2_rmin(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return arm::geo::fv3_rmin(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return arm::geo::fv4_rmin(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<2, int>
{
    using V = vec<2, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return arm::geo::sv2_rmin(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return arm::geo::sv3_rmin(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return arm::geo::sv4_rmin(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return arm::geo::fv2_rmax(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return arm::geo::fv3_rmax(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return arm::geo::fv4_rmax(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<2, int>
{
    using V = vec<2, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return arm::geo::sv2_rmax(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return arm::geo::sv3_rmax(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return arm::geo::sv4_rmax(x.st);
    }
};

template<>
struct ktm::detail::common_implement::abs<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vabs_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::abs<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vabsq_f32(x.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::abs<2, int>
{
    using V = vec<2, int>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vabs_s32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::abs<N, int, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vabsq_s32(x.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::min<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vminnm_f32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::min<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vminnmq_f32(x.st, y.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::min<2, int>
{
    using V = vec<2, int>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vmin_s32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::min<N, int, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vminq_s32(x.st, y.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::max<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vmaxnm_f32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::max<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vmaxnmq_f32(x.st, y.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::max<2, int>
{
    using V = vec<2, int>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vmax_s32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::max<N, int, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vmaxq_s32(x.st, y.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::clamp<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        ret.st = arm::ext::clamp_f32(v.st, min.st, max.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::clamp<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        ret.st = arm::ext::clampq_f32(v.st, min.st, max.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::clamp<2, int>
{
    using V = vec<2, int>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        ret.st = arm::ext::clamp_s32(v.st, min.st, max.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::clamp<N, int, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        ret.st = arm::ext::clampq_s32(v.st, min.st, max.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::floor<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::floor_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::floor<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::floorq_f32(x.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::ceil<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::ceil_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::ceil<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::ceilq_f32(x.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::round<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::round_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::round<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::roundq_f32(x.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::rsqrt<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::rsqrt_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::rsqrt<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::rsqrtq_f32(x.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::recip<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::recip_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::recip<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::recipq_f32(x.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::lerp<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x, const V& y, float t) noexcept
    {
        V ret;
        float32x2_t t_t = vdup_n_f32(t);
        ret.st = vadd_f32(x.st, vmul_f32(t_t, vsub_f32(y.st, x.st)));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::lerp<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x, const V& y, float t) noexcept
    {
        V ret;
        float32x4_t t_t = vdupq_n_f32(t);
        ret.st = vaddq_f32(x.st, vmulq_f32(t_t, vsubq_f32(y.st, x.st)));
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::mix<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        V ret;
        ret.st = vadd_f32(x.st, vmul_f32(t.st, vsub_f32(y.st, x.st)));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::mix<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        V ret;
        ret.st = vaddq_f32(x.st, vmulq_f32(t.st, vsubq_f32(y.st, x.st)));
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::step<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& edge, const V& x) noexcept
    {
        V ret;
        uint32x2_t cmp = vclt_f32(x.st, edge.st);
        uint32x2_t tmp = vand_u32(vreinterpret_u32_f32(vdup_n_f32(1.f)), cmp);
        ret.st = vreinterpret_f32_u32(tmp);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::step<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& edge, const V& x) noexcept
    {
        V ret;
        uint32x4_t cmp = vcltq_f32(x.st, edge.st);
        uint32x4_t tmp = vandq_u32(vreinterpretq_u32_f32(vdupq_n_f32(1.f)), cmp);
        ret.st = vreinterpretq_f32_u32(tmp);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::smoothstep<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        V ret;
        float32x2_t tmp = arm::ext::div_f32(vsub_f32(x.st, edge0.st), vsub_f32(edge1.st, edge0.st));
        tmp = arm::ext::clamp_f32(tmp, vdup_n_f32(0.f), vdup_n_f32(1.f));
        ret.st = vmul_f32(vmul_f32(tmp, tmp), vsub_f32(vdup_n_f32(3.f), vmul_f32(vdup_n_f32(2.f), tmp)));
        return ret;
    }
};


template<size_t N>
struct ktm::detail::common_implement::smoothstep<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        V ret;
        float32x4_t tmp = arm::ext::divq_f32(vsubq_f32(x.st, edge0.st), vsubq_f32(edge1.st, edge0.st));
        tmp = arm::ext::clampq_f32(tmp, vdupq_n_f32(0.f), vdupq_n_f32(1.f));
        ret.st = vmulq_f32(vmulq_f32(tmp, tmp), vsubq_f32(vdupq_n_f32(3.f), vmulq_f32(vdupq_n_f32(2.f), tmp)));
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::fract<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        float32x2_t floor = arm::ext::floor_f32(x.st);
        ret.st = vsub_f32(x.st, floor);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::fract<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        float32x4_t floor = arm::ext::floorq_f32(x.st);
        ret.st = vsubq_f32(x.st, floor);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::fast_rsqrt<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::fast_rsqrt_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::fast_rsqrt<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::fast_rsqrtq_f32(x.st);
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::fast_recip<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::fast_recip_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::fast_recip<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = arm::ext::fast_recipq_f32(x.st);
        return ret;
    }
};

#if KTM_SIMD_ARM & KTM_SIMD_A64_FLAG

template<>
struct ktm::detail::common_implement::sqrt<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vsqrt_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::sqrt<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vsqrtq_f32(x.st);
        return ret;
    }
};

#endif

#elif defined(KTM_SIMD_X86)

template<size_t L>
struct ktm::detail::common_implement::elem_move<L, 3, float>
{
    static_assert(L > 0 && L < 3);
    using V = vec<3, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        constexpr size_t i1 = 1 + L < 3 ? 1 + L : L - 2;
        constexpr size_t i2 = 2 + L < 3 ? 2 + L : L - 1; 
        ret.st = _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(3, i2, i1, L));
        return ret;
    }
};

template<size_t L>
struct ktm::detail::common_implement::elem_move<L, 4, float>
{
    static_assert(L > 0 && L < 4);
    using V = vec<4, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        constexpr size_t i1 = 1 + L < 4 ? 1 + L : L - 3;
        constexpr size_t i2 = 2 + L < 4 ? 2 + L : L - 2; 
        constexpr size_t i3 = 3 + L < 4 ? 3 + L : L - 1; 
        ret.st = _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(i3, i2, i1, L));
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return x86::geo::fv3_radd(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return x86::geo::fv4_radd(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return x86::geo::fv3_rmin(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return x86::geo::fv4_rmin(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return x86::geo::fv3_rmax(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return x86::geo::fv4_rmax(x.st);  
    }
};

template<size_t N>
struct ktm::detail::common_implement::abs<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = x86::ext::abs_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::min<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_min_ps(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::max<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_max_ps(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::clamp<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        ret.st = x86::ext::clamp_ps(v.st, min.st, max.st);
        return ret; 
    }
};

template<size_t N>
struct ktm::detail::common_implement::floor<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = x86::ext::floor_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::ceil<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = x86::ext::ceil_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::round<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = x86::ext::round_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::sqrt<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = _mm_sqrt_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::rsqrt<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = x86::ext::rsqrt_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::recip<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = x86::ext::recip_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::lerp<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x, const V& y, float t) noexcept
    {
        V ret;
        __m128 t_t = _mm_set1_ps(t);
        ret.st = _mm_add_ps(x.st, _mm_mul_ps(t_t, _mm_sub_ps(y.st, x.st)));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::mix<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        V ret;
        ret.st = _mm_add_ps(x.st, _mm_mul_ps(t.st, _mm_sub_ps(y.st, x.st)));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::step<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& edge, const V& x) noexcept
    {
        V ret;
        __m128 cmp = _mm_cmplt_ps(x.st, edge.st);
        ret.st = _mm_and_ps(_mm_set1_ps(1.f), cmp);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::smoothstep<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        V ret;
        __m128 tmp = _mm_div_ps(_mm_sub_ps(x.st, edge0.st), _mm_sub_ps(edge1.st, edge0.st));
        tmp = x86::ext::clamp_ps(tmp, _mm_setzero_ps(), _mm_set1_ps(1.f));
        ret.st = _mm_mul_ps(_mm_mul_ps(tmp, tmp), _mm_sub_ps(_mm_set1_ps(3.f), _mm_mul_ps(_mm_set1_ps(2.f), tmp)));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::fract<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        __m128 floor = x86::ext::floor_ps(x.st);
        ret.st = _mm_sub_ps(x.st, floor);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::fast_rsqrt<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = x86::ext::fast_rsqrt_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::fast_recip<N, float, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = x86::ext::fast_recip_ps(x.st);
        return ret;
    }
};

#if KTM_SIMD_X86 & KTM_SIMD_SSE2_FLAG

template<size_t L>
struct ktm::detail::common_implement::elem_move<L, 3, int>
{
    static_assert(L > 0 && L < 3);
    using V = vec<3, int>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        constexpr size_t i1 = 1 + L < 3 ? 1 + L : L - 2;
        constexpr size_t i2 = 2 + L < 3 ? 2 + L : L - 1; 
        ret.st = _mm_shuffle_epi32(x.st, _MM_SHUFFLE(3, i2, i1, L));
        return ret;
    }
};

template<size_t L>
struct ktm::detail::common_implement::elem_move<L, 4, int>
{
    static_assert(L > 0 && L < 4);
    using V = vec<4, int>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        constexpr size_t i1 = 1 + L < 4 ? 1 + L : L - 3;
        constexpr size_t i2 = 2 + L < 4 ? 2 + L : L - 2; 
        constexpr size_t i3 = 3 + L < 4 ? 3 + L : L - 1;  
        ret.st = _mm_shuffle_epi32(x.st, _MM_SHUFFLE(i3, i2, i1, L));
        return ret;
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return x86::geo::sv3_radd(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return x86::geo::sv4_radd(x.st);
    }
};

template<size_t N>
struct ktm::detail::common_implement::abs<N, int, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = x86::ext::abs_epi32(x.st);
        return ret;
    }
};

#endif // KTM_SIMD_X86 & KTM_SIMD_SSE2_FLAG

#if KTM_SIMD_X86 & KTM_SIMD_SSE4_1_FLAG

template<>
struct ktm::detail::common_implement::reduce_min<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return x86::geo::sv3_rmin(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return x86::geo::sv4_rmin(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return x86::geo::sv3_rmax(x.st); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return x86::geo::sv4_rmax(x.st);
    }
};

template<size_t N>
struct ktm::detail::common_implement::min<N, int, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_min_epi32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::max<N, int, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = _mm_max_epi32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::clamp<N, int, std::enable_if_t<N == 3 || N == 4>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        ret.st = x86::ext::clamp_epi32(v.st, min.st, max.st);
        return ret; 
    }
};

#endif // KTM_SIMD_X86 & KTM_SIMD_SSE4_1_FLAG

#endif

#endif
