#ifndef _MAT_OPT_IMPL_SIMD_H_
#define _MAT_OPT_IMPL_SIMD_H_

#include "Math/MathType/BaseType.h"
#include "MatOptImpl.h"

#ifdef __ARM_NEON__
#include <arm_neon.h>

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, float>>
{
    using M = mat<Col, Raw, float>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    using SimdT = std::select_if_t<Col == 2, float32x2_t, float32x4_t>;

    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v, std::index_sequence<Ns...>) noexcept
    {
        SimdT ret;
        ret = ((core(reinterpret_cast<const ColV*>(&m)[Ns], reinterpret_cast<const float*>(&v)[Ns]))+ ...);;
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE SimdT core(const ColV& matrix_v, float v_elem) noexcept
    {
        if constexpr(Col == 2)
        {
            return vmul_f32(vld1_f32(reinterpret_cast<const float*>(&matrix_v)), vdup_n_f32(v_elem));
        }
        else
        {
            return vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&matrix_v)), vdupq_n_f32(v_elem));
        }
    } 
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, float>>
{
    using M = mat<Col, Raw, float>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE RawV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RawV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RawV ret;
        ((reinterpret_cast<float*>(&ret)[Ns] = core(v, reinterpret_cast<const ColV*>(&m)[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE float core(const ColV& v, const ColV& matrix_v)
    {
        if constexpr(Col == 2)
        {
            return vaddv_f32(vmul_f32(vld1_f32(reinterpret_cast<const float*>(&v)), vld1_f32(reinterpret_cast<const float*>(&matrix_v))));
        }
        else if constexpr(Col == 3)
        {
            float32x4_t v_mul_mv = vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&v)), vld1q_f32(reinterpret_cast<const float*>(&matrix_v)));
            return vaddvq_f32(vsetq_lane_f32(zero<float>, v_mul_mv, 3));
        }
        else
        {
            return vaddvq_f32(vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&v)), vld1q_f32(reinterpret_cast<const float*>(&matrix_v))));
        }
    }
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::add<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, float>>
{
    using M = mat<Col, Raw, float>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((core(reinterpret_cast<ColV*>(&ret)[Ns], reinterpret_cast<const ColV*>(&m1)[Ns], reinterpret_cast<const ColV*>(&m2)[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        if constexpr(Col == 2)
        {
            vst1_f32(reinterpret_cast<float*>(&ret_v), vadd_f32(vld1_f32(reinterpret_cast<const float*>(&m1_v)), vld1_f32(reinterpret_cast<const float*>(&m2_v))));
        }
        else 
        {
            vst1q_f32(reinterpret_cast<float*>(&ret_v), vaddq_f32(vld1q_f32(reinterpret_cast<const float*>(&m1_v)), vld1q_f32(reinterpret_cast<const float*>(&m2_v))));
        }
    }
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::minus<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, float>>
{
    using M = mat<Col, Raw, float>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_raw_n<M>>());
    }
private:
   template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((core(reinterpret_cast<ColV*>(&ret)[Ns], reinterpret_cast<const ColV*>(&m1)[Ns], reinterpret_cast<const ColV*>(&m2)[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        if constexpr(Col == 2)
        {
            vst1_f32(reinterpret_cast<float*>(&ret_v), vsub_f32(vld1_f32(reinterpret_cast<const float*>(&m1_v)), vld1_f32(reinterpret_cast<const float*>(&m2_v))));
        }
        else 
        {
            vst1q_f32(reinterpret_cast<float*>(&ret_v), vsubq_f32(vld1q_f32(reinterpret_cast<const float*>(&m1_v)), vld1q_f32(reinterpret_cast<const float*>(&m2_v))));
        }
    }
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, int>>
{
    using M = mat<Col, Raw, int>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    using SimdT = std::select_if_t<Col == 2, int32x2_t, int32x4_t>;

    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v, std::index_sequence<Ns...>) noexcept
    {
        SimdT ret;
        ret = ((core(reinterpret_cast<const ColV*>(&m)[Ns], reinterpret_cast<const int*>(&v)[Ns]))+ ...);;
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE SimdT core(const ColV& matrix_v, int v_elem) noexcept
    {
        if constexpr(Col == 2)
        {
            return vmul_s32(vld1_s32(reinterpret_cast<const int*>(&matrix_v)), vdup_n_s32(v_elem));
        }
        else
        {
            return vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&matrix_v)), vdupq_n_s32(v_elem));
        }
    } 
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, int>>
{
    using M = mat<Col, Raw, int>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE RawV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RawV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RawV ret;
        ((reinterpret_cast<int*>(&ret)[Ns] = core(v, reinterpret_cast<const ColV*>(&m)[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE int core(const ColV& v, const ColV& matrix_v)
    {
        if constexpr(Col == 2)
        {
            return vaddv_s32(vmul_s32(vld1_s32(reinterpret_cast<const int*>(&v)), vld1_s32(reinterpret_cast<const int*>(&matrix_v))));
        }
        else if constexpr(Col == 3)
        {
            int32x4_t v_mul_mv = vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&v)), vld1q_s32(reinterpret_cast<const int*>(&matrix_v)));
            return vaddvq_s32(vsetq_lane_s32(zero<int>, v_mul_mv, 3));
        }
        else
        {
            return vaddvq_s32(vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&v)), vld1q_s32(reinterpret_cast<const int*>(&matrix_v))));
        }
    }
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::add<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, int>>
{
    using M = mat<Col, Raw, int>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((core(reinterpret_cast<ColV*>(&ret)[Ns], reinterpret_cast<const ColV*>(&m1)[Ns], reinterpret_cast<const ColV*>(&m2)[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        if constexpr(Col == 2)
        {
            vst1_s32(reinterpret_cast<int*>(&ret_v), vadd_s32(vld1_s32(reinterpret_cast<const int*>(&m1_v)), vld1_s32(reinterpret_cast<const int*>(&m2_v))));
        }
        else 
        {
            vst1q_s32(reinterpret_cast<int*>(&ret_v), vaddq_s32(vld1q_s32(reinterpret_cast<const int*>(&m1_v)), vld1q_s32(reinterpret_cast<const int*>(&m2_v))));
        }
    }
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::minus<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, int>>
{
    using M = mat<Col, Raw, int>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_raw_n<M>>());
    }
private:
   template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((core(reinterpret_cast<ColV*>(&ret)[Ns], reinterpret_cast<const ColV*>(&m1)[Ns], reinterpret_cast<const ColV*>(&m2)[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        if constexpr(Col == 2)
        {
            vst1_s32(reinterpret_cast<int*>(&ret_v), vsub_s32(vld1_s32(reinterpret_cast<const int*>(&m1_v)), vld1_s32(reinterpret_cast<const int*>(&m2_v))));
        }
        else 
        {
            vst1q_s32(reinterpret_cast<int*>(&ret_v), vsubq_s32(vld1q_s32(reinterpret_cast<const int*>(&m1_v)), vld1q_s32(reinterpret_cast<const int*>(&m2_v))));
        }
    }
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::mat_mul_vec<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, unsigned int>>
{
    using M = mat<Col, Raw, unsigned int>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    using SimdT = std::select_if_t<Col == 2, uint32x2_t, uint32x4_t>;

    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v, std::index_sequence<Ns...>) noexcept
    {
        SimdT ret;
        ret = ((core(reinterpret_cast<const ColV*>(&m)[Ns], reinterpret_cast<const unsigned int*>(&v)[Ns]))+ ...);;
        return *reinterpret_cast<ColV*>(&ret); 
    }

    static CHTHOLLY_INLINE SimdT core(const ColV& matrix_v, unsigned int v_elem) noexcept
    {
        if constexpr(Col == 2)
        {
            return vmul_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&matrix_v)), vdup_n_u32(v_elem));
        }
        else
        {
            return vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&matrix_v)), vdupq_n_u32(v_elem));
        }
    } 
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::vec_mul_mat<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, unsigned int>>
{
    using M = mat<Col, Raw, unsigned int>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE RawV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RawV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RawV ret;
        ((reinterpret_cast<unsigned int*>(&ret)[Ns] = core(v, reinterpret_cast<const ColV*>(&m)[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE unsigned int core(const ColV& v, const ColV& matrix_v)
    {
        if constexpr(Col == 2)
        {
            return vaddv_u32(vmul_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&v)), vld1_u32(reinterpret_cast<const unsigned int*>(&matrix_v))));
        }
        else if constexpr(Col == 3)
        {
            uint32x4_t v_mul_mv = vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&v)), vld1q_u32(reinterpret_cast<const unsigned int*>(&matrix_v)));
            return vaddvq_u32(vsetq_lane_u32(zero<unsigned int>, v_mul_mv, 3));
        }
        else
        {
            return vaddvq_u32(vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&v)), vld1q_u32(reinterpret_cast<const unsigned int*>(&matrix_v))));
        }
    }
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::add<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, unsigned int>>
{
    using M = mat<Col, Raw, unsigned int>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((core(reinterpret_cast<ColV*>(&ret)[Ns], reinterpret_cast<const ColV*>(&m1)[Ns], reinterpret_cast<const ColV*>(&m2)[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        if constexpr(Col == 2)
        {
            vst1_u32(reinterpret_cast<unsigned int*>(&ret_v), vadd_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&m1_v)), vld1_u32(reinterpret_cast<const unsigned int*>(&m2_v))));
        }
        else 
        {
            vst1q_u32(reinterpret_cast<unsigned int*>(&ret_v), vaddq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&m1_v)), vld1q_u32(reinterpret_cast<const unsigned int*>(&m2_v))));
        }
    }
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::minus<Col, Raw, std::enable_if_t<Col >= 2 && Col <= 4, unsigned int>>
{
    using M = mat<Col, Raw, unsigned int>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_raw_n<M>>());
    }
private:
   template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        ((core(reinterpret_cast<ColV*>(&ret)[Ns], reinterpret_cast<const ColV*>(&m1)[Ns], reinterpret_cast<const ColV*>(&m2)[Ns])), ...);
        return ret;
    }

    static CHTHOLLY_INLINE void core(ColV& ret_v, const ColV& m1_v, const ColV& m2_v)
    {
        if constexpr(Col == 2)
        {
            vst1_u32(reinterpret_cast<unsigned int*>(&ret_v), vsub_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&m1_v)), vld1_u32(reinterpret_cast<const unsigned int*>(&m2_v))));
        }
        else 
        {
            vst1q_u32(reinterpret_cast<unsigned int*>(&ret_v), vsubq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&m1_v)), vld1q_u32(reinterpret_cast<const unsigned int*>(&m2_v))));
        }
    }
};

#endif

#endif
