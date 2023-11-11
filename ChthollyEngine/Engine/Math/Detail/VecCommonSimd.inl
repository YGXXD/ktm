#ifndef _VEC_COMMON_SIMD_INL_
#define _VEC_COMMON_SIMD_INL_

#include "VecCommonFwd.h"
#include "Math/Library/Definition.h"

#if defined(CHTHOLLY_SIMD_NEON)

template<size_t L>
struct ktm::detail::vec_common_implement::elem_move<L, 2, float>
{
    static_assert(L == 1);
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        float32x2_t ret = vld1_f32(&x[0]);
        ret = _neon_shuffle_f32(ret, ret, 0, L);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t L>
struct ktm::detail::vec_common_implement::elem_move<L, 3, float>
{
    static_assert(L > 0 && L < 3);
    using V = vec<3, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        constexpr size_t i1 = 1 + L < 3 ? 1 + L : L - 2;
        constexpr size_t i2 = 2 + L < 3 ? 2 + L : L - 1; 
        float32x4_t ret = vld1q_f32(&x[0]);
        ret = _neon_shuffleq_f32(ret, ret, 3, i2, i1, L);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t L>
struct ktm::detail::vec_common_implement::elem_move<L, 4, float>
{
    static_assert(L > 0 && L < 4);
    using V = vec<4, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        constexpr size_t i1 = 1 + L < 4 ? 1 + L : L - 3;
        constexpr size_t i2 = 2 + L < 4 ? 2 + L : L - 2; 
        constexpr size_t i3 = 3 + L < 4 ? 3 + L : L - 1;  
        float32x4_t ret = vld1q_f32(&x[0]);
        ret = _neon_shuffleq_f32(ret, ret, i3, i2, i1, L);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t L>
struct ktm::detail::vec_common_implement::elem_move<L, 2, int>
{
    static_assert(L == 1);
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        int32x2_t ret = vld1_s32(&x[0]);
        ret = _neon_shuffle_s32(ret, ret, 0, L);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t L>
struct ktm::detail::vec_common_implement::elem_move<L, 3, int>
{
    static_assert(L > 0 && L < 3);
    using V = vec<3, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        constexpr size_t i1 = 1 + L < 3 ? 1 + L : L - 2;
        constexpr size_t i2 = 2 + L < 3 ? 2 + L : L - 1; 
        int32x4_t ret = vld1q_s32(&x[0]);
        ret = _neon_shuffleq_s32(ret, ret, 3, i2, i1, L);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t L>
struct ktm::detail::vec_common_implement::elem_move<L, 4, int>
{
    static_assert(L > 0 && L < 3);
    using V = vec<3, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        constexpr size_t i1 = 1 + L < 4 ? 1 + L : L - 3;
        constexpr size_t i2 = 2 + L < 4 ? 2 + L : L - 2; 
        constexpr size_t i3 = 3 + L < 4 ? 3 + L : L - 1;  
        int32x4_t ret = vld1q_s32(&x[0]);
        ret = _neon_shuffleq_s32(ret, ret, i3, i2, i1, L);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_add<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        return vaddv_f32(vld1_f32(&x[0]));
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_add<3, float>
{
    using V = vec<3, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        float32x4_t tmp = vld1q_f32(&x[0]);
        return vaddvq_f32(vsetq_lane_f32(zero<float>, tmp, 3)); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_add<4, float>
{
    using V = vec<4, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        return vaddvq_f32(vld1q_f32(&x[0])); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_add<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        return vaddv_s32(vld1_s32(&x[0]));
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_add<3, int>
{
    using V = vec<3, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        int32x4_t tmp = vld1q_s32(&x[0]);
        return vaddvq_s32(vsetq_lane_s32(zero<int>, tmp, 3)); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_add<4, int>
{
    using V = vec<4, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        return vaddvq_s32(vld1q_s32(&x[0])); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_min<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        return vminv_f32(vld1_f32(&x[0]));
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_min<3, float>
{
    using V = vec<3, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        float32x4_t tmp = vld1q_f32(&x[0]);
        return vminvq_f32(vsetq_lane_f32(tmp[2], tmp, 3));
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_min<4, float>
{
    using V = vec<4, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        return vminvq_f32(vld1q_f32(&x[0])); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_min<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        return vminv_s32(vld1_s32(&x[0]));
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_min<3, int>
{
    using V = vec<3, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        int32x4_t tmp = vld1q_s32(&x[0]);
        return vminvq_s32(vsetq_lane_s32(tmp[2], tmp, 3)); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_min<4, int>
{
    using V = vec<4, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        return vminvq_s32(vld1q_s32(&x[0])); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_max<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        return vmaxv_f32(vld1_f32(&x[0]));
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_max<3, float>
{
    using V = vec<3, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        float32x4_t tmp = vld1q_f32(&x[0]);
        return vmaxvq_f32(vsetq_lane_f32(tmp[2], tmp, 3)); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_max<4, float>
{
    using V = vec<4, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        return vmaxvq_f32(vld1q_f32(&x[0])); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_max<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        return vmaxv_s32(vld1_s32(&x[0]));
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_max<3, int>
{
    using V = vec<3, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        int32x4_t tmp = vld1q_s32(&x[0]);
        return vmaxvq_s32(vsetq_lane_s32(tmp[2], tmp, 3)); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_max<4, int>
{
    using V = vec<4, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        return vmaxvq_s32(vld1q_s32(&x[0])); 
    }
};

template<>
struct ktm::detail::vec_common_implement::abs<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        float32x2_t tmp = vld1_f32(&x[0]);
        float32x2_t ret = vabs_f32(tmp);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::abs<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        float32x4_t tmp = vld1q_f32(&x[0]);
        float32x4_t ret = vabsq_f32(tmp);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::abs<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        int32x2_t tmp = vld1_s32(&x[0]);
        int32x2_t ret = vabs_s32(tmp);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::abs<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        int32x4_t tmp = vld1q_s32(&x[0]);
        int32x4_t ret = vabsq_s32(tmp);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::min<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x2_t ret = vmin_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::min<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x4_t ret = vminq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::min<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        int32x2_t ret = vmin_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::min<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        int32x4_t ret = vminq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::max<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x2_t ret = vmax_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::max<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        float32x4_t ret = vmaxq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::max<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        int32x2_t ret = vmax_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::max<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        int32x4_t ret = vmaxq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::clamp<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        float32x2_t ret = vclamp_f32(vld1_f32(&v[0]), vld1_f32(&min[0]), vld1_f32(&max[0]));
        return *reinterpret_cast<V*>(&ret); 
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::clamp<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        float32x4_t ret = vclampq_f32(vld1q_f32(&v[0]), vld1q_f32(&min[0]), vld1q_f32(&max[0]));
        return *reinterpret_cast<V*>(&ret); 
    }
};

template<>
struct ktm::detail::vec_common_implement::clamp<2, int>
{
    using V = vec<2, int>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        int32x2_t ret = vclamp_s32(vld1_s32(&v[0]), vld1_s32(&min[0]), vld1_s32(&max[0]));
        return *reinterpret_cast<V*>(&ret); 
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::clamp<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        int32x4_t ret = vclampq_s32(vld1q_s32(&v[0]), vld1q_s32(&min[0]), vld1q_s32(&max[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::lerp<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y, float t) noexcept
    {
        float32x2_t t_x = vld1_f32(&x[0]);
        float32x2_t t_y = vld1_f32(&y[0]);
        float32x2_t t_t = vdup_n_f32(t);
        float32x2_t ret = vadd_f32(t_x, vmul_f32(t_t, vsub_f32(t_y, t_x)));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::lerp<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y, float t) noexcept
    {
        float32x4_t t_x = vld1q_f32(&x[0]);
        float32x4_t t_y = vld1q_f32(&y[0]);
        float32x4_t t_t = vdupq_n_f32(t);
        float32x4_t ret = vaddq_f32(t_x, vmulq_f32(t_t, vsubq_f32(t_y, t_x)));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::mix<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        float32x2_t t_x = vld1_f32(&x[0]);
        float32x2_t t_y = vld1_f32(&y[0]);
        float32x2_t t_t = vld1_f32(&t[0]);
        float32x2_t ret = vadd_f32(t_x, vmul_f32(t_t, vsub_f32(t_y, t_x)));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::mix<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        float32x4_t t_x = vld1q_f32(&x[0]);
        float32x4_t t_y = vld1q_f32(&y[0]);
        float32x4_t t_t = vld1q_f32(&t[0]);
        float32x4_t ret = vaddq_f32(t_x, vmulq_f32(t_t, vsubq_f32(t_y, t_x)));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::recip<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        float32x2_t ret = vdiv_f32(vdup_n_f32(one<float>), vld1_f32(&x[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::recip<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        float32x4_t ret = vdivq_f32(vdupq_n_f32(one<float>), vld1q_f32(&x[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::step<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& edge, const V& x) noexcept
    {
        float32x2_t cmp = vclt_f32(vld1_f32(&x[0]), vld1_f32(&edge[0]));
        uint32x2_t tmp = vand_u32(vreinterpret_u32_f32(vdup_n_f32(one<float>)), vreinterpret_u32_f32(cmp));
        float32x2_t ret = vreinterpret_f32_u32(tmp);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::step<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& edge, const V& x) noexcept
    {
        float32x4_t cmp = vcltq_f32(vld1q_f32(&x[0]), vld1q_f32(&edge[0]));
        uint32x4_t tmp = vandq_u32(vreinterpretq_u32_f32(vdupq_n_f32(one<float>)), vreinterpretq_u32_f32(cmp));
        float32x4_t ret = vreinterpretq_f32_u32(tmp);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::smoothstep<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        float32x2_t t_edge0 = vld1_f32(&edge0[0]);
        float32x2_t t_edge1 = vld1_f32(&edge1[0]); 
        float32x2_t t_x = vld1_f32(&x[0]);
        float32x2_t tmp = vdiv_f32(vsub_f32(t_x, t_edge0), vsub_f32(t_edge1, t_edge0));
        tmp = vmax_f32(tmp, vdup_n_f32(zero<float>));
        tmp = vmin_f32(tmp, vdup_n_f32(one<float>));
        float32x2_t ret = vmul_f32(vmul_f32(tmp, tmp), vsub_f32(vdup_n_f32(3.f), vmul_f32(vdup_n_f32(2.f), tmp)));
        return *reinterpret_cast<V*>(&ret);
    }
};


template<size_t N>
struct ktm::detail::vec_common_implement::smoothstep<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        float32x4_t t_edge0 = vld1q_f32(&edge0[0]);
        float32x4_t t_edge1 = vld1q_f32(&edge1[0]); 
        float32x4_t t_x = vld1q_f32(&x[0]);
        float32x4_t tmp = vdivq_f32(vsubq_f32(t_x, t_edge0), vsubq_f32(t_edge1, t_edge0));
        tmp = vclampq_f32(tmp, vdupq_n_f32(zero<float>), vdupq_n_f32(one<float>));
        float32x4_t ret = vmulq_f32(vmulq_f32(tmp, tmp), vsubq_f32(vdupq_n_f32(3.f), vmulq_f32(vdupq_n_f32(2.f), tmp)));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::fract<2, float>
{
    using V = vec<2, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        float32x2_t t_x = vld1_f32(&x[0]);
        float32x2_t t_floor = vrndm_f32(t_x);
        float32x2_t ret = vmin_f32(vsub_f32(t_x, t_floor), vdup_n_f32(one<float>));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::fract<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        float32x4_t t_x = vld1q_f32(&x[0]);
        float32x4_t t_floor = vrndmq_f32(t_x);
        float32x4_t ret = vminq_f32(vsubq_f32(t_x, t_floor), vdupq_n_f32(one<float>));
        return *reinterpret_cast<V*>(&ret);
    }
};

#elif defined(CHTHOLLY_SIMD_SSE)

template<size_t L>
struct ktm::detail::vec_common_implement::elem_move<L, 3, float>
{
    static_assert(L > 0 && L < 3);
    using V = vec<3, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        constexpr size_t i1 = 1 + L < 3 ? 1 + L : L - 2;
        constexpr size_t i2 = 2 + L < 3 ? 2 + L : L - 1; 
        __m128 ret = _mm_load_ps(&x[0]);
        ret = _mm_shuffle_ps(ret, ret, _MM_SHUFFLE(3, i2, i1, L));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t L>
struct ktm::detail::vec_common_implement::elem_move<L, 4, float>
{
    static_assert(L > 0 && L < 4);
    using V = vec<4, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        constexpr size_t i1 = 1 + L < 4 ? 1 + L : L - 3;
        constexpr size_t i2 = 2 + L < 4 ? 2 + L : L - 2; 
        constexpr size_t i3 = 3 + L < 4 ? 3 + L : L - 1; 
        __m128 ret = _mm_load_ps(&x[0]);
        ret = _mm_shuffle_ps(ret, ret, _MM_SHUFFLE(i3, i2, i1, L));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_add<3, float>
{
    using V = vec<3, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        __m128 tmp = _mm_load_ps(&x[0]);
        __m128 sum_0 = _mm_add_ss(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128 sum_1 = _mm_add_ss(sum_0, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        return *reinterpret_cast<float*>(&sum_1); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_add<4, float>
{
    using V = vec<4, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        __m128 tmp = _mm_load_ps(&x[0]);
        __m128 sum_0 = _mm_add_ps(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128 sum_1 = _mm_add_ss(sum_0, _mm_shuffle_ps(sum_0, sum_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return *reinterpret_cast<float*>(&sum_1); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_min<3, float>
{
    using V = vec<3, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        __m128 tmp = _mm_load_ps(&x[0]);
        __m128 min_0 = _mm_min_ss(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128 min_1 = _mm_min_ss(min_0, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        return *reinterpret_cast<float*>(&min_1); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_min<4, float>
{
    using V = vec<4, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        __m128 tmp = _mm_load_ps(&x[0]);
        __m128 min_0 = _mm_min_ps(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128 min_1 = _mm_min_ss(min_0, _mm_shuffle_ps(min_0, min_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return *reinterpret_cast<float*>(&min_1); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_max<3, float>
{
    using V = vec<3, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        __m128 tmp = _mm_load_ps(&x[0]);
        __m128 max_0 = _mm_max_ss(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128 max_1 = _mm_max_ss(max_0, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        return *reinterpret_cast<float*>(&max_1); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_max<4, float>
{
    using V = vec<4, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        __m128 tmp = _mm_load_ps(&x[0]);
        __m128 max_0 = _mm_max_ps(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128 max_1 = _mm_max_ss(max_0, _mm_shuffle_ps(max_0, max_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return *reinterpret_cast<float*>(&max_1); 
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::abs<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        __m128 ret = _mm_abs_ps(_mm_load_ps(&x[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::min<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128 ret = _mm_min_ps(_mm_load_ps(&x[0]), mm_load_ps(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::max<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128 ret = _mm_max_ps(_mm_load_ps(&x[0]), mm_load_ps(&y[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::clamp<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        __m128 ret = _mm_clamp_ps(_mm_load_ps(&v[0]), _mm_load_ps(&min[0]), _mm_load_ps(&max[0]));
        return *reinterpret_cast<V*>(&ret); 
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::lerp<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y, float t) noexcept
    {
        __m128 t_x = _mm_load_ps(&x[0]);
        __m128 t_y = _mm_load_ps(&y[0]);
        __m128 t_t = _mm_set1_ps(t);
        __m128 ret = _mm_add_ps(t_x, _mm_mul_ps(t_t, _mm_sub_ps(t_y, t_x)));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::mix<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        __m128 t_x = _mm_load_ps(&x[0]);
        __m128 t_y = _mm_load_ps(&y[0]);
        __m128 t_t = _mm_load_ps(&t[0]);
        __m128 ret = _mm_add_ps(t_x, _mm_mul_ps(t_t, _mm_sub_ps(t_y, t_x)));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::recip<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        __m128 ret = _mm_div_ps(_mm_set1_ps(one<float>), _mm_load_ps(&x[0]));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::step<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& edge, const V& x) noexcept
    {
        __m128 cmp = _mm_cmplt_ps(_mm_load_ps(&x[0]), _mm_load_ps(&edge[0]));
        __m128 ret = _mm_and_ps(_mm_set1_ps(one<float>), cmp);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::smoothstep<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        __m128 t_edge0 = _mm_load_ps(&edge0[0]);
        __m128 t_edge1 = _mm_load_ps(&edge1[0]);
        __m128 t_x = _mm_load_ps(&x[0]);
        __m128 tmp = _mm_div_ps(_mm_sub_ps(t_x, t_edge0), _mm_sub_ps(t_edge1, t_edge0));
        tmp = _mm_clamp_ps(tmp, _mm_set1_ps(zero<float>), _mm_set1_ps(one<float>));
        __m128 ret = _mm_mul_ps(_mm_mul_ps(tmp, tmp), _mm_sub_ps(_mm_set1_ps(3.f), _mm_mul_ps(_mm_set1_ps(2.f), tmp)));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::fract<N, std::enable_if_t<N == 3 || N == 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        __m128 t_x = _mm_load_ps(&x[0]);
#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG
        __m128 t_floor = _mm_floor_ps(t_x);
#else 
        const union { unsigned int i; float f; } mask = { 0x80000000 };
		__m128 tmp = _mm_and_ps(t_x, _mm_set1_ps(mask.f));
		tmp = _mm_or_ps(tmp, _mm_set_ps1(8388608.f));
        __m128 rnd = _mm_sub_ps(_mm_add_ps(t_x, tmp), tmp);
		tmp = _mm_cmplt_ps(t_x, rnd);
		tmp = _mm_and_ps(tmp, _mm_set1_ps(1.f));
		__m128 t_floor = _mm_sub_ps(rnd, tmp);
#endif
        __m128 ret = _mm_min_ps(_mm_sub_ps(t_x, t_floor), _mm_set1_ps(one<float>));
        return *reinterpret_cast<V*>(&ret);
    }
};

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

template<size_t L>
struct ktm::detail::vec_common_implement::elem_move<L, 3, int>
{
    static_assert(L > 0 && L < 3);
    using V = vec<3, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        constexpr size_t i1 = 1 + L < 3 ? 1 + L : L - 2;
        constexpr size_t i2 = 2 + L < 3 ? 2 + L : L - 1; 
        __m128i ret = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        ret = _mm_shuffle_epi32(ret, _MM_SHUFFLE(3, i2, i1, L));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t L>
struct ktm::detail::vec_common_implement::elem_move<L, 4, int>
{
    static_assert(L > 0 && L < 4);
    using V = vec<4, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        constexpr size_t i1 = 1 + L < 4 ? 1 + L : L - 3;
        constexpr size_t i2 = 2 + L < 4 ? 2 + L : L - 2; 
        constexpr size_t i3 = 3 + L < 4 ? 3 + L : L - 1;  
        __m128i ret = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        ret = _mm_shuffle_epi32(ret, _MM_SHUFFLE(i3, i2, i1, L));
        return *reinterpret_cast<V*>(&ret);
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_add<3, int>
{
    using V = vec<3, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        __m128i tmp = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i sum_0 = _mm_add_epi32(tmp, _mm_shuffle_epi32(tmp, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128i sum_1 = _mm_add_epi32(sum_0, _mm_shuffle_epi32(tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        return *reinterpret_cast<int*>(&sum_1); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_add<4, int>
{
    using V = vec<4, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        __m128i tmp = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i sum_0 = _mm_add_epi32(tmp, _mm_shuffle_epi32(tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128i sum_1 = _mm_add_epi32(sum_0, _mm_shuffle_epi32(sum_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return *reinterpret_cast<int*>(&sum_1); 
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::abs<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE3_FLAG
        __m128i ret = _mm_abs_epi32(t_x);
#else
        __m128i tmp = _mm_srai_epi32(t_x, 31);
		__m128i ret = _mm_sub_epi32(_mm_xor_si128(t_x, tmp), tmp);
#endif
        return *reinterpret_cast<V*>(&ret);
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

template<>
struct ktm::detail::vec_common_implement::reduce_min<3, int>
{
    using V = vec<3, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        __m128i tmp = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i min_0 = _mm_min_epi32(tmp, _mm_shuffle_epi32(tmp, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128i min_1 = _mm_min_epi32(min_0, _mm_shuffle_epi32(tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        return *reinterpret_cast<int*>(&min_1); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_min<4, int>
{
    using V = vec<4, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        __m128i tmp = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i min_0 = _mm_min_epi32(tmp, _mm_shuffle_epi32(tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128i min_1 = _mm_min_epi32(min_0, _mm_shuffle_epi32(min_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return *reinterpret_cast<int*>(&min_1); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_max<3, int>
{
    using V = vec<3, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        __m128i tmp = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i max_0 = _mm_max_epi32(tmp, _mm_shuffle_epi32(tmp, _MM_SHUFFLE(0, 3, 2, 1)));
        __m128i max_1 = _mm_max_epi32(max_0, _mm_shuffle_epi32(tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        return *reinterpret_cast<int*>(&max_1); 
    }
};

template<>
struct ktm::detail::vec_common_implement::reduce_max<4, int>
{
    using V = vec<4, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        __m128i tmp = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i max_0 = _mm_max_epi32(tmp, _mm_shuffle_epi32(tmp, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128i max_1 = _mm_max_epi32(max_0, _mm_shuffle_epi32(max_0, _MM_SHUFFLE(0, 3, 2, 1)));
        return *reinterpret_cast<int*>(&max_1); 
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::min<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i t_y = _mm_load_si128(reinterpret_cast<const __m128i*>(&y[0]));
        __m128i ret = _mm_min_epi32(t_x, t_y);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::max<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        __m128i t_x = _mm_load_si128(reinterpret_cast<const __m128i*>(&x[0]));
        __m128i t_y = _mm_load_si128(reinterpret_cast<const __m128i*>(&y[0]));
        __m128i ret = _mm_max_epi32(t_x, t_y);
        return *reinterpret_cast<V*>(&ret);
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::clamp<N, std::enable_if_t<N == 3 || N == 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        __m128i t_v = _mm_load_si128(reinterpret_cast<const __m128i*>(&v[0]));
        __m128i t_min = _mm_load_si128(reinterpret_cast<const __m128i*>(&min[0]));
        __m128i t_max = _mm_load_si128(reinterpret_cast<const __m128i*>(&max[0]));
        __m128i ret = _mm_clamp_epi32(t_v, t_min, t_max);
        return *reinterpret_cast<V*>(&ret); 
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

#endif

#endif