#ifndef _I_VEC_OPT_H_
#define _I_VEC_OPT_H_

#include "Math/TypeBase.h"

namespace ktl
{
template<class Father, class Child>
struct IVecOpt : Father
{
    using Father::Father;
    using T = math_traits_t<Child>;
    static constexpr int N = vec_traits_len<Child>;

    CHTHOLLY_INLINE Child operator+(const Child& y) const noexcept
    {
        return Add(y, std::make_index_sequence<N>());
    }

    CHTHOLLY_INLINE Child& operator+=(const Child& y) noexcept
    {
        return AddToSelf(y, std::make_index_sequence<N>());
    }

    CHTHOLLY_INLINE Child operator-(const Child& y) const noexcept
    {
        return Minus(y, std::make_index_sequence<N>());
    }

    CHTHOLLY_INLINE Child& operator-=(const Child& y) noexcept
    {
        return MinusToSelf(y, std::make_index_sequence<N>());
    }

    CHTHOLLY_INLINE Child operator*(const Child& y) const noexcept
    {
        return Mul(y, std::make_index_sequence<N>()); 
    }

    CHTHOLLY_INLINE Child& operator*=(const Child& y) noexcept
    {
        return MulToSelf(y, std::make_index_sequence<N>());
    }

    CHTHOLLY_INLINE Child operator/(const Child& y) const noexcept
    {
        return Div(y, std::make_index_sequence<N>());
    }

    CHTHOLLY_INLINE Child& operator/=(const Child& y) noexcept
    {
        return DivToSelf(y, std::make_index_sequence<N>());
    }

    CHTHOLLY_INLINE Child operator-() const noexcept
    {
        return Opposite(std::make_index_sequence<N>());
    }

    CHTHOLLY_INLINE Child operator*(T a) const noexcept
    {
        return MulScalar(a, std::make_index_sequence<N>());
    }

    CHTHOLLY_INLINE Child& operator*=(T a) noexcept
    {
        return MulScalarToSelf(a, std::make_index_sequence<N>());
    }

    friend CHTHOLLY_INLINE Child operator*(T a, const Child& x) noexcept
    {
        return x * a;
    }

    CHTHOLLY_INLINE Child operator/(T a) const noexcept
    {
        return DivScalar(a, std::make_index_sequence<N>());
    }

    CHTHOLLY_INLINE Child& operator/=(T a) noexcept
    {
        return DivScalarToSelf(a, std::make_index_sequence<N>());
    }

private:

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child Add(const Child& y, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(this)[Ns] + reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& AddToSelf(const Child& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(this)[Ns] += reinterpret_cast<const T*>(&y)[Ns]), ...);
        return reinterpret_cast<Child&>(*this);
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child Minus(const Child& y, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(this)[Ns] - reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    } 

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& MinusToSelf(const Child& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(this)[Ns] -= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return reinterpret_cast<Child&>(*this); 
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child Mul(const Child& y, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(this)[Ns] * reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& MulToSelf(const Child& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(this)[Ns] *= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return reinterpret_cast<Child&>(*this);
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child Div(const Child& y, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(this)[Ns] / reinterpret_cast<const T*>(&y)[Ns]), ...);
        return ret;
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& DivToSelf(const Child& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(this)[Ns] /= reinterpret_cast<const T*>(&y)[Ns]), ...);
        return reinterpret_cast<Child&>(*this);
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child Opposite(std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = -reinterpret_cast<const T*>(this)[Ns]), ...);
        return ret; 
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child MulScalar(T a, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(this)[Ns] * a), ...);
        return ret;  
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& MulScalarToSelf(T a, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(this)[Ns] *= a), ...);
        return reinterpret_cast<Child&>(*this);
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child DivScalar(T a, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reinterpret_cast<const T*>(this)[Ns] / a), ...);
        return ret;  
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& DivScalarToSelf(T a, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<T*>(this)[Ns] /= a), ...);
        return reinterpret_cast<Child&>(*this);
    }
};
}

#endif