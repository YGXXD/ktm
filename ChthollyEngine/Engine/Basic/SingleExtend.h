#ifndef _SINGLE_EXTEND_H_
#define _SINGLE_EXTEND_H_

#include "TraitsEx.h"

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
struct EmptyChild { };

template<typename TpList, class Child, typename = std::enable_if_t<!TpList::IsExistSameTemplate>>
struct SingleExtends;

template<class Child>
struct SingleExtends<TemplateList<>, Child> 
{
    using FatherType = EmptyChild<Child>;
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