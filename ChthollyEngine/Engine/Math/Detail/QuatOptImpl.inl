#ifndef _QUAT_OPT_IMPL_INL_
#define _QUAT_OPT_IMPL_INL_

#include "QuatOptImpl.h"
#include "Math/MathType/BaseType.h"

template<typename T>
struct ktm::detail::quat_opt_implement::mul
{
    using Q = quat<T>;
    static CHTHOLLY_INLINE Q call(const Q& x, const Q& y) noexcept
    {
        Q ret;
        ret[0] = x[0] * y[0] - x[1] * y[1] - x[2] * y[2] - x[3] * y[3];
        ret[1] = x[0] * y[1] + y[0] * x[1] + x[2] * y[3] - x[3] * y[2];
        ret[2] = x[0] * y[2] + y[0] * x[2] + x[3] * y[1] - x[1] * y[3];
        ret[3] = x[0] * y[3] + y[0] * x[3] + x[1] * y[2] - x[2] * y[1];
        return ret;
    }
};

template<typename T>
struct ktm::detail::quat_opt_implement::mul_to_self
{
    using Q = quat<T>;
    static CHTHOLLY_INLINE void call(Q& x, const Q& y) noexcept
    {
        Q tmp = x;
        x[0] = tmp[0] * y[0] - tmp[1] * y[1] - tmp[2] * y[2] - tmp[3] * y[3];
        x[1] = tmp[0] * y[1] + y[0] * tmp[1] + tmp[2] * y[3] - tmp[3] * y[2];
        x[2] = tmp[0] * y[2] + y[0] * tmp[2] + tmp[3] * y[1] - tmp[1] * y[3];
        x[3] = tmp[0] * y[3] + y[0] * tmp[3] + tmp[1] * y[2] - tmp[2] * y[1];
    }
};

#endif