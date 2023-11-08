#ifndef _VEC_OPT_IMPL_INL_
#define _VEC_OPT_IMPL_INL_

#include "VecOptImpl.h"
#include "Math/MathType/BaseType.h"
#include "Math/MathLib/Common.h"

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::add
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = x[Ns] + y[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::add_to_self
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE void call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((x[Ns] += y[Ns]), ...);
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::minus
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = x[Ns] - y[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::minus_to_self
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE void call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((x[Ns] -= y[Ns]), ...);
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::mul
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = x[Ns] * y[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::mul_to_self
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE void call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((x[Ns] *= y[Ns]), ...);
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::div
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = x[Ns] / y[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::div_to_self
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE void call(V& x, const V& y) noexcept
    {
        call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE void call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((x[Ns] /= y[Ns]), ...);
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::opposite
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = -x[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::add_scalar
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = x[Ns] + scalar), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::add_scalar_to_self
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE void call(V& x, T scalar) noexcept
    {
        call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE void call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((x[Ns] += scalar), ...);
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::minus_scalar
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = x[Ns] - scalar), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE void call(V& x, T scalar) noexcept
    {
        call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE void call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((x[Ns] -= scalar), ...);
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::mul_scalar
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {
        return call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = x[Ns] * scalar), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE void call(V& x, T scalar) noexcept
    {
        call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE void call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((x[Ns] *= scalar), ...);
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::div_scalar
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE V call(const V& x, T scalar) noexcept
    {   
        if constexpr(std::is_floating_point_v<T>)
            return mul_scalar<N, T>::call(x, one<T> / scalar);
        else 
            return call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = x[Ns] / scalar), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::div_scalar_to_self
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE void call(V& x, T scalar) noexcept
    {
        if constexpr(std::is_floating_point_v<T>)
            mul_scalar_to_self<N, T>::call(x, one<T> / scalar);
        else 
            call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE void call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((x[Ns] /= scalar), ...);
    }
};

template<size_t N, typename T>
struct ktm::detail::vec_opt_implement::equal
{
    using V = vec<N, T>;
    static CHTHOLLY_INLINE bool call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE bool call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        if constexpr(std::is_floating_point_v<T>)
        {
            return (ktm::equal_zero(x[Ns] - y[Ns]) && ...);
        }
        else
        {
            return ((x[Ns] == y[Ns]) && ...);
        }
    }
};

#endif
