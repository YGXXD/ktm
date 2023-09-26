#ifndef _MAT_COMMON_IMPL_INL_
#define _MAT_COMMON_IMPL_INL_

#include "Math/MathType/BaseType.h"
#include "MatCommonImpl.h"

template<size_t Col, size_t Row, typename T>
struct ktm::detail::mat_common_implement::transpose
{
	using M = mat<Col, Row, T>;
    using RetM = mat_traits_tp_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        return call(m, std::make_index_sequence<mat_traits_col_n<M>>(), std::make_index_sequence<mat_traits_row_n<M>>());
    }
private:
    template<size_t ...Rs, size_t ...Cs>
    static CHTHOLLY_INLINE RetM call(const M& m, std::index_sequence<Rs...>, std::index_sequence<Cs...>) noexcept
    {
        RetM ret;
        size_t row_index;
        ((row_index = Rs, ret[Rs] = RowV(m[Cs][row_index]...)), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::mat_common_implement::determinant<N, N, T>
{
    static_assert(N >= 2 && N <= 4);
    using M = mat<N, N, T>;
    static CHTHOLLY_INLINE T call(const M& m) noexcept
    {
        if constexpr(N == 2)
        {
            return m[0][0] * m[1][1] - m[1][0] * m[0][1];
        }
        else if constexpr(N == 3)
        {
            return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) +
                   m[1][0] * (m[2][1] * m[0][2] - m[0][1] * m[2][2]) +
                   m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
        }
        else if constexpr(N == 4)
        {
            T d00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
            T d01 = m[3][2] * m[1][3] - m[1][2] * m[3][3];
            T d02 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
            T r0  = m[1][1] * d00 + m[2][1] * d01 + m[3][1] * d02;
            T r1  = m[1][0] * d00 + m[2][0] * d01 + m[3][0] * d02;

            T d10 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
            T d11 = m[3][0] * m[1][1] - m[1][0] * m[3][1];
            T d12 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
            T r2  = m[1][3] * d10 + m[2][3] * d11 + m[3][3] * d12;
            T r3  = m[1][2] * d10 + m[2][2] * d11 + m[3][2] * d12;
                   
            return m[0][0] * r0 - m[0][1] * r1 + m[0][2] * r2 - m[0][3] * r3;
        }
    }
};

template<size_t N, typename T>
struct ktm::detail::mat_common_implement::inverse<N, N, T>
{
    static_assert(N >= 2 && N <= 4 && std::is_floating_point_v<T>);
    using M = mat<N, N, T>;
    static CHTHOLLY_INLINE M call(const M& m) noexcept
    {
        T one_over_det = one<T> / determinant<N, N, T>::call(m);
        M ret;
        if constexpr(N == 2)
        {
            ret[0][0] = m[1][1] * one_over_det;
            ret[0][1] = - m[1][0] * one_over_det; 
            ret[1][0] = - m[0][1] * one_over_det; 
            ret[1][1] = m[0][0] * one_over_det; 
        }
        if constexpr(N == 3)
        {
            ret[0][0] = one_over_det * (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
            ret[0][1] = one_over_det * (m[2][1] * m[0][2] - m[0][1] * m[2][2]);
            ret[0][2] = one_over_det * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
            ret[1][0] = one_over_det * (m[2][0] * m[1][2] - m[1][0] * m[2][2]);    
            ret[1][1] = one_over_det * (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
            ret[1][2] = one_over_det * (m[1][0] * m[0][2] - m[0][0] * m[1][2]);
            ret[2][0] = one_over_det * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
            ret[2][1] = one_over_det * (m[2][0] * m[0][1] - m[0][0] * m[2][1]);
            ret[2][2] = one_over_det * (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
        }
        else
        {
            ret[0][0] = one_over_det *
                        (m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] +
                         m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2]);

            ret[0][1] = one_over_det *
                        (m[3][1] * m[0][3] * m[2][2] - m[3][1] * m[0][2] * m[2][3] - m[2][1] * m[0][3] * m[3][2] +
                         m[2][1] * m[0][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] - m[0][1] * m[2][2] * m[3][3]);

            ret[0][2] = one_over_det *
                        (m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] +
                         m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2]);

            ret[0][3] = one_over_det *
                        (m[2][1] * m[0][3] * m[1][2] - m[2][1] * m[0][2] * m[1][3] - m[1][1] * m[0][3] * m[2][2] +
                         m[1][1] * m[0][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] - m[0][1] * m[1][2] * m[2][3]);

            ret[1][0] = one_over_det *
                        (m[3][0] * m[1][3] * m[2][2] - m[3][0] * m[1][2] * m[2][3] - m[2][0] * m[1][3] * m[3][2] +
                         m[2][0] * m[1][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] - m[1][0] * m[2][2] * m[3][3]);

            ret[1][1] = one_over_det *
                        (m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] +
                         m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2]);

            ret[1][2] = one_over_det *
                        (m[3][0] * m[0][3] * m[1][2] - m[3][0] * m[0][2] * m[1][3] - m[1][0] * m[0][3] * m[3][2] +
                         m[1][0] * m[0][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] - m[0][0] * m[1][2] * m[3][3]);

            ret[1][3] = one_over_det *
                        (m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] +
                         m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2]);

            ret[2][0] = one_over_det *
                        (m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] +
                         m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1]);

            ret[2][1] = one_over_det *
                        (m[3][0] * m[0][3] * m[2][1] - m[3][0] * m[0][1] * m[2][3] - m[2][0] * m[0][3] * m[3][1] +
                         m[2][0] * m[0][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] - m[0][0] * m[2][1] * m[3][3]);

            ret[2][2] = one_over_det *
                        (m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] +
                         m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1]);

            ret[2][3] = one_over_det *
                        (m[2][0] * m[0][3] * m[1][1] - m[2][0] * m[0][1] * m[1][3] - m[1][0] * m[0][3] * m[2][1] +
                         m[1][0] * m[0][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] - m[0][0] * m[1][1] * m[2][3]);

            ret[3][0] = one_over_det *
                        (m[3][0] * m[1][2] * m[2][1] - m[3][0] * m[1][1] * m[2][2] - m[2][0] * m[1][2] * m[3][1] +
                         m[2][0] * m[1][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] - m[1][0] * m[2][1] * m[3][2]);

            ret[3][1] = one_over_det *
                        (m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] +
                         m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1]);

            ret[3][2] = one_over_det *
                        (m[3][0] * m[0][2] * m[1][1] - m[3][0] * m[0][1] * m[1][2] - m[1][0] * m[0][2] * m[3][1] +
                         m[1][0] * m[0][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] - m[0][0] * m[1][1] * m[3][2]);

            ret[3][3] = one_over_det *
                        (m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] +
                         m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1]);
        }
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::mat_common_implement::trace<N, N, T>
{
    static_assert(N >= 2 && N <= 4);
    using M = mat<N, N, T>;
    static CHTHOLLY_INLINE T call(const M& m) noexcept
    {
        return call(m, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T call(const M& m, std::index_sequence<Ns...>) noexcept
    {
        return ((m[Ns][Ns])+ ...);
    }
};
#endif
