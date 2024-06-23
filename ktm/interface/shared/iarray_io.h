//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_I_ARRAY_IO_H_
#define _KTM_I_ARRAY_IO_H_

#include <iostream>
#include "../../setup.h"
#include "../../traits/type_single_extends.h"

namespace ktm
{

template<class Father, class Child>
struct iarray_io : Father
{
    using Father::Father;
    using Father::child_ptr;

    friend KTM_FUNC std::ostream& operator<<(std::ostream& out, const Child& x) noexcept { return x.stdout(out); }
    friend KTM_FUNC std::istream& operator>>(std::istream& in, Child& x) noexcept { return x.stdin(in); }
private:
    KTM_FUNC std::ostream& stdout(std::ostream& o) const noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, stdout_impl))
            return child_ptr()->stdout_impl(o);
        else
        {
            auto it = child_ptr()->begin();
            for(; it != child_ptr()->end() - 1; ++it)
                o << *it << " ";
            o << *it;
            return o;
        }
    }

    KTM_FUNC std::istream& stdin(std::istream& i) noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, stdin_impl))
            return child_ptr()->stdin_impl(i);
        else
        {
            for(auto it = child_ptr()->begin(); it != child_ptr()->end(); ++it)
                i >> *it;
            return i;
        }
    }

    KTM_CRTP_CHILD_IMPL_CHECK(stdout, stdout_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(stdin, stdin_impl)
};

}

#endif