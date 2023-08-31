#ifndef _I_DOT_H_
#define _I_DOT_H_

#include "Math/TypeBase.h"

namespace ktm
{
struct DotImplement
{
private:
    template<class Father, class Child> friend class IDot;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Dot;
};

template<class Father, class Child>
struct IDot : Father
{
    using Father::Father;
    using value_type = math_traits_t<Child>;
    static constexpr int len = vec_traits_len<Child>;

    static value_type Dot(const Child& x, const Child& y) noexcept
    {
        return DotImplement::Dot<len, value_type, Child>::Call(x, y);
    }

    value_type Dot(const Child& y) noexcept
    {
        return DotImplement::Dot<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    
};
}

template<int N, typename T, class V>
struct ktm::DotImplement::Dot<N, T, V>
{
    static CHTHOLLY_INLINE T Call(const V& x, const V& y) noexcept
    {
        return Call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T Call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        T ret = ((reinterpret_cast<const T*>(&x)[Ns] * reinterpret_cast<const T*>(&y)[Ns]) + ...);
        return ret;
    } 
};
#endif