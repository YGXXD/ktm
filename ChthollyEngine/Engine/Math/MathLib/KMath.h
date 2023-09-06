#ifndef _K_MATH_H_
#define _K_MATH_H_

#include "Chtholly.h"

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
    static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> lerp(T x, T y, T t)
    {
        return x + t * (y - x);
    }
}

#endif