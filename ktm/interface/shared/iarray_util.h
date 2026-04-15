//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_I_ARRAY_UTIL_H_
#define _KTM_I_ARRAY_UTIL_H_

#include <tuple>
#include <cstddef>
#include "../../setup.h"

namespace ktm
{

template <class Father, class Child>
struct iarray_util : Father
{
    using Father::child_ptr;
    using Father::Father;

    KTM_INLINE auto& to_array() noexcept { return child_ptr()->to_array_impl(); }

    KTM_INLINE const auto& to_array() const noexcept { return child_ptr()->to_array_impl(); }

    KTM_INLINE auto begin() noexcept { return to_array().begin(); }

    KTM_INLINE const auto begin() const noexcept { return to_array().begin(); }

    KTM_INLINE auto end() noexcept { return to_array().end(); }

    KTM_INLINE const auto end() const noexcept { return to_array().end(); }

    KTM_INLINE auto rbegin() noexcept { return to_array().rbegin(); }

    KTM_INLINE const auto rbegin() const noexcept { return to_array().rbegin(); }

    KTM_INLINE auto rend() noexcept { return to_array().rend(); }

    KTM_INLINE const auto rend() const noexcept { return to_array().rend(); }

    KTM_INLINE const auto cbegin() const noexcept { return begin(); }

    KTM_INLINE const auto cend() const noexcept { return end(); }

    KTM_INLINE const auto crbegin() const noexcept { return rbegin(); }

    KTM_INLINE const auto crend() const noexcept { return rend(); }

    KTM_INLINE constexpr size_t size() const noexcept { return std::tuple_size_v<std::decay_t<decltype(to_array())>>; }

    KTM_INLINE constexpr size_t max_size() const noexcept { return size(); }

    KTM_INLINE constexpr bool empty() const noexcept { return false; }

    KTM_INLINE auto& at(size_t i) { return to_array().at(i); }

    KTM_INLINE const auto& at(size_t i) const { return to_array().at(i); }

    KTM_INLINE auto& front() noexcept { return to_array().front(); }

    KTM_INLINE const auto& front() const noexcept { return to_array().front(); }

    KTM_INLINE auto& back() noexcept { return to_array().back(); }

    KTM_INLINE const auto& back() const noexcept { return to_array().back(); }

    KTM_INLINE auto data() noexcept { return to_array().data(); }

    KTM_INLINE const auto data() const noexcept { return to_array().data(); }

    KTM_INLINE auto& operator[](size_t i) noexcept { return to_array()[i]; }

    KTM_INLINE const auto& operator[](size_t i) const noexcept { return to_array()[i]; }

    friend KTM_INLINE bool operator==(const Child& x, const Child& y) noexcept { return x.to_array() == y.to_array(); }

    friend KTM_INLINE bool operator!=(const Child& x, const Child& y) noexcept { return x.to_array() != y.to_array(); }

    friend KTM_INLINE bool operator<(const Child& x, const Child& y) noexcept { return x.to_array() < y.to_array(); }

    friend KTM_INLINE bool operator>(const Child& x, const Child& y) noexcept { return x.to_array() > y.to_array(); }

    friend KTM_INLINE bool operator<=(const Child& x, const Child& y) noexcept { return x.to_array() <= y.to_array(); }

    friend KTM_INLINE bool operator>=(const Child& x, const Child& y) noexcept { return x.to_array() >= y.to_array(); }
};

} // namespace ktm

#endif