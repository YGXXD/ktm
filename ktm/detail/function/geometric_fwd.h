#ifndef _KTM_GEOMETRIC_FWD_H_
#define _KTM_GEOMETRIC_FWD_H_

#include <cstddef>
#include <type_traits>

namespace ktm 
{
namespace detail
{
namespace geometric_implement
{
template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct dot;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct project;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T> && (N == 2 || N == 3)>>
struct cross;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct length;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct distance;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct normalize;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct reflect;

template<size_t N, typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
struct refract;
}
}
}

#endif