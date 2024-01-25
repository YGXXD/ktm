#ifndef _KTM_MATRIX_FWD_H_
#define _KTM_MATRIX_FWD_H_

#include <cstddef>
#include <type_traits>

namespace ktm
{
namespace detail
{
namespace matrix_implement
{
template<size_t N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct trace;

template<size_t Row, size_t Col, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct transpose;

template<size_t N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct determinant;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct inverse;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct factor_lu;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct factor_qr;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct eigen_qr_it;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct eigen_jacobi_it;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct factor_svd;
}
}
}

#endif