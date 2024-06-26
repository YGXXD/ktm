//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_VEC_DATA_INL_
#define _KTM_VEC_DATA_INL_

#include "vec_data_fwd.h"
#include "../../setup.h"
#include "../../type/vec_fwd.h"

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_data_implement::vec_storage
{
private:
    constexpr static KTM_INLINE size_t elem_num() noexcept
    {
        if constexpr(N == 3)
            return 4;
        else 
            return N;
    }

    constexpr static KTM_INLINE size_t align() noexcept
    {
        if constexpr(N <= 4)
            return elem_num() * sizeof(T);
        else
            return sizeof(T);
    }
public:
    struct alignas(align()) type 
    {
    private:
        T e[elem_num()];
    };

};

template<size_t OUT, size_t IN, typename T, typename Void>
struct ktm::detail::vec_data_implement::vec_swizzle
{
private:
    template<size_t ...E>
    constexpr static KTM_INLINE bool enable_swizzle() noexcept
    {
        return (sizeof...(E) == OUT) && ((E < IN) && ...);
    }
public:
    using V = vec<IN, T>;
    using RetV = vec<OUT, T>;

    template<size_t ...E>
    static KTM_INLINE std::enable_if_t<enable_swizzle<E...>(), RetV> call(const V& v) noexcept
    {
        return RetV(v[E]...);
    }
};

#endif