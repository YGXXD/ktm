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

    template<class M>
    CHTHOLLY_INLINE std::enable_if_t<mat_traits_col_n<M> == mat_traits_raw_n<M>, mat_traits_t<M>> determinant(const M& m)
    {
        return detail::mat_common_implement::determinant<M>::call(m);
    }
}

#endif