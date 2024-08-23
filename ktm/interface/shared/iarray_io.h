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
private:
    template<typename T>
    KTM_FUNC std::basic_ostream<T>& std_stream_out(std::basic_ostream<T>& o) const noexcept
    {
        auto it = child_ptr()->begin();
        for(; it != child_ptr()->end() - 1; ++it)
            o << *it << " ";
        o << *it;
        return o;
    }

    template<typename T>
    KTM_FUNC std::basic_istream<T>& std_stream_in(std::basic_istream<T>& i) noexcept
    {
        for(auto it = child_ptr()->begin(); it != child_ptr()->end(); ++it)
            i >> *it;
        return i;
    }
};

}

#endif