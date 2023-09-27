#ifndef _MAT_COMMON_IMPL_INL_
#define _MAT_COMMON_IMPL_INL_

#include "Math/MathType/BaseType.h"
#include "Math/MathLib/Common.h"
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
struct ktm::detail::mat_common_implement::factor_lu<N, N, T>
{
    static_assert(N >= 2 && N <= 4 && std::is_floating_point_v<T>);
    using M = mat<N, N, T>;
    static CHTHOLLY_INLINE std::tuple<M, M> call(const M& m) noexcept
    {
        M l { }, u { };
        // u[i][0] = m[i][0]
        // l[0][j] = m[0][j] / u[0][0]
        for(int i = 0; i < N; ++i)
        {
            u[i][0] = m[i][0];
            l[i][i] = one<T>;
            l[0][i] = m[0][i];
        }

        for (int i = 1; i < N; i++)
        {
            //                     \- j-1
            // u[i][j] = m[i][j] - |  l[k][j] * u[i][k]
            //                     /- k=0
            for(int j = 1; j <= i; ++j)
            {
                u[i][j] = m[i][j];
                for(int k = 0; k < j; ++k)
                {
                    u[i][j] -= l[k][j] * u[i][k];
                }
            }

            //                     \- i-1
            // l[i][j] = m[i][j] - |  l[k][j] * u[i][k] / u[i][i]
            //                     /- k=0
            for(int j = i + 1; j < N; ++j)
            {
                l[i][j] = m[i][j];
                for(int k = 0; k < i; ++k)
                {
                    l[i][j] -= l[k][j] * u[i][k];
                }
                l[i][j] /= u[i][i];
            }
        }
        return { l, u };
    }
};

template<size_t N, typename T>
struct ktm::detail::mat_common_implement::factor_qr<N, N, T>
{
    static_assert(N >= 2 && N <= 4 && std::is_floating_point_v<T>);
    using M = mat<N, N, T>;
    static CHTHOLLY_INLINE std::tuple<M, M> call(const M& m) noexcept
    {
        M q { }, r { m };

        for(int i = 0; i < N; ++i)
        {
            q[i][i] = one<T>;
        }

        for(int k = 0; k < N; ++k)
        {
            T eta = zero<T>;
            for(int i = k; i < N; ++i)
            {
                eta = max(eta, abs(r[k][i]));
            }

            T alpha = zero<T>;
            for(int i = k; i < N; ++i)
            {
                alpha += r[k][i] * r[k][i] / (eta * eta);
            }
            if(r[k][k] > zero<T>)
            {
                eta = -eta;
            }
            alpha = eta * sqrt(alpha);

            T rho = sqrt(static_cast<T>(2) * alpha * (alpha - r[k][k]));
            r[k][k] = (r[k][k] - alpha) / rho;
            for(int i = k + 1; i < N; ++i)
            {
                r[k][i] /= rho;
            }

            for(int j = 0; j < N; ++j)
            {
                T t = zero<T>;
                for(int l = k; l < N; ++l)
                {
                    t += r[k][l] * q[j][l];
                }
                for(int i = k; i < N; ++i)
                {
                    q[j][i] -= static_cast<T>(2) * t * q[k][i];
                }
            }

            for(int j = 0; j < N; ++j)
            {
                T t = zero<T>;
                for(int l = k; l < N; ++l)
                {
                    t += r[k][l] * r[j][l];
                }
                for(int i = k; i < N; ++i)
                {
                    r[j][i] -= static_cast<T>(2) * t * r[k][i];
                }
            }
            r[k][k] = alpha;
            for(int i = k + 1; i < N; ++i)
            {
                r[k][i] = zero<T>;
            }
        }
        return { transpose<N, N, T>::call(q), r };
    }
};

#endif
