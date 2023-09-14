#ifndef _VEC_COMMON_IMPL_INL_
#define _VEC_COMMON_IMPL_INL_

#include "VecCommonImpl.h"
#include "Math/MathLib/Common.h"

template<size_t N, class V>
struct ktm::detail::vec_common_implement::elem_move
{
    static_assert(N > 0 && N < vec_traits_len<V>);
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[(Ns + N) < vec_traits_len<V> ? Ns + N : Ns + N - vec_traits_len<V>]), ...);
        return ret;
    }
};

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
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::abs(reinterpret_cast<const T*>(&x)[Ns])), ...);
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
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::min(reinterpret_cast<const T*>(&x)[Ns], reinterpret_cast<const T*>(&y)[Ns])), ...);
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
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::max(reinterpret_cast<const T*>(&x)[Ns], reinterpret_cast<const T*>(&y)[Ns])), ...);
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
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::clamp(reinterpret_cast<const T*>(&v)[Ns], reinterpret_cast<const T*>(&min)[Ns], reinterpret_cast<const T*>(&max)[Ns])), ...);
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
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::mix(reinterpret_cast<const T*>(&x)[Ns], reinterpret_cast<const T*>(&y)[Ns], t)), ...);
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
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::mix(reinterpret_cast<const T*>(&x)[Ns], reinterpret_cast<const T*>(&y)[Ns], reinterpret_cast<const T*>(&t)[Ns])), ...);
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
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::step(reinterpret_cast<const T*>(&edge)[Ns], reinterpret_cast<const T*>(&x)[Ns])), ...);
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
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::smoothstep(reinterpret_cast<const T*>(&edge0)[Ns], reinterpret_cast<const T*>(&edge1)[Ns], reinterpret_cast<const T*>(&x)[Ns])), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_common_implement::fract
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
        ((reinterpret_cast<T*>(&ret)[Ns] = ktm::fract(reinterpret_cast<const T*>(&x)[Ns])), ...);
        return ret;
    }
};

#endif