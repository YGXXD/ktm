#ifndef _I_VECTOR_H_
#define _I_VECTOR_H_

namespace ktl
{
template<class Father, class Child>
struct IVector : Father
{
    using Father::Father;
    
};
}

#endif