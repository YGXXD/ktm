//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_ARRAY_CALC_SIMD_INL_
#define _KTM_ARRAY_CALC_SIMD_INL_

#include "array_calc_fwd.h"
#include "../../setup.h"
#include "../../simd/skv.h"

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE | KTM_SIMD_WASM)

template<>
struct ktm::detail::array_calc_implement::add<float, 4>
{
    using A = std::array<float, 4>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        _store128_f32(out.data(), _add128_f32(_load128_f32(x.data()), _load128_f32(y.data())));
    }
};

template<>
struct ktm::detail::array_calc_implement::sub<float, 4>
{
    using A = std::array<float, 4>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        _store128_f32(out.data(), _sub128_f32(_load128_f32(x.data()), _load128_f32(y.data())));
    }
};

template<>
struct ktm::detail::array_calc_implement::neg<float, 4>
{
    using A = std::array<float, 4>;
    static KTM_INLINE void call(A& out, const A& x) noexcept
    {
        _store128_f32(out.data(), _neg128_f32(_load128_f32(x.data())));
    }
};

template<>
struct ktm::detail::array_calc_implement::mul<float, 4>
{
    using A = std::array<float, 4>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        _store128_f32(out.data(), _mul128_f32(_load128_f32(x.data()), _load128_f32(y.data())));
    }
};

template<>
struct ktm::detail::array_calc_implement::div<float, 4>
{
    using A = std::array<float, 4>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        _store128_f32(out.data(), _div128_f32(_load128_f32(x.data()), _load128_f32(y.data())));
    }
};

template<>
struct ktm::detail::array_calc_implement::add_scalar<float, 4>
{
    using A = std::array<float, 4>;
    static KTM_INLINE void call(A& out, const A& x, float scalar) noexcept
    {
        _store128_f32(out.data(), _add128_f32(_load128_f32(x.data()), _dup128_f32(scalar)));
    }
};

template<>
struct ktm::detail::array_calc_implement::sub_scalar<float, 4>
{
    using A = std::array<float, 4>;
    static KTM_INLINE void call(A& out, const A& x, float scalar) noexcept
    {
        _store128_f32(out.data(), _sub128_f32(_load128_f32(x.data()), _dup128_f32(scalar)));
    }
};

template<>
struct ktm::detail::array_calc_implement::mul_scalar<float, 4>
{
    using A = std::array<float, 4>;
    static KTM_INLINE void call(A& out, const A& x, float scalar) noexcept
    {
        _store128_f32(out.data(), _mul128_f32(_load128_f32(x.data()), _dup128_f32(scalar)));
    }
};

template<>
struct ktm::detail::array_calc_implement::div_scalar<float, 4>
{
    using A = std::array<float, 4>;
    static KTM_INLINE void call(A& out, const A& x, float scalar) noexcept
    {
        _store128_f32(out.data(), _div128_f32(_load128_f32(x.data()), _dup128_f32(scalar)));
    }
};

#endif // KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE)

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE2)

template<>
struct ktm::detail::array_calc_implement::add<int, 4>
{
    using A = std::array<int, 4>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        skv::sv4 x_st = _cast128_s32_f32(_load128_f32(x.data()));
        skv::sv4 y_st = _cast128_s32_f32(_load128_f32(y.data())); 
        _store128_f32(out.data(), _cast128_f32_s32(_add128_s32(x_st, y_st)));
    }
};

template<>
struct ktm::detail::array_calc_implement::sub<int, 4>
{
    using A = std::array<int, 4>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        skv::sv4 x_st = _cast128_s32_f32(_load128_f32(x.data()));
        skv::sv4 y_st = _cast128_s32_f32(_load128_f32(y.data())); 
        _store128_f32(out.data(), _cast128_f32_s32(_sub128_s32(x_st, y_st)));
    }
};

template<>
struct ktm::detail::array_calc_implement::neg<int, 4>
{
    using A = std::array<int, 4>;
    static KTM_INLINE void call(A& out, const A& x) noexcept
    {
        skv::sv4 x_st = _cast128_s32_f32(_load128_f32(x.data()));
        _store128_f32(out.data(), _cast128_f32_s32(_neg128_f32(x_st)));
    }
};

template<>
struct ktm::detail::array_calc_implement::add_scalar<int, 4>
{
    using A = std::array<int, 4>;
    static KTM_INLINE void call(A& out, const A& x, int scalar) noexcept
    {
        skv::sv4 x_st = _cast128_s32_f32(_load128_f32(x.data()));
        _store128_f32(out.data(), _cast128_f32_s32(_add128_s32(x_st, _dup128_s32(scalar))));
    }
};

template<>
struct ktm::detail::array_calc_implement::sub_scalar<int, 4>
{
    using A = std::array<int, 4>;
    static KTM_INLINE void call(A& out, const A& x, int scalar) noexcept
    {
        skv::sv4 x_st = _cast128_s32_f32(_load128_f32(x.data()));
        _store128_f32(out.data(), _cast128_f32_s32(_sub128_s32(x_st, _dup128_s32(scalar))));
    }
};

#endif // KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE2)

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE4_1)

template<>
struct ktm::detail::array_calc_implement::mul<int, 4>
{
    using A = std::array<int, 4>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        skv::sv4 x_st = _cast128_s32_f32(_load128_f32(x.data()));
        skv::sv4 y_st = _cast128_s32_f32(_load128_f32(y.data())); 
        _store128_f32(out.data(), _cast128_f32_s32(_mul128_s32(x_st, y_st)));
    }
};

template<>
struct ktm::detail::array_calc_implement::mul_scalar<int, 4>
{
    using A = std::array<int, 4>;
    static KTM_INLINE void call(A& out, const A& x, int scalar) noexcept
    {
        skv::sv4 x_st = _cast128_s32_f32(_load128_f32(x.data()));
        _store128_f32(out.data(), _cast128_f32_s32(_mul128_s32(x_st, _dup128_s32(scalar))));
    }
};

#endif // KTM_SIMD_ENABLE(KTM_SIMD_NEON | KTM_SIMD_SSE4_1 | KTM_SIMD_WASM)

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON)

template<>
struct ktm::detail::array_calc_implement::add<float, 2>
{
    using A = std::array<float, 2>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        _store64_f32(out.data(), _add64_f32(_load64_f32(x.data()), _load64_f32(y.data())));
    }
};

template<>
struct ktm::detail::array_calc_implement::sub<float, 2>
{
    using A = std::array<float, 2>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        _store64_f32(out.data(), _sub64_f32(_load64_f32(x.data()), _load64_f32(y.data())));
    }
};

template<>
struct ktm::detail::array_calc_implement::neg<float, 2>
{
    using A = std::array<float, 2>;
    static KTM_INLINE void call(A& out, const A& x) noexcept
    {
        _store64_f32(out.data(), _neg64_f32(_load64_f32(x.data())));
    }
};

template<>
struct ktm::detail::array_calc_implement::mul<float, 2>
{
    using A = std::array<float, 2>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        _store64_f32(out.data(), _mul64_f32(_load64_f32(x.data()), _load64_f32(y.data())));
    }
};

template<>
struct ktm::detail::array_calc_implement::div<float, 2>
{
    using A = std::array<float, 2>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        _store64_f32(out.data(), _div64_f32(_load64_f32(x.data()), _load64_f32(y.data())));
    }
};

template<>
struct ktm::detail::array_calc_implement::add_scalar<float, 2>
{
    using A = std::array<float, 2>;
    static KTM_INLINE void call(A& out, const A& x, float scalar) noexcept
    {
        _store64_f32(out.data(), _add64_f32(_load64_f32(x.data()), _dup64_f32(scalar)));
    }
};

template<>
struct ktm::detail::array_calc_implement::sub_scalar<float, 2>
{
    using A = std::array<float, 2>;
    static KTM_INLINE void call(A& out, const A& x, float scalar) noexcept
    {
        _store64_f32(out.data(), _sub64_f32(_load64_f32(x.data()), _dup64_f32(scalar)));
    }
};

template<>
struct ktm::detail::array_calc_implement::mul_scalar<float, 2>
{
    using A = std::array<float, 2>;
    static KTM_INLINE void call(A& out, const A& x, float scalar) noexcept
    {
        _store64_f32(out.data(), _mul64_f32(_load64_f32(x.data()), _dup64_f32(scalar)));
    }
};

template<>
struct ktm::detail::array_calc_implement::div_scalar<float, 2>
{
    using A = std::array<float, 2>;
    static KTM_INLINE void call(A& out, const A& x, float scalar) noexcept
    {
        _store64_f32(out.data(), _div64_f32(_load64_f32(x.data()), _dup64_f32(scalar)));
    }
};

template<>
struct ktm::detail::array_calc_implement::add<int, 2>
{
    using A = std::array<int, 2>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        skv::sv2 x_st = _cast64_s32_f32(_load64_f32(x.data()));
        skv::sv2 y_st = _cast64_s32_f32(_load64_f32(y.data())); 
        _store64_f32(out.data(), _cast64_f32_s32(_add64_s32(x_st, y_st)));
    }
};

template<>
struct ktm::detail::array_calc_implement::sub<int, 2>
{
    using A = std::array<int, 2>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        skv::sv2 x_st = _cast64_s32_f32(_load64_f32(x.data()));
        skv::sv2 y_st = _cast64_s32_f32(_load64_f32(y.data())); 
        _store64_f32(out.data(), _cast64_f32_s32(_sub64_s32(x_st, y_st)));
    }
};

template<>
struct ktm::detail::array_calc_implement::neg<int, 2>
{
    using A = std::array<int, 2>;
    static KTM_INLINE void call(A& out, const A& x) noexcept
    {
        skv::sv2 x_st = _cast64_s32_f32(_load64_f32(x.data()));
        _store64_f32(out.data(), _cast64_f32_s32(_neg64_f32(x_st)));
    }
};

template<>
struct ktm::detail::array_calc_implement::mul<int, 2>
{
    using A = std::array<int, 2>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        skv::sv2 x_st = _cast64_s32_f32(_load64_f32(x.data()));
        skv::sv2 y_st = _cast64_s32_f32(_load64_f32(y.data())); 
        _store64_f32(out.data(), _cast64_f32_s32(_mul64_s32(x_st, y_st)));
    }
};

template<>
struct ktm::detail::array_calc_implement::add_scalar<int, 2>
{
    using A = std::array<int, 2>;
    static KTM_INLINE void call(A& out, const A& x, int scalar) noexcept
    {
        skv::sv2 x_st = _cast64_s32_f32(_load64_f32(x.data()));
        _store64_f32(out.data(), _cast64_f32_s32(_add64_s32(x_st, _dup64_s32(scalar))));
    }
};

template<>
struct ktm::detail::array_calc_implement::sub_scalar<int, 2>
{
    using A = std::array<int, 2>;
    static KTM_INLINE void call(A& out, const A& x, int scalar) noexcept
    {
        skv::sv2 x_st = _cast64_s32_f32(_load64_f32(x.data()));
        _store64_f32(out.data(), _cast64_f32_s32(_sub64_s32(x_st, _dup64_s32(scalar))));
    }
};

template<>
struct ktm::detail::array_calc_implement::mul_scalar<int, 2>
{
    using A = std::array<int, 2>;
    static KTM_INLINE void call(A& out, const A& x, int scalar) noexcept
    {
        skv::sv2 x_st = _cast64_s32_f32(_load64_f32(x.data()));
        _store64_f32(out.data(), _cast64_f32_s32(_mul64_s32(x_st, _dup64_s32(scalar))));
    }
};

#endif // KTM_SIMD_ENABLE(KTM_SIMD_NEON)

#endif
