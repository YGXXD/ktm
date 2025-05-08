//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_TEST_H_
#define _KTM_TEST_H_

#include "ktm.h"
#include <iostream>
#include <cassert>

#define TEST_EQUAL_WITH_EPSILON(x, y, e)                                                                           \
    {                                                                                                              \
        auto _vx = x;                                                                                              \
        auto _vy = y;                                                                                              \
        auto _e = e;                                                                                               \
        if (!ktm::equal(_vx, _vy, _e))                                                                             \
        {                                                                                                          \
            std::cerr << "Test failed at line " << __LINE__ << ": " << _vx << " != " << _vy << " (with tolerance " \
                      << _e << ")" << std::endl;                                                                   \
            return 1;                                                                                              \
        }                                                                                                          \
    }
#define TEST_EQUAL(x, y) TEST_EQUAL_WITH_EPSILON(x, y, 1e-5f)
#define TEST_EQUAL_FAST(x, y) TEST_EQUAL_WITH_EPSILON(x, y, 5e-2f)
#define TEST_EQUAL_MATRIX(x, y, row)   \
    {                                  \
        auto _mx = x;                  \
        auto _my = y;                  \
        auto _row = row;               \
        for (int i = 0; i < _row; i++) \
        {                              \
            TEST_EQUAL(_mx[i], _my[i]) \
        }                              \
    }
#define TEST_EQUAL_QUATERNION(x, y) TEST_EQUAL(*(x), *(y))
#define TEST_EQUAL_COMPLEX(x, y) TEST_EQUAL_QUATERNION(x, y)

#endif