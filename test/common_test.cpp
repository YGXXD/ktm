//  MIT License
//
//  Copyright (c) 2023-2026 有个小小杜
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

    TEST_EQUAL(ktm::fvec1(1.0f) + ktm::fvec1(3.0f), ktm::fvec1(4.0f));
    TEST_EQUAL(ktm::fvec2(1.0f, 2.0f) + ktm::fvec2(3.0f, 4.0f), ktm::fvec2(4.0f, 6.0f));
    TEST_EQUAL(ktm::fvec3(1.0f, 2.0f, 3.0f) + ktm::fvec3(4.0f, 5.0f, 6.0f), ktm::fvec3(5.0f, 7.0f, 9.0f));
    TEST_EQUAL(ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f) + ktm::fvec4(5.0f, 6.0f, 7.0f, 8.0f),
               ktm::fvec4(6.0f, 8.0f, 10.0f, 12.0f));
    TEST_EQUAL(ktm::fvec1(4.0f) - ktm::fvec1(1.0f), ktm::fvec1(3.0f));
    TEST_EQUAL(ktm::fvec2(4.0f, 6.0f) - ktm::fvec2(1.0f, 2.0f), ktm::fvec2(3.0f, 4.0f));
    TEST_EQUAL(ktm::fvec3(5.0f, 7.0f, 9.0f) - ktm::fvec3(1.0f, 2.0f, 3.0f), ktm::fvec3(4.0f, 5.0f, 6.0f));
    TEST_EQUAL(ktm::fvec4(6.0f, 8.0f, 10.0f, 12.0f) - ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f),
               ktm::fvec4(5.0f, 6.0f, 7.0f, 8.0f));
    TEST_EQUAL(ktm::fvec1(2.0f) * ktm::fvec1(3.0f), ktm::fvec1(6.0f));
    TEST_EQUAL(ktm::fvec2(2.0f, 3.0f) * ktm::fvec2(3.0f, 4.0f), ktm::fvec2(6.0f, 12.0f));
    TEST_EQUAL(ktm::fvec3(2.0f, 3.0f, 4.0f) * ktm::fvec3(3.0f, 4.0f, 5.0f), ktm::fvec3(6.0f, 12.0f, 20.0f));
    TEST_EQUAL(ktm::fvec4(2.0f, 3.0f, 4.0f, 5.0f) * ktm::fvec4(3.0f, 4.0f, 5.0f, 6.0f),
               ktm::fvec4(6.0f, 12.0f, 20.0f, 30.0f));
    TEST_EQUAL(ktm::fvec1(6.0f) / ktm::fvec1(2.0f), ktm::fvec1(3.0f));
    TEST_EQUAL(ktm::fvec2(6.0f, 12.0f) / ktm::fvec2(2.0f, 3.0f), ktm::fvec2(3.0f, 4.0f));
    TEST_EQUAL(ktm::fvec3(6.0f, 12.0f, 20.0f) / ktm::fvec3(2.0f, 3.0f, 4.0f), ktm::fvec3(3.0f, 4.0f, 5.0f));
    TEST_EQUAL(ktm::fvec4(6.0f, 12.0f, 20.0f, 30.0f) / ktm::fvec4(2.0f, 3.0f, 4.0f, 5.0f),
               ktm::fvec4(3.0f, 4.0f, 5.0f, 6.0f));
    TEST_EQUAL(ktm_op_madd(ktm::fvec1(1.0f), ktm::fvec1(2.0f), ktm::fvec1(3.0f)), ktm::fvec1(7.0f));
    TEST_EQUAL(ktm_op_madd(ktm::fvec2(1.0f, 2.0f), ktm::fvec2(2.0f, 3.0f), ktm::fvec2(3.0f, 4.0f)),
               ktm::fvec2(7.0f, 14.0f));
    TEST_EQUAL(ktm_op_madd(ktm::fvec3(1.0f, 2.0f, 3.0f), ktm::fvec3(2.0f, 3.0f, 4.0f), ktm::fvec3(3.0f, 4.0f, 5.0f)),
               ktm::fvec3(7.0f, 14.0f, 23.0f));
    TEST_EQUAL(ktm_op_madd(ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f), ktm::fvec4(2.0f, 3.0f, 4.0f, 5.0f),
                           ktm::fvec4(3.0f, 4.0f, 5.0f, 6.0f)),
               ktm::fvec4(7.0f, 14.0f, 23.0f, 34.0f));

    TEST_EQUAL(ktm::reduce_add(ktm::fvec1(1.0f)), 1.0f);
    TEST_EQUAL(ktm::reduce_add(ktm::fvec2(1.0f, 2.0f)), 3.0f);
    TEST_EQUAL(ktm::reduce_add(ktm::fvec3(1.0f, 2.0f, 3.0f)), 6.0f);
    TEST_EQUAL(ktm::reduce_add(ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f)), 10.0f);
    TEST_EQUAL(ktm::reduce_max(ktm::fvec1(2.0f)), 2.0f);
    TEST_EQUAL(ktm::reduce_max(ktm::fvec2(1.0f, 2.0f)), 2.0f);
    TEST_EQUAL(ktm::reduce_max(ktm::fvec3(1.0f, 3.0f, 2.0f)), 3.0f);
    TEST_EQUAL(ktm::reduce_max(ktm::fvec4(1.0f, 4.0f, 2.0f, 3.0f)), 4.0f);
    TEST_EQUAL(ktm::reduce_min(ktm::fvec1(2.0f)), 2.0f);
    TEST_EQUAL(ktm::reduce_min(ktm::fvec2(1.0f, 2.0f)), 1.0f);
    TEST_EQUAL(ktm::reduce_min(ktm::fvec3(2.0f, 1.0f, 3.0f)), 1.0f);
    TEST_EQUAL(ktm::reduce_min(ktm::fvec4(4.0f, 2.0f, 1.0f, 3.0f)), 1.0f);
    TEST_EQUAL(ktm::abs(ktm::fvec1(-3.14f)), ktm::fvec1(3.14f));
    TEST_EQUAL(ktm::abs(ktm::fvec2(-3.14f, 2.5f)), ktm::fvec2(3.14f, 2.5f));
    TEST_EQUAL(ktm::abs(ktm::fvec3(-1.0f, -2.0f, 3.0f)), ktm::fvec3(1.0f, 2.0f, 3.0f));
    TEST_EQUAL(ktm::abs(ktm::fvec4(-1.0f, -2.0f, 3.0f, -4.0f)), ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f));
    TEST_EQUAL(ktm::min(ktm::fvec1(1.0f), ktm::fvec1(4.0f)), ktm::fvec1(1.0f));
    TEST_EQUAL(ktm::min(ktm::fvec2(1.0f, 4.0f), ktm::fvec2(2.0f, 3.0f)), ktm::fvec2(1.0f, 3.0f));
    TEST_EQUAL(ktm::min(ktm::fvec3(1.0f, 4.0f, 2.0f), ktm::fvec3(2.0f, 3.0f, 1.0f)), ktm::fvec3(1.0f, 3.0f, 1.0f));
    TEST_EQUAL(ktm::min(ktm::fvec4(1.0f, 4.0f, 2.0f, 5.0f), ktm::fvec4(2.0f, 3.0f, 1.0f, 4.0f)),
               ktm::fvec4(1.0f, 3.0f, 1.0f, 4.0f));
    TEST_EQUAL(ktm::max(ktm::fvec1(1.0f), ktm::fvec1(4.0f)), ktm::fvec1(4.0f));
    TEST_EQUAL(ktm::max(ktm::fvec2(1.0f, 4.0f), ktm::fvec2(2.0f, 3.0f)), ktm::fvec2(2.0f, 4.0f));
    TEST_EQUAL(ktm::max(ktm::fvec3(1.0f, 4.0f, 2.0f), ktm::fvec3(2.0f, 3.0f, 1.0f)), ktm::fvec3(2.0f, 4.0f, 2.0f));
    TEST_EQUAL(ktm::max(ktm::fvec4(1.0f, 4.0f, 2.0f, 5.0f), ktm::fvec4(2.0f, 3.0f, 1.0f, 4.0f)),
               ktm::fvec4(2.0f, 4.0f, 2.0f, 5.0f));
    TEST_EQUAL(ktm::clamp(ktm::fvec1(-1.0f), ktm::fvec1(0.0f), ktm::fvec1(2.0f)), ktm::fvec1(0.0f));
    TEST_EQUAL(ktm::clamp(ktm::fvec2(-1.0f, 2.5f), ktm::fvec2(0.0f), ktm::fvec2(2.0f)), ktm::fvec2(0.0f, 2.0f));
    TEST_EQUAL(ktm::clamp(ktm::fvec3(0.5f, -1.0f, 2.5f), ktm::fvec3(0.0f), ktm::fvec3(2.0f)),
               ktm::fvec3(0.5f, 0.0f, 2.0f));
    TEST_EQUAL(ktm::clamp(ktm::fvec4(0.5f, -1.0f, 2.5f, 3.0f), ktm::fvec4(0.0f), ktm::fvec4(2.0f)),
               ktm::fvec4(0.5f, 0.0f, 2.0f, 2.0f));
    TEST_EQUAL(ktm::floor(ktm::fvec1(1.7f)), ktm::fvec1(1.0f));
    TEST_EQUAL(ktm::floor(ktm::fvec2(1.7f, 2.3f)), ktm::fvec2(1.0f, 2.0f));
    TEST_EQUAL(ktm::floor(ktm::fvec3(1.7f, 2.3f, 3.9f)), ktm::fvec3(1.0f, 2.0f, 3.0f));
    TEST_EQUAL(ktm::floor(ktm::fvec4(1.7f, 2.3f, 3.9f, 4.1f)), ktm::fvec4(1.0f, 2.0f, 3.0f, 4.0f));
    TEST_EQUAL(ktm::ceil(ktm::fvec1(1.7f)), ktm::fvec1(2.0f));
    TEST_EQUAL(ktm::ceil(ktm::fvec2(1.7f, 2.3f)), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL(ktm::ceil(ktm::fvec3(1.7f, 2.3f, 3.9f)), ktm::fvec3(2.0f, 3.0f, 4.0f));
    TEST_EQUAL(ktm::ceil(ktm::fvec4(1.7f, 2.3f, 3.9f, 4.1f)), ktm::fvec4(2.0f, 3.0f, 4.0f, 5.0f));
    TEST_EQUAL(ktm::round(ktm::fvec1(1.7f)), ktm::fvec1(2.0f));
    TEST_EQUAL(ktm::round(ktm::fvec2(1.7f, 2.3f)), ktm::fvec2(2.0f, 2.0f));
    TEST_EQUAL(ktm::round(ktm::fvec3(1.7f, 2.3f, 3.9f)), ktm::fvec3(2.0f, 2.0f, 4.0f));
    TEST_EQUAL(ktm::round(ktm::fvec4(1.7f, 2.3f, 3.9f, 4.1f)), ktm::fvec4(2.0f, 2.0f, 4.0f, 4.0f));
    TEST_EQUAL(ktm::fract(ktm::fvec1(1.7f)), ktm::fvec1(0.7f));
    TEST_EQUAL(ktm::fract(ktm::fvec2(1.7f, 2.3f)), ktm::fvec2(0.7f, 0.3f));
    TEST_EQUAL(ktm::fract(ktm::fvec3(1.7f, 2.3f, 3.9f)), ktm::fvec3(0.7f, 0.3f, 0.9f));
    TEST_EQUAL(ktm::fract(ktm::fvec4(1.7f, 2.3f, 3.9f, 4.1f)), ktm::fvec4(0.7f, 0.3f, 0.9f, 0.1f));
    TEST_EQUAL(ktm::mod(ktm::fvec1(5.0f), ktm::fvec1(3.0f)), ktm::fvec1(2.0f));
    TEST_EQUAL(ktm::mod(ktm::fvec2(5.0f, 7.0f), ktm::fvec2(3.0f, 4.0f)), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL(ktm::mod(ktm::fvec3(5.0f, 7.0f, 9.0f), ktm::fvec3(3.0f, 4.0f, 5.0f)), ktm::fvec3(2.0f, 3.0f, 4.0f));
    TEST_EQUAL(ktm::mod(ktm::fvec4(5.0f, 7.0f, 9.0f, 11.0f), ktm::fvec4(3.0f, 4.0f, 5.0f, 6.0f)),
               ktm::fvec4(2.0f, 3.0f, 4.0f, 5.0f));
    TEST_EQUAL(ktm::lerp(ktm::fvec1(0.0f), ktm::fvec1(1.0f), 0.5f), ktm::fvec1(0.5f));
    TEST_EQUAL(ktm::lerp(ktm::fvec2(0.0f), ktm::fvec2(1.0f), 0.5f), ktm::fvec2(0.5f));
    TEST_EQUAL(ktm::lerp(ktm::fvec3(0.0f), ktm::fvec3(1.0f), 0.5f), ktm::fvec3(0.5f));
    TEST_EQUAL(ktm::lerp(ktm::fvec4(0.0f), ktm::fvec4(1.0f), 0.5f), ktm::fvec4(0.5f));
    TEST_EQUAL(ktm::mix(ktm::fvec1(0.0f), ktm::fvec1(1.0f), ktm::fvec1(0.5f)), ktm::fvec1(0.5f));
    TEST_EQUAL(ktm::mix(ktm::fvec2(0.0f), ktm::fvec2(1.0f), ktm::fvec2(0.5f)), ktm::fvec2(0.5f));
    TEST_EQUAL(ktm::mix(ktm::fvec3(0.0f), ktm::fvec3(1.0f), ktm::fvec3(0.5f)), ktm::fvec3(0.5f));
    TEST_EQUAL(ktm::mix(ktm::fvec4(0.0f), ktm::fvec4(1.0f), ktm::fvec4(0.5f)), ktm::fvec4(0.5f));
    TEST_EQUAL(ktm::step(ktm::fvec1(0.5f), ktm::fvec1(0.7f)), ktm::fvec1(1.0f));
    TEST_EQUAL(ktm::step(ktm::fvec2(0.5f), ktm::fvec2(0.7f, 0.3f)), ktm::fvec2(1.0f, 0.0f));
    TEST_EQUAL(ktm::step(ktm::fvec2(0.0f), ktm::fvec2(1.0f, -1.0f)), ktm::fvec2(1.0f, 0.0f));
    TEST_EQUAL(ktm::step(ktm::fvec2(0.5f), ktm::fvec2(0.5f, 0.49f)), ktm::fvec2(1.0f, 0.0f));
    TEST_EQUAL(ktm::step(ktm::fvec3(0.5f), ktm::fvec3(0.7f, 0.3f, 0.5f)), ktm::fvec3(1.0f, 0.0f, 1.0f));
    TEST_EQUAL(ktm::step(ktm::fvec4(0.5f), ktm::fvec4(0.7f, 0.3f, 0.5f, 0.49f)), ktm::fvec4(1.0f, 0.0f, 1.0f, 0.0f));
    TEST_EQUAL(ktm::sqrt(ktm::fvec1(4.0f)), ktm::fvec1(2.0f));
    TEST_EQUAL(ktm::sqrt(ktm::fvec2(4.0f, 9.0f)), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL(ktm::sqrt(ktm::fvec3(4.0f, 9.0f, 16.0f)), ktm::fvec3(2.0f, 3.0f, 4.0f));
    TEST_EQUAL(ktm::sqrt(ktm::fvec4(4.0f, 9.0f, 16.0f, 25.0f)), ktm::fvec4(2.0f, 3.0f, 4.0f, 5.0f));
    TEST_EQUAL(ktm::rsqrt(ktm::fvec1(4.0f)), ktm::fvec1(0.5f));
    TEST_EQUAL(ktm::rsqrt(ktm::fvec2(4.0f, 9.0f)), ktm::fvec2(0.5f, 0.333333f));
    TEST_EQUAL(ktm::rsqrt(ktm::fvec3(4.0f, 9.0f, 16.0f)), ktm::fvec3(0.5f, 0.333333f, 0.25f));
    TEST_EQUAL(ktm::rsqrt(ktm::fvec4(4.0f, 9.0f, 16.0f, 25.0f)), ktm::fvec4(0.5f, 0.333333f, 0.25f, 0.2f));
    TEST_EQUAL(ktm::pow(ktm::fvec1(2.0f), ktm::fvec1(3.0f)), ktm::fvec1(8.0f));
    TEST_EQUAL(ktm::pow(ktm::fvec2(2.0f), ktm::fvec2(3.0f)), ktm::fvec2(8.0f));
    TEST_EQUAL(ktm::pow(ktm::fvec3(2.0f), ktm::fvec3(3.0f)), ktm::fvec3(8.0f));
    TEST_EQUAL(ktm::pow(ktm::fvec4(2.0f), ktm::fvec4(3.0f)), ktm::fvec4(8.0f));
    TEST_EQUAL(ktm::exp(ktm::fvec1(1.0f)), ktm::fvec1(2.718282f));
    TEST_EQUAL(ktm::exp(ktm::fvec2(0.0f, 1.0f)), ktm::fvec2(1.0f, 2.718282f));
    TEST_EQUAL(ktm::exp(ktm::fvec3(0.0f, 1.0f, 2.0f)), ktm::fvec3(1.0f, 2.718282f, 7.389056f));
    TEST_EQUAL(ktm::exp(ktm::fvec4(0.0f, 1.0f, 2.0f, 3.0f)), ktm::fvec4(1.0f, 2.718282f, 7.389056f, 20.085537f));
    TEST_EQUAL(ktm::log(ktm::fvec1(2.718282f)), ktm::fvec1(1.0f));
    TEST_EQUAL(ktm::log(ktm::fvec2(1.0f, 2.718282f)), ktm::fvec2(0.0f, 1.0f));
    TEST_EQUAL(ktm::log(ktm::fvec3(1.0f, 2.718282f, 7.389056f)), ktm::fvec3(0.0f, 1.0f, 2.0f));
    TEST_EQUAL(ktm::log(ktm::fvec4(1.0f, 2.718282f, 7.389056f, 20.085537f)), ktm::fvec4(0.0f, 1.0f, 2.0f, 3.0f));
    TEST_EQUAL_FAST(ktm::fast::sqrt(ktm::fvec1(4.0f)), ktm::fvec1(2.0f));
    TEST_EQUAL_FAST(ktm::fast::sqrt(ktm::fvec2(4.0f, 9.0f)), ktm::fvec2(2.0f, 3.0f));
    TEST_EQUAL_FAST(ktm::fast::sqrt(ktm::fvec3(4.0f, 9.0f, 16.0f)), ktm::fvec3(2.0f, 3.0f, 4.0f));
    TEST_EQUAL_FAST(ktm::fast::sqrt(ktm::fvec4(4.0f, 9.0f, 16.0f, 25.0f)), ktm::fvec4(2.0f, 3.0f, 4.0f, 5.0f));
    TEST_EQUAL_FAST(ktm::fast::rsqrt(ktm::fvec1(4.0f)), ktm::fvec1(0.5f));
    TEST_EQUAL_FAST(ktm::fast::rsqrt(ktm::fvec2(4.0f, 9.0f)), ktm::fvec2(0.5f, 0.333333f));
    TEST_EQUAL_FAST(ktm::fast::rsqrt(ktm::fvec3(4.0f, 9.0f, 16.0f)), ktm::fvec3(0.5f, 0.333333f, 0.25f));
    TEST_EQUAL_FAST(ktm::fast::rsqrt(ktm::fvec4(4.0f, 9.0f, 16.0f, 25.0f)), ktm::fvec4(0.5f, 0.333333f, 0.25f, 0.2f));
    TEST_EQUAL_FAST(ktm::fast::recip(ktm::fvec1(2.0f)), ktm::fvec1(0.5f));
    TEST_EQUAL_FAST(ktm::fast::recip(ktm::fvec2(2.0f, 4.0f)), ktm::fvec2(0.5f, 0.25f));
    TEST_EQUAL_FAST(ktm::fast::recip(ktm::fvec3(2.0f, 4.0f, 5.0f)), ktm::fvec3(0.5f, 0.25f, 0.2f));
    TEST_EQUAL_FAST(ktm::fast::recip(ktm::fvec4(2.0f, 4.0f, 5.0f, 8.0f)), ktm::fvec4(0.5f, 0.25f, 0.2f, 0.125f));
    TEST_EQUAL(ktm::sin(ktm::fvec1(ktm::pi<float> / 6.0f)), ktm::fvec1(0.5f));
    TEST_EQUAL(ktm::sin(ktm::fvec2(ktm::pi<float> / 6.0f, ktm::pi<float> / 3.0f)), ktm::fvec2(0.5f, 0.866025f));
    TEST_EQUAL(ktm::sin(ktm::fvec3(ktm::pi<float> / 6.0f, ktm::pi<float> / 3.0f, ktm::pi<float> / 2.0f)),
               ktm::fvec3(0.5f, 0.866025f, 1.0f));
    TEST_EQUAL(
        ktm::sin(ktm::fvec4(ktm::pi<float> / 6.0f, ktm::pi<float> / 3.0f, ktm::pi<float> / 2.0f, ktm::pi<float>)),
        ktm::fvec4(0.5f, 0.866025f, 1.0f, 0.0f));
    TEST_EQUAL(ktm::cos(ktm::fvec1(ktm::pi<float> / 3.0f)), ktm::fvec1(0.5f));
    TEST_EQUAL(ktm::cos(ktm::fvec2(ktm::pi<float> / 3.0f, ktm::pi<float> / 6.0f)), ktm::fvec2(0.5f, 0.866025f));
    TEST_EQUAL(ktm::cos(ktm::fvec3(ktm::pi<float> / 3.0f, ktm::pi<float> / 6.0f, ktm::pi<float> / 2.0f)),
               ktm::fvec3(0.5f, 0.866025f, 0.0f));
    TEST_EQUAL(ktm::cos(ktm::fvec4(ktm::pi<float> / 3.0f, ktm::pi<float> / 6.0f, ktm::pi<float> / 2.0f, 0.0f)),
               ktm::fvec4(0.5f, 0.866025f, 0.0f, 1.0f));
    TEST_EQUAL(ktm::tan(ktm::fvec1(ktm::pi<float> / 6.0f)), ktm::fvec1(0.577350f));
    TEST_EQUAL(ktm::tan(ktm::fvec2(ktm::pi<float> / 6.0f, ktm::pi<float> / 3.0f)), ktm::fvec2(0.577350f, 1.732051f));
    TEST_EQUAL(ktm::tan(ktm::fvec3(ktm::pi<float> / 6.0f, ktm::pi<float> / 3.0f, ktm::pi<float> / 4.0f)),
               ktm::fvec3(0.577350f, 1.732051f, 1.0f));
    TEST_EQUAL(ktm::tan(ktm::fvec4(ktm::pi<float> / 6.0f, ktm::pi<float> / 3.0f, ktm::pi<float> / 4.0f, 0.0f)),
               ktm::fvec4(0.577350f, 1.732051f, 1.0f, 0.0f));
    TEST_EQUAL(ktm::sinh(ktm::fvec1(0.5f)), ktm::fvec1(0.521095f));
    TEST_EQUAL(ktm::sinh(ktm::fvec2(0.5f, 1.2f)), ktm::fvec2(0.521095f, 1.509461f));
    TEST_EQUAL(ktm::sinh(ktm::fvec3(0.5f, 1.2f, 2.0f)), ktm::fvec3(0.521095305f, 1.50946136f, 3.62686041f));
    TEST_EQUAL(ktm::sinh(ktm::fvec4(0.5f, 1.2f, 2.0f, 3.0f)),
               ktm::fvec4(0.521095305f, 1.50946136f, 3.62686041f, 10.0178749f));
    TEST_EQUAL(ktm::cosh(ktm::fvec1(0.5f)), ktm::fvec1(1.127626f));
    TEST_EQUAL(ktm::cosh(ktm::fvec2(0.5f, 1.2f)), ktm::fvec2(1.127626f, 1.810656f));
    TEST_EQUAL(ktm::cosh(ktm::fvec3(0.5f, 1.2f, 2.0f)), ktm::fvec3(1.12762597f, 1.81065557f, 3.76219569f));
    TEST_EQUAL(ktm::cosh(ktm::fvec4(0.5f, 1.2f, 2.0f, 3.0f)),
               ktm::fvec4(1.12762597f, 1.81065557f, 3.76219569f, 10.067662f));
    TEST_EQUAL(ktm::tanh(ktm::fvec1(0.5f)), ktm::fvec1(0.462117f));
    TEST_EQUAL(ktm::tanh(ktm::fvec2(0.5f, 1.2f)), ktm::fvec2(0.462117f, 0.833655f));
    TEST_EQUAL(ktm::tanh(ktm::fvec3(0.5f, 1.2f, 2.0f)), ktm::fvec3(0.462117157f, 0.833654607f, 0.96402758f));
    TEST_EQUAL(ktm::tanh(ktm::fvec4(0.5f, 1.2f, 2.0f, 3.0f)),
               ktm::fvec4(0.462117157f, 0.833654607f, 0.96402758f, 0.995054754f));

    return 0;
}
