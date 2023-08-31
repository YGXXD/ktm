#ifndef _I_VEC_OPT_H_
#define _I_VEC_OPT_H_

#include "Math/TypeBase.h"

namespace ktm
{
template<class Father, class Child>
struct IVecOpt : Father
{
    using Father::Father;
    using value_type = math_traits_t<Child>;
    static constexpr int len = vec_traits_len<Child>;

    CHTHOLLY_INLINE Child operator+(const Child& y) const noexcept
    {
        return Add(y, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child& operator+=(const Child& y) noexcept
    {
        return AddToSelf(y, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child operator-(const Child& y) const noexcept
    {
        return Minus(y, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child& operator-=(const Child& y) noexcept
    {
        return MinusToSelf(y, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child operator*(const Child& y) const noexcept
    {
        return Mul(y, std::make_index_sequence<len>()); 
    }

    CHTHOLLY_INLINE Child& operator*=(const Child& y) noexcept
    {
        return MulToSelf(y, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child operator/(const Child& y) const noexcept
    {
        return Div(y, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child& operator/=(const Child& y) noexcept
    {
        return DivToSelf(y, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child operator-() const noexcept
    {
        return Opposite(std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child operator+(value_type a) const noexcept
    {
        return AddScalar(a, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child& operator+=(value_type a) noexcept
    {
        return AddScalarToSelf(a, std::make_index_sequence<len>());
    }

    friend CHTHOLLY_INLINE Child operator+(value_type a, const Child& x) noexcept
    {
        return x + a;
    }

     CHTHOLLY_INLINE Child operator-(value_type a) const noexcept
    {
        return MinusScalar(a, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child& operator-=(value_type a) noexcept
    {
        return MinusScalarToSelf(a, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child operator*(value_type a) const noexcept
    {
        return MulScalar(a, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child& operator*=(value_type a) noexcept
    {
        return MulScalarToSelf(a, std::make_index_sequence<len>());
    }

    friend CHTHOLLY_INLINE Child operator*(value_type a, const Child& x) noexcept
    {
        return x * a;
    }

    CHTHOLLY_INLINE Child operator/(value_type a) const noexcept
    {
        return DivScalar(a, std::make_index_sequence<len>());
    }

    CHTHOLLY_INLINE Child& operator/=(value_type a) noexcept
    {
        return DivScalarToSelf(a, std::make_index_sequence<len>());
    }

private:

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child Add(const Child& y, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<value_type*>(&ret)[Ns] = reinterpret_cast<const value_type*>(this)[Ns] + reinterpret_cast<const value_type*>(&y)[Ns]), ...);
        return ret;
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& AddToSelf(const Child& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<value_type*>(this)[Ns] += reinterpret_cast<const value_type*>(&y)[Ns]), ...);
        return reinterpret_cast<Child&>(*this);
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child Minus(const Child& y, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<value_type*>(&ret)[Ns] = reinterpret_cast<const value_type*>(this)[Ns] - reinterpret_cast<const value_type*>(&y)[Ns]), ...);
        return ret;
    } 

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& MinusToSelf(const Child& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<value_type*>(this)[Ns] -= reinterpret_cast<const value_type*>(&y)[Ns]), ...);
        return reinterpret_cast<Child&>(*this); 
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child Mul(const Child& y, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<value_type*>(&ret)[Ns] = reinterpret_cast<const value_type*>(this)[Ns] * reinterpret_cast<const value_type*>(&y)[Ns]), ...);
        return ret;
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& MulToSelf(const Child& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<value_type*>(this)[Ns] *= reinterpret_cast<const value_type*>(&y)[Ns]), ...);
        return reinterpret_cast<Child&>(*this);
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child Div(const Child& y, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<value_type*>(&ret)[Ns] = reinterpret_cast<const value_type*>(this)[Ns] / reinterpret_cast<const value_type*>(&y)[Ns]), ...);
        return ret;
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& DivToSelf(const Child& y, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<value_type*>(this)[Ns] /= reinterpret_cast<const value_type*>(&y)[Ns]), ...);
        return reinterpret_cast<Child&>(*this);
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child Opposite(std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<value_type*>(&ret)[Ns] = -reinterpret_cast<const value_type*>(this)[Ns]), ...);
        return ret; 
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child AddScalar(value_type a, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<value_type*>(&ret)[Ns] = reinterpret_cast<const value_type*>(this)[Ns] + a), ...);
        return ret;  
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& AddScalarToSelf(value_type a, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<value_type*>(this)[Ns] += a), ...);
        return reinterpret_cast<Child&>(*this);
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child MinusScalar(value_type a, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<value_type*>(&ret)[Ns] = reinterpret_cast<const value_type*>(this)[Ns] - a), ...);
        return ret;  
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& MinusScalarToSelf(value_type a, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<value_type*>(this)[Ns] -= a), ...);
        return reinterpret_cast<Child&>(*this);
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child MulScalar(value_type a, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<value_type*>(&ret)[Ns] = reinterpret_cast<const value_type*>(this)[Ns] * a), ...);
        return ret;  
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& MulScalarToSelf(value_type a, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<value_type*>(this)[Ns] *= a), ...);
        return reinterpret_cast<Child&>(*this);
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child DivScalar(value_type a, std::index_sequence<Ns...>) const noexcept
    {
        Child ret;
        ((reinterpret_cast<value_type*>(&ret)[Ns] = reinterpret_cast<const value_type*>(this)[Ns] / a), ...);
        return ret;  
    }

    template<size_t ...Ns>
    CHTHOLLY_INLINE Child& DivScalarToSelf(value_type a, std::index_sequence<Ns...>) noexcept
    {
        ((reinterpret_cast<value_type*>(this)[Ns] /= a), ...);
        return reinterpret_cast<Child&>(*this);
    }

};
}

#endif