#ifndef _MATH_H_
#define _MATH_H_

#include "MathType.h"
#include <time.h>
#include <simd/simd.h>
#include "Vec.h"
#include "TypeBase.h"

static inline simd_float4 t1(simd_float4 v)
{
    simd_float4 x = {1, 1, 66, 1};
	return v + x;
}

static inline ktl::float4 t2(ktl::float4 v)
{
    ktl::float4 x = {1, 1, 66, 1}; 
	return v + x;
}

static inline ktl::Vec<4, float, true> t3(ktl::Vec<4, float, true> v)
{
    //ktl::Vec<2, float, true> t();
    ktl::Vec<2, float, true> t1(1,66);
    ktl::Vec<4, float, true> t( t1,t1);
    float32x4_t b = vld1q_f32(t.data.p) + vld1q_f32(v.data.p);
    ktl::Vec<4, float, true> r;
    vst1q_f32(r.data.p, b);
    
    return r;
}

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

    clock_t start1;
    clock_t start2;
    clock_t end1;
    clock_t end2;
    clock_t start3;
    clock_t end3;
    simd_float4 v = {1, 1, 66, 1};
    start1 = clock();
    for(int i = 0; i < 10000000; ++i)
    {
        v = t1(v);
    }
    end1 = clock();
    ktl::float4 x = {1, 1, 66, 1}; 
    start2 = clock();
    for(int i = 0; i < 10000000; ++i)
    {
        x = t2(x);
    }
    end2 = clock();
    ktl::Vec<4, float, true> y(1, 1, 66, 1); 
    start3 = clock();
    for(int i = 0; i < 10000000; ++i)
    {
        y = t3(y);
    }
    end3 = clock();
    std::cout << (double)(end1 - start1) << ", " << (double)(end2 - start2) << ", " << (double)(end3 - start3) << std::endl;
    // ktl::Vec<double, 4> v = ktl::MakeVec<double, 4>({ 5.0, 2.0, 3.0 }, 1);
    // std::cout << v.m[0] << ", " << v.m[1] << ", " << v.m[2] << ", " << v.m[3] << std::endl;
    std::cout << v[1] << "," << x.y << "," << y.data.p[1] << std::endl;
    
    ktl::Vec<1, float, false> tr(16); 
    ktl::Vec<2, float, false> tt(12, 15); 
    ktl::Vec<4, float, false> uu(tr);

    std::cout << uu.data.p[0] << ", " << uu.data.p[1] << ", " << uu.data.p[2] << ", " << uu.data.p[3] << std::endl; 

    std::shared_ptr<int> p;
}

#endif