//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "../ktm/ktm.h"

int main(int argc, char* argv[])
{
    ktm::fmat4x4 affine_mat;
    std::cout << "affine3d construct matrix test:" << std::endl;
    ktm::faffine3d a1{};
    a1.rotate_axis(0.6f * ktm::pi<float>, {0.6f, 0.8f, 0.f});
    a1 >> affine_mat;
    std::cout << affine_mat << "\n" << ktm::rotate3d_axis(0.6f * ktm::pi<float>, {0.6f, 0.8f, 0.f}) << std::endl;

    ktm::faffine3d a2{};
    a2.rotate_from_to({0.6f, 0.8f, 0.f}, {-1.f, 0.f, 0.f});
    a2 >> affine_mat;
    std::cout << affine_mat << "\n" << rotate3d_from_to(ktm::fvec3{0.6f, 0.8f, 0.f}, ktm::fvec3{-1.f, 0.f, 0.f}) << std::endl;

    ktm::faffine3d a3{};
    a3.shear_y(0.3 * ktm::pi<float>, 0.7 * ktm::pi<float>);
    a3 >> affine_mat;
    std::cout << affine_mat << "\n" << ktm::shear3d_y(0.3f * ktm::pi<float>, 0.7f * ktm::pi<float>) << std::endl;

    std::cout << "affine3d transform and matrix transform test:" << std::endl;
    ktm::faffine3d a4{};
    a4.translate(2.f, 2.f, 5.f).
        rotate_axis(0.7f * ktm::pi<float>, {0.f, 0.8f, 0.6f}).
            shear_y(0.3 * ktm::pi<float>, 0.7 * ktm::pi<float>).
                scale(1.f, 2.f, 2.f);
    ktm::fmat4x4 a4_mat = ktm::translate3d(ktm::fvec3{2.f, 2.f, 5.f}) * 
                        ktm::rotate3d_axis(0.7f * ktm::pi<float>, ktm::fvec3{0.f, 0.8f, 0.6f}) *
                           ktm::shear3d_y(0.3f * ktm::pi<float>, 0.7f * ktm::pi<float>) * 
                             ktm::scale3d(ktm::fvec3{1.f, 2.f, 2.f}); 
    ktm::fvec4 a4_vec = ktm::fvec4(5.f, 3.f, -9.f, 1.f);
    a4 >> affine_mat;
    std::cout << affine_mat << "\n" << a4_mat << std::endl;
    std::cout << affine_mat * a4_vec << "\n" << a4_mat * a4_vec << std::endl;

    auto affine_factor = ktm::decompose_affine(affine_mat);

    std::cout << "affine3d_matrix factor translation rotation shear scale:" << std::endl;
    std::cout << affine_factor.get_translate() << "\n" << 
        affine_factor.get_rotate() << "\n" << 
            affine_factor.get_shear() << "\n" << 
                affine_factor.get_scale() << std::endl;
    std::cout << affine_factor.get_translate() * 
        affine_factor.get_rotate() * 
            affine_factor.get_shear() * 
                affine_factor.get_scale() * a4_vec << std::endl;

    std::cout << "affine3d invert test:" << std::endl;
    ktm::fmat4x4 invert_matrix;
    a4.invert() >> invert_matrix;
    std::cout << invert_matrix * affine_mat << std::endl;
    std::cout << invert_matrix * affine_mat * ktm::fvec4(2.5f, 6.6f, -8.f, 1.f) << std::endl;

    std::cout << "affine3d concat test:" << std::endl;
    ktm::faffine3d a5, a6, a7;
    ktm::fmat4x4 a5_mat, a6_mat, a7_mat;
    ktm::fvec4 a5_vec = ktm::fvec4(5.f, -5.f, -7.f, 1.f);
    a6.translate(6.f, 8.f, 5.f).
        shear_x(0.3 * ktm::pi<float>, 0.7 * ktm::pi<float>).
            scale(1.f, 2.f, 2.f);
    a6 >> a6_mat;
    a5.translate(2.f, 2.f, 5.f).
        rotate_axis(0.7f * ktm::pi<float>, {0.f, 0.8f, 0.6f}).
            scale(4.f, 4.f, 2.f) << a6_mat;
    a7.translate(2.f, 2.f, 5.f).
        rotate_axis(0.7f * ktm::pi<float>, {0.f, 0.8f, 0.6f}).
            scale(4.f, 4.f, 2.f).
                translate(6.f, 8.f, 5.f).
                    shear_x(0.3 * ktm::pi<float>, 0.7 * ktm::pi<float>).
                        scale(1.f, 2.f, 2.f);
    a5 >> a5_mat;
    a7 >> a7_mat;
    std::cout << a5_mat << "\n" << a7_mat << std::endl;
    std::cout << a5_mat * a5_vec << "\n" << a7_mat * a5_vec << std::endl;
    
    return 0;
}