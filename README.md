<img align='top' src='img/logo.png' width="128"></img>

> **k**u**t**ori **m**ath，珂朵莉数学库，属于珂学家的图形数学库

✨**如果你喜欢珂朵莉，给我点一点小星星**✨

<img align='right' src='img/kutori.png' width="192"></img>

[![code-size](https://img.shields.io/github/languages/code-size/YGXXD/ktm?style=flat)](https://github.com/YGXXD/ktm/archive/main.zip) [![license](https://img.shields.io/github/license/YGXXD/ktm)](LICENSE) [![tag](https://img.shields.io/github/v/tag/YGXXD/ktm)](https://github.com/YGXXD/ktm/tags)

### 环境 

- 编译器：cl，clang，gcc；
- c++版本：c++17及以上；

### 特性 

- head-only，api层次清晰，包含头文件即可接入项目；
- 代码结构优雅，基本数学类由[模版继承组件化](#组件设计)实现静态ECS；
- 高性能跨平台，simd指令集加速提供计算性能优化；

### 构建和安装 

```shell
# unix
mkdir build && cd build
cmake ..
sudo make install

# windows
cmake -S . -B ./build
cmake --install ./build --config Release
```

### 项目中使用 

```cmake
# CMakeLists
add_executable(exemple main.cpp)

find_package(ktm REQUIRED)
target_link_libraries(exemple PUBLIC ktm::ktm)
```

### 示例 

```c++
#include <ktm/ktm.h>
#include <iostream>

using namespace ktm;
using namespace std;

int main(int argv, char* argc[])
{
    // 构造向量vector
    fvec3 vector { 5.f, -5.f, 1.f };

    // 通过旋转角和轴构建四元数quaternion
    fquat quaternion = fquat::angle_axis(half_pi<float>, fvec3(0.f, 0.6f, 0.8f));
    // 利用四元数quaternion旋转向量vector
    cout << quaternion * vector << endl;
    
    // 通过四元数quaternion构建旋转矩阵rotate
    fmat3x3 rotate = quaternion.matrix3x3();
    // 利用矩阵rotate旋转向量vector
    cout << rotate * vector << endl;

    // 构建仿射变换affine, 定义矩阵model
    faffine3d affine { }; fmat4x4 model;
    // 仿射变换affine进行平移旋转缩放后, 输入到矩阵model
    affine.translate(2.f, 1.f, -3.f).rotate(quaternion).scale(2.f, 2.f, 4.f) >> model;
    // 利用矩阵model变换向量vector
    cout << model * fvec4(vector, 1.f) << endl;

    // 构建视口变换矩阵view
    fmat4x4 view = look_at_lh(fvec3(10.f, 10.f, 10.f), fvec3(), fvec3(0.f, 0.f, 1.f));
    // 构建投影变换矩阵projection
    fmat4x4 projection = perspective_lh(0.5f * half_pi<float>, 16.f / 9.f, 0.1f, 100.f);
    // 利用矩阵model, view, projection构建mvp变换矩阵
    cout << projection * view * model << endl;
 
    return 0;
}
```

### 组件设计

**共享组件**

|组件|功能|
|:-|:-|
|[iarray_util](ktm/interface/shared/iarray_util.h)|支持std::array的特性的包装组件|
|[iarray_add](ktm/interface/shared/iarray_calc.h)|数组和数组之间的加减运算|
|[iarray_mul](ktm/interface/shared/iarray_calc.h)|数组和数组之间的乘除运算|
|[iarray_madd](ktm/interface/shared/iarray_calc.h)|数组和数组之间的乘加复合运算|
|[iarray_add_scalar](ktm/interface/shared/iarray_calc.h)|数组和标量之间的加减运算|
|[iarray_mul_scalar](ktm/interface/shared/iarray_calc.h)|数组和标量之间的乘除运算|
|[iarray_madd_scalar](ktm/interface/shared/iarray_calc.h)|数组和标量之间的乘加复合运算|
|[iarray_io](ktm/interface/shared/iarray_io.h)|数组的输入输出，集成std标准IO流|
|[iarray_tostring](ktm/interface/shared/iarray_tostring.h)|数组到字符串的转换功能|

**向量组件** 

|组件|功能|
|:-|:-|
|[ivec_calc](ktm/interface/vector/ivec_calc.h)|三维向量和三维向量，三位向量和标量之间的加减乘除运算|
|[ivec_array](ktm/interface/vector/ivec_array.h)|支持向量强制转化为数组|
|[ivec_data](ktm/interface/vector/ivec_data.h)|包含向量的数据，构造函数，向量混洗|

**矩阵组件** 

|组件|功能|
|:-|:-|
|[imat_mul](ktm/interface/matrix/imat_mul.h)|矩阵和矩阵，矩阵和向量之间的乘法运算|
|[imat_array](ktm/interface/matrix/imat_array.h)|支持矩阵强制转化为数组|
|[imat_make](ktm/interface/matrix/imat_make.h)|提供了构造矩阵的静态方法|
|[imat_data](ktm/interface/matrix/imat_data.h)|包含矩阵的数据和构造函数|

**四元数组件** 

|组件|功能|
|:-|:-|
|[iquat_mul](ktm/interface/quaternion/iquat_mul.h)|四元数和四元数，四元数和三维向量之间的乘法运算|
|[iquat_array](ktm/interface/quaternion/iquat_array.h)|支持四元数强制转化为数组|
|[iquat_make](ktm/interface/quaternion/iquat_make.h)|提供了构造四元数的静态方法|
|[iquat_data](ktm/interface/quaternion/iquat_data.h)|包含四元数的数据，构造函数，获取四元数旋转信息的方法|

**复数组件** 

|组件|功能|
|:-|:-|
|[icomp_mul](ktm/interface/complex/icomp_mul.h)|复数和复数，复数和二维向量之间的乘法运算|
|[icomp_array](ktm/interface/complex/icomp_array.h)|支持复数强制转化为数组|
|[icomp_make](ktm/interface/complex/icomp_make.h)|提供了构造复数的静态方法|
|[icomp_data](ktm/interface/complex/icomp_data.h)|包含复数的数据，构造函数，获取复数旋转信息的方法|

**复合组件** 

|组件|组成部分|
|:-|:-|
|[iarray_add_calc](ktm/interface/shared/iarray_calc.h)|iarray_add，iarray_add_scalar|
|[iarray_mul_calc](ktm/interface/shared/iarray_calc.h)|iarray_mul，iarray_mul_scalar|
|[iarray_madd_calc](ktm/interface/shared/iarray_calc.h)|iarray_madd，iarray_madd_scalar|
|[iarray_calc](ktm/interface/shared/iarray_calc.h)|iarray_add_calc，iarray_mul_calc，iarray_madd_calc|

**基本数学类** 

|类|组成部分|
|:-|:-|
|[vec](ktm/type/vec.h)|ivec_data，ivec_array，ivec_calc，iarray_io，iarray_calc，iarray_util|
|[mat](ktm/type/mat.h)|imat_data，imat_make，imat_array，imat_mul，iarray_io，iarray_add，iarray_madd_scalar，iarray_mul_scalar，iarray_util|
|[quat](ktm/type/quat.h)|iquat_data，iquat_make，iquat_array，iquat_mul，iarray_io，iarray_add，iarray_madd_scalar，iarray_mul_scalar，iarray_util|
|[comp](ktm/type/comp.h)|icomp_data，icomp_make，icomp_array，icomp_mul，iarray_io，iarray_add，iarray_madd_scalar，iarray_mul_scalar，iarray_util|

### 许可证

&emsp;&emsp;ktm使用MIT许可证，详细信息请参见[LICENSE](LICENSE)文件。