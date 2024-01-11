#ifndef _KTM_VEC_H_
#define _KTM_VEC_H_

#include "basic.h"
#include "../traits/type_single_extend.h"
#include "../interface/shared/iarray.h"
#include "../interface/vector/ivec_data.h"
#include "../interface/vector/ivec_array.h"
#include "../interface/vector/ivec_calc.h"

namespace ktm
{

template<size_t N, typename T>
struct vec<N, T> : single_extends_t<template_list<iarray, ivec_data, ivec_array, ivec_calc>, vec<N, T>> 
{
    using fater_type = single_extends_t<template_list<iarray, ivec_data, ivec_array, ivec_calc>, vec<N, T>>; 
    using fater_type::fater_type;
};

}

#include "../detail/vector/vec_data.inl"
#include "../detail/vector/vec_data_simd.inl"
#include "../detail/vector/vec_calc.inl"
#include "../detail/vector/vec_calc_simd.inl"

#endif