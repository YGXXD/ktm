//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_EXPONENTIAL_H_
#define _KTM_EXPONENTIAL_H_

#include <cmath>
#include "../setup.h"
#include "../type/basic.h"
#include "../traits/type_traits_math.h"

namespace ktm
{

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> sqrt(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::sqrtf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::sqrt(x);
    else 
        return ::sqrtl(x);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> rsqrt(T x) noexcept
{
    return one<T> / sqrt(x);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> recip(T x) noexcept
{
    return one<T> / x;
}

template<size_t N, typename T>
KTM_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> pow(T x) noexcept
{
    if constexpr(N == 0)
        return one<T>;
    else
        return x * pow<N - 1>(x);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> pow2(T x) noexcept
{
    return pow<2>(x);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> pow5(T x) noexcept
{
    return pow<5>(x);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> exp(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::expf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::exp(x);
    else 
        return ::expl(x); 
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> exp2(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::exp2f(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::exp2(x);
    else 
        return ::exp2l(x); 
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> expm1(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::expm1f(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::expm1(x);
    else 
        return ::expm1l(x); 
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> log(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::logf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::log(x);
    else 
        return ::logl(x); 
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> log10(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::log10f(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::log10(x);
    else 
        return ::log10l(x); 
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> log2(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::log2f(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::log2(x);
    else 
        return ::log2l(x); 
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> log1p(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::log1pf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::log1p(x);
    else 
        return ::log1pl(x); 
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> logb(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::logbf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::logb(x);
    else 
        return ::logbl(x); 
}

namespace fast
{
// 雷神三算法: u = 0.0450465
template<typename T>
KTM_INLINE std::enable_if_t<is_listing_type_v<type_list<float, double>, T>, T> sqrt(T x) noexcept
{
    using integral_type = std::select_if_t<std::is_same_v<T, float>, unsigned int, unsigned long long>;
    integral_type i = *reinterpret_cast<const integral_type*>(&x);
    if constexpr(std::is_same_v<integral_type, unsigned int>)
        i = 0x1fbd1df5 + (i >> 1);
    else
        i = 0x1ff7a3bea91d9b1b + (i >> 1);
    T ret = *reinterpret_cast<T*>(&i); 
    return (ret + x / ret) * static_cast<T>(0.5);
}

template<typename T>
KTM_INLINE std::enable_if_t<is_listing_type_v<type_list<float, double>, T>, T> rsqrt(T x) noexcept
{
    using integral_type = std::select_if_t<std::is_same_v<T, float>, unsigned int, unsigned long long>;
    integral_type i = *reinterpret_cast<const integral_type*>(&x);
    if constexpr(std::is_same_v<integral_type, unsigned int>)
        i = 0x5f3759df - (i >> 1);
    else
        i = 0x5fe6eb3bfb58d152 - (i >> 1);
    T ret = *reinterpret_cast<T*>(&i); 
    return ret * (static_cast<T>(1.5) - (static_cast<T>(0.5) * x * ret * ret));
}

template<typename T>
KTM_INLINE std::enable_if_t<is_listing_type_v<type_list<float, double>, T>, T> recip(T x) noexcept
{
    using integral_type = std::select_if_t<std::is_same_v<T, float>, unsigned int, unsigned long long>;
    integral_type i = *reinterpret_cast<const integral_type*>(&x);
    if constexpr(std::is_same_v<integral_type, unsigned int>)
        i = 0x7ef477d5 - i;
    else
        i = 0x7fde8efaa4766c6e - i;
    T ret = *reinterpret_cast<T*>(&i); 
    return ret * (static_cast<T>(2) - x * ret);
}

}

}

#endif