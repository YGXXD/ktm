#ifndef _BASE_TYPE_H_
#define _BASE_TYPE_H_

#include "Chtholly.h"

namespace ktm
{

template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
inline constexpr T pi = static_cast<T>(3.141592653589793);

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
inline constexpr T zero = static_cast<T>(0);

template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
inline constexpr T one = static_cast<T>(1);

template<size_t N, typename T, typename = std::enable_if_t<(N > 0) && std::is_arithmetic_v<T>>> struct vec;
template<size_t Col, size_t Raw, typename T, typename = std::enable_if_t<(Col > 0) && (Raw > 0) && std::is_arithmetic_v<T>>> struct mat;

template<typename T>
struct math_traits;

template<size_t N, typename T>
struct math_traits<vec<N, T>>
{
    static constexpr size_t len = N;
    using type = T;
};

template<size_t Col, size_t Raw, typename T>
struct math_traits<mat<Col, Raw, T>>
{
    static constexpr size_t col = Col;
    static constexpr size_t raw = Raw;
    using type = T;
};

template<typename T>
using math_traits_t = typename math_traits<T>::type;

template<typename T>
inline constexpr size_t vec_traits_len = math_traits<T>::len;

template<typename T>
inline constexpr size_t mat_traits_col = math_traits<T>::col;

template<typename T>
inline constexpr size_t mat_traits_raw = math_traits<T>::raw;

}

#endif