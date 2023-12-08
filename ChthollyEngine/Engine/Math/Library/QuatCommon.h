#ifndef _QUAT_COMMON_H_
#define _QUAT_COMMON_H_

#include "Quaternion.h"
#include "Common.h"
#include "Geometry.h"

namespace ktm
{
template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, Q> conjugate(const Q& q) noexcept
{
    using T = quat_traits_t<Q>;
    return Q(q.vector * quat_traits_storage_t<Q>(one<T>, -one<T>, -one<T>, -one<T>));
}

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, Q> inverse(const Q& q) noexcept
{
    using T = quat_traits_t<Q>;
    return Q(conjugate(q).vector * (one<T> / (length_squared(q.vector))));
}

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, Q> negate(const Q& q) noexcept
{
    return Q(-q.vector);
}

template<class Q>
CHTHOLLY_INLINE quat_traits_t<Q> dot(const Q& p, const Q& q) noexcept
{
    return dot(p.vector, q.vector);
}

template<class Q>
CHTHOLLY_INLINE quat_traits_t<Q> length(const Q& q) noexcept
{
    return length(q.vector);
}

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, Q> normalize(const Q& q) noexcept
{
    using T = quat_traits_t<Q>;
    T length_squared = dot(q.vector, q.vector);
    if(equal_zero(length_squared)) {
        return Q(one<T>, zero<T>, zero<T>, zero<T>);
    }
    return Q(q.vector * rsqrt(length_squared));
}

}

#endif