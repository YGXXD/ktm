#ifndef _I_MAT_ARRAY_H_
#define _I_MAT_ARRAY_H_

#include "Math/MathType/BaseType.h"

namespace ktm
{
template<class Father, class Child>
struct IMatArray;

template<class Father, size_t Col, size_t Raw, typename T>
struct IMatArray<Father, mat<Col, Raw, T>> : Father
{
    using Father::Father;
    using array_type = std::array<vec<Col, T>, Raw>;
};
}

#endif