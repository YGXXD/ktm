#ifndef _KTM_QUAT_H_
#define _KTM_QUAT_H_

#include "vec.h"
#include "mat.h"
#include "../traits/type_single_extend.h"
#include "../interface/shared/iarray.h"
#include "../interface/quaternion/iquat_data.h"
#include "../interface/quaternion/iquat_make.h"
#include "../interface/quaternion/iquat_array.h"
#include "../interface/quaternion/iquat_calc.h"

namespace ktm
{
template<typename T>
struct quat<T> : single_extends_t<template_list<iarray, iquat_data, iquat_make, iquat_array, iquat_calc>, quat<T>>
{
    using fater_type = single_extends_t<template_list<iarray, iquat_data, iquat_make, iquat_array, iquat_calc>, quat<T>>;
    using fater_type::fater_type;
};
}

#include "../detail/quaternion/quat_calc.inl"
#include "../detail/quaternion/quat_calc_simd.inl"

#endif