#ifndef _VEC_OPT_IMPL_INL_
#define _VEC_OPT_IMPL_INL_

#include "VecOptImpl.h"
#include "Math/MathType/BaseType.h"

template<class V>
struct ktm::detail::vec_opt_implement::add
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
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] + reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::add_to_self
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] += reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::minus
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
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] - reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::minus_to_self
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] -= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::mul
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
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] * reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::mul_to_self
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] *= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::div
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
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] / reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::div_to_self
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] /= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::opposite
{
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
        ((reinterpret_cast<T*>(&ret)[Ns] = -reinterpret_cast<const T*>(&x)[Ns]), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::add_scalar
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] + scalar), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::add_scalar_to_self
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V& call(V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] += scalar), ...);
        return x; 
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::minus_scalar
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] - scalar), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V& call(V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] -= scalar), ...);
        return x; 
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::mul_scalar
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] * scalar), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V& call(V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] *= scalar), ...);
        return x; 
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::div_scalar
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {   
        if constexpr(std::is_floating_point_v<T>)
            return mul_scalar<V>::call(x, one<T> / scalar);
        else 
            return call(x, scalar, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] / scalar), ...);
        return ret;
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::div_scalar_to_self
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE V& call(V& x, T scalar) noexcept
    {
        if constexpr(std::is_floating_point_v<T>)
            return mul_scalar_to_self<V>::call(x, one<T> / scalar);
        else 
            return call(x, scalar, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] /= scalar), ...);
        return x; 
    }
};

template<class V>
struct ktm::detail::vec_opt_implement::equal
{
    using T = vec_traits_t<V>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<vec_traits_len<V>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE bool call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        return ((reinterpret_cast<const T*>(&x)[Ns] == reinterpret_cast<const T*>(&y)[Ns]) && ...);
    }
};

#endif