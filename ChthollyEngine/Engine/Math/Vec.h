#ifndef _VEC_H_
#define _VEC_H_

#include "Chtholly.h"
#include "TypeBase.h"

namespace ktl
{

template<int N, typename T, bool Simd>
struct Vec
{
    static_assert(N > 0);
    typedef Vec<N, T, Simd> Type;
    typedef T ValueType;
    static inline constexpr int Length = N;

    // construct
    Vec();
    Vec(const Vec &v);
    Vec(Vec&& v);
    template<typename ArgT, typename ...ArgsT>
    Vec(ArgT v, ArgsT... vs);

    CHTHOLLY_INLINE Vec& operator=(const Vec& v);
    CHTHOLLY_INLINE Vec& operator=(Vec&& v);

    typename Storage<N, T, Simd>::type data;

    template<typename ...ArgsT>
    CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_vs<ArgsT...>> InitWithValues(ArgsT... vs); 
    template<int U, typename ...ArgsT>
    CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_vs<int, ArgsT...>> InitWithVecValues(const Vec<U, T, Simd> &v, ArgsT... vs);
    template<int ...U>
    CHTHOLLY_INLINE void InitWithVectors(const Vec<U, T, Simd>&... vs);
};

}

template<int N, typename T, bool Simd>
ktl::Vec<N, T, Simd>::Vec() : data({ }) { }

template<int N, typename T, bool Simd>
ktl::Vec<N, T, Simd>::Vec(const Vec& v) : data(v.data) { }

template<int N, typename T, bool Simd>
ktl::Vec<N, T, Simd>::Vec(Vec&& v) : data(v.data) { }

template<int N, typename T, bool Simd>
template<typename ArgT, typename ...ArgsT>
ktl::Vec<N, T, Simd>::Vec(ArgT v, ArgsT... vs)
{
    static_assert(GetMathType<ArgT>::value == MathType::Arithmetic || GetMathType<ArgT>::value == MathType::Vector);
    if constexpr(ktl::GetMathType<ArgT>::value == ktl::MathType::Arithmetic)
    {
        InitWithValues(v, std::forward<ArgsT>(vs)...);
    }
    else if constexpr(ktl::GetMathType<ArgT>::value == ktl::MathType::Vector)
    {
        if constexpr(!sizeof...(ArgsT) || std::is_arithmetic_vs<int, ArgsT...>)
        {
            InitWithVecValues(v, std::forward<ArgsT>(vs)...);
        }
        else
        {
            InitWithVectors(v, std::forward<ArgsT>(vs)...);
        }
    }
}

template<int N, typename T, bool Simd>
CHTHOLLY_INLINE ktl::Vec<N, T, Simd>& ktl::Vec<N, T, Simd>::operator=(const Vec& v)
{
    data = v.data;
    return *this;
}

template<int N, typename T, bool Simd>
CHTHOLLY_INLINE ktl::Vec<N, T, Simd>& ktl::Vec<N, T, Simd>::operator=(Vec&& v)
{
    data = v.data;
    return *this;
}

template<int N, typename T, bool Simd>
template<typename ...ArgsT>
CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_vs<ArgsT...>> ktl::Vec<N, T, Simd>::InitWithValues(ArgsT... vs)
{
    static_assert(sizeof...(ArgsT) <= N);
    data = { static_cast<T>(vs)... };
}

template<int N, typename T, bool Simd>
template<int U, typename ...ArgsT>
CHTHOLLY_INLINE std::enable_if_t<std::is_arithmetic_vs<int, ArgsT...>> ktl::Vec<N, T, Simd>::InitWithVecValues(const Vec<U, T, Simd>& v, ArgsT... vs)
{
    static_assert(sizeof...(ArgsT) + U <= N && U < N);
    using v_t = typename Storage<U, T, false>::type;
    *reinterpret_cast<v_t*>(data.p) = *(reinterpret_cast<const v_t*>(v.data.p));

    using args_t = typename Storage<N - U, T, false>::type;
    if constexpr(sizeof...(ArgsT) > 0)
    {
        *reinterpret_cast<args_t*>(data.p + U) = { static_cast<T>(vs)... };
    }
    else 
    {
        *reinterpret_cast<args_t*>(data.p + U) = { };
    }
}

template<int N, typename T, bool Simd>
template<int ...U>
void ktl::Vec<N, T, Simd>::InitWithVectors(const Vec<U, T, Simd>&... vs)
{
    static_assert((U + ...) <= N);
    static_assert(sizeof...(U) > 1);
    int index = 0;
    ((*reinterpret_cast<typename Storage<U, T, false>::type*>(data.p + index) = 
        *reinterpret_cast<const typename Storage<U, T, false>::type*>(vs.data.p), index += U), ...);

    if constexpr((U + ...) < N)
    {
        using end_t = typename Storage<N - (U + ...), T, false>::type;
        *reinterpret_cast<end_t*>(data.p + (U + ...)) = { };
    }
}

//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator+=(const Vec<N, T, Simd>& v);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator+=(Vec<N, T, Simd>&& v);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator-=(const Vec<N, T, Simd>& v);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator-=(Vec<N, T, Simd>&& v);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator*=(const Vec<N, T, Simd>& v);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator*=(Vec<N, T, Simd>&& v);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator/=(const Vec<N, T, Simd>& v);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator/=(Vec<N, T, Simd>&& v);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator+=(T scalar);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator-=(T scalar);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator*=(T scalar);
//     CHTHOLLY_INLINE Vec<N, T, Simd>& operator/=(T scalar);

// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator+(const Vec<N, T, Simd>& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator+(const Vec<N, T, Simd>& v1, Vec<N, T, Simd>&& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator+(Vec<N, T, Simd>&& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator+(Vec<N, T, Simd>&& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator-(const Vec<N, T, Simd>& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator-(const Vec<N, T, Simd>& v1, Vec<N, T, Simd>&& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator-(Vec<N, T, Simd>&& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator-(Vec<N, T, Simd>&& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator*(const Vec<N, T, Simd>& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator*(const Vec<N, T, Simd>& v1, Vec<N, T, Simd>&& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator*(Vec<N, T, Simd>&& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator*(Vec<N, T, Simd>&& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator/(const Vec<N, T, Simd>& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator/(const Vec<N, T, Simd>& v1, Vec<N, T, Simd>&& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator/(Vec<N, T, Simd>&& v1, const Vec<N, T, Simd>& v2);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator/(Vec<N, T, Simd>&& v1, const Vec<N, T, Simd>& v2);

// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator+(const Vec<N, T, Simd>& v1, T scalar);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator+(Vec<N, T, Simd>&& v1, T scalar);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator+(T scalar, const Vec<N, T, Simd>& v1);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator+(T scalar, Vec<N, T, Simd>&& v1);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator-(const Vec<N, T, Simd>& v1, T scalar);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator-(Vec<N, T, Simd>&& v1, T scalar);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator-(T scalar, const Vec<N, T, Simd>& v1);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator-(T scalar, Vec<N, T, Simd>&& v1);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator*(const Vec<N, T, Simd>& v1, T scalar);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator*(Vec<N, T, Simd>&& v1, T scalar);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator*(T scalar, const Vec<N, T, Simd>& v1);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator*(T scalar, Vec<N, T, Simd>&& v1);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator/(const Vec<N, T, Simd>& v1, T scalar);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator/(Vec<N, T, Simd>&& v1, T scalar);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator/(T scalar, const Vec<N, T, Simd>& v1);
// template<int N, typename T, bool Simd>
// CHTHOLLY_INLINE Vec<N, T, Simd> operator/(T scalar, Vec<N, T, Simd>&& v1);
#endif
