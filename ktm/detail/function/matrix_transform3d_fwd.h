//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_MATRIX_TRANSFORM_3D_FWD_H_
#define _KTM_MATRIX_TRANSFORM_3D_FWD_H_

#include "../../setup.h"
#include "../../type/vec_fwd.h"
#include "../../type/mat_fwd.h"
#include "../../traits/type_traits_ext.h"

namespace ktm
{
namespace detail
{
namespace matrix_transform3d_implement
{

template <typename T, typename StartV>
KTM_NOINLINE std::enable_if_t<std::is_floating_point_v<T> && std::is_exist_same_vs<StartV, vec<3, T>, int>>
rotate3d_normal(mat<4, 4, T>& out, T sin_theta, T cos_theta, const vec<3, T>& normal, StartV&& normal_start) noexcept;

}
} // namespace detail
} // namespace ktm

#endif