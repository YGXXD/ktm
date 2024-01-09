#ifndef _I_MAT_MAKE_H_
#define _I_MAT_MAKE_H_

#include "../../type/basic.h"

namespace ktm
{
template<class Father, class Child>
struct IMatMake;

template<class Father, size_t Row, typename T>
struct IMatMake<Father, mat<Row, 2, T>> : Father
{
    static CHTHOLLY_INLINE mat<Row, 2, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1) noexcept
    {
        return from_row(row0, row1, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE mat<Row, 2, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1, std::index_sequence<Ns...>) noexcept
    {
        return mat<Row, 2, T>({ reinterpret_cast<const T*>(&row0)[Ns], reinterpret_cast<const T*>(&row1)[Ns] }...);
    }
};

template<class Father, typename T>
struct IMatMake<Father, mat<2, 2, T>> : Father
{
    static CHTHOLLY_INLINE mat<2, 2, T> from_row(const vec<2, T>& row0, const vec<2, T>& row1) noexcept
    {
        return mat<2, 2, T>({ { reinterpret_cast<const T*>(&row0)[0], reinterpret_cast<const T*>(&row1)[0] },
                              { reinterpret_cast<const T*>(&row0)[1], reinterpret_cast<const T*>(&row1)[1] } });
    }

    static CHTHOLLY_INLINE mat<2, 2, T> from_diag(const vec<2, T>& diag) noexcept
    {
        return mat<2, 2, T>({ { reinterpret_cast<const T*>(&diag)[0], zero<T> },
                              { zero<T>, reinterpret_cast<const T*>(&diag)[1] } });
    }

    static CHTHOLLY_INLINE mat<2, 2, T> from_eye() noexcept
    {
        return mat<2, 2, T>({ { one<T>, zero<T> },
                              { zero<T>, one<T> } });
    } 
};

template<class Father, size_t Row, typename T>
struct IMatMake<Father, mat<Row, 3, T>> : Father
{
    static CHTHOLLY_INLINE mat<Row, 3, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1, const vec<Row, T>& row2) noexcept
    {
        return from_row(row0, row1, row2, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE mat<Row, 3, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1, const vec<Row, T>& row2, std::index_sequence<Ns...>) noexcept
    {
        return mat<Row, 3, T>({ reinterpret_cast<const T*>(&row0)[Ns], reinterpret_cast<const T*>(&row1)[Ns], reinterpret_cast<const T*>(&row2)[Ns] }...);
    }
};

template<class Father, typename T>
struct IMatMake<Father, mat<3, 3, T>> : Father
{
    static CHTHOLLY_INLINE mat<3, 3, T> from_row(const vec<3, T>& row0, const vec<3, T>& row1, const vec<3, T>& row2) noexcept
    {
        return mat<3, 3, T>({ { reinterpret_cast<const T*>(&row0)[0], reinterpret_cast<const T*>(&row1)[0], reinterpret_cast<const T*>(&row2)[0] },
                              { reinterpret_cast<const T*>(&row0)[1], reinterpret_cast<const T*>(&row1)[1], reinterpret_cast<const T*>(&row2)[1] },
                              { reinterpret_cast<const T*>(&row0)[2], reinterpret_cast<const T*>(&row1)[2], reinterpret_cast<const T*>(&row2)[2] } });
    }

    static CHTHOLLY_INLINE mat<3, 3, T> from_diag(const vec<3, T>& diag) noexcept
    {
        return mat<3, 3, T>({ { reinterpret_cast<const T*>(&diag)[0], zero<T>, zero<T> },
                              { zero<T>, reinterpret_cast<const T*>(&diag)[1], zero<T> }, 
                              { zero<T>, zero<T>, reinterpret_cast<const T*>(&diag)[2] } });
    }

    static CHTHOLLY_INLINE mat<3, 3, T> from_eye() noexcept
    {
        return mat<3, 3, T>({ { one<T>, zero<T>, zero<T> },
                              { zero<T>, one<T>, zero<T> }, 
                              { zero<T>, zero<T>, one<T> } }); 
    }
};

template<class Father, size_t Row, typename T>
struct IMatMake<Father, mat<Row, 4, T>> : Father
{
    static CHTHOLLY_INLINE mat<Row, 4, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1, const vec<Row, T>& row2, const vec<Row, T>& row3) noexcept
    {
        return from_row(row0, row1, row2, row3, std::make_index_sequence<Row>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE mat<Row, 4, T> from_row(const vec<Row, T>& row0, const vec<Row, T>& row1, const vec<Row, T>& row2, const vec<Row, T>& row3, std::index_sequence<Ns...>) noexcept
    {
        return mat<Row, 4, T>({ reinterpret_cast<const T*>(&row0)[Ns], reinterpret_cast<const T*>(&row1)[Ns],
                                reinterpret_cast<const T*>(&row2)[Ns], reinterpret_cast<const T*>(&row3)[Ns] }...);
    }
};

template<class Father, typename T>
struct IMatMake<Father, mat<4, 4, T>> : Father
{
    static CHTHOLLY_INLINE mat<4, 4, T> from_row(const vec<4, T>& row0, const vec<4, T>& row1, const vec<4, T>& row2, const vec<4, T>& row3) noexcept
    {
        return mat<4, 4, T>({ { reinterpret_cast<const T*>(&row0)[0], reinterpret_cast<const T*>(&row1)[0], reinterpret_cast<const T*>(&row2)[0], reinterpret_cast<const T*>(&row3)[0] },
                              { reinterpret_cast<const T*>(&row0)[1], reinterpret_cast<const T*>(&row1)[1], reinterpret_cast<const T*>(&row2)[1], reinterpret_cast<const T*>(&row3)[1] },
                              { reinterpret_cast<const T*>(&row0)[2], reinterpret_cast<const T*>(&row1)[2], reinterpret_cast<const T*>(&row2)[2], reinterpret_cast<const T*>(&row3)[2] },
                              { reinterpret_cast<const T*>(&row0)[3], reinterpret_cast<const T*>(&row1)[3], reinterpret_cast<const T*>(&row2)[3], reinterpret_cast<const T*>(&row3)[3] } });
    }

    static CHTHOLLY_INLINE mat<4, 4, T> from_diag(const vec<4, T>& diag) noexcept
    {
        return mat<4, 4, T>({ { reinterpret_cast<const T*>(&diag)[0], zero<T>, zero<T>, zero<T> },
                              { zero<T>, reinterpret_cast<const T*>(&diag)[1], zero<T>, zero<T> }, 
                              { zero<T>, zero<T>, reinterpret_cast<const T*>(&diag)[2], zero<T> },
                              { zero<T>, zero<T>, zero<T>, reinterpret_cast<const T*>(&diag)[3] } });
    }

    static CHTHOLLY_INLINE mat<4, 4, T> from_eye() noexcept
    {
        return mat<4, 4, T>({ { one<T>, zero<T>, zero<T>, zero<T> },
                              { zero<T>, one<T>, zero<T>, zero<T> }, 
                              { zero<T>, zero<T>, one<T>, zero<T> },
                              { zero<T>, zero<T>, zero<T>, one<T> } }); 
    }
};
}

#endif