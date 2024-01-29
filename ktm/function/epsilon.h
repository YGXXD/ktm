#ifndef _KTM_EPSILON_H_
#define _KTM_EPSILON_H_

#include "../setup.h"
#include "../type/basic.h"
#include "../traits/type_traits_math.h"
#include "arithmetic.h"
#include "common.h"

namespace ktm
{

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, bool> equal_zero(T x, T e = std::numeric_limits<T>::epsilon()) noexcept
{
    return abs(x) < e;
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, bool> equal(T x, T y, T e = std::numeric_limits<T>::epsilon()) noexcept
{
    return equal_zero(x - y, e);
}

template<typename V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, bool> equal_zero(V x, vec_traits_base_t<V> e = std::numeric_limits<vec_traits_base_t<V>>::epsilon()) noexcept
{
    return reduce_max(abs(x)) < e;
}

template<typename V>
KTM_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, bool> equal(V x, V y, vec_traits_base_t<V> e = std::numeric_limits<vec_traits_base_t<V>>::epsilon()) noexcept
{
    return equal_zero(x - y, e);
}

}
#endif