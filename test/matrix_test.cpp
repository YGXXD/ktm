//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "../ktm/ktm.h"

int main(int argc, char* argv[])
{
    std::cout << "mat_mul_vec test:" << std::endl;
    ktm::fmat3x2 mt1 = { { 1, 2}, { 1, 2 }, {3, 4} };
    ktm::fvec3 v1 = { 2, 2, 2};

    std::cout << mt1 << std::endl;
    std::cout << v1 << std::endl;
    std::cout << mt1 * v1 << std::endl;

    std::cout << "vec_mul_mat test:" << std::endl;
    ktm::fmat3x2 mt2 = { { 3, 2}, { 1, 2 }, {3, 4} };
    ktm::fvec2 v2 = { 2, 1 };

    std::cout << mt2 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v2 * mt2 << std::endl;

    std::cout << "mat_mul_mat test:" << std::endl; 
    ktm::fmat3x2 mt3 = { { 3, 2}, { 1, 2 }, {3, 4} };
    ktm::fmat2x3 mt4 = { {3, 3, 3}, { 1, 1, 1}};
    std::cout << mt3 << std::endl;
    std::cout << mt4 << std::endl;
    std::cout << mt3 * mt4 << std::endl;

    std::cout << "add test:" << std::endl; 
    ktm::fmat4x3 mt5 = { {3, 3, 3}, { 1, 1, 1}, { 2, 3, 3}, { }};
    std::cout << mt5 << std::endl;
    std::cout << mt5 + mt5 << std::endl;

    std::cout << "equal test:" << std::endl; 
    ktm::fmat4x3 mt6 = mt5; 
    std::cout << (mt5 == mt6) << "," << (mt5 == ktm::fmat4x3()) << std::endl;

    std::cout << "transpose test:" << std::endl; 
    ktm::fmat3x3 mt7_1 = { { 2, -1, 207 }, {-1, 2, -1}, { 20, -1, 2 } };
    std::cout << mt7_1 << std::endl;
    std::cout << ktm::transpose(mt7_1) << std::endl; 
    ktm::fmat2x2 mt7_2 = { { 2, -1 }, { 50, 20 } };
    std::cout << mt7_2 << std::endl;
    std::cout << ktm::transpose(mt7_2) << std::endl; 

    std::cout << "determinant test:" << std::endl;  
    ktm::fmat4x4 mt8 = { {2, -1, 9, 9}, {-1, 2, -1, -8}, { 20, -1, 2, 2}, { 1, 3, 2, 77 }};
    ktm::smat4x4 smt8 = { {2, -1, 9, 9}, {-1, 2, -1, -8}, { 20, -1, 2, 2}, { 1, 3, 2, 77 }};
    std::cout << ktm::determinant(mt8) << "\n" << ktm::determinant(smt8) << std::endl;

    std::cout << "inverse test:" << std::endl;  
    ktm::fmat4x4 mt9 = { {2, -1, 9, 9}, {-1, 2, -1, -8}, { 20, -1, 2, 2}, { 1, 3, 2, 77 }};
    std::cout << ktm::inverse(mt9) * mt9 * mt8 << std::endl; 

    return 0;
}