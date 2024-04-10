#include "ktm/ktm.h"
#include <iostream>

static void VecTest()
{
    ktm::fvec3 t1 { -6, 7, 9 };
    ktm::svec3 t2 { -6, 7, 9 };

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
    std::cout << "value: " << t3 << "\nstep: " << ktm::step({-100.f, 200.f, 10.f}, t3) << std::endl;
    std::cout << "smoothstep: " << ktm::smoothstep({-100.f, 20.f, -200.f}, {100.f, 200.f, 200.f}, t3) << std::endl;
    std::cout << "lerp: " << ktm::lerp(t1, t3, 0.6f) << std::endl;
    std::cout << "mix: " << ktm::mix(t1, t3, {0.5f, 0.6f, 0.3f}) << std::endl; 
    std::cout << "fract: " << ktm::fract(t3) << std::endl;
    std::cout << "floor: " << ktm::floor(t3) << std::endl;
    std::cout << "ceil: " << ktm::ceil(t3) << std::endl;
    std::cout << "round: " << ktm::round(t3) << std::endl;
    std::cout << "sqrt: " << ktm::sqrt(t5) << std::endl;
    std::cout << "rsqrt: " << ktm::rsqrt(t5) << std::endl;
    std::cout << "recip: " << ktm::recip(t3) << std::endl;
}

static void GeoTest()
{
    ktm::fvec3 a = { 1.1f, 2.5f, 3.8f };
    ktm::fvec3 b = { 6.9f, 2.3f, -3.1f }; 
    std::cout << "dot: " << ktm::dot(a, b) << std::endl;
    std::cout << "length: " << ktm::length(a) << " " << ktm::length(b) << std::endl;
    std::cout << "project: " << ktm::project(a, b) << std::endl;
    std::cout << "normalize: " << ktm::normalize(b) << std::endl;
    std::cout << "reflect: " << ktm::reflect(a, b) << std::endl; 
    std::cout << "refract: " << ktm::refract(a, b, 1.3) << std::endl; 
}

static void MatTest()
{
    std::cout << "mat_mul_vec test:" << std::endl;
    ktm::fmat3x2 mt1 = { { 1, 2}, { 1, 2 }, {3, 4} };
    ktm::fvec3 v1 = { 2, 2, 2};

    std::cout << mt1 << std::endl;
    std::cout << v1 << std::endl;
    std::cout << mt1 * v1 << std::endl;

    std::cout << "vec_mul_mat test:" << std::endl;
    ktm::fmat3x2 mt2 = { { 3, 2}, { 1, 2 }, {3, 4} };
    ktm::fvec2 v2 = { 2, 1 };

    std::cout << mt2 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v2 * mt2 << std::endl;

    std::cout << "mat_mul_mat test:" << std::endl; 
    ktm::fmat3x2 mt3 = { { 3, 2}, { 1, 2 }, {3, 4} };
    ktm::fmat2x3 mt4 = { {3, 3, 3}, { 1, 1, 1}};
    std::cout << mt3 << std::endl;
    std::cout << mt4 << std::endl;
    std::cout << mt3 * mt4 << std::endl;

    std::cout << "add test:" << std::endl; 
    ktm::fmat4x3 mt5 = { {3, 3, 3}, { 1, 1, 1}, { 2, 3, 3}, { }};
    std::cout << mt5 << std::endl;
    std::cout << mt5 + mt5 << std::endl;

    std::cout << "equal test:" << std::endl; 
    ktm::fmat4x3 mt6 = mt5; 
    std::cout << (mt5 == mt6) << "," << (mt5 == ktm::fmat4x3()) << std::endl;

    std::cout << "transpose test:" << std::endl; 
    ktm::fmat3x3 mt7_1 = { { 2, -1, 207 }, {-1, 2, -1}, { 20, -1, 2 } };
    std::cout << mt7_1 << std::endl;
    std::cout << ktm::transpose(mt7_1) << std::endl; 
    ktm::fmat2x2 mt7_2 = { { 2, -1 }, { 50, 20 } };
    std::cout << mt7_2 << std::endl;
    std::cout << ktm::transpose(mt7_2) << std::endl; 

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

static void QuatTest()
{
    ktm::fvec3 v1 = { 2.f, 2.f, 10.f };
    ktm::fquat q1 = ktm::fquat::from_to(ktm::fvec3(1.f, 0.f, 0.f), ktm::fvec3(0.f, 1.f, 0.f));
    ktm::fquat q2 = ktm::fquat::from_to(ktm::fvec3(0.f, 1.f, 0.f), ktm::fvec3(0.f, 0.f, 1.f));

    ktm::fvec3 v2 = q2 * q1 * v1;
    std::cout << "effect (quat mul quat) rotate vec" << std::endl;
    std::cout << v2 << std::endl;

    ktm::fquat q3 = ktm::fquat::from_to(ktm::fvec3(1.f, 0.f, 0.f), ktm::fvec3(0.f, 0.f, 1.f)); 
    std::cout << "effect quat mul vec" << std::endl;
    std::cout << q3 * v1 << std::endl;

    ktm::fquat q4 = ktm::fquat::angle_axis(ktm::half_pi<float>, ktm::fvec3(0.f, 0.6f, 0.8f));
    std::cout << "angle_axis rotate vec" << std::endl;
    std::cout << q4 * v2 << std::endl;

    ktm::fmat4x4 q4_mat = ktm::rotate_axis(ktm::half_pi<float>, ktm::fvec3(0.f, 0.6f, 0.8f));
    ktm::fquat q5 = ktm::fquat::from_matrix(q4_mat);
    std::cout << "mat cvt quat" << std::endl; 
    std::cout << q4 << "\n" << q5 << std::endl;

    ktm::fmat4x4 q5_mat = q5.matrix4x4();
    std::cout << "quat cvt mat" << std::endl;
    std::cout << q5_mat << "\n" << q4_mat << std::endl;

    ktm::fmat3x3 q5_mat3x3 = q5.matrix3x3();
    std::cout << "matrix and quat effect" << std::endl;
    std::cout << q5_mat3x3 * v2 << "\n" << q5 * v2 << std::endl;
}

int main(int argc, char* argv[])
{
    VecTest();
    GeoTest();
    MatTest();
    QuatTest();
    return 0;
}
