#ifndef _K_MATH_H_
#define _K_MATH_H_

#include "Math/MathType/BaseType.h"

namespace ktm
{
template<typename T>
static CHTHOLLY_INLINE std::enable_if_t<(std::is_arithmetic_v<T> && !std::is_unsigned_v<T>), T> abs(T x)
{
    return x < 0 ? -x : x;
}

template<typename T>
static CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> max(T x, T y)
{
    return x > y ? x : y;
}

template<typename T>
static CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> min(T x, T y)
{
    return x < y ? x : y;
}

template<typename T>
static CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> clamp(T v, T min, T max)
{
    return v < min ? min : v > max ? max : v;
}

template<typename T>
static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> mix(T x, T y, T t)
{
    return x + t * (y - x);
}

template<typename T>
static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> rsqrt(T x)
{
    using integral_type = std::select_if_t<std::is_same_v<T, float>, unsigned int, unsigned long long>;
    T a = x;
    integral_type i = *reinterpret_cast<integral_type*>(&a);

    //原算法u的值为0.0450465
    if constexpr(std::is_same_v<integral_type, unsigned int>)
    {
        i = 0x5f3759df - (i >> 1);
    }
    else // std::is_same_v<integral_type, unsigned long long> 
    {
        i = 0x5fe6eb3bfb58d152 - (i >> 1);
    }
    //求出平方根倒数近似解
    a = *reinterpret_cast<T*>(&i); 
    
    //用牛顿迭代法进行迭代增加精度
    a = a * (static_cast<T>(1.5) - (static_cast<T>(0.5) * x * a * a));
    // a = a * (static_cast<T>(1.5) - (static_cast<T>(0.5) * x * a * a));
        
    return a;
}

template<typename T>
static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> step(T edge, T x)
{
    return x < edge ? one<T> : zero<T>;
}

template<typename T>
static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> smoothstep(T edge0, T edge1, T x)
{
    const T tmp = clamp<T>((x - edge0) / (edge1 - edge0), zero<T>, one<T>);
    return tmp * tmp * (static_cast<T>(3) - static_cast<T>(2) * tmp);
}

// template<typename T>
// static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> floor(T x)
// {
//     using logic_type = std::select_if_t<std::is_same_v<T, float>, unsigned int, unsigned long long>;
//     if constexpr(std::is_same_v<T, float>)
//     {
//         int exp = (*reinterpret_cast<logic_type*>(&x) & 0x7f800000) >> 23;
//     }
//     else // std::is_same_v<T, double>  
//     {
//         int exp = ((*reinterpret_cast<logic_type*>(&x) & 0x7ff0000000000000) >> 52) - 1023;
//         if(exp < 0)
//         {
//             return exp < 0 ? -one<T> : zero<T>;
//         }
//         else if(exp > 52)
//         {
//             return x;
//         }
//         else 
//         {
//             logic_type mask = 0x000fffffffffffff >> exp;
//             if((*reinterpret_cast<logic_type*>(&x) & mask) == 0)
//             {
//                 return x;
//             }
//             else 
//             {
//                 logic_type ret = *reinterpret_cast<logic_type*>(&x) & (~mask);
//                 return *reinterpret_cast<T*>(&ret) - step(zero<T>, x);
//             } 
//         }
//     }
// }
}

#endif