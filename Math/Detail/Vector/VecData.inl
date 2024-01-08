#ifndef _VEC_DATA_INL_
#define _VEC_DATA_INL_

#include "VecDataFwd.h"

template<size_t N, typename T>
struct ktm::detail::vec_data_implement::vec_storage
{
private:
    constexpr static CHTHOLLY_INLINE size_t align() noexcept
    {
        if constexpr(N == 2)
        {
            return 2 * sizeof(T);
        }
        else if constexpr(N == 3 || N == 4)
        {
            return 4 * sizeof(T);
        }
        else
        {
            return sizeof(T);
        }
    }
    constexpr static CHTHOLLY_INLINE size_t elem_num() noexcept
    {
        if constexpr(N == 3)
        {
            return 4;
        }
        else 
        {
            return N;
        }
    }
public:
    struct alignas(align()) type 
    {
    private:
        T e[elem_num()];
    };

};

template<size_t ON, size_t IN, typename T, size_t ...E>
struct ktm::detail::vec_data_implement::vec_swizzle
{
    static_assert(ON <= IN && sizeof...(E) == ON && ((E < IN) && ...));
    using V = vec<IN, T>;
    using RetV = vec<ON, T>;
    static CHTHOLLY_INLINE RetV call(const V& v) noexcept
    {
        return RetV(v[E]...);
    }
};

#endif