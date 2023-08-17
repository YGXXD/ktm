#ifndef _MATHOLLY_H_
#define _MATHOLLY_H_

#include "BaseType.h"

static void mathTest()
{
    xxd::float3 a = {8, 10, 8};
    xxd::float3 b = {9, 2, 9};
    xxd::float3 c = {10, 4, 10};
    xxd::float3 d = {7, 10, 7};
    auto ret = (a * b) / (c - d);

    std::cout << ret.x << "," << ret.y << "," << ret.z << std::endl;

    ret = ret / 4;
    std::cout << ret.x << "," << ret.y << "," << ret.z << std::endl;

}

#endif