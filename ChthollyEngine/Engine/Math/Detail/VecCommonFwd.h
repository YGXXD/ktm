#ifndef _VEC_COMMON_FWD_H_
#define _VEC_COMMON_FWD_H_

#include <cstddef>

namespace ktm
{
namespace detail
{
namespace vec_common_implement
{

template<size_t StepN, size_t N, typename T>
struct elem_move;

template<size_t N, typename T>
struct reduce_add;

template<size_t N, typename T>
struct reduce_min;

template<size_t N, typename T>
struct reduce_max;

template<size_t N, typename T>
struct abs;

template<size_t N, typename T>
struct min;

template<size_t N, typename T>
struct max;

template<size_t N, typename T>
struct clamp;

template<size_t N, typename T>
struct lerp;

template<size_t N, typename T>
struct mix;

template<size_t N, typename T>
struct recip;

template<size_t N, typename T>
struct step;

template<size_t N, typename T>
struct smoothstep;

template<size_t N, typename T>
struct fract;

}
}
}

#endif
