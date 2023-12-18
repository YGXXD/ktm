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
        T xx = i * i, yy = j * j, zz = k * k, xy = i * j, xz = i * k, xw = i * r, yz = j * k, yw = j * r, zw = k * r;
        m[0][0] = one<T> - static_cast<T>(2) * (yy + zz);
        m[0][1] = static_cast<T>(2) * (xy + zw);
        m[0][2] = static_cast<T>(2) * (xz - yw);
        m[1][0] = static_cast<T>(2) * (xy - zw);
        m[1][1] = one<T> - static_cast<T>(2) * (xx + zz);
        m[1][2] = static_cast<T>(2) * (yz + xw);
        m[2][0] = static_cast<T>(2) * (xz + yw); 
        m[2][1] = static_cast<T>(2) * (yz - xw);
        m[2][2] = one<T> - static_cast<T>(2) * (yy + xx);
    }
};
}

#endif