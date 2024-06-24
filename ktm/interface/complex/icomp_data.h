//  MIT License
//
//  Copyright (c) 2024 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_I_COMP_DATA_H_
#define _KTM_I_COMP_DATA_H_

#include "../../setup.h"
#include "../../type/vec_fwd.h"
#include "../../type/comp_fwd.h"
#include "../../type/mat_fwd.h"
#include "../../detail/vector/vec_data_fwd.h"
#include "../../function/trigonometric.h"

namespace ktm
{
    
template<class Father, class Child>
struct icomp_data;

template<class Father, typename T>
struct icomp_data<Father, comp<T>> : Father
{
    using Father::Father;
    union
    {
        struct { T i, r; };
        typename detail::vec_data_implement::vec_storage<2, T>::type st;
    };
    constexpr explicit icomp_data(T x, T y) noexcept : i(x), r(y) { }
    explicit icomp_data(const vec<2, T> vec) noexcept : i(vec.x), r(vec.y) { }

    KTM_INLINE T real() const noexcept { return r; }
    KTM_INLINE T imag() const noexcept { return i; } 
    KTM_INLINE T angle() const noexcept { return atan2(imag(), real()); }
    
    KTM_INLINE mat<2, 2, T> matrix2x2() const noexcept 
    {
        return mat<2, 2, T>(vec<2, T>(r, i), vec<2, T>(-i, r));
    }

    KTM_INLINE mat<3, 3, T> matrix3x3() const noexcept
    {
        return mat<3, 3, T>(vec<3, T>(r, i, zero<T>), vec<3, T>(-i, r, zero<T>), vec<3, T>(zero<T>, zero<T>, one<T>));
    }

    KTM_INLINE vec<2, T>& operator*() noexcept
    {
        return reinterpret_cast<vec<2, T>&>(*this);
    }

    KTM_INLINE const vec<2, T>& operator*() const noexcept
    {
        return reinterpret_cast<const vec<2, T>&>(*this);
    }
};

}

#endif