//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main(int argc, char* argv[])
{
    ktm::fmat4x4 affine_fmat;

    ktm::faffine3d a1 {};
    a1.rotate_axis(0.6f * ktm::pi<float>, { 0.6f, 0.8f, 0.0f });
    a1 >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat, ktm::rotate3d_axis(0.6f * ktm::pi<float>, { 0.6f, 0.8f, 0.0f }), 4);

    ktm::faffine3d a2 {};
    a2.rotate_from_to({ 0.6f, 0.8f, 0.0f }, { -1.0f, 0.0f, 0.0f });
    a2 >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat,
                      ktm::rotate3d_from_to(ktm::fvec3 { 0.6f, 0.8f, 0.0f }, ktm::fvec3 { -1.0f, 0.0f, 0.0f }), 4);

    ktm::faffine3d a3 {};
    a3.shear_y(0.3f * ktm::pi<float>, 0.7f * ktm::pi<float>);
    a3 >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat, ktm::shear3d_y(0.3f * ktm::pi<float>, 0.7f * ktm::pi<float>), 4);

    ktm::faffine3d a4 {};
    a4.translate(2.0f, 2.0f, 5.0f)
        .rotate_axis(0.7f * ktm::pi<float>, { 0.0f, 0.8f, 0.6f })
        .shear_y(0.3f * ktm::pi<float>, 0.7f * ktm::pi<float>)
        .scale(1.0f, 2.0f, 2.0f);
    ktm::fmat4x4 a4_mat = ktm::translate3d(ktm::fvec3 { 2.0f, 2.0f, 5.0f }) *
                          ktm::rotate3d_axis(0.7f * ktm::pi<float>, ktm::fvec3 { 0.0f, 0.8f, 0.6f }) *
                          ktm::shear3d_y(0.3f * ktm::pi<float>, 0.7f * ktm::pi<float>) *
                          ktm::scale3d(ktm::fvec3 { 1.0f, 2.0f, 2.0f });
    ktm::fvec4 a4_vec = ktm::fvec4(5.0f, 3.0f, -9.0f, 1.0f);
    a4 >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat, a4_mat, 4);
    TEST_EQUAL(affine_fmat * a4_vec, a4_mat * a4_vec);
    a4.invert().concat(affine_fmat) >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat, ktm::fmat4x4::from_eye(), 4);

    ktm::faffine3d a5, a6, a7;
    ktm::fmat4x4 a5_mat, a6_mat, a7_mat;
    ktm::fvec4 a5_vec = ktm::fvec4(5.0f, -5.0f, -7.0f, 1.0f);
    a6.translate(6.0f, 8.0f, 5.0f).shear_x(0.3f * ktm::pi<float>, 0.7f * ktm::pi<float>).scale(1.0f, 2.0f, 2.0f);
    a6 >> a6_mat;
    a5.translate(2.0f, 2.0f, 5.0f).rotate_axis(0.7f * ktm::pi<float>, { 0.0f, 0.8f, 0.6f }).scale(4.0f, 4.0f, 2.0f)
        << a6_mat;
    a7.translate(2.0f, 2.0f, 5.0f)
        .rotate_axis(0.7f * ktm::pi<float>, { 0.0f, 0.8f, 0.6f })
        .scale(4.0f, 4.0f, 2.0f)
        .translate(6.0f, 8.0f, 5.0f)
        .shear_x(0.3f * ktm::pi<float>, 0.7f * ktm::pi<float>)
        .scale(1.0f, 2.0f, 2.0f);
    a5 >> a5_mat;
    a7 >> a7_mat;
    TEST_EQUAL_MATRIX(a5_mat, a7_mat, 4);
    TEST_EQUAL_MATRIX(a5_mat * a5_vec, a7_mat * a5_vec, 4);

    return 0;
}