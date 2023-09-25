#ifndef _MAT_COMMON_IMPL_H_
#define _MAT_COMMON_IMPL_H_

#include <cstddef>

namespace ktm
{
namespace detail
{
namespace mat_common_implement
{
template<size_t Col, size_t Row, typename T>
struct transpose;

template<size_t Col, size_t Row, typename T>
struct determinant;

template<size_t Col, size_t Row, typename T>
struct inverse;
}
}
}

#include "MatCommonImpl.inl"
#include "MatCommonImplSimd.inl"
#endif
