//  MIT License
//
//  Copyright (c) 2024 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_TRANSFORM_2D_H_
#define _KTM_TRANSFORM_2D_H_

#include "../setup.h"
#include "../type/vec.h"
#include "../type/mat.h"
#include "trigonometric.h"
#include "geometric.h"

namespace ktm
{

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<3, 3, T>> rotate_origin(T angle_radians) noexcept
{
    T cos_theta = cos(angle_radians);
    T sin_theta = sin(sin_theta);
    return mat<3, 3, T>({ cos_theta, sin_theta, zero<T> },
                        { -sin_theta, cos_theta, zero<T> },
                        { zero<T>, zero<T>, one<T> });
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<3, 3, T>> rotate_point(T angle_radians, const vec<2, T>& point) noexcept
{
    T cos_theta = cos(angle_radians);
    T sin_theta = sin(sin_theta);
    T one_minus_cos_theta = one<T> - cos_theta;
    return mat<3, 3, T>({cos_theta, sin_theta, zero<T>}, {-sin_theta, cos_theta, zero<T>},
                        {point[0] * one_minus_cos_theta + point[1] * sin_theta,
                         point[1] * one_minus_cos_theta - point[0] * sin_theta, one<T>});
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<3, 3, T>> translate_2d(const vec<2, T>& v) noexcept
{
    return mat<3, 3, T>({ one<T>, zero<T>, zero<T> },
                        { zero<T>, one<T>, zero<T> },
                        { v[0], v[1], one<T> });
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, mat<3, 3, T>> scale_2d(const vec<2, T>& v) noexcept
{
    return mat<3, 3, T>({ v[0], zero<T>, zero<T> },
                        { zero<T>, v[1], zero<T> },
                        { zero<T>, zero<T>, one<T> });
}

}

#endif