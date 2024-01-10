#ifndef _KTM_COMMON_FWD_H_
#define _KTM_COMMON_FWD_H_

#include <cstddef>

namespace ktm
{
namespace detail
{
namespace common_implement
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
struct floor;

template<size_t N, typename T>
struct ceil;

template<size_t N, typename T>
struct round;

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
