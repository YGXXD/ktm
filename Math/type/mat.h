#ifndef _KTM_MAT_H_
#define _KTM_MAT_H_

#include "vec.h"
#include "../interface/shared/iarray.h"
#include "../interface/matrix/imat_data.h"
#include "../interface/matrix/imat_make.h"
#include "../interface/matrix/imat_array.h"
#include "../interface/matrix/imat_calc.h"

namespace ktm
{
template<size_t Row, size_t Col, typename T>
struct mat<Row, Col, T> : ktl::SingleExtends_t<ktl::TemplateList<ktm::iarray, ktm::imat_data, ktm::imat_make, ktm::imat_array, ktm::imat_calc>, mat<Row, Col, T>>
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<ktm::iarray, ktm::imat_data, ktm::imat_make, ktm::imat_array, ktm::imat_calc>, mat<Row, Col, T>>;
    using Father::Father;
};
}

#include "../detail/matrix/mat_calc.inl"
#include "../detail/matrix/mat_calc_simd.inl"

#endif