//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_I_ARRAY_INIT_H_
#define _KTM_I_ARRAY_INIT_H_

#include <cstring>
#include <algorithm>
#include "../../setup.h"

namespace ktm
{

template<class Father, class Child>
struct iarray_init : Father
{
    using Father::Father;
    using Father::child_ptr;
    using typename Father::array_type;

#if defined(KTM_DEFAULT_CONSTRUCT_INIT)
    KTM_FUNC iarray_init() noexcept { std::memset(child_ptr()->data(), 0, sizeof(array_type)); }
#endif
    KTM_FUNC iarray_init(std::initializer_list<typename array_type::value_type> li) noexcept
    {
        const size_t offset = li.size() < child_ptr()->size() ? li.size() : child_ptr()->size();
        std::copy(li.begin(), li.begin() + offset, child_ptr()->begin());
#if defined(KTM_DEFAULT_CONSTRUCT_INIT)
        std::fill(child_ptr()->begin() + offset, child_ptr()->end(), typename array_type::value_type { });
#endif
    };
    KTM_FUNC iarray_init(const iarray_init& copy) noexcept { std::memcpy(child_ptr()->data(), copy.data(), sizeof(array_type)); }
    KTM_FUNC iarray_init(iarray_init&& copy) noexcept { std::memcpy(child_ptr()->data(), copy.data(), sizeof(array_type)); };
    KTM_FUNC iarray_init& operator=(const iarray_init& copy) noexcept { std::memcpy(child_ptr()->data(), copy.data(), sizeof(array_type)); return *this; }
    KTM_FUNC iarray_init& operator=(iarray_init&& copy) noexcept { std::memcpy(child_ptr()->data(), copy.data(), sizeof(array_type)); return *this; }
};

}

#endif