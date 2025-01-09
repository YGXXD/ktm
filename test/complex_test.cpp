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
    ktm::fvec2 v1 = { 2.f, 2.f };
    ktm::fcomp c1 = ktm::fcomp::from_to(ktm::fvec2(1.f, 0.f), ktm::fvec2(0.f, 1.f));
    ktm::fcomp c2 = ktm::fcomp::from_to(ktm::fvec2(0.f, 1.f), ktm::fvec2(1.f, 0.f));

    ktm::fvec2 v2 = c1 * c2 * v1;
    std::cout << "effect (comp mul comp) rotate vec" << std::endl;
    std::cout << v2 << std::endl;

    ktm::fcomp c3 = ktm::fcomp::from_to(ktm::fvec2(0.6f, 0.8f), ktm::fvec2(1.f, 0.f));
    std::cout << "effect comp mul vec" << std::endl;
    std::cout << c3 * v1 << std::endl;

    ktm::fcomp c4 = ktm::fcomp::from_angle(ktm::half_pi<float>);
    std::cout << "from_angle rotate vec" << std::endl;
    std::cout << c4 * v2 << std::endl;

    ktm::fcomp c5 = ktm::fcomp::from_angle(ktm::half_pi<float>);
    ktm::fcomp c6 = ktm::fcomp::from_angle(ktm::tow_pi<float>);
    ktm::fvec2 v3 = { 1.f, 1.f };
    std::cout << "slerp comp rotate vec" << std::endl;
    for (float i = 0.f; i <= 1.00005f; i += 0.1f)
    {
        ktm::fcomp c = slerp(c5, c6, i);
        ktm::fmat2x2 m = c.matrix2x2();
        std::cout << c * v3 << std::endl;
        std::cout << m * v3 << std::endl;
    }

    std::cout << "inverse: " << ktm::inverse(c5) << std::endl;
    std::cout << "negate: " << -c5 << std::endl;
    std::cout << "normalize: " << ktm::normalize(c5) << std::endl;
    std::cout << "log(exp): " << ktm::log(ktm::exp(c3)) << std::endl;
    std::cout << "slerp: " << ktm::slerp(c5, c3, 0.5f) << std::endl;
    std::cout << "slerp_longest: " << ktm::slerp_longest(c5, c3, 0.5f) << std::endl;

    return 0;
}