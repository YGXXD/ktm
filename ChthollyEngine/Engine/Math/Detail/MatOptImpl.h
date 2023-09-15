#ifndef _MAT_OPT_IMPL_H_
#define _MAT_OPT_IMPL_H_

namespace ktm
{
namespace detail
{
namespace mat_opt_implement
{
template<class M>
struct mat_mul_vec;

template<class M>
struct vec_mul_mat;

template<class M>
struct mat_mul_mat;

template<class M>
struct add;

template<class M>
struct minus;

template<class M>
struct equal;

}
}
}

#include "MatOptImpl.inl"
#include "MatOptImplSimd.inl"
#endif