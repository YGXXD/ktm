#ifndef _KTM_QUAT_FWD_H_
#define _KTM_QUAT_FWD_H_

#include <cstdint>
#include <type_traits>

namespace ktm 
{
    
template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>> 
struct quat;

}

#endif