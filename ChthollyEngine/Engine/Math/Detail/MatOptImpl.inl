#ifndef _MAT_OPT_IMPL_INL_
#define _MAT_OPT_IMPL_INL_

#include "MatOptImpl.h"
#include "Math/MathType/BaseType.h"
#include "Math/MathLib/VecCommon.h"

template<class M>
struct ktm::detail::mat_opt_implement::mat_mul_vec
{
    using T = mat_traits_t<M>;
    using ColT = mat_traits_col_t<M>;
    using RawT = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE ColT call(const M& m, const RawT& v) noexcept
    {
        return call(m, v, std::make_index_sequence<ktm::mat_traits_col_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColT call(const M& m, const RawT& v, std::index_sequence<Ns...>) noexcept
    {
        ColT ret;
        ret = ((reinterpret_cast<const ColT*>(&m)[Ns] * reinterpret_cast<const T*>(&v)[Ns]) + ...);
        return ret;
    }
};

template<class M>
struct ktm::detail::mat_opt_implement::vec_mul_mat
{
    using T = mat_traits_t<M>;
    using ColT = mat_traits_col_t<M>;
    using RawT = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE RawT call(const ColT& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<ktm::mat_traits_col_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RawT call(const ColT& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RawT ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reduce_add<ColT>(reinterpret_cast<const ColT*>(&m)[Ns] * v)), ...);
        return ret;
    }
};

template<class M>
struct ktm::detail::mat_opt_implement::mat_mul_mat
{
    using T = mat_traits_t<M>;
    using ColT = mat_traits_col_t<M>;
    using RawT = mat_traits_raw_t<M>;

    template<size_t U>
    using M2 = mat<U, ktm::mat_traits_col_n<M>, T>;
    template<size_t U>
    using RetM = mat<U, ktm::mat_traits_raw_n<M>, T>;

    template<size_t U>
    static CHTHOLLY_INLINE RetM<U> call(const M& m1 , const M2<U>& m2) noexcept
    {
        return call(m1, m2,  std::make_index_sequence<U>());
    }
private:
    template<size_t U, size_t ...Ns>
    static CHTHOLLY_INLINE RetM<U> call(const M& m1 , const M2<U>& m2, std::index_sequence<Ns...>) noexcept
    {
        RetM<U> ret;
        ((reinterpret_cast<ColT*>(&ret)[Ns] = mat_mul_vec<M>::call(m1, reinterpret_cast<const RawT*>(&m2)[Ns])), ...);
        return ret;
    }
};

template<class M>
struct ktm::detail::mat_opt_implement::add
{
    using ColT = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_col_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        (((reinterpret_cast<ColT*>(&ret)[Ns] = reinterpret_cast<const ColT*>(&m1)[Ns] + reinterpret_cast<const ColT*>(&m2)[Ns])), ...);
        return ret;
    }
};

template<class M>
struct ktm::detail::mat_opt_implement::minus
{
    using ColT = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_col_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        (((reinterpret_cast<ColT*>(&ret)[Ns] = reinterpret_cast<const ColT*>(&m1)[Ns] - reinterpret_cast<const ColT*>(&m2)[Ns])), ...);
        return ret;
    }
};

template<class M>
struct ktm::detail::mat_opt_implement::equal
{
    using ColT = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE bool call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_col_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE bool call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        return ((reinterpret_cast<const ColT*>(&m1)[Ns] == reinterpret_cast<const ColT*>(&m2)[Ns]) && ...);
    }
};

#endif