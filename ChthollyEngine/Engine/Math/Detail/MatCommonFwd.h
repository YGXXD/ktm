#ifndef _MAT_COMMON_FWD_H_
#define _MAT_COMMON_FWD_H_

#include <cstddef>

namespace ktm
{
namespace detail
{
namespace mat_common_implement
{
template<size_t N, typename T>
struct trace;

template<size_t Row, size_t Col, typename T>
struct transpose;

template<size_t N, typename T>
struct determinant;

template<size_t N, typename T>
struct inverse;

template<size_t N, typename T>
struct factor_lu;

template<size_t N, typename T>
struct factor_qr;

template<size_t N, typename T>
struct eigen_qr_it;

template<size_t N, typename T>
struct eigen_jacobi_it;

template<size_t N, typename T>
struct factor_svd;
}
}
}

#endif
