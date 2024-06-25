//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_MAT_MUL_SIMD_H_
#define _KTM_MAT_MUL_SIMD_H_

#include "mat_mul_fwd.h"
#include "../../simd/skv.h"

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE | KTM_SIMD_WASM)

template<size_t Row, size_t Col>
struct ktm::detail::mat_mul_implement::mat_mul_vec<Row, Col, float, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        ColV ret;
        loop_reduce<Row>(ret.st, m, v, _mul128_f32(m[0].st, _dup128_f32(v[0])), 
        [](const skv::fv4& ret_st, const ColV& m_col, const float& v_val) -> skv::fv4 
        {
            return _madd128_f32(ret_st, m_col.st, _dup128_f32(v_val));
        });
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_mul_implement::vec_mul_mat<Row, Col, float, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, float>;
    using ColV = vec<Col, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        RowV ret;
        loop_scalar<Row>(ret, m, v, 
        [](const ColV& m_col, const ColV& v) -> float
        {
            if constexpr(Col == 3)
                return skv::radd_fv3(_mul128_f32(m_col.st, v.st));
            else
                return skv::radd_fv4(_mul128_f32(m_col.st, v.st));
        });
        return ret;
    }
};

#endif // KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE | KTM_SIMD_WASM)

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE4_1 | KTM_SIMD_WASM)

template<size_t Row, size_t Col>
struct ktm::detail::mat_mul_implement::mat_mul_vec<Row, Col, int, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        ColV ret;
        loop_reduce<Row>(ret.st, m, v, _mul128_s32(m[0].st, _dup128_s32(v[0])), 
        [](const skv::sv4& ret_st, const ColV& m_col, const int& v_val) -> skv::sv4 
        {
            return _madd128_s32(ret_st, m_col.st, _dup128_s32(v_val));
        });
        return ret;
    }
};

template<size_t Row, size_t Col>
struct ktm::detail::mat_mul_implement::vec_mul_mat<Row, Col, int, std::enable_if_t<Col == 3 || Col == 4>>
{
    using M = mat<Row, Col, int>;
    using ColV = vec<Col, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        RowV ret;
        loop_scalar<Row>(ret, m, v, 
        [](const ColV& m_col, const ColV& v) -> int
        {
            if constexpr(Col == 3)
                return skv::radd_sv3(_mul128_s32(m_col.st, v.st));
            else
                return skv::radd_sv4(_mul128_s32(m_col.st, v.st));
        });
        return ret;
    }
};

#endif // KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE4_1 | KTM_SIMD_WASM)

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON)

template<size_t Row>
struct ktm::detail::mat_mul_implement::mat_mul_vec<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = vec<2, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        ColV ret;
        loop_reduce<Row>(ret.st, m, v, _mul64_f32(m[0].st, _dup64_f32(v[0])), 
        [](const skv::fv2& ret_st, const ColV& m_col, const float& v_val) -> skv::fv2 
        {
            return _madd64_f32(ret_st, m_col.st, _dup64_f32(v_val));
        });
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_mul_implement::vec_mul_mat<Row, 2, float>
{
    using M = mat<Row, 2, float>;
    using ColV = vec<2, float>;
    using RowV = vec<Row, float>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        RowV ret;
        loop_scalar<Row>(ret, m, v, 
        [](const ColV& m_col, const ColV& v) -> float
        {
            return skv::radd_fv2(_mul64_f32(m_col.st, v.st));
        });
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_mul_implement::mat_mul_vec<Row, 2, int>
{
    using M = mat<Row, 2, int>;
    using ColV = vec<2, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE ColV call(const M& m, const RowV& v) noexcept
    {
        ColV ret;
        loop_reduce<Row>(ret.st, m, v, _mul64_s32(m[0].st, _dup64_s32(v[0])), 
        [](const skv::sv2& ret_st, const ColV& m_col, const int& v_val) -> skv::sv2 
        {
            return _madd64_s32(ret_st, m_col.st, _dup64_s32(v_val));
        });
        return ret;
    }
};

template<size_t Row>
struct ktm::detail::mat_mul_implement::vec_mul_mat<Row, 2, int>
{
    using M = mat<Row, 2, int>;
    using ColV = vec<2, int>;
    using RowV = vec<Row, int>;
    static KTM_INLINE RowV call(const ColV& v, const M& m) noexcept
    {
        RowV ret;
        loop_scalar<Row>(ret, m, v, 
        [](const ColV& m_col, const ColV& v) -> int 
        {
            return skv::radd_sv2(_mul64_s32(m_col.st, v.st));
        });
        return ret;
    }
};

#endif // KTM_SIMD_ENABLE(KTM_SIMD_NEON)

#endif