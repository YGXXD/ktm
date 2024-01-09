#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vector.h"
#include "Math/interface/ICommon/IArray.h"
#include "Math/interface/IMatrix/IMatData.h"
#include "Math/interface/IMatrix/IMatMake.h"
#include "Math/interface/IMatrix/IMatArray.h"
#include "Math/interface/IMatrix/IMatOpt.h"

namespace ktm
{
template<size_t Row, size_t Col, typename T>
struct mat<Row, Col, T> : ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IMatData, ktm::IMatMake, ktm::IMatArray, ktm::IMatOpt>, mat<Row, Col, T>>
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IMatData, ktm::IMatMake, ktm::IMatArray, ktm::IMatOpt>, mat<Row, Col, T>>;
    using Father::Father;
};
}

#include "Math/detail/Matrix/MatOpt.inl"
#include "Math/detail/Matrix/MatOptSimd.inl"

#endif