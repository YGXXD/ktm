//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "../ktm/ktm.h"
#include <iostream>

int main(int argc, char* argv[])
{
    ktm::fvec3 t1 { -6.f, 7.f, 9.f };
    ktm::svec3 t2 { -6, 7, 9 };

    std::cout << "reduce_add: " << ktm::reduce_add(t1) << ", " << ktm::reduce_add(t2) << std::endl;
    std::cout << "reduce_max: " << ktm::reduce_max(t1) << ", " << ktm::reduce_max(t2) << std::endl;
    std::cout << "reduce_min: " << ktm::reduce_min(t1) << ", " << ktm::reduce_min(t2) << std::endl;
    std::cout << "abs: " << ktm::abs(t1) << ", " << ktm::abs(t2) << std::endl;
    std::cout << "clamp: " << ktm::clamp(t1, {-5.f, -5.f, -5.f}, {8.f, 8.f, 8.f}) << ", " << ktm::clamp(t2, {-5, -5, -5}, {8, 8, 8}) << std::endl;

    ktm::fvec3 t3{ 8.f, 9.f, -10.f };
    ktm::fvec3 t4 = (ktm::fvec3)t2;
    ktm::fvec3 t5 = { 2.8f, 3.5f, 8.9f };
    t3 *= t1 + t5;

    std::cout << "equal: " << (t1 == t3) << ", " << (t1 == t4) << ", " << (t2 == (ktm::svec3)t1) << std::endl;
    std::cout << "value: " << t3 << std::endl;
    std::cout << "step: " << ktm::step({-100.f, 200.f, 10.f}, t3) << std::endl;
    std::cout << "smoothstep: " << ktm::smoothstep({-100.f, 20.f, -200.f}, {100.f, 200.f, 200.f}, t3) << std::endl;
    std::cout << "lerp: " << ktm::lerp(t1, t3, 0.6f) << std::endl;
    std::cout << "mix: " << ktm::mix(t1, t3, {0.5f, 0.6f, 0.3f}) << std::endl;
    std::cout << "fract: " << ktm::fract(t3) << std::endl;
    std::cout << "floor: " << ktm::floor(t3) << std::endl;
    std::cout << "ceil: " << ktm::ceil(t3) << std::endl;
    std::cout << "round: " << ktm::round(t3) << std::endl;
    std::cout << "mod: " << ktm::mod(t3, {2.f, 3.f, 3.f}) << std::endl;
    std::cout << "sqrt: " << ktm::sqrt(t5) << std::endl;
    std::cout << "rsqrt: " << ktm::rsqrt(t5) << std::endl;
    std::cout << "recip: " << ktm::recip(t3) << std::endl;
    std::cout << "fast_sqrt: " << ktm::fast::sqrt(t5) << std::endl;
    std::cout << "fast_rsqrt: " << ktm::fast::rsqrt(t5) << std::endl;
    std::cout << "fast_recip: " << ktm::fast::recip(t3) << std::endl;

    return 0;
}