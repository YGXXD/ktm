#ifndef _I_QUAT_OPT_H_
#define _I_QUAT_OPT_H_

#include "Math/Library/ArtcBase.h"
#include "Math/Detail/Vector/VecOptFwd.h"
#include "Math/Detail/Quaternion/QuatOptFwd.h"

namespace ktm
{
template<class Father, class Child>
struct IQuatOpt;

template<class Father, typename T>
struct IQuatOpt<Father, quat<T>> : Father
{
    using Father::Father;

    CHTHOLLY_INLINE quat<T> operator+(const quat<T>& y) const noexcept
    {
        quat<T> ret;
        ret.vector = detail::vec_opt_implement::add<4, T>::call(reinterpret_cast<const vec<4, T>&>(*this), y.vector);
        return ret;
    }

    CHTHOLLY_INLINE quat<T>& operator+=(const quat<T>& y) noexcept
    {
        detail::vec_opt_implement::add_to_self<4, T>::call(reinterpret_cast<vec<4, T>&>(*this), y.vector);
        return reinterpret_cast<quat<T>&>(*this);
    }

    CHTHOLLY_INLINE quat<T> operator-(const quat<T>& y) const noexcept
    {
        quat<T> ret;
        ret.vector = detail::vec_opt_implement::minus<4, T>::call(reinterpret_cast<const vec<4, T>&>(*this), y.vector);
        return ret;
    }

    CHTHOLLY_INLINE quat<T>& operator-=(const quat<T>& y) noexcept
    {
        detail::vec_opt_implement::minus_to_self<4, T>::call(reinterpret_cast<vec<4, T>&>(*this), y.vector);
        return reinterpret_cast<quat<T>&>(*this);
    }

    CHTHOLLY_INLINE quat<T> operator*(const quat<T>& y) const noexcept
    {
        return detail::quat_opt_implement::mul<T>::call(reinterpret_cast<const quat<T>&>(*this), y);
    }

    CHTHOLLY_INLINE quat<T>& operator*=(const quat<T>& y) noexcept
    {
        quat<T>& this_ref = reinterpret_cast<quat<T>&>(*this);
        detail::quat_opt_implement::mul_to_self<T>::call(this_ref, y); 
        return this_ref;
    }

    CHTHOLLY_INLINE vec<3, T> operator*(const vec<3, T>& v) const noexcept
    {
        return detail::quat_opt_implement::act<T>::call(reinterpret_cast<const quat<T>&>(*this), v); 
    }

    CHTHOLLY_INLINE quat<T> operator*(T scalar) const noexcept
    {
        quat<T> ret;
        ret.vector = detail::vec_opt_implement::mul_scalar<4, T>::call(reinterpret_cast<const vec<4, T>&>(*this), scalar);
        return ret;
    }

    friend CHTHOLLY_INLINE quat<T> operator*(T scalar, const quat<T>& x) noexcept 
    { 
        return x * scalar; 
    }

    CHTHOLLY_INLINE quat<T>& operator*=(T scalar) noexcept
    {
        detail::vec_opt_implement::mul_scalar_to_self<4, T>::call(reinterpret_cast<vec<4, T>&>(*this), scalar);
        return reinterpret_cast<quat<T>&>(*this);
    }

    CHTHOLLY_INLINE bool operator==(const quat<T>& y) const noexcept
    {
        return detail::vec_opt_implement::equal<4, T>::call(reinterpret_cast<const vec<4, T>&>(*this), y.vector); 
    }

    CHTHOLLY_INLINE bool operator!=(const quat<T>& y) const noexcept
    {
        return !detail::vec_opt_implement::equal<4, T>::call(reinterpret_cast<const vec<4, T>&>(*this), y.vector); 
    }
};

}

#endif