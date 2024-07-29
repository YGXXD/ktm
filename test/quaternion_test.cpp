//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "../ktm/ktm.h"

int main(int argc, char* argv[])
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

    ktm::fmat4x4 q4_mat = ktm::rotate3d_axis(ktm::half_pi<float>, ktm::fvec3(0.f, 0.6f, 0.8f));
    ktm::fquat q5 = ktm::fquat::from_matrix(q4_mat);
    std::cout << "mat cvt quat" << std::endl; 
    std::cout << q4 << "\n" << q5 << std::endl;

    ktm::fmat4x4 q5_mat = q5.matrix4x4();
    std::cout << "quat cvt mat" << std::endl;
    std::cout << q5_mat << "\n" << q4_mat << std::endl;

    ktm::fmat3x3 q5_mat3x3 = q5.matrix3x3();
    std::cout << "matrix and quat effect" << std::endl;
    std::cout << q5_mat3x3 * v2 << "\n" << q5 * v2 << std::endl;

    ktm::fquat q6 = ktm::fquat::angle_axis(ktm::half_pi<float>, ktm::fvec3(1.f, 0.f, 0.f));
    ktm::fquat q7 = ktm::fquat::angle_axis(ktm::tow_pi<float>, ktm::fvec3(0.6f, -0.8f, 0.f));
    ktm::fvec3 v3 = { 1.f, 1.f, 1.f };
    std::cout << "slerp comp rotate vec" << std::endl;
    for(float i = 0.f; i <= 1.00005f; i += 0.1f)
    {
        ktm::fquat q = slerp(q6, q7, i);
        ktm::fmat3x3 m = q.matrix3x3();
        std::cout << q * v3 << std::endl;
        std::cout << m * v3 << std::endl;
    }

    std::cout << "inverse: " << ktm::inverse(q5) << std::endl;
    std::cout << "negate: " << -q5 << std::endl;
    std::cout << "normalize: " << ktm::normalize(q5) << std::endl;
    std::cout << "log(exp): " << ktm::log(ktm::exp(q5)) << std::endl;
    std::cout << "slerp: " << ktm::slerp(q5, q3, 0.5f) << std::endl;
    std::cout << "slerp_longest: " << ktm::slerp_longest(q5, q3, 0.5f) << std::endl;

    return 0;
}