//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main(int argc, char* argv[])
{
    TEST_EQUAL(ktm::length(ktm::fvec2(3.0f, 4.0f)), 5.0f);
    TEST_EQUAL(ktm::length(ktm::fvec3(2.0f, 2.0f, 1.0f)), 3.0f);
    TEST_EQUAL(ktm::length(ktm::fvec4(2.0f, 2.0f, 2.0f, 2.0f)), 4.0f);
    TEST_EQUAL(ktm::length(ktm::fvec2(5.0f, 12.0f)), 13.0f);
    TEST_EQUAL(ktm::length(ktm::fvec3(3.0f, 4.0f, 5.0f)), 7.071067811865475f);
    TEST_EQUAL(ktm::length(ktm::fvec4(1.0f, 2.0f, 2.0f, 1.0f)), 3.1622776601683795f);

    TEST_EQUAL(ktm::distance(ktm::fvec2(0.0f, 0.0f), ktm::fvec2(3.0f, 4.0f)), 5.0f);
    TEST_EQUAL(ktm::distance(ktm::fvec2(-1.0f, -1.0f), ktm::fvec2(2.0f, 3.0f)), 5.0f);
    TEST_EQUAL(ktm::distance(ktm::fvec2(1.0f, 1.0f), ktm::fvec2(4.0f, 5.0f)), 5.0f);
    TEST_EQUAL(ktm::distance(ktm::fvec2(-2.0f, -2.0f), ktm::fvec2(1.0f, 2.0f)), 5.0f);
    TEST_EQUAL(ktm::distance(ktm::fvec2(2.0f, 2.0f), ktm::fvec2(5.0f, 6.0f)), 5.0f);
    TEST_EQUAL(ktm::distance(ktm::fvec2(-3.0f, -3.0f), ktm::fvec2(0.0f, 1.0f)), 5.0f);

    TEST_EQUAL(ktm::dot(ktm::fvec2(1.0f, 0.0f), ktm::fvec2(0.0f, 1.0f)), 0.0f);
    TEST_EQUAL(ktm::dot(ktm::fvec2(2.0f, 1.0f), ktm::fvec2(-1.0f, 2.0f)), 0.0f);
    TEST_EQUAL(ktm::dot(ktm::fvec2(3.0f, -1.0f), ktm::fvec2(1.0f, 3.0f)), 0.0f);
    TEST_EQUAL(ktm::dot(ktm::fvec2(1.0f, 2.0f), ktm::fvec2(-2.0f, 1.0f)), 0.0f);
    TEST_EQUAL(ktm::dot(ktm::fvec2(2.0f, 3.0f), ktm::fvec2(-3.0f, 2.0f)), 0.0f);
    TEST_EQUAL(ktm::dot(ktm::fvec2(3.0f, 4.0f), ktm::fvec2(-4.0f, 3.0f)), 0.0f);

    TEST_EQUAL(ktm::normalize(ktm::fvec2(3.0f, 4.0f)), ktm::fvec2(0.6f, 0.8f));
    TEST_EQUAL(ktm::normalize(ktm::fvec2(5.0f, 0.0f)), ktm::fvec2(1.0f, 0.0f));
    TEST_EQUAL(ktm::normalize(ktm::fvec2(0.0f, 5.0f)), ktm::fvec2(0.0f, 1.0f));
    TEST_EQUAL(ktm::normalize(ktm::fvec2(1.0f, 1.0f)), ktm::fvec2(0.7071067811865475f, 0.7071067811865475f));
    TEST_EQUAL(ktm::normalize(ktm::fvec2(2.0f, 2.0f)), ktm::fvec2(0.7071067811865475f, 0.7071067811865475f));
    TEST_EQUAL(ktm::normalize(ktm::fvec2(3.0f, 3.0f)), ktm::fvec2(0.7071067811865475f, 0.7071067811865475f));

    TEST_EQUAL(ktm::cross(ktm::fvec3(1.0f, 0.0f, 0.0f), ktm::fvec3(0.0f, 1.0f, 0.0f)), ktm::fvec3(0.0f, 0.0f, 1.0f));
    TEST_EQUAL(ktm::cross(ktm::fvec3(0.0f, 1.0f, 0.0f), ktm::fvec3(0.0f, 0.0f, 1.0f)), ktm::fvec3(1.0f, 0.0f, 0.0f));
    TEST_EQUAL(ktm::cross(ktm::fvec3(1.0f, 1.0f, 0.0f), ktm::fvec3(0.0f, 1.0f, 1.0f)), ktm::fvec3(1.0f, -1.0f, 1.0f));
    TEST_EQUAL(ktm::cross(ktm::fvec3(2.0f, 0.0f, 0.0f), ktm::fvec3(0.0f, 2.0f, 0.0f)), ktm::fvec3(0.0f, 0.0f, 4.0f));
    TEST_EQUAL(ktm::cross(ktm::fvec3(0.0f, 2.0f, 0.0f), ktm::fvec3(0.0f, 0.0f, 2.0f)), ktm::fvec3(4.0f, 0.0f, 0.0f));
    TEST_EQUAL(ktm::cross(ktm::fvec3(2.0f, 2.0f, 0.0f), ktm::fvec3(0.0f, 2.0f, 2.0f)), ktm::fvec3(4.0f, -4.0f, 4.0f));

    TEST_EQUAL(ktm::reflect(ktm::fvec3(1.0f, -1.0f, 0.0f), ktm::fvec3(0.0f, 1.0f, 0.0f)), ktm::fvec3(1.0f, 1.0f, 0.0f));
    TEST_EQUAL(ktm::reflect(ktm::fvec3(1.0f, 0.0f, -1.0f), ktm::fvec3(0.0f, 0.0f, 1.0f)), ktm::fvec3(1.0f, 0.0f, 1.0f));
    TEST_EQUAL(ktm::reflect(ktm::fvec3(-1.0f, 1.0f, 0.0f), ktm::fvec3(1.0f, 0.0f, 0.0f)), ktm::fvec3(1.0f, 1.0f, 0.0f));
    TEST_EQUAL(ktm::reflect(ktm::fvec3(2.0f, -2.0f, 0.0f), ktm::fvec3(0.0f, 1.0f, 0.0f)), ktm::fvec3(2.0f, 2.0f, 0.0f));
    TEST_EQUAL(ktm::reflect(ktm::fvec3(2.0f, 0.0f, -2.0f), ktm::fvec3(0.0f, 0.0f, 1.0f)), ktm::fvec3(2.0f, 0.0f, 2.0f));
    TEST_EQUAL(ktm::reflect(ktm::fvec3(-2.0f, 2.0f, 0.0f), ktm::fvec3(1.0f, 0.0f, 0.0f)), ktm::fvec3(2.0f, 2.0f, 0.0f));

    TEST_EQUAL(ktm::refract(ktm::fvec3(1.0f, -1.0f, 0.0f), ktm::fvec3(0.0f, 1.0f, 0.0f), 0.5f),
               ktm::fvec3(0.5f, -1.0f, 0.0f));
    TEST_EQUAL(ktm::refract(ktm::fvec3(1.0f, 0.0f, -1.0f), ktm::fvec3(0.0f, 0.0f, 1.0f), 0.6f),
               ktm::fvec3(0.6f, 0.0f, -1.0f));
    TEST_EQUAL(ktm::refract(ktm::fvec3(-1.0f, 1.0f, 0.0f), ktm::fvec3(1.0f, 0.0f, 0.0f), 0.7f),
               ktm::fvec3(-1.0f, 0.7f, 0.0f));
    TEST_EQUAL(ktm::refract(ktm::fvec3(2.0f, -2.0f, 0.0f), ktm::fvec3(0.0f, 1.0f, 0.0f), 0.8f),
               ktm::fvec3(1.6f, -1.70880079f, 0.0f));
    TEST_EQUAL(ktm::refract(ktm::fvec3(2.0f, 0.0f, -2.0f), ktm::fvec3(0.0f, 0.0f, 1.0f), 0.9f),
               ktm::fvec3(1.8f, 0.0f, -1.85202587f));
    TEST_EQUAL(ktm::refract(ktm::fvec3(-2.0f, 2.0f, 0.0f), ktm::fvec3(1.0f, 0.0f, 0.0f), 0.75f),
               ktm::fvec3(-1.63935959f, 1.5f, 0.0f));

    TEST_EQUAL_FAST(ktm::fast::length(ktm::fvec2(3.0f, 4.0f)), 5.0f);
    TEST_EQUAL_FAST(ktm::fast::length(ktm::fvec2(5.0f, 12.0f)), 13.0f);
    TEST_EQUAL_FAST(ktm::fast::length(ktm::fvec2(6.0f, 8.0f)), 10.0f);
    TEST_EQUAL_FAST(ktm::fast::length(ktm::fvec2(8.0f, 15.0f)), 17.0f);
    TEST_EQUAL_FAST(ktm::fast::length(ktm::fvec2(9.0f, 12.0f)), 15.0f);
    TEST_EQUAL_FAST(ktm::fast::length(ktm::fvec2(12.0f, 16.0f)), 20.0f);

    TEST_EQUAL_FAST(ktm::fast::distance(ktm::fvec2(0.0f, 0.0f), ktm::fvec2(3.0f, 4.0f)), 5.0f);
    TEST_EQUAL_FAST(ktm::fast::distance(ktm::fvec2(-1.0f, -1.0f), ktm::fvec2(2.0f, 3.0f)), 5.0f);
    TEST_EQUAL_FAST(ktm::fast::distance(ktm::fvec2(1.0f, 1.0f), ktm::fvec2(4.0f, 5.0f)), 5.0f);
    TEST_EQUAL_FAST(ktm::fast::distance(ktm::fvec2(-2.0f, -2.0f), ktm::fvec2(1.0f, 2.0f)), 5.0f);
    TEST_EQUAL_FAST(ktm::fast::distance(ktm::fvec2(2.0f, 2.0f), ktm::fvec2(5.0f, 6.0f)), 5.0f);
    TEST_EQUAL_FAST(ktm::fast::distance(ktm::fvec2(-3.0f, -3.0f), ktm::fvec2(0.0f, 1.0f)), 5.0f);

    TEST_EQUAL_FAST(ktm::fast::normalize(ktm::fvec2(3.0f, 4.0f)), ktm::fvec2(0.6f, 0.8f));
    TEST_EQUAL_FAST(ktm::fast::normalize(ktm::fvec2(5.0f, 0.0f)), ktm::fvec2(1.0f, 0.0f));
    TEST_EQUAL_FAST(ktm::fast::normalize(ktm::fvec2(0.0f, 5.0f)), ktm::fvec2(0.0f, 1.0f));
    TEST_EQUAL_FAST(ktm::fast::normalize(ktm::fvec2(1.0f, 1.0f)), ktm::fvec2(0.7071067811865475f, 0.7071067811865475f));
    TEST_EQUAL_FAST(ktm::fast::normalize(ktm::fvec2(2.0f, 2.0f)), ktm::fvec2(0.7071067811865475f, 0.7071067811865475f));
    TEST_EQUAL_FAST(ktm::fast::normalize(ktm::fvec2(3.0f, 3.0f)), ktm::fvec2(0.7071067811865475f, 0.7071067811865475f));

    TEST_EQUAL_FAST(ktm::fast::project(ktm::fvec3(1.0f, 0.0f, 0.0f), ktm::fvec3(2.0f, 0.0f, 0.0f)),
                    ktm::fvec3(1.0f, 0.0f, 0.0f));
    TEST_EQUAL_FAST(ktm::fast::project(ktm::fvec3(0.0f, 1.0f, 0.0f), ktm::fvec3(0.0f, 2.0f, 0.0f)),
                    ktm::fvec3(0.0f, 1.0f, 0.0f));
    TEST_EQUAL_FAST(ktm::fast::project(ktm::fvec3(0.0f, 0.0f, 1.0f), ktm::fvec3(0.0f, 0.0f, 2.0f)),
                    ktm::fvec3(0.0f, 0.0f, 1.0f));
    TEST_EQUAL_FAST(ktm::fast::project(ktm::fvec3(1.0f, 1.0f, 0.0f), ktm::fvec3(2.0f, 0.0f, 0.0f)),
                    ktm::fvec3(1.0f, 0.0f, 0.0f));
    TEST_EQUAL_FAST(ktm::fast::project(ktm::fvec3(0.0f, 1.0f, 1.0f), ktm::fvec3(0.0f, 2.0f, 0.0f)),
                    ktm::fvec3(0.0f, 1.0f, 0.0f));
    TEST_EQUAL_FAST(ktm::fast::project(ktm::fvec3(1.0f, 0.0f, 1.0f), ktm::fvec3(0.0f, 0.0f, 2.0f)),
                    ktm::fvec3(0.0f, 0.0f, 1.0f));

    return 0;
}