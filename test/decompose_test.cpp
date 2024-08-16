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
    ktm::mat<5, 5, double> pdmt = 
    {
        {6, -1, 0, 0, 0},
        {-1, 7, -1, 0, 0},
        {0, -1, 8, -1, 0},
        {0, 0, -1, 9, -1},
        {0, 0, 0, -1, 10}
    };

    ktm::fmat2x2 mt1 = { { 1.f, 2.f }, { 3.f, 4.f } };
    ktm::fmat3x3 mt2 = { { 1.f, 2.f, 3.f }, { 4.f, 5.f, 6.f}, { 7.f, -1.f, -2.f }};
    ktm::mat<5, 5, double> mt3 = 
    { 
        { 1, 4, 7, 2, 3 }, 
        { 4, 5, -1, 4, -1 }, 
        { 7, -1, -2, -5, 4 },
        { 2, 4, -5, 7, -5 },
        { 3, -1, 4, -5, 4 },
    };

    std::cout << "decompose lu1 test:" << std::endl;
    auto lu1 = ktm::decompose_lu_cholesky(pdmt);
    std::cout << lu1.get_l() << "\n" << lu1.get_u() << "\n" << lu1.get_l() * lu1.get_u() << std::endl;

    std::cout << std::endl;

    std::cout << "decompose lu2 test:" << std::endl;
    auto lu2 = ktm::decompose_lu_doolittle(mt1);
    std::cout << lu2.get_l() << "\n" << lu2.get_u() << "\n" << lu2.get_l() * lu2.get_u() << std::endl;

    std::cout << std::endl;

    std::cout << "decompose lu3 test:" << std::endl;
    auto lu3 = ktm::decompose_lu_crout(mt3);
    std::cout << lu3.get_l() << "\n" << lu3.get_u() << "\n" << lu3.get_l() * lu3.get_u() << std::endl;

    std::cout << std::endl;

    std::cout << "decompose qr test:" << std::endl;
    auto qr1 = ktm::decompose_qr_householder(mt1);
    std::cout << qr1.get_q() << "\n" << qr1.get_r() << "\n" << qr1.get_q() * qr1.get_r() << std::endl;

    std::cout << std::endl;

    std::cout << "decompose qr2 test:" << std::endl;
    auto qr2 = ktm::decompose_qr_givens(mt2);
    std::cout << qr2.get_q() << "\n" << qr2.get_r() << "\n" << qr2.get_q() * qr2.get_r() << std::endl;

    std::cout << std::endl;

    std::cout << "decompose qr3 test:" << std::endl;
    auto qr3 = ktm::decompose_qr_schmitd(mt3);
    std::cout << qr3.get_q() << "\n" << qr3.get_r() << "\n" << qr3.get_q() * qr3.get_r() << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "decompose edv1 test:" << std::endl;
    auto edv1 = ktm::decompose_edv_jacobi(mt3);
    ktm::mat<5, 5, double> eigen_value_m1 = ktm::mat<5, 5, double>::from_diag(edv1.get_value());
    std::cout << edv1.get_vector() << "\n" << edv1.get_value()
        << "\n" << edv1.get_vector() * eigen_value_m1 * ktm::transpose(edv1.get_vector()) << std::endl; 

    std::cout << std::endl;

    ktm::fmat2x2 mt5 = { { 5.f, 2.f }, { 2.f, -3.f } };
    
    std::cout << "decompose edv2 test:" << std::endl;
    auto edv2 = ktm::decompose_edv_shiftqr(mt5);
    ktm::fmat2x2 eigen_value_m2 = ktm::fmat2x2::from_diag(edv2.get_value());
    std::cout << edv2.get_vector() << "\n" << edv2.get_value()
        << "\n" << edv2.get_vector() * eigen_value_m2 * ktm::transpose(edv2.get_vector()) << std::endl; 

    std::cout << std::endl;

    ktm::fmat3x3 mt6 = { { 5.f, 2.f, 2.f }, { 2.f, 5.f, -5.2f }, { 2.f, -5.2f, 7.f } };
    
    std::cout << "decompose edv3 test:" << std::endl;
    auto edv3 = ktm::decompose_edv_shiftqr(mt6);
    ktm::fmat3x3 eigen_value_m3 = ktm::fmat3x3::from_diag(edv3.get_value());
    std::cout << edv3.get_vector() << "\n" << edv3.get_value()
        << "\n" << edv3.get_vector() * eigen_value_m3 * ktm::transpose(edv3.get_vector()) << std::endl;

    std::cout << std::endl;

    ktm::mat<6, 4, double> mt4 = 
    { 
        { 1, 4, 7, 2 }, 
        { 4, 5, -1, 4 }, 
        { 7.2, -1.6, -2, -5 },
        { 2, 4, 5, 7.5 },
        { 3.8, -1, 4, -5.4 },
        { 2, 4.9, 11, 7.2 }
    };

    std::cout << "decompose svd1 test:" << std::endl;
    auto usv1 = ktm::decompose_svd(mt1);
    ktm::fmat2x2 s1 = ktm::fmat2x2::from_diag(usv1.get_s());
    std::cout << usv1.get_u() << "\n" << usv1.get_s() << "\n" << usv1.get_vt() 
        << "\n" << usv1.get_u() * s1 * usv1.get_vt() << std::endl;

    std::cout << std::endl;

    std::cout << "decompose svd2 test:" << std::endl;
    auto usv2 = ktm::decompose_svd(mt4);
    ktm::mat<6, 4, double> s2 = { };
    for(int i = 0; i < 4; ++i)
        s2[i][i] = usv2.get_s()[i];
    std::cout << usv2.get_u() << "\n" << usv2.get_s() << "\n" << usv2.get_vt() 
        << "\n" << usv2.get_u() * s2 * usv2.get_vt() << std::endl; 
    
    std::cout << std::endl;

    std::cout << "decompose svd3 test:" << std::endl;
    auto usv3 = ktm::decompose_svd(ktm::transpose(mt4));
    ktm::mat<4, 6, double> s3 = { };
    for(int i = 0; i < 4; ++i)
        s3[i][i] = usv3.get_s()[i]; 
    std::cout << usv3.get_u() << "\n" << usv3.get_s() << "\n" << usv3.get_vt() 
        << "\n" << usv3.get_u() * s3 * usv3.get_vt() << std::endl; 

    std::cout << std::endl;

    ktm::fmat2x2 mt7 = { { -5.f, 0.f }, { 3.f, 1.f } };

    std::cout << "decompose affine1 test" << std::endl;
    auto affine1 = ktm::decompose_affine(mt7);
    std::cout << affine1.get_translate() << "\n" << 
        affine1.get_rotate() << "\n" << 
            affine1.get_shear() << "\n" << 
                affine1.get_scale() << std::endl;
    std::cout << affine1.get_translate() * 
        affine1.get_rotate() * 
            affine1.get_shear() * 
                affine1.get_scale() << std::endl;

    std::cout << std::endl;

    ktm::mat<6, 6, double> mt8 = 
    { 
        { 1.f, 4.f, 7.f, 2.f, 5.f, 0.f }, 
        { 4.f, 5.f, -1.f, 4.f, 3.f, 0.f}, 
        { 7.2f, -1.6f, -2.f, -5.f, 4.f, 0.f },
        { 2.f, 4.f, 5.f, 7.5f, 0.8f, 0.f },
        { 3.8f, -1.f, 4.f, -5.4f, 4.6f, 0.f },
        { 8.f, 9.f, -2.f, 7.6f, 9.1f, 1.f }
    };
    
    std::cout << "decompose affine2 test" << std::endl;
    auto affine2 = ktm::decompose_affine(mt8);
    std::cout << affine2.get_translate() << "\n" << 
        affine2.get_rotate() << "\n" << 
            affine2.get_shear() << "\n" << 
                affine2.get_scale() << std::endl;
    std::cout << affine2.get_translate() * 
        affine2.get_rotate() * 
            affine2.get_shear() * 
                affine2.get_scale() << std::endl;

    return 0;
}