#ifndef _MAT_OPT_FWD_H_ 
#define _MAT_OPT_FWD_H_

#include <cstddef>

namespace ktm
{
namespace detail
{
namespace mat_opt_implement
{
template<size_t Row, size_t Col, typename T>
struct mat_mul_vec;

template<size_t Row, size_t Col, typename T>
struct vec_mul_mat;

template<size_t Row, size_t Col, typename T>
struct mat_mul_mat;

template<size_t Row, size_t Col, typename T>
struct add;

template<size_t Row, size_t Col, typename T>
struct minus;

template<size_t Row, size_t Col, typename T>
struct equal;

}
}
}

#endif
