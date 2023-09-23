#ifndef _MAT_OPT_IMPL_INL_
#define _MAT_OPT_IMPL_INL_

#include "MatOptImpl.h"
#include "Math/MathType/BaseType.h"
#include "Math/MathLib/VecCommon.h"

template<size_t Col, size_t Raw, typename T>
struct ktm::detail::mat_opt_implement::mat_mul_vec
{
	using M = mat<Col, Raw, T>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v) noexcept
    {
        return call(m, v, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE ColV call(const M& m, const RawV& v, std::index_sequence<Ns...>) noexcept
    {
        ColV ret;
        ret = ((reinterpret_cast<const ColV*>(&m)[Ns] * reinterpret_cast<const T*>(&v)[Ns]) + ...);
        return ret;
    }
};

template<size_t Col, size_t Raw, typename T>
struct ktm::detail::mat_opt_implement::vec_mul_mat
{
    using M = mat<Col, Raw, T>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;
    static CHTHOLLY_INLINE RawV call(const ColV& v, const M& m) noexcept
    {
        return call(v, m, std::make_index_sequence<mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE RawV call(const ColV& v, const M& m, std::index_sequence<Ns...>) noexcept
    {
        RawV ret;
        ((reinterpret_cast<T*>(&ret)[Ns] = reduce_add<ColV>(reinterpret_cast<const ColV*>(&m)[Ns] * v)), ...);
        return ret;
    }
};

template<size_t Col, size_t Raw, typename T>
struct ktm::detail::mat_opt_implement::mat_mul_mat
{
    using M = mat<Col, Raw, T>;
    using ColV = mat_traits_col_t<M>;
    using RawV = mat_traits_raw_t<M>;

    template<size_t U>
    using M2 = mat<mat_traits_raw_n<M>, U, T>;
    template<size_t U>
    using RetM = mat<mat_traits_col_n<M>, U, T>;

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
        ((reinterpret_cast<ColV*>(&ret)[Ns] = mat_mul_vec<Col, Raw, T>::call(m1, reinterpret_cast<const RawV*>(&m2)[Ns])), ...);
        return ret;
    }
};

template<size_t Col, size_t Raw, typename T>
struct ktm::detail::mat_opt_implement::add
{
	using M = mat<Col, Raw, T>;
    using ColV = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        (((reinterpret_cast<ColV*>(&ret)[Ns] = reinterpret_cast<const ColV*>(&m1)[Ns] + reinterpret_cast<const ColV*>(&m2)[Ns])), ...);
        return ret;
    }
};

template<size_t Col, size_t Raw, typename T>
struct ktm::detail::mat_opt_implement::minus
{
	using M = mat<Col, Raw, T>;
    using ColV = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE M call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        M ret;
        (((reinterpret_cast<ColV*>(&ret)[Ns] = reinterpret_cast<const ColV*>(&m1)[Ns] - reinterpret_cast<const ColV*>(&m2)[Ns])), ...);
        return ret;
    }
};

template<size_t Col, size_t Raw, typename T>
struct ktm::detail::mat_opt_implement::equal
{
	using M = mat<Col, Raw, T>;
    using ColV = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE bool call(const M& m1, const M& m2) noexcept
    {
        return call(m1, m2, std::make_index_sequence<ktm::mat_traits_raw_n<M>>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE bool call(const M& m1, const M& m2, std::index_sequence<Ns...>) noexcept
    {
        return ((reinterpret_cast<const ColV*>(&m1)[Ns] == reinterpret_cast<const ColV*>(&m2)[Ns]) && ...);
    }
};

#endif
