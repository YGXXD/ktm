#ifndef _I_VECTOR_H_
#define _I_VECTOR_H_

#include "Math/TypeBase.h"

namespace ktm
{

template<class Father, class Child>
struct IVecData;

template<class Father, typename T>
struct alignas(sizeof(T)) IVecData<Father, vec<1, T>> : Father
{
    using Father::Father;
    union
    {
        struct { T x; };
        struct { T r; };
    };
    constexpr IVecData(T xi) noexcept : x(xi) { }
    template<typename U, typename = std::enable_if_t<!std::is_same_v<U, T>>>
    IVecData(const vec<1, U>& v) : x(static_cast<T>(v.x)) { }
};

template<class Father, typename T>
struct alignas(2 * sizeof(T)) IVecData<Father, vec<2, T>> : Father
{
    using Father::Father;
    union
    {
        struct { T x, y; };
        struct { T r, g; };
    };
    constexpr IVecData(T xi, T yi) noexcept : x(xi), y(yi) { }
    IVecData(const vec<1, T>& v, T yi) noexcept : x(v.x), y(yi) { }
    template<typename U, typename = std::enable_if_t<!std::is_same_v<U, T>>>
    IVecData(const vec<3, U>& v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) { }
};

template<class Father, typename T>
struct alignas(4 * sizeof(T)) IVecData<Father, vec<3, T>> : Father
{
    using Father::Father;
    union
    {
        struct { T x, y, z; };
        struct { T r, g, b; };
    };
    constexpr IVecData(T xi, T yi, T zi) noexcept : x(xi), y(yi), z(zi) { }
    IVecData(const vec<2, T>& v, T zi) : x(v.x), y(v.y), z(zi) { }
    template<typename U, typename = std::enable_if_t<!std::is_same_v<U, T>>>
    IVecData(const vec<3, U>& v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)) { }
};

template<class Father, typename T>
struct alignas(4 * sizeof(T)) IVecData<Father, vec<4, T>> : Father
{
    using Father::Father;
    union
    {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
    };
    constexpr IVecData(T xi, T yi, T zi, T wi) noexcept : x(xi), y(yi), z(zi), w(wi) { }
    IVecData(const vec<3, T>& v, T wi) : x(v.x), y(v.y), z(v.z), w(wi) { }
    template<typename U, typename = std::enable_if_t<!std::is_same_v<U, T>>>
    IVecData(const vec<4, U>& v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)), w(static_cast<T>(v.w)) { }
};

}

#endif