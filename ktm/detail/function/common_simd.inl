#ifndef _KTM_COMMON_SIMD_INL_
#define _KTM_COMMON_SIMD_INL_

#include "common_fwd.h"
#include "../../setup.h"
#include "../../type/basic.h"

#if defined(KTM_SIMD_NEON)

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
        return vaddv_f32(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vaddvq_f32(vsetq_lane_f32(zero<float>, x.st, 3)); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vaddvq_f32(x.st); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<2, int>
{
    using V = vec<2, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return vaddv_s32(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return vaddvq_s32(vsetq_lane_s32(zero<int>, x.st, 3)); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return vaddvq_s32(x.st); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vminv_f32(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vminvq_f32(vcopyq_laneq_f32(x.st, 3, x.st, 2));
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vminvq_f32(x.st); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<2, int>
{
    using V = vec<2, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return vminv_s32(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return vminvq_s32(vcopyq_laneq_s32(x.st, 3, x.st, 2)); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return vminvq_s32(x.st); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vmaxv_f32(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vmaxvq_f32(vcopyq_laneq_f32(x.st, 3, x.st, 2)); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        return vmaxvq_f32(x.st); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<2, int>
{
    using V = vec<2, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return vmaxv_s32(x.st);
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return vmaxvq_s32(vcopyq_laneq_s32(x.st, 3, x.st, 2)); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        return vmaxvq_s32(x.st); 
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
struct ktm::detail::common_implement::abs<N, std::enable_if_t<N == 3 || N == 4, float>>
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
struct ktm::detail::common_implement::abs<N, std::enable_if_t<N == 3 || N == 4, int>>
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
        ret.st = vmin_f32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::min<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vminq_f32(x.st, y.st);
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
struct ktm::detail::common_implement::min<N, std::enable_if_t<N == 3 || N == 4, int>>
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
        ret.st = vmax_f32(x.st, y.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::max<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        ret.st = vmaxq_f32(x.st, y.st);
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
struct ktm::detail::common_implement::max<N, std::enable_if_t<N == 3 || N == 4, int>>
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
        ret.st = neon::ext::clamp_f32(v.st, min.st, max.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::clamp<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        ret.st = neon::ext::clampq_f32(v.st, min.st, max.st);
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
        ret.st = neon::ext::clamp_s32(v.st, min.st, max.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::clamp<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        ret.st = neon::ext::clampq_s32(v.st, min.st, max.st);
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
        ret.st = vrndm_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::floor<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vrndmq_f32(x.st);
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
        ret.st = vrndp_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::ceil<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vrndpq_f32(x.st);
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
        ret.st = vrndi_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::round<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = vrndiq_f32(x.st);
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
struct ktm::detail::common_implement::lerp<N, std::enable_if_t<N == 3 || N == 4, float>>
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
struct ktm::detail::common_implement::mix<N, std::enable_if_t<N == 3 || N == 4, float>>
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
struct ktm::detail::common_implement::recip<2, float>
{
    using V = vec<2, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = neon::ext::recip_f32(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::recip<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = neon::ext::recipq_f32(x.st);
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
        uint32x2_t tmp = vand_u32(vreinterpret_u32_f32(vdup_n_f32(one<float>)), cmp);
        ret.st = vreinterpret_f32_u32(tmp);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::step<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& edge, const V& x) noexcept
    {
        V ret;
        uint32x4_t cmp = vcltq_f32(x.st, edge.st);
        uint32x4_t tmp = vandq_u32(vreinterpretq_u32_f32(vdupq_n_f32(one<float>)), cmp);
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
        float32x2_t tmp = vdiv_f32(vsub_f32(x.st, edge0.st), vsub_f32(edge1.st, edge0.st));
        tmp = neon::ext::clamp_f32(tmp, vdup_n_f32(zero<float>), vdup_n_f32(one<float>));
        ret.st = vmul_f32(vmul_f32(tmp, tmp), vsub_f32(vdup_n_f32(3.f), vmul_f32(vdup_n_f32(2.f), tmp)));
        return ret;
    }
};


template<size_t N>
struct ktm::detail::common_implement::smoothstep<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        V ret;
        float32x4_t tmp = vdivq_f32(vsubq_f32(x.st, edge0.st), vsubq_f32(edge1.st, edge0.st));
        tmp = neon::ext::clampq_f32(tmp, vdupq_n_f32(zero<float>), vdupq_n_f32(one<float>));
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
        float32x2_t floor = vrndm_f32(x.st);
        ret.st = vsub_f32(x.st, floor);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::fract<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        float32x4_t floor = vrndmq_f32(x.st);
        ret.st = vsubq_f32(x.st, floor);
        return ret;
    }
};

#elif defined(KTM_SIMD_SSE)

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
        __m128 sum_0 = _mm_add_ss(x.st, _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128 sum_1 = _mm_add_ss(sum_0, _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        return _mm_cvtss_f32(sum_1); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        __m128 sum_0 = _mm_add_ps(x.st, _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128 sum_1 = _mm_add_ss(sum_0, _mm_shuffle_ps(sum_0, sum_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return _mm_cvtss_f32(sum_1); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        __m128 min_0 = _mm_min_ss(x.st, _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128 min_1 = _mm_min_ss(min_0, _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        return _mm_cvtss_f32(min_1); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        __m128 min_0 = _mm_min_ps(x.st, _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128 min_1 = _mm_min_ss(min_0, _mm_shuffle_ps(min_0, min_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return _mm_cvtss_f32(min_1); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<3, float>
{
    using V = vec<3, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        __m128 max_0 = _mm_max_ss(x.st, _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128 max_1 = _mm_max_ss(max_0, _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        return _mm_cvtss_f32(max_1); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<4, float>
{
    using V = vec<4, float>;
    static KTM_INLINE float call(const V& x) noexcept
    {
        __m128 max_0 = _mm_max_ps(x.st, _mm_shuffle_ps(x.st, x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128 max_1 = _mm_max_ss(max_0, _mm_shuffle_ps(max_0, max_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return _mm_cvtss_f32(max_1);  
    }
};

template<size_t N>
struct ktm::detail::common_implement::abs<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = intrin::ext::abs_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::min<N, std::enable_if_t<N == 3 || N == 4, float>>
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
struct ktm::detail::common_implement::max<N, std::enable_if_t<N == 3 || N == 4, float>>
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
struct ktm::detail::common_implement::clamp<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        ret.st = intrin::ext::clamp_ps(v.st, min.st, max.st);
        return ret; 
    }
};

template<size_t N>
struct ktm::detail::common_implement::floor<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = intrin::ext::floor_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::ceil<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = intrin::ext::ceil_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::round<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = intrin::ext::round_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::lerp<N, std::enable_if_t<N == 3 || N == 4, float>>
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
struct ktm::detail::common_implement::mix<N, std::enable_if_t<N == 3 || N == 4, float>>
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
struct ktm::detail::common_implement::recip<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = intrin::ext::recip_ps(x.st);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::step<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& edge, const V& x) noexcept
    {
        V ret;
        __m128 cmp = _mm_cmplt_ps(x.st, edge.st);
        ret.st = _mm_and_ps(_mm_set1_ps(one<float>), cmp);
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::smoothstep<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        V ret;
        __m128 tmp = _mm_div_ps(_mm_sub_ps(x.st, edge0.st), _mm_sub_ps(edge1.st, edge0.st));
        tmp = intrin::ext::clamp_ps(tmp, _mm_setzero_ps(), _mm_set1_ps(one<float>));
        ret.st = _mm_mul_ps(_mm_mul_ps(tmp, tmp), _mm_sub_ps(_mm_set1_ps(3.f), _mm_mul_ps(_mm_set1_ps(2.f), tmp)));
        return ret;
    }
};

template<size_t N>
struct ktm::detail::common_implement::fract<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        __m128 floor = intrin::ext::floor_ps(x.st);
        ret.st = _mm_sub_ps(x.st, floor);
        return ret;
    }
};

#if KTM_SIMD_SSE & KTM_SIMD_SSE2_FLAG

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
        __m128i sum_0 = _mm_add_epi32(x.st, _mm_shuffle_epi32(x.st, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128i sum_1 = _mm_add_epi32(sum_0, _mm_shuffle_epi32(x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        return _mm_cvtsi128_si32(sum_1); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_add<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        __m128i sum_0 = _mm_add_epi32(x.st, _mm_shuffle_epi32(x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128i sum_1 = _mm_add_epi32(sum_0, _mm_shuffle_epi32(sum_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return _mm_cvtsi128_si32(sum_1); 
    }
};

template<size_t N>
struct ktm::detail::common_implement::abs<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        ret.st = intrin::ext::abs_epi32(x.st);
        return ret;
    }
};

#endif // KTM_SIMD_SSE & KTM_SIMD_SSE2_FLAG

#if KTM_SIMD_SSE & KTM_SIMD_SSE4_1_FLAG

template<>
struct ktm::detail::common_implement::reduce_min<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        __m128i min_0 = _mm_min_epi32(x.st, _mm_shuffle_epi32(x.st, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128i min_1 = _mm_min_epi32(min_0, _mm_shuffle_epi32(x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        return _mm_cvtsi128_si32(min_1); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_min<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        __m128i min_0 = _mm_min_epi32(x.st, _mm_shuffle_epi32(x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128i min_1 = _mm_min_epi32(min_0, _mm_shuffle_epi32(min_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return _mm_cvtsi128_si32(min_1); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<3, int>
{
    using V = vec<3, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        __m128i max_0 = _mm_max_epi32(x.st, _mm_shuffle_epi32(x.st, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128i max_1 = _mm_max_epi32(max_0, _mm_shuffle_epi32(x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        return _mm_cvtsi128_si32(max_1); 
    }
};

template<>
struct ktm::detail::common_implement::reduce_max<4, int>
{
    using V = vec<4, int>;
    static KTM_INLINE int call(const V& x) noexcept
    {
        __m128i max_0 = _mm_max_epi32(x.st, _mm_shuffle_epi32(x.st, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128i max_1 = _mm_max_epi32(max_0, _mm_shuffle_epi32(max_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return _mm_cvtsi128_si32(max_1); 
    }
};

template<size_t N>
struct ktm::detail::common_implement::min<N, std::enable_if_t<N == 3 || N == 4, int>>
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
struct ktm::detail::common_implement::max<N, std::enable_if_t<N == 3 || N == 4, int>>
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
struct ktm::detail::common_implement::clamp<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        ret.st = intrin::ext::clamp_epi32(v.st, min.st, max.st);
        return ret; 
    }
};

#endif // KTM_SIMD_SSE & KTM_SIMD_SSE4_1_FLAG

#endif

#endif
