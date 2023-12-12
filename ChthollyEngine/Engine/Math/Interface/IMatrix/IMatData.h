#ifndef _I_MAT_DATA_H_
#define _I_MAT_DATA_H_ 

#include "Math/Library/ArtcBase.h"

namespace ktm
{
template<class Father, class Child>
struct IMatData;

template<class Father, size_t Col, typename T>
struct alignas(sizeof(vec<Col, T>)) IMatData<Father, mat<2, Col, T>> : Father
{
    using Father::Father;
    IMatData(const vec<Col, T>& col0, const vec<Col, T>& col1) noexcept : columns{ col0, col1 } { }
private:
    vec<Col, T> columns[2];
};

template<class Father, size_t Col, typename T>
struct alignas(sizeof(vec<Col, T>)) IMatData<Father, mat<3, Col, T>> : Father
{
    using Father::Father;
    IMatData(const vec<Col, T>& col0, const vec<Col, T>& col1, const vec<Col, T>& col2) noexcept : columns{ col0, col1, col2 } { }
private:
    vec<Col, T> columns[3];
};

template<class Father, size_t Col, typename T>
struct alignas(sizeof(vec<Col, T>)) IMatData<Father, mat<4, Col, T>> : Father
{
    using Father::Father;
    IMatData(const vec<Col, T>& col0, const vec<Col, T>& col1, const vec<Col, T>& col2, const vec<Col, T>& col3) noexcept : columns{ col0, col1, col2, col3 } { }
private:
    vec<Col, T> columns[4];
};

}

#endif