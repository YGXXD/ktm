//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main(int argc, char* argv[])
{
    ktm::fmat3x3 affine_fmat;

    ktm::faffine2d a1 {};
    a1.rotate(0.6f * ktm::pi<float>);
    a1 >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat, ktm::rotate2d(0.6f * ktm::pi<float>), 3);

    ktm::faffine2d a2 {};
    a2.shear_x(0.5f * ktm::half_pi<float>);
    a2 >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat, ktm::shear2d_x(0.5f * ktm::half_pi<float>), 3);

    ktm::faffine2d a3 {};
    a3.translate(9.0f, -7.0f);
    a3 >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat, ktm::translate2d(ktm::fvec2(9.0f, -7.0f)), 3);

    ktm::faffine2d a4 {};
    a4.translate(2.0f, 2.0f).rotate(0.7f * ktm::pi<float>).shear_y(0.3f * ktm::pi<float>).scale(1.0f, 2.0f);
    ktm::fmat3x3 a4_mat = ktm::translate2d(ktm::fvec2 { 2.0f, 2.0f }) * ktm::rotate2d(0.7f * ktm::pi<float>) *
                          ktm::shear2d_y(0.3f * ktm::pi<float>) * ktm::scale2d(ktm::fvec2 { 1.0f, 2.0f });
    ktm::fvec3 a4_vec = ktm::fvec3(5.0f, -9.0f, 1.0f);
    a4 >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat, a4_mat, 3);
    TEST_EQUAL(affine_fmat * a4_vec, a4_mat * a4_vec);
    a4.invert().concat(affine_fmat) >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat, ktm::fmat3x3::from_eye(), 3);

    ktm::faffine2d a5, a6, a7;
    ktm::fmat3x3 a5_mat, a6_mat, a7_mat;
    ktm::fvec3 a5_vec = ktm::fvec3(5.0f, -7.8f, 1.0f);
    a6.translate(6.0f, -8.0f).shear_x(0.32f * ktm::pi<float>).scale(2.0f, -2.0f);
    a6 >> a6_mat;
    a5.translate(2.0f, 5.0f).rotate(0.7f * ktm::pi<float>).scale(4.0f, 2.0f) << a6_mat << a6;
    a7.translate(2.0f, 5.0f)
        .rotate(0.7f * ktm::pi<float>)
        .scale(4.0f, 2.0f)
        .translate(6.0f, -8.0f)
        .shear_x(0.32f * ktm::pi<float>)
        .scale(2.0f, -2.0f)
        .translate(6.0f, -8.0f)
        .shear_x(0.32f * ktm::pi<float>)
        .scale(2.0f, -2.0f);
    a5 >> a5_mat;
    a7 >> a7_mat;
    TEST_EQUAL_MATRIX(a5_mat, a7_mat, 3);
    TEST_EQUAL(a5_mat * a5_vec, a7_mat * a5_vec);

    return 0;
}