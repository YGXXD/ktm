#ifndef _KTM_GEOMETRIC_H_
#define _KTM_GEOMETRIC_H_

#include "../setup.h"
#include "../traits/type_traits_math.h"
#include "../type/vec.h"
#include "common.h"

namespace ktm
{
template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, vec_traits_base_t<V>> dot(const V& x, const V& y) noexcept
{ 
    return reduce_add(x * y); 
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> project(const V& x, const V& y) noexcept
{
    return dot(x, y) / dot(y, y) * y; 
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, vec<3, T>> cross(const vec<3, T>& x, const vec<3, T>& y) noexcept
{
    return { x[1] * y[2] - x[2] * y[1], x[2] * y[0] - x[0] * y[2], x[0] * y[1] - x[1] * y[0] };
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, vec<3, T>> cross(const vec<2, T>& x, const vec<2, T>& y) noexcept
{
    return { zero<T>, zero<T>, x[0] * y[1] - x[1] * y[0] };
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, vec_traits_base_t<V>> length_squared(const V& x) noexcept
{ 
    return dot(x, x);
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, vec_traits_base_t<V>> length(const V& x) noexcept
{
    return sqrt(length_squared(x));
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, vec_traits_base_t<V>> distance(const V& x, const V& y) noexcept
{
    return length(y - x);
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> normalize(const V& x) noexcept
{
    return rsqrt(length_squared(x)) * x;
}

template<class V>
KTM_INLINE std::enable_if_t<std::is_exist_same_vs<float, double, vec_traits_base_t<V>>, V> fast_normalize(const V& x) noexcept
{
    return fast_rsqrt(length_squared(x)) * x;
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> reflect(const V& x, const V& n) noexcept
{
    return x - 2 * dot(x, n) * n;
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> refract(const V& x, const V& n, vec_traits_base_t<V> eta) noexcept
{
    using value_type = vec_traits_base_t<V>;
    const value_type k = one<value_type> - eta * eta * (one<value_type> - dot(x, n) * dot(x, n));
    return k >= zero<value_type> ? eta * x - (eta * dot(x, n) + sqrt(k)) * n : V();
}
}

#endif