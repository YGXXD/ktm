//  MIT License
//
//  Copyright (c) 2024 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_LOOP_UTIL_H_
#define _KTM_LOOP_UTIL_H_

#include <utility>
#include <functional>
#include "../setup.h"

namespace ktm
{
namespace detail
{
template<size_t LoopN, typename T>
struct loop_op_new
{
    template<typename OP, typename ...As>
    static KTM_FUNC void call(T& out, OP&& op, As&& ...ls)
    {
        if constexpr(LoopN <= 4)
            call(out, std::forward<OP>(op), std::make_index_sequence<LoopN>(), std::forward<As>(ls)...);
        else
            call(out, std::forward<OP>(op), LoopN, std::forward<As>(ls)...);
    }
private:
    template<typename OP, typename ...As, size_t ...Ns>
    static KTM_FUNC void call(T& out, OP&& op, std::index_sequence<Ns...>, As&& ...ls)
    {
        constexpr auto apply_lambda = [](T& out, OP&& op, As&& ...ls, size_t index) -> void { out[index] = op(ls[index]...); };
        (apply_lambda(out, std::forward<OP>(op), std::forward<As>(ls)..., Ns), ...);
    }

    template<typename OP, typename ...As>
    static KTM_FUNC void call(T& out, OP&& op, size_t loop, As&& ...ls)
    {
        for(int i = 0; i < loop; ++i)
            out[i] = op(ls[i]...);
    }
};

template<size_t LoopN>
struct loop_op_new<LoopN, void>
{
    template<typename OP, typename ...As>
    static KTM_FUNC void call(OP&& op, As&& ...ls)
    {
        if constexpr(LoopN <= 4)
            call(std::forward<OP>(op), std::make_index_sequence<LoopN>(), std::forward<As>(ls)...);
        else
            call(std::forward<OP>(op), LoopN, std::forward<As>(ls)...);
    }
private:
    template<typename OP, typename ...As, size_t ...Ns>
    static KTM_FUNC void call(OP&& op, std::index_sequence<Ns...>, As&& ...ls)
    {
        constexpr auto apply_lambda = [](OP&& op, As&& ...ls, size_t index) -> void { op(ls[index]...); };
        (apply_lambda(std::forward<OP>(op), std::forward<As>(ls)..., Ns), ...);
    }

    template<typename OP, typename ...As>
    static KTM_FUNC void call(OP&& op, size_t loop, As&& ...ls)
    {
        for(int i = 0; i < loop; ++i)
            op(ls[i]...);
    } 
};

template<typename R, typename A1, typename OP, size_t ...Ns>
KTM_FUNC void loop_op(R&& self, A1&& l0, OP&& op, std::index_sequence<Ns...>)
{
    ((self[Ns] = op(l0[Ns])), ...);
}

template<typename R, typename A1, typename OP>
KTM_FUNC void loop_op(R&& self, A1&& l0, OP&& op, size_t loop)
{
    for(int i = 0; i < loop; ++i)
        self[i] = op(l0[i]);
}

template<size_t LoopN, typename R, typename A1, typename OP>
KTM_FUNC void loop_op(R&& self, A1&& l0, OP&& op)
{
    if constexpr(LoopN <= 4)
        loop_op(self, std::forward<A1>(l0), std::forward<OP>(op), std::make_index_sequence<LoopN>());
    else
        loop_op(self, std::forward<A1>(l0), std::forward<OP>(op), LoopN);
}

template<typename R, typename A1, typename A2, typename OP, size_t ...Ns>
KTM_FUNC void loop_op(R&& self, A1&& l0, A2&& l1, OP&& op, std::index_sequence<Ns...>)
{
    ((self[Ns] = op(l0[Ns], l1[Ns])), ...);
}

template<typename R, typename A1, typename A2, typename OP>
KTM_FUNC void loop_op(R&& self, A1&& l0, A2&& l1, OP&& op, size_t loop)
{
    for(int i = 0; i < loop; ++i)
        self[i] = op(l0[i], l1[i]);
}

template<size_t LoopN, typename R, typename A1, typename A2, typename OP>
KTM_FUNC void loop_op(R&& self, A1&& l0, A2&& l1, OP&& op)
{
    if constexpr(LoopN <= 4)
        loop_op(self, std::forward<A1>(l0), std::forward<A2>(l1), std::forward<OP>(op), std::make_index_sequence<LoopN>());
    else
        loop_op(self, std::forward<A1>(l0), std::forward<A2>(l1), std::forward<OP>(op), LoopN);
}

template<typename R, typename A1, typename A2, typename A3, typename OP, size_t ...Ns>
KTM_FUNC void loop_op(R&& self, A1&& l0, A2&& l1, A3&& l2, OP&& op, std::index_sequence<Ns...>)
{
    ((self[Ns] = op(l0[Ns], l1[Ns], l2[Ns])), ...);
}

template<typename R, typename A1, typename A2, typename A3, typename OP>
KTM_FUNC void loop_op(R&& self, A1&& l0, A2&& l1, A3&& l2, OP&& op, size_t loop)
{
    for(int i = 0; i < loop; ++i)
        self[i] = op(l0[i], l1[i], l2[i]);
}

template<size_t LoopN, typename R, typename A1, typename A2, typename A3, typename OP>
KTM_FUNC void loop_op(R&& self, A1&& l0, A2&& l1, A3&& l2, OP&& op)
{
    if constexpr(LoopN <= 4)
        loop_op(self, std::forward<A1>(l0), std::forward<A2>(l1), std::forward<A3>(l2), std::forward<OP>(op), std::make_index_sequence<LoopN>());
    else
        loop_op(self, std::forward<A1>(l0), std::forward<A2>(l1), std::forward<A3>(l2), std::forward<OP>(op), LoopN); 
}

// template<typename A0, typename OP, size_t ...Ns>
// KTM_FUNC void loop_op_ref(A0&& l0, OP&& op, std::index_sequence<Ns...>)
// {
//     (op(l0[Ns]), ...);
// }

// template<typename A0, typename OP>
// KTM_FUNC void loop_op_ref(A0&& l0, OP&& op, size_t loop)
// {
//     for(int i = 0; i < loop; ++i)
//         op(l0[i]);
// }

// template<size_t LoopN, typename A0, typename OP>
// KTM_FUNC void loop_op_ref(A0&& l0, OP&& op)
// {
//     if constexpr(LoopN <= 4)
//         loop_op_ref(std::forward<A0>(l0), std::forward<OP>(op), std::make_index_sequence<LoopN>());
//     else
//         loop_op_ref(std::forward<A0>(l0), std::forward<OP>(op), LoopN);
// }

// template<typename A0, typename A1, typename OP, size_t ...Ns>
// KTM_FUNC void loop_op_ref(A0&& l0, A1&& l1, OP&& op, std::index_sequence<Ns...>)
// {
//     (op(l0[Ns], l1[Ns]), ...);
// }

// template<typename A0, typename A1, typename OP>
// KTM_FUNC void loop_op_ref(A0&& l0, A1&& l1, OP&& op, size_t loop)
// {
//     for(int i = 0; i < loop; ++i)
//         op(l0[i], l1[i]);
// }

// template<size_t LoopN, typename A0, typename A1, typename OP>
// KTM_FUNC void loop_op_ref(A0&& l0, A1&& l1, OP&& op)
// {
//     if constexpr(LoopN <= 4)
//         loop_op_ref(std::forward<A0>(l0), std::forward<A1>(l1), std::forward<OP>(op), std::make_index_sequence<LoopN>());
//     else
//         loop_op_ref(std::forward<A0>(l0), std::forward<A1>(l1), std::forward<OP>(op), LoopN);
// }

// template<typename A0, typename A1, typename A2, typename OP, size_t ...Ns>
// KTM_FUNC void loop_op_ref(A0&& l0, A1&& l1, A2&& l2, OP&& op, std::index_sequence<Ns...>)
// {
//     (op(l0[Ns], l1[Ns], l2[Ns]), ...);
// }

// template<typename A0, typename A1, typename A2, typename OP>
// KTM_FUNC void loop_op_ref(A0&& l0, A1&& l1, A2&& l2, OP&& op, size_t loop)
// {
//     for(int i = 0; i < loop; ++i)
//         op(l0[i], l1[i], l2[i]);
// }

// template<size_t LoopN, typename A0, typename A1, typename A2, typename OP>
// KTM_FUNC void loop_op_ref(A0&& l0, A1&& l1, A2&& l2, OP&& op)
// {
//     if constexpr(LoopN <= 4)
//         loop_op_ref(std::forward<A0>(l0), std::forward<A1>(l1), std::forward<A2>(l2), std::forward<OP>(op), std::make_index_sequence<LoopN>());
//     else
//         loop_op_ref(std::forward<A0>(l0), std::forward<A1>(l1), std::forward<A2>(l2), std::forward<OP>(op), LoopN);
// }

// template<typename A0, typename A1, typename A2, typename A3, typename OP, size_t ...Ns>
// KTM_FUNC void loop_op_ref(A0&& l0, A1&& l1, A2&& l2, A3&& l3, OP&& op, std::index_sequence<Ns...>)
// {
//     (op(l0[Ns], l1[Ns], l2[Ns], l3[Ns]), ...);
// }

// template<typename A0, typename A1, typename A2, typename A3, typename OP>
// KTM_FUNC void loop_op_ref(A0&& l0, A1&& l1, A2&& l2, A3&& l3, OP&& op, size_t loop)
// {
//     for(int i = 0; i < loop; ++i)
//         op(l0[i], l1[i], l2[i], l3[i]);
// }

// template<size_t LoopN, typename A0, typename A1, typename A2, typename A3, typename OP>
// KTM_FUNC void loop_op_ref(A0&& l0, A1&& l1, A2&& l2, A3&& l3, OP&& op)
// {
//     if constexpr(LoopN <= 4)
//         loop_op_ref(std::forward<A0>(l0), std::forward<A1>(l1), std::forward<A2>(l2), std::forward<A3>(l3), std::forward<OP>(op), std::make_index_sequence<LoopN>());
//     else
//         loop_op_ref(std::forward<A0>(l0), std::forward<A1>(l1), std::forward<A2>(l2), std::forward<A3>(l3), std::forward<OP>(op), LoopN); 
// }

template<typename T, typename A, typename OP, size_t ...Ns>
KTM_FUNC void loop_reduce(T& self, const A& l0, OP&& op, std::index_sequence<Ns...>)
{
    ((self = op(self, l0[Ns + 1])), ...);
}

template<typename T, typename A, typename OP>
KTM_FUNC void loop_reduce(T& self, const A& l0, OP&& op, size_t loop)
{
    for(int i = 0; i < loop; ++i)
        self = op(self, l0[i + 1]);
}

template<size_t LoopN, typename T, typename A, typename OP>
KTM_FUNC void loop_reduce(T& self, const A& l0, const T& init, OP&& op)
{
    self = init;
    if constexpr(LoopN <= 4)
        loop_reduce(self, l0, std::forward<OP>(op), std::make_index_sequence<LoopN - 1>());
    else
        loop_reduce(self, l0, std::forward<OP>(op), LoopN - 1); 
}

template<typename T, typename A, typename U, typename OP, size_t ...Ns>
KTM_FUNC void loop_reduce(T& self, const A& l0, const U& l1, OP&& op, std::index_sequence<Ns...>)
{
    ((self = op(self, l0[Ns + 1], l1[Ns + 1])), ...);
}

template<typename T, typename A, typename U, typename OP>
KTM_FUNC void loop_reduce(T& self, const A& l0, const U& l1, OP&& op, size_t loop)
{
    for(int i = 0; i < loop; ++i)
        self = op(self, l0[i + 1], l1[i + 1]);
}

template<size_t LoopN, typename T, typename A, typename U, typename OP>
KTM_FUNC void loop_reduce(T& self, const A& l0, const U& l1, const T& init, OP&& op)
{
    self = init;
    if constexpr(LoopN <= 4)
        loop_reduce(self, l0, l1, std::forward<OP>(op), std::make_index_sequence<LoopN - 1>());
    else
        loop_reduce(self, l0, l1, std::forward<OP>(op), LoopN - 1);
}

}
}

#endif