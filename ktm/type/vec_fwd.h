#ifndef _KTM_VEC_FWD_H_
#define _KTM_VEC_FWD_H_

#include <cstddef>
#include <type_traits>

namespace ktm 
{
    
template<size_t N, typename T, typename = std::enable_if_t<(N > 0) && std::is_arithmetic_v<T>>> 
struct vec;

}

#endif