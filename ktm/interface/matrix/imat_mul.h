//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_I_MAT_MUL_H_
#define _KTM_I_MAT_MUL_H_

#include "../../setup.h"
#include "../../type/vec_fwd.h"
#include "../../type/mat_fwd.h"
#include "../../detail/matrix/mat_mul_fwd.h"

namespace ktm
{

template<class Father, class Child>
struct imat_mul;

template<class Father, size_t Row, size_t Col, typename T>
struct imat_mul<Father, mat<Row, Col, T>> : Father
{
    using Father::Father;

    friend KTM_INLINE vec<Col, T> operator*(const mat<Row, Col, T>& m, const vec<Row, T>& v) noexcept
    {
        return detail::mat_mul_implement::mat_mul_vec<Row, Col, T>::call(m, v); 
    }

    friend KTM_INLINE vec<Row, T> operator*(const vec<Col, T>& v, const mat<Row, Col, T>& m) noexcept
    {
        return detail::mat_mul_implement::vec_mul_mat<Row, Col, T>::call(v, m); 
    }

    template<size_t U>
    friend KTM_INLINE mat<U, Col, T> operator*(const mat<Row, Col, T>& m1, const mat<U, Row, T>& m2) noexcept
    {
        return detail::mat_mul_implement::mat_mul_mat<Row, Col, T>::template call<U>(m1, m2); 
    }
};

}

#endif
