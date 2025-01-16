//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main()
{
    TEST_EQUAL_QUATERNION(ktm::fquat(1.0f, 2.0f, -1.0f, -2.0f) + ktm::fquat(2.0f, -1.0f, 1.0f, 3.0f),
                          ktm::fquat(3.0f, 1.0f, 0.0f, 1.0f));
    TEST_EQUAL_QUATERNION(ktm::fquat(1.0f, 2.0f, -1.0f, -2.0f) - ktm::fquat(2.0f, -1.0f, 1.0f, 3.0f),
                          ktm::fquat(-1.0f, 3.0f, -2.0f, -5.0f));
    TEST_EQUAL_QUATERNION(ktm::fquat(1.0f, 2.0f, -1.0f, -2.0f) * 2.0f, ktm::fquat(2.0f, 4.0f, -2.0f, -4.0f));
    TEST_EQUAL_QUATERNION(-ktm::fquat(1.0f, 2.0f, -1.0f, -2.0f), ktm::fquat(-1.0f, -2.0f, 1.0f, 2.0f));

    TEST_EQUAL_QUATERNION(ktm::conjugate(ktm::fquat(2.0f, 3.0f, -1.0f, -2.0f)), ktm::fquat(-2.0f, -3.0f, 1.0f, -2.0f));
    TEST_EQUAL_QUATERNION(ktm::inverse(ktm::fquat(1.0f)) * ktm::fquat(1.0f), ktm::fquat::identity());
    TEST_EQUAL_QUATERNION(ktm::fquat(2.0f) * ktm::inverse(ktm::fquat(2.0f)), ktm::fquat::identity());
    TEST_EQUAL(ktm::sqrt(ktm::dot(ktm::fquat(1.5f), ktm::fquat(1.5f))), ktm::length(ktm::fquat(1.5f)));
    TEST_EQUAL(ktm::length(ktm::normalize(ktm::fquat(1.0f, 2.0f, 3.0f, 4.0f))), 1.0f);
    TEST_EQUAL_QUATERNION(ktm::normalize(ktm::fquat()), ktm::fquat(0.0f, 0.0f, 0.0f, 1.0f));
    TEST_EQUAL_QUATERNION(ktm::exp(ktm::fquat(1.0f, 2.0f, -1.0f, 1.0f)),
                          ktm::fquat(0.708185f, 1.416370f, -0.708185f, -2.092821f));
    TEST_EQUAL_QUATERNION(ktm::log(ktm::fquat(0.5f, 1.0f, -0.5f, 2.0f)),
                          ktm::fquat(0.224319f, 0.448638f, -0.224319f, 0.852374f));
    TEST_EQUAL_QUATERNION(ktm::log(ktm::exp(ktm::fquat(0.5f, 1.5f, -0.5f, 2.5f))), ktm::fquat(0.5f, 1.5f, -0.5f, 2.5f));

    ktm::fmat4x4 m = ktm::rotate3d_axis(1.0f, ktm::normalize(ktm::fvec3(0.0f, 0.6f, 0.8f)));
    ktm::fquat q1 = ktm::fquat::from_matrix(m);
    ktm::fquat q2 = ktm::fquat::angle_axis(1.0f, ktm::fvec3(1.0f, 0.0f, 0.0f));
    ktm::fquat q3 = ktm::fquat::angle_axis(2.0f, ktm::fvec3(0.0f, 1.0f, 0.0f));
    ktm::fvec3 v1(1.0f, -1.0f, 1.0f);
    TEST_EQUAL_MATRIX(q1.matrix4x4(), m, 4);
    TEST_EQUAL(q1.matrix3x3() * v1, q1 * v1);
    TEST_EQUAL(q2 * q3 * v1, (q2 * q3).matrix3x3() * v1);
    TEST_EQUAL(q3 * v1, (q3.matrix4x4() * ktm::fvec4(v1, 1.0f)).xyz());

    ktm::fquat q4 = ktm::fquat::angle_axis(ktm::half_pi<float>, ktm::fvec3(1.0f, 0.0f, 0.0f));
    ktm::fquat q5 = ktm::fquat::angle_axis(ktm::pi<float>, ktm::fvec3(1.0f, 0.0f, 0.0f));
    TEST_EQUAL(ktm::dot(q4, q5), std::cos(ktm::half_pi<float> * 0.5f));

    for (float t = 0.0f; t <= 1.0f; t += 0.05f)
    {
        ktm::fquat lerp_q = ktm::lerp(q4, q5, t);
        TEST_EQUAL(*lerp_q, ktm::lerp(*q4, *q5, t));

        ktm::fquat slerp_q = ktm::slerp(q4, q5, t);
        TEST_EQUAL(slerp_q * v1, slerp_q.matrix3x3() * v1);

        ktm::fquat slerp_longest_q = ktm::slerp_longest(q4, q5, t);
        TEST_EQUAL(slerp_longest_q * v1, slerp_longest_q.matrix3x3() * v1);
    }

    return 0;
}