//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main()
{
    TEST_EQUAL_COMPLEX(ktm::fcomp(1.0f, 2.0f) + ktm::fcomp(2.0f, -1.0f), ktm::fcomp(3.0f, 1.0f));
    TEST_EQUAL_COMPLEX(ktm::fcomp(1.0f, 2.0f) - ktm::fcomp(2.0f, -1.0f), ktm::fcomp(-1.0f, 3.0f));
    TEST_EQUAL_COMPLEX(ktm::fcomp(1.0f, 2.0f) * 2.0f, ktm::fcomp(2.0f, 4.0f));
    TEST_EQUAL_COMPLEX(-ktm::fcomp(1.0f, 2.0f), ktm::fcomp(-1.0f, -2.0f));

    TEST_EQUAL_COMPLEX(ktm::conjugate(ktm::fcomp(3.0f, 2.0f)), ktm::fcomp(-3.0f, 2.0f));
    TEST_EQUAL_COMPLEX(ktm::inverse(ktm::fcomp(1.0f)) * ktm::fcomp(1.0f), ktm::fcomp::identity());
    TEST_EQUAL_COMPLEX(ktm::fcomp(1.5f) * ktm::inverse(ktm::fcomp(1.5f)), ktm::fcomp::identity());
    TEST_EQUAL(ktm::sqrt(ktm::dot(ktm::fcomp(2.7f), ktm::fcomp(2.7f))), ktm::length(ktm::fcomp(2.7f)));
    TEST_EQUAL(ktm::length(ktm::normalize(ktm::fcomp(2.7f, 1.3f))), 1.0f);
    TEST_EQUAL_COMPLEX(ktm::normalize(ktm::fcomp()), ktm::fcomp(0.0f, 1.0f));
    TEST_EQUAL_COMPLEX(ktm::exp(ktm::fcomp(2.0f, 1.0f)), ktm::fcomp(2.47172667f, -1.13120438f));
    TEST_EQUAL_COMPLEX(ktm::log(ktm::fcomp(3.0f, 1.0f)), ktm::fcomp(1.249045772f, 1.151292546f));
    TEST_EQUAL_COMPLEX(ktm::log(ktm::exp(ktm::fcomp(ktm::half_pi<float>, 5.0f))), ktm::fcomp(ktm::half_pi<float>, 5.0f));

    ktm::fmat3x3 m = ktm::rotate2d(1.0f);
    ktm::fcomp c1 = ktm::fcomp::from_matrix(m);
    ktm::fcomp c2 = ktm::fcomp::from_angle(1.0f);
    ktm::fvec2 v1(1.0f, 1.0f);
    TEST_EQUAL_COMPLEX(c1, c2);
    TEST_EQUAL(c2 * v1, c2.matrix2x2() * v1);

    ktm::fcomp c3 = ktm::fcomp::from_angle(ktm::half_pi<float>);
    ktm::fcomp c4 = ktm::fcomp::from_angle(ktm::pi<float>);
    TEST_EQUAL(ktm::dot(c3, c4), std::cos(ktm::half_pi<float>));

    for (float t = 0.0f; t <= 1.0f; t += 0.05f)
    {
        ktm::fcomp lerp_c = ktm::lerp(c2, c3, t);
        TEST_EQUAL(*lerp_c, ktm::lerp(*c2, *c3, t));

        ktm::fcomp slerp_c = ktm::slerp(c2, c3, t);
        TEST_EQUAL(slerp_c * v1, slerp_c.matrix2x2() * v1);

        ktm::fcomp slerp_longest_c = ktm::slerp_longest(c2, c3, t);
        TEST_EQUAL(slerp_longest_c * v1, slerp_longest_c.matrix2x2() * v1);
    }

    return 0;
}