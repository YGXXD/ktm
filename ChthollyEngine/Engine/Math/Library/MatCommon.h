#ifndef _MAT_COMMON_H_
#define _MAT_COMMON_H_

#include "Matrix.h"
#include "Math/Detail/MatCommonImpl.h"

namespace ktm
{
template<class M>
CHTHOLLY_INLINE mat_traits_tp_t<M> transpose(const M& m) noexcept
{
    return detail::mat_common_implement::transpose<mat_traits_row_n<M>, mat_traits_col_n<M>, mat_traits_t<M>>::call(m);
} 

template<class M>
CHTHOLLY_INLINE std::enable_if_t<mat_traits_row_n<M> == mat_traits_col_n<M>, mat_traits_t<M>> trace(const M& m)
{
    return detail::mat_common_implement::trace<mat_traits_col_n<M>, mat_traits_t<M>>::call(m);
}

template<class M>
CHTHOLLY_INLINE std::enable_if_t<mat_traits_row_n<M> == mat_traits_col_n<M>, mat_traits_t<M>> determinant(const M& m)
{
    return detail::mat_common_implement::determinant<mat_traits_col_n<M>, mat_traits_t<M>>::call(m);
}

template<class M>
CHTHOLLY_INLINE std::enable_if_t<mat_traits_row_n<M> == mat_traits_col_n<M> && std::is_floating_point_v<mat_traits_t<M>>, M> inverse(const M& m)
{
    return detail::mat_common_implement::inverse<mat_traits_col_n<M>, mat_traits_t<M>>::call(m);
}

template<class M>
CHTHOLLY_INLINE std::enable_if_t<mat_traits_row_n<M> == mat_traits_col_n<M> && std::is_floating_point_v<mat_traits_t<M>>, std::tuple<M, M>> factor_lu(const M& m)
{
    return detail::mat_common_implement::factor_lu<mat_traits_col_n<M>, mat_traits_t<M>>::call(m);
}

template<class M>
CHTHOLLY_INLINE std::enable_if_t<mat_traits_row_n<M> == mat_traits_col_n<M> && std::is_floating_point_v<mat_traits_t<M>>, std::tuple<M, M>> factor_qr(const M& m)
{
    return detail::mat_common_implement::factor_qr<mat_traits_col_n<M>, mat_traits_t<M>>::call(m);
}

template<class M>
CHTHOLLY_INLINE std::enable_if_t<mat_traits_row_n<M> == mat_traits_col_n<M> && std::is_floating_point_v<mat_traits_t<M>>, std::tuple<M, M, M>> factor_svd(const M& m)
{
    return detail::mat_common_implement::factor_svd<mat_traits_col_n<M>, mat_traits_t<M>>::call(m);
}
}

#endif
