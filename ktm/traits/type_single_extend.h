//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_TYPE_SINGLE_EXTEND_H_
#define _KTM_TYPE_SINGLE_EXTEND_H_

#include "type_traits_function.h"

namespace ktm 
{

// type container
template<typename ...Ts>
struct type_list 
{
    static inline constexpr bool is_all_same = std::is_same_vs<Ts...>;
    static inline constexpr bool is_exist_same = std::is_exist_same_vs<Ts...>;
    template<size_t N>
    using index = std::select_idx_t<N, Ts...>;
};

// template container
template<template<typename ...> class ...Tps>
struct template_list 
{
    static inline constexpr bool is_all_same = std::is_template_same_vs<Tps...>;
    static inline constexpr bool is_exist_same = std::is_template_exist_same_vs<Tps...>;
};

// single_extends's template
template<class Child>
struct empty_child 
{ 
protected:
    inline constexpr Child* child_ptr() noexcept { return static_cast<Child*>(this); }
    inline constexpr const Child* child_ptr() const noexcept { return static_cast<const Child*>(this); }
};

template<typename TpList, class Child, typename = std::enable_if_t<!TpList::is_exist_same>>
struct single_extends;

template<class Child>
struct single_extends<template_list<>, Child> 
{
    using type = empty_child<Child>;
};

template<template<class F, class C> class Father, 
         template<class F, class C> class... Fathers,
         class Child>
struct single_extends<template_list<Father, Fathers...>, Child>  
{
    using type = Father<typename single_extends<template_list<Fathers...>, Child>::type, Child>;
};

template<typename TpList, class Child>
using single_extends_t = typename single_extends<TpList, Child>::type;

// example:
// struct D : single_extends<template_list<C, B, A>, D>::type { }
// struct D's inheritance is { D : C : B : A : empty_child }

}

#define KTM_CRTP_CHILD_IMPL_VALUE(class_name, implement) decltype(check_##implement<class_name>(0))::value
#define KTM_CRTP_CHILD_IMPL_CHECK(interface, implement) \
template <typename CheckT, typename T> \
static inline constexpr auto check_##implement(T) \
    -> std::enable_if_t<ktm::is_same_function_traits_v<decltype(&CheckT::interface), decltype(&CheckT::implement)>, std::true_type>; \
template<typename CheckT> static inline constexpr std::false_type check_##implement(...);

#endif