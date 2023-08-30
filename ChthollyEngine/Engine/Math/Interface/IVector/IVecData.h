#ifndef _I_VECTOR_H_
#define _I_VECTOR_H_

#include "Math/TypeBase.h"

namespace ktl
{

template<class Father, class Child>
struct IVecData;

template<class Father, typename T>
struct alignas(sizeof(T)) IVecData<Father, vec<1, T>> : Father
{
    using Father::Father;
    union
    {
        T elems[1];
        struct { T x; };
        struct { T r; };
    };
    constexpr IVecData(T xi) noexcept : x(xi) { }
};

template<class Father, typename T>
struct alignas(2 * sizeof(T)) IVecData<Father, vec<2, T>> : Father
{
    using Father::Father;
    union
    {
        T elems[2];
        struct { T x, y; };
        struct { T r, g; };
    };
    constexpr IVecData(T xi, T yi) noexcept : x(xi), y(yi) { }
};

template<class Father, typename T>
struct alignas(4 * sizeof(T)) IVecData<Father, vec<3, T>> : Father
{
    using Father::Father;
    union
    {
        T elems[3];
        struct { T x, y, z; };
        struct { T r, g, b; };
    };
    constexpr IVecData(T xi, T yi, T zi) noexcept : x(xi), y(yi), z(zi) { }
};

template<class Father, typename T>
struct alignas(4 * sizeof(T)) IVecData<Father, vec<4, T>> : Father
{
    using Father::Father;
    union
    {
        T elems[4];
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
    };
    constexpr IVecData(T xi, T yi, T zi, T wi) noexcept : x(xi), y(yi), z(zi), w(wi) { }
};

}

#endif