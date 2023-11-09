#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Definition.h"
#include "Math/Interface/ICommon/IArray.h"
#include "Math/Interface/IVector/IVecOpt.h"
#include "Math/Interface/IVector/IVecData.h"
#include "Math/Interface/IVector/IVecArray.h"

namespace ktm
{

template<size_t N, typename T>
struct vec<N, T> : ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IVecData, ktm::IVecArray, ktm::IVecOpt>, vec<N, T>> 
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IVecData, ktm::IVecArray, ktm::IVecOpt>, vec<N, T>>; 
    using Father::Father;
};

}

#include "Math/Detail/Vector.inl"
#include "Math/Detail/VectorSimd.inl"
#endif