#ifndef _VEC_COMMON_IMPL_INL_
#define _VEC_COMMON_IMPL_INL_

#include "VecCommonImpl.h"
#include <Math/MathType/BaseType.h>
#include <Math/MathLib/KMath.h>

template<class V>
struct ktm::detail::vec_common_implement::reduce_add
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE T call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        return (reinterpret_cast<const T*>(&x)[Ns] + ...);
    }
};

template<class V>
struct ktm::detail::vec_common_implement::reduce_min
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE T call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<vec_traits_len<V> - 1>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        if constexpr(sizeof...(Ns))
        {
            T ret = reinterpret_cast<const T*>(&x)[0];
            ((ret = ktm::min<T>(ret, reinterpret_cast<const T*>(&x)[Ns + 1])), ...);
            return ret;
        }
        else
            return *reinterpret_cast<const T*>(&x);
    }
};

template<class V>
struct ktm::detail::vec_common_implement::reduce_max
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE T call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<vec_traits_len<V> - 1>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        if constexpr(sizeof...(Ns))
        {
            T ret = reinterpret_cast<const T*>(&x)[0];
            ((ret = ktm::max<T>(ret, reinterpret_cast<const T*>(&x)[Ns + 1])), ...);
            return ret;
        }
        else
            return *reinterpret_cast<const T*>(&x);
    }
};

template<class V>
struct ktm::detail::vec_common_implement::abs
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(std::is_unsigned_v<T>)
            return x;
        else
            return call(x, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::abs<T>(reinterpret_cast<const T*>(&x)[Ns])), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_common_implement::min
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::min<T>(reinterpret_cast<const T*>(&x)[Ns], reinterpret_cast<const T*>(&y)[Ns])), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_common_implement::max
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::max<T>(reinterpret_cast<const T*>(&x)[Ns], reinterpret_cast<const T*>(&y)[Ns])), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_common_implement::clamp
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        return call(v, min, max, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::clamp<T>(reinterpret_cast<const T*>(&v)[Ns], reinterpret_cast<const T*>(&min)[Ns], reinterpret_cast<const T*>(&max)[Ns])), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_common_implement::lerp
{
    using T = vec_traits_t<V>;
    static_assert(std::is_floating_point_v<T>);
    static CHTHOLLY_INLINE V call(const V& x, const V& y, T t) noexcept
    {
        return call(x, y, t, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, const V& y, T t, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::mix<T>(reinterpret_cast<const T*>(&x)[Ns], reinterpret_cast<const T*>(&y)[Ns], t)), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_common_implement::mix
{
    using T = vec_traits_t<V>;
    static_assert(std::is_floating_point_v<T>);
    static CHTHOLLY_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        return call(x, y, t, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, const V& y, const V& t, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::mix<T>(reinterpret_cast<const T*>(&x)[Ns], reinterpret_cast<const T*>(&y)[Ns], reinterpret_cast<const T*>(&t)[Ns])), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_common_implement::recip
{
    using T = vec_traits_t<V>;
    static_assert(std::is_floating_point_v<T>);
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = one<T> / reinterpret_cast<const T*>(&x)[Ns]), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_common_implement::rsqrt
{
    using T = vec_traits_t<V>;
    static_assert(std::is_floating_point_v<T>);
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::rsqrt<T>(reinterpret_cast<const T*>(&x)[Ns])), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_common_implement::step
{
    using T = vec_traits_t<V>;
    static_assert(std::is_floating_point_v<T>);
    static CHTHOLLY_INLINE V call(const V& edge, const V& x) noexcept
    {
        return call(edge, x, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& edge, const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::step<T>(reinterpret_cast<const T*>(&edge)[Ns], reinterpret_cast<const T*>(&x)[Ns])), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_common_implement::smoothstep
{
    using T = vec_traits_t<V>;
    static_assert(std::is_floating_point_v<T>);
    static CHTHOLLY_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        return call(edge0, edge1, x, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& edge0, const V& edge1, const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::smoothstep<T>(reinterpret_cast<const T*>(&edge0)[Ns], reinterpret_cast<const T*>(&edge1)[Ns], reinterpret_cast<const T*>(&x)[Ns])), ...);
        return ret;
    }
};

#endif