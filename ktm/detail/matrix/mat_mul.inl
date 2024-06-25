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
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        ColV ret;
        loop_reduce<Row>(ret, m, v, m[0] * v[0], 
        [](const ColV& ret, const ColV& m_col, const T& v_val) -> ColV 
        {
            return ret + m_col * v_val;
        });
        return ret;
    }
};

template<size_t Row, size_t Col, typename T, typename Void>
struct ktm::detail::mat_mul_implement::vec_mul_mat
{
    using M = mat<Row, Col, T>;
    using ColV = vec<Col, T>;
    using RowV = vec<Row, T>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        RowV ret;
        loop_scalar<Row>(ret, m, v, 
        [](const ColV& m_col, const ColV& v) -> T
        {
            return ktm::reduce_add(m_col * v);
        });
        return ret;
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
    static KTM_INLINE RetM<U> call(const M& m1 , const M2<U>& m2) noexcept
    {
        RetM<U> ret;
        loop_scalar<U>(ret, m2, m1, 
        [](const RowV& m2_col, const M& m1) -> ColV
        {
            return mat_mul_vec<Row, Col, T>::call(m1, m2_col);
        });
        return ret;
    }
};

#endif
