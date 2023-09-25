#ifndef _I_MAT_OPT_H_
#define _I_MAT_OPT_H_

#include "Math/MathType/BaseType.h"
#include "Math/Detail/MatOptImpl.h"

namespace ktm
{
template<class Father, class Child>
struct IMatOpt;

template<class Father, size_t Col, size_t Row, typename T>
struct IMatOpt<Father, mat<Col, Row, T>> : Father
{
    using Father::Father;

    CHTHOLLY_INLINE vec<Col, T> operator*(const vec<Row, T>& v) const noexcept
    {
        return detail::mat_opt_implement::mat_mul_vec<Col, Row, T>::call(reinterpret_cast<const mat<Col, Row, T>&>(*this), v); 
    }

    friend CHTHOLLY_INLINE vec<Row, T> operator*(const vec<Col, T>& v, const mat<Col, Row, T>& m) noexcept
    {
        return detail::mat_opt_implement::vec_mul_mat<Col, Row, T>::call(v, m); 
    }

    template<size_t U>
    CHTHOLLY_INLINE mat<Col, U, T> operator*(const mat<Row, U, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::mat_mul_mat<Col, Row, T>::template call<U>(reinterpret_cast<const mat<Col, Row, T>&>(*this), m2); 
    }

    CHTHOLLY_INLINE mat<Col, Row, T> operator+(const mat<Col, Row, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::add<Col, Row, T>::call(reinterpret_cast<const mat<Col, Row, T>&>(*this), m2); 
    }

    CHTHOLLY_INLINE mat<Col, Row, T> operator-(const mat<Col, Row, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::minus<Col, Row, T>::call(reinterpret_cast<const mat<Col, Row, T>&>(*this), m2); 
    }

    CHTHOLLY_INLINE bool operator==(const mat<Col, Row, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::equal<Col, Row, T>::call(reinterpret_cast<const mat<Col, Row, T>&>(*this), m2); 
    }

    CHTHOLLY_INLINE bool operator!=(const mat<Col, Row, T>& m2) const noexcept
    {
        return !detail::mat_opt_implement::equal<Col, Row, T>::call(reinterpret_cast<const mat<Col, Row, T>&>(*this), m2); 
    }

};
}

#endif
