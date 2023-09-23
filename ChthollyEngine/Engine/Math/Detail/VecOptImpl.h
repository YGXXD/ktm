#ifndef _VEC_OPT_IMPL_H_
#define _VEC_OPT_IMPL_H_

#include <cstddef>

namespace ktm
{
namespace detail
{
namespace vec_opt_implement
{
template<size_t N, typename T>
struct add;

template<size_t N, typename T>
struct add_to_self;

template<size_t N, typename T>
struct minus;

template<size_t N, typename T>
struct minus_to_self; 

template<size_t N, typename T>
struct mul;

template<size_t N, typename T>
struct mul_to_self;

template<size_t N, typename T>
struct div;

template<size_t N, typename T>
struct div_to_self; 

template<size_t N, typename T>
struct opposite;

template<size_t N, typename T>
struct add_scalar;

template<size_t N, typename T>
struct add_scalar_to_self;  

template<size_t N, typename T>
struct minus_scalar;

template<size_t N, typename T>
struct minus_scalar_to_self;  

template<size_t N, typename T>
struct mul_scalar;

template<size_t N, typename T>
struct mul_scalar_to_self;  

template<size_t N, typename T>
struct div_scalar;

template<size_t N, typename T>
struct div_scalar_to_self;

template<size_t N, typename T>
struct equal;

}
}
}

#include "VecOptImpl.inl"
#include "VecOptImplSimd.inl"
#endif
