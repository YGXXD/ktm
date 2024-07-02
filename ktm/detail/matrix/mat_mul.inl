//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_MAT_MUL_INL_
#define _KTM_MAT_MUL_INL_

#include "mat_mul_fwd.h"
#include "../loop_util.h"
#include "../../type/vec_fwd.h"
#include "../../type/mat_fwd.h"
#include "../../function/common.h"

template<size_t Row, size_t Col, typename T, typename Void>
struct ktm::detail::mat_mul_implement::mat_mul_vec
{
	using M = mat<Row, Col, T>;
    using ColV = vec<Col, T>;
    using RowV = vec<Row, T>;
    static KTM_INLINE void call(ColV& out, const M& m, const RowV& v) noexcept
    {
        out = m[0] * v[0];
        loop_op<Row - 1, void>::call(
            [&out](const ColV& m_col, const T& v_val) -> void { ktm_operator_smadd(out, m_col, v_val); }, &m[1], &v[1]);
    }
};

template<size_t Row, size_t Col, typename T, typename Void>
struct ktm::detail::mat_mul_implement::vec_mul_mat
{
    using M = mat<Row, Col, T>;
    using ColV = vec<Col, T>;
    using RowV = vec<Row, T>;
    static KTM_INLINE void call(RowV& out, const ColV& v, const M& m) noexcept
    {
        loop_op<Row, RowV>::call(out, 
            [&v](const ColV& m_col) -> T { return ktm::reduce_add(m_col * v); }, m);
    }
};

template<size_t Row, size_t Col, typename T, typename Void>
struct ktm::detail::mat_mul_implement::mat_mul_mat
{
    using M = mat<Row, Col, T>;
    using ColV = vec<Col, T>;
    using RowV = vec<Row, T>;

    template<size_t U>
    using M2 = mat<U, Row, T>;
    
    template<size_t U>
    using RetM = mat<U, Col, T>;

    template<size_t U>
    static KTM_INLINE void call(RetM<U>& out, const M& m1 , const M2<U>& m2) noexcept
    {
        loop_op<U, void>::call(
            [&m1](ColV& out_col, const RowV& m2_col) -> void 
                { mat_mul_vec<Row, Col, T>::call(out_col, m1, m2_col); }, out, m2);
    }
};

#endif
