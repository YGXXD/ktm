//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_VECTOR_EXPONENTIAL_INL_
#define _KTM_VECTOR_EXPONENTIAL_INL_

#include "vector_exponential_fwd.h"
#include "../loop_util.h"
#include "../../type/vec_fwd.h"
#include "../../function/exponential.h"

template<size_t N, typename T, typename Void>
struct ktm::detail::vector_exponential_implement::sqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::sqrt<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vector_exponential_implement::rsqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::rsqrt<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vector_exponential_implement::recip
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::recip<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vector_exponential_implement::fast_sqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::fast::sqrt<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vector_exponential_implement::fast_rsqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::fast::rsqrt<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vector_exponential_implement::fast_recip
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::fast::recip<T>, x);
        return ret;
    }
};

#endif