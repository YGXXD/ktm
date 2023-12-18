#ifndef _I_QUAT_MAKE_H_
#define _I_QUAT_MAKE_H_

#include "Math/Library/ArtcBase.h"
#include "Math/Library/ArtcCommon.h"
#include "Math/Library/VecGeometry.h"
#include "Math/Library/MatCommon.h"

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
        return quat<T>(zero<T>, zero<T>, zero<T>, one<T>);
    }

    static CHTHOLLY_INLINE quat<T> real_imag(T real, const vec<3, T>& imag) noexcept
    {
        return quat<T>(imag.x, imag.y, imag.z, real);
    } 

    static CHTHOLLY_INLINE quat<T> angle_axis(T angle, const vec<3, T>& axis) noexcept
    {
        return angle_axis_nomal(angle, normalize(axis));
    }
 
    static CHTHOLLY_INLINE quat<T> angle_axis_nomal(T angle, const vec<3, T>& axis) noexcept
    {
        T sin_0p5angle = sin(angle * static_cast<T>(0.5));
        return quat<T>(sin_0p5angle * axis[0], sin_0p5angle * axis[1], sin_0p5angle * axis[2], cos(angle * static_cast<T>(0.5)));
    }

    static CHTHOLLY_INLINE quat<T> from_to(const vec<3, T>& from, const vec<3, T>& to) noexcept
    {
        return from_to_nomal(normalize(from), normalize(to));
    }
    static CHTHOLLY_NOINLINE quat<T> from_to_nomal(const vec<3, T>& from, const vec<3, T>& to) noexcept
    {
        if (dot(from, to) >= 0) {
            return from_to_less_0p5pi(from, to); 
        }
        
        vec<3, T> half = from + to;
        
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

    static CHTHOLLY_INLINE quat<T> from_matrix(const mat<4, 4, T>& m) noexcept
    {
        const mat<3, 3, T>* m33_ptr = reinterpret_cast<const mat<3, 3, T>*>(&m);
        return from_matrix(*m33_ptr);
    }

    static CHTHOLLY_NOINLINE quat<T> from_matrix(const mat<3, 3, T>& m) noexcept
    {
        T m_trace = trace(m);
        if (m_trace >= zero<T>)
        {
            T r = static_cast<T>(2) * sqrt(one<T> + m_trace);
            T rinv = one<T> / r;
            return quat<T>(rinv * (m[1][2] - m[2][1]), rinv * (m[2][0] - m[0][2]), rinv * (m[0][1] - m[1][0]),
                           r / static_cast<T>(4));
        }
        else if (m[0][0] >= m[1][1] && m[0][0] >= m[2][2])
        {
            T r = static_cast<T>(2) * sqrt(one<T> - m[1][1] - m[2][2] + m[0][0]);
            T rinv = one<T> / r;
            return quat<T>(r / static_cast<T>(4), rinv * (m[0][1] + m[1][0]), rinv * (m[0][2] + m[2][0]),
                           rinv * (m[1][2] - m[2][1]));
        }
        else if (m[1][1] >= m[2][2])
        {
            T r = static_cast<T>(2) * sqrt(one<T> - m[0][0] - m[2][2] + m[1][1]);
            T rinv = one<T> / r;
            return quat<T>(rinv * (m[0][1] + m[1][0]), r / static_cast<T>(4), rinv * (m[1][2] + m[2][1]),
                           rinv * (m[2][0] - m[0][2]));
        }
        else
        {
            T r = static_cast<T>(2) * sqrt(one<T> - m[0][0] - m[1][1] + m[2][2]);
            T rinv = one<T> / r;
            return quat<T>(rinv * (m[0][2] + m[2][0]), rinv * (m[1][2] + m[2][1]), r / static_cast<T>(4),
                           rinv * (m[0][1] - m[1][0]));
        }
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