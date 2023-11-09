#ifndef _MAT_OPT_IMPL_SIMD_H_
#define _MAT_OPT_IMPL_SIMD_H_

#include "MatOptImpl.h"
#include "Math/MathType/BaseType.h"

#if defined(CHTHOLLY_SIMD_NEON)

template<size_t Row>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        float32x2_t ret = vadd_f32_all(core(m[Ns], v[Ns])...);
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
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        float32x4_t ret = vaddq_f32_all(core(m[Ns], v[Ns])...);
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
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
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
        return vaddv_f32(vmul_f32(vld1_f32(&v[0]), vld1_f32(&matrix_v[0])));
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, float>
{
    using M = mat<Row, 3, float>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
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
        float32x4_t v_mul_mv = vmulq_f32(vld1q_f32(&v[0]), vld1q_f32(&matrix_v[0]));
        return vaddvq_f32(vsetq_lane_f32(zero<float>, v_mul_mv, 3));
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, float>
{
    using M = mat<Row, 4, float>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
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
        return vaddvq_f32(vmulq_f32(vld1q_f32(&v[0]), vld1q_f32(&matrix_v[0])));
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::add<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        int32x2_t ret = vadd_s32_all(core(m[Ns], v[Ns])...);
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
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        int32x4_t ret = vaddq_s32_all(core(m[Ns], v[Ns])...);
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
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
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
        return vaddv_s32(vmul_s32(vld1_s32(&v[0]), vld1_s32(&matrix_v[0])));
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, int>
{
    using M = mat<Row, 3, int>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
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
        int32x4_t v_mul_mv = vmulq_s32(vld1q_s32(&v[0]), vld1q_s32(&matrix_v[0]));
        return vaddvq_s32(vsetq_lane_s32(zero<int>, v_mul_mv, 3));
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, int>
{
    using M = mat<Row, 4, int>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
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
        return vaddvq_s32(vmulq_s32(vld1q_s32(&v[0]), vld1q_s32(&matrix_v[0])));
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::add<Row, 2, int>
{
    using M = mat<Row, 2, int>;
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:

    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        __m128 ret = _mm_add_ps_all(core(m[Ns], v[Ns])...);
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
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
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
        __m128 t_mul = _mm_mul_ps(_mm_load_ps(&v[0]), _mm_load_ps(&matrix_v[0]));
        __m128 sum1 = _mm_add_ss(t_mul, _mm_shuffle_ps(t_mul, t_mul, _MM_SHUFFLE(2, 1, 0, 3)));
        __m128 sum2 = _mm_add_ss(sum1, _mm_shuffle_ps(t_mul, t_mul, _MM_SHUFFLE(1, 0, 3, 2)));
        return *reinterpret_cast<float*>(&sum2); 
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, float>
{
    using M = mat<Row, 4, float>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
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
        __m128 t_mul = _mm_mul_ps(_mm_load_ps(&v[0]), _mm_load_ps(&matrix_v[0]));
        __m128 sum1 = _mm_add_ps(t_mul, _mm_shuffle_ps(t_mul, t_mul, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128 sum2 = _mm_add_ss(sum1, _mm_shuffle_ps(sum1, sum1, _MM_SHUFFLE(2, 1, 0, 3)));
        return *reinterpret_cast<float*>(&sum2); 
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_opt_implement::add<Row, Col, std::enable_if_t<Col == 3 || Col == 4, float>>
{
    using M = mat<Row, Col, float>;
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
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
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<Row>());
    }
private:

    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        __m128i ret = _mm_add_epi32_all(core(m[Ns], v[Ns])...);
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE __m128i core(const ColV& matrix_v, int v_elem) noexcept
    {
        return _mm_mul_epi32(_mm_load_si128(reinterpret_cast<const __m128i*>(&matrix_v[0])), _mm_set1_epi32(v_elem));
    } 
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 3, int>
{
    using M = mat<Row, 3, int>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
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
        __m128i t_mul = _mm_mul_epi32(_mm_load_si128(reinterpret_cast<const __m128i*>(&v[0])), _mm_load_si128(reinterpret_cast<const __m128i*>(&matrix_v[0])));
        __m128i sum1 = _mm_add_epi32(t_mul, _mm_shuffle_epi32(t_mul, _MM_SHUFFLE(2, 1, 0, 3)));
        __m128i sum2 = _mm_add_epi32(sum1, _mm_shuffle_epi32(t_mul, _MM_SHUFFLE(1, 0, 3, 2)));
        return *reinterpret_cast<float*>(&sum2); 
    }
};

template<size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Row, 4, int>
{
    using M = mat<Row, 4, int>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
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
        __m128i t_mul = _mm_mul_epi32(_mm_load_si128(reinterpret_cast<const __m128i*>(&v[0])), _mm_load_si128(reinterpret_cast<const __m128i*>(&matrix_v[0])));
        __m128i sum1 = _mm_add_epi32(t_mul, _mm_shuffle_epi32(t_mul, _MM_SHUFFLE(1, 0, 3, 2)));
        __m128i sum2 = _mm_add_epi32(sum1, _mm_shuffle_epi32(sum1, _MM_SHUFFLE(2, 1, 0, 3)));
        return *reinterpret_cast<float*>(&sum2); 
    }
};

#endif // CHTHOLLY_SIMD_SSE & CHTHOLLY_SIMD_SSE4_1_FLAG

#endif

#endif
