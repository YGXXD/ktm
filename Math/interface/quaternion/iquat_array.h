#ifndef _KTM_I_QUAT_ARRAY_H_
#define _KTM_I_QUAT_ARRAY_H_

#include "../../type/basic.h"
#include <array>

namespace ktm
{
template<class Father, class Child>
struct iquat_array;

template<class Father,typename T>
struct iquat_array<Father, quat<T>> : Father
{
    using Father::Father;
    using array_type = std::array<T, 4>;
};
}

#endif