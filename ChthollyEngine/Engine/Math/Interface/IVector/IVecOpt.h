#ifndef _I_VEC_OPT_H_
#define _I_VEC_OPT_H_

#include "Math/TypeBase.h"

namespace ktm
{

struct VecOptImplement
{
private:
    template<class Father, class Child> friend class IVecOpt;
    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Add;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct AddToSelf;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Minus;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MinusToSelf; 

    template<class Father, class Child> friend class IVecOpt;
    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Mul;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MulToSelf;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Div;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct DivToSelf; 

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Opposite;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct AddScalar;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct AddScalarToSelf;  

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MinusScalar;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MinusScalarToSelf;  

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MulScalar;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MulScalarToSelf;  

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct DivScalar;

    template<int N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct DivScalarToSelf;  
};

template<class Father, class Child>
struct IVecOpt : Father
{
    using Father::Father;
    using value_type = math_traits_t<Child>;
    static constexpr int len = vec_traits_len<Child>;

    CHTHOLLY_INLINE Child operator+(const Child& y) const noexcept
    {
        return VecOptImplement::Add<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    CHTHOLLY_INLINE Child& operator+=(const Child& y) noexcept
    {
        return VecOptImplement::AddToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    CHTHOLLY_INLINE Child operator-(const Child& y) const noexcept
    {
        return VecOptImplement::Minus<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    CHTHOLLY_INLINE Child& operator-=(const Child& y) noexcept
    {
        return VecOptImplement::MinusToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    CHTHOLLY_INLINE Child operator*(const Child& y) const noexcept
    {
        return VecOptImplement::Mul<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    CHTHOLLY_INLINE Child& operator*=(const Child& y) noexcept
    {
        return VecOptImplement::MulToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    CHTHOLLY_INLINE Child operator/(const Child& y) const noexcept
    {
        return VecOptImplement::Div<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    CHTHOLLY_INLINE Child& operator/=(const Child& y) noexcept
    {
        return VecOptImplement::DivToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    CHTHOLLY_INLINE Child operator-() const noexcept
    {
        return VecOptImplement::Opposite<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this));
    }

    CHTHOLLY_INLINE Child operator+(value_type scalar) const noexcept
    {
        return VecOptImplement::AddScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    CHTHOLLY_INLINE Child& operator+=(value_type scalar) noexcept
    {
        return VecOptImplement::AddScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    friend CHTHOLLY_INLINE Child operator+(value_type a, const Child& x) noexcept
    {
        return x + a;
    }

     CHTHOLLY_INLINE Child operator-(value_type scalar) const noexcept
    {
        return VecOptImplement::MinusScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    CHTHOLLY_INLINE Child& operator-=(value_type scalar) noexcept
    {
        return VecOptImplement::MinusScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    CHTHOLLY_INLINE Child operator*(value_type scalar) const noexcept
    {
        return VecOptImplement::MulScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    CHTHOLLY_INLINE Child& operator*=(value_type scalar) noexcept
    {
        return VecOptImplement::MulScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    friend CHTHOLLY_INLINE Child operator*(value_type a, const Child& x) noexcept
    {
        return x * a;
    }

    CHTHOLLY_INLINE Child operator/(value_type scalar) const noexcept
    {
        return VecOptImplement::DivScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    CHTHOLLY_INLINE Child& operator/=(value_type scalar) noexcept
    {
        return VecOptImplement::DivScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }
};
}

#include "IVecOpt.inl"
#endif