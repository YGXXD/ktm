#ifndef _KTM_QUAT_H_
#define _KTM_QUAT_H_

#include "vec.h"
#include "mat.h"
#include "../interface/shared/iarray.h"
#include "../interface/quaternion/iquat_data.h"
#include "../interface/quaternion/iquat_make.h"
#include "../interface/quaternion/iquat_array.h"
#include "../interface/quaternion/iquat_calc.h"

namespace ktm
{
template<typename T>
struct quat<T> : ktl::SingleExtends_t<ktl::TemplateList<ktm::iarray, ktm::iquat_data, ktm::iquat_make, ktm::iquat_array, ktm::iquat_calc>, quat<T>>
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<ktm::iarray, ktm::iquat_data, ktm::iquat_make, ktm::iquat_array, ktm::iquat_calc>, quat<T>>;
    using Father::Father;
};
}

#include "../detail/quaternion/quat_calc.inl"
#include "../detail/quaternion/quat_calc_simd.inl"

#endif