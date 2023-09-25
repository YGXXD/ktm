#ifndef _I_MAT_ARRAY_H_
#define _I_MAT_ARRAY_H_

#include "Math/MathType/BaseType.h"

namespace ktm
{
template<class Father, class Child>
struct IMatArray;

template<class Father, size_t Col, size_t Row, typename T>
struct IMatArray<Father, mat<Col, Row, T>> : Father
{
    using Father::Father;
    using array_type = std::array<vec<Col, T>, Row>;
};
}

#endif