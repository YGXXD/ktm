#ifndef _MATHOLLY_H_
#define _MATHOLLY_H_

#include "BaseType.h"

static void mathTest()
{
    xxd::double4 a = {8, 10, 8, 10};
    xxd::double4 b = {9, 2, 9, 2};
    xxd::double4 c = {10, 4, 10, 4};
    xxd::double4 d = {7, 10, 7, 10};
    auto ret = (a * b) / (c - d);

    std::cout << ret.x << ", " << ret.y << ", " << ret.z << ", " << ret.w << std::endl;

    ret *= (a * b) / (c - d);
    std::cout << ret.x << ", " << ret.y << ", " << ret.z << ", " << ret.w << std::endl;

}

#endif