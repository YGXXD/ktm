#ifndef _I_MAT_OPT_H_
#define _I_MAT_OPT_H_

#include "Math/MathType/BaseType.h"
#include "Math/Detail/MatOptImpl.h"

namespace ktm
{
template<class Father, class Child>
struct IMatOpt;

template<class Father, size_t Col, size_t Raw, typename T>
struct IMatOpt<Father, mat<Col, Raw, T>> : Father
{
    using Father::Father;

    CHTHOLLY_INLINE vec<Raw, T> operator*(const vec<Col, T>& v) const noexcept
    {
        return detail::mat_opt_implement::mat_mul_vec<mat<Col, Raw, T>>::call(reinterpret_cast<const mat<Col, Raw, T>&>(*this), v); 
    }

    friend CHTHOLLY_INLINE vec<Col, T> operator*(const vec<Raw, T>& v, const mat<Col, Raw, T>& m) noexcept
    {
        return detail::mat_opt_implement::vec_mul_mat<mat<Col, Raw, T>>::call(v, m); 
    }

    template<size_t U>
    CHTHOLLY_INLINE mat<U, Raw, T> operator*(const mat<U, Col, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::mat_mul_mat<mat<Col, Raw, T>>::call(reinterpret_cast<const mat<Col, Raw, T>&>(*this), m2); 
    }

    CHTHOLLY_INLINE mat<Col, Raw, T> operator+(const mat<Col, Raw, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::add<mat<Col, Raw, T>>::call(reinterpret_cast<const mat<Col, Raw, T>&>(*this), m2); 
    }

    CHTHOLLY_INLINE mat<Col, Raw, T> operator-(const mat<Col, Raw, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::minus<mat<Col, Raw, T>>::call(reinterpret_cast<const mat<Col, Raw, T>&>(*this), m2); 
    }

    CHTHOLLY_INLINE bool operator==(const mat<Col, Raw, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::equal<mat<Col, Raw, T>>::call(reinterpret_cast<const mat<Col, Raw, T>&>(*this), m2); 
    }

    CHTHOLLY_INLINE bool operator!=(const mat<Col, Raw, T>& m2) const noexcept
    {
        return !detail::mat_opt_implement::equal<mat<Col, Raw, T>>::call(reinterpret_cast<const mat<Col, Raw, T>&>(*this), m2); 
    }

};
}

#endif