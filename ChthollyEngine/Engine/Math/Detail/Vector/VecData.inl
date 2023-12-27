#ifndef _VEC_DATA_INL_
#define _VEC_DATA_INL_

#include "VecDataFwd.h"

template<size_t N, typename T>
struct ktm::detail::vec_data_implement::vec_storage
{
    struct type 
    {
    private:
        template<size_t ON, size_t IN, typename VT, size_t ...E>
        friend struct vec_swizzle;
        T e[N];
    };
};

template<size_t ON, size_t IN, typename T, size_t ...E>
struct ktm::detail::vec_data_implement::vec_swizzle
{
    static_assert(sizeof...(E) == ON);
    static CHTHOLLY_INLINE vec<ON, T> call(const typename vec_storage<IN, T>::type& st) noexcept
    {
        return vec<ON, T>(st.e[E]...);
    }
};

#endif