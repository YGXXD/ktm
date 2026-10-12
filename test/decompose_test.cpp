//  MIT License
//
//  Copyright (c) 2023-2026 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main(int argc, char* argv[])
{
    ktm::fmat1x1 m1 = { { 10.0f } };
    ktm::mat<5, 5, float> m2 = { { 6.0f, -1.0f, 0.0f, 0.0f, 0.0f },
                                 { -1.0f, 7.0f, -1.0f, 0.0f, 0.0f },
                                 { 0.0f, -1.0f, 8.0f, -1.0f, 0.0f },
                                 { 0.0f, 0.0f, -1.0f, 9.0f, -1.0f },
                                 { 0.0f, 0.0f, 0.0f, -1.0f, 10.0f } };
    ktm::fmat2x2 m3 = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
    ktm::mat<5, 5, float> m4 = {
        { 1.0f, 4.0f, 7.0f, 2.0f, 3.0f },   { 4.0f, 5.0f, -1.0f, 4.0f, -1.0f }, { 7.0f, -1.0f, -2.0f, -5.0f, 4.0f },
        { 2.0f, 4.0f, -5.0f, 7.0f, -5.0f }, { 3.0f, -1.0f, 4.0f, -5.0f, 4.0f },
    };

    auto lu1 = ktm::decompose_lu_cholesky(m1);
    std::cout << lu1.get_l() << std::endl;
    std::cout << lu1.get_u() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(lu1.get_l() * lu1.get_u(), m1, 1);

    auto lu2 = ktm::decompose_lu_cholesky(m2);
    std::cout << lu2.get_l() << std::endl;
    std::cout << lu2.get_u() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(lu2.get_l() * lu2.get_u(), m2, 5);

    auto lu3 = ktm::decompose_lu_doolittle(m3);
    std::cout << lu3.get_l() << std::endl;
    std::cout << lu3.get_u() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(lu3.get_l() * lu3.get_u(), m3, 2);

    auto lu4 = ktm::decompose_lu_crout(m4);
    std::cout << lu4.get_l() << std::endl;
    std::cout << lu4.get_u() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(lu4.get_l() * lu4.get_u(), m4, 5);

    ktm::fmat1x1 m5 = { { -3.0f } };
    ktm::fmat2x2 m6 = { { 8.0f, 2.0f }, { 5.0f, -4.0f } };
    ktm::fmat3x3 m7 = { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, { 7.0f, -1.0f, -2.0f } };
    ktm::mat<5, 5, float> m8 = {
        { 2.0f, 1.0f, 3.0f, 4.0f, 2.0f },  { 1.0f, 5.0f, 2.0f, -1.0f, 3.0f }, { 3.0f, 2.0f, 4.0f, 1.0f, -2.0f },
        { 4.0f, -1.0f, 1.0f, 6.0f, 2.0f }, { 2.0f, 3.0f, -2.0f, 2.0f, 3.0f },
    };

    auto qr1 = ktm::decompose_qr_givens(m5);
    std::cout << qr1.get_q() << std::endl;
    std::cout << qr1.get_r() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(qr1.get_q() * qr1.get_r(), m5, 1);

    auto qr2 = ktm::decompose_qr_householder(m6);
    std::cout << qr2.get_q() << std::endl;
    std::cout << qr2.get_r() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(qr2.get_q() * qr2.get_r(), m6, 2);

    auto qr3 = ktm::decompose_qr_givens(m7);
    std::cout << qr3.get_q() << std::endl;
    std::cout << qr3.get_r() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(qr3.get_q() * qr3.get_r(), m7, 3);

    auto qr4 = ktm::decompose_qr_schmitd(m8);
    std::cout << qr4.get_q() << std::endl;
    std::cout << qr4.get_r() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(qr4.get_q() * qr4.get_r(), m8, 5);

    ktm::mat<5, 5, float> m9 = {
        { 6.0f, 2.0f, -1.0f, 3.0f, 1.0f }, { 2.0f, 8.0f, 4.0f, -2.0f, 0.0f }, { -1.0f, 4.0f, 7.0f, 2.0f, -3.0f },
        { 3.0f, -2.0f, 2.0f, 9.0f, 5.0f }, { 1.0f, 0.0f, -3.0f, 5.0f, 4.0f },
    };
    ktm::fmat1x1 m10 = { { 7.0f } };
    ktm::fmat2x2 m11 = { { 5.0f, 2.0f }, { 2.0f, -3.0f } };
    ktm::fmat3x3 m12 = { { 5.0f, 2.0f, 2.0f }, { 2.0f, 5.0f, -5.2f }, { 2.0f, -5.2f, 7.0f } };

    auto edv1 = ktm::decompose_edv_jacobi(m9);
    std::cout << edv1.get_vector() << std::endl;
    std::cout << edv1.get_value() << std::endl;
    auto edv1_ret =
        edv1.get_vector() * ktm::mat<5, 5, float>::from_diag(edv1.get_value()) * ktm::transpose(edv1.get_vector());
    TEST_EQUAL_MATRIX_NORMAL(edv1_ret, m9, 5);

    auto edv2 = ktm::decompose_edv_jacobi(m10);
    std::cout << edv2.get_vector() << std::endl;
    std::cout << edv2.get_value() << std::endl;
    auto edv2_ret = edv2.get_vector() * ktm::fmat1x1::from_diag(edv2.get_value()) * ktm::transpose(edv2.get_vector());
    TEST_EQUAL_MATRIX_NORMAL(edv2_ret, m10, 1);

    auto edv3 = ktm::decompose_edv_shiftqr(m10);
    std::cout << edv3.get_vector() << std::endl;
    std::cout << edv3.get_value() << std::endl;
    auto edv3_ret = edv3.get_vector() * ktm::fmat1x1::from_diag(edv3.get_value()) * ktm::transpose(edv3.get_vector());
    TEST_EQUAL_MATRIX_NORMAL(edv3_ret, m10, 1);

    auto edv4 = ktm::decompose_edv_shiftqr(m11);
    std::cout << edv4.get_vector() << std::endl;
    std::cout << edv4.get_value() << std::endl;
    auto edv4_ret = edv4.get_vector() * ktm::fmat2x2::from_diag(edv4.get_value()) * ktm::transpose(edv4.get_vector());
    TEST_EQUAL_MATRIX_NORMAL(edv4_ret, m11, 2);

    auto edv5 = ktm::decompose_edv_shiftqr(m12);
    std::cout << edv5.get_vector() << std::endl;
    std::cout << edv5.get_value() << std::endl;
    auto edv5_ret = edv5.get_vector() * ktm::fmat3x3::from_diag(edv5.get_value()) * ktm::transpose(edv5.get_vector());
    TEST_EQUAL_MATRIX_NORMAL(edv5_ret, m12, 3);

    ktm::mat<5, 5, float> m13 = { { 2.0f, -1.0f, 0.0f, 0.0f, 0.0f },
                                  { -1.0f, 3.0f, -1.0f, 0.0f, 0.0f },
                                  { 0.0f, -1.0f, 4.0f, -1.0f, 0.0f },
                                  { 0.0f, 0.0f, -1.0f, 5.0f, -1.0f },
                                  { 0.0f, 0.0f, 0.0f, -1.0f, -10.0f } };
    ktm::mat<6, 4, float> m14 = { { 1.0f, 4.0f, 7.0f, 2.0f },    { 4.0f, 5.0f, -1.0f, 4.0f },
                                  { 7.2f, -1.6f, -2.0f, -5.0f }, { 2.0f, 4.0f, 5.0f, 7.5f },
                                  { 3.8f, -1.0f, 4.0f, -5.4f },  { 2.0f, 4.9f, 11.0f, 7.2f } };
    ktm::fmat4x1 m15 = { { 2.0f }, { 4.0f }, { 6.0f }, { 8.0f } };

    auto usv1 = ktm::decompose_svd(m13);
    std::cout << usv1.get_u() << std::endl;
    std::cout << usv1.get_s() << std::endl;
    std::cout << usv1.get_vt() << std::endl;
    auto usv1_ret = usv1.get_u() * ktm::mat<5, 5, float>::from_diag(usv1.get_s()) * usv1.get_vt();
    TEST_EQUAL_MATRIX_NORMAL(usv1_ret, m13, 5);

    auto usv2 = ktm::decompose_svd(m14);
    std::cout << usv2.get_u() << std::endl;
    std::cout << usv2.get_s() << std::endl;
    std::cout << usv2.get_vt() << std::endl;
    ktm::mat<6, 4, float> s2 = {};
    for (int i = 0; i < 4; ++i)
        s2[i][i] = usv2.get_s()[i];
    TEST_EQUAL_MATRIX_NORMAL(usv2.get_u() * s2 * usv2.get_vt(), m14, 6);

    auto usv3 = ktm::decompose_svd(ktm::transpose(m14));
    std::cout << usv3.get_u() << std::endl;
    std::cout << usv3.get_s() << std::endl;
    std::cout << usv3.get_vt() << std::endl;
    ktm::mat<4, 6, float> s3 = {};
    for (int i = 0; i < 4; ++i)
        s3[i][i] = usv3.get_s()[i];
    TEST_EQUAL_MATRIX_NORMAL(usv3.get_u() * s3 * usv3.get_vt(), ktm::transpose(m14), 4);

    auto usv4 = ktm::decompose_svd(m15);
    std::cout << usv4.get_u() << std::endl;
    std::cout << usv4.get_s() << std::endl;
    std::cout << usv4.get_vt() << std::endl;
    ktm::fmat4x1 s4 = {};
    s4[0][0] = usv4.get_s()[0];
    TEST_EQUAL_MATRIX_NORMAL(usv4.get_u() * s4 * usv4.get_vt(), m15, 4);

    ktm::fmat1x1 m16 = { { 5.0f } };
    ktm::fmat2x2 m17 = { { -5.0f, 0.0f }, { 3.0f, 1.0f } };
    ktm::fmat4x4 m18 = { { 1.0f, 4.0f, 7.2f, 0.0f },
                         { 4.0f, 5.0f, -1.6f, 0.0f },
                         { 7.0f, -1.0f, -2.0f, 0.0f },
                         { 2.0f, 3.0f, 4.0f, 1.0f } };
    ktm::mat<5, 5, float> m19 = { { 4.0f, 2.0f, 2.0f, 4.0f, 0.0f },
                                  { 4.0f, 5.0f, -3.0f, -9.0f, 0.0f },
                                  { -7.0f, 3.0f, 1.0f, 2.0f, 0.0f },
                                  { -1.0f, 3.0f, -4.0f, 1.0f, 0.0f },
                                  { 8.0f, -2.0f, -3.0f, 3.0f, 1.0f } };

    auto affine1 = ktm::decompose_affine(m16);
    std::cout << affine1.get_translate() << std::endl;
    std::cout << affine1.get_rotate() << std::endl;
    std::cout << affine1.get_shear() << std::endl;
    std::cout << affine1.get_scale() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(affine1.get_translate() * affine1.get_rotate() * affine1.get_shear() * affine1.get_scale(),
                             m16, 1);

    auto affine2 = ktm::decompose_affine(m17);
    std::cout << affine2.get_translate() << std::endl;
    std::cout << affine2.get_rotate() << std::endl;
    std::cout << affine2.get_shear() << std::endl;
    std::cout << affine2.get_scale() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(affine2.get_translate() * affine2.get_rotate() * affine2.get_shear() * affine2.get_scale(),
                             m17, 2);

    auto affine3 = ktm::decompose_affine(m18);
    std::cout << affine3.get_translate() << std::endl;
    std::cout << affine3.get_rotate() << std::endl;
    std::cout << affine3.get_shear() << std::endl;
    std::cout << affine3.get_scale() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(affine3.get_translate() * affine3.get_rotate() * affine3.get_shear() * affine3.get_scale(),
                             m18, 4);

    auto affine4 = ktm::decompose_affine(m19);
    std::cout << affine4.get_translate() << std::endl;
    std::cout << affine4.get_rotate() << std::endl;
    std::cout << affine4.get_shear() << std::endl;
    std::cout << affine4.get_scale() << std::endl;
    TEST_EQUAL_MATRIX_NORMAL(affine4.get_translate() * affine4.get_rotate() * affine4.get_shear() * affine4.get_scale(),
                             m19, 5);

    return 0;
}
