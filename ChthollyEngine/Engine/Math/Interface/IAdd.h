#ifndef _I_ADD_H_
#define _I_ADD_H_

#include "Chtholly.h"

namespace ktl
{
template<typename Father, typename Child>
struct IAdd : Father
{
    using Father::Father;

    CHTHOLLY_INLINE Child operator+(const Child& x) const noexcept
    {
        return static_cast<const Child*>(this)->Add(x);
    }

    CHTHOLLY_INLINE Child& operator+=(const Child& x) noexcept
    {
        return static_cast<Child*>(this)->AddToSelf(x);
    }

    CHTHOLLY_INLINE Child operator-(const Child& x) const noexcept
    {
        return static_cast<const Child*>(this)->Minus(x);
    }

    CHTHOLLY_INLINE Child& operator-=(const Child& x) noexcept
    {
        return static_cast<Child*>(this)->MinusToSelf(x);
    }

    CHTHOLLY_INLINE Child operator-() const noexcept
    {
        return static_cast<const Child*>(this)->Inverse();
    }

    CHTHOLLY_INLINE Child operator*(int a) const noexcept
    {
        return static_cast<const Child*>(this)->AddMul(a);
    }

    CHTHOLLY_INLINE Child& operator*=(int a) noexcept
    {
        return static_cast<Child*>(this)->AddMulToSelf(a);
    }

    friend CHTHOLLY_INLINE Child operator*(int a, const Child& x) noexcept
    {
        return x * a;
    }
};
}



#endif