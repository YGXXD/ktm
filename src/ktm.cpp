//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#include "../ktm/ktm.h"
#include <iostream>

using namespace ktm;
using namespace std;

int main(int argv, char* argc[])
{
    cout << "hello kutori math" << endl;
    cout << "rsqrt approximation of 4 is " << fast::rsqrt<float>(4.f) << endl;
    return 0;
}