#ifndef _TYPE_BASE_H_
#define _TYPE_BASE_H_

#include "Chtholly.h"

namespace ktl::math
{

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
inline constexpr T epsilon = static_cast<T>(0.001);

template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
inline constexpr T pi = static_cast<T>(3.141592653589793);

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
inline constexpr T zero = static_cast<T>(0);

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
inline constexpr T one = static_cast<T>(1);

template<int N, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>> struct vec;
template<int Col, int Raw, typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>> struct mat;

template<typename T>
struct math_traits;

template<int N, typename T>
struct math_traits<vec<N, T>>
{
    
    static constexpr int size = N;
    using type = T;
};

template<int Col, int Raw, typename T>
struct math_traits<mat<Col, Raw, T>>
{
    static constexpr int size = Col * Raw;
    using type = T;

};

template<typename T>
using math_traits_t = typename math_traits<T>::type;

template<typename T>
inline constexpr int math_traits_n = math_traits<T>::size;

}

#endif