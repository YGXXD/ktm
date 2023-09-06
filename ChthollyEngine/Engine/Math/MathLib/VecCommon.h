#ifndef _VEC_COMMON_H_
#define _VEC_COMMON_H_

#include "Math/MathType/VecType.h"
#include "Math/Detail/VecCommonImpl.h"

namespace ktm
{

    template<class V>
    static CHTHOLLY_INLINE vec_traits_t<V> reduce_add(const V& x)
    {
        return detail::vec_common_implement::reduce_add<V>::call(x);
    }

    template<class V>
    static CHTHOLLY_INLINE vec_traits_t<V> reduce_min(const V& x)
    {
        return detail::vec_common_implement::reduce_min<V>::call(x);
    }

    template<class V>
    static CHTHOLLY_INLINE vec_traits_t<V> reduce_max(const V& x)
    {
        return detail::vec_common_implement::reduce_max<V>::call(x);
    }

    template<class V>
    static CHTHOLLY_INLINE vec_traits_self_t<V> abs(const V& x)
    {
        return detail::vec_common_implement::abs<V>::call(x);
    }

    template<class V>
    static CHTHOLLY_INLINE vec_traits_self_t<V> min(const V& x, const V& y)
    {
        return detail::vec_common_implement::min<V>::call(x, y);
    }

    template<class V>
    static CHTHOLLY_INLINE vec_traits_self_t<V> max(const V& x, const V& y)
    {
        return detail::vec_common_implement::max<V>::call(x, y);
    }

    template<class V>
    static CHTHOLLY_INLINE vec_traits_self_t<V> clamp(const V& min, const V& max, const V& v)
    {
        return detail::vec_common_implement::clamp<V>::call(min, max, v);
    }
}   

#endif