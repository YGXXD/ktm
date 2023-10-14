#ifndef _MAT_COMMON_IMPL_INL_
#define _MAT_COMMON_IMPL_INL_

#include "Math/MathType/BaseType.h"
#include "Math/MathLib/Common.h"
#include "MatCommonImpl.h"

template<size_t N, typename T>
struct ktm::detail::mat_common_implement::trace
{
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

template<size_t Row, size_t Col, typename T>
struct ktm::detail::mat_common_implement::transpose
{
	using M = mat<Row, Col, T>;
    using RetM = mat_traits_tp_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        return call(m, std::make_index_sequence<Col>(), std::make_index_sequence<Row>());
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
struct ktm::detail::mat_common_implement::determinant
{
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
        else
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
struct ktm::detail::mat_common_implement::inverse
{
    static_assert(std::is_floating_point_v<T>);
    using M = mat<N, N, T>;
    static CHTHOLLY_INLINE M call(const M& m) noexcept
    {
        T one_over_det = one<T> / determinant<N, T>::call(m);
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
struct ktm::detail::mat_common_implement::factor_lu
{
    static_assert(std::is_floating_point_v<T>);
    using M = mat<N, N, T>;
    static CHTHOLLY_NOINLINE std::tuple<M, M> call(const M& m) noexcept
    {
        M l = M::from_eye(), u { };
        // u[i][0] = m[i][0]
        // l[0][j] = m[0][j] / u[0][0]
        for(int i = 0; i < N; ++i)
        {
            u[i][0] = m[i][0];
            l[0][i] = m[0][i] / u[0][0];
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
struct ktm::detail::mat_common_implement::factor_qr
{
    static_assert(std::is_floating_point_v<T>);
    using M = mat<N, N, T>;
    static CHTHOLLY_NOINLINE std::tuple<M, M> call(const M& m) noexcept
    {
        M q = M::from_eye(), r { m };
        // householder
        for(int i = 0; i < N; ++i)
        {
            T alpha = zero<T>;
            for(int j = i; j < N; ++j)
            {
                alpha += r[i][j] * r[i][j];
            }
            alpha = r[i][i] > zero<T> ? -sqrt(alpha) : sqrt(alpha);

            T r_rho = rsqrt(static_cast<T>(2) * alpha * (alpha - r[i][i]));
            r[i][i] = (r[i][i] - alpha) * r_rho;
            for(int j = i + 1; j < N; ++j)
            {
                r[i][j] *= r_rho;
            }

            for(int k = 0; k < N; ++k)
            {
                T tq = zero<T>;
                T tr = zero<T>;
                for(int j = i; j < N; ++j)
                {
                    tq += r[i][j] * q[k][j];
                    tr += r[i][j] * r[k][j];
                }
                for(int j = i; j < N; ++j)
                {
                    q[k][j] -= static_cast<T>(2) * tq * r[i][j];
                    r[k][j] -= static_cast<T>(2) * tr * r[i][j];
                }
            }
            r[i][i] = alpha;
            for(int j = i + 1; j < N; ++j)
            {
                r[i][j] = zero<T>;
            }
        }
        return { transpose<N, N, T>::call(q), r };
    }
};

template<size_t N, typename T>
struct ktm::detail::mat_common_implement::eigen
{
    using M = mat<N, N, T>;
    using E = vec<N, T>;
    static CHTHOLLY_NOINLINE std::tuple<E, M> call(const M& m) noexcept
    {
        // qr iterator calc eigen vector and value
        M a { m }, eigen_vec = M::from_eye();
        E eigen_value, last_eigen_value;

        for(int i = 0; i < N; ++i)
        {
            eigen_value[i] = a[i][i]; 
        }
        
        for(int it = 0; it < 100; ++it) 
        {
            last_eigen_value = eigen_value;
            std::tuple<M, M> qr = factor_qr<N, T>::call(a);
            a = std::get<1>(qr) * std::get<0>(qr);
            eigen_vec = eigen_vec * std::get<0>(qr);

            for(int i = 0; i < N; ++i)
            {
                eigen_value[i] = a[i][i]; 
            }
            if(equal_zero(reduce_max(abs(eigen_value - last_eigen_value))))
                break;
        }
        return { eigen_value, eigen_vec };
    }
};

template<size_t N, typename T>
struct ktm::detail::mat_common_implement::factor_svd
{
    static_assert(std::is_floating_point_v<T>);
    using M = mat<N, N, T>;

    static CHTHOLLY_NOINLINE std::tuple<M, M, M> call(const M& m)
    {
        if constexpr(N == 2)
        {
            T a = m[0][0], c = m[0][1], b = m[1][0], d = m[1][1];
            T a2 = pow2(a), b2 = pow2(b), c2 = pow2(c), d2 = pow2(d);
            T a2_p_b2 = a2 + b2;
            T c2_p_d2 = c2 + d2;
            T ac_p_bd = a * c + b * d;
            T two_ac_p_bd = 2 * ac_p_bd;
            T a2_p_b2_m_c2_m_d2 = a2_p_b2 - c2_p_d2;

            T theta = static_cast<T>(0.5) * atan2(two_ac_p_bd, a2_p_b2_m_c2_m_d2);
            T cos_theta = cos(theta);
            T sin_theta = sin(theta);

            M u = { { cos_theta, sin_theta }, { -sin_theta, cos_theta } };
            
            T sg1 = a2_p_b2 + c2_p_d2;
            T sg2 = sqrt(pow2(a2_p_b2_m_c2_m_d2) + pow2(two_ac_p_bd));
            T sigma1 = sqrt(static_cast<T>(0.5) * (sg1 + sg2));
            T sigma2 = sqrt(static_cast<T>(0.5) * (sg1 - sg2));
            M s = { { sigma1, 0 }, { 0, sigma2 } };

            T phi   = static_cast<T>(0.5) * atan2(static_cast<T>(2) * (a * b + c * d), a2 - b2 + c2 - d2);
            T cos_phi   = cos(phi);
            T sin_phi   = sin(phi);

            T s11 = (a * cos_theta + c * sin_theta) * cos_theta + ( b * cos_theta + d * sin_theta) * sin_phi;
            T s22 = (a * sin_theta - c * cos_theta) * sin_phi   + (-b * sin_theta + d * cos_theta) * cos_phi;
            T sign_s11 = static_cast<T>(s11 > 0 ? 1 : (s11 < 0 ? -1 : 0));
            T sign_s22 = static_cast<T>(s22 > 0 ? 1 : (s22 < 0 ? -1 : 0));

            M v = { { sign_s11 * cos_phi, sign_s11 * sin_phi }, { -sign_s22 * sin_phi, sign_s22 * cos_phi } };
            return { u, s, v };
        }
        else
        {
            std::tuple<vec<N, T>, M> ata_eigen = eigen<N, T>::call(transpose<N, N, T>::call(m) * m);
            vec<N, T>& ata_eigen_value_ref = std::get<0>(ata_eigen);
            for(int i = 0; i < N; ++i)
            {
                ata_eigen_value_ref[i] = sqrt(abs(ata_eigen_value_ref[i])); 
            }
            M v = transpose<N, N, T>::call(std::get<1>(ata_eigen));
            M s = M::from_diag(ata_eigen_value_ref);
            for(int i = 0; i < N; ++i)
            {
                ata_eigen_value_ref[i] = one<T> / ata_eigen_value_ref[i];  
            }
            M u = m * std::get<1>(ata_eigen) * M::from_diag(ata_eigen_value_ref);
            return { u, s, v };
        }
    }
};
#endif
