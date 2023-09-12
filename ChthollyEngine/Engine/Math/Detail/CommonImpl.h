#ifndef _COMMON_IMPL_H_
#define _COMMON_IMPL_H_

namespace ktm
{
namespace detail
{
namespace common_implement
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

template<class V>
struct lerp;

template<class V>
struct mix;

template<class V>
struct recip;

template<class V>
struct rsqrt;

template<class V>
struct step;

template<class V>
struct smoothstep;

template<class V>
struct fract;

}
}
}

#include "CommonImpl.inl"
#endif