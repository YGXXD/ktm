#ifndef _KTM_TRAITS_H_
#define _KTM_TRAITS_H_

#include "basic.h"

namespace ktm
{

// vec traits
template<typename T>
struct vec_traits;

template<size_t N, typename T>
struct vec_traits<vec<N, T>>
{
    using base_type = T;
    static constexpr size_t len = N;
};

template<typename T>
using vec_traits_base_t = typename vec_traits<T>::base_type;

template<typename T>
inline constexpr size_t vec_traits_len = vec_traits<T>::len;

// mat traits
template<typename T>
struct mat_traits;

template<size_t Row, size_t Col, typename T>
struct mat_traits<mat<Row, Col, T>>
{
    using base_type = T;
    using tp_type = mat<Col, Row, T>;
    using col_type = vec<Col, T>;
    using row_type = vec<Row, T>;
    static constexpr size_t col = Col;
    static constexpr size_t row = Row;
};

template<typename T>
using mat_traits_base_t = typename mat_traits<T>::base_type;

template<typename T>
using mat_traits_tp_t = typename mat_traits<T>::tp_type;

template<typename T>
using mat_traits_col_t = typename mat_traits<T>::col_type;

template<typename T>
using mat_traits_row_t = typename mat_traits<T>::row_type;

template<typename T>
inline constexpr size_t mat_traits_col_n = mat_traits<T>::col;

template<typename T>
inline constexpr size_t mat_traits_row_n = mat_traits<T>::row;

// quat traits
template<typename T>
struct quat_traits;

template<typename T>
struct quat_traits<quat<T>>
{
    using base_type = T;
    using storage_type = vec<4, T>;
};

template<typename T>
using quat_traits_base_t = typename quat_traits<T>::base_type;

template<typename T>
using quat_traits_storage_t = typename quat_traits<T>::storage_type;

// 数学库类型特性
template<typename T>
struct is_vector : std::false_type { };

template<size_t N, typename T>
struct is_vector<vec<N, T>> : std::true_type{ };

template<typename T>
struct is_matrix : std::false_type { };

template<size_t Row, size_t Col, typename T>
struct is_matrix<mat<Row, Col, T>> : std::true_type { };

template<typename T>
struct is_square_matrix : std::false_type { };

template<size_t N, typename T>
struct is_square_matrix<mat<N, N, T>> : std::true_type { };

template<typename T>
struct is_quaternion : std::false_type { };

template<typename T>
struct is_quaternion<quat<T>> : std::true_type { };

template<typename T>
struct is_floating_point_base : std::false_type { };

template<size_t N, typename T>
struct is_floating_point_base<vec<N, T>> : std::is_floating_point<T> { };

template<size_t Row, size_t Col, typename T>
struct is_floating_point_base<mat<Row, Col, T>> : std::is_floating_point<T> { };

template<typename T>
struct is_floating_point_base<quat<T>> : std::true_type { };

template<typename T>
inline constexpr bool is_vector_v = is_vector<T>::value;

template<typename T>
inline constexpr bool is_matrix_v = is_matrix<T>::value;

template<typename T>
inline constexpr bool is_square_matrix_v = is_square_matrix<T>::value;

template<typename T>
inline constexpr bool is_quaternion_v = is_quaternion<T>::value;

template<typename T>
inline constexpr bool is_floating_point_base_v = is_floating_point_base<T>::value;
}

#endif