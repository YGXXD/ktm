//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_ARRAY_CALC_FWD_H_ 
#define _KTM_ARRAY_CALC_FWD_H_

#include <array>
#include <cstddef>

namespace ktm
{
namespace detail
{
namespace array_calc_implement
{

template<typename T, size_t N>
struct add;

template<typename T, size_t N>
struct sub;

template<typename T, size_t N>
struct neg;

template<typename T, size_t N>
struct mul;

template<typename T, size_t N>
struct div;

template<typename T, size_t N>
struct add_scalar;

template<typename T, size_t N>
struct sub_scalar;

template<typename T, size_t N>
struct mul_scalar;

template<typename T, size_t N>
struct div_scalar;

}
}
}

#endif
