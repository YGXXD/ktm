# ktm

> **k**u**t**ori **m**ath，珂朵莉数学库，属于珂学家开发游戏的3D数学库

⭐ *如果你喜欢珂朵莉，给我点一点小星星*

[![repo-size](https://img.shields.io/github/languages/code-size/YGXXD/ktm?style=flat)](https://github.com/YGXXD/ktm/archive/main.zip) [![license](https://img.shields.io/github/license/YGXXD/ktm)](LICENSE) [![tag](https://img.shields.io/github/v/tag/YGXXD/ktm)](https://github.com/YGXXD/ktm/tags) 

**环境**

- 编译器：MSVC，Clang，GCC
- C++版本：C++17以上

**特点** 

- head-only，引入头文件即可使用
- 支持Simd指令集加速，SSE，SSE2，SSE3，SSE4.1，SSE4.2，Neon，Wasm
- 代码结构清晰，类利用模板实现组件化

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

using namespace ktm;
using namespace std;

int main() {
    // 构造向量v
    fvec3 v { -6.f, 7.f, 9.f };
    // 通过角和轴构建四元数q
    fquat q = fquat::angle_axis(half_pi<float>, fvec3(0.f, 0.6f, 0.8f));
    // 通过四元数q转为矩阵
    fmat3x3 m = q.matrix3x3();

    // 利用四元数q旋转向量v
    cout << q * v << endl;
    // 利用矩阵m旋转向量v
    cout << m * v << endl;
    
    return 0;
}
```