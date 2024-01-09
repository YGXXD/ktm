#ifndef _KTM_VEC_H_
#define _KTM_VEC_H_

#include "basic.h"
#include "Math/interface/ICommon/IArray.h"
#include "Math/interface/IVector/IVecOpt.h"
#include "Math/interface/IVector/IVecData.h"
#include "Math/interface/IVector/IVecArray.h"

namespace ktm
{

template<size_t N, typename T>
struct vec<N, T> : ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IVecData, ktm::IVecArray, ktm::IVecOpt>, vec<N, T>> 
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IVecData, ktm::IVecArray, ktm::IVecOpt>, vec<N, T>>; 
    using Father::Father;
};

}

#include "Math/detail/Vector/VecData.inl"
#include "Math/detail/Vector/VecDataSimd.inl"
#include "Math/detail/Vector/VecOpt.inl"
#include "Math/detail/Vector/VecOptSimd.inl"

#endif