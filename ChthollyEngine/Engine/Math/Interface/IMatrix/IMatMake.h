#ifndef _I_MAT_MAKE_H_
#define _I_MAT_MAKE_H_

#include "Math/MathType/BaseType.h"

namespace ktm
{
template<class Father, class Child>
struct IMatMake;

template<class Father, size_t Raw, typename T>
struct IMatMake<Father, mat<2, Raw, T>> : Father
{
    static CHTHOLLY_INLINE mat<2, Raw, T> from_raw(const vec<Raw, T>& raw0, const vec<Raw, T>& raw1) noexcept
    {
        return from_raw(raw0, raw1, std::make_index_sequence<Raw>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE mat<2, Raw, T> from_raw(const vec<Raw, T>& raw0, const vec<Raw, T>& raw1, std::index_sequence<Ns...>) noexcept
    {
        return mat<2, Raw, T>({ reinterpret_cast<const T*>(&raw0)[Ns], reinterpret_cast<const T*>(&raw1)[Ns] }...);
    }
};


template<class Father, size_t Raw, typename T>
struct IMatMake<Father, mat<3, Raw, T>> : Father
{
    static CHTHOLLY_INLINE mat<3, Raw, T> from_raw(const vec<Raw, T>& raw0, const vec<Raw, T>& raw1, const vec<Raw, T>& raw2) noexcept
    {
        return from_raw(raw0, raw1, raw2, std::make_index_sequence<Raw>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE mat<3, Raw, T> from_raw(const vec<Raw, T>& raw0, const vec<Raw, T>& raw1, const vec<Raw, T>& raw2, std::index_sequence<Ns...>) noexcept
    {
        return mat<3, Raw, T>({ reinterpret_cast<const T*>(&raw0)[Ns], reinterpret_cast<const T*>(&raw1)[Ns], reinterpret_cast<const T*>(&raw2)[Ns] }...);
    }
};


template<class Father, size_t Raw, typename T>
struct IMatMake<Father, mat<4, Raw, T>> : Father
{
    static CHTHOLLY_INLINE mat<4, Raw, T> from_raw(const vec<Raw, T>& raw0, const vec<Raw, T>& raw1, const vec<Raw, T>& raw2, const vec<Raw, T>& raw3) noexcept
    {
        return from_raw(raw0, raw1, raw2, raw3, std::make_index_sequence<Raw>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE mat<4, Raw, T> from_raw(const vec<Raw, T>& raw0, const vec<Raw, T>& raw1, const vec<Raw, T>& raw2, const vec<Raw, T>& raw3, std::index_sequence<Ns...>) noexcept
    {
        return mat<4, Raw, T>({ reinterpret_cast<const T*>(&raw0)[Ns], reinterpret_cast<const T*>(&raw1)[Ns],
                                reinterpret_cast<const T*>(&raw2)[Ns], reinterpret_cast<const T*>(&raw3)[Ns] }...);
    }
};
}

#endif