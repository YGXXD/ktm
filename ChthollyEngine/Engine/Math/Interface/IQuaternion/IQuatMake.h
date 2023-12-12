#ifndef _I_QUAT_MAKE_H_
#define _I_QUAT_MAKE_H_

#include "Math/Library/ArtcBase.h"
#include "Math/Library/ArtcCommon.h"
#include "Math/Library/VecGeometry.h"

namespace ktm
{
template<class Father, class Child>
struct IQuatMake;

template<class Father, typename T>
struct IQuatMake<Father, quat<T>> : Father
{
    using Father::Father;

    static CHTHOLLY_INLINE quat<T> identity() noexcept
    {
        return quat<T>(one<T>, zero<T>, zero<T>, zero<T>);
    }

    static CHTHOLLY_INLINE quat<T> real_imag(T real, const vec<3, T>& imag) noexcept
    {
        return quat<T>(real, imag.x, imag.y, imag.z);
    } 

    static CHTHOLLY_INLINE quat<T> angle_axis(T angle, const vec<3, T>& axis) noexcept
    {
        T sin_0p5angle = sin(angle * static_cast<T>(0.5));
        return quat<T>(cos(angle * static_cast<T>(0.5)), sin_0p5angle * axis[0], sin_0p5angle * axis[1], sin_0p5angle * axis[2]);
    }

    static CHTHOLLY_NOINLINE quat<T> from_to(const vec<3, T>& from, const vec<3, T>& to) noexcept
    {
        if (dot(from, to) >= 0) {
            return from_to_less_0p5pi(from, to); 
        }
        
        vec<3, T> half = normalize(from) + normalize(to);
        
        if (equal_zero(length_squared(half))) 
        {
            vec<3, T> abs_from = abs(from);
            if (abs_from.x <= abs_from.y && abs_from.x <= abs_from.z)
                return real_imag(zero<T>, normalize(cross(from, vec<3, T>(one<T>, zero<T>, zero<T>)))); 
            else if (abs_from.y <= abs_from.z)
                return real_imag(zero<T>, normalize(cross(from, vec<3, T>(zero<T>, one<T>, zero<T>)))); 
            else
                return real_imag(zero<T>, normalize(cross(from, vec<3, T>(zero<T>, zero<T>, one<T>)))); 
        }

        half = normalize(half);
        return from_to_less_0p5pi(from, half) * from_to_less_0p5pi(half, to);
    }

private:
    static CHTHOLLY_INLINE quat<T> from_to_less_0p5pi(const vec<3, T>& from, const vec<3, T>& to)
    {
        // 计算向量旋转夹角小于二分之pi的四元数
        vec<3, T> half = normalize(from + to);
        return real_imag(dot(from, half), cross(from, half));
    }
};

}

#endif