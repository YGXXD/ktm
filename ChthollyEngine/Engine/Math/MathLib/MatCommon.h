#ifndef _MAT_COMMON_H_
#define _MAT_COMMON_H_

#include "Math/MathType/BaseType.h"
#include "Math/Detail/MatCommonImpl.h"

namespace ktm
{
    template<class M>
    CHTHOLLY_INLINE mat_traits_tp_t<M> transpose(const M& m) noexcept
    {
        return detail::mat_common_implement::transpose<M>::call(m);
    } 
}

#endif