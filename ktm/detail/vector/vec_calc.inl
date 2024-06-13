//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_VEC_CALC_INL_
#define _KTM_VEC_CALC_INL_

#include "vec_calc_fwd.h"
#include "../loop_util.h"
#include "../../type/basic.h"
#include "../../type/vec_fwd.h"

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::add
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        loop_op<N>(ret, x, y, std::plus<T>());
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::add_to_self
{
    using V = vec<N, T>;
    static KTM_INLINE void call(V& x, const V& y) noexcept
    {
        loop_op<N>(x, x, y, std::plus<T>());
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::minus
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        loop_op<N>(ret, x, y, std::minus<T>());
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::minus_to_self
{
    using V = vec<N, T>;
    static KTM_INLINE void call(V& x, const V& y) noexcept
    {
        loop_op<N>(x, x, y, std::minus<T>());
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::mul
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        loop_op<N>(ret, x, y, std::multiplies<T>());
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::mul_to_self
{
    using V = vec<N, T>;
    static KTM_INLINE void call(V& x, const V& y) noexcept
    {
        loop_op<N>(x, x, y, std::multiplies<T>());
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::div
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        loop_op<N>(ret, x, y, std::divides<T>());
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::div_to_self
{
    using V = vec<N, T>;
    static KTM_INLINE void call(V& x, const V& y) noexcept
    {
        loop_op<N>(x, x, y, std::divides<T>());
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::opposite
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N>(ret, x, std::negate<T>());
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::add_scalar
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, T scalar) noexcept
    {
        V ret;
        loop_scalar<N>(ret, x, scalar, std::plus<T>());
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::add_scalar_to_self
{
    using V = vec<N, T>;
    static KTM_INLINE void call(V& x, T scalar) noexcept
    {
        loop_scalar<N>(x, x, scalar, std::plus<T>());
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::minus_scalar
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, T scalar) noexcept
    {
        V ret;
        loop_scalar<N>(ret, x, scalar, std::minus<T>());
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::minus_scalar_to_self
{
    using V = vec<N, T>;
    static KTM_INLINE void call(V& x, T scalar) noexcept
    {
        loop_scalar<N>(x, x, scalar, std::minus<T>());
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::mul_scalar
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, T scalar) noexcept
    {
        V ret;
        loop_scalar<N>(ret, x, scalar, std::multiplies<T>());
        return ret; 
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::mul_scalar_to_self
{
    using V = vec<N, T>;
    static KTM_INLINE void call(V& x, T scalar) noexcept
    {
        loop_scalar<N>(x, x, scalar, std::multiplies<T>());
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::div_scalar
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, T scalar) noexcept
    {   
        if constexpr(std::is_floating_point_v<T>)
            return mul_scalar<N, T>::call(x, one<T> / scalar);
        else
        {
            V ret;
            loop_scalar<N>(ret, x, scalar, std::divides<T>());
            return ret;
        }
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_calc_implement::div_scalar_to_self
{
    using V = vec<N, T>;
    static KTM_INLINE void call(V& x, T scalar) noexcept
    {
        if constexpr(std::is_floating_point_v<T>)
            mul_scalar_to_self<N, T>::call(x, one<T> / scalar);
        else
            loop_scalar<N>(x, x, scalar, std::divides<T>());
    }
};

#endif
