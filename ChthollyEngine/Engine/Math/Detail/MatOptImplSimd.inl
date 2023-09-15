#ifndef _MAT_OPT_IMPL_SIMD_H_
#define _MAT_OPT_IMPL_SIMD_H_

#include "Math/MathType/BaseType.h"
#include "MatOptImpl.h"

#ifdef __ARM_NEON__
#include <arm_neon.h>

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::mat_mul_vec<ktm::mat<Col, Raw, std::enable_if_t<Col >= 2 && Col <=4, float>>>
{
    using M = mat<Col, Raw, float>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v, std::index_sequence<Ns...>) noexcept
    {
        if constexpr(Col == 2)
        {
            float32x2_t ret;
            ((ret = ((float32x2_t) __builtin_neon_vld1_v(reinterpret_cast<const ColV*>(&m)[Ns], 9)) *
                    ((float32x2_t) {reinterpret_cast<const float*>(&v)[Ns], reinterpret_cast<const float*>(&v)[Ns]}))+ ...);
            return *reinterpret_cast<ColV*>(&ret);
        }
        else
        {
            float32x4_t ret;
            ((ret = ((float32x4_t) __builtin_neon_vld1q_v(reinterpret_cast<const ColV*>(&m)[Ns], 41)) *
                    ((float32x4_t) {reinterpret_cast<const float*>(&v)[Ns], reinterpret_cast<const float*>(&v)[Ns], reinterpret_cast<const float*>(&v)[Ns], reinterpret_cast<const float*>(&v)[Ns]}))+ ...);
            return *reinterpret_cast<ColV*>(&ret); 
        }
    }
};

template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::mat_mul_vec<ktm::mat<Col, Raw, std::enable_if_t<Col >= 2 && Col <=4, int>>>
{
    using M = mat<Col, Raw, int>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v, std::index_sequence<Ns...>) noexcept
    {
        if constexpr(Col == 2)
        {
            int32x2_t ret;
            ((ret = ((int32x2_t) __builtin_neon_vld1_v(reinterpret_cast<const ColV*>(&m)[Ns], 2)) *
                    ((int32x2_t) {reinterpret_cast<const int*>(&v)[Ns], reinterpret_cast<const int*>(&v)[Ns]}))+ ...);
            return *reinterpret_cast<ColV*>(&ret);
        }
        else
        {
            int32x4_t ret;
            ((ret = ((int32x4_t) __builtin_neon_vld1q_v(reinterpret_cast<const ColV*>(&m)[Ns], 34)) *
                    ((int32x4_t) {reinterpret_cast<const int*>(&v)[Ns], reinterpret_cast<const int*>(&v)[Ns], reinterpret_cast<const int*>(&v)[Ns], reinterpret_cast<const int*>(&v)[Ns]}))+ ...);
            return *reinterpret_cast<ColV*>(&ret); 
        }
    }
};


template<size_t Col, size_t Raw>
struct ktm::detail::mat_opt_implement::mat_mul_vec<ktm::mat<Col, Raw, std::enable_if_t<Col >= 2 && Col <=4, unsigned int>>>
{
    using M = mat<Col, Raw, unsigned int>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v, std::index_sequence<Ns...>) noexcept
    {
        if constexpr(Col == 2)
        {
            uint32x2_t ret;
            ((ret = ((uint32x2_t) __builtin_neon_vld1_v(reinterpret_cast<const ColV*>(&m)[Ns], 18)) *
                    ((uint32x2_t) {reinterpret_cast<const unsigned int*>(&v)[Ns], reinterpret_cast<const unsigned int*>(&v)[Ns]}))+ ...);
            return *reinterpret_cast<ColV*>(&ret);
        }
        else
        {
            uint32x4_t ret;
            ((ret = ((uint32x4_t) __builtin_neon_vld1q_v(reinterpret_cast<const ColV*>(&m)[Ns], 50)) *
                    ((uint32x4_t) {reinterpret_cast<const unsigned int*>(&v)[Ns], reinterpret_cast<const unsigned int*>(&v)[Ns], reinterpret_cast<const unsigned int*>(&v)[Ns], reinterpret_cast<const unsigned int*>(&v)[Ns]}))+ ...);
            return *reinterpret_cast<ColV*>(&ret); 
        }
    }
};

#endif

#endif