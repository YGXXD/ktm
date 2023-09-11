#ifndef _I_VEC_OPT_H_
#define _I_VEC_OPT_H_

#include "Math/MathType/BaseType.h"
#include "Math/Detail/VecOptImpl.h"

namespace ktm
{
template<class Father, class Child>
struct IVecOpt;

template<class Father, size_t N, typename T>
struct IVecOpt<Father, vec<N, T>> : Father
{
    using Father::Father;
    
    CHTHOLLY_INLINE vec<N, T> operator+(const vec<N, T>& y) const noexcept
    {
        return detail::vec_opt_implement::add<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T>& operator+=(const vec<N, T>& y) noexcept
    {
        return detail::vec_opt_implement::add_to_self<vec<N, T>>::call(reinterpret_cast<vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T> operator-(const vec<N, T>& y) const noexcept
    {
        return detail::vec_opt_implement::minus<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T>& operator-=(const vec<N, T>& y) noexcept
    {
        return detail::vec_opt_implement::minus_to_self<vec<N, T>>::call(reinterpret_cast<vec<N, T>&>(*this), y);
    }
    
    CHTHOLLY_INLINE vec<N, T> operator*(const vec<N, T>& y) const noexcept
    {
        return detail::vec_opt_implement::mul<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T>& operator*=(const vec<N, T>& y) noexcept
    {
        return detail::vec_opt_implement::mul_to_self<vec<N, T>>::call(reinterpret_cast<vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T> operator/(const vec<N, T>& y) const noexcept
    {
        return detail::vec_opt_implement::div<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T>& operator/=(const vec<N, T>& y) noexcept
    {
        return detail::vec_opt_implement::div_to_self<vec<N, T>>::call(reinterpret_cast<vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T> operator-() const noexcept
    {
        return detail::vec_opt_implement::opposite<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this));
    }

    CHTHOLLY_INLINE vec<N, T> operator+(T scalar) const noexcept
    {
        return detail::vec_opt_implement::add_scalar<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this), scalar);
    }

    CHTHOLLY_INLINE vec<N, T>& operator+=(T scalar) noexcept
    {
        return detail::vec_opt_implement::add_scalar_to_self<vec<N, T>>::call(reinterpret_cast<vec<N, T>&>(*this), scalar);
    }

    friend CHTHOLLY_INLINE vec<N, T> operator+(T a, const vec<N, T>& x) noexcept 
    { 
        return x + a; 
    }

    CHTHOLLY_INLINE vec<N, T> operator-(T scalar) const noexcept
    {
        return detail::vec_opt_implement::minus_scalar<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this), scalar);
    }

    CHTHOLLY_INLINE vec<N, T>& operator-=(T scalar) noexcept
    {
        return detail::vec_opt_implement::minus_scalar_to_self<vec<N, T>>::call(reinterpret_cast<vec<N, T>&>(*this), scalar);
    }

    CHTHOLLY_INLINE vec<N, T> operator*(T scalar) const noexcept
    {
        return detail::vec_opt_implement::mul_scalar<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this), scalar);
    }

    CHTHOLLY_INLINE vec<N, T>& operator*=(T scalar) noexcept
    {
        return detail::vec_opt_implement::mul_scalar_to_self<vec<N, T>>::call(reinterpret_cast<vec<N, T>&>(*this), scalar);
    }

    friend CHTHOLLY_INLINE vec<N, T> operator*(T a, const vec<N, T>& x) noexcept 
    {
        return x * a; 
    }
    
    CHTHOLLY_INLINE vec<N, T> operator/(T scalar) const noexcept
    {
        return detail::vec_opt_implement::div_scalar<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this), scalar);
    }

    CHTHOLLY_INLINE vec<N, T>& operator/=(T scalar) noexcept
    {
        return detail::vec_opt_implement::div_scalar_to_self<vec<N, T>>::call(reinterpret_cast<vec<N, T>&>(*this), scalar);
    }

    CHTHOLLY_INLINE bool operator==(const vec<N, T>& y)
    {
        return detail::vec_opt_implement::equal<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE bool operator!=(const vec<N, T>& y)
    {
        return !detail::vec_opt_implement::equal<vec<N, T>>::call(reinterpret_cast<const vec<N, T>&>(*this), y);
    }
};

}
#endif