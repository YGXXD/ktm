//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_ARRAY_CALC_INL_
#define _KTM_ARRAY_CALC_INL_

#include "array_calc_fwd.h"
#include "../loop_util.h"
#include "../../type/basic.h"

template<typename T, size_t N, typename Void>
struct ktm::detail::array_calc_implement::add
{
    using A = std::array<T, N>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        loop_op<N>(out, x, y, std::plus<T>());
    }
};

template<typename T, size_t N, typename Void>
struct ktm::detail::array_calc_implement::sub
{
    using A = std::array<T, N>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        loop_op<N>(out, x, y, std::minus<T>());
    }
};

template<typename T, size_t N, typename Void>
struct ktm::detail::array_calc_implement::neg
{
    using A = std::array<T, N>;
    static KTM_INLINE void call(A& out, const A& x) noexcept
    {
        loop_op<N>(out, x, std::negate<T>());
    }
};

template<typename T, size_t N, typename Void>
struct ktm::detail::array_calc_implement::mul
{
    using A = std::array<T, N>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        loop_op<N>(out, x, y, std::multiplies<T>());
    }
};

template<typename T, size_t N, typename Void>
struct ktm::detail::array_calc_implement::div
{
    using A = std::array<T, N>;
    static KTM_INLINE void call(A& out, const A& x, const A& y) noexcept
    {
        loop_op<N>(out, x, y, std::divides<T>());
    }
};

template<typename T, size_t N, typename Void>
struct ktm::detail::array_calc_implement::add_scalar
{
    using A = std::array<T, N>;
    template<typename S>
    static KTM_INLINE std::enable_if_t<std::is_arithmetic_v<S>> call(A& out, const A& x, S scalar) noexcept
    {
        loop_scalar<N>(out, x, scalar, std::plus<T>());
    }
};

template<typename T, size_t N, typename Void>
struct ktm::detail::array_calc_implement::sub_scalar
{
    using A = std::array<T, N>;
    template<typename S>
    static KTM_INLINE std::enable_if_t<std::is_arithmetic_v<S>> call(A& out, const A& x, S scalar) noexcept
    {
        loop_scalar<N>(out, x, scalar, std::minus<T>());
    }
};

template<typename T, size_t N, typename Void>
struct ktm::detail::array_calc_implement::mul_scalar
{
    using A = std::array<T, N>;
    template<typename S> 
    static KTM_INLINE std::enable_if_t<std::is_arithmetic_v<S>> call(A& out, const A& x, S scalar) noexcept
    {
        loop_scalar<N>(out, x, scalar, std::multiplies<T>());
    }
};

template<typename T, size_t N, typename Void>
struct ktm::detail::array_calc_implement::div_scalar
{
    using A = std::array<T, N>;
    template<typename S> 
    static KTM_INLINE std::enable_if_t<std::is_arithmetic_v<S>> call(A& out, const A& x, S scalar) noexcept
    {
        if constexpr(std::is_floating_point_v<S>)
            ktm::detail::array_calc_implement::mul_scalar<T, N>::call(out, x, one<T> / scalar);
        else
            loop_scalar<N>(out, x, scalar, std::divides<T>());
    }
};

#endif
