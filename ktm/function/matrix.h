#ifndef _KTM_MATRIX_H_
#define _KTM_MATRIX_H_

#include "../setup.h"
#include "../type/traits.h"
#include "../type/mat.h"
#include "../detail/function/matrix_fwd.h"

namespace ktm
{
template<class M>
CHTHOLLY_INLINE std::enable_if_t<is_matrix_v<M>, mat_traits_tp_t<M>> transpose(const M& m) noexcept
{
    return detail::matrix_implement::transpose<mat_traits_row_n<M>, mat_traits_col_n<M>, mat_traits_base_t<M>>::call(m);
} 

template<class M>
CHTHOLLY_INLINE std::enable_if_t<is_square_matrix_v<M>, mat_traits_base_t<M>> trace(const M& m)
{
    return detail::matrix_implement::trace<mat_traits_col_n<M>, mat_traits_base_t<M>>::call(m);
}

template<class M>
CHTHOLLY_INLINE std::enable_if_t<is_square_matrix_v<M>, mat_traits_base_t<M>> determinant(const M& m)
{
    return detail::matrix_implement::determinant<mat_traits_col_n<M>, mat_traits_base_t<M>>::call(m);
}

template<class M>
CHTHOLLY_INLINE std::enable_if_t<is_square_matrix_v<M> && is_floating_point_base_v<M>, M> inverse(const M& m)
{
    return detail::matrix_implement::inverse<mat_traits_col_n<M>, mat_traits_base_t<M>>::call(m);
}

template<class M>
CHTHOLLY_INLINE std::enable_if_t<is_square_matrix_v<M> && is_floating_point_base_v<M>, std::tuple<M, M>> factor_lu(const M& m)
{
    return detail::matrix_implement::factor_lu<mat_traits_col_n<M>, mat_traits_base_t<M>>::call(m);
}

template<class M>
CHTHOLLY_INLINE std::enable_if_t<is_square_matrix_v<M> && is_floating_point_base_v<M>, std::tuple<M, M>> factor_qr(const M& m)
{
    return detail::matrix_implement::factor_qr<mat_traits_col_n<M>, mat_traits_base_t<M>>::call(m);
}

template<class M>
CHTHOLLY_INLINE std::enable_if_t<is_square_matrix_v<M> && is_floating_point_base_v<M>, std::tuple<M, M, M>> factor_svd(const M& m)
{
    return detail::matrix_implement::factor_svd<mat_traits_col_n<M>, mat_traits_base_t<M>>::call(m);
}
}

#include "../detail/function/matrix.inl"
#include "../detail/function/matrix_simd.inl"

#endif
