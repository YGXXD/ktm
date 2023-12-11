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
    using T = quat_traits_base_t<Q>;
    return Q(q.vector * quat_traits_storage_t<Q>(one<T>, -one<T>, -one<T>, -one<T>));
}

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, Q> inverse(const Q& q) noexcept
{
    using T = quat_traits_base_t<Q>;
    return Q(conjugate(q).vector * (one<T> / (length_squared(q.vector))));
}

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, Q> negate(const Q& q) noexcept
{
    return Q(-q.vector);
}

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, quat_traits_base_t<Q>> dot(const Q& p, const Q& q) noexcept
{
    return dot(p.vector, q.vector);
}

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, quat_traits_base_t<Q>> length(const Q& q) noexcept
{
    return length(q.vector);
}

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, Q> normalize(const Q& q) noexcept
{
    using T = quat_traits_base_t<Q>;
    T length_squared = dot(q.vector, q.vector);
    if(equal_zero(length_squared)) {
        return Q(one<T>, zero<T>, zero<T>, zero<T>);
    }
    return Q(q.vector * rsqrt(length_squared));
}

// template<class Q>
// CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, vec<3, quat_traits_base_t<Q>>> act(const Q& q, const vec<3, quat_traits_base_t<Q>>& v) noexcept
// {
//     using T = quat_traits_base_t<Q>;
//     vec<3, quat_traits_base_t<Q>> t = static_cast<T>(2) * cross(q.imag(), v);
//     return v + (q.real() * t) + cross(q.imag(), t);
// }

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, Q> slerp_internal(const Q& x, const Q& y, quat_traits_base_t<Q> t)
{
    using T = quat_traits_base_t<Q>;
    T s = one<T> - t;
    T a = static_cast<T>(2) * atan2(length(x.vector - x.vector), length(x.vector + x.vector));// angel
    T r = one<T> / sinc(a);
    return normalize(Q(sinc(s * a) * r * s * x.vector + sinc(t * a) * r * t * y.vector));
}

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, Q> slerp(const Q& x, const Q& y, quat_traits_base_t<Q> t)
{
    if (dot(x, y) >= 0)
        return slerp_internal(x, y, t);
    return slerp_internal(x, negate(y), t);
}

template<class Q>
CHTHOLLY_INLINE std::enable_if_t<is_quaternion_v<Q>, Q> slerp_longest(const Q& x, const Q& y, quat_traits_base_t<Q> t)
{
    if (dot(x, y) >= 0)
        return slerp_internal(x, negate(y), t);
    return slerp_internal(x, y, t);
}


}

#endif