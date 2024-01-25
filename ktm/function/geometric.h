#ifndef _KTM_GEOMETRIC_H_
#define _KTM_GEOMETRIC_H_

#include "../setup.h"
#include "../traits/type_traits_math.h"
#include "../type/vec.h"
#include "../detail/function/geometric_fwd.h"

namespace ktm
{
template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, vec_traits_base_t<V>> dot(const V& x, const V& y) noexcept
{ 
    return detail::geometric_implement::dot<vec_traits_len<V>, vec_traits_base_t<V>>::call(x, y);
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> project(const V& x, const V& y) noexcept
{
    return detail::geometric_implement::project<vec_traits_len<V>, vec_traits_base_t<V>>::call(x, y);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, vec<3, T>> cross(const vec<3, T>& x, const vec<3, T>& y) noexcept
{
    return detail::geometric_implement::cross<3, T>::call(x, y);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, vec<3, T>> cross(const vec<2, T>& x, const vec<2, T>& y) noexcept
{
    return detail::geometric_implement::cross<2, T>::call(x, y);
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, vec_traits_base_t<V>> length(const V& x) noexcept
{
    return detail::geometric_implement::length<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, vec_traits_base_t<V>> distance(const V& x, const V& y) noexcept
{
    return detail::geometric_implement::distance<vec_traits_len<V>, vec_traits_base_t<V>>::call(x, y);
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> normalize(const V& x) noexcept
{
    return detail::geometric_implement::normalize<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> reflect(const V& x, const V& n) noexcept
{
    return detail::geometric_implement::reflect<vec_traits_len<V>, vec_traits_base_t<V>>::call(x, n);
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> refract(const V& x, const V& n, vec_traits_base_t<V> eta) noexcept
{
    return detail::geometric_implement::refract<vec_traits_len<V>, vec_traits_base_t<V>>::call(x, n, eta);
}
}

#include "../detail/function/geometric.inl"

#endif