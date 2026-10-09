//  MIT License
//
//  Copyright (c) 2023-2026 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_MAT_FWD_H_
#define _KTM_MAT_FWD_H_

#include <cstddef>
#include <type_traits>

namespace ktm
{

// 本地为支持 1 维而修改：放宽 (Row > 1) && (Col > 1) 为 (Row > 0) && (Col > 0)
template <size_t Row, size_t Col, typename T,
          typename = std::enable_if_t<(Row > 0) && (Col > 0) && std::is_arithmetic_v<T>>>
struct mat;

}

#endif