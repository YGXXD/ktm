#ifndef _I_ADD_H_
#define _I_ADD_H_

#include "Chtholly.h"

namespace ktl
{
template<typename F, typename C>
struct IAdd 
{

};

template<typename F, typename C>
struct IVectorAdd
{

};

struct VecD : SingleExtends<TemplateList<IVectorAdd, IAdd>, VecD> { };

}

#endif