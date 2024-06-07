//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_COMMON_INL_
#define _KTM_COMMON_INL_

#include <utility>
#include "common_fwd.h"
#include "../../setup.h"
#include "../../type/vec_fwd.h"
#include "../../function/arithmetic.h"
#include "../../function/exponential.h"

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::reduce_add
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            T ret = zero<T>;
            for(int i = 0; i < N; ++i)
                ret += x[i];
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        return (x[Ns] + ...);
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::reduce_min
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N - 1>());
        else
        {
            T ret = x[0];
            for(int i = 0; i < N - 1; ++i)
                ret = ktm::min(ret, x[i + 1]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        T ret = x[0];
        ((ret = ktm::min(ret, x[Ns + 1])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::reduce_max
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N - 1>());
        else
        {
            T ret = x[0];
            for(int i = 0; i < N - 1; ++i)
                ret = ktm::max(ret, x[i + 1]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        T ret = x[0];
        ((ret = ktm::max(ret, x[Ns + 1])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::abs
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::abs(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::abs(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::min
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N <= 4)
            return call(x, y, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::min(x[i], y[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::min(x[Ns], y[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::max
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N <= 4)
            return call(x, y, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::max(x[i], y[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::max(x[Ns], y[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::clamp
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        if constexpr(N <= 4)
            return call(v, min, max, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::clamp(v[i], min[i], max[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& v, const V& min, const V& max, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::clamp(v[Ns], min[Ns], max[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::floor
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::floor(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::floor(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::ceil
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::ceil(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::ceil(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::round
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::round(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::round(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fract
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::fract(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::fract(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::mod
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N <= 4)
            return call(x, y, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::mod(x[i], y[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::mod(x[Ns], y[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::lerp
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y, T t) noexcept
    {
        if constexpr(N <= 4)
            return call(x, y, t, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::lerp(x[i], y[i], t);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, const V& y, T t, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::lerp(x[Ns], y[Ns], t)), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::mix
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        if constexpr(N <= 4)
            return call(x, y, t, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::lerp(x[i], y[i], t[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, const V& y, const V& t, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::lerp(x[Ns], y[Ns], t[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::step
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& edge, const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(edge, x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::step(edge[i], x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& edge, const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::step(edge[Ns], x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::smoothstep
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(edge0, edge1, x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::smoothstep(edge0[i], edge1[i], x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::smoothstep(edge0[Ns], edge1[Ns], x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::sqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::sqrt(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::sqrt(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::rsqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::rsqrt(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::rsqrt(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::recip
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::recip(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::recip(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fast_sqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::fast::sqrt(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::fast::sqrt(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fast_rsqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::fast::rsqrt(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::fast::rsqrt(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fast_recip
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(N <= 4)
            return call(x, std::make_index_sequence<N>());
        else
        {
            V ret;
            for(int i = 0; i < N; ++i)
                ret[i] = ktm::fast::recip(x[i]);
            return ret;
        }
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::fast::recip(x[Ns])), ...);
        return ret;
    }
};

#endif
