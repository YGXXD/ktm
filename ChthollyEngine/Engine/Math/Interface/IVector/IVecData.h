#ifndef _I_VECTOR_H_
#define _I_VECTOR_H_

#include "Math/Library/ArtcBase.h"

#define KTM_PERMUTATION_2_2(x, y) \
CHTHOLLY_INLINE vec<2, T> x##y() const noexcept { return vec<2, T>(x, y); } \
CHTHOLLY_INLINE vec<2, T> y##x() const noexcept { return vec<2, T>(y, x); }

#define KTM_PERMUTATION_3_2(x, y, z) \
CHTHOLLY_INLINE vec<3, T> x##y##z() const noexcept { return vec<3, T>(x, y, z); } \
CHTHOLLY_INLINE vec<3, T> x##z##y() const noexcept { return vec<3, T>(x, z, y); }

#define KTM_PERMUTATION_3_3(x, y, z) \
KTM_PERMUTATION_3_2(x, y, z) \
KTM_PERMUTATION_3_2(y, z, x) \
KTM_PERMUTATION_3_2(z, x, y)

#define KTM_PERMUTATION_4_2(x, y, z, w) \
CHTHOLLY_INLINE vec<4, T> x##y##z##w() const noexcept { return vec<4, T>(x, y, z, w); } \
CHTHOLLY_INLINE vec<4, T> x##y##w##z() const noexcept { return vec<4, T>(x, y, w, z); }

#define KTM_PERMUTATION_4_3(x, y, z, w) \
KTM_PERMUTATION_4_2(x, y, z, w) \
KTM_PERMUTATION_4_2(x, z, w, y) \
KTM_PERMUTATION_4_2(x, w, y, z)

#define KTM_PERMUTATION_4_4(x, y, z, w) \
KTM_PERMUTATION_4_3(x, y, z, w) \
KTM_PERMUTATION_4_3(y, z, w, x) \
KTM_PERMUTATION_4_3(z, w, x, y) \
KTM_PERMUTATION_4_3(w, x, y, z)

#define KTM_SWIZZLE_VEC2(x, y) KTM_PERMUTATION_2_2(x, y)

#define KTM_SWIZZLE_VEC3(x, y, z) \
KTM_PERMUTATION_3_3(x, y, z) \
KTM_PERMUTATION_2_2(x, y) \
KTM_PERMUTATION_2_2(x, z) \
KTM_PERMUTATION_2_2(y, z)

#define KTM_SWIZZLE_VEC4(x, y, z, w) \
KTM_PERMUTATION_4_4(x, y, z, w) \
KTM_PERMUTATION_3_3(x, y, z) \
KTM_PERMUTATION_3_3(x, y, w) \
KTM_PERMUTATION_3_3(x, z, w) \
KTM_PERMUTATION_3_3(y, z, w) \
KTM_PERMUTATION_2_2(x, y) \
KTM_PERMUTATION_2_2(x, z) \
KTM_PERMUTATION_2_2(x, w) \
KTM_PERMUTATION_2_2(y, z) \
KTM_PERMUTATION_2_2(y, w) \
KTM_PERMUTATION_2_2(z, w) 

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
    IVecData(const vec<2, U>& v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) { }

    KTM_SWIZZLE_VEC2(x, y)
    KTM_SWIZZLE_VEC2(r, g)
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

    KTM_SWIZZLE_VEC3(x, y, z)
    KTM_SWIZZLE_VEC3(r, g, b) 
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

    KTM_SWIZZLE_VEC4(x, y, z, w)
    KTM_SWIZZLE_VEC4(r, g, b, a)
};

}

#endif