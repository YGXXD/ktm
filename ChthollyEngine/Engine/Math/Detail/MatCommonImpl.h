#ifndef _MAT_COMMON_IMPL_H_
#define _MAT_COMMON_IMPL_H_

namespace ktm
{
namespace detail
{
namespace mat_common_implement
{
template<class M>
struct transpose;

template<class M>
struct determinant;

}
}
}

#include "MatCommonImpl.inl"
#include "MatCommonImplSimd.inl"
#endif