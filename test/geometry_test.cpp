//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#include "../ktm/ktm.h"

int main(int argc, char* argv[])
{
    ktm::fvec3 a = { 1.1f, 2.5f, 3.8f };
    ktm::fvec3 b = { 6.9f, 2.3f, -3.1f }; 

    std::cout << "dot: " << ktm::dot(a, b) << std::endl;
    std::cout << "length: " << ktm::length(a) << " " << ktm::length(b) << std::endl;
    std::cout << "fast_length: " << ktm::fast::length(a) << " " << ktm::fast::length(b) << std::endl;
    std::cout << "distance: " << ktm::distance(a, b) << std::endl;
    std::cout << "fast_distance: " << ktm::fast::distance(a, b) << std::endl;
    std::cout << "project: " << ktm::project(a, b) << std::endl;
    std::cout << "fast_project: " << ktm::fast::project(a, b) << std::endl;
    std::cout << "normalize: " << ktm::normalize(b) << std::endl;
    std::cout << "fast_normalize: " << ktm::fast::normalize(b) << std::endl;
    std::cout << "reflect: " << ktm::reflect(a, b) << std::endl; 
    std::cout << "refract: " << ktm::refract(a, b, 1.3) << std::endl; 

    return 0;
}