#ifndef _KTM_MAT_CALC_SIMD_H_
#define _KTM_MAT_CALC_SIMD_H_

#include "mat_calc_fwd.h"
#include "../../simd/intrin.h"

#if defined(KTM_SIMD_ARM)

template<size_t Row>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = vec<2, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row - 1>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret;
        ret.st = vmul_f32(m[0].st, vdup_n_f32(v[0]));
        ((ret.st = vfma_f32(ret.st, m[Ns + 1].st, vdup_n_f32(v[Ns + 1]))), ...);
        return ret; 
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, Col, float, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row - 1>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret;
        ret.st = vmulq_f32(m[0].st, vdupq_n_f32(v[0]));
        ((ret.st = vfmaq_f32(ret.st, m[Ns + 1].st, vdupq_n_f32(v[Ns + 1]))), ...);
        return ret; 
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = vec<2, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = arm::geo::fv2_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, float>
{
    using M = mat<Row, 3, float>;
    using ColV = vec<3, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = arm::geo::fv3_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, float>
{
    using M = mat<Row, 4, float>;
    using ColV = vec<4, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = arm::geo::fv4_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::add<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = vec<2, float>;
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vadd_f32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::add<Row, Col, float, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
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
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vsub_f32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::minus<Row, Col, float, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
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
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret;
        ret.st = vmul_s32(m[0].st, vdup_n_s32(v[0]));
        ((ret.st = vmla_s32(ret.st, m[Ns + 1].st, vdup_n_s32(v[Ns + 1]))), ...);
        return ret; 
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, Col, int, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {   
        ColV ret;
        ret.st = vmulq_s32(m[0].st, vdupq_n_s32(v[0]));
        ((ret.st = vmlaq_s32(ret.st, m[Ns + 1].st, vdupq_n_s32(v[Ns + 1]))), ...);
        return ret; 
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 2, int>
{
    using M = mat<Row, 2, int>;
    using ColV = vec<2, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = arm::geo::sv2_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, int>
{
    using M = mat<Row, 3, int>;
    using ColV = vec<3, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = arm::geo::sv3_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, int>
{
    using M = mat<Row, 4, int>;
    using ColV = vec<4, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = arm::geo::sv4_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::add<Row, 2, int>
{
    using M = mat<Row, 2, int>;
    using ColV = vec<2, int>;
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vadd_s32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::add<Row, Col, int, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
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
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vsub_s32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::minus<Row, Col, int, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = vsubq_s32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

#elif defined(KTM_SIMD_X86)

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, Col, float, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row - 1>());
    }
private:

    template<size_t ...Ns>
    static KTM_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret;
        ret.st = _mm_mul_ps(m[0].st, _mm_set1_ps(v[0]));
        ((ret.st = _mm_add_ps(ret.st, _mm_mul_ps(m[Ns + 1].st, _mm_set1_ps(v[Ns + 1])))), ...);
        return ret; 
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, float>
{
    using M = mat<Row, 3, float>;
    using ColV = vec<3, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = x86::geo::fv3_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, float>
{
    using M = mat<Row, 4, float>;
    using ColV = vec<4, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = x86::geo::fv4_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::add<Row, Col, float, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = _mm_add_ps(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::minus<Row, Col, float, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = _mm_sub_ps(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

#if KTM_SIMD_X86 & KTM_SIMD_SSE2_FLAG

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::add<Row, Col, int, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = _mm_add_epi32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::minus<Row, Col, int, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    static KTM_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<Row>());
    }
private:
   template<size_t ...Ns>
    static KTM_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((ret[Ns].st = _mm_sub_epi32(m1[Ns].st, m2[Ns].st)), ...);
        return ret;
    }
};

#endif // KTM_SIMD_X86 & KTM_SIMD_SSE2_FLAG

#if KTM_SIMD_X86 & KTM_SIMD_SSE4_1_FLAG

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, Col, int, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row - 1>());
    }
private:

    template<size_t ...Ns>
    static KTM_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret;
        ret.st = _mm_mullo_epi32(m[0].st, _mm_set1_ps(v[0]));
        ((ret.st = _mm_add_epi32(ret.st, _mm_mullo_epi32(m[Ns + 1].st, _mm_set1_ps(v[Ns + 1])))), ...);
        return ret; 
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, int>
{
    using M = mat<Row, 3, int>;
    using ColV = vec<3, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = x86::geo::sv3_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, int>
{
    using M = mat<Row, 4, int>;
    using ColV = vec<4, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = x86::geo::sv4_dot1(v.st, m[Ns].st)), ...);
        return ret;
    }
};

#endif // KTM_SIMD_X86 & KTM_SIMD_SSE4_1_FLAG

#endif

#endif
