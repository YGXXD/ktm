#ifndef _I_QUAT_DATA_H_
#define _I_QUAT_DATA_H_

#include "Math/Library/Definition.h"
#include "Math/Library/Common.h"
#include "Math/Library/Geometry.h"

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

    CHTHOLLY_INLINE T real() const noexcept { return r; }
    CHTHOLLY_INLINE vec<3, T> imag() const noexcept { return vec<3, T>(i, j, k); } 
    CHTHOLLY_INLINE T angle() const noexcept { return static_cast<T>(2) * atan2(length(imag()), r); }
    CHTHOLLY_INLINE vec<3, T> axis() const noexcept { return normalize(imag()); } 
};
}

#endif