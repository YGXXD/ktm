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
    ktm::dmat4x4 affine_dmat;

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
    a3.shear_y(0.3 * ktm::pi<float>, 0.7 * ktm::pi<float>);
    a3 >> affine_fmat;
    TEST_EQUAL_MATRIX(affine_fmat, ktm::shear3d_y(0.3f * ktm::pi<float>, 0.7f * ktm::pi<float>), 4);

    ktm::daffine3d a4 {};
    a4.translate(2.0, 2.0, 5.0)
        .rotate_axis(0.7 * ktm::pi<double>, { 0.0, 0.8, 0.6 })
        .shear_y(0.3 * ktm::pi<double>, 0.7 * ktm::pi<double>)
        .scale(1.0, 2.0, 2.0);
    ktm::dmat4x4 a4_mat = ktm::translate3d(ktm::dvec3 { 2.0, 2.0, 5.0 }) *
                          ktm::rotate3d_axis(0.7 * ktm::pi<double>, ktm::dvec3 { 0.0, 0.8, 0.6 }) *
                          ktm::shear3d_y(0.3 * ktm::pi<double>, 0.7 * ktm::pi<double>) *
                          ktm::scale3d(ktm::dvec3 { 1.0, 2.0, 2.0 });
    ktm::dvec4 a4_vec = ktm::dvec4(5.0, 3.0, -9.0, 1.0);
    a4 >> affine_dmat;
    TEST_EQUAL_MATRIX(affine_dmat, a4_mat, 4);
    TEST_EQUAL(affine_dmat * a4_vec, a4_mat * a4_vec);
    auto affine_factor = ktm::decompose_affine(affine_dmat);
    TEST_EQUAL(affine_dmat * a4_vec, affine_factor.get_translate() * affine_factor.get_rotate() *
                                         affine_factor.get_shear() * affine_factor.get_scale() * a4_vec);
    a4.invert().concat(affine_dmat) >> affine_dmat;
    TEST_EQUAL_MATRIX(affine_dmat, ktm::dmat4x4::from_eye(), 4);

    ktm::faffine3d a5, a6, a7;
    ktm::fmat4x4 a5_mat, a6_mat, a7_mat;
    ktm::fvec4 a5_vec = ktm::fvec4(5.0f, -5.0f, -7.0f, 1.0f);
    a6.translate(6.0f, 8.0f, 5.0f).shear_x(0.3 * ktm::pi<float>, 0.7 * ktm::pi<float>).scale(1.0f, 2.0f, 2.0f);
    a6 >> a6_mat;
    a5.translate(2.0f, 2.0f, 5.0f).rotate_axis(0.7f * ktm::pi<float>, { 0.0f, 0.8f, 0.6f }).scale(4.0f, 4.0f, 2.0f)
        << a6_mat;
    a7.translate(2.0f, 2.0f, 5.0f)
        .rotate_axis(0.7f * ktm::pi<float>, { 0.0f, 0.8f, 0.6f })
        .scale(4.0f, 4.0f, 2.0f)
        .translate(6.0f, 8.0f, 5.0f)
        .shear_x(0.3 * ktm::pi<float>, 0.7 * ktm::pi<float>)
        .scale(1.0f, 2.0f, 2.0f);
    a5 >> a5_mat;
    a7 >> a7_mat;
    TEST_EQUAL_MATRIX(a5_mat, a7_mat, 4);
    TEST_EQUAL_MATRIX(a5_mat * a5_vec, a7_mat * a5_vec, 4);

    return 0;
}