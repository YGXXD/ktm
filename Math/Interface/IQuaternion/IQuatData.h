#ifndef _I_QUAT_DATA_H_
#define _I_QUAT_DATA_H_

#include "../../type/basic.h"
#include "Math/function/ArtcCommon.h"
#include "Math/function/VecGeometry.h"

namespace ktm
{
template<class Father, class Child>
struct IQuatData;

template<class Father, typename T>
struct IQuatData<Father, quat<T>> : Father
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
    CHTHOLLY_INLINE mat<3, 3, T> matrix3x3() const noexcept 
    {
        mat<3, 3, T> ret;
        matrix(ret);
        return ret;
    }
    CHTHOLLY_INLINE mat<4, 4, T> matrix4x4() const noexcept 
    {
        mat<4, 4, T> ret = { };
        ret[3][3] = one<T>;
        mat<3, 3, T>* m33_ptr = reinterpret_cast<mat<3, 3, T>*>(&ret);
        matrix(*m33_ptr);
        return ret;
    }
private:
    CHTHOLLY_NOINLINE void matrix(mat<3, 3, T>& m) const noexcept
    {
        T xx2 = i * i * static_cast<T>(2), yy2 = j * j * static_cast<T>(2), zz2 = k * k * static_cast<T>(2);
        T xy2 = i * j * static_cast<T>(2), xz2 = i * k * static_cast<T>(2), xw2 = i * r * static_cast<T>(2);
        T yz2 = j * k * static_cast<T>(2), yw2 = j * r * static_cast<T>(2), zw2 = k * r * static_cast<T>(2);
        m[0][0] = one<T> - (yy2 + zz2);
        m[0][1] = xy2 + zw2;
        m[0][2] = xz2 - yw2;
        m[1][0] = xy2 - zw2;
        m[1][1] = one<T> - (xx2 + zz2);
        m[1][2] = yz2 + xw2;
        m[2][0] = xz2 + yw2; 
        m[2][1] = yz2 - xw2;
        m[2][2] = one<T> - (yy2 + xx2);
    }
};
}

#endif