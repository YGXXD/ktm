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

// 定义vector
template<size_t N, typename T, typename = std::enable_if_t<(N > 0) && std::is_arithmetic_v<T>>> struct vec;

template<typename T>
struct vec_traits;

template<size_t N, typename T>
struct vec_traits<vec<N, T>>
{
    static constexpr size_t len = N;
    using type = T;
};

template<typename T>
using vec_traits_t = typename vec_traits<T>::type;

template<typename T>
inline constexpr size_t vec_traits_len = vec_traits<T>::len;

// 定义matrix
template<size_t Col, size_t Raw, typename T, typename = std::enable_if_t<(Col > 0) && (Raw > 0) && std::is_arithmetic_v<T>>> struct mat;

template<typename T>
struct mat_traits;

template<size_t Col, size_t Raw, typename T>
struct mat_traits<mat<Col, Raw, T>>
{
    static constexpr size_t col = Col;
    static constexpr size_t raw = Raw;
    using type = T;
};

template<typename T>
using mat_traits_t = typename mat_traits<T>::type;

template<typename T>
inline constexpr size_t mat_traits_col = mat_traits<T>::col;

template<typename T>
inline constexpr size_t mat_traits_raw = mat_traits<T>::raw;

}

#endif