#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <type_traits>

// std traits extensions
namespace std
{

// 选择类型, E为true选择前者，否则为后者
template<bool E, typename TT, typename FT>
struct select_if;

template<typename TT, typename FT>
struct select_if<true, TT, FT> { using type = TT; };

template<typename TT, typename FT>
struct select_if<false, TT, FT> { using type = FT; };

template<bool E, typename TT, typename FT>
using select_if_t = typename select_if<E, TT, FT>::type;

// 多个类型相比较,都相同返回true,有一个不相同返回false
template<class ...Tps>
inline bool is_same_vs;

template<class Tp1, class Tp2, class ...Tps>
inline constexpr bool is_same_vs<Tp1, Tp2, Tps...> = is_same_vs<Tp1, Tp2> && is_same_vs<Tp2, Tps...>;

template<class Tp, class Up>
inline constexpr bool is_same_vs<Tp, Up> = is_same_v<Tp, Up>;

template<class Tp>
inline constexpr bool is_same_vs<Tp> = true;

template<>
inline constexpr bool is_same_vs<> = true;

// 多个类型检测,都为数学基本类型返回true,有一个不为数学基本类型返回false
template<class ...Tps>
inline bool is_arithmetic_vs;

template<class Tp, class ...Tps>
inline constexpr bool is_arithmetic_vs<Tp, Tps...> = is_arithmetic_vs<Tp> && is_arithmetic_vs<Tps...>;

template<class Tp>
inline constexpr bool is_arithmetic_vs<Tp> = is_arithmetic_v<Tp>;

template<>
inline constexpr bool is_arithmetic_vs<> = false;

// 多个类型检测,存在相同的类型返回true,没有相同类型返回false
template<class ...Tps>
inline bool is_exist_same_vs;

template<class Tp, class ...Tps>
inline constexpr bool is_exist_same_vs<Tp, Tps...> = (is_same_v<Tp, Tps> || ...) || is_exist_same_vs<Tps...>;

template<class Tp>
inline constexpr bool is_exist_same_vs<Tp> = false;

template<>
inline constexpr bool is_exist_same_vs<> = false;

// 检测两个模版类型是否相同
template<template<typename ...> class Tp, template<typename ...> class Up>
struct is_template_same : std::false_type { };

template<template<typename ...> class Tp>
struct is_template_same<Tp, Tp> : std::true_type { };

template<template<typename ...> class Tp, template<typename ...> class Up>
inline constexpr bool is_template_same_v = is_template_same<Tp, Up>::value;

// 检测多个模版类型是否相同
template<template<typename ...> class ...Tps>
inline bool is_template_same_vs;

template<template<typename ...> class Tp1, template<typename ...> class Tp2, template<typename ...> class ...Tps>
inline constexpr bool is_template_same_vs<Tp1, Tp2, Tps...> = is_template_same_vs<Tp1, Tp2> && is_template_same_vs<Tp2, Tps...>;

template<template<typename ...> class Tp, template<typename ...> class Up>
inline constexpr bool is_template_same_vs<Tp, Up> = is_template_same_v<Tp, Up>;

template<template<typename ...> class Tp>
inline constexpr bool is_template_same_vs<Tp> = true;

template<>
inline constexpr bool is_template_same_vs<> = true;

// 检测存在模版类型相同
template<template<typename ...> class ...Tps>
inline bool is_template_exist_same_vs;

template<template<typename ...> class Tp, template<typename ...> class ...Tps>
inline constexpr bool is_template_exist_same_vs<Tp, Tps...> = (is_template_same_v<Tp, Tps> || ...) || is_template_exist_same_vs<Tps...>;

template<template<typename ...> class Tp>
inline constexpr bool is_template_exist_same_vs<Tp> = false;

template<>
inline constexpr bool is_template_exist_same_vs<> = false;

}

// ktl template 
namespace ktl
{

// 存储类型的容器
template<typename ...Ts>
struct TypeList 
{
    static inline constexpr bool IsAllSameType = std::is_same_vs<Ts...>;
    static inline constexpr bool IsExistSameType = std::is_exist_same_vs<Ts...>;
    static inline constexpr bool IsAllArithmetic = std::is_arithmetic_vs<Ts...>;
};

// 模版特化后的实例类型
template<typename TList, template<typename ...> class Tp>
struct TInstance;

template<template<typename ...> class Tp, typename ...Ts>
struct TInstance<TypeList<Ts...>, Tp>
{
	using Type = Tp<Ts...>;
};

template<typename TList, template<typename ...> class Tp>
using TInstance_t = typename TInstance<TList, Tp>::Type;

// 存储模版未特化类型的容器
template<template<typename ...> class ...Tps>
struct TemplateList 
{
    static inline constexpr bool IsAllSameTemplate = std::is_template_same_vs<Tps...>;
    static inline constexpr bool IsExistSameTemplate = std::is_template_exist_same_vs<Tps...>;
};

// 单继承化模版
template<class Child>
struct Nil { };

template<typename TpList, class Child, typename = std::enable_if_t<!TpList::IsExistSameTemplate>>
struct SingleExtends;

template<class Child>
struct SingleExtends<TemplateList<>, Child> 
{
    using FatherType = Nil<Child>;
};

template <template<class F, class C> class Father, 
          template<class F, class C> class... Fathers,
          class Child>
struct SingleExtends<TemplateList<Father, Fathers...>, Child>  
{
    using FatherType = Father<typename SingleExtends<TemplateList<Fathers...>, Child>::FatherType, Child>;
};

template<typename TpList, class Child>
using SingleExtends_t = typename SingleExtends<TpList, Child>::FatherType;

// D : C : B : A : Nil
// struct D : SingleExtends_t<TemplateList<C, B, A>, D>::type { }
// 父类里面特化的模版为最后一级子类, A<D>, B<D>, C<D>
}

#endif