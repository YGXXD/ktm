//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_I_ARRAY_CALC_H_
#define _KTM_I_ARRAY_CALC_H_

#include "../../setup.h"
#include "../../traits/type_traits_math.h"
#include "../../traits/type_single_extends.h"
#include "../../detail/shared/array_calc_fwd.h"

#define KTM_ARRAY_CALC_CALL(calc_name, ...) \
using ArrayT = std::extract_type_t<decltype(child_ptr()->to_array())>; \
detail::array_calc_implement::calc_name<typename ArrayT::value_type, ArrayT().size()>::call(__VA_ARGS__);

namespace ktm
{

template<class Father, class Child>
struct iarray_add : Father
{
    using Father::Father;
    using Father::child_ptr;

    KTM_FUNC Child operator+(const Child& y) const noexcept { return add(y); }
    KTM_FUNC Child& operator+=(const Child& y) noexcept { return add_to_self(y); }
    KTM_FUNC Child operator-(const Child& y) const noexcept { return sub(y); }
    KTM_FUNC Child& operator-=(const Child& y) noexcept { return sub_to_self(y); }
    KTM_FUNC Child operator-() const noexcept { return neg(); }
private:
    KTM_FUNC Child add(const Child& y) const noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, add_impl))
            return child_ptr()->add_impl(y);
        else
        {
            Child ret;
            KTM_ARRAY_CALC_CALL(add, ret.to_array(), child_ptr()->to_array(), y.to_array())
            return ret;
        }
    }

    KTM_FUNC Child& add_to_self(const Child& y) noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, add_to_self_impl))
            return child_ptr()->add_to_self_impl(y);
        else
        {
            KTM_ARRAY_CALC_CALL(add, child_ptr()->to_array(), child_ptr()->to_array(), y.to_array())
            return *child_ptr();
        }
    }

    KTM_FUNC Child sub(const Child& y) const noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, sub_impl))
            return child_ptr()->sub_impl(y);
        else
        {
            Child ret;
            KTM_ARRAY_CALC_CALL(sub, ret.to_array(), child_ptr()->to_array(), y.to_array())
            return ret;
        }
    }

    KTM_FUNC Child& sub_to_self(const Child& y) noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, sub_to_self_impl))
            return child_ptr()->sub_to_self_impl(y);
        else
        {
            KTM_ARRAY_CALC_CALL(sub, child_ptr()->to_array(), child_ptr()->to_array(), y.to_array())
            return *child_ptr(); 
        }
    }

    KTM_FUNC Child neg() const noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, neg_impl))
            return child_ptr()->neg_impl();
        else
        {
            Child ret;
            KTM_ARRAY_CALC_CALL(neg, ret.to_array(), child_ptr()->to_array())
            return ret;
        }
    }

    KTM_CRTP_CHILD_IMPL_CHECK(add, add_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(add_to_self, add_to_self_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(sub, sub_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(sub_to_self, sub_to_self_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(neg, neg_impl)
};

template<class Father, class Child>
struct iarray_mul : Father
{
    using Father::Father;
    using Father::child_ptr;

    KTM_FUNC Child operator*(const Child& y) const noexcept { return mul(y); }
    KTM_FUNC Child& operator*=(const Child& y) noexcept { return mul_to_self(y); }
    KTM_FUNC Child operator/(const Child& y) const noexcept { return div(y); }
    KTM_FUNC Child& operator/=(const Child& y) noexcept { return div_to_self(y); }
private:
    KTM_FUNC Child mul(const Child& y) const noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, mul_impl))
            return child_ptr()->mul(y);
        else
        {
            Child ret;
            KTM_ARRAY_CALC_CALL(mul, ret.to_array(), child_ptr()->to_array(), y.to_array())
            return ret;
        }
    }

    KTM_FUNC Child& mul_to_self(const Child& y) noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, mul_to_self_impl))
            return child_ptr()->mul_to_self_impl(y);
        else
        {
            KTM_ARRAY_CALC_CALL(mul, child_ptr()->to_array(), child_ptr()->to_array(), y.to_array())
            return *child_ptr();
        }
    }

    KTM_FUNC Child div(const Child& y) const noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, div_impl))
            return child_ptr()->div_impl(y);
        else
        {
            Child ret;
            KTM_ARRAY_CALC_CALL(div, ret.to_array(), child_ptr()->to_array(), y.to_array())
            return ret;
        }
    }

    KTM_FUNC Child& div_to_self(const Child& y) noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, div_to_self_impl))
            return child_ptr()->div_to_self_impl(y);
        else
        {
            KTM_ARRAY_CALC_CALL(div, child_ptr()->to_array(), child_ptr()->to_array(), y.to_array())
            return *child_ptr();
        } 
    }

    KTM_CRTP_CHILD_IMPL_CHECK(mul, mul_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(mul_to_self, mul_to_self_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(div, div_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(div_to_self, div_to_self_impl)
};

template<class Father, class Child>
struct iarray_add_scalar : Father
{
    using Father::Father;
    using Father::child_ptr;
    using ScalarT = typename math_traits<Child>::base_type;

    KTM_FUNC Child operator+(ScalarT scalar) const noexcept { return add_scalar(scalar); }
    KTM_FUNC Child& operator+=(ScalarT scalar) noexcept { return add_scalar_to_self(scalar); }
    KTM_FUNC Child operator-(ScalarT scalar) const noexcept { return sub_scalar(scalar); }
    KTM_FUNC Child& operator-=(ScalarT scalar) noexcept { return sub_scalar_to_self(scalar); }
    friend KTM_FUNC Child operator+(ScalarT scalar, const Child& x) noexcept { return x + scalar; }
private:
    KTM_FUNC Child add_scalar(ScalarT scalar) const noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, add_scalar_impl))
            return child_ptr()->add_scalar_impl(scalar);
        else
        {
            Child ret;
            KTM_ARRAY_CALC_CALL(add_scalar, ret.to_array(), child_ptr()->to_array(), scalar)
            return ret;
        }
    }

    KTM_FUNC Child& add_scalar_to_self(ScalarT scalar) noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, add_scalar_to_self_impl))
            return child_ptr()->add_scalar_to_self_impl(scalar);
        else
        {
            KTM_ARRAY_CALC_CALL(add_scalar, child_ptr()->to_array(), child_ptr()->to_array(), scalar) 
            return *child_ptr();
        }
    }

    KTM_FUNC Child sub_scalar(ScalarT scalar) const noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, sub_scalar_impl))
            return child_ptr()->sub_scalar_impl(scalar);
        else
        {
            Child ret;
            KTM_ARRAY_CALC_CALL(sub_scalar, ret.to_array(), child_ptr()->to_array(), scalar)
            return ret;
        }
    }

    KTM_FUNC Child& sub_scalar_to_self(ScalarT scalar) noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, sub_scalar_to_self_impl))
            return child_ptr()->sub_scalar_to_self_impl(scalar);
        else
        {
            KTM_ARRAY_CALC_CALL(sub_scalar, child_ptr()->to_array(), child_ptr()->to_array(), scalar) 
            return *child_ptr();
        } 
    } 

    KTM_CRTP_CHILD_IMPL_CHECK(add_scalar, add_scalar_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(add_scalar_to_self, add_scalar_to_self_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(sub_scalar, sub_scalar_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(sub_scalar_to_self, sub_scalar_to_self_impl)
};

template<class Father, class Child>
struct iarray_mul_scalar : Father
{
    using Father::Father;
    using Father::child_ptr;
    using ScalarT = typename math_traits<Child>::base_type;

    KTM_FUNC Child operator*(ScalarT scalar) const noexcept { return mul_scalar(scalar); }
    KTM_FUNC Child& operator*=(ScalarT scalar) noexcept { return mul_scalar_to_self(scalar); }
    KTM_FUNC Child operator/(ScalarT scalar) const noexcept { return div_scalar(scalar); }
    KTM_FUNC Child& operator/=(ScalarT scalar) noexcept { return div_scalar_to_self(scalar); }
    friend KTM_FUNC Child operator*(ScalarT scalar, const Child& x) noexcept { return x * scalar; }
private:
    KTM_FUNC Child mul_scalar(ScalarT scalar) const noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, mul_scalar_impl))
            return child_ptr()->mul_scalar_impl(scalar);
        else
        {
            Child ret;
            KTM_ARRAY_CALC_CALL(mul_scalar, ret.to_array(), child_ptr()->to_array(), scalar)
            return ret;
        }
    }

    KTM_FUNC Child& mul_scalar_to_self(ScalarT scalar) noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, mul_scalar_to_self_impl))
            return child_ptr()->mul_scalar_to_self_impl(scalar);
        else
        {
            KTM_ARRAY_CALC_CALL(mul_scalar, child_ptr()->to_array(), child_ptr()->to_array(), scalar) 
            return *child_ptr();
        }
    }

    KTM_FUNC Child div_scalar(ScalarT scalar) const noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, div_scalar_impl))
            return child_ptr()->div_scalar_impl(scalar);
        else
        {
            Child ret;
            KTM_ARRAY_CALC_CALL(div_scalar, ret.to_array(), child_ptr()->to_array(), scalar)
            return ret;
        }
    }

    KTM_FUNC Child& div_scalar_to_self(ScalarT scalar) noexcept
    {
        if constexpr(KTM_CRTP_CHILD_IMPL_VALUE(Child, div_scalar_to_self_impl))
            return child_ptr()->div_scalar_to_self_impl(scalar);
        else
        {
            KTM_ARRAY_CALC_CALL(div_scalar, child_ptr()->to_array(), child_ptr()->to_array(), scalar) 
            return *child_ptr();
        } 
    } 

    KTM_CRTP_CHILD_IMPL_CHECK(mul_scalar, mul_scalar_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(mul_scalar_to_self, mul_scalar_to_self_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(div_scalar, div_scalar_impl)
    KTM_CRTP_CHILD_IMPL_CHECK(div_scalar_to_self, div_scalar_to_self_impl)
};

template<class Father, class Child>
using iarray_add_calc = combine_interface<iarray_add, iarray_add_scalar>::type<Father, Child>;

template<class Father, class Child>
using iarray_mul_calc = combine_interface<iarray_mul, iarray_mul_scalar>::type<Father, Child>;

template<class Father, class Child>
using iarray_calc = combine_interface<iarray_add_calc, iarray_mul_calc>::type<Father, Child>;

}

#include "../../detail/shared/array_calc.inl"
#include "../../detail/shared/array_calc_simd.inl"

#endif