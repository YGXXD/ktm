#ifndef _TRANSFORM_3D_H_
#define _TRANSFORM_3D_H_

#include "Matrix.h"
#include "Vector.h"
#include "VecGeometry.h"

namespace ktm
{

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> view_look_at(const vec<3, T>& eye_pos, const vec<3, T>& focus_pos, const vec<3, T>& up)
{
    vec<3, T> z = normalize(focus_pos - eye_pos);
    vec<3, T> x = normalize(cross(up, z));
    vec<3, T> y = cross(z, x);
    T wx = -dot(eye_pos, x);
    T wy = -dot(eye_pos, y);
    T wz = -dot(eye_pos, z);

    return mat<4, 4, T>({ x[0], x[1], x[2], wx },
                        { y[0] ,y[1], y[2], wy },
                        { z[0], z[1], z[2], wz },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> perspective(T fov_radians, T aspect, T znear, T zfar)
{
    T ys = one<T> / tan(fov_radians * static_cast<T>(0.5));
    T xs = ys / aspect;
    T zs = zfar / ( znear - zfar );
    return mat<4, 4, T>({ xs, zero<T>, zero<T>, zero<T> },
                        { zero<T>, ys, zero<T>, zero<T> },
                        { zero<T>, zero<T>, -zs, znear * zs },
                        { zero<T>, zero<T>, one<T>, zero<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> ortho(T left, T right, T top, T bottom, T znear, T zfar)
{
    T dx = right - left;
    T dy = top - bottom;
    T dz = zfar - znear;
    return mat<4, 4, T>({ static_cast<T>(2) / dx, zero<T>, zero<T>, (right + left) / (-dx) },
                        { zero<T>, static_cast<T>(2) / dy, zero<T>, (top + bottom) / (-dy) },
                        { zero<T>, zero<T>, one<T> / dz, znear / (-dz) },
                        { zero<T>, zero<T>, zero<T>, one<T>});
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> rotate_x(float angle_radians)
{
    return mat<4, 4, T>({ one<T>, zero<T>, zero<T>, zero<T> },
                        { zero<T>, cos(angle_radians), -sin(angle_radians), zero<T> },
                        { zero<T>, sin(angle_radians), cos(angle_radians), zero<T> },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> rotate_y(float angle_radians)
{
    return mat<4, 4, T>({ cos(angle_radians), zero<T>, sin(angle_radians), zero<T> },
                        { zero<T>, one<T>, zero<T>, zero<T> },
                        { -sin(angle_radians), zero<T>, cos(angle_radians), zero<T> },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> rotate_z(float angle_radians)
{
    return mat<4, 4, T>({ cos(angle_radians), -sin(angle_radians), zero<T>, zero<T> },
                        { sin(angle_radians), cos(angle_radians), zero<T>, zero<T> },
                        { zero<T>, zero<T>, one<T>, zero<T> },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> translate(const vec<3, T>& v)
{
    return mat<4, 4, T>({ one<T>, zero<T>, zero<T>, v[0] },
                        { zero<T>, one<T>, zero<T>, v[1] },
                        { zero<T>, zero<T>, one<T>, v[2] },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> scale(const vec<3, T>& v)
{
    return mat<4, 4, T>({ v[0], zero<T>, zero<T>, zero<T> },
                        { zero<T>, v[1], zero<T>, zero<T> },
                        { zero<T>, zero<T>, v[2], zero<T> },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}

}

#endif