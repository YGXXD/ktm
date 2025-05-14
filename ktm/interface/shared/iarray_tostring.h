//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_I_ARRAY_TOSTRING_H_
#define _KTM_I_ARRAY_TOSTRING_H_

#include <string>
#include "../../setup.h"
#include "../../traits/type_single_extends.h"

namespace ktm
{

template <class Father, class Child>
struct iarray_tostring : Father
{
    using Father::child_ptr;
    using Father::Father;

    KTM_CRTP_INTERFACE_REGISTER(to_string, to_string_impl)

    KTM_FUNC std::string to_string() const noexcept
    {
        if constexpr (KTM_CRTP_INTERFACE_IMPLEMENT(Child, to_string_impl))
            return child_ptr()->to_string_impl();
        else
        {
            std::string str;
            for (auto it = child_ptr()->begin(); it != child_ptr()->end() - 1; ++it)
                str += std::to_string(*it) + " ";
            str += std::to_string(child_ptr()->back());
            return str;
        }
    }

    KTM_CRTP_INTERFACE_REGISTER(to_wstring, to_wstring_impl)

    KTM_FUNC std::wstring to_wstring() const noexcept
    {
        if constexpr (KTM_CRTP_INTERFACE_IMPLEMENT(Child, to_wstring_impl))
            return child_ptr()->to_wstring_impl();
        else
        {
            std::wstring str;
            for (auto it = child_ptr()->begin(); it != child_ptr()->end() - 1; ++it)
                str += std::to_wstring(*it) + L" ";
            str += std::to_wstring(child_ptr()->back());
            return str;
        }
    }
};

} // namespace ktm

#endif