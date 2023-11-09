#ifndef _VEC_COMMON_H_
#define _VEC_COMMON_H_

#include "Vector.h"
#include "Math/Detail/VecCommonFwd.h"

namespace ktm
{

template<size_t StepN, class V>
CHTHOLLY_INLINE std::enable_if_t<(StepN > 0 && StepN < vec_traits_len<V>), V> elem_move(const V& x) noexcept
{
    return detail::vec_common_implement::elem_move<StepN, vec_traits_len<V>, vec_traits_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE vec_traits_t<V> reduce_add(const V& x) noexcept
{
    return detail::vec_common_implement::reduce_add<vec_traits_len<V>, vec_traits_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE vec_traits_t<V> reduce_min(const V& x) noexcept
{
    return detail::vec_common_implement::reduce_min<vec_traits_len<V>, vec_traits_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE vec_traits_t<V> reduce_max(const V& x) noexcept
{
    return detail::vec_common_implement::reduce_max<vec_traits_len<V>, vec_traits_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE vec_traits_self_t<V> abs(const V& x) noexcept
{
    return detail::vec_common_implement::abs<vec_traits_len<V>, vec_traits_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE vec_traits_self_t<V> min(const V& x, const V& y) noexcept
{
    return detail::vec_common_implement::min<vec_traits_len<V>, vec_traits_t<V>>::call(x, y);
}

template<class V>
CHTHOLLY_INLINE vec_traits_self_t<V> max(const V& x, const V& y) noexcept
{
    return detail::vec_common_implement::max<vec_traits_len<V>, vec_traits_t<V>>::call(x, y);
}

template<class V>
CHTHOLLY_INLINE vec_traits_self_t<V> clamp(const V& v, const V& min, const V& max) noexcept
{
    return detail::vec_common_implement::clamp<vec_traits_len<V>, vec_traits_t<V>>::call(v, min, max);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, V> lerp(const V& x, const V& y, vec_traits_t<V> t) noexcept
{
    return detail::vec_common_implement::lerp<vec_traits_len<V>, vec_traits_t<V>>::call(x, y, t);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, V> mix(const V& x, const V& y, const V& t) noexcept
{
    return detail::vec_common_implement::mix<vec_traits_len<V>, vec_traits_t<V>>::call(x, y, t);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, V> recip(const V& x) noexcept
{
    return detail::vec_common_implement::recip<vec_traits_len<V>, vec_traits_t<V>>::call(x);
} 

template<class V>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, V> step(const V& edge, const V& x) noexcept
{
    return detail::vec_common_implement::step<vec_traits_len<V>, vec_traits_t<V>>::call(edge, x);
} 

template<class V>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, V> smoothstep(const V& edge0, const V& edge1, const V& x) noexcept
{
    return detail::vec_common_implement::smoothstep<vec_traits_len<V>, vec_traits_t<V>>::call(edge0, edge1, x);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, V> fract(const V& x) noexcept
{
    return detail::vec_common_implement::fract<vec_traits_len<V>, vec_traits_t<V>>::call(x);
}

}   

#include "Math/Detail/VecCommon.inl"
#include "Math/Detail/VecCommonSimd.inl"

#endif
