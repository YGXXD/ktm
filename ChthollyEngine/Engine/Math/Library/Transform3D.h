#ifndef _TRANSFORM_3D_H_
#define _TRANSFORM_3D_H_

#include "Matrix.h"
#include "Vector.h"
#include "VecGeometry.h"

namespace ktm
{

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> view_look_at(const vec<3, T>& eye_pos, const vec<3, T>& focus_pos, const vec<3, T>& up) noexcept
{
    vec<3, T> z = normalize(focus_pos - eye_pos);
    vec<3, T> x = normalize(cross(up, z));
    vec<3, T> y = cross(z, x);
    T wx = -dot(eye_pos, x);
    T wy = -dot(eye_pos, y);
    T wz = -dot(eye_pos, z);
    return mat<4, 4, T>({ x[0], y[0], z[0], zero<T> },
                        { x[1] ,y[1], z[1], zero<T> },
                        { x[2], y[2], z[2], zero<T> },
                        { wx, wy, wz, one<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> perspective(T fov_radians, T aspect, T znear, T zfar) noexcept
{
    T ys = one<T> / tan(fov_radians * static_cast<T>(0.5));
    T xs = ys / aspect;
    T zs = zfar / ( znear - zfar );
    return mat<4, 4, T>({ xs, zero<T>, zero<T>, zero<T> },
                        { zero<T>, ys, zero<T>, zero<T> },
                        { zero<T>, zero<T>, -zs, one<T> },
                        { zero<T>, zero<T>, znear * zs, zero<T> }); 
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> ortho(T left, T right, T top, T bottom, T znear, T zfar) noexcept
{
    T dx = right - left;
    T dy = top - bottom;
    T dz = zfar - znear;
    return mat<4, 4, T>({ static_cast<T>(2) / dx, zero<T>, zero<T>, zero<T> },
                        { zero<T>, static_cast<T>(2) / dy, zero<T>, zero<T> },
                        { zero<T>, zero<T>, one<T> / dz, zero<T> },
                        { (right + left) / (-dx), (top + bottom) / (-dy), znear / (-dz), one<T>});
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> rotate_x(T angle_radians) noexcept
{
    return mat<4, 4, T>({ one<T>, zero<T>, zero<T>, zero<T> },
                        { zero<T>, cos(angle_radians), sin(angle_radians), zero<T> },
                        { zero<T>, -sin(angle_radians), cos(angle_radians), zero<T> },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> rotate_y(T angle_radians) noexcept
{
    return mat<4, 4, T>({ cos(angle_radians), zero<T>, -sin(angle_radians), zero<T> },
                        { zero<T>, one<T>, zero<T>, zero<T> },
                        { sin(angle_radians), zero<T>, cos(angle_radians), zero<T> },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> rotate_z(T angle_radians) noexcept
{
    return mat<4, 4, T>({ cos(angle_radians), sin(angle_radians), zero<T>, zero<T> },
                        { -sin(angle_radians), cos(angle_radians), zero<T>, zero<T> },
                        { zero<T>, zero<T>, one<T>, zero<T> },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}

namespace detail
{
namespace transform_3d
{
template<typename T>
CHTHOLLY_NOINLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> rotate_normal(T sin_theta, T cos_theta, const vec<3, T>& normal) noexcept
{
	T one_minus_cos_theta = one<T> - cos_theta;
    T xx_one_minus_cos = normal[0] * normal[0] * one_minus_cos_theta;
    T xy_one_minus_cos = normal[0] * normal[1] * one_minus_cos_theta;
    T xz_one_minus_cos = normal[0] * normal[2] * one_minus_cos_theta;
    T yy_one_minus_cos = normal[1] * normal[1] * one_minus_cos_theta;
    T yz_one_minus_cos = normal[1] * normal[2] * one_minus_cos_theta;
    T zz_one_minus_cos = normal[2] * normal[2] * one_minus_cos_theta;
    T x_sin = normal[0] * sin_theta, y_sin = normal[1] * sin_theta, z_sin = normal[2] * sin_theta; 
	return mat<4, 4, T>({ xx_one_minus_cos + cos_theta, xy_one_minus_cos + z_sin, xz_one_minus_cos - y_sin, zero<T> },
                        { xy_one_minus_cos - z_sin, yy_one_minus_cos + cos_theta, yz_one_minus_cos + x_sin, zero<T> },
                        { xz_one_minus_cos + y_sin, yz_one_minus_cos - x_sin, zz_one_minus_cos + cos_theta, zero<T> },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}
}
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> rotate_axis(T angle, const vec<3, T>& axis) noexcept
{
	return detail::transform_3d::rotate_normal(sin(angle), cos(angle), axis);
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> rotate_from_to(const vec<3, T>& from, const vec<3, T>& to) noexcept
{
    T cos_theta = dot(from, to);
    T sin_theta = sqrt(one<T> - cos_theta * cos_theta);
	return detail::transform_3d::rotate_normal(sin_theta, cos_theta, normalize(cross(from, to)));
}

template<typename T>
CHTHOLLY_NOINLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> rotate_any_axis(T angle, const vec<3, T>& axis_start, const vec<3, T>& axis) noexcept
{
	T cos_theta = cos(angle);
	T sin_theta = sin(angle);
	T one_minus_cos_theta = one<T> - cos_theta;
    T xx_one_minus_cos = axis[0] * axis[0] * one_minus_cos_theta;
    T xy_one_minus_cos = axis[0] * axis[1] * one_minus_cos_theta;
    T xz_one_minus_cos = axis[0] * axis[2] * one_minus_cos_theta;
    T yy_one_minus_cos = axis[1] * axis[1] * one_minus_cos_theta;
    T yz_one_minus_cos = axis[1] * axis[2] * one_minus_cos_theta;
    T zz_one_minus_cos = axis[2] * axis[2] * one_minus_cos_theta;
    T x_sin = axis[0] * sin_theta, y_sin = axis[1] * sin_theta, z_sin = axis[2] * sin_theta;
    T a = axis_start[0], b = axis_start[1], c = axis_start[2];
	return mat<4, 4, T>({ xx_one_minus_cos + cos_theta, xy_one_minus_cos + z_sin, xz_one_minus_cos - y_sin, zero<T> },
                        { xy_one_minus_cos - z_sin, yy_one_minus_cos + cos_theta, yz_one_minus_cos + x_sin, zero<T> },
                        { xz_one_minus_cos + y_sin, yz_one_minus_cos - x_sin, zz_one_minus_cos + cos_theta, zero<T> },
                        { a * (one_minus_cos_theta - xx_one_minus_cos) + b * (z_sin - xy_one_minus_cos) - c * (y_sin + xz_one_minus_cos),
                          b * (one_minus_cos_theta - yy_one_minus_cos) + c * (x_sin - yz_one_minus_cos) - a * (z_sin + xy_one_minus_cos),
                          c * (one_minus_cos_theta - zz_one_minus_cos) + a * (y_sin - xz_one_minus_cos) - b * (x_sin + yz_one_minus_cos),
                          one<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> translate(const vec<3, T>& v) noexcept
{
    return mat<4, 4, T>({ one<T>, zero<T>, zero<T>, zero<T> },
                        { zero<T>, one<T>, zero<T>, zero<T> },
                        { zero<T>, zero<T>, one<T>, zero<T> },
                        { v[0], v[1], v[2], one<T> });
}

template<typename T>
CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<4, 4, T>> scale(const vec<3, T>& v) noexcept
{
    return mat<4, 4, T>({ v[0], zero<T>, zero<T>, zero<T> },
                        { zero<T>, v[1], zero<T>, zero<T> },
                        { zero<T>, zero<T>, v[2], zero<T> },
                        { zero<T>, zero<T>, zero<T>, one<T> });
}

}

#endif