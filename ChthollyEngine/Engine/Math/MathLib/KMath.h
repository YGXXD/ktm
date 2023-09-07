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
    static CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> clamp(T min, T max, T v)
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
        using integral_type = std::select_if_t<std::is_same_v<T, float>, int, long long>;
        T a = x;
        integral_type i = *reinterpret_cast<integral_type*>(&a);

        //原算法u的值为0.0450465
        if constexpr(std::is_same_v<integral_type, int>)
        {
            i = 0x5f3759df - (i >> 1);
        }
        else // std::is_same_v<integral_type, long long> 
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
    static CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> step(T edge, T x)
    {
        return x < edge ? one<T> : zero<T>;
    }
}

#endif