#ifndef _KTM_VEC_DATA_INL_
#define _KTM_VEC_DATA_INL_

#include "vec_data_fwd.h"
#include "../../setup.h"

template<size_t N, typename T, typename Void>
struct ktm::detail::vec_data_implement::vec_storage
{
private:
    constexpr static KTM_INLINE size_t align() noexcept
    {
        if constexpr(N == 2)
            return 2 * sizeof(T);
        else if constexpr(N == 3 || N == 4)
            return 4 * sizeof(T);
        else
            return sizeof(T);
    }
    constexpr static KTM_INLINE size_t elem_num() noexcept
    {
        if constexpr(N == 3)
            return 4;
        else 
            return N;
    }
public:
    struct alignas(align()) type 
    {
    private:
        T e[elem_num()];
    };

};

template<size_t ON, size_t IN, typename T, typename Void>
struct ktm::detail::vec_data_implement::vec_swizzle
{
    using V = vec<IN, T>;
    using RetV = vec<ON, T>;
    template<size_t ...E>
    static KTM_INLINE std::enable_if_t<sizeof...(E) == ON && ((E < IN) && ...), RetV> call(const V& v) noexcept
    {
        return RetV(v[E]...);
    }
};

#endif