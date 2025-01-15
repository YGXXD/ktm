//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main()
{
    ktm::fmat2x2 m1 = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
    ktm::fmat2x2 m2 = { { 4.0f, 3.0f }, { 2.0f, 1.0f } };
    TEST_EQUAL_MATRIX(m1 + m2, ktm::fmat2x2({ { 5.0f, 5.0f }, { 5.0f, 5.0f } }), 2);
    TEST_EQUAL_MATRIX(m1 - m2, ktm::fmat2x2({ { -3.0f, -1.0f }, { 1.0f, 3.0f } }), 2);
    TEST_EQUAL_MATRIX(m1 * 2.0f, ktm::fmat2x2({ { 2.0f, 4.0f }, { 6.0f, 8.0f } }), 2);
    TEST_EQUAL_MATRIX(m1 * m2, ktm::fmat2x2({ { 13.0f, 20.0f }, { 5.0f, 8.0f } }), 2);
    TEST_EQUAL_MATRIX(m1 / 2.0f, ktm::fmat2x2({ { 0.5f, 1.0f }, { 1.5f, 2.0f } }), 2);
    ktm::fmat2x2 m3 = { { 2.0f, 1.0f }, { 1.0f, 2.0f } };
    TEST_EQUAL_MATRIX(ktm::transpose(m3), ktm::fmat2x2({ { 2.0f, 1.0f }, { 1.0f, 2.0f } }), 2);
    TEST_EQUAL(ktm::trace(m3), 4.0f);
    TEST_EQUAL(ktm::diagonal(m3), ktm::fvec2(2.0f, 2.0f));
    TEST_EQUAL(ktm::determinant(m3), 3.0f);
    TEST_EQUAL_MATRIX(ktm::inverse(m3) * m3, ktm::fmat2x2::from_eye(), 2);
    TEST_EQUAL_MATRIX(m3 * ktm::inverse(m3), ktm::fmat2x2::from_eye(), 2);

    ktm::fmat3x3 m4 = { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f }, { 7.0f, 8.0f, 9.0f } };
    ktm::fmat3x3 m5 = { { 9.0f, 8.0f, 7.0f }, { 6.0f, 5.0f, 4.0f }, { 3.0f, 2.0f, 1.0f } };
    TEST_EQUAL_MATRIX(m4 + m5,
                      ktm::fmat3x3({ { 10.0f, 10.0f, 10.0f }, { 10.0f, 10.0f, 10.0f }, { 10.0f, 10.0f, 10.0f } }), 3);
    TEST_EQUAL_MATRIX(m4 - m5, ktm::fmat3x3({ { -8.0f, -6.0f, -4.0f }, { -2.0f, 0.0f, 2.0f }, { 4.0f, 6.0f, 8.0f } }),
                      3);
    TEST_EQUAL_MATRIX(m4 * 2.0f,
                      ktm::fmat3x3({ { 2.0f, 4.0f, 6.0f }, { 8.0f, 10.0f, 12.0f }, { 14.0f, 16.0f, 18.0f } }), 3);
    TEST_EQUAL_MATRIX(m4 * m5,
                      ktm::fmat3x3({ { 90.0f, 114.0f, 138.0f }, { 54.0f, 69.0f, 84.0f }, { 18.0f, 24.0f, 30.0f } }), 3);
    TEST_EQUAL_MATRIX(m4 / 2.0f, ktm::fmat3x3({ { 0.5f, 1.0f, 1.5f }, { 2.0f, 2.5f, 3.0f }, { 3.5f, 4.0f, 4.5f } }), 3);
    ktm::fmat3x3 m6 = { { 2.0f, 1.0f, 3.0f }, { 1.0f, 2.0f, 1.0f }, { 3.0f, 4.0f, 1.0f } };
    TEST_EQUAL_MATRIX(ktm::transpose(m6),
                      ktm::fmat3x3({ { 2.0f, 1.0f, 3.0f }, { 1.0f, 2.0f, 4.0f }, { 3.0f, 1.0f, 1.0f } }), 3);
    TEST_EQUAL(ktm::trace(m6), 5.0f);
    TEST_EQUAL(ktm::diagonal(m6), ktm::fvec3(2.0f, 2.0f, 1.0f));
    TEST_EQUAL(ktm::determinant(m6), -8.0f);
    TEST_EQUAL_MATRIX(ktm::inverse(m6) * m6, ktm::fmat3x3::from_eye(), 3);
    TEST_EQUAL_MATRIX(m6 * ktm::inverse(m6), ktm::fmat3x3::from_eye(), 3);

    ktm::fmat4x4 m7 = {
        { 1.0f, 2.0f, 3.0f, 4.9f }, { 4.0f, 5.0f, 6.0f, 1.0f }, { 7.0f, 8.0f, 9.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }
    };
    ktm::fmat4x4 m8 = {
        { 9.0f, 8.0f, 7.0f, 2.8f }, { 6.0f, 5.0f, 4.0f, 1.0f }, { 3.0f, 2.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }
    };
    TEST_EQUAL_MATRIX(m7 + m8,
                      ktm::fmat4x4({ { 10.0f, 10.0f, 10.0f, 7.7f },
                                     { 10.0f, 10.0f, 10.0f, 2.0f },
                                     { 10.0f, 10.0f, 10.0f, 2.0f },
                                     { 2.0f, 2.0f, 2.0f, 2.0f } }),
                      4);
    TEST_EQUAL_MATRIX(m7 - m8,
                      ktm::fmat4x4({ { -8.0f, -6.0f, -4.0f, 2.1f },
                                     { -2.0f, 0.0f, 2.0f, 0.0f },
                                     { 4.0f, 6.0f, 8.0f, 0.0f },
                                     { 0.0f, 0.0f, 0.0f, 0.0f } }),
                      4);
    TEST_EQUAL_MATRIX(m7 * 2.0f,
                      ktm::fmat4x4({ { 2.0f, 4.0f, 6.0f, 9.8f },
                                     { 8.0f, 10.0f, 12.0f, 2.0f },
                                     { 14.0f, 16.0f, 18.0f, 2.0f },
                                     { 2.0f, 2.0f, 2.0f, 2.0f } }),
                      4);
    TEST_EQUAL_MATRIX(m7 * m8,
                      ktm::fmat4x4({ { 92.8f, 116.8f, 140.8f, 61.9f },
                                     { 55.0f, 70.0f, 85.0f, 39.4f },
                                     { 19.0f, 25.0f, 31.0f, 18.7f },
                                     { 13.0f, 16.0f, 19.0f, 7.9f } }),
                      4);
    TEST_EQUAL_MATRIX(m7 / 2.0f,
                      ktm::fmat4x4({ { 0.5f, 1.0f, 1.5f, 2.45f },
                                     { 2.0f, 2.5f, 3.0f, 0.5f },
                                     { 3.5f, 4.0f, 4.5f, 0.5f },
                                     { 0.5f, 0.5f, 0.5f, 0.5f } }),
                      4);
    ktm::fmat4x4 m9 = {
        { 2.0f, 1.0f, 3.0f, 4.0f }, { 1.0f, 2.0f, 1.0f, -3.0f }, { 3.0f, 4.0f, 1.0f, 2.0f }, { 2.0f, 1.0f, -2.0f, 3.0f }
    };
    TEST_EQUAL_MATRIX(ktm::transpose(m9),
                      ktm::fmat4x4({ { 2.0f, 1.0f, 3.0f, 2.0f },
                                     { 1.0f, 2.0f, 4.0f, 1.0f },
                                     { 3.0f, 1.0f, 1.0f, -2.0f },
                                     { 4.0f, -3.0f, 2.0f, 3.0f } }),
                      4);
    TEST_EQUAL(ktm::trace(m9), 8.0f);
    TEST_EQUAL(ktm::diagonal(m9), ktm::fvec4(2.0f, 2.0f, 1.0f, 3.0f));
    TEST_EQUAL(ktm::determinant(m9), 73.0f);
    TEST_EQUAL_MATRIX(ktm::inverse(m9) * m9, ktm::fmat4x4::from_eye(), 4);
    TEST_EQUAL_MATRIX(m9 * ktm::inverse(m9), ktm::fmat4x4::from_eye(), 4);

    return 0;
}