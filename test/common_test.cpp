//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "ktm_test.h"

int main(int argc, char* argv[])
{
    TEST_EQUAL(ktm::abs(-3.14f), 3.14f);
    TEST_EQUAL(ktm::min(2.5f, 3.5f), 2.5f);
    TEST_EQUAL(ktm::max(2.5f, 3.5f), 3.5f);
    TEST_EQUAL(ktm::clamp(0.0f, 1.0f, 2.0f), 1.0f);
    TEST_EQUAL(ktm::floor(3.7f), 3.0f);
    TEST_EQUAL(ktm::ceil(3.2f), 4.0f);
    TEST_EQUAL(ktm::round(3.5f), 4.0f);
    TEST_EQUAL(ktm::fract(3.7f), 0.7f);
    TEST_EQUAL(ktm::mod(5.0f, 3.0f), 2.0f);
    TEST_EQUAL(ktm::lerp(0.0f, 1.0f, 0.5f), 0.5f);
    TEST_EQUAL(ktm::mix(0.0f, 1.0f, 0.5f), 0.5f);
    TEST_EQUAL(ktm::step(0.5f, 0.7f), 1.0f);
    TEST_EQUAL(ktm::smoothstep(0.0f, 1.0f, 0.5f), 0.5f);
    TEST_EQUAL(ktm::pow<2>(2.0f), 4.0f);
    TEST_EQUAL(ktm::pow2(2.0f), 4.0f);
    TEST_EQUAL(ktm::pow5(2.0f), 32.0f);
    TEST_EQUAL(ktm::sqrt(4.0f), 2.0f);
    TEST_EQUAL(ktm::rsqrt(4.0f), 0.5f);
    TEST_EQUAL(ktm::recip(2.0f), 0.5f);
    TEST_EQUAL(ktm::cbrt(8.0f), 2.0f);
    TEST_EQUAL(ktm::pow(2.0f, 3.0f), 8.0f);
    TEST_EQUAL(ktm::exp(1.0f), 2.718282f);
    TEST_EQUAL(ktm::exp2(3.0f), 8.0f);
    TEST_EQUAL(ktm::expm1(1.0f), 1.718282f);
    TEST_EQUAL(ktm::log(2.718282f), 1.0f);
    TEST_EQUAL(ktm::log10(100.0f), 2.0f);
    TEST_EQUAL(ktm::log2(8.0f), 3.0f);
    TEST_EQUAL(ktm::log1p(1.718282f), 1.0f);
    TEST_EQUAL_FAST(ktm::fast::sqrt(4.0f), 2.0f);
    TEST_EQUAL_FAST(ktm::fast::rsqrt(4.0f), 0.5f);
    TEST_EQUAL_FAST(ktm::fast::recip(2.0f), 0.5f);
    TEST_EQUAL(ktm::radians(30.0f), ktm::pi<float> / 6.0f);
    TEST_EQUAL(ktm::radians(45.0f), ktm::pi<float> / 4.0f);
    TEST_EQUAL(ktm::radians(60.0f), ktm::pi<float> / 3.0f);
    TEST_EQUAL(ktm::degrees(ktm::pi<float> / 3.0f), 60.0f);
    TEST_EQUAL(ktm::sin(ktm::pi<float> / 6.0f), 0.5f);
    TEST_EQUAL(ktm::sin(ktm::pi<float> / 3.0f), 0.866025f);
    TEST_EQUAL(ktm::cos(ktm::pi<float> / 3.0f), 0.5f);
    TEST_EQUAL(ktm::cos(ktm::pi<float> / 6.0f), 0.866025f);
    TEST_EQUAL(ktm::tan(ktm::pi<float> / 6.0f), 0.577350f);
    TEST_EQUAL(ktm::tan(ktm::pi<float> / 3.0f), 1.732051f);
    TEST_EQUAL(ktm::asin(0.5f), ktm::pi<float> / 6.0f);
    TEST_EQUAL(ktm::asin(0.866025f), ktm::pi<float> / 3.0f);
    TEST_EQUAL(ktm::acos(0.5f), ktm::pi<float> / 3.0f);
    TEST_EQUAL(ktm::acos(0.866025f), ktm::pi<float> / 6.0f);
    TEST_EQUAL(ktm::atan(0.577350f), ktm::pi<float> / 6.0f);
    TEST_EQUAL(ktm::atan(1.732051f), ktm::pi<float> / 3.0f);
    TEST_EQUAL(ktm::atan2(0.5f, 0.866025f), ktm::pi<float> / 6.0f);
    TEST_EQUAL(ktm::atan2(0.866025f, 0.5f), ktm::pi<float> / 3.0f);
    TEST_EQUAL(ktm::sinc(ktm::pi<float> / 4.0f), 0.900316f);
    TEST_EQUAL(ktm::sinh(0.5f), 0.521095f);
    TEST_EQUAL(ktm::sinh(1.2f), 1.509461f);
    TEST_EQUAL(ktm::cosh(0.5f), 1.127626f);
    TEST_EQUAL(ktm::cosh(1.2f), 1.810656f);
    TEST_EQUAL(ktm::tanh(0.5f), 0.462117f);
    TEST_EQUAL(ktm::tanh(1.2f), 0.833655f);
    TEST_EQUAL(ktm::asinh(1.5f), 1.194763f);
    TEST_EQUAL(ktm::asinh(2.5f), 1.647231f);
    TEST_EQUAL(ktm::acosh(1.5f), 0.962424f);
    TEST_EQUAL(ktm::acosh(2.5f), 1.566799f);
    TEST_EQUAL(ktm::atanh(0.5f), 0.549306f);
    TEST_EQUAL(ktm::atanh(0.8f), 1.098612f);
    TEST_EQUAL(ktm::fvec2(1.0f, 2.0f) + ktm::fvec2(3.0f, 4.0f), ktm::fvec2(4.0f, 6.0f));
    TEST_EQUAL(ktm::fvec3(1.0f, 2.0f, 3.0f) + ktm::fvec3(4.0f, 5.0f, 6.0f), ktm::fvec3(5.0f, 7.0f, 9.0f));
    TEST_EQUAL(ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f) + ktm::fvec4(5.0f, 6.0f, 7.0f, 8.0f),
               ktm::fvec4(6.0f, 8.0f, 10.0f, 12.0f));

    TEST_EQUAL(ktm::fvec2(4.0f, 6.0f) - ktm::fvec2(1.0f, 2.0f), ktm::fvec2(3.0f, 4.0f));
    TEST_EQUAL(ktm::fvec3(5.0f, 7.0f, 9.0f) - ktm::fvec3(1.0f, 2.0f, 3.0f), ktm::fvec3(4.0f, 5.0f, 6.0f));
    TEST_EQUAL(ktm::fvec4(6.0f, 8.0f, 10.0f, 12.0f) - ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f),
               ktm::fvec4(5.0f, 6.0f, 7.0f, 8.0f));
    TEST_EQUAL(ktm::fvec2(2.0f, 3.0f) * ktm::fvec2(3.0f, 4.0f), ktm::fvec2(6.0f, 12.0f));
    TEST_EQUAL(ktm::fvec3(2.0f, 3.0f, 4.0f) * ktm::fvec3(3.0f, 4.0f, 5.0f), ktm::fvec3(6.0f, 12.0f, 20.0f));
    TEST_EQUAL(ktm::fvec4(2.0f, 3.0f, 4.0f, 5.0f) * ktm::fvec4(3.0f, 4.0f, 5.0f, 6.0f),
               ktm::fvec4(6.0f, 12.0f, 20.0f, 30.0f));
    TEST_EQUAL(ktm::fvec2(6.0f, 12.0f) / ktm::fvec2(2.0f, 3.0f), ktm::fvec2(3.0f, 4.0f));
    TEST_EQUAL(ktm::fvec3(6.0f, 12.0f, 20.0f) / ktm::fvec3(2.0f, 3.0f, 4.0f), ktm::fvec3(3.0f, 4.0f, 5.0f));
    TEST_EQUAL(ktm::fvec4(6.0f, 12.0f, 20.0f, 30.0f) / ktm::fvec4(2.0f, 3.0f, 4.0f, 5.0f),
               ktm::fvec4(3.0f, 4.0f, 5.0f, 6.0f));
    TEST_EQUAL(ktm_op_madd(ktm::fvec2(1.0f, 2.0f), ktm::fvec2(2.0f, 3.0f), ktm::fvec2(3.0f, 4.0f)),
               ktm::fvec2(7.0f, 14.0f));
    TEST_EQUAL(ktm_op_madd(ktm::fvec3(1.0f, 2.0f, 3.0f), ktm::fvec3(2.0f, 3.0f, 4.0f), ktm::fvec3(3.0f, 4.0f, 5.0f)),
               ktm::fvec3(7.0f, 14.0f, 23.0f));
    TEST_EQUAL(ktm_op_madd(ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f), ktm::fvec4(2.0f, 3.0f, 4.0f, 5.0f),
                           ktm::fvec4(3.0f, 4.0f, 5.0f, 6.0f)),
               ktm::fvec4(7.0f, 14.0f, 23.0f, 34.0f));

    TEST_EQUAL(ktm::reduce_add(ktm::fvec2(1.0f, 2.0f)), 3.0f);
    TEST_EQUAL(ktm::reduce_add(ktm::fvec3(1.0f, 2.0f, 3.0f)), 6.0f);
    TEST_EQUAL(ktm::reduce_add(ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f)), 10.0f);
    TEST_EQUAL(ktm::reduce_max(ktm::fvec2(1.0f, 2.0f)), 2.0f);
    TEST_EQUAL(ktm::reduce_max(ktm::fvec3(1.0f, 3.0f, 2.0f)), 3.0f);
    TEST_EQUAL(ktm::reduce_max(ktm::fvec4(1.0f, 4.0f, 2.0f, 3.0f)), 4.0f);
    TEST_EQUAL(ktm::reduce_min(ktm::fvec2(1.0f, 2.0f)), 1.0f);
    TEST_EQUAL(ktm::reduce_min(ktm::fvec3(2.0f, 1.0f, 3.0f)), 1.0f);
    TEST_EQUAL(ktm::reduce_min(ktm::fvec4(4.0f, 2.0f, 1.0f, 3.0f)), 1.0f);
    TEST_EQUAL(ktm::abs(ktm::fvec2(-3.14f, 2.5f)), ktm::fvec2(3.14f, 2.5f));
    TEST_EQUAL(ktm::abs(ktm::fvec3(-1.0f, -2.0f, 3.0f)), ktm::fvec3(1.0f, 2.0f, 3.0f));
    TEST_EQUAL(ktm::abs(ktm::fvec4(-1.0f, -2.0f, 3.0f, -4.0f)), ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f));
    TEST_EQUAL(ktm::min(ktm::fvec2(1.0f, 4.0f), ktm::fvec2(2.0f, 3.0f)), ktm::fvec2(1.0f, 3.0f));
    TEST_EQUAL(ktm::max(ktm::fvec2(1.0f, 4.0f), ktm::fvec2(2.0f, 3.0f)), ktm::fvec2(2.0f, 4.0f));
    TEST_EQUAL(ktm::clamp(ktm::fvec3(0.5f, -1.0f, 2.5f), ktm::fvec3(0.0f), ktm::fvec3(2.0f)),
               ktm::fvec3(0.5f, 0.0f, 2.0f));
    TEST_EQUAL(ktm::floor(ktm::fvec2(1.7f, 2.3f)), ktm::fvec2(1.0f, 2.0f));
    TEST_EQUAL(ktm::ceil(ktm::fvec2(1.7f, 2.3f)), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL(ktm::round(ktm::fvec2(1.7f, 2.3f)), ktm::fvec2(2.0f, 2.0f));
    TEST_EQUAL(ktm::fract(ktm::fvec2(1.7f, 2.3f)), ktm::fvec2(0.7f, 0.3f));
    TEST_EQUAL(ktm::mod(ktm::fvec2(5.0f, 7.0f), ktm::fvec2(3.0f, 4.0f)), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL(ktm::lerp(ktm::fvec3(0.0f), ktm::fvec3(1.0f), 0.5f), ktm::fvec3(0.5f));
    TEST_EQUAL(ktm::mix(ktm::fvec3(0.0f), ktm::fvec3(1.0f), ktm::fvec3(0.5f)), ktm::fvec3(0.5f));
    TEST_EQUAL(ktm::step(ktm::fvec2(0.5f), ktm::fvec2(0.7f, 0.3f)), ktm::fvec2(1.0f, 0.0f));
    TEST_EQUAL(ktm::step(ktm::fvec2(0.0f), ktm::fvec2(1.0f, -1.0f)), ktm::fvec2(1.0f, 0.0f));
    TEST_EQUAL(ktm::step(ktm::fvec2(0.5f), ktm::fvec2(0.5f, 0.49f)), ktm::fvec2(1.0f, 0.0f));
    TEST_EQUAL(ktm::sqrt(ktm::fvec2(4.0f, 9.0f)), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL(ktm::rsqrt(ktm::fvec2(4.0f, 9.0f)), ktm::fvec2(0.5f, 0.333333f));
    TEST_EQUAL(ktm::pow(ktm::fvec2(2.0f), ktm::fvec2(3.0f)), ktm::fvec2(8.0f));
    TEST_EQUAL(ktm::exp(ktm::fvec2(0.0f, 1.0f)), ktm::fvec2(1.0f, 2.718282f));
    TEST_EQUAL(ktm::log(ktm::fvec2(1.0f, 2.718282f)), ktm::fvec2(0.0f, 1.0f));
    TEST_EQUAL_FAST(ktm::fast::sqrt(ktm::fvec2(4.0f, 9.0f)), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL_FAST(ktm::fast::rsqrt(ktm::fvec2(4.0f, 9.0f)), ktm::fvec2(0.5f, 0.333333f));
    TEST_EQUAL_FAST(ktm::fast::recip(ktm::fvec2(2.0f, 4.0f)), ktm::fvec2(0.5f, 0.25f));
    TEST_EQUAL(ktm::sin(ktm::fvec2(ktm::pi<float> / 6.0f, ktm::pi<float> / 3.0f)), ktm::fvec2(0.5f, 0.866025f));
    TEST_EQUAL(ktm::cos(ktm::fvec2(ktm::pi<float> / 3.0f, ktm::pi<float> / 6.0f)), ktm::fvec2(0.5f, 0.866025f));
    TEST_EQUAL(ktm::tan(ktm::fvec2(ktm::pi<float> / 6.0f, ktm::pi<float> / 3.0f)), ktm::fvec2(0.577350f, 1.732051f));
    TEST_EQUAL(ktm::sinh(ktm::fvec2(0.5f, 1.2f)), ktm::fvec2(0.521095f, 1.509461f));
    TEST_EQUAL(ktm::cosh(ktm::fvec2(0.5f, 1.2f)), ktm::fvec2(1.127626f, 1.810656f));
    TEST_EQUAL(ktm::tanh(ktm::fvec2(0.5f, 1.2f)), ktm::fvec2(0.462117f, 0.833655f));

    return 0;
}
