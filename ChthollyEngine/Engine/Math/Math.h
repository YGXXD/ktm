#ifndef _MATH_H_
#define _MATH_H_

#include "MathType.h"
#include <time.h>

static void mathTest()
{
    ktl::double4 a = {8, 10, 8, 10};
    ktl::double4 b = {9, 2, 9, 2};
    ktl::double4 c = {10, 4, 10, 4};
    ktl::double4 d = {7, 10, 7, 10};
    auto ret = (a * b) / (c - d);

    std::cout << ret.x << ", " << ret.y << ", " << ret.z << ", " << ret.w << std::endl;

    ret *= (a * b) / (c - d);
    std::cout << ret.x << ", " << ret.y << ", " << ret.z << ", " << ret.w << std::endl;

    // clock_t start1;
    // clock_t start2;
    // clock_t end1;
    // clock_t end2;
    // start1 = clock();
    // for(int i = 0; i < 10000000; ++i)
    // {
    //     ktl::Vec<double, 4> v = {1, 1, 66, 1};
    // }
    // end1 = clock();
    // start2 = clock();
    // for(int i = 0; i < 10000000; ++i)
    // {
    //    ktl::double4 x = {1, 1, 66, 1}; 
     
    // }
    // end2 = clock();
    // std::cout << (double)(end1 - start1) << ", " << (double)(end2 - start2) << std::endl;
    // ktl::Vec<double, 4> v = ktl::MakeVec<double, 4>({ 5.0, 2.0, 3.0 }, 1);
    // std::cout << v.m[0] << ", " << v.m[1] << ", " << v.m[2] << ", " << v.m[3] << std::endl;

}

#endif