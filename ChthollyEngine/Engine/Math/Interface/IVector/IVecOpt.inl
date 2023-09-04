#ifndef _I_VEC_OPT_INL_
#define _I_VEC_OPT_INL_

#include "IVecOpt.h"

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::add<N, T, V>
{
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
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

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::add_to_self<N, T, V>
{
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] += reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::minus<N, T, V>
{
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
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

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::minus_to_self<N, T, V>
{
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] -= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::mul<N, T, V>
{
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
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

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::mul_to_self<N, T, V>
{
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] *= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::div<N, T, V>
{
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
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

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::div_to_self<N, T, V>
{
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] /= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::opposite<N, T, V>
{
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N>());
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

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::add_scalar<N, T, V>
{
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<N>());
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

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<N, T, V>
{
    static CHTHOLLY_INLINE V& call(V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] += scalar), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::minus_scalar<N, T, V>
{
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<N>());
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

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<N, T, V>
{
    static CHTHOLLY_INLINE V& call(V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] -= scalar), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::mul_scalar<N, T, V>
{
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<N>());
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

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<N, T, V>
{
    static CHTHOLLY_INLINE V& call(V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] *= scalar), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::div_scalar<N, T, V>
{
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {   
        if constexpr(std::is_floating_point_v<T>)
            return ktm::detail::vec_opt_implement::mul_scalar<N, T, V>::call(x, one<T> / scalar);
        else 
            return call(x, scalar, std::make_index_sequence<N>());
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

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::div_scalar_to_self<N, T, V>
{
    static CHTHOLLY_INLINE V& call(V& x, T scalar) noexcept
    {
        if constexpr(std::is_floating_point_v<T>)
            return ktm::detail::vec_opt_implement::mul_scalar_to_self<N, T, V>::call(x, one<T> / scalar);
        else 
            return call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] /= scalar), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::reduce_add<N, T, V>
{
    static CHTHOLLY_INLINE T call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        return (reinterpret_cast<const T*>(&x)[Ns] + ...);
    }
};

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::reduce_min<N, T, V>
{
    static CHTHOLLY_INLINE T call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N - 1>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        if constexpr(sizeof...(Ns))
        {
            T ret = reinterpret_cast<const T*>(&x)[0];
            ((ret = std::min<T>(ret, reinterpret_cast<const T*>(&x)[Ns + 1])), ...);
            return ret;
        }
        else
            return *reinterpret_cast<const T*>(&x);
    }
};

template<size_t N, typename T, class V>
struct ktm::detail::vec_opt_implement::reduce_max<N, T, V>
{
    static CHTHOLLY_INLINE T call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N - 1>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        if constexpr(sizeof...(Ns))
        {
            T ret = reinterpret_cast<const T*>(&x)[0];
            ((ret = std::max<T>(ret, reinterpret_cast<const T*>(&x)[Ns + 1])), ...);
            return ret;
        }
        else
            return *reinterpret_cast<const T*>(&x);
    }
};
#endif