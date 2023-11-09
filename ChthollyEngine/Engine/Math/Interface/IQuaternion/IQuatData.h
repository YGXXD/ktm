#ifndef _I_QUAT_DATA_H_
#define _I_QUAT_DATA_H_

#include "Math/Library/Definition.h"

namespace ktm
{
template<class Father, class Child>
struct IQuatData;

template<class Father, typename T>
struct alignas(sizeof(vec<4, T>)) IQuatData<Father, quat<T>> : Father
{
    using Father::Father;
    union
    {
        struct { vec<4, T> vector; };
        struct { T r, i, j, k; };
    };
    constexpr IQuatData(T w, T x, T y, T z) noexcept : r(w), i(x), j(y), k(z) { }
    IQuatData(const vec<4, T>& vec) noexcept : vector(vec) { }
};
}

#endif