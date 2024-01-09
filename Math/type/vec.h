#ifndef _KTM_VEC_H_
#define _KTM_VEC_H_

#include "basic.h"
#include "../interface/shared/iarray.h"
#include "../interface/vector/ivec_data.h"
#include "../interface/vector/ivec_array.h"
#include "../interface/vector/ivec_calc.h"

namespace ktm
{

template<size_t N, typename T>
struct vec<N, T> : ktl::SingleExtends_t<ktl::TemplateList<ktm::iarray, ktm::ivec_data, ktm::ivec_array, ktm::ivec_calc>, vec<N, T>> 
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<ktm::iarray, ktm::ivec_data, ktm::ivec_array, ktm::ivec_calc>, vec<N, T>>; 
    using Father::Father;
};

}

#include "../detail/vector/vec_data.inl"
#include "../detail/vector/vec_data_simd.inl"
#include "../detail/vector/vec_calc.inl"
#include "../detail/vector/vec_calc_simd.inl"

#endif