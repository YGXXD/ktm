#ifndef _MAT_OPT_SIMD_H_
#define _MAT_OPT_SIMD_H_

#include "MatOptFwd.h"
#include "Math/Library/ArtcBase.h"

#if defined(CHTHOLLY_SIMD_NEON)

template<size_t Row>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = vec<2, float>;
    using RowV = vec<Row, float>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret;
        ret.st = neon::ex::add_f32_all(vmul_f32(m[Ns].st, vdup_n_f32(v[Ns]))...);
        return ret; 
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, Col, std::enable_if_t<Col == 3 || Col == 4, float>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    using RowV = vec<Row, float>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret;
        ret.st = neon::ex::addq_f32_all(vmulq_f32(m[Ns].st, vdupq_n_f32(v[Ns]))...);
        return ret; 
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = vec<2, float>;
    using RowV = vec<Row, float>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = neon::geo::fv2_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, float>
{
    using M = mat<Row, 3, float>;
    using ColV = vec<3, float>;
    using RowV = vec<Row, float>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = neon::geo::fv3_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, float>
{
    using M = mat<Row, 4, float>;
    using ColV = vec<4, float>;
    using RowV = vec<Row, float>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = neon::geo::fv4_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::add<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = vec<2, float>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vadd_f32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::add<Row, Col, std::enable_if_t<Col == 3 || Col == 4, float>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vaddq_f32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::minus<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = vec<2, float>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vsub_f32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::minus<Row, Col, std::enable_if_t<Col == 3 || Col == 4, float>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vsubq_f32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, 2, int>
{
    using M = mat<Row, 2, int>;
    using ColV = vec<2, int>;
    using RowV = vec<Row, int>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret;
        ret.st = neon::ex::add_s32_all(vmul_s32(m[Ns].st, vdup_n_s32(v[Ns]))...);
        return ret; 
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, Col, std::enable_if_t<Col == 3 || Col == 4, int>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    using RowV = vec<Row, int>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {   
        ColV ret;
        ret.st = neon::ex::addq_s32_all(vmulq_s32(m[Ns].st, vdupq_n_s32(v[Ns]))...);
        return ret; 
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 2, int>
{
    using M = mat<Row, 2, int>;
    using ColV = vec<2, int>;
    using RowV = vec<Row, int>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = neon::geo::sv2_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, int>
{
    using M = mat<Row, 3, int>;
    using ColV = vec<3, int>;
    using RowV = vec<Row, int>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = neon::geo::sv3_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, int>
{
    using M = mat<Row, 4, int>;
    using ColV = vec<4, int>;
    using RowV = vec<Row, int>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = neon::geo::sv4_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::add<Row, 2, int>
{
    using M = mat<Row, 2, int>;
    using ColV = vec<2, int>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vadd_s32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::add<Row, Col, std::enable_if_t<Col == 3 || Col == 4, int>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vaddq_s32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::minus<Row, 2, int>
{
    using M = mat<Row, 2, int>;
    using ColV = vec<2, int>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vsub_s32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::minus<Row, Col, std::enable_if_t<Col == 3 || Col == 4, int>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vsubq_s32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

#elif defined(CHTHOLLY_SIMD_SSE)

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, Col, std::enable_if_t<Col == 3 || Col == 4, float>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    using RowV = vec<Row, float>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:

    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret;
        ret.st = intrin::ex::add_ps_all(_mm_mul_ps(m[Ns].st, _mm_set1_ps(v[Ns]))...);
        return ret; 
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, float>
{
    using M = mat<Row, 3, float>;
    using ColV = vec<3, float>;
    using RowV = vec<Row, float>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = intrin::geo::fv3_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, float>
{
    using M = mat<Row, 4, float>;
    using ColV = vec<4, float>;
    using RowV = vec<Row, float>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = intrin::geo::fv4_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::add<Row, Col, std::enable_if_t<Col == 3 || Col == 4, float>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = _mm_add_ps(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::minus<Row, Col, std::enable_if_t<Col == 3 || Col == 4, float>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = _mm_sub_ps(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::add<Row, Col, std::enable_if_t<Col == 3 || Col == 4, int>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = _mm_add_epi32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::minus<Row, Col, std::enable_if_t<Col == 3 || Col == 4, int>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = _mm_sub_epi32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE2_FLAG

#if CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, Col, std::enable_if_t<Col == 3 || Col == 4, int>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    using RowV = vec<Row, int>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:

    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret; 
        ret.st = intrin::ex::add_epi32_all(_mm_mullo_epi32(m[Ns].st, _mm_set1_epi32(v[Ns]))...);
        return ret; 
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, int>
{
    using M = mat<Row, 3, int>;
    using ColV = vec<3, int>;
    using RowV = vec<Row, int>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = intrin::geo::sv3_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, int>
{
    using M = mat<Row, 4, int>;
    using ColV = vec<4, int>;
    using RowV = vec<Row, int>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = intrin::geo::sv4_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

#endif

#endif
