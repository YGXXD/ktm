<img align='top' src='img/logo.png' width="128"></img>

> **k**u**t**ori **m**ath，珂朵莉数学库，属于珂学家开发游戏的3D数学库

<img align='right' src='img/kutori.png' width="192"></img>

✨**如果你喜欢珂朵莉，给我点一点小星星**✨

[![code-size](https://img.shields.io/github/languages/code-size/YGXXD/ktm?style=flat)](https://github.com/YGXXD/ktm/archive/main.zip) [![license](https://img.shields.io/github/license/YGXXD/ktm)](LICENSE) [![tag](https://img.shields.io/github/v/tag/YGXXD/ktm)](https://github.com/YGXXD/ktm/tags)

**环境**

- 编译器：cl，clang，gcc
- c++版本：c++17及以上

**特性**

- head-only，引入头文件即可使用
- 支持simd指令集，sse，sse2，sse3，sse4.1，sse4.2，neon，wasm
- 代码结构清晰，使用模板实现数学类组件化

**构建和安装**

```shell
# unix
mkdir build && cd build
cmake ..
sudo make install

# windows
cmake -S . -B ./build
cmake --install ./build --config Release
```

**示例** 

```c++
#include <ktm/ktm.h>
#include <iostream>

using namespace ktm;
using namespace std;

int main() {
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
    faffine3d affine {}; fmat4x4 model;
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