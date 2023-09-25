#ifndef _I_MAT_MAKE_H_
#define _I_MAT_MAKE_H_

#include "Math/MathType/BaseType.h"

namespace ktm
{
template<class Father, class Child>
struct IMatMake;

template<class Father, size_t Row, typename T>
struct IMatMake<Father, mat<2, Row, T>> : Father
{
    static CHTHOLLY_INLINE mat<2, Row, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1) noexcept
    {
        return from_row(row0, row1, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE mat<2, Row, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1, std::index_sequence<Ns...>) noexcept
    {
        return mat<2, Row, T>({ reinterpret_cast<const T*>(&row0)[Ns], reinterpret_cast<const T*>(&row1)[Ns] }...);
    }
};


template<class Father, size_t Row, typename T>
struct IMatMake<Father, mat<3, Row, T>> : Father
{
    static CHTHOLLY_INLINE mat<3, Row, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1, const vec<Row, T>& row2) noexcept
    {
        return from_row(row0, row1, row2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE mat<3, Row, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1, const vec<Row, T>& row2, std::index_sequence<Ns...>) noexcept
    {
        return mat<3, Row, T>({ reinterpret_cast<const T*>(&row0)[Ns], reinterpret_cast<const T*>(&row1)[Ns], reinterpret_cast<const T*>(&row2)[Ns] }...);
    }
};


template<class Father, size_t Row, typename T>
struct IMatMake<Father, mat<4, Row, T>> : Father
{
    static CHTHOLLY_INLINE mat<4, Row, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1, const vec<Row, T>& row2, const vec<Row, T>& row3) noexcept
    {
        return from_row(row0, row1, row2, row3, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE mat<4, Row, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1, const vec<Row, T>& row2, const vec<Row, T>& row3, std::index_sequence<Ns...>) noexcept
    {
        return mat<4, Row, T>({ reinterpret_cast<const T*>(&row0)[Ns], reinterpret_cast<const T*>(&row1)[Ns],
                                reinterpret_cast<const T*>(&row2)[Ns], reinterpret_cast<const T*>(&row3)[Ns] }...);
    }
};
}

#endif