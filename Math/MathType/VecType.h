#ifndef _VEC_TYPE_H_
#define _VEC_TYPE_H_

#include "Math/type/vec.h"

namespace ktm
{

template<size_t N>
using fvec = vec<N, float>;
using fvec1 = fvec<1>;
using fvec2 = fvec<2>;
using fvec3 = fvec<3>;
using fvec4 = fvec<4>;

template<size_t N>
using svec = vec<N, int>;
using svec1 = svec<1>;
using svec2 = svec<2>;
using svec3 = svec<3>;
using svec4 = svec<4>;

template<size_t N>
using uvec = vec<N, unsigned int>;
using uvec1 = uvec<1>;
using uvec2 = uvec<2>;
using uvec3 = uvec<3>;
using uvec4 = uvec<4>;

template<size_t N>
using dvec = vec<N, double>;
using dvec1 = dvec<1>;
using dvec2 = dvec<2>;
using dvec3 = dvec<3>;
using dvec4 = dvec<4>;

}

#endif