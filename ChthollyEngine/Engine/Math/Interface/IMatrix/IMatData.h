#include "Math/MathType/BaseType.h"

namespace ktm
{
template<class Father, class Child>
struct IMatData;

template<class Father, size_t Raw, typename T>
struct alignas(alignof(vec<Raw, T>)) IMatData<Father, mat<2, Raw, T>> : Father
{
    using Father::Father;
    IMatData(const vec<Raw, T>& col1, const vec<Raw, T>& col2) : columns{ col1, col2 } { }
private:
    vec<Raw, T> columns[2];
};

template<class Father, size_t Raw, typename T>
struct alignas(alignof(vec<Raw, T>)) IMatData<Father, mat<3, Raw, T>> : Father
{
    using Father::Father;
    IMatData(const vec<Raw, T>& col1, const vec<Raw, T>& col2, const vec<Raw, T>& col3) : columns{ col1, col2, col3 } { }
private:
    vec<Raw, T> columns[3];
};

template<class Father, size_t Raw, typename T>
struct alignas(alignof(vec<Raw, T>)) IMatData<Father, mat<4, Raw, T>> : Father
{
    using Father::Father;
    IMatData(const vec<Raw, T>& col1, const vec<Raw, T>& col2, const vec<Raw, T>& col3, const vec<Raw, T>& col4) : columns{ col1, col2, col3, col4 } { }
private:
    vec<Raw, T> columns[4];
};

}