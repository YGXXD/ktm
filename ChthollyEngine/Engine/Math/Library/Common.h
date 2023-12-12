#ifndef _COMMON_H_
#define _COMMON_H_

#include "ArtcBase.h"

namespace ktm
{

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<(std::is_arithmetic_v<T> && !std::is_unsigned_v<T>), T> abs(T x) noexcept
{
    return x < 0 ? -x : x;
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> max(T x, T y) noexcept
{
    return x > y ? x : y;
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> min(T x, T y) noexcept
{
    return x < y ? x : y;
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> clamp(T v, T min, T max) noexcept
{
    return ktm::min<T>(ktm::max<T>(v, min), max);
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> pow2(T x) noexcept
{
    return x * x;
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> pow5(T x) noexcept
{
    return pow2(x) * pow2(x) * x;
}

template<size_t N, typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> pow(T x) noexcept
{
    if constexpr(N == 0)
    {
        return one<T>;
    }
    else
    {
        return x * pow<N - 1>(x);
    }
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, bool> near_zero(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
    {
        return abs(x) < 1e-4f;
    }
    else 
    {
        return abs(x) < 1e-8;
    }
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, bool> equal_zero(T x) noexcept
{
    return abs(x) < epsilon<float>;
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> exp(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::expf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::exp(x);
    else 
        return ::expl(x); 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> log(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::logf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::log(x);
    else 
        return ::logl(x); 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> sin(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::sinf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::sin(x);
    else 
        return ::sinl(x); 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> asin(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::asinf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::asin(x);
    else 
        return ::asinl(x); 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> sinc(T x) noexcept
{
    if(equal_zero(x)) return one<T>;

    if constexpr(std::is_same_v<T, float>)
        return ::sinf(x) / x;
    else if constexpr(std::is_same_v<T, double>)
        return ::sin(x) / x;
    else 
        return ::sinl(x) / x; 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> cos(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::cosf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::cos(x);
    else 
        return ::cosl(x); 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> acos(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::acosf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::acos(x);
    else 
        return ::acosl(x); 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> tan(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::tanf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::tan(x);
    else 
        return ::tanl(x); 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> atan(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::atanf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::atan(x);
    else 
        return ::atanl(x); 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> atan2(T x, T y) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::atan2f(x, y);
    else if constexpr(std::is_same_v<T, double>)
        return ::atan2(x, y);
    else 
        return ::atan2l(x, y); 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> floor(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::floorf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::floor(x);
    else 
        return ::floorl(x);
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> ceil(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::ceilf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::ceil(x);
    else 
        return ::ceill(x);
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> round(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::roundf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::round(x);
    else 
        return ::roundl(x);
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> sqrt(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::sqrtf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::sqrt(x);
    else 
        return ::sqrtl(x);
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> mix(T x, T y, T t) noexcept
{
    return x + t * (y - x);
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_exist_same_vs<float, double, T>, T> fast_rsqrt(T x) noexcept
{
    using integral_type = std::select_if_t<std::is_same_v<T, float>, unsigned int, unsigned long long>;
    integral_type i = *reinterpret_cast<const integral_type*>(&x);

    // 雷神三算法u的值为0.0450465
    if constexpr(std::is_same_v<integral_type, unsigned int>)
    {
        i = 0x5f3759df - (i >> 1);
    }
    else // std::is_same_v<integral_type, unsigned long long> 
    {
        i = 0x5fe6eb3bfb58d152 - (i >> 1);
    }
    // 求出平方根倒数近似解
    T ret = *reinterpret_cast<T*>(&i); 
    // 用牛顿迭代法进行迭代增加精度
    ret = ret * (static_cast<T>(1.5) - (static_cast<T>(0.5) * x * ret * ret)); 

    return ret;
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> rsqrt(T x) noexcept
{
    if constexpr(std::is_same_v<T, long double>)
    {
        return one<long double> / ::sqrtl(x);
    }
    else
    {
        using integral_type = std::select_if_t<std::is_same_v<T, float>, unsigned int, unsigned long long>;
        integral_type i = *reinterpret_cast<const integral_type*>(&x);

        if constexpr(std::is_same_v<integral_type, unsigned int>)
        {
            i = 0x5f3759df - (i >> 1);
        }
        else // std::is_same_v<integral_type, unsigned long long> 
        {
            i = 0x5fe6eb3bfb58d152 - (i >> 1);
        }
        T tmp = *reinterpret_cast<T*>(&i); 
        T ret = tmp * (static_cast<T>(1.5) - (static_cast<T>(0.5) * x * tmp * tmp)); 
        while(!equal_zero(ret - tmp))
        {
            tmp = ret;
            ret = tmp * (static_cast<T>(1.5) - (static_cast<T>(0.5) * x * tmp * tmp)); 
        }
        
        return ret;
    }
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> step(T edge, T x) noexcept
{
    return x < edge ? one<T> : zero<T>;
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> smoothstep(T edge0, T edge1, T x) noexcept
{
    const T tmp = ktm::clamp<T>((x - edge0) / (edge1 - edge0), zero<T>, one<T>);
    return tmp * tmp * (static_cast<T>(3) - static_cast<T>(2) * tmp);
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> fract(T x) noexcept
{
    return min(x - ktm::floor<T>(x), one<T>);
} 

}

#endif