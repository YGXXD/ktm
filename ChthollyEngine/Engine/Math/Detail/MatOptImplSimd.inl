#ifndef _MAT_OPT_IMPL_SIMD_H_
#define _MAT_OPT_IMPL_SIMD_H_

#include "Math/MathType/BaseType.h"
#include "MatOptImpl.h"

#if defined(CHTHOLLY_SIMD_NEON)
#include <arm_neon.h>

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, float>>
{
    using M = mat<Col, Row, float>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<mat_traits_row_n<M>>());
    }
private:
    using SimdT = std::select_if_t<Col == 2, float32x2_t, float32x4_t>;

    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        SimdT ret;
        ret = ((core(m[Ns], v[Ns]))+ ...);;
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE SimdT core(const ColV& matrix_v, float v_elem) noexcept
    {
        if constexpr(Col == 2)
        {
            return vmul_f32(vld1_f32(&matrix_v[0]), vdup_n_f32(v_elem));
        }
        else
        {
            return vmulq_f32(vld1q_f32(&matrix_v[0]), vdupq_n_f32(v_elem));
        }
    } 
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, float>>
{
    using M = mat<Col, Row, float>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<mat_traits_row_n<M>>());
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
        if constexpr(Col == 2)
        {
            return vaddv_f32(vmul_f32(vld1_f32(&v[0]), vld1_f32(&matrix_v[0])));
        }
        else if constexpr(Col == 3)
        {
            float32x4_t v_mul_mv = vmulq_f32(vld1q_f32(&v[0]), vld1q_f32(&matrix_v[0]));
            return vaddvq_f32(vsetq_lane_f32(zero<float>, v_mul_mv, 3));
        }
        else
        {
            return vaddvq_f32(vmulq_f32(vld1q_f32(&v[0]), vld1q_f32(&matrix_v[0])));
        }
    }
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::add<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, float>>
{
    using M = mat<Col, Row, float>;
    using ColV = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_row_n<M>>());
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
        if constexpr(Col == 2)
        {
            vst1_f32(&ret_v[0], vadd_f32(vld1_f32(&m1_v[0]), vld1_f32(&m2_v[0])));
        }
        else 
        {
            vst1q_f32(&ret_v[0], vaddq_f32(vld1q_f32(&m1_v[0]), vld1q_f32(&m2_v[0])));
        }
    }
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::minus<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, float>>
{
    using M = mat<Col, Row, float>;
    using ColV = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_row_n<M>>());
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
        if constexpr(Col == 2)
        {
            vst1_f32(&ret_v[0], vsub_f32(vld1_f32(&m1_v[0]), vld1_f32(&m2_v[0])));
        }
        else 
        {
            vst1q_f32(&ret_v[0], vsubq_f32(vld1q_f32(&m1_v[0]), vld1q_f32(&m2_v[0])));
        }
    }
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, int>>
{
    using M = mat<Col, Row, int>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<mat_traits_row_n<M>>());
    }
private:
    using SimdT = std::select_if_t<Col == 2, int32x2_t, int32x4_t>;

    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        SimdT ret;
        ret = ((core(m[Ns], v[Ns]))+ ...);;
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE SimdT core(const ColV& matrix_v, int v_elem) noexcept
    {
        if constexpr(Col == 2)
        {
            return vmul_s32(vld1_s32(&matrix_v[0]), vdup_n_s32(v_elem));
        }
        else
        {
            return vmulq_s32(vld1q_s32(&matrix_v[0]), vdupq_n_s32(v_elem));
        }
    } 
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, int>>
{
    using M = mat<Col, Row, int>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<mat_traits_row_n<M>>());
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
        if constexpr(Col == 2)
        {
            return vaddv_s32(vmul_s32(vld1_s32(&v[0]), vld1_s32(&matrix_v[0])));
        }
        else if constexpr(Col == 3)
        {
            int32x4_t v_mul_mv = vmulq_s32(vld1q_s32(&v[0]), vld1q_s32(&matrix_v[0]));
            return vaddvq_s32(vsetq_lane_s32(zero<int>, v_mul_mv, 3));
        }
        else
        {
            return vaddvq_s32(vmulq_s32(vld1q_s32(&v[0]), vld1q_s32(&matrix_v[0])));
        }
    }
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::add<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, int>>
{
    using M = mat<Col, Row, int>;
    using ColV = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_row_n<M>>());
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
        if constexpr(Col == 2)
        {
            vst1_s32(&ret_v[0], vadd_s32(vld1_s32(&m1_v[0]), vld1_s32(&m2_v[0])));
        }
        else 
        {
            vst1q_s32(&ret_v[0], vaddq_s32(vld1q_s32(&m1_v[0]), vld1q_s32(&m2_v[0])));
        }
    }
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::minus<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, int>>
{
    using M = mat<Col, Row, int>;
    using ColV = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_row_n<M>>());
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
        if constexpr(Col == 2)
        {
            vst1_s32(&ret_v[0], vsub_s32(vld1_s32(&m1_v[0]), vld1_s32(&m2_v[0])));
        }
        else 
        {
            vst1q_s32(&ret_v[0], vsubq_s32(vld1q_s32(&m1_v[0]), vld1q_s32(&m2_v[0])));
        }
    }
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, unsigned int>>
{
    using M = mat<Col, Row, unsigned int>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<mat_traits_row_n<M>>());
    }
private:
    using SimdT = std::select_if_t<Col == 2, uint32x2_t, uint32x4_t>;

    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RowV& v, std::index_sequence<Ns...>) noexcept
    {
        SimdT ret;
        ret = ((core(m[Ns], v[Ns]))+ ...);;
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE SimdT core(const ColV& matrix_v, unsigned int v_elem) noexcept
    {
        if constexpr(Col == 2)
        {
            return vmul_u32(vld1_u32(&matrix_v[0]), vdup_n_u32(v_elem));
        }
        else
        {
            return vmulq_u32(vld1q_u32(&matrix_v[0]), vdupq_n_u32(v_elem));
        }
    } 
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, unsigned int>>
{
    using M = mat<Col, Row, unsigned int>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<mat_traits_row_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RowV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RowV ret;
        ((ret[Ns] = core(v, m[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE unsigned int core(const ColV& v, const ColV& matrix_v)
    {
        if constexpr(Col == 2)
        {
            return vaddv_u32(vmul_u32(vld1_u32(&v[0]), vld1_u32(&matrix_v[0])));
        }
        else if constexpr(Col == 3)
        {
            uint32x4_t v_mul_mv = vmulq_u32(vld1q_u32(&v[0]), vld1q_u32(&matrix_v[0]));
            return vaddvq_u32(vsetq_lane_u32(zero<int>, v_mul_mv, 3));
        }
        else
        {
            return vaddvq_u32(vmulq_u32(vld1q_u32(&v[0]), vld1q_u32(&matrix_v[0])));
        }
    }
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::add<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, unsigned int>>
{
    using M = mat<Col, Row, unsigned int>;
    using ColV = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_row_n<M>>());
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
        if constexpr(Col == 2)
        {
            vst1_u32(&ret_v[0], vadd_u32(vld1_u32(&m1_v[0]), vld1_u32(&m2_v[0])));
        }
        else 
        {
            vst1q_u32(&ret_v[0], vaddq_u32(vld1q_u32(&m1_v[0]), vld1q_u32(&m2_v[0])));
        }
    }
};

template<size_t Col, size_t Row>
struct ktm::detail::mat_opt_implement::minus<Col, Row, std::enable_if_t<Col >= 2 && Col <= 4, unsigned int>>
{
    using M = mat<Col, Row, unsigned int>;
    using ColV = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_row_n<M>>());
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
        if constexpr(Col == 2)
        {
            vst1_u32(&ret_v[0], vsub_u32(vld1_u32(&m1_v[0]), vld1_u32(&m2_v[0])));
        }
        else 
        {
            vst1q_u32(&ret_v[0], vsubq_u32(vld1q_u32(&m1_v[0]), vld1q_u32(&m2_v[0])));
        }
    }
};

#endif

#endif
