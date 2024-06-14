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

template<typename R, typename A1, typename OP, size_t ...Ns>
KTM_FUNC void loop_op(R&& self, A1&& l0, OP&& op, std::index_sequence<Ns...>)
{
    ((self[Ns] = op(l0[Ns])), ...);
}

template<size_t LoopN, typename R, typename A1, typename OP>
KTM_FUNC void loop_op(R&& self, A1&& l0, OP&& op)
{
    if constexpr(LoopN <= 4)
        return loop_op(self, std::forward<A1>(l0), std::forward<OP>(op), std::make_index_sequence<LoopN>());
    else
    {
        for(int i = 0; i < LoopN; ++i)
            self[i] = op(l0[i]);
    }
}

template<typename R, typename A1, typename A2, typename OP, size_t ...Ns>
KTM_FUNC void loop_op(R&& self, A1&& l0, A2&& l1, OP&& op, std::index_sequence<Ns...>)
{
    ((self[Ns] = op(l0[Ns], l1[Ns])), ...);
}

template<size_t LoopN, typename R, typename A1, typename A2, typename OP>
KTM_FUNC void loop_op(R&& self, A1&& l0, A2&& l1, OP&& op)
{
    if constexpr(LoopN <= 4)
        return loop_op(self, std::forward<A1>(l0), std::forward<A2>(l1), std::forward<OP>(op), std::make_index_sequence<LoopN>());
    else
    {
        for(int i = 0; i < LoopN; ++i)
            self[i] = op(l0[i], l1[i]);
    }
}

template<typename R, typename A1, typename A2, typename A3, typename OP, size_t ...Ns>
KTM_FUNC void loop_op(R&& self, A1&& l0, A2&& l1, A3&& l2, OP&& op, std::index_sequence<Ns...>)
{
    ((self[Ns] = op(l0[Ns], l1[Ns], l2[Ns])), ...);
}

template<size_t LoopN, typename R, typename A1, typename A2, typename A3, typename OP>
KTM_FUNC void loop_op(R&& self, A1&& l0, A2&& l1, A3&& l2, OP&& op)
{
    if constexpr(LoopN <= 4)
        return loop_op(self, std::forward<A1>(l0), std::forward<A2>(l1), std::forward<A3>(l2), std::forward<OP>(op), std::make_index_sequence<LoopN>());
    else
    {
        for(int i = 0; i < LoopN; ++i)
            self[i] = op(l0[i], l1[i], l2[i]);
    }
}

template<typename R, typename A1, typename T, typename OP, size_t ...Ns>
KTM_FUNC void loop_scalar(R&& self, A1&& l0, const T& scalar, OP&& op, std::index_sequence<Ns...>)
{
    ((self[Ns] = op(l0[Ns], scalar)), ...);
}

template<size_t LoopN, typename R, typename A1, typename T, typename OP>
KTM_FUNC void loop_scalar(R&& self, A1&& l0, const T& scalar, OP&& op)
{
    if constexpr(LoopN <= 4)
        return loop_scalar(self, std::forward<A1>(l0), scalar, std::forward<OP>(op), std::make_index_sequence<LoopN>());
    else
    {
        for(int i = 0; i < LoopN; ++i)
            self[i] = op(l0[i], scalar);
    }
}

template<typename R, typename A1, typename A2, typename T, typename OP, size_t ...Ns>
KTM_FUNC void loop_scalar(R&& self, A1&& l0, A2&& l1, const T& scalar, OP&& op, std::index_sequence<Ns...>)
{
    ((self[Ns] = op(l0[Ns], l1[Ns], scalar)), ...);
}

template<size_t LoopN, typename R, typename A1, typename A2, typename T, typename OP>
KTM_FUNC void loop_scalar(R&& self, A1&& l0, A2&& l1, const T& scalar, OP&& op)
{
    if constexpr(LoopN <= 4)
        return loop_scalar(self, std::forward<A1>(l0), std::forward<A2>(l1), scalar, std::forward<OP>(op), std::make_index_sequence<LoopN>());
    else
    {
        for(int i = 0; i < LoopN; ++i)
            self[i] = op(l0[i], l1[i], scalar);
    }
}

template<typename T, typename A, typename OP, size_t ...Ns>
KTM_FUNC void loop_reduce(T& self, const A& l0, OP&& op, std::index_sequence<Ns...>)
{
    ((self = op(self, l0[Ns + 1])), ...);
}

template<size_t LoopN, typename T, typename A, typename OP>
KTM_FUNC void loop_reduce(T& self, const A& l0, const T& init, OP&& op)
{
    self = init;
    if constexpr(LoopN <= 4)
        return loop_reduce(self, l0, std::forward<OP>(op), std::make_index_sequence<LoopN - 1>());
    else
    {
        for(int i = 1; i < LoopN; ++i)
            self = op(self, l0[i]);
    }
}

template<typename T, typename A, typename U, typename OP, size_t ...Ns>
KTM_FUNC void loop_reduce(T& self, const A& l0, const U& l1, OP&& op, std::index_sequence<Ns...>)
{
    ((self = op(self, l0[Ns + 1], l1[Ns + 1])), ...);
}

template<size_t LoopN, typename T, typename A, typename U, typename OP>
KTM_FUNC void loop_reduce(T& self, const A& l0, const U& l1, const T& init, OP&& op)
{
    self = init;
    if constexpr(LoopN <= 4)
        return loop_reduce(self, l0, l1, std::forward<OP>(op), std::make_index_sequence<LoopN - 1>());
    else
    {
        for(int i = 1; i < LoopN; ++i)
            self = op(self, l0[i], l1[i]);
    }
}

}
}

#endif