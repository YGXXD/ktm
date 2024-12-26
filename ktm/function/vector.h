//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_VECTOR_H_
#define _KTM_VECTOR_H_

#include "../setup.h"
#include "../type/vec.h"
#include "../traits/type_traits_math.h"
#include "../detail/function/vector_fwd.h"

namespace ktm
{

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V>, vec_traits_base_t<V>> reduce_add(const V& x) noexcept
{
    return detail::vector_implement::reduce_add<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V>, vec_traits_base_t<V>> reduce_min(const V& x) noexcept
{
    return detail::vector_implement::reduce_min<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

template<class V>
KTM_INLINE std::enable_if_t<is_vector_v<V>, vec_traits_base_t<V>> reduce_max(const V& x) noexcept
{
    return detail::vector_implement::reduce_max<vec_traits_len<V>, vec_traits_base_t<V>>::call(x);
}

}

#include "../detail/function/vector.inl"
#include "../detail/function/vector_simd.inl"

#endif