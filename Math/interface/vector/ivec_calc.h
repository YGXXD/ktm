#ifndef _KTM_I_VEC_CALC_H_
#define _KTM_I_VEC_CALC_H_

#include "../../type/basic.h"
#include "../../detail/vector/vec_calc_fwd.h"

namespace ktm
{
template<class Father, class Child>
struct ivec_calc;

template<class Father, size_t N, typename T>
struct ivec_calc<Father, vec<N, T>> : Father
{
    using Father::Father;
    
    CHTHOLLY_INLINE vec<N, T> operator+(const vec<N, T>& y) const noexcept
    {
        return detail::vec_calc_implement::add<N, T>::call(reinterpret_cast<const vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T>& operator+=(const vec<N, T>& y) noexcept
    {
        vec<N, T>& this_ref = reinterpret_cast<vec<N, T>&>(*this);
        detail::vec_calc_implement::add_to_self<N, T>::call(this_ref, y);
        return this_ref;
    }

    CHTHOLLY_INLINE vec<N, T> operator-(const vec<N, T>& y) const noexcept
    {
        return detail::vec_calc_implement::minus<N, T>::call(reinterpret_cast<const vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T>& operator-=(const vec<N, T>& y) noexcept
    {
        vec<N, T>& this_ref = reinterpret_cast<vec<N, T>&>(*this);
        detail::vec_calc_implement::minus_to_self<N, T>::call(this_ref, y);
        return this_ref;
    }
    
    CHTHOLLY_INLINE vec<N, T> operator*(const vec<N, T>& y) const noexcept
    {
        return detail::vec_calc_implement::mul<N, T>::call(reinterpret_cast<const vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T>& operator*=(const vec<N, T>& y) noexcept
    {
        vec<N, T>& this_ref = reinterpret_cast<vec<N, T>&>(*this);
        detail::vec_calc_implement::mul_to_self<N, T>::call(this_ref, y);
        return this_ref;
    }

    CHTHOLLY_INLINE vec<N, T> operator/(const vec<N, T>& y) const noexcept
    {
        return detail::vec_calc_implement::div<N, T>::call(reinterpret_cast<const vec<N, T>&>(*this), y);
    }

    CHTHOLLY_INLINE vec<N, T>& operator/=(const vec<N, T>& y) noexcept
    {
        vec<N, T>& this_ref = reinterpret_cast<vec<N, T>&>(*this);
        detail::vec_calc_implement::div_to_self<N, T>::call(this_ref, y);
        return this_ref;
    }

    CHTHOLLY_INLINE vec<N, T> operator-() const noexcept
    {
        return detail::vec_calc_implement::opposite<N, T>::call(reinterpret_cast<const vec<N, T>&>(*this));
    }

    CHTHOLLY_INLINE vec<N, T> operator+(T scalar) const noexcept
    {
        return detail::vec_calc_implement::add_scalar<N, T>::call(reinterpret_cast<const vec<N, T>&>(*this), scalar);
    }

    CHTHOLLY_INLINE vec<N, T>& operator+=(T scalar) noexcept
    {
        vec<N, T>& this_ref = reinterpret_cast<vec<N, T>&>(*this);
        detail::vec_calc_implement::add_scalar_to_self<N, T>::call(this_ref, scalar);
        return this_ref;
    }

    friend CHTHOLLY_INLINE vec<N, T> operator+(T a, const vec<N, T>& x) noexcept 
    { 
        return x + a; 
    }

    CHTHOLLY_INLINE vec<N, T> operator-(T scalar) const noexcept
    {
        return detail::vec_calc_implement::minus_scalar<N, T>::call(reinterpret_cast<const vec<N, T>&>(*this), scalar);
    }

    CHTHOLLY_INLINE vec<N, T>& operator-=(T scalar) noexcept
    {
        vec<N, T>& this_ref = reinterpret_cast<vec<N, T>&>(*this);
        detail::vec_calc_implement::minus_scalar_to_self<N, T>::call(this_ref, scalar);
        return this_ref;
    }

    CHTHOLLY_INLINE vec<N, T> operator*(T scalar) const noexcept
    {
        return detail::vec_calc_implement::mul_scalar<N, T>::call(reinterpret_cast<const vec<N, T>&>(*this), scalar);
    }

    CHTHOLLY_INLINE vec<N, T>& operator*=(T scalar) noexcept
    {
        vec<N, T>& this_ref = reinterpret_cast<vec<N, T>&>(*this);
        detail::vec_calc_implement::mul_scalar_to_self<N, T>::call(this_ref, scalar);
        return this_ref;
    }

    friend CHTHOLLY_INLINE vec<N, T> operator*(T a, const vec<N, T>& x) noexcept 
    {
        return x * a; 
    }
    
    CHTHOLLY_INLINE vec<N, T> operator/(T scalar) const noexcept
    {
        return detail::vec_calc_implement::div_scalar<N, T>::call(reinterpret_cast<const vec<N, T>&>(*this), scalar);
    }

    CHTHOLLY_INLINE vec<N, T>& operator/=(T scalar) noexcept
    {
        vec<N, T>& this_ref = reinterpret_cast<vec<N, T>&>(*this);
        detail::vec_calc_implement::div_scalar_to_self<N, T>::call(this_ref, scalar);
        return this_ref;
    }
};

}
#endif