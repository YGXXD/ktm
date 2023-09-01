#ifndef _I_VEC_OPT_H_
#define _I_VEC_OPT_H_

#include "Math/TypeBase.h"

namespace ktm
{

struct VecComImplement
{
private:
    template<class Father, class Child> friend class IVecCom;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Add;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct AddToSelf;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct Minus;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, math_traits_t<V>> && vec_traits_len<V> == N>>
    struct MinusToSelf; 

    template<class Father, class Child> friend class IVecCom;
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
struct IVecCom : Father
{
    using Father::Father;
    using value_type = math_traits_t<Child>;
    static constexpr size_t len = vec_traits_len<Child>;

    Child operator+(const Child& y) const noexcept
    {
        return VecComImplement::Add<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    Child& operator+=(const Child& y) noexcept
    {
        return VecComImplement::AddToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    Child operator-(const Child& y) const noexcept
    {
        return VecComImplement::Minus<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    Child& operator-=(const Child& y) noexcept
    {
        return VecComImplement::MinusToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    Child operator*(const Child& y) const noexcept
    {
        return VecComImplement::Mul<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    Child& operator*=(const Child& y) noexcept
    {
        return VecComImplement::MulToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    Child operator/(const Child& y) const noexcept
    {
        return VecComImplement::Div<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), y);
    }

    Child& operator/=(const Child& y) noexcept
    {
        return VecComImplement::DivToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), y);
    }

    Child operator-() const noexcept
    {
        return VecComImplement::Opposite<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this));
    }

    Child operator+(value_type scalar) const noexcept
    {
        return VecComImplement::AddScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    Child& operator+=(value_type scalar) noexcept
    {
        return VecComImplement::AddScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    friend Child operator+(value_type a, const Child& x) noexcept
    {
        return x + a;
    }

    Child operator-(value_type scalar) const noexcept
    {
        return VecComImplement::MinusScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    Child& operator-=(value_type scalar) noexcept
    {
        return VecComImplement::MinusScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    Child operator*(value_type scalar) const noexcept
    {
        return VecComImplement::MulScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    Child& operator*=(value_type scalar) noexcept
    {
        return VecComImplement::MulScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    friend Child operator*(value_type a, const Child& x) noexcept
    {
        return x * a;
    }

    Child operator/(value_type scalar) const noexcept
    {
        return VecComImplement::DivScalar<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this), scalar);
    }

    Child& operator/=(value_type scalar) noexcept
    {
        return VecComImplement::DivScalarToSelf<len, value_type, Child>::Call(reinterpret_cast<Child&>(*this), scalar);
    }

    value_type ReduceSum() const noexcept
    {
        return VecComImplement::ReduceSum<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this)); 
    }

    value_type ReduceMin() const noexcept
    {
        return VecComImplement::ReduceMin<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this)); 
    }

    value_type ReduceMax() const noexcept
    {
        return VecComImplement::ReduceMax<len, value_type, Child>::Call(reinterpret_cast<const Child&>(*this)); 
    }
};
}

#include "IVecCom.inl"
#endif