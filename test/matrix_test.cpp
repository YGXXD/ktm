//  MIT License
//
//  Copyright (c) 2023-2026 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main()
{
    ktm::fmat1x1 m1 = { { 2.0f } };
    ktm::fmat1x1 m2 = { { 4.0f } };
    TEST_EQUAL_MATRIX(m1 + m2, ktm::fmat1x1({ { 6.0f } }), 1);
    TEST_EQUAL_MATRIX(m1 - m2, ktm::fmat1x1({ { -2.0f } }), 1);
    TEST_EQUAL_MATRIX(m1 * 2.0f, ktm::fmat1x1({ { 4.0f } }), 1);
    TEST_EQUAL_MATRIX(m1 * m2, ktm::fmat1x1({ { 8.0f } }), 1);
    TEST_EQUAL_MATRIX(m1 / 2.0f, ktm::fmat1x1({ { 1.0f } }), 1);
    ktm::fmat1x1 m3 = { { 3.0f } };
    TEST_EQUAL_MATRIX(ktm::transpose(m3), ktm::fmat1x1({ { 3.0f } }), 1);
    TEST_EQUAL(ktm::trace(m3), 3.0f);
    TEST_EQUAL(ktm::diagonal(m3), ktm::fvec1(3.0f));
    TEST_EQUAL(ktm::determinant(m3), 3.0f);
    TEST_EQUAL_MATRIX(ktm::inverse(m3) * m3, ktm::fmat1x1::from_eye(), 1);
    TEST_EQUAL_MATRIX(m3 * ktm::inverse(m3), ktm::fmat1x1::from_eye(), 1);
    TEST_EQUAL(m3 * ktm::fvec1(2.0f), ktm::fvec1(6.0f));
    TEST_EQUAL(ktm::fvec1(2.0f) * m3, ktm::fvec1(6.0f));

    ktm::fmat2x2 m4 = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
    ktm::fmat2x2 m5 = { { 4.0f, 3.0f }, { 2.0f, 1.0f } };
    TEST_EQUAL_MATRIX(m4 + m5, ktm::fmat2x2({ { 5.0f, 5.0f }, { 5.0f, 5.0f } }), 2);
    TEST_EQUAL_MATRIX(m4 - m5, ktm::fmat2x2({ { -3.0f, -1.0f }, { 1.0f, 3.0f } }), 2);
    TEST_EQUAL_MATRIX(m4 * 2.0f, ktm::fmat2x2({ { 2.0f, 4.0f }, { 6.0f, 8.0f } }), 2);
    TEST_EQUAL_MATRIX(m4 * m5, ktm::fmat2x2({ { 13.0f, 20.0f }, { 5.0f, 8.0f } }), 2);
    TEST_EQUAL_MATRIX(m4 / 2.0f, ktm::fmat2x2({ { 0.5f, 1.0f }, { 1.5f, 2.0f } }), 2);
    ktm::fmat2x2 m6 = { { 2.0f, 1.0f }, { 1.0f, 2.0f } };
    TEST_EQUAL_MATRIX(ktm::transpose(m6), ktm::fmat2x2({ { 2.0f, 1.0f }, { 1.0f, 2.0f } }), 2);
    TEST_EQUAL(ktm::trace(m6), 4.0f);
    TEST_EQUAL(ktm::diagonal(m6), ktm::fvec2(2.0f, 2.0f));
    TEST_EQUAL(ktm::determinant(m6), 3.0f);
    TEST_EQUAL_MATRIX(ktm::inverse(m6) * m6, ktm::fmat2x2::from_eye(), 2);
    TEST_EQUAL_MATRIX(m6 * ktm::inverse(m6), ktm::fmat2x2::from_eye(), 2);
    TEST_EQUAL(m6 * ktm::fvec2(1.0f, 2.0f), ktm::fvec2(4.0f, 5.0f));
    TEST_EQUAL(ktm::fvec2(1.0f, 2.0f) * m6, ktm::fvec2(4.0f, 5.0f));

    ktm::fmat3x3 m7 = { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f } };
    ktm::fmat3x3 m8 = { { 9.0f, 8.0f, 7.0f }, { 6.0f, 5.0f, 4.0f }, { 3.0f, 2.0f, 1.0f } };
    TEST_EQUAL_MATRIX(m7 + m8,
                      ktm::fmat3x3({ { 10.0f, 10.0f, 10.0f }, { 10.0f, 10.0f, 10.0f }, { 10.0f, 10.0f, 10.0f } }), 3);
    TEST_EQUAL_MATRIX(m7 - m8, ktm::fmat3x3({ { -8.0f, -6.0f, -4.0f }, { -2.0f, 0.0f, 2.0f }, { 4.0f, 6.0f, 8.0f } }),
                      3);
    TEST_EQUAL_MATRIX(m7 * 2.0f,
                      ktm::fmat3x3({ { 2.0f, 4.0f, 6.0f }, { 8.0f, 10.0f, 12.0f }, { 14.0f, 16.0f, 18.0f } }), 3);
    TEST_EQUAL_MATRIX(m7 * m8,
                      ktm::fmat3x3({ { 90.0f, 114.0f, 138.0f }, { 54.0f, 69.0f, 84.0f }, { 18.0f, 24.0f, 30.0f } }), 3);
    TEST_EQUAL_MATRIX(m7 / 2.0f, ktm::fmat3x3({ { 0.5f, 1.0f, 1.5f }, { 2.0f, 2.5f, 3.0f }, { 3.5f, 4.0f, 4.5f } }), 3);
    ktm::fmat3x3 m9 = { { 2.0f, 1.0f, 3.0f }, { 1.0f, 2.0f, 1.0f }, { 3.0f, 4.0f, 1.0f } };
    TEST_EQUAL_MATRIX(ktm::transpose(m9),
                      ktm::fmat3x3({ { 2.0f, 1.0f, 3.0f }, { 1.0f, 2.0f, 4.0f }, { 3.0f, 1.0f, 1.0f } }), 3);
    TEST_EQUAL(ktm::trace(m9), 5.0f);
    TEST_EQUAL(ktm::diagonal(m9), ktm::fvec3(2.0f, 2.0f, 1.0f));
    TEST_EQUAL(ktm::determinant(m9), -8.0f);
    TEST_EQUAL_MATRIX(ktm::inverse(m9) * m9, ktm::fmat3x3::from_eye(), 3);
    TEST_EQUAL_MATRIX(m9 * ktm::inverse(m9), ktm::fmat3x3::from_eye(), 3);
    TEST_EQUAL(m9 * ktm::fvec3(1.0f, 2.0f, 3.0f), ktm::fvec3(13.0f, 17.0f, 8.0f));
    TEST_EQUAL(ktm::fvec3(1.0f, 2.0f, 3.0f) * m9, ktm::fvec3(13.0f, 8.0f, 14.0f));

    ktm::fmat4x4 m10 = {
        { 1.0f, 2.0f, 3.0f, 4.9f }, { 4.0f, 5.0f, 6.0f, 1.0f }, { 7.0f, 8.0f, 9.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }
    };
    ktm::fmat4x4 m11 = {
        { 9.0f, 8.0f, 7.0f, 2.8f }, { 6.0f, 5.0f, 4.0f, 1.0f }, { 3.0f, 2.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }
    };
    TEST_EQUAL_MATRIX(m10 + m11,
                      ktm::fmat4x4({ { 10.0f, 10.0f, 10.0f, 7.7f },
                                     { 10.0f, 10.0f, 10.0f, 2.0f },
                                     { 10.0f, 10.0f, 10.0f, 2.0f },
                                     { 2.0f, 2.0f, 2.0f, 2.0f } }),
                      4);
    TEST_EQUAL_MATRIX(m10 - m11,
                      ktm::fmat4x4({ { -8.0f, -6.0f, -4.0f, 2.1f },
                                     { -2.0f, 0.0f, 2.0f, 0.0f },
                                     { 4.0f, 6.0f, 8.0f, 0.0f },
                                     { 0.0f, 0.0f, 0.0f, 0.0f } }),
                      4);
    TEST_EQUAL_MATRIX(m10 * 2.0f,
                      ktm::fmat4x4({ { 2.0f, 4.0f, 6.0f, 9.8f },
                                     { 8.0f, 10.0f, 12.0f, 2.0f },
                                     { 14.0f, 16.0f, 18.0f, 2.0f },
                                     { 2.0f, 2.0f, 2.0f, 2.0f } }),
                      4);
    TEST_EQUAL_MATRIX(m10 * m11,
                      ktm::fmat4x4({ { 92.8f, 116.8f, 140.8f, 61.9f },
                                     { 55.0f, 70.0f, 85.0f, 39.4f },
                                     { 19.0f, 25.0f, 31.0f, 18.7f },
                                     { 13.0f, 16.0f, 19.0f, 7.9f } }),
                      4);
    TEST_EQUAL_MATRIX(m10 / 2.0f,
                      ktm::fmat4x4({ { 0.5f, 1.0f, 1.5f, 2.45f },
                                     { 2.0f, 2.5f, 3.0f, 0.5f },
                                     { 3.5f, 4.0f, 4.5f, 0.5f },
                                     { 0.5f, 0.5f, 0.5f, 0.5f } }),
                      4);
    ktm::fmat4x4 m12 = {
        { 2.0f, 1.0f, 3.0f, 4.0f }, { 1.0f, 2.0f, 1.0f, -3.0f }, { 3.0f, 4.0f, 1.0f, 2.0f }, { 2.0f, 1.0f, -2.0f, 3.0f }
    };
    TEST_EQUAL_MATRIX(ktm::transpose(m12),
                      ktm::fmat4x4({ { 2.0f, 1.0f, 3.0f, 2.0f },
                                     { 1.0f, 2.0f, 4.0f, 1.0f },
                                     { 3.0f, 1.0f, 1.0f, -2.0f },
                                     { 4.0f, -3.0f, 2.0f, 3.0f } }),
                      4);
    TEST_EQUAL(ktm::trace(m12), 8.0f);
    TEST_EQUAL(ktm::diagonal(m12), ktm::fvec4(2.0f, 2.0f, 1.0f, 3.0f));
    TEST_EQUAL(ktm::determinant(m12), 73.0f);
    TEST_EQUAL_MATRIX(ktm::inverse(m12) * m12, ktm::fmat4x4::from_eye(), 4);
    TEST_EQUAL_MATRIX(m12 * ktm::inverse(m12), ktm::fmat4x4::from_eye(), 4);
    TEST_EQUAL(m12 * ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f), ktm::fvec4(21.0f, 21.0f, 0.0f, 16.0f));
    TEST_EQUAL(ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f) * m12, ktm::fvec4(29.0f, -4.0f, 22.0f, 10.0f));

    ktm::fmat1x4 m13 = { { 1.0f, 2.0f, 3.0f, 4.0f } };
    ktm::fmat4x1 m14 = { { 5.0f }, { 6.0f }, { 7.0f }, { 8.0f } };
    TEST_EQUAL_MATRIX(ktm::transpose(m13), ktm::fmat4x1({ { 1.0f }, { 2.0f }, { 3.0f }, { 4.0f } }), 4);
    TEST_EQUAL_MATRIX(ktm::transpose(m14), ktm::fmat1x4({ { 5.0f, 6.0f, 7.0f, 8.0f } }), 1);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m13)), m13, 1);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m14)), m14, 4);
    TEST_EQUAL_MATRIX(m13 + ktm::fmat1x4({ { 9.0f, 8.0f, 7.0f, 6.0f } }),
                      ktm::fmat1x4({ { 10.0f, 10.0f, 10.0f, 10.0f } }), 1);
    TEST_EQUAL_MATRIX(m14 - ktm::fmat4x1({ { 1.0f }, { 2.0f }, { 3.0f }, { 4.0f } }),
                      ktm::fmat4x1({ { 4.0f }, { 4.0f }, { 4.0f }, { 4.0f } }), 4);
    TEST_EQUAL_MATRIX(m13 * 2.0f, ktm::fmat1x4({ { 2.0f, 4.0f, 6.0f, 8.0f } }), 1);
    TEST_EQUAL_MATRIX(m14 / 2.0f, ktm::fmat4x1({ { 2.5f }, { 3.0f }, { 3.5f }, { 4.0f } }), 4);
    TEST_EQUAL_MATRIX(m13 * m14,
                      ktm::fmat4x4({ { 5.0f, 10.0f, 15.0f, 20.0f },
                                     { 6.0f, 12.0f, 18.0f, 24.0f },
                                     { 7.0f, 14.0f, 21.0f, 28.0f },
                                     { 8.0f, 16.0f, 24.0f, 32.0f } }),
                      4);
    TEST_EQUAL_MATRIX(m14 * m13, ktm::fmat1x1({ { 70.0f } }), 1);
    TEST_EQUAL(m13 * ktm::fvec1(2.0f), ktm::fvec4(2.0f, 4.0f, 6.0f, 8.0f));
    TEST_EQUAL(ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f) * m13, ktm::fvec1(30.0f));
    TEST_EQUAL(m14 * ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f), ktm::fvec1(70.0f));
    TEST_EQUAL(ktm::fvec1(2.0f) * m14, ktm::fvec4(10.0f, 12.0f, 14.0f, 16.0f));

    ktm::fmat1x2 m15 = { { 1.0f, 2.0f } };
    ktm::fmat2x1 m16 = { { 3.0f }, { 4.0f } };
    TEST_EQUAL_MATRIX(ktm::transpose(m15), ktm::fmat2x1({ { 1.0f }, { 2.0f } }), 2);
    TEST_EQUAL_MATRIX(ktm::transpose(m16), ktm::fmat1x2({ { 3.0f, 4.0f } }), 1);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m15)), m15, 1);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m16)), m16, 2);
    TEST_EQUAL_MATRIX(m15 + ktm::fmat1x2({ { 9.0f, 8.0f } }), ktm::fmat1x2({ { 10.0f, 10.0f } }), 1);
    TEST_EQUAL_MATRIX(m16 - ktm::fmat2x1({ { 1.0f }, { 2.0f } }), ktm::fmat2x1({ { 2.0f }, { 2.0f } }), 2);
    TEST_EQUAL_MATRIX(m15 * 2.0f, ktm::fmat1x2({ { 2.0f, 4.0f } }), 1);
    TEST_EQUAL_MATRIX(m16 / 2.0f, ktm::fmat2x1({ { 1.5f }, { 2.0f } }), 2);
    TEST_EQUAL_MATRIX(m15 * m16, ktm::fmat2x2({ { 3.0f, 6.0f }, { 4.0f, 8.0f } }), 2);
    TEST_EQUAL_MATRIX(m16 * m15, ktm::fmat1x1({ { 11.0f } }), 1);
    TEST_EQUAL(m15 * ktm::fvec1(2.0f), ktm::fvec2(2.0f, 4.0f));
    TEST_EQUAL(ktm::fvec2(1.0f, 2.0f) * m15, ktm::fvec1(5.0f));
    TEST_EQUAL(m16 * ktm::fvec2(1.0f, 2.0f), ktm::fvec1(11.0f));
    TEST_EQUAL(ktm::fvec1(2.0f) * m16, ktm::fvec2(6.0f, 8.0f));

    ktm::fmat1x3 m17 = { { 1.0f, 2.0f, 3.0f } };
    ktm::fmat3x1 m18 = { { 4.0f }, { 5.0f }, { 6.0f } };
    TEST_EQUAL_MATRIX(ktm::transpose(m17), ktm::fmat3x1({ { 1.0f }, { 2.0f }, { 3.0f } }), 3);
    TEST_EQUAL_MATRIX(ktm::transpose(m18), ktm::fmat1x3({ { 4.0f, 5.0f, 6.0f } }), 1);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m17)), m17, 1);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m18)), m18, 3);
    TEST_EQUAL_MATRIX(m17 + ktm::fmat1x3({ { 9.0f, 8.0f, 7.0f } }), ktm::fmat1x3({ { 10.0f, 10.0f, 10.0f } }), 1);
    TEST_EQUAL_MATRIX(m18 - ktm::fmat3x1({ { 1.0f }, { 2.0f }, { 3.0f } }),
                      ktm::fmat3x1({ { 3.0f }, { 3.0f }, { 3.0f } }), 3);
    TEST_EQUAL_MATRIX(m17 * 2.0f, ktm::fmat1x3({ { 2.0f, 4.0f, 6.0f } }), 1);
    TEST_EQUAL_MATRIX(m18 / 2.0f, ktm::fmat3x1({ { 2.0f }, { 2.5f }, { 3.0f } }), 3);
    TEST_EQUAL_MATRIX(m17 * m18,
                      ktm::fmat3x3({ { 4.0f, 8.0f, 12.0f }, { 5.0f, 10.0f, 15.0f }, { 6.0f, 12.0f, 18.0f } }), 3);
    TEST_EQUAL_MATRIX(m18 * m17, ktm::fmat1x1({ { 32.0f } }), 1);
    TEST_EQUAL(m17 * ktm::fvec1(2.0f), ktm::fvec3(2.0f, 4.0f, 6.0f));
    TEST_EQUAL(ktm::fvec3(1.0f, 2.0f, 3.0f) * m17, ktm::fvec1(14.0f));
    TEST_EQUAL(m18 * ktm::fvec3(1.0f, 2.0f, 3.0f), ktm::fvec1(32.0f));
    TEST_EQUAL(ktm::fvec1(2.0f) * m18, ktm::fvec3(8.0f, 10.0f, 12.0f));

    ktm::fmat2x3 m19 = { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f } };
    ktm::fmat3x2 m20 = { { 7.0f, 8.0f }, { 9.0f, 10.0f }, { 11.0f, 12.0f } };
    TEST_EQUAL_MATRIX(ktm::transpose(m19), ktm::fmat3x2({ { 1.0f, 4.0f }, { 2.0f, 5.0f }, { 3.0f, 6.0f } }), 3);
    TEST_EQUAL_MATRIX(ktm::transpose(m20), ktm::fmat2x3({ { 7.0f, 9.0f, 11.0f }, { 8.0f, 10.0f, 12.0f } }), 2);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m19)), m19, 2);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m20)), m20, 3);
    TEST_EQUAL_MATRIX(m19 + ktm::fmat2x3({ { 9.0f, 8.0f, 7.0f }, { 6.0f, 5.0f, 4.0f } }),
                      ktm::fmat2x3({ { 10.0f, 10.0f, 10.0f }, { 10.0f, 10.0f, 10.0f } }), 2);
    TEST_EQUAL_MATRIX(m20 - ktm::fmat3x2({ { 1.0f, 2.0f }, { 3.0f, 4.0f }, { 5.0f, 6.0f } }),
                      ktm::fmat3x2({ { 6.0f, 6.0f }, { 6.0f, 6.0f }, { 6.0f, 6.0f } }), 3);
    TEST_EQUAL_MATRIX(m19 * 2.0f, ktm::fmat2x3({ { 2.0f, 4.0f, 6.0f }, { 8.0f, 10.0f, 12.0f } }), 2);
    TEST_EQUAL_MATRIX(m20 / 2.0f, ktm::fmat3x2({ { 3.5f, 4.0f }, { 4.5f, 5.0f }, { 5.5f, 6.0f } }), 3);
    TEST_EQUAL_MATRIX(m19 * m20,
                      ktm::fmat3x3({ { 39.0f, 54.0f, 69.0f }, { 49.0f, 68.0f, 87.0f }, { 59.0f, 82.0f, 105.0f } }), 3);
    TEST_EQUAL_MATRIX(m20 * m19, ktm::fmat2x2({ { 58.0f, 64.0f }, { 139.0f, 154.0f } }), 2);
    TEST_EQUAL(m19 * ktm::fvec2(1.0f, 2.0f), ktm::fvec3(9.0f, 12.0f, 15.0f));
    TEST_EQUAL(ktm::fvec3(1.0f, 2.0f, 3.0f) * m19, ktm::fvec2(14.0f, 32.0f));
    TEST_EQUAL(m20 * ktm::fvec3(1.0f, 2.0f, 3.0f), ktm::fvec2(58.0f, 64.0f));
    TEST_EQUAL(ktm::fvec2(1.0f, 2.0f) * m20, ktm::fvec3(23.0f, 29.0f, 35.0f));

    ktm::fmat2x4 m21 = { { 1.0f, 2.0f, 3.0f, 4.0f }, { 5.0f, 6.0f, 7.0f, 8.0f } };
    ktm::fmat4x2 m22 = { { 9.0f, 10.0f }, { 11.0f, 12.0f }, { 13.0f, 14.0f }, { 15.0f, 16.0f } };
    TEST_EQUAL_MATRIX(ktm::transpose(m21),
                      ktm::fmat4x2({ { 1.0f, 5.0f }, { 2.0f, 6.0f }, { 3.0f, 7.0f }, { 4.0f, 8.0f } }), 4);
    TEST_EQUAL_MATRIX(ktm::transpose(m22),
                      ktm::fmat2x4({ { 9.0f, 11.0f, 13.0f, 15.0f }, { 10.0f, 12.0f, 14.0f, 16.0f } }), 2);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m21)), m21, 2);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m22)), m22, 4);
    TEST_EQUAL_MATRIX(m21 + ktm::fmat2x4({ { 9.0f, 8.0f, 7.0f, 6.0f }, { 5.0f, 4.0f, 3.0f, 2.0f } }),
                      ktm::fmat2x4({ { 10.0f, 10.0f, 10.0f, 10.0f }, { 10.0f, 10.0f, 10.0f, 10.0f } }), 2);
    TEST_EQUAL_MATRIX(m22 - ktm::fmat4x2({ { 1.0f, 2.0f }, { 3.0f, 4.0f }, { 5.0f, 6.0f }, { 7.0f, 8.0f } }),
                      ktm::fmat4x2({ { 8.0f, 8.0f }, { 8.0f, 8.0f }, { 8.0f, 8.0f }, { 8.0f, 8.0f } }), 4);
    TEST_EQUAL_MATRIX(m21 * 2.0f, ktm::fmat2x4({ { 2.0f, 4.0f, 6.0f, 8.0f }, { 10.0f, 12.0f, 14.0f, 16.0f } }), 2);
    TEST_EQUAL_MATRIX(m22 / 2.0f, ktm::fmat4x2({ { 4.5f, 5.0f }, { 5.5f, 6.0f }, { 6.5f, 7.0f }, { 7.5f, 8.0f } }), 4);
    TEST_EQUAL_MATRIX(m21 * m22,
                      ktm::fmat4x4({ { 59.0f, 78.0f, 97.0f, 116.0f },
                                     { 71.0f, 94.0f, 117.0f, 140.0f },
                                     { 83.0f, 110.0f, 137.0f, 164.0f },
                                     { 95.0f, 126.0f, 157.0f, 188.0f } }),
                      4);
    TEST_EQUAL_MATRIX(m22 * m21, ktm::fmat2x2({ { 130.0f, 140.0f }, { 322.0f, 348.0f } }), 2);
    TEST_EQUAL(m21 * ktm::fvec2(1.0f, 2.0f), ktm::fvec4(11.0f, 14.0f, 17.0f, 20.0f));
    TEST_EQUAL(ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f) * m21, ktm::fvec2(30.0f, 70.0f));
    TEST_EQUAL(m22 * ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f), ktm::fvec2(130.0f, 140.0f));
    TEST_EQUAL(ktm::fvec2(1.0f, 2.0f) * m22, ktm::fvec4(29.0f, 35.0f, 41.0f, 47.0f));

    ktm::fmat3x4 m23 = { { 1.0f, 2.0f, 3.0f, 4.0f }, { 5.0f, 6.0f, 7.0f, 8.0f }, { 9.0f, 10.0f, 11.0f, 12.0f } };
    ktm::fmat4x3 m24 = {
        { 13.0f, 14.0f, 15.0f }, { 16.0f, 17.0f, 18.0f }, { 19.0f, 20.0f, 21.0f }, { 22.0f, 23.0f, 24.0f }
    };
    TEST_EQUAL_MATRIX(
        ktm::transpose(m23),
        ktm::fmat4x3({ { 1.0f, 5.0f, 9.0f }, { 2.0f, 6.0f, 10.0f }, { 3.0f, 7.0f, 11.0f }, { 4.0f, 8.0f, 12.0f } }), 4);
    TEST_EQUAL_MATRIX(
        ktm::transpose(m24),
        ktm::fmat3x4(
            { { 13.0f, 16.0f, 19.0f, 22.0f }, { 14.0f, 17.0f, 20.0f, 23.0f }, { 15.0f, 18.0f, 21.0f, 24.0f } }),
        3);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m23)), m23, 3);
    TEST_EQUAL_MATRIX(ktm::transpose(ktm::transpose(m24)), m24, 4);
    TEST_EQUAL_MATRIX(
        m23 + ktm::fmat3x4({ { 9.0f, 8.0f, 7.0f, 6.0f }, { 5.0f, 4.0f, 3.0f, 2.0f }, { 1.0f, 0.0f, -1.0f, -2.0f } }),
        ktm::fmat3x4(
            { { 10.0f, 10.0f, 10.0f, 10.0f }, { 10.0f, 10.0f, 10.0f, 10.0f }, { 10.0f, 10.0f, 10.0f, 10.0f } }),
        3);
    TEST_EQUAL_MATRIX(
        m24 -
            ktm::fmat4x3({ { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f }, { 10.0f, 11.0f, 12.0f } }),
        ktm::fmat4x3(
            { { 12.0f, 12.0f, 12.0f }, { 12.0f, 12.0f, 12.0f }, { 12.0f, 12.0f, 12.0f }, { 12.0f, 12.0f, 12.0f } }),
        4);
    TEST_EQUAL_MATRIX(
        m23 * 2.0f,
        ktm::fmat3x4({ { 2.0f, 4.0f, 6.0f, 8.0f }, { 10.0f, 12.0f, 14.0f, 16.0f }, { 18.0f, 20.0f, 22.0f, 24.0f } }),
        3);
    TEST_EQUAL_MATRIX(
        m24 / 2.0f,
        ktm::fmat4x3({ { 6.5f, 7.0f, 7.5f }, { 8.0f, 8.5f, 9.0f }, { 9.5f, 10.0f, 10.5f }, { 11.0f, 11.5f, 12.0f } }),
        4);
    TEST_EQUAL_MATRIX(m23 * m24,
                      ktm::fmat4x4({ { 218.0f, 260.0f, 302.0f, 344.0f },
                                     { 263.0f, 314.0f, 365.0f, 416.0f },
                                     { 308.0f, 368.0f, 428.0f, 488.0f },
                                     { 353.0f, 422.0f, 491.0f, 560.0f } }),
                      4);
    TEST_EQUAL_MATRIX(
        m24 * m23, ktm::fmat3x3({ { 190.0f, 200.0f, 210.0f }, { 470.0f, 496.0f, 522.0f }, { 750.0f, 792.0f, 834.0f } }),
        3);
    TEST_EQUAL(m23 * ktm::fvec3(1.0f, 2.0f, 3.0f), ktm::fvec4(38.0f, 44.0f, 50.0f, 56.0f));
    TEST_EQUAL(ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f) * m23, ktm::fvec3(30.0f, 70.0f, 110.0f));
    TEST_EQUAL(m24 * ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f), ktm::fvec3(190.0f, 200.0f, 210.0f));
    TEST_EQUAL(ktm::fvec3(1.0f, 2.0f, 3.0f) * m24, ktm::fvec4(86.0f, 104.0f, 122.0f, 140.0f));

    return 0;
}
