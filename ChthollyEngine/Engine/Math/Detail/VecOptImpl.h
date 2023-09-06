#ifndef _VEC_OPT_IMPL_H_
#define _VEC_OPT_IMPL_H_

namespace ktm
{
namespace detail
{
namespace vec_opt_implement
{
template<class V>
struct add;

template<class V>
struct add_to_self;

template<class V>
struct minus;

template<class V>
struct minus_to_self; 

template<class V>
struct mul;

template<class V>
struct mul_to_self;

template<class V>
struct div;

template<class V>
struct div_to_self; 

template<class V>
struct opposite;

template<class V>
struct add_scalar;

template<class V>
struct add_scalar_to_self;  

template<class V>
struct minus_scalar;

template<class V>
struct minus_scalar_to_self;  

template<class V>
struct mul_scalar;

template<class V>
struct mul_scalar_to_self;  

template<class V>
struct div_scalar;

template<class V>
struct div_scalar_to_self;

}
}
}

#include "VecOptImpl.inl"
#include "VecOptImplSimd.inl"
#endif