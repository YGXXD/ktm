#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vector.h"
#include "Math/Interface/ICommon/IArray.h"
#include "Math/Interface/IMatrix/IMatData.h"
#include "Math/Interface/IMatrix/IMatMake.h"
#include "Math/Interface/IMatrix/IMatArray.h"
#include "Math/Interface/IMatrix/IMatOpt.h"

namespace ktm
{
template<size_t Row, size_t Col, typename T>
struct mat<Row, Col, T> : ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IMatData, ktm::IMatMake, ktm::IMatArray, ktm::IMatOpt>, mat<Row, Col, T>>
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<ktm::IArray, ktm::IMatData, ktm::IMatMake, ktm::IMatArray, ktm::IMatOpt>, mat<Row, Col, T>>;
    using Father::Father;
};
}

#include "Math/Detail/Matrix/Matrix.inl"
#include "Math/Detail/Matrix/MatrixSimd.inl"

#endif