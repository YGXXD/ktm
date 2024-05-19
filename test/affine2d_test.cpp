//  MIT License
//
//  Copyright (c) 2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "../ktm/ktm.h"

int main(int argc, char* argv[])
{
    ktm::fmat3x3 affine_mat;
    std::cout << "affine2d construct matrix test:" << std::endl;
    ktm::faffine2d a1{};
    a1.rotate(0.6f * ktm::pi<float>);
    a1 >> affine_mat;
    std::cout << affine_mat << "\n" << ktm::rotate2d(0.6f * ktm::pi<float>) << std::endl;

    ktm::faffine2d a2{};
    a2.shear_x(0.5f * ktm::half_pi<float>);
    a2 >> affine_mat;
    std::cout << affine_mat << "\n" << ktm::shear2d_x(0.5f * ktm::half_pi<float>) << std::endl;

    ktm::faffine2d a3{};
    a3.translate(9.f, -7.f);
    a3 >> affine_mat;
    std::cout << affine_mat << "\n" << ktm::translate2d(ktm::fvec2(9.f, -7.f)) << std::endl;

    std::cout << "affine2d transform and matrix transform test:" << std::endl;
    ktm::faffine2d a4{};
    a4.translate(2.f, 2.f).
        rotate(0.7f * ktm::pi<float>).
            shear_y(0.3 * ktm::pi<float>).
                scale(1.f, 2.f);
    ktm::fmat3x3 a4_mat = ktm::translate2d(ktm::fvec2{2.f, 2.f}) * 
                        ktm::rotate2d(0.7f * ktm::pi<float>) *
                           ktm::shear2d_y(0.3f * ktm::pi<float>) * 
                             ktm::scale2d(ktm::fvec2{1.f, 2.f}); 
    ktm::fvec3 a4_vec = ktm::fvec3(5.f, -9.f, 1.f);
    a4 >> affine_mat;
    std::cout << affine_mat << "\n" << a4_mat << std::endl;
    std::cout << affine_mat * a4_vec << "\n" << a4_mat * a4_vec << std::endl;

    auto affine_factor = ktm::factor_affine(affine_mat);

    std::cout << "affine2d_matrix factor translation rotation shear scale:" << std::endl;
    std::cout << std::get<0>(affine_factor) << "\n" << 
        std::get<1>(affine_factor) << "\n" << 
            std::get<2>(affine_factor) << "\n" << 
                std::get<3>(affine_factor) << std::endl;
    std::cout << std::get<0>(affine_factor) * 
        std::get<1>(affine_factor) * 
            std::get<2>(affine_factor) * 
                std::get<3>(affine_factor) * a4_vec << std::endl;

    std::cout << "affine2d invert test:" << std::endl;
    ktm::fmat3x3 invert_matrix;
    a4.invert() >> invert_matrix;
    std::cout << invert_matrix * affine_mat << std::endl;
    std::cout << invert_matrix * affine_mat * ktm::fvec3(23.5f, -6.6f, 1.f) << std::endl;

    std::cout << "affine2d concat test:" << std::endl;
    ktm::faffine2d a5, a6, a7;
    ktm::fmat3x3 a5_mat, a6_mat, a7_mat;
    ktm::fvec3 a5_vec = ktm::fvec3(5.f, -7.8f, 1.f);
    a6.translate(6.f, -8.f).
        shear_x(0.32f * ktm::pi<float>).
            scale(2.f, -2.f);
    a6 >> a6_mat;
    a5.translate(2.f, 5.f).
        rotate(0.7f * ktm::pi<float>).
            scale(4.f, 2.f) << a6_mat << a6;
    a7.translate(2.f, 5.f).
        rotate(0.7f * ktm::pi<float>).
            scale(4.f, 2.f).
                translate(6.f, -8.f).
                    shear_x(0.32f * ktm::pi<float>).
                        scale(2.f, -2.f).
                            translate(6.f, -8.f).
                                shear_x(0.32f * ktm::pi<float>).
                                    scale(2.f, -2.f);
    a5 >> a5_mat;
    a7 >> a7_mat;
    std::cout << a5_mat << "\n" << a7_mat << std::endl;
    std::cout << a5_mat * a5_vec << "\n" << a7_mat * a5_vec << std::endl;
    
    return 0;
}