#include "Math/MathType/BaseType.h"

namespace ktm
{
template<class Father, class Child>
struct IMatData;

template<class Father, size_t Col, typename T>
struct alignas(sizeof(vec<Col, T>)) IMatData<Father, mat<Col, 2, T>> : Father
{
    using Father::Father;
    IMatData(const vec<Col, T>& col0, const vec<Col, T>& col1) : columns{ col0, col1 } { }
private:
    vec<Col, T> columns[2];
};

template<class Father, size_t Col, typename T>
struct alignas(sizeof(vec<Col, T>)) IMatData<Father, mat<Col, 3, T>> : Father
{
    using Father::Father;
    IMatData(const vec<Col, T>& col0, const vec<Col, T>& col1, const vec<Col, T>& col2) : columns{ col0, col1, col2 } { }
private:
    vec<Col, T> columns[3];
};

template<class Father, size_t Col, typename T>
struct alignas(sizeof(vec<Col, T>)) IMatData<Father, mat<Col, 4, T>> : Father
{
    using Father::Father;
    IMatData(const vec<Col, T>& col0, const vec<Col, T>& col1, const vec<Col, T>& col2, const vec<Col, T>& col3) : columns{ col0, col1, col2, col3 } { }
private:
    vec<Col, T> columns[4];
};

}