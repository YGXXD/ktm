#ifndef _QUAT_COMMON_H_
#define _QUAT_COMMON_H_

#include "Quaternion.h"
#include "Common.h"
#include "Geometry.h"

namespace ktm
{
template<class Q>
CHTHOLLY_INLINE quat_traits_selt_t<Q> conjugate(const Q& q) noexcept
{
    using T = quat_traits_t<Q>;
    return Q(q.vector * quat_traits_storage_t<Q>(one<T>, -one<T>, -one<T>, -one<T>));
}

template<class Q>
CHTHOLLY_INLINE quat_traits_selt_t<Q> inverse(const Q& q) noexcept
{
    using T = quat_traits_t<Q>;
    return Q(conjugate(q).vector * (one<T> / (length_squared(q.vector))));
}

template<class Q>
CHTHOLLY_INLINE quat_traits_selt_t<Q> negate(const Q& q) noexcept
{
    return Q(-q.vector);
}

}

#endif