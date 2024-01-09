#ifndef _KTM_I_MAT_CALC_H_
#define _KTM_I_MAT_CALC_H_

#include "../../type/basic.h"
#include "../../detail/matrix/mat_calc_fwd.h"

namespace ktm
{
template<class Father, class Child>
struct imat_calc;

template<class Father, size_t Row, size_t Col, typename T>
struct imat_calc<Father, mat<Row, Col, T>> : Father
{
    using Father::Father;

    CHTHOLLY_INLINE vec<Col, T> operator*(const vec<Row, T>& v) const noexcept
    {
        return detail::mat_opt_implement::mat_mul_vec<Row, Col, T>::call(reinterpret_cast<const mat<Row, Col, T>&>(*this), v); 
    }

    friend CHTHOLLY_INLINE vec<Row, T> operator*(const vec<Col, T>& v, const mat<Row, Col, T>& m) noexcept
    {
        return detail::mat_opt_implement::vec_mul_mat<Row, Col, T>::call(v, m); 
    }

    template<size_t U>
    CHTHOLLY_INLINE mat<U, Col, T> operator*(const mat<U, Row, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::mat_mul_mat<Row, Col, T>::template call<U>(reinterpret_cast<const mat<Row, Col, T>&>(*this), m2); 
    }

    CHTHOLLY_INLINE mat<Row, Col, T> operator+(const mat<Row, Col, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::add<Row, Col, T>::call(reinterpret_cast<const mat<Row, Col, T>&>(*this), m2); 
    }

    CHTHOLLY_INLINE mat<Row, Col, T> operator-(const mat<Row, Col, T>& m2) const noexcept
    {
        return detail::mat_opt_implement::minus<Row, Col, T>::call(reinterpret_cast<const mat<Row, Col, T>&>(*this), m2); 
    }
};
}

#endif
