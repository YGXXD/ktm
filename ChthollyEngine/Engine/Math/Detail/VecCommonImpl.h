#ifndef _VEC_COMMON_IMPL_H_
#define _VEC_COMMON_IMPL_H_

namespace ktm
{
namespace detail
{
namespace vec_common_implement
{
template<class V>
struct reduce_add;

template<class V>
struct reduce_min;

template<class V>
struct reduce_max;

template<class V>
struct abs;

template<class V>
struct min;

template<class V>
struct max;

template<class V>
struct clamp;
}
}
}

#include "VecCommonImpl.inl"
#endif