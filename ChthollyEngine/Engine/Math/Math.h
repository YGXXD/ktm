#ifndef _MATH_H___
#define _MATH_H___

#include "MathType.h"
#include "MathType/BaseType.h"
#include "MathType/VecType.h"
#include "Math/MathLib/Geometry.h"
#include "Math/MathType/MatType.h"
#include "Math/MathLib/MatCommon.h"
#include "Math/MathLib/VecCommon.h"
#include <pmmintrin.h>

// static inline simd_float4 t1(simd_float4 v)
// {
//     simd_float4 x = {1, 1, 66, 1};
// 	return v + x;
// }

// static inline ktl::float4 t2(ktl::float4 v)
// {
//     ktl::float4 x = {1, 1, 66, 1}; 
// 	return v + x;
// }

// static inline ktm::fvec4 t3(ktm::fvec4 v)
// {
//     ktm::fvec4 x = {1, 1, 66, 1}; 
// 	return v + x;
// }

// static void mathTest()
// {
//     ktl::double4 a = {8, 10, 8, 10};
//     ktl::double4 b = {9, 2, 9, 2};
//     ktl::double4 c = {10, 4, 10, 4};
//     ktl::double4 d = {7, 10, 7, 10};
//     auto ret = (a * b) / (c - d);
    
//     std::cout << ret.x << ", " << ret.y << ", " << ret.z << ", " << ret.w << std::endl;

//     ret *= (a * b) / (c - d);
//     std::cout << ret.x << ", " << ret.y << ", " << ret.z << ", " << ret.w << std::endl;
    
//     clock_t start1;
//     clock_t start2;
//     clock_t end1;
//     clock_t end2;
//     clock_t start3;
//     clock_t end3;
//     simd_float4 v = {1, 1, 66, 1};
//     start1 = clock();
//     for(int i = 0; i < 10000000; ++i)
//     {
//         v = t1(v);
//     }
//     end1 = clock();
//     ktl::float4 x = {1, 1, 66, 1}; 
//     start2 = clock();
//     for(int i = 0; i < 10000000; ++i)
//     {
//         x = t2(x);
//     }
//     end2 = clock();
//     ktm::fvec4 kt = {1, 1, 66, 1}; 
//     start3 = clock();
//     for(int i = 0; i < 10000000; ++i)
//     {
//         kt = t3(kt);
//     } 
//     end3 = clock();
//     std::cout << (double)(end1 - start1) << ", " << (double)(end2 - start2) << ", " << (double)(end3 - start3) << std::endl;
//     // ktl::Vec<double, 4> v = ktl::MakeVec<double, 4>({ 5.0, 2.0, 3.0 }, 1);
//     // std::cout << v.m[0] << ", " << v.m[1] << ", " << v.m[2] << ", " << v.m[3] << std::endl;
//     std::cout << v[1] << "," << x.y << "," << kt.y << std::endl;

//     std::cout << sizeof(ktm::fvec3) << std::endl;
//     ktm::dvec3 aaa = { 1, 2, -3.7 };
//     aaa = -(aaa + aaa);
//     aaa *= -(aaa + aaa);
//     ktm::fvec3 bbb(aaa); 
//     ktm::fvec3 ccc = static_cast<ktm::fvec3>(aaa) + 10.f;
//     std::cout << ktm::distance(ktm::project(ktm::nomorlize(aaa), aaa), aaa) << ", " << ccc << ", " << static_cast<ktm::svec3>(aaa) << ", " << aaa << ", " << ((float*)&bbb)[3] << ", " << (std::abs(((float*)&bbb)[3]) < 1e-6) << std::endl;
//     std::array<float, 3> arr = { 1, 2, 3 };
//     std::initializer_list<int> pp = { 1, 2, 3, 4, 5};
//     ktm::fvec1 pi = { 1.9f };
//     pi += pi;
//     std::cout << ktm::clamp(aaa, {1, 2, 4}, { 0.4, 0.6, 0.2})  << "\n" << ktm::mix(bbb, {1, 2, 4}, {0.4, 0.6 ,0.2})<< "\n" << aaa << std::endl;
//     simd_double4 codet = { 1, 2, 3, 4};
//     std::cout << codet.odd[0] << ", " << codet.odd[1] << std::endl;
// }

template <size_t N, size_t N2, typename T>
struct Test {};

template <size_t N, typename T>
struct Test<N, N, T> {};

template <size_t N>
struct Test<N, N, float> {};

static void mathTest2()
{
    std::cout << "mat_mul_vec test:" << std::endl;
    ktm::fmat2x3 mt1 = { { 1, 2}, { 1, 2 }, {3, 4} };
    ktm::fvec3 v1 = { 2, 2, 2};

    std::cout << mt1 << std::endl;
    std::cout << v1 << std::endl;
    std::cout << mt1 * v1 << std::endl;

    std::cout << "vec_mul_mat test:" << std::endl;
    ktm::fmat2x3 mt2 = { { 3, 2}, { 1, 2 }, {3, 4} };
    ktm::fvec2 v2 = { 2, 1 };

    std::cout << mt2 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v2 * mt2 << std::endl;

    std::cout << "mat_mul_mat test:" << std::endl; 
    ktm::fmat2x3 mt3 = { { 3, 2}, { 1, 2 }, {3, 4} };
    ktm::fmat3x2 mt4 = { {3, 3, 3}, { 1, 1, 1}};
    std::cout << mt3 << std::endl;
    std::cout << mt4 << std::endl;
    std::cout << mt3 * mt4 << std::endl;

    std::cout << "add test:" << std::endl; 
    ktm::fmat3x4 mt5 = { {3, 3, 3}, { 1, 1, 1}, { 2, 3, 3}, { }};
    std::cout << mt5 << std::endl;
    std::cout << mt5 + mt5 << std::endl;

    std::cout << "equal test:" << std::endl; 
    ktm::fmat3x4 mt6 = mt5; 
    std::cout << (mt5 == mt6) << "," << (mt5 == ktm::fmat3x4()) << std::endl;
    
    std::cout << "speed mul test:" << std::endl; 
    clock_t start1;
    clock_t end1;
    clock_t start3;
    clock_t end3;
    ktm::fvec3 x = { 1, 2, 3 };
    ktm::fvec3 y = { 3, 3, 3 };
    std::cout << ktm::cross(x, y) << std::endl;
    ktm::fmat3x3 k1 = { { 1, 7, 3 }, { 2, 5, 7},{3, 3,  2}};
    float p1 = 0;
    // ktm::fvec4 t1 = { 1, 1, 1, 1 };
    start1 = clock();
    for(int i = 0; i < 10000000; ++i)
    {
        //x = ktm::cross(x, y);
        // k1 = ktm::transpose(k1 * k1);
        //k1 = k1 + k1;
        //p1 += ktm::determinant(k1);
    }
    end1 = clock();
    std::cout << (double)(end1 - start1)<< std::endl;
    
    std::cout << "transpose test:" << std::endl; 
    ktm::fmat4x4 mt7 = { { 1, 2, 3 , 4}, { 2, 2, 2, 6},{3, 3, 1, 3}, {1, 9,1, 1}};
    std::cout << mt7 << std::endl;
    std::cout << ktm::transpose(mt7) << std::endl; 
    
    std::cout << ktm::determinant(k1) << std::endl;
    std::cout << k1 * ktm::inverse(k1) * k1 << "\n" ;

    std::cout << alignof(ktm::fvec4) << std::endl;
    std::cout << mt7 * ktm::inverse(mt7) * mt7 << "\n" ;

#if defined(__SSE2__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86_FP)
    float in0[4] = { 1, 2, 3, 4};
    float in1[4] = { 1, 2, 3, 4};
    float in2[4] = { 1, 2, 3, 4};
    float in3[4] = { 1, 2, 3, 4};
    __m128 i0 = _mm_load_ps(in0);
    __m128 i1 = _mm_load_ps(in1);
    __m128 i2 = _mm_load_ps(in2);
    __m128 i3 = _mm_load_ps(in3);
    
    i0 = _mm_shuffle_ps(i0, i0, _MM_SHUFFLE(0, 1, 2, 3));
    i0 = _mm_set_ps(1, 2, 3, 4);

    __m128 tmp0 = _mm_shuffle_ps(i0, i1, 0x44);
    float* tmpf0 = (float*)&i0;
    std::cout << tmpf0[0] << ", " << tmpf0[1] << ", " << tmpf0[2] << ", " << tmpf0[3] << std::endl;
	__m128 tmp2 = _mm_shuffle_ps(i0, i1, 0xEE);
	__m128 tmp1 = _mm_shuffle_ps(i2, i3, 0x44);
	__m128 tmp3 = _mm_shuffle_ps(i2, i3, 0xEE);
    
	__m128 ret0 = _mm_shuffle_ps(tmp0, tmp1, 0x88);
	__m128 ret1 = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
	__m128 ret2 = _mm_shuffle_ps(tmp2, tmp3, 0x88);
	__m128 ret3 = _mm_shuffle_ps(tmp2, tmp3, 0xDD);

    _mm_store_ps(in0, ret0);
    _mm_store_ps(in1, ret1);
    _mm_store_ps(in2, ret2);
    _mm_store_ps(in3, ret3);

    std::cout << in0[0] << ", " << in0[1] << ", " << in0[2] << ", " << in0[3] << std::endl;
#endif

    int temp = 0x12345678;
    int* point1=&temp;
    short* point2=(short *)&temp;
    if(*point2==0x1234){
        std::cout<<"Windows little"<<std::endl;
    }else{
        std::cout<<"Windows big"<<std::endl;
    }

    ktm::fmat4x4 a = {{1, 2, 3,4 },{9,8,9,1},{2,3,6,1},{ 7,4,7,0}};
    std::cout << ktm::inverse(a) * a << std::endl;
    Test<4,4,float> t;
    auto lu = ktm::factor_lu(a);
    std::cout << std::get<0>(lu) << "\n" << std::get<1>(lu) << "\n" << std::get<0>(lu) * std::get<1>(lu) << std::endl;

    ktm::dmat3x3 b = {{1, 0, -1 },{2, 1, 4},{-2, 3, 5}};
    auto qr = ktm::factor_svd(b);
    std::cout << std::get<0>(qr) << "\n" << std::get<1>(qr) << "\n" << std::get<0>(qr) * std::get<1>(qr) << std::endl;
    std::cout << ktm::dot(std::get<0>(qr)[0], std::get<0>(qr)[1]) << std::endl;
    std::cout << ktm::rsqrt<float>(4.f) << std::endl;
}
#endif