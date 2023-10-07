#ifndef _MATH_TEST_H_
#define _MATH_TEST_H_

#include "MathType/BaseType.h"
#include "MathType/VecType.h"
#include "Math/MathLib/Geometry.h"
#include "Math/MathType/MatType.h"
#include "Math/MathLib/MatCommon.h"
#include "Math/MathLib/VecCommon.h"

static void VecTest()
{
    ktm::fvec3 t1 { -6, 7, 9 };
    ktm::svec3 t2 { -6, 7, 9 };

    std::cout << "elem_move: " << ktm::elem_move<1>(t1) << ", " << ktm::elem_move<2>(t2) << std::endl;
    std::cout << "reduce_add: " << ktm::reduce_add(t1) << ", " << ktm::reduce_add(t2) << std::endl; 
    std::cout << "reduce_max: " << ktm::reduce_max(t1) << ", " << ktm::reduce_max(t2) << std::endl;
    std::cout << "reduce_min: " << ktm::reduce_min(t1) << ", " << ktm::reduce_min(t2) << std::endl;
    std::cout << "abs: " << ktm::abs(t1) << ", " << ktm::abs(t2) << std::endl;
    std::cout << "clamp: " << ktm::clamp(t1, {-5, -5, -5}, {8, 8, 8}) << ", " << ktm::clamp(t2, {-5, -5, -5}, {8, 8, 8}) << std::endl;

    ktm::fvec3 t3 { 8, 9, -10 };
    ktm::fvec3 t4 = (ktm::fvec3)t2;

    ktm::fvec3 t5 = { 2.8, 3.5, 8.9 }; 
    t3 *= t1 + t5;

    std::cout << "equal: " << (t1 == t3) << ", " << (t1 == t4) << ", " << (t2 == (ktm::svec3)t1) << std::endl;
    std::cout << "value: " << t3 << "\nstep: " << ktm::step({-100, 200, 10}, t3) << std::endl;
    std::cout << "smoothstep: " << ktm::smoothstep({-100, 20, -200}, {100, 200, 200}, t3) << std::endl;
    std::cout << "recip: " << ktm::recip(t3) << std::endl;
    std::cout << "lerp: " << ktm::lerp(t1, t3, 0.6) << std::endl;
    std::cout << "mix: " << ktm::mix(t1, t3, {0.5, 0.6, 0.3}) << std::endl; 
    std::cout << "fract: " << ktm::fract(t3) << std::endl;
}

static void MatTest()
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

    std::cout << "transpose test:" << std::endl; 
    ktm::fmat3x3 mt7 = { { 2, -1, 207 }, {-1, 2, -1}, { 20, -1, 2 } };
    std::cout << mt7 << std::endl;
    std::cout << ktm::transpose(mt7) << std::endl; 

    std::cout << "determinant test:" << std::endl;  
    ktm::fmat4x4 mt8 = { {2, -1, 9, 9}, {-1, 2, -1, -8}, { 20, -1, 2, 2}, { 1, 3, 2, 77 }};
    ktm::smat4x4 smt8 = { {2, -1, 9, 9}, {-1, 2, -1, -8}, { 20, -1, 2, 2}, { 1, 3, 2, 77 }};
    std::cout << ktm::determinant(mt8) << "\n" << ktm::determinant(smt8) << std::endl;

    std::cout << "inverse test:" << std::endl;  
    ktm::fmat4x4 mt9 = { {2, -1, 9, 9}, {-1, 2, -1, -8}, { 20, -1, 2, 2}, { 1, 3, 2, 77 }};
    std::cout << ktm::inverse(mt9) * mt9 * mt8 << std::endl;

    std::cout << "factor lu test:" << std::endl;
    auto lu = ktm::factor_lu(mt8);
    std::cout << std::get<0>(lu) << "\n" << std::get<1>(lu) << "\n" << std::get<0>(lu) * std::get<1>(lu) << std::endl;

    std::cout << "factor qr test:" << std::endl;
    auto qr = ktm::factor_qr(mt8);
    std::cout << std::get<0>(qr) << "\n" << std::get<1>(qr) << "\n" << std::get<0>(qr) * std::get<1>(qr) << std::endl;

    std::cout << "factor svd test:" << std::endl;
    auto usv = ktm::factor_svd(mt8);
    std::cout << std::get<0>(usv) << "\n" << std::get<1>(usv) << "\n" << std::get<2>(usv) 
        << "\n" << std::get<0>(usv) * std::get<1>(usv) * std::get<2>(usv) << std::endl; 
}
#endif