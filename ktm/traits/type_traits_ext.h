//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _STD_TYPE_TRAITS_EXT_H_
#define _STD_TYPE_TRAITS_EXT_H_

#include <type_traits>
#include <cstddef>

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

// 选择类型, 根据索引选择后面的类型
template<size_t N, typename ...Ts>
struct select_idx;

template<size_t N, typename T, typename ...Ts>
struct select_idx<N, T, Ts...> { using type = typename select_idx<N - 1, Ts...>::type; };

template<typename T, typename ...Ts>
struct select_idx<0, T, Ts...> { using type = T; };

template<size_t N, typename ...Ts>
using select_idx_t = typename select_idx<N, Ts...>::type;

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
struct is_template_same : false_type { };

template<template<typename ...> class Tp>
struct is_template_same<Tp, Tp> : true_type { };

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

#endif