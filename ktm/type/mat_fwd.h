#ifndef _KTM_MAT_FWD_H_
#define _KTM_MAT_FWD_H_

#include <cstdint>
#include <type_traits>

namespace ktm 
{
    
template<size_t Row, size_t Col, typename T, typename = std::enable_if_t<(Row > 1) && (Col > 1) && std::is_arithmetic_v<T>>> 
struct mat;

}

#endif