#ifndef _I_VEC_OPT_H_
#define _I_VEC_OPT_H_

#include "Math/MathType/BaseType.h"

namespace ktm
{

template<class Father, class Child>
struct IVecOpt : Father
{
    using Father::Father;
    using value_type = vec_traits_t<Child>;
    static constexpr size_t len = vec_traits_len<Child>;

    Child operator+(const Child& y) const noexcept;
    Child& operator+=(const Child& y) noexcept;
    Child operator-(const Child& y) const noexcept;
    Child& operator-=(const Child& y) noexcept;
    Child operator*(const Child& y) const noexcept;
    Child& operator*=(const Child& y) noexcept;
    Child operator/(const Child& y) const noexcept;
    Child& operator/=(const Child& y) noexcept;
    Child operator-() const noexcept;
    Child operator+(value_type scalar) const noexcept;
    Child& operator+=(value_type scalar) noexcept;
    friend CHTHOLLY_INLINE Child operator+(value_type a, const Child& x) noexcept { return x + a; }
    Child operator-(value_type scalar) const noexcept;
    Child& operator-=(value_type scalar) noexcept;
    Child operator*(value_type scalar) const noexcept;
    Child& operator*=(value_type scalar) noexcept;
    friend CHTHOLLY_INLINE Child operator*(value_type a, const Child& x) noexcept { return x * a; }
    Child operator/(value_type scalar) const noexcept;
    Child& operator/=(value_type scalar) noexcept;
    value_type get_sum() const noexcept;
    value_type get_min() const noexcept;
    value_type get_max() const noexcept;
};

namespace detail
{
struct vec_opt_implement
{
private:
    template<class Father, class Child> friend class ::ktm::IVecOpt;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct add;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct add_to_self;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct minus;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct minus_to_self; 

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct mul;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct mul_to_self;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct div;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct div_to_self; 

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct opposite;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct add_scalar;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct add_scalar_to_self;  

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct minus_scalar;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct minus_scalar_to_self;  

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct mul_scalar;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct mul_scalar_to_self;  

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct div_scalar;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct div_scalar_to_self;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct reduce_add;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct reduce_min;

    template<size_t N, typename T, class V, typename = std::enable_if_t<std::is_same_v<T, vec_traits_t<V>> && vec_traits_len<V> == N>>
    struct reduce_max;
};

}
}

#include "IVecOpt.inl"
#endif