//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_COMMON_INL_
#define _KTM_COMMON_INL_

#include "common_fwd.h"
#include "../loop_util.h"
#include "../../type/vec_fwd.h"
#include "../../function/arithmetic.h"
#include "../../function/exponential.h"

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::reduce_add
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        T ret;
        loop_reduce<N>(ret, x, x[0], std::plus<T>());
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::reduce_min
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        T ret;
        loop_reduce<N>(ret, x, x[0], ktm::min<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::reduce_max
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        T ret;
        loop_reduce<N>(ret, x, x[0], ktm::max<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::abs
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::abs<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::min
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        loop_op<N>(ret, x, y, ktm::min<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::max
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        loop_op<N>(ret, x, y, ktm::max<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::clamp
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        loop_op<N>(ret, v, min, max, ktm::clamp<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::floor
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::floor<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::ceil
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::ceil<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::round
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::round<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fract
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::fract<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::mod
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        loop_op<N>(ret, x, y, ktm::mod<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::lerp
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y, T t) noexcept
    {
        V ret;
        loop_scalar<N>(ret, x, y, t, ktm::lerp<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::mix
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        V ret;
        loop_op<N>(ret, x, y, t, ktm::lerp<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::step
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& edge, const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, edge, x, ktm::step<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::smoothstep
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, edge0, edge1, x, ktm::smoothstep<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::sqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::sqrt<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::rsqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::rsqrt<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::recip
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::recip<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fast_sqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::fast::sqrt<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fast_rsqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::fast::rsqrt<T>);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fast_recip
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, ktm::fast::recip<T>);
        return ret;
    }
};

#endif
