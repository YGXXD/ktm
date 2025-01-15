//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main(int argc, char* argv[])
{
    ktm::mat<5, 5, float> m1 = { { 6.0f, -1.0f, 0.0f, 0.0f, 0.0f },
                                 { -1.0f, 7.0f, -1.0f, 0.0f, 0.0f },
                                 { 0.0f, -1.0f, 8.0f, -1.0f, 0.0f },
                                 { 0.0f, 0.0f, -1.0f, 9.0f, -1.0f },
                                 { 0.0f, 0.0f, 0.0f, -1.0f, 10.0f } };
    ktm::fmat2x2 m2 = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
    ktm::mat<5, 5, float> m3 = {
        { 1.0f, 4.0f, 7.0f, 2.0f, 3.0f },   { 4.0f, 5.0f, -1.0f, 4.0f, -1.0f }, { 7.0f, -1.0f, -2.0f, -5.0f, 4.0f },
        { 2.0f, 4.0f, -5.0f, 7.0f, -5.0f }, { 3.0f, -1.0f, 4.0f, -5.0f, 4.0f },
    };

    auto lu1 = ktm::decompose_lu_cholesky(m1);
    std::cout << lu1.get_l() << std::endl;
    std::cout << lu1.get_u() << std::endl;
    TEST_EQUAL_MATRIX(lu1.get_l() * lu1.get_u(), m1, 5);

    auto lu2 = ktm::decompose_lu_doolittle(m2);
    std::cout << lu2.get_l() << std::endl;
    std::cout << lu2.get_u() << std::endl;
    TEST_EQUAL_MATRIX(lu2.get_l() * lu2.get_u(), m2, 2);

    auto lu3 = ktm::decompose_lu_crout(m3);
    std::cout << lu3.get_l() << std::endl;
    std::cout << lu3.get_u() << std::endl;
    TEST_EQUAL_MATRIX(lu3.get_l() * lu3.get_u(), m3, 5);

    ktm::fmat2x2 m4 = { { 8.0f, 2.0f }, { 5.0f, -4.0f } };
    ktm::fmat3x3 m5 = { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, { 7.0f, -1.0f, -2.0f } };
    ktm::mat<5, 5, float> m6 = {
        { 2.0f, 1.0f, 3.0f, 4.0f, 2.0f },  { 1.0f, 5.0f, 2.0f, -1.0f, 3.0f }, { 3.0f, 2.0f, 4.0f, 1.0f, -2.0f },
        { 4.0f, -1.0f, 1.0f, 6.0f, 2.0f }, { 2.0f, 3.0f, -2.0f, 2.0f, 3.0f },
    };

    auto qr1 = ktm::decompose_qr_householder(m4);
    std::cout << qr1.get_q() << std::endl;
    std::cout << qr1.get_r() << std::endl;
    TEST_EQUAL_MATRIX(qr1.get_q() * qr1.get_r(), m4, 2);

    auto qr2 = ktm::decompose_qr_givens(m5);
    std::cout << qr2.get_q() << std::endl;
    std::cout << qr2.get_r() << std::endl;
    TEST_EQUAL_MATRIX(qr2.get_q() * qr2.get_r(), m5, 3);

    auto qr3 = ktm::decompose_qr_schmitd(m6);
    std::cout << qr3.get_q() << std::endl;
    std::cout << qr3.get_r() << std::endl;
    TEST_EQUAL_MATRIX(qr3.get_q() * qr3.get_r(), m6, 5);

    ktm::mat<5, 5, float> m7 = {
        { 6.0f, 2.0f, -1.0f, 3.0f, 1.0f }, { 2.0f, 8.0f, 4.0f, -2.0f, 0.0f }, { -1.0f, 4.0f, 7.0f, 2.0f, -3.0f },
        { 3.0f, -2.0f, 2.0f, 9.0f, 5.0f }, { 1.0f, 0.0f, -3.0f, 5.0f, 4.0f },
    };
    ktm::fmat2x2 m8 = { { 5.0f, 2.0f }, { 2.0f, -3.0f } };
    ktm::fmat3x3 m9 = { { 5.0f, 2.0f, 2.0f }, { 2.0f, 5.0f, -5.2f }, { 2.0f, -5.2f, 7.0f } };
    auto edv1 = ktm::decompose_edv_jacobi(m7);
    std::cout << edv1.get_vector() << std::endl;
    std::cout << edv1.get_value() << std::endl;
    auto edv1_ret =
        edv1.get_vector() * ktm::mat<5, 5, float>::from_diag(edv1.get_value()) * ktm::transpose(edv1.get_vector());
    TEST_EQUAL_MATRIX(edv1_ret, m7, 5);

    auto edv2 = ktm::decompose_edv_shiftqr(m8);
    std::cout << edv2.get_vector() << std::endl;
    std::cout << edv2.get_value() << std::endl;
    auto edv2_ret = edv2.get_vector() * ktm::fmat2x2::from_diag(edv2.get_value()) * ktm::transpose(edv2.get_vector());
    TEST_EQUAL_MATRIX(edv2_ret, m8, 2);

    auto edv3 = ktm::decompose_edv_shiftqr(m9);
    std::cout << edv3.get_vector() << std::endl;
    std::cout << edv3.get_value() << std::endl;
    auto edv3_ret = edv3.get_vector() * ktm::fmat3x3::from_diag(edv3.get_value()) * ktm::transpose(edv3.get_vector());
    TEST_EQUAL_MATRIX(edv3_ret, m9, 3);

    ktm::mat<5, 5, float> m10 = { { 2.0f, -1.0f, 0.0f, 0.0f, 0.0f },
                                   { -1.0f, 3.0f, -1.0f, 0.0f, 0.0f },
                                   { 0.0f, -1.0f, 4.0f, -1.0f, 0.0f },
                                   { 0.0f, 0.0f, -1.0f, 5.0f, -1.0f },
                                   { 0.0f, 0.0f, 0.0f, -1.0f, -10.0f } };
    ktm::mat<6, 4, float> m11 = { { 1.0f, 4.0f, 7.0f, 2.0f },   { 4.0f, 5.0f, -1.0f, 4.0f },      { 7.2f, -1.6f, -2.0f, -5.0f },
                                   { 2.0f, 4.0f, 5.0f, 7.5f }, { 3.8f, -1.0f, 4.0f, -5.4f }, { 2.0f, 4.9f, 11.0f, 7.2f } };

    auto usv1 = ktm::decompose_svd(m10);
    std::cout << usv1.get_u() << std::endl;
    std::cout << usv1.get_s() << std::endl;
    std::cout << usv1.get_vt() << std::endl;
    auto usv1_ret = usv1.get_u() * ktm::mat<5, 5, float>::from_diag(usv1.get_s()) * usv1.get_vt();
    TEST_EQUAL_MATRIX(usv1_ret, m10, 5);

    auto usv2 = ktm::decompose_svd(m11);
    std::cout << usv2.get_u() << std::endl;
    std::cout << usv2.get_s() << std::endl;
    std::cout << usv2.get_vt() << std::endl;
    ktm::mat<6, 4, float> s2 = {};
    for (int i = 0; i < 4; ++i)
        s2[i][i] = usv2.get_s()[i];
    TEST_EQUAL_MATRIX(usv2.get_u() * s2 * usv2.get_vt(), m11, 6);

    auto usv3 = ktm::decompose_svd(ktm::transpose(m11));
    std::cout << usv3.get_u() << std::endl;
    std::cout << usv3.get_s() << std::endl;
    std::cout << usv3.get_vt() << std::endl;
    ktm::mat<4, 6, float> s3 = {};
    for (int i = 0; i < 4; ++i)
        s3[i][i] = usv3.get_s()[i];
    TEST_EQUAL_MATRIX(usv3.get_u() * s3 * usv3.get_vt(), ktm::transpose(m11), 4);

    ktm::fmat2x2 m12 = { { -5.f, 0.f }, { 3.f, 1.f } };
    ktm::mat<6, 6, float> mt13 = { { 1.0f, 4.0f, 7.0f, 2.0f, 5.0f, 0.0f },    { 4.0f, 5.0f, -1.0f, 4.0f, 3.0f, 0.0f },
                                    { 7.2f, -1.6f, -2.0f, -5.0f, 4.0f, 0.0f }, { 2.0f, 4.0f, 5.0f, 7.5f, 0.8f, 0.0f },
                                    { 3.8f, -1.0f, 4.0f, -5.4f, 4.6f, 0.0f },  { 8.0f, 9.0f, -2.0f, 7.6f, 9.1f, 1.0f } };

    auto affine1 = ktm::decompose_affine(m12);
    std::cout << affine1.get_translate() << std::endl;
    std::cout << affine1.get_rotate() << std::endl;
    std::cout << affine1.get_shear() << std::endl;
    std::cout << affine1.get_scale() << std::endl;
    TEST_EQUAL_MATRIX(affine1.get_translate() * affine1.get_rotate() * affine1.get_shear() * affine1.get_scale(), m12,
                      2);

    auto affine2 = ktm::decompose_affine(mt13);
    std::cout << affine2.get_translate() << std::endl;
    std::cout << affine2.get_rotate() << std::endl;
    std::cout << affine2.get_shear() << std::endl;
    std::cout << affine2.get_scale() << std::endl;
    TEST_EQUAL_MATRIX(affine2.get_translate() * affine2.get_rotate() * affine2.get_shear() * affine2.get_scale(), mt13,
                      6);

    return 0;
}