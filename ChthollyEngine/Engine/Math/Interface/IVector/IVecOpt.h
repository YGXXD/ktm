#ifndef _I_VEC_OPT_H_
#define _I_VEC_OPT_H_

#include "Math/MathType/BaseType.h"

namespace ktm
{

struct VecOptImplement
{
private:
    template<class Father, class Child> friend class IVecOpt;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Add;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct AddToSelf;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Minus;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MinusToSelf; 

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Mul;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MulToSelf;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Div;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct DivToSelf; 

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Opposite;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct AddScalar;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct AddScalarToSelf;  

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MinusScalar;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MinusScalarToSelf;  

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MulScalar;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MulScalarToSelf;  

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct DivScalar;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct DivScalarToSelf;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct ReduceSum;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct ReduceMin;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct ReduceMax;
};

template<class Father, class Child>
struct IVecOpt : Father
{
    using Father::Father;
    using value_type = math_traits_t<Child>;
    static constexpr size_t len = vec_traits_len<Child>;

    Child operator+(const Child& y) const noexcept
    {
        return VecOptImplement::Add<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    Child& operator+=(const Child& y) noexcept
    {
        return VecOptImplement::AddToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    Child operator-(const Child& y) const noexcept
    {
        return VecOptImplement::Minus<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    Child& operator-=(const Child& y) noexcept
    {
        return VecOptImplement::MinusToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    Child operator*(const Child& y) const noexcept
    {
        return VecOptImplement::Mul<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    Child& operator*=(const Child& y) noexcept
    {
        return VecOptImplement::MulToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    Child operator/(const Child& y) const noexcept
    {
        return VecOptImplement::Div<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    Child& operator/=(const Child& y) noexcept
    {
        return VecOptImplement::DivToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    Child operator-() const noexcept
    {
        return VecOptImplement::Opposite<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this));
    }

    Child operator+(value_type scalar) const noexcept
    {
        return VecOptImplement::AddScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    Child& operator+=(value_type scalar) noexcept
    {
        return VecOptImplement::AddScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    friend CHTHOLLY_INLINE Child operator+(value_type a, const Child& x) noexcept
    {
        return x + a;
    }

    Child operator-(value_type scalar) const noexcept
    {
        return VecOptImplement::MinusScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    Child& operator-=(value_type scalar) noexcept
    {
        return VecOptImplement::MinusScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    Child operator*(value_type scalar) const noexcept
    {
        return VecOptImplement::MulScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    Child& operator*=(value_type scalar) noexcept
    {
        return VecOptImplement::MulScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    friend CHTHOLLY_INLINE Child operator*(value_type a, const Child& x) noexcept
    {
        return x * a;
    }

    Child operator/(value_type scalar) const noexcept
    {
        return VecOptImplement::DivScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    Child& operator/=(value_type scalar) noexcept
    {
        return VecOptImplement::DivScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    value_type GetSum() const noexcept
    {
        return VecOptImplement::ReduceSum<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this)); 
    }

    value_type GetMin() const noexcept
    {
        return VecOptImplement::ReduceMin<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this)); 
    }

    value_type GetMax() const noexcept
    {
        return VecOptImplement::ReduceMax<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this)); 
    }
};
}

#include "IVecOpt.inl"
#endif