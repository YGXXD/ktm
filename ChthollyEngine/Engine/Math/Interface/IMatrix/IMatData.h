#include "Math/MathType/BaseType.h"

namespace ktm
{
template<class Father, class Child>
struct IMatData;

template<class Father, typename T>
struct alignas(alignof(vec<2, T>)) IMatData<Father, mat<2, 2, T>> : Father
{
    static_assert(std::is_same_v<mat_traits_col_t<mat<2, 2, T>>, vec<2, T>>);
    vec<2, T> columns[2];

    IMatData(const vec<2, T>& col1, const vec<2, T>& col2) : columns{ col1, col2 } { }
    IMatData(T m00, T m10, 
             T m01, T m11) : columns{ { m00, m10 }, 
                                      { m01, m11 } } { };

    static_assert(std::is_same_v<mat_traits_raw_t<mat<2, 2, T>>, vec<2, T>>);
    static CHTHOLLY_INLINE mat<2, 2, T> from_raw(const vec<2, T>& raw1, const vec<2, T>& raw2)
    {
        return mat<2, 2, T>(vec<2, T>(raw1.x, raw2.x), 
                            vec<2, T>(raw1.y, raw2.y));
    }
    static CHTHOLLY_INLINE mat<2, 2, T> from_raw(T m00, T m01, 
                                                 T m10, T m11)
    {
        return mat<2, 2, T>(m00, m10, 
                            m01, m11);
    }

};



template<class Father, typename T>
struct alignas(alignof(vec<3, T>)) IMatData<Father, mat<3, 3, T>> : Father
{
    static_assert(std::is_same_v<mat_traits_col_t<mat<3, 3, T>>, vec<3, T>>);
    vec<3, T> columns[3];

    IMatData(const vec<3, T>& col1, const vec<3, T>& col2, const vec<3, T>& col3) : columns{ col1, col2, col3 } { }
    IMatData(T m00, T m10, T m20, 
             T m01, T m11, T m21, 
             T m02, T m12, T m22) : columns{ { m00, m10, m20 }, 
                                             { m01, m11, m21 }, 
                                             { m02, m12, m22 } } { };

    static_assert(std::is_same_v<mat_traits_raw_t<mat<3, 3, T>>, vec<3, T>>);
    static CHTHOLLY_INLINE mat<3, 3, T> from_raw(const vec<3, T>& raw1, const vec<3, T>& raw2, const vec<3, T>& raw3)
    {
        return mat<3, 3, T>(vec<3, T>(raw1.x, raw2.x, raw3.x), 
                            vec<3, T>(raw1.y, raw2.y, raw3.y), 
                            vec<3, T>(raw1.z, raw2.z, raw3.z));
    }
    static CHTHOLLY_INLINE mat<3, 3, T> from_raw(T m00, T m01, T m02, 
                                                 T m10, T m11, T m12, 
                                                 T m20, T m21, T m22)
    {
        return mat<3, 3, T>(m00, m10, m20, 
                            m01, m11, m21, 
                            m02, m12, m22);
    }
};

template<class Father, typename T>
struct alignas(alignof(vec<4, T>)) IMatData<Father, mat<4, 4, T>> : Father
{
    static_assert(std::is_same_v<mat_traits_col_t<mat<4, 4, T>>, vec<4, T>>);
    vec<4, T> columns[4];

    IMatData(const vec<4, T>& col1, const vec<4, T>& col2, const vec<4, T>& col3, const vec<4, T>& col4) : columns{ col1, col2, col3, col4 } { }
    IMatData(T m00, T m10, T m20, T m30, 
             T m01, T m11, T m21, T m31, 
             T m02, T m12, T m22, T m32, 
             T m03, T m13, T m23, T m33) : columns{ { m00, m10, m20, m30 }, 
                                                    { m01, m11, m21, m31 }, 
                                                    { m02, m12, m22, m32 }, 
                                                    { m03, m13, m23, m33 } } { };

    static_assert(std::is_same_v<mat_traits_raw_t<mat<4, 4, T>>, vec<4, T>>);
    static CHTHOLLY_INLINE mat<4, 4, T> from_raw(const vec<4, T>& raw1, const vec<4, T>& raw2, const vec<4, T>& raw3, const vec<4, T>& raw4)
    {
        return mat<4, 4, T>(vec<4, T>(raw1.x, raw2.x, raw3.x, raw4.x), 
                            vec<4, T>(raw1.y, raw2.y, raw3.y, raw4.y), 
                            vec<4, T>(raw1.z, raw2.z, raw3.z, raw4.z), 
                            vec<4, T>(raw1.w, raw2.w, raw3.w, raw4.w));
    }
    static CHTHOLLY_INLINE mat<4, 4, T> from_raw(T m00, T m01, T m02, T m03, 
                                                 T m10, T m11, T m12, T m13, 
                                                 T m20, T m21, T m22, T m23, 
                                                 T m30, T m31, T m32, T m33)
    {
        return mat<4, 4, T>(m00, m10, m20, m30, 
                            m01, m11, m21, m31, 
                            m02, m12, m22, m32, 
                            m03, m13, m23, m33);
    }
};

}