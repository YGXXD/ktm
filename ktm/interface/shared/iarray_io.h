//  MIT License
//
//  Copyright (c) 2023-2024 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_I_ARRAY_IO_H_
#define _KTM_I_ARRAY_IO_H_

#include <iosfwd>
#include "../../setup.h"
#include "../../traits/type_traits_ext.h"

namespace ktm
{

template<class Father, class Child>
struct iarray_io : Father
{
    using Father::Father;
    using Father::child_ptr;

    template<typename T, typename = std::enable_if_t<std::is_exist_same_vs<char, wchar_t, T>>>
    friend KTM_FUNC std::basic_ostream<T>& operator<<(std::basic_ostream<T>& out, const Child& x) noexcept { return x.std_stream_out(out); }
    template<typename T, typename = std::enable_if_t<std::is_exist_same_vs<char, wchar_t, T>>> 
    friend KTM_FUNC std::basic_istream<T>& operator>>(std::basic_istream<T>& in, Child& x) noexcept { return x.std_stream_in(in); }
    
    template<typename T, typename = std::enable_if_t<std::is_exist_same_vs<char, wchar_t, T>>>  
    friend KTM_FUNC std::basic_ostringstream<T>& operator<<(std::basic_ostringstream<T>& out, const Child& x) noexcept { return x.std_stream_out(out); }
    template<typename T, typename = std::enable_if_t<std::is_exist_same_vs<char, wchar_t, T>>> 
    friend KTM_FUNC std::basic_istringstream<T>& operator>>(std::basic_istringstream<T>& in, Child& x) noexcept { return x.std_stream_in(in); }

    template<typename T, typename = std::enable_if_t<std::is_exist_same_vs<char, wchar_t, T>>>  
    friend KTM_FUNC std::basic_ofstream<T>& operator<<(std::basic_ofstream<T>& out, const Child& x) noexcept { return x.std_stream_out(out); }
    template<typename T, typename = std::enable_if_t<std::is_exist_same_vs<char, wchar_t, T>>> 
    friend KTM_FUNC std::basic_ifstream<T>& operator>>(std::basic_ifstream<T>& in, Child& x) noexcept { return x.std_stream_in(in); } 
private:
    template<template<typename ...> class OSTp, typename T>
    KTM_FUNC OSTp<T>& std_stream_out(OSTp<T>& o) const noexcept
    {
        auto it = child_ptr()->begin();
        for(; it != child_ptr()->end() - 1; ++it)
            o << *it << " ";
        o << *it;
        return o;
    }

    template<template<typename ...> class ISTp, typename T>
    KTM_FUNC ISTp<T>& std_stream_in(ISTp<T>& i) noexcept
    {
        for(auto it = child_ptr()->begin(); it != child_ptr()->end(); ++it)
            i >> *it;
        return i;
    }
};

}

#endif