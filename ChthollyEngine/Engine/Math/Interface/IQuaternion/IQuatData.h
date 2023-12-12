#ifndef _I_QUAT_DATA_H_
#define _I_QUAT_DATA_H_

#include "Math/Library/ArtcBase.h"
#include "Math/Library/ArtcCommon.h"
#include "Math/Library/VecGeometry.h"

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
        struct { T i, j, k, r; };
    };
    constexpr IQuatData(T x, T y, T z, T w) noexcept : i(x), j(y), k(z), r(w) { }
    IQuatData(const vec<4, T>& vec) noexcept : vector(vec) { }

    CHTHOLLY_INLINE T real() const noexcept { return r; }
    CHTHOLLY_INLINE vec<3, T> imag() const noexcept { return vec<3, T>(i, j, k); } 
    CHTHOLLY_INLINE T angle() const noexcept { return static_cast<T>(2) * atan2(length(imag()), real()); }
    CHTHOLLY_INLINE vec<3, T> axis() const noexcept { return normalize(imag()); } 
};
}

#endif