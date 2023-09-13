#ifndef _BASE_TYPE_H_
#define _BASE_TYPE_H_

#include "Chtholly.h"

namespace ktm
{

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> pi = static_cast<T>(3.141592653589793);

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> zero = static_cast<T>(0);

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> one = static_cast<T>(1);

// 定义vector
template<size_t N, typename T, typename = std::enable_if_t<(N > 0) && std::is_arithmetic_v<T>>> struct vec;

template<typename T>
struct vec_traits;

template<size_t N, typename T>
struct vec_traits<vec<N, T>>
{
    using type = T;
    using self_type = vec<N, T>;
    static constexpr size_t len = N;
};

template<typename T>
using vec_traits_t = typename vec_traits<T>::type;

template<typename T>
using vec_traits_self_t = typename vec_traits<T>::self_type;

template<typename T>
inline constexpr size_t vec_traits_len = vec_traits<T>::len;

// 定义matrix, Col为列的长度, Raw为行的长度
template<size_t Col, size_t Raw, typename T, typename = std::enable_if_t<(Col > 1) && (Raw > 1) && std::is_arithmetic_v<T>>> struct mat;

template<typename T>
struct mat_traits;

template<size_t Col, size_t Raw, typename T>
struct mat_traits<mat<Col, Raw, T>>
{
    using type = T;
    using self_type = mat<Col, Raw, T>;
    using col_type = vec<Col, T>;
    using raw_type = vec<Raw, T>;
    using tp_type = mat<Raw, Col, T>;
    static constexpr size_t col = Col;
    static constexpr size_t raw = Raw;
};

template<typename T>
using mat_traits_t = typename mat_traits<T>::type;

template<typename T>
using mat_traits_self_t = typename mat_traits<T>::self_type;

template<typename T>
using mat_traits_col_t = typename mat_traits<T>::col_type;

template<typename T>
using mat_traits_raw_t = typename mat_traits<T>::raw_type;

template<typename T>
using mat_traits_tp_t = typename mat_traits<T>::tp_type;

template<typename T>
inline constexpr size_t mat_traits_col_n = mat_traits<T>::col;

template<typename T>
inline constexpr size_t mat_traits_raw_n = mat_traits<T>::raw;

}

#endif