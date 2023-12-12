#ifndef _I_MAT_ARRAY_H_
#define _I_MAT_ARRAY_H_

#include "Math/Library/ArtcBase.h"

namespace ktm
{
template<class Father, class Child>
struct IMatArray;

template<class Father, size_t Row, size_t Col, typename T>
struct IMatArray<Father, mat<Row, Col, T>> : Father
{
    using Father::Father;
    using array_type = std::array<vec<Col, T>, Row>;
};
}

#endif