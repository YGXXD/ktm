//  MIT License
//
//  Copyright (c) 2023-2026 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main()
{
    const ktm::fvec2 v2(1.0f, 2.0f);
    TEST_EQUAL(v2.swizzle<0>(), ktm::fvec1(1.0f));
    TEST_EQUAL(v2.swizzle<1>(), ktm::fvec1(2.0f));
    TEST_EQUAL((v2.swizzle<0, 1>()), ktm::fvec2(1.0f, 2.0f));
    TEST_EQUAL((v2.swizzle<1, 0>()), ktm::fvec2(2.0f, 1.0f));
    TEST_EQUAL((v2.swizzle<1, 1>()), ktm::fvec2(2.0f, 2.0f));

    TEST_EQUAL(v2.xy(), ktm::fvec2(1.0f, 2.0f));
    TEST_EQUAL(v2.yx(), ktm::fvec2(2.0f, 1.0f));
    TEST_EQUAL(v2.rg(), ktm::fvec2(1.0f, 2.0f));
    TEST_EQUAL(v2.gr(), ktm::fvec2(2.0f, 1.0f));

    const ktm::fvec3 v3(1.0f, 2.0f, 3.0f);
    TEST_EQUAL(v3.swizzle<0>(), ktm::fvec1(1.0f));
    TEST_EQUAL(v3.swizzle<2>(), ktm::fvec1(3.0f));
    TEST_EQUAL((v3.swizzle<2, 0>()), ktm::fvec2(3.0f, 1.0f));
    TEST_EQUAL((v3.swizzle<1, 1>()), ktm::fvec2(2.0f, 2.0f));
    TEST_EQUAL((v3.swizzle<0, 1, 2>()), ktm::fvec3(1.0f, 2.0f, 3.0f));
    TEST_EQUAL((v3.swizzle<2, 1, 0>()), ktm::fvec3(3.0f, 2.0f, 1.0f));
    TEST_EQUAL((v3.swizzle<1, 1, 1>()), ktm::fvec3(2.0f, 2.0f, 2.0f));

    TEST_EQUAL(v3.xyz(), ktm::fvec3(1.0f, 2.0f, 3.0f));
    TEST_EQUAL(v3.xzy(), ktm::fvec3(1.0f, 3.0f, 2.0f));
    TEST_EQUAL(v3.yzx(), ktm::fvec3(2.0f, 3.0f, 1.0f));
    TEST_EQUAL(v3.yxz(), ktm::fvec3(2.0f, 1.0f, 3.0f));
    TEST_EQUAL(v3.zxy(), ktm::fvec3(3.0f, 1.0f, 2.0f));
    TEST_EQUAL(v3.zyx(), ktm::fvec3(3.0f, 2.0f, 1.0f));

    TEST_EQUAL(v3.rgb(), ktm::fvec3(1.0f, 2.0f, 3.0f));
    TEST_EQUAL(v3.rbg(), ktm::fvec3(1.0f, 3.0f, 2.0f));
    TEST_EQUAL(v3.grb(), ktm::fvec3(2.0f, 1.0f, 3.0f));
    TEST_EQUAL(v3.gbr(), ktm::fvec3(2.0f, 3.0f, 1.0f));
    TEST_EQUAL(v3.brg(), ktm::fvec3(3.0f, 1.0f, 2.0f));
    TEST_EQUAL(v3.bgr(), ktm::fvec3(3.0f, 2.0f, 1.0f));

    TEST_EQUAL(v3.xy(), ktm::fvec2(1.0f, 2.0f));
    TEST_EQUAL(v3.yx(), ktm::fvec2(2.0f, 1.0f));
    TEST_EQUAL(v3.xz(), ktm::fvec2(1.0f, 3.0f));
    TEST_EQUAL(v3.zx(), ktm::fvec2(3.0f, 1.0f));
    TEST_EQUAL(v3.yz(), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL(v3.zy(), ktm::fvec2(3.0f, 2.0f));

    TEST_EQUAL(v3.rg(), ktm::fvec2(1.0f, 2.0f));
    TEST_EQUAL(v3.gr(), ktm::fvec2(2.0f, 1.0f));
    TEST_EQUAL(v3.rb(), ktm::fvec2(1.0f, 3.0f));
    TEST_EQUAL(v3.br(), ktm::fvec2(3.0f, 1.0f));
    TEST_EQUAL(v3.gb(), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL(v3.bg(), ktm::fvec2(3.0f, 2.0f));

    const ktm::fvec4 v4(1.0f, 2.0f, 3.0f, 4.0f);
    TEST_EQUAL(v4.swizzle<3>(), ktm::fvec1(4.0f));
    TEST_EQUAL((v4.swizzle<3, 1>()), ktm::fvec2(4.0f, 2.0f));
    TEST_EQUAL((v4.swizzle<0, 0>()), ktm::fvec2(1.0f, 1.0f));
    TEST_EQUAL((v4.swizzle<3, 2, 1>()), ktm::fvec3(4.0f, 3.0f, 2.0f));
    TEST_EQUAL((v4.swizzle<0, 2, 1>()), ktm::fvec3(1.0f, 3.0f, 2.0f));
    TEST_EQUAL((v4.swizzle<0, 1, 2, 3>()), ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f));
    TEST_EQUAL((v4.swizzle<3, 2, 1, 0>()), ktm::fvec4(4.0f, 3.0f, 2.0f, 1.0f));
    TEST_EQUAL((v4.swizzle<2, 2, 2, 2>()), ktm::fvec4(3.0f, 3.0f, 3.0f, 3.0f));

    TEST_EQUAL(v4.xyzw(), ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f));
    TEST_EQUAL(v4.xywz(), ktm::fvec4(1.0f, 2.0f, 4.0f, 3.0f));
    TEST_EQUAL(v4.xzwy(), ktm::fvec4(1.0f, 3.0f, 4.0f, 2.0f));
    TEST_EQUAL(v4.xzyw(), ktm::fvec4(1.0f, 3.0f, 2.0f, 4.0f));
    TEST_EQUAL(v4.xwyz(), ktm::fvec4(1.0f, 4.0f, 2.0f, 3.0f));
    TEST_EQUAL(v4.xwzy(), ktm::fvec4(1.0f, 4.0f, 3.0f, 2.0f));
    TEST_EQUAL(v4.yzwx(), ktm::fvec4(2.0f, 3.0f, 4.0f, 1.0f));
    TEST_EQUAL(v4.yzxw(), ktm::fvec4(2.0f, 3.0f, 1.0f, 4.0f));
    TEST_EQUAL(v4.ywxz(), ktm::fvec4(2.0f, 4.0f, 1.0f, 3.0f));
    TEST_EQUAL(v4.ywzx(), ktm::fvec4(2.0f, 4.0f, 3.0f, 1.0f));
    TEST_EQUAL(v4.yxzw(), ktm::fvec4(2.0f, 1.0f, 3.0f, 4.0f));
    TEST_EQUAL(v4.yxwz(), ktm::fvec4(2.0f, 1.0f, 4.0f, 3.0f));
    TEST_EQUAL(v4.zwxy(), ktm::fvec4(3.0f, 4.0f, 1.0f, 2.0f));
    TEST_EQUAL(v4.zwyx(), ktm::fvec4(3.0f, 4.0f, 2.0f, 1.0f));
    TEST_EQUAL(v4.zxyw(), ktm::fvec4(3.0f, 1.0f, 2.0f, 4.0f));
    TEST_EQUAL(v4.zxwy(), ktm::fvec4(3.0f, 1.0f, 4.0f, 2.0f));
    TEST_EQUAL(v4.zywx(), ktm::fvec4(3.0f, 2.0f, 4.0f, 1.0f));
    TEST_EQUAL(v4.zyxw(), ktm::fvec4(3.0f, 2.0f, 1.0f, 4.0f));
    TEST_EQUAL(v4.wxyz(), ktm::fvec4(4.0f, 1.0f, 2.0f, 3.0f));
    TEST_EQUAL(v4.wxzy(), ktm::fvec4(4.0f, 1.0f, 3.0f, 2.0f));
    TEST_EQUAL(v4.wyzx(), ktm::fvec4(4.0f, 2.0f, 3.0f, 1.0f));
    TEST_EQUAL(v4.wyxz(), ktm::fvec4(4.0f, 2.0f, 1.0f, 3.0f));
    TEST_EQUAL(v4.wzxy(), ktm::fvec4(4.0f, 3.0f, 1.0f, 2.0f));
    TEST_EQUAL(v4.wzyx(), ktm::fvec4(4.0f, 3.0f, 2.0f, 1.0f));

    TEST_EQUAL(v4.rgba(), ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f));
    TEST_EQUAL(v4.rgab(), ktm::fvec4(1.0f, 2.0f, 4.0f, 3.0f));
    TEST_EQUAL(v4.rbag(), ktm::fvec4(1.0f, 3.0f, 4.0f, 2.0f));
    TEST_EQUAL(v4.rbga(), ktm::fvec4(1.0f, 3.0f, 2.0f, 4.0f));
    TEST_EQUAL(v4.ragb(), ktm::fvec4(1.0f, 4.0f, 2.0f, 3.0f));
    TEST_EQUAL(v4.rabg(), ktm::fvec4(1.0f, 4.0f, 3.0f, 2.0f));
    TEST_EQUAL(v4.gbar(), ktm::fvec4(2.0f, 3.0f, 4.0f, 1.0f));
    TEST_EQUAL(v4.gbra(), ktm::fvec4(2.0f, 3.0f, 1.0f, 4.0f));
    TEST_EQUAL(v4.garb(), ktm::fvec4(2.0f, 4.0f, 1.0f, 3.0f));
    TEST_EQUAL(v4.gabr(), ktm::fvec4(2.0f, 4.0f, 3.0f, 1.0f));
    TEST_EQUAL(v4.grba(), ktm::fvec4(2.0f, 1.0f, 3.0f, 4.0f));
    TEST_EQUAL(v4.grab(), ktm::fvec4(2.0f, 1.0f, 4.0f, 3.0f));
    TEST_EQUAL(v4.barg(), ktm::fvec4(3.0f, 4.0f, 1.0f, 2.0f));
    TEST_EQUAL(v4.bagr(), ktm::fvec4(3.0f, 4.0f, 2.0f, 1.0f));
    TEST_EQUAL(v4.brga(), ktm::fvec4(3.0f, 1.0f, 2.0f, 4.0f));
    TEST_EQUAL(v4.brag(), ktm::fvec4(3.0f, 1.0f, 4.0f, 2.0f));
    TEST_EQUAL(v4.bgar(), ktm::fvec4(3.0f, 2.0f, 4.0f, 1.0f));
    TEST_EQUAL(v4.bgra(), ktm::fvec4(3.0f, 2.0f, 1.0f, 4.0f));
    TEST_EQUAL(v4.argb(), ktm::fvec4(4.0f, 1.0f, 2.0f, 3.0f));
    TEST_EQUAL(v4.arbg(), ktm::fvec4(4.0f, 1.0f, 3.0f, 2.0f));
    TEST_EQUAL(v4.agbr(), ktm::fvec4(4.0f, 2.0f, 3.0f, 1.0f));
    TEST_EQUAL(v4.agrb(), ktm::fvec4(4.0f, 2.0f, 1.0f, 3.0f));
    TEST_EQUAL(v4.abrg(), ktm::fvec4(4.0f, 3.0f, 1.0f, 2.0f));
    TEST_EQUAL(v4.abgr(), ktm::fvec4(4.0f, 3.0f, 2.0f, 1.0f));

    TEST_EQUAL(v4.xyz(), ktm::fvec3(1.0f, 2.0f, 3.0f));
    TEST_EQUAL(v4.xzy(), ktm::fvec3(1.0f, 3.0f, 2.0f));
    TEST_EQUAL(v4.yzx(), ktm::fvec3(2.0f, 3.0f, 1.0f));
    TEST_EQUAL(v4.yxz(), ktm::fvec3(2.0f, 1.0f, 3.0f));
    TEST_EQUAL(v4.zxy(), ktm::fvec3(3.0f, 1.0f, 2.0f));
    TEST_EQUAL(v4.zyx(), ktm::fvec3(3.0f, 2.0f, 1.0f));
    TEST_EQUAL(v4.xyw(), ktm::fvec3(1.0f, 2.0f, 4.0f));
    TEST_EQUAL(v4.xwy(), ktm::fvec3(1.0f, 4.0f, 2.0f));
    TEST_EQUAL(v4.ywx(), ktm::fvec3(2.0f, 4.0f, 1.0f));
    TEST_EQUAL(v4.yxw(), ktm::fvec3(2.0f, 1.0f, 4.0f));
    TEST_EQUAL(v4.wxy(), ktm::fvec3(4.0f, 1.0f, 2.0f));
    TEST_EQUAL(v4.wyx(), ktm::fvec3(4.0f, 2.0f, 1.0f));
    TEST_EQUAL(v4.xzw(), ktm::fvec3(1.0f, 3.0f, 4.0f));
    TEST_EQUAL(v4.xwz(), ktm::fvec3(1.0f, 4.0f, 3.0f));
    TEST_EQUAL(v4.zwx(), ktm::fvec3(3.0f, 4.0f, 1.0f));
    TEST_EQUAL(v4.zxw(), ktm::fvec3(3.0f, 1.0f, 4.0f));
    TEST_EQUAL(v4.wxz(), ktm::fvec3(4.0f, 1.0f, 3.0f));
    TEST_EQUAL(v4.wzx(), ktm::fvec3(4.0f, 3.0f, 1.0f));
    TEST_EQUAL(v4.yzw(), ktm::fvec3(2.0f, 3.0f, 4.0f));
    TEST_EQUAL(v4.ywz(), ktm::fvec3(2.0f, 4.0f, 3.0f));
    TEST_EQUAL(v4.zwy(), ktm::fvec3(3.0f, 4.0f, 2.0f));
    TEST_EQUAL(v4.zyw(), ktm::fvec3(3.0f, 2.0f, 4.0f));
    TEST_EQUAL(v4.wyz(), ktm::fvec3(4.0f, 2.0f, 3.0f));
    TEST_EQUAL(v4.wzy(), ktm::fvec3(4.0f, 3.0f, 2.0f));

    TEST_EQUAL(v4.rgb(), ktm::fvec3(1.0f, 2.0f, 3.0f));
    TEST_EQUAL(v4.rbg(), ktm::fvec3(1.0f, 3.0f, 2.0f));
    TEST_EQUAL(v4.grb(), ktm::fvec3(2.0f, 1.0f, 3.0f));
    TEST_EQUAL(v4.gbr(), ktm::fvec3(2.0f, 3.0f, 1.0f));
    TEST_EQUAL(v4.brg(), ktm::fvec3(3.0f, 1.0f, 2.0f));
    TEST_EQUAL(v4.bgr(), ktm::fvec3(3.0f, 2.0f, 1.0f));
    TEST_EQUAL(v4.rga(), ktm::fvec3(1.0f, 2.0f, 4.0f));
    TEST_EQUAL(v4.rag(), ktm::fvec3(1.0f, 4.0f, 2.0f));
    TEST_EQUAL(v4.gar(), ktm::fvec3(2.0f, 4.0f, 1.0f));
    TEST_EQUAL(v4.gra(), ktm::fvec3(2.0f, 1.0f, 4.0f));
    TEST_EQUAL(v4.arg(), ktm::fvec3(4.0f, 1.0f, 2.0f));
    TEST_EQUAL(v4.agr(), ktm::fvec3(4.0f, 2.0f, 1.0f));
    TEST_EQUAL(v4.rba(), ktm::fvec3(1.0f, 3.0f, 4.0f));
    TEST_EQUAL(v4.rab(), ktm::fvec3(1.0f, 4.0f, 3.0f));
    TEST_EQUAL(v4.bar(), ktm::fvec3(3.0f, 4.0f, 1.0f));
    TEST_EQUAL(v4.bra(), ktm::fvec3(3.0f, 1.0f, 4.0f));
    TEST_EQUAL(v4.arb(), ktm::fvec3(4.0f, 1.0f, 3.0f));
    TEST_EQUAL(v4.abr(), ktm::fvec3(4.0f, 3.0f, 1.0f));
    TEST_EQUAL(v4.gba(), ktm::fvec3(2.0f, 3.0f, 4.0f));
    TEST_EQUAL(v4.gab(), ktm::fvec3(2.0f, 4.0f, 3.0f));
    TEST_EQUAL(v4.bga(), ktm::fvec3(3.0f, 2.0f, 4.0f));
    TEST_EQUAL(v4.bag(), ktm::fvec3(3.0f, 4.0f, 2.0f));
    TEST_EQUAL(v4.agb(), ktm::fvec3(4.0f, 2.0f, 3.0f));
    TEST_EQUAL(v4.abg(), ktm::fvec3(4.0f, 3.0f, 2.0f));

    TEST_EQUAL(v4.xy(), ktm::fvec2(1.0f, 2.0f));
    TEST_EQUAL(v4.yx(), ktm::fvec2(2.0f, 1.0f));
    TEST_EQUAL(v4.xz(), ktm::fvec2(1.0f, 3.0f));
    TEST_EQUAL(v4.zx(), ktm::fvec2(3.0f, 1.0f));
    TEST_EQUAL(v4.xw(), ktm::fvec2(1.0f, 4.0f));
    TEST_EQUAL(v4.wx(), ktm::fvec2(4.0f, 1.0f));
    TEST_EQUAL(v4.yz(), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL(v4.zy(), ktm::fvec2(3.0f, 2.0f));
    TEST_EQUAL(v4.yw(), ktm::fvec2(2.0f, 4.0f));
    TEST_EQUAL(v4.wy(), ktm::fvec2(4.0f, 2.0f));
    TEST_EQUAL(v4.zw(), ktm::fvec2(3.0f, 4.0f));
    TEST_EQUAL(v4.wz(), ktm::fvec2(4.0f, 3.0f));

    TEST_EQUAL(v4.rg(), ktm::fvec2(1.0f, 2.0f));
    TEST_EQUAL(v4.gr(), ktm::fvec2(2.0f, 1.0f));
    TEST_EQUAL(v4.rb(), ktm::fvec2(1.0f, 3.0f));
    TEST_EQUAL(v4.br(), ktm::fvec2(3.0f, 1.0f));
    TEST_EQUAL(v4.ra(), ktm::fvec2(1.0f, 4.0f));
    TEST_EQUAL(v4.ar(), ktm::fvec2(4.0f, 1.0f));
    TEST_EQUAL(v4.gb(), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL(v4.bg(), ktm::fvec2(3.0f, 2.0f));
    TEST_EQUAL(v4.ga(), ktm::fvec2(2.0f, 4.0f));
    TEST_EQUAL(v4.ag(), ktm::fvec2(4.0f, 2.0f));
    TEST_EQUAL(v4.ba(), ktm::fvec2(3.0f, 4.0f));
    TEST_EQUAL(v4.ab(), ktm::fvec2(4.0f, 3.0f));

    return 0;
}
