#ifndef _KTM_MATRIX_INL_
#define _KTM_MATRIX_INL_

#include "matrix_fwd.h"
#include "../../setup.h"
#include "../../type/basic.h"
#include "../../type/mat_fwd.h"
#include "../../function/arithmetic.h"
#include "../../function/common.h"

template<size_t N, typename T>
struct ktm::detail::matrix_implement::trace
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
struct ktm::detail::matrix_implement::transpose
{
	using M = mat<Row, Col, T>;
    using RetM = mat<Col, Row, T>;
    using RowV = vec<Row, T>;
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

template<typename T>
struct ktm::detail::matrix_implement::determinant<2, T>
{
    using M = mat<2, 2, T>;
    static CHTHOLLY_INLINE T call(const M& m) noexcept
    {
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
    }
};

template<typename T>
struct ktm::detail::matrix_implement::determinant<3, T>
{
    using M = mat<3, 3, T>;
    static CHTHOLLY_INLINE T call(const M& m) noexcept
    {
        return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) +
               m[1][0] * (m[2][1] * m[0][2] - m[0][1] * m[2][2]) +
               m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
    }
};

template<typename T>
struct ktm::detail::matrix_implement::determinant<4, T>
{
    using M = mat<4, 4, T>;
    static CHTHOLLY_INLINE T call(const M& m) noexcept
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
};

template<typename T>
struct ktm::detail::matrix_implement::inverse<2, T>
{
    static_assert(std::is_floating_point_v<T>);
    using M = mat<2, 2, T>;
    static CHTHOLLY_INLINE M call(const M& m) noexcept
    {
        T one_over_det = one<T> / determinant<2, T>::call(m);
        M ret;
        ret[0][0] = m[1][1] * one_over_det;
        ret[0][1] = - m[1][0] * one_over_det; 
        ret[1][0] = - m[0][1] * one_over_det; 
        ret[1][1] = m[0][0] * one_over_det;
        return ret;
    }
};

template<typename T>
struct ktm::detail::matrix_implement::inverse<3, T>
{
    static_assert(std::is_floating_point_v<T>);
    using M = mat<3, 3, T>;
    static CHTHOLLY_INLINE M call(const M& m) noexcept
    {
        T one_over_det = one<T> / determinant<3, T>::call(m);
        M ret;
        ret[0][0] = one_over_det * (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
        ret[0][1] = one_over_det * (m[2][1] * m[0][2] - m[0][1] * m[2][2]);
        ret[0][2] = one_over_det * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
        ret[1][0] = one_over_det * (m[2][0] * m[1][2] - m[1][0] * m[2][2]);    
        ret[1][1] = one_over_det * (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
        ret[1][2] = one_over_det * (m[1][0] * m[0][2] - m[0][0] * m[1][2]);
        ret[2][0] = one_over_det * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
        ret[2][1] = one_over_det * (m[2][0] * m[0][1] - m[0][0] * m[2][1]);
        ret[2][2] = one_over_det * (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
        return ret;
    }
};

template<typename T>
struct ktm::detail::matrix_implement::inverse<4, T>
{
    static_assert(std::is_floating_point_v<T>);
    using M = mat<4, 4, T>;
    static CHTHOLLY_INLINE M call(const M& m) noexcept
    {
        T one_over_det = one<T> / determinant<4, T>::call(m);
        M ret;
        ret[0][0] =
            one_over_det * (m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] +
                            m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2]);
        ret[0][1] =
            one_over_det * (m[3][1] * m[0][3] * m[2][2] - m[3][1] * m[0][2] * m[2][3] - m[2][1] * m[0][3] * m[3][2] +
                            m[2][1] * m[0][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] - m[0][1] * m[2][2] * m[3][3]);
        ret[0][2] =
            one_over_det * (m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] +
                            m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2]);
        ret[0][3] =
            one_over_det * (m[2][1] * m[0][3] * m[1][2] - m[2][1] * m[0][2] * m[1][3] - m[1][1] * m[0][3] * m[2][2] +
                            m[1][1] * m[0][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] - m[0][1] * m[1][2] * m[2][3]);
        ret[1][0] =
            one_over_det * (m[3][0] * m[1][3] * m[2][2] - m[3][0] * m[1][2] * m[2][3] - m[2][0] * m[1][3] * m[3][2] +
                            m[2][0] * m[1][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] - m[1][0] * m[2][2] * m[3][3]);
        ret[1][1] =
            one_over_det * (m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] +
                            m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2]);
        ret[1][2] =
            one_over_det * (m[3][0] * m[0][3] * m[1][2] - m[3][0] * m[0][2] * m[1][3] - m[1][0] * m[0][3] * m[3][2] +
                            m[1][0] * m[0][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] - m[0][0] * m[1][2] * m[3][3]);
        ret[1][3] =
            one_over_det * (m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] +
                            m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2]);
        ret[2][0] =
            one_over_det * (m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] +
                            m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1]);
        ret[2][1] =
            one_over_det * (m[3][0] * m[0][3] * m[2][1] - m[3][0] * m[0][1] * m[2][3] - m[2][0] * m[0][3] * m[3][1] +
                            m[2][0] * m[0][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] - m[0][0] * m[2][1] * m[3][3]);
        ret[2][2] =
            one_over_det * (m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] +
                            m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1]);
        ret[2][3] =
            one_over_det * (m[2][0] * m[0][3] * m[1][1] - m[2][0] * m[0][1] * m[1][3] - m[1][0] * m[0][3] * m[2][1] +
                            m[1][0] * m[0][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] - m[0][0] * m[1][1] * m[2][3]);
        ret[3][0] =
            one_over_det * (m[3][0] * m[1][2] * m[2][1] - m[3][0] * m[1][1] * m[2][2] - m[2][0] * m[1][2] * m[3][1] +
                            m[2][0] * m[1][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] - m[1][0] * m[2][1] * m[3][2]);
        ret[3][1] =
            one_over_det * (m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] +
                            m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1]);
        ret[3][2] =
            one_over_det * (m[3][0] * m[0][2] * m[1][1] - m[3][0] * m[0][1] * m[1][2] - m[1][0] * m[0][2] * m[3][1] +
                            m[1][0] * m[0][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] - m[0][0] * m[1][1] * m[3][2]);
        ret[3][3] =
            one_over_det * (m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] +
                            m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1]);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::matrix_implement::factor_lu
{
    static_assert(std::is_floating_point_v<T>);
    using M = mat<N, N, T>;
    static CHTHOLLY_NOINLINE std::tuple<M, M> call(const M& m) noexcept
    {
        M l = M::from_eye(), u { };
        // 求矩阵lu分解
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
struct ktm::detail::matrix_implement::factor_qr
{
    static_assert(std::is_floating_point_v<T>);
    using M = mat<N, N, T>;
    static CHTHOLLY_NOINLINE std::tuple<M, M> call(const M& m) noexcept
    {
        // householder变换求矩阵qr分解
        M q = M::from_eye(), r { m };
        
        for(int i = 0; i < N; ++i)
        {
            T alpha = zero<T>;
            for(int j = i; j < N; ++j)
            {
                alpha += r[i][j] * r[i][j];
            }
            alpha = r[i][i] > zero<T> ? -ktm::sqrt(alpha) : ktm::sqrt(alpha);

            T r_rho = ktm::rsqrt(static_cast<T>(2) * alpha * (alpha - r[i][i]));
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
struct ktm::detail::matrix_implement::eigen_qr_it
{
    using M = mat<N, N, T>;
    using E = vec<N, T>;
    static CHTHOLLY_NOINLINE std::tuple<E, M> call(const M& m) noexcept
    {
        // qr迭代法求矩阵特征向量和特征值
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
            if(ktm::equal_zero(ktm::reduce_max(ktm::abs(eigen_value - last_eigen_value))))
                break;
        }
        return { eigen_value, eigen_vec };
    }
};

template<size_t N, typename T>
struct ktm::detail::matrix_implement::eigen_jacobi_it
{
    using M = mat<N, N, T>;
    using E = vec<N, T>;
    static CHTHOLLY_NOINLINE std::tuple<E, M> call(const M& m) noexcept
    {
        // jacobi迭代求矩阵特征向量和特征值(矩阵必须为对称矩阵)
        M a { m }, eigen_vec = M::from_eye();
        E eigen_value;

        for(int it = 0; it < 100; ++it)
        {
            // 找到非对角线的最大元素
            int col = 0, row = 1;
            T nd_max = ktm::abs(a[0][1]);
            for(int i = 0; i < N; ++i)
            {
                for(int j = i + 1; j < N; ++j)
                {
                    T nd_elem = ktm::abs(a[i][j]);
                    if(nd_elem > nd_max)
                    {
                        col = i;
                        row = j;
                        nd_max = nd_elem;
                    }
                }
            }
            
            if(ktm::equal_zero(nd_max))
                break;
            
            T acc = a[col][col];
            T arr = a[row][row];
            T acr = a[col][row];
            
            // 计算旋转角度
            T sin_theta, cos_theta, sin_2theta, cos_2theta;

            if(ktm::equal(arr, acc))
            {
                if(acr < 0)
                {
                    sin_theta = -ktm::rsqrt(static_cast<T>(2));
                    cos_theta = ktm::rsqrt(static_cast<T>(2));
                    sin_2theta = -one<T>;
                    cos_2theta = zero<T>;
                }
                else 
                {
                    sin_theta = ktm::rsqrt(static_cast<T>(2));
                    cos_theta = ktm::rsqrt(static_cast<T>(2));
                    sin_2theta = one<T>;
                    cos_2theta = zero<T>; 
                }
            }
            else
            {
                T theta = static_cast<T>(0.5) * ktm::atan2(static_cast<T>(2) * acr, arr - acc);
                sin_theta = ktm::sin(theta);
                cos_theta = ktm::cos(theta);
                sin_2theta = ktm::sin(static_cast<T>(2) * theta);
                cos_2theta = ktm::cos(static_cast<T>(2) * theta);
            }

            // 计算迭代后的的矩阵元素
            a[col][col] = arr * sin_theta * sin_theta + acc * cos_theta * cos_theta + acr * sin_2theta; 
            a[row][row] = arr * cos_theta * cos_theta + acc * sin_theta * sin_theta + acr * sin_2theta;
            a[col][row] = static_cast<T>(0.5) * (acc - arr) * sin_2theta + acr * cos_2theta;
            a[row][col] = a[col][row];

            for(int i = 0; i < N; ++i)
            {
                if((i != col) && (i != row))
                {
                    T aci = a[col][i];
                    T ari = a[row][i];

                    a[col][i] = cos_theta * aci - sin_theta * ari;
                    a[row][i] = cos_theta * ari + sin_theta * aci;
                    a[i][col] = a[col][i];
                    a[i][row] = a[row][i];
                }
            }

            // 计算特征向量
            for(int i = 0; i < N; ++i)
            {
                T eci = eigen_vec[col][i];
                T eri = eigen_vec[row][i];

                eigen_vec[col][i] = cos_theta * eci - sin_theta * eri;
                eigen_vec[row][i] = cos_theta * eri + sin_theta * eci;
            }
        }

        for(int i = 0; i < N; ++i)
        {
            eigen_value[i] = a[i][i];
        }

        return { eigen_value, eigen_vec };
    }
};

template<size_t N, typename T>
struct ktm::detail::matrix_implement::factor_svd
{
    static_assert(std::is_floating_point_v<T>);
    using M = mat<N, N, T>;

    static CHTHOLLY_NOINLINE std::tuple<M, M, M> call(const M& m)
    {
        // 求矩阵svd分解(通过jacobi迭代法找矩阵特征向量和特征值)
        std::tuple<vec<N, T>, M> ata_eigen = eigen_jacobi_it<N, T>::call(transpose<N, N, T>::call(m) * m);
        vec<N, T>& ata_eigen_value_ref = std::get<0>(ata_eigen);
        for(int i = 0; i < N; ++i)
        {
            ata_eigen_value_ref[i] = ktm::sqrt(ktm::abs(ata_eigen_value_ref[i])); 
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
};

// template<typename T>
// struct ktm::detail::matrix_implement::factor_svd<2, T>
// {
//     // ref: https://lucidar.me/en/mathematics/singular-value-decomposition-of-a-2x2-matrix/
//     static_assert(std::is_floating_point_v<T>);
//     using M = mat<2, 2, T>;
//     static CHTHOLLY_NOINLINE std::tuple<M, M, M> call(const M& m)
//     {
//         T a = m[0][0], c = m[0][1], b = m[1][0], d = m[1][1];
//         T a2 = ktm::pow2(a), b2 = ktm::pow2(b), c2 = ktm::pow2(c), d2 = ktm::pow2(d);
//         T a2_p_b2 = a2 + b2;
//         T c2_p_d2 = c2 + d2;
//         T ac_p_bd = a * c + b * d;
//         T two_ac_p_bd = 2 * ac_p_bd;
//         T a2_p_b2_m_c2_m_d2 = a2_p_b2 - c2_p_d2;

//         T theta = static_cast<T>(0.5) * ktm::atan2(two_ac_p_bd, a2_p_b2_m_c2_m_d2);
//         T cos_theta = ktm::cos(theta);
//         T sin_theta = ktm::sin(theta);

//         M u = { { cos_theta, sin_theta }, { -sin_theta, cos_theta } };

//         T sg1 = a2_p_b2 + c2_p_d2;
//         T sg2 = ktm::sqrt(ktm::pow2(a2_p_b2_m_c2_m_d2) + ktm::pow2(two_ac_p_bd));
//         T sigma1 = ktm::sqrt(static_cast<T>(0.5) * (sg1 + sg2));
//         T sigma2 = ktm::sqrt(static_cast<T>(0.5) * (sg1 - sg2));
//         M s = { { sigma1, 0 }, { 0, sigma2 } };

//         T phi   = static_cast<T>(0.5) * ktm::atan2(static_cast<T>(2) * (a * b + c * d), a2 - b2 + c2 - d2);
//         T cos_phi   = ktm::cos(phi);
//         T sin_phi   = ktm::sin(phi);

//         T s11 = (a * cos_theta + c * sin_theta) * cos_theta + ( b * cos_theta + d * sin_theta) * sin_phi;
//         T s22 = (a * sin_theta - c * cos_theta) * sin_phi   + (-b * sin_theta + d * cos_theta) * cos_phi;
//         T sign_s11 = static_cast<T>(s11 > 0 ? 1 : (s11 < 0 ? -1 : 0));
//         T sign_s22 = static_cast<T>(s22 > 0 ? 1 : (s22 < 0 ? -1 : 0));

//         M v = { { sign_s11 * cos_phi, sign_s11 * sin_phi }, { -sign_s22 * sin_phi, sign_s22 * cos_phi } };
//         return { u, s, v };
//     } 
// };
#endif
