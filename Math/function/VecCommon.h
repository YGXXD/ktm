#ifndef _VEC_COMMON_H_
#define _VEC_COMMON_H_

#include "../type/traits.h"
#include "../type/vec.h"
#include "Math/detail/VecCommon/VecCommonFwd.h"

namespace ktm
{

template<size_t StepN, class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V> && (StepN > 0) && (StepN < vec_traits_len<V>), V> elem_move(const V& x) noexcept
{
    return detail::vec_common_implement::elem_move<StepN, vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V>, vec_traits_base_t<V>> reduce_add(const V& x) noexcept
{
    return detail::vec_common_implement::reduce_add<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V>, vec_traits_base_t<V>> reduce_min(const V& x) noexcept
{
    return detail::vec_common_implement::reduce_min<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V>, vec_traits_base_t<V>> reduce_max(const V& x) noexcept
{
    return detail::vec_common_implement::reduce_max<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V>, V> abs(const V& x) noexcept
{
    return detail::vec_common_implement::abs<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V>, V> min(const V& x, const V& y) noexcept
{
    return detail::vec_common_implement::min<vec_traits_len<V>, vec_traits_base_t<V>>::call(x, y);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V>, V> max(const V& x, const V& y) noexcept
{
    return detail::vec_common_implement::max<vec_traits_len<V>, vec_traits_base_t<V>>::call(x, y);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V>, V> clamp(const V& v, const V& min, const V& max) noexcept
{
    return detail::vec_common_implement::clamp<vec_traits_len<V>, vec_traits_base_t<V>>::call(v, min, max);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> floor(const V& x) noexcept
{
    return detail::vec_common_implement::floor<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> ceil(const V& x) noexcept
{
    return detail::vec_common_implement::ceil<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> round(const V& x) noexcept
{
    return detail::vec_common_implement::round<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> lerp(const V& x, const V& y, vec_traits_base_t<V> t) noexcept
{
    return detail::vec_common_implement::lerp<vec_traits_len<V>, vec_traits_base_t<V>>::call(x, y, t);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> mix(const V& x, const V& y, const V& t) noexcept
{
    return detail::vec_common_implement::mix<vec_traits_len<V>, vec_traits_base_t<V>>::call(x, y, t);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> recip(const V& x) noexcept
{
    return detail::vec_common_implement::recip<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
} 

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> step(const V& edge, const V& x) noexcept
{
    return detail::vec_common_implement::step<vec_traits_len<V>, vec_traits_base_t<V>>::call(edge, x);
} 

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> smoothstep(const V& edge0, const V& edge1, const V& x) noexcept
{
    return detail::vec_common_implement::smoothstep<vec_traits_len<V>, vec_traits_base_t<V>>::call(edge0, edge1, x);
}

template<class V>
CHTHOLLY_INLINE std::enable_if_t<is_vector_v<V> && is_floating_point_base_v<V>, V> fract(const V& x) noexcept
{
    return detail::vec_common_implement::fract<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

}   

#include "Math/detail/VecCommon/VecCommon.inl"
#include "Math/detail/VecCommon/VecCommonSimd.inl"

#endif
