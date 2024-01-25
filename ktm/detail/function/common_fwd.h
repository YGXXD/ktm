#ifndef _KTM_COMMON_FWD_H_
#define _KTM_COMMON_FWD_H_

#include <cstddef>
#include <type_traits>

namespace ktm
{
namespace detail
{
namespace common_implement
{

template<size_t StepN, size_t N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T> && (StepN > 0 && StepN < N)>>
struct elem_move;

template<size_t N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct reduce_add;

template<size_t N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct reduce_min;

template<size_t N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct reduce_max;

template<size_t N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct abs;

template<size_t N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct min;

template<size_t N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct max;

template<size_t N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct clamp;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct floor;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct ceil;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct round;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct lerp;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct mix;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct recip;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct step;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct smoothstep;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct fract;

}
}
}

#endif