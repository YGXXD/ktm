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
        float32x2_t ret = neon::ex::add_f32_all(core(m[Ns], v[Ns])...);
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE float32x2_t core(const ColV& matrix_v, float v_elem) noexcept
    {
        return vmul_f32(vld1_f32(&matrix_v[0]), vdup_n_f32(v_elem));
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
        float32x4_t ret = neon::ex::addq_f32_all(core(m[Ns], v[Ns])...);
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE float32x4_t core(const ColV& matrix_v, float v_elem) noexcept
    {
        return vmulq_f32(vld1q_f32(&matrix_v[0]), vdupq_n_f32(v_elem));
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
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE float core(const ColV& v, const ColV& matrix_v) noexcept
    {
        return neon::geo::fv2_dot1(vld1_f32(&v[0]), vld1_f32(&matrix_v[0]));
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
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE float core(const ColV& v, const ColV& matrix_v) noexcept
    {
        return neon::geo::fv4_dot1<3>(vld1q_f32(&v[0]), vld1q_f32(&matrix_v[0]));
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
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE float core(const ColV& v, const ColV& matrix_v)
    {
        return neon::geo::fv4_dot1<4>(vld1q_f32(&v[0]), vld1q_f32(&matrix_v[0]));
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
        ((core(ret[Ns], m1[Ns], m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        vst1_f32(&ret_v[0], vadd_f32(vld1_f32(&m1_v[0]), vld1_f32(&m2_v[0])));
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
        ((core(ret[Ns], m1[Ns], m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        vst1q_f32(&ret_v[0], vaddq_f32(vld1q_f32(&m1_v[0]), vld1q_f32(&m2_v[0])));
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
        ((core(&ret[Ns], &m1[Ns], &m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        vst1_f32(&ret_v[0], vsub_f32(vld1_f32(&m1_v[0]), vld1_f32(&m2_v[0])));
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
        ((core(&ret[Ns], &m1[Ns], &m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        vst1q_f32(&ret_v[0], vsubq_f32(vld1q_f32(&m1_v[0]), vld1q_f32(&m2_v[0])));
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
        int32x2_t ret = neon::ex::add_s32_all(core(m[Ns], v[Ns])...);
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE int32x2_t core(const ColV& matrix_v, int v_elem) noexcept
    {
        return vmul_s32(vld1_s32(&matrix_v[0]), vdup_n_s32(v_elem));
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
        int32x4_t ret = neon::ex::addq_s32_all(core(m[Ns], v[Ns])...);
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE std::select_if_t<Col == 2, int32x2_t, int32x4_t> core(const ColV& matrix_v, int v_elem) noexcept
    {
        return vmulq_s32(vld1q_s32(&matrix_v[0]), vdupq_n_s32(v_elem));
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
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE int core(const ColV& v, const ColV& matrix_v) noexcept
    {
        return neon::geo::sv2_dot1(vld1_s32(&v[0]), vld1_s32(&matrix_v[0]));
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
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE int core(const ColV& v, const ColV& matrix_v) noexcept
    {
        return neon::geo::sv4_dot1<3>(vld1q_s32(&v[0]), vld1q_s32(&matrix_v[0]));
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
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE int core(const ColV& v, const ColV& matrix_v)
    {
        return neon::geo::sv4_dot1<4>(vld1q_s32(&v[0]), vld1q_s32(&matrix_v[0]));
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
        ((core(ret[Ns], m1[Ns], m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        vst1_s32(&ret_v[0], vadd_s32(vld1_s32(&m1_v[0]), vld1_s32(&m2_v[0])));
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
        ((core(ret[Ns], m1[Ns], m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        vst1q_s32(&ret_v[0], vaddq_s32(vld1q_s32(&m1_v[0]), vld1q_s32(&m2_v[0])));
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
        ((core(&ret[Ns], &m1[Ns], &m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        vst1_s32(&ret_v[0], vsub_s32(vld1_s32(&m1_v[0]), vld1_s32(&m2_v[0])));
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
        ((core(&ret[Ns], &m1[Ns], &m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        vst1q_s32(&ret_v[0], vsubq_s32(vld1q_s32(&m1_v[0]), vld1q_s32(&m2_v[0])));
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
        __m128 ret = intrin::ex::add_ps_all(core(m[Ns], v[Ns])...);
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE __m128 core(const ColV& matrix_v, float v_elem) noexcept
    {
        return _mm_mul_ps(_mm_load_ps(&matrix_v[0]), _mm_set1_ps(v_elem));
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
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE float core(const ColV& v, const ColV& matrix_v)
    {
        return intrin::geo::fv4_dot1<3>(_mm_load_ps(&v[0]), _mm_load_ps(&matrix_v[0])); 
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
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE float core(const ColV& v, const ColV& matrix_v)
    {
        return intrin::geo::fv4_dot1<4>(_mm_load_ps(&v[0]), _mm_load_ps(&matrix_v[0])); 
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
        ((core(ret[Ns], m1[Ns], m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        _mm_store_ps(&ret_v[0], _mm_add_ps(_mm_load_ps(&m1_v[0]), _mm_load_ps(&m2_v[0])));
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
        ((core(&ret[Ns], &m1[Ns], &m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        _mm_store_ps(&ret_v[0], _mm_sub_ps(_mm_load_ps(&m1_v[0]), _mm_load_ps(&m2_v[0])));
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
        ((core(ret[Ns], m1[Ns], m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        _mm_store_si128(reinterpret_cast<__m128i*>(&ret_v[0]), _mm_add_epi32(_mm_load_si128(reinterpret_cast<const __m128i*>(&m1_v[0])), _mm_load_si128(reinterpret_cast<const __m128i*>(&m2_v[0]))));
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
        ((core(&ret[Ns], &m1[Ns], &m2[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        _mm_store_si128(reinterpret_cast<__m128i*>(&ret_v[0]), _mm_sub_epi32(_mm_load_si128(reinterpret_cast<const __m128i*>(&m1_v[0])), _mm_load_si128(reinterpret_cast<const __m128i*>(&m2_v[0]))));
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
        __m128i ret = intrin::ex::add_epi32_all(core(m[Ns], v[Ns])...);
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE __m128i core(const ColV& matrix_v, int v_elem) noexcept
    {
        return _mm_mullo_epi32(_mm_load_si128(reinterpret_cast<const __m128i*>(&matrix_v[0])), _mm_set1_epi32(v_elem));
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
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE float core(const ColV& v, const ColV& matrix_v)
    {
        return intrin::geo::sv4_dot1<3>(_mm_load_si128(reinterpret_cast<const __m128i*>(&v[0])), _mm_load_si128(reinterpret_cast<const __m128i*>(&matrix_v[0])));
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
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE float core(const ColV& v, const ColV& matrix_v)
    {
        return intrin::geo::sv4_dot1<4>(_mm_load_si128(reinterpret_cast<const __m128i*>(&v[0])), _mm_load_si128(reinterpret_cast<const __m128i*>(&matrix_v[0])));
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

#endif

#endif
