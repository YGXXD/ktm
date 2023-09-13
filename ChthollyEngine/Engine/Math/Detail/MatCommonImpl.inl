#ifndef _MAT_COMMON_IMPL_INL_
#define _MAT_COMMON_IMPL_INL_

#include "Math/MathType/BaseType.h"
#include "MatCommonImpl.h"

template<class M>
struct ktm::detail::mat_common_implement::transpose
{
    using RetM = mat_traits_tp_t<M>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        return call(m, std::make_index_sequence<mat_traits_col_n<M>>(), std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Rs, size_t ...Cs>
    static CHTHOLLY_INLINE RetM call(const M& m, std::index_sequence<Rs...>, std::index_sequence<Cs...>) noexcept
    {
        RetM ret;
        size_t raw_index;
        ((raw_index = Rs, reinterpret_cast<RawV*>(&ret)[Rs] = RawV(reinterpret_cast<const float*>(&reinterpret_cast<const ColV*>(&m)[Cs])[raw_index]...)), ...);
        return ret;
    }
};

#endif