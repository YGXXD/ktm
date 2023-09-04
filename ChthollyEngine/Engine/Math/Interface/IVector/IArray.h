#ifndef _I_ARRAY_H_
#define _I_ARRAY_H_

#include "Math/MathType/BaseType.h"

namespace ktm
{

template<class Father, class Child>
struct IArray : Father
{
    using Father::Father;
    using value_type = vec_traits_t<Child>;
    static constexpr size_t len = vec_traits_len<Child>;
    using array_type = std::array<value_type, len>;

    template<size_t Index> 
    CHTHOLLY_INLINE value_type get() const noexcept { static_assert(Index < len); return reinterpret_cast<const value_type*>(this)[Index]; }
    template<size_t Index> 
    CHTHOLLY_INLINE void set(value_type v) noexcept { static_assert(Index < len); reinterpret_cast<value_type*>(this)[Index] = v; }

    CHTHOLLY_INLINE array_type& to_array() noexcept { return reinterpret_cast<array_type&>(*this); }
    CHTHOLLY_INLINE const array_type& to_array() const noexcept { return reinterpret_cast<const array_type&>(*this); }

    CHTHOLLY_INLINE void fill(value_type v) noexcept { to_array().fill(v); };
    CHTHOLLY_INLINE void swap(Child& other) noexcept { to_array().swap(other.to_array()); }

    CHTHOLLY_INLINE typename array_type::iterator begin() noexcept { return to_array().begin(); }
    CHTHOLLY_INLINE typename array_type::const_iterator begin() const noexcept { return to_array().begin(); }
    CHTHOLLY_INLINE typename array_type::iterator end() noexcept { return to_array().end(); }
    CHTHOLLY_INLINE typename array_type::const_iterator end() const noexcept { return to_array().end(); }

    CHTHOLLY_INLINE typename array_type::reverse_iterator rbegin() noexcept { return to_array().rbegin(); }
    CHTHOLLY_INLINE typename array_type::const_reverse_iterator rbegin() const noexcept { return to_array().rbegin(); }
    CHTHOLLY_INLINE typename array_type::reverse_iterator rend() noexcept { return to_array().rend(); }
    CHTHOLLY_INLINE typename array_type::const_reverse_iterator rend() const noexcept { return to_array().rend(); }

    CHTHOLLY_INLINE typename array_type::const_iterator cbegin() const noexcept { return begin(); }
    CHTHOLLY_INLINE typename array_type::const_iterator cend() const noexcept { return end(); }
    CHTHOLLY_INLINE typename array_type::const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    CHTHOLLY_INLINE typename array_type::const_reverse_iterator crend() const noexcept { return rend(); }

    constexpr size_t size() const noexcept { return len; }
    constexpr size_t max_size() const noexcept { return len; }
    constexpr bool empty() const noexcept { return false; }

    CHTHOLLY_INLINE typename array_type::reference at(size_t i) { return to_array().at(i); }
    CHTHOLLY_INLINE typename array_type::const_reference at(size_t i) const { return to_array().at(i); }
    CHTHOLLY_INLINE typename array_type::reference front() noexcept { return to_array().front(); }
    CHTHOLLY_INLINE typename array_type::const_reference front() const noexcept { return to_array().front(); }
    CHTHOLLY_INLINE typename array_type::reference back() noexcept { return to_array().back(); }
    CHTHOLLY_INLINE typename array_type::const_reference back() const noexcept { return to_array().back(); }

    CHTHOLLY_INLINE typename array_type::pointer data() noexcept { return reinterpret_cast<value_type*>(this); }
    CHTHOLLY_INLINE typename array_type::const_pointer data() const noexcept { return reinterpret_cast<const value_type*>(this); }

    CHTHOLLY_INLINE typename array_type::reference operator[](size_t i) noexcept { return to_array()[i]; }
    CHTHOLLY_INLINE typename array_type::const_reference operator[](size_t i) const noexcept { return to_array()[i]; }
    CHTHOLLY_INLINE bool operator==(const Child& y) const noexcept { return to_array() == y.to_array(); }
    CHTHOLLY_INLINE bool operator!=(const Child& y) const noexcept { return to_array() != y.to_array(); }
    CHTHOLLY_INLINE bool operator< (const Child& y) const noexcept { return to_array() <  y.to_array(); }
    CHTHOLLY_INLINE bool operator> (const Child& y) const noexcept { return to_array() >  y.to_array(); }
    CHTHOLLY_INLINE bool operator<=(const Child& y) const noexcept { return to_array() <= y.to_array(); }
    CHTHOLLY_INLINE bool operator>=(const Child& y) const noexcept { return to_array() >= y.to_array(); }
    friend CHTHOLLY_INLINE std::ostream& operator<<(std::ostream& o, const Child& x) 
    {
        auto it = x.begin();
        for(; it != x.end() - 1; ++it)
            o << *it << " ";
        o << *it;
        return o;
    }
    friend CHTHOLLY_INLINE std::istream& operator>>(std::istream& i, const Child& x) 
    {
        for(auto it = x.begin(); it != x.end(); ++it)
            i >> *it;
        return i;
    }

};
}


#endif