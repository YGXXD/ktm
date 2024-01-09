#ifndef _I_ARRAY_H_
#define _I_ARRAY_H_

#include "Math/function/ArtcBase.h"
#include <array>
#include <iostream>

namespace ktm
{

template<class Father, class Child>
struct IArray : Father
{
    using Father::Father;
    using typename Father::array_type;

    template<size_t Index> 
    CHTHOLLY_FUNC typename array_type::value_type get() const noexcept { static_assert(Index < size()); return reinterpret_cast<typename array_type::const_pointer>(this)[Index]; }
    template<size_t Index> 
    CHTHOLLY_FUNC void set(typename array_type::const_reference v) noexcept { static_assert(Index < size()); reinterpret_cast<typename array_type::pointer>(this)[Index] = v; }

    CHTHOLLY_FUNC array_type& to_array() noexcept { return reinterpret_cast<array_type&>(*this); }
    CHTHOLLY_FUNC const array_type& to_array() const noexcept { return reinterpret_cast<const array_type&>(*this); }

    CHTHOLLY_FUNC void fill(typename array_type::const_reference v) noexcept { to_array().fill(v); };
    CHTHOLLY_FUNC void swap(Child& other) noexcept { to_array().swap(other.to_array()); }

    CHTHOLLY_FUNC typename array_type::iterator begin() noexcept { return to_array().begin(); }
    CHTHOLLY_FUNC typename array_type::const_iterator begin() const noexcept { return to_array().begin(); }
    CHTHOLLY_FUNC typename array_type::iterator end() noexcept { return to_array().end(); }
    CHTHOLLY_FUNC typename array_type::const_iterator end() const noexcept { return to_array().end(); }

    CHTHOLLY_FUNC typename array_type::reverse_iterator rbegin() noexcept { return to_array().rbegin(); }
    CHTHOLLY_FUNC typename array_type::const_reverse_iterator rbegin() const noexcept { return to_array().rbegin(); }
    CHTHOLLY_FUNC typename array_type::reverse_iterator rend() noexcept { return to_array().rend(); }
    CHTHOLLY_FUNC typename array_type::const_reverse_iterator rend() const noexcept { return to_array().rend(); }

    CHTHOLLY_FUNC typename array_type::const_iterator cbegin() const noexcept { return begin(); }
    CHTHOLLY_FUNC typename array_type::const_iterator cend() const noexcept { return end(); }
    CHTHOLLY_FUNC typename array_type::const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    CHTHOLLY_FUNC typename array_type::const_reverse_iterator crend() const noexcept { return rend(); }

    constexpr size_t size() const noexcept { return to_array().size(); }
    constexpr size_t max_size() const noexcept { return to_array().max_size(); }
    constexpr bool empty() const noexcept { return false; }

    CHTHOLLY_FUNC typename array_type::reference at(size_t i) { return to_array().at(i); }
    CHTHOLLY_FUNC typename array_type::const_reference at(size_t i) const { return to_array().at(i); }
    CHTHOLLY_FUNC typename array_type::reference front() noexcept { return to_array().front(); }
    CHTHOLLY_FUNC typename array_type::const_reference front() const noexcept { return to_array().front(); }
    CHTHOLLY_FUNC typename array_type::reference back() noexcept { return to_array().back(); }
    CHTHOLLY_FUNC typename array_type::const_reference back() const noexcept { return to_array().back(); }

    CHTHOLLY_FUNC typename array_type::pointer data() noexcept { return to_array().data(); }
    CHTHOLLY_FUNC typename array_type::const_pointer data() const noexcept { return to_array().data(); }

    CHTHOLLY_FUNC typename array_type::reference operator[](size_t i) noexcept { return to_array()[i]; }
    CHTHOLLY_FUNC typename array_type::const_reference operator[](size_t i) const noexcept { return to_array()[i]; }

    friend CHTHOLLY_FUNC bool operator==(const Child& x, const Child& y) { return x.to_array() == y.to_array(); }
    friend CHTHOLLY_FUNC bool operator!=(const Child& x, const Child& y) { return x.to_array() != y.to_array(); }
    friend CHTHOLLY_FUNC bool operator< (const Child& x, const Child& y) { return x.to_array() <  y.to_array(); }
    friend CHTHOLLY_FUNC bool operator> (const Child& x, const Child& y) { return x.to_array() >  y.to_array(); }
    friend CHTHOLLY_FUNC bool operator<=(const Child& x, const Child& y) { return x.to_array() <= y.to_array(); }
    friend CHTHOLLY_FUNC bool operator>=(const Child& x, const Child& y) { return x.to_array() >= y.to_array(); }

    friend CHTHOLLY_FUNC std::ostream& operator<<(std::ostream& o, const Child& x) noexcept 
    {
        auto it = x.begin();
        for(; it != x.end() - 1; ++it)
            o << *it << " ";
        o << *it;
        return o;
    }
    friend CHTHOLLY_FUNC std::istream& operator>>(std::istream& i, const Child& x) noexcept
    {
        for(auto it = x.begin(); it != x.end(); ++it)
            i >> *it;
        return i;
    }

};
}


#endif