#ifndef _MATHOLLY_H_
#define _MATHOLLY_H_

#include "BaseType.h"

static void mathTest()
{
    xxd::int2 a = {8, 10};
    xxd::int2 b = {9, 2};
    xxd::int2 c = {10, 4};
    xxd::int2 d = {7, 10};
    auto ret = (a * b) / (c - d);

    std::cout << ret.x << "," << ret.y << std::endl;
}

#endif