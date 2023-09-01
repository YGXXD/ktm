#ifndef _I_VEC_OPT_INL_
#define _I_VEC_OPT_INL_

#include "IVecCom.h"

template<size_t N, typename T, class V>
struct ktm::VecComImplement::Add<N, T, V>
{
    static CHTHOLLY_INLINE V Call(const V& x, const V& y) noexcept
    {
        return Call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V Call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] + reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::AddToSelf<N, T, V>
{
    static CHTHOLLY_INLINE V& Call(V& x, const V& y) noexcept
    {
        return Call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& Call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] += reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::Minus<N, T, V>
{
    static CHTHOLLY_INLINE V Call(const V& x, const V& y) noexcept
    {
        return Call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V Call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] - reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::MinusToSelf<N, T, V>
{
    static CHTHOLLY_INLINE V& Call(V& x, const V& y) noexcept
    {
        return Call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& Call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] -= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::Mul<N, T, V>
{
    static CHTHOLLY_INLINE V Call(const V& x, const V& y) noexcept
    {
        return Call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V Call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] * reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::MulToSelf<N, T, V>
{
    static CHTHOLLY_INLINE V& Call(V& x, const V& y) noexcept
    {
        return Call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& Call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] *= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::Div<N, T, V>
{
    static CHTHOLLY_INLINE V Call(const V& x, const V& y) noexcept
    {
        return Call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V Call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] / reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::DivToSelf<N, T, V>
{
    static CHTHOLLY_INLINE V& Call(V& x, const V& y) noexcept
    {
        return Call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& Call(V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] /= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::Opposite<N, T, V>
{
    static CHTHOLLY_INLINE V Call(const V& x) noexcept
    {
        return Call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V Call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = -reinterpret_cast<const T*>(&x)[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::AddScalar<N, T, V>
{
    static CHTHOLLY_INLINE V Call(const V& x, T scalar) noexcept
    {
        return Call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V Call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] + scalar), ...);
        return ret;
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::AddScalarToSelf<N, T, V>
{
    static CHTHOLLY_INLINE V& Call(V& x, T scalar) noexcept
    {
        return Call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& Call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] += scalar), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::MinusScalar<N, T, V>
{
    static CHTHOLLY_INLINE V Call(const V& x, T scalar) noexcept
    {
        return Call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V Call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] - scalar), ...);
        return ret;
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::MinusScalarToSelf<N, T, V>
{
    static CHTHOLLY_INLINE V& Call(V& x, T scalar) noexcept
    {
        return Call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& Call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] -= scalar), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::MulScalar<N, T, V>
{
    static CHTHOLLY_INLINE V Call(const V& x, T scalar) noexcept
    {
        return Call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V Call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] * scalar), ...);
        return ret;
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::MulScalarToSelf<N, T, V>
{
    static CHTHOLLY_INLINE V& Call(V& x, T scalar) noexcept
    {
        return Call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& Call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] *= scalar), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::DivScalar<N, T, V>
{
    static CHTHOLLY_INLINE V Call(const V& x, T scalar) noexcept
    {   
        if constexpr(std::is_floating_point_v<T>)
            return ktm::VecComImplement::MulScalar<N, T, V>::Call(x, one<T> / scalar);
        else 
            return Call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V Call(const V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(&x)[Ns] / scalar), ...);
        return ret;
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::DivScalarToSelf<N, T, V>
{
    static CHTHOLLY_INLINE V& Call(V& x, T scalar) noexcept
    {
        if constexpr(std::is_floating_point_v<T>)
            return ktm::VecComImplement::MulScalarToSelf<N, T, V>::Call(x, one<T> / scalar);
        else 
            return Call(x, scalar, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE V& Call(V& x, T scalar, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(&x)[Ns] /= scalar), ...);
        return x; 
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::ReduceSum<N, T, V>
{
    static CHTHOLLY_INLINE T Call(const V& x) noexcept
    {
        return Call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T Call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        return (reinterpret_cast<const T*>(&x)[Ns] + ...);
    }
};

template<size_t N, typename T, class V>
struct ktm::VecComImplement::ReduceMin<N, T, V>
{
    static CHTHOLLY_INLINE T Call(const V& x) noexcept
    {
        return Call(x, std::make_index_sequence<N - 1>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T Call(const V& x, std::index_sequence<Ns...>) noexcept
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
struct ktm::VecComImplement::ReduceMax<N, T, V>
{
    static CHTHOLLY_INLINE T Call(const V& x) noexcept
    {
        return Call(x, std::make_index_sequence<N - 1>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T Call(const V& x, std::index_sequence<Ns...>) noexcept
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