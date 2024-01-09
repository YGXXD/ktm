#ifndef _I_VEC_ARRAY_H_
#define _I_VEC_ARRAY_H_

#include "../../type/basic.h"
#include <array>

namespace ktm
{

template<class Father, class Child>
struct IVecArray;

template<class Father, size_t N, typename T>
struct IVecArray<Father, vec<N, T>> : Father
{
    using Father::Father;
    using array_type = std::array<T, N>;
};
}

#endif