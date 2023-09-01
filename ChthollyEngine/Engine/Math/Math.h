#ifndef _MATH_H_
#define _MATH_H_

#include "MathType.h"
#include <simd/simd.h>
#include "TypeBase.h"
#include "Interface/IVector/IVecOpt.h"
#include "Interface/IVector/IVecData.h"
#include "Interface/IVector/IArray.h"

template<int N, typename T>
struct ktm::vec<N, T> : ktl::SingleExtends_t<ktl::TemplateList<IVecData, IArray, IVecOpt>, ktm::vec<N, T>> 
{
    using Father = ktl::SingleExtends_t<ktl::TemplateList<IVecData, IArray, IVecOpt>, ktm::vec<N, T>>; 
    using Father::Father;
};

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

static inline ktm::vec<4, float> t3(ktm::vec<4, float> v)
{
    ktm::vec<4, float> x = {1, 1, 66, 1}; 
	return v + x;
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
    ktm::vec<4,float> kt = {1, 1, 66, 1}; 
    start3 = clock();
    for(int i = 0; i < 10000000; ++i)
    {
        kt = t3(kt);
    } 
    end3 = clock();
    std::cout << (double)(end1 - start1) << ", " << (double)(end2 - start2) << ", " << (double)(end3 - start3) << std::endl;
    // ktl::Vec<double, 4> v = ktl::MakeVec<double, 4>({ 5.0, 2.0, 3.0 }, 1);
    // std::cout << v.m[0] << ", " << v.m[1] << ", " << v.m[2] << ", " << v.m[3] << std::endl;
    std::cout << v[1] << "," << x.y << "," << kt.y << std::endl;

    typedef ktm::vec<3, float> fvec3;
    typedef ktm::vec<3, int> svec3;
    std::cout << sizeof(fvec3) << std::endl;
    fvec3 aaa = { 1, 2, 3.7};
    aaa = -(aaa + aaa);
    
    const fvec3 bbb(aaa);
    aaa *= aaa + aaa;
    svec3 opo(aaa); 
    //bbb.x = 100;
    int iio = 5;
    int oo = (bbb >= bbb);
    std::cout << aaa.ReduceMax() << "," << static_cast<svec3>(aaa) << "," << aaa << std::endl;
    std::array<float, 3> arr = { 1, 2, 3 };
    std::initializer_list<int> pp = { 1, 2, 3, 4, 5};
    // for(int i = 0; i < 100; ++i)
    // {
    //     std::cout << pp.begin()[1] << " ";
    // }
    // std::cout << std::endl;

}

#endif