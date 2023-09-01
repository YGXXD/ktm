#ifndef _I_ARRAY_H_
#define _I_ARRAY_H_

#include "Math/TypeBase.h"

namespace ktm
{

template<class Father, class Child>
struct IArray : Father
{
    using Father::Father;
    using value_type = math_traits_t<Child>;
    static constexpr size_t len = vec_traits_len<Child>;
    using array_type = std::array<value_type, len>;

    template<size_t Index> 
    CHTHOLLY_INLINE value_type Get() const noexcept { static_assert(Index < len); return reinterpret_cast<const value_type*>(this)[Index]; }
    template<size_t Index> 
    CHTHOLLY_INLINE void Set(value_type v) noexcept { static_assert(Index < len); reinterpret_cast<value_type*>(this)[Index] = v; }

    CHTHOLLY_INLINE array_type& ToArray() noexcept { return reinterpret_cast<array_type&>(*this); }
    CHTHOLLY_INLINE const array_type& ToArray() const noexcept { return reinterpret_cast<const array_type&>(*this); }

    CHTHOLLY_INLINE void Fill(value_type v) noexcept { ToArray().fill(v); };
    CHTHOLLY_INLINE void Swap(Child& other) noexcept { ToArray().swap(other.ToArray()); }

    CHTHOLLY_INLINE typename array_type::iterator Begin() noexcept { return ToArray().begin(); }
    CHTHOLLY_INLINE typename array_type::const_iterator Begin() const noexcept { return ToArray().begin(); }
    CHTHOLLY_INLINE typename array_type::iterator End() noexcept { return ToArray().end(); }
    CHTHOLLY_INLINE typename array_type::const_iterator End() const noexcept { return ToArray().end(); }

    CHTHOLLY_INLINE typename array_type::reverse_iterator RBegin() noexcept { return ToArray().rbegin(); }
    CHTHOLLY_INLINE typename array_type::const_reverse_iterator RBegin() const noexcept { return ToArray().rbegin(); }
    CHTHOLLY_INLINE typename array_type::reverse_iterator REnd() noexcept { return ToArray().rend(); }
    CHTHOLLY_INLINE typename array_type::const_reverse_iterator REnd() const noexcept { return ToArray().rend(); }

    CHTHOLLY_INLINE typename array_type::const_iterator CBegin() const noexcept { return Begin(); }
    CHTHOLLY_INLINE typename array_type::const_iterator CEnd() const noexcept { return End(); }
    CHTHOLLY_INLINE typename array_type::const_reverse_iterator CRBegin() const noexcept { return RBegin(); }
    CHTHOLLY_INLINE typename array_type::const_reverse_iterator CREnd() const noexcept { return REnd(); }

    constexpr size_t Size() const noexcept { return len; }
    constexpr size_t MaxSize() const noexcept { return len; }
    constexpr bool Empty() const noexcept { return false; }

    CHTHOLLY_INLINE typename array_type::reference At(size_t i) { return ToArray().at(i); }
    CHTHOLLY_INLINE typename array_type::const_reference At(size_t i) const { return ToArray().at(i); }
    CHTHOLLY_INLINE typename array_type::reference Front() noexcept { return ToArray().front(); }
    CHTHOLLY_INLINE typename array_type::const_reference Front() const noexcept { return ToArray().front(); }
    CHTHOLLY_INLINE typename array_type::reference Back() noexcept { return ToArray().back(); }
    CHTHOLLY_INLINE typename array_type::const_reference Back() const noexcept { return ToArray().back(); }

    CHTHOLLY_INLINE typename array_type::pointer Data() noexcept { return reinterpret_cast<value_type*>(this); }
    CHTHOLLY_INLINE typename array_type::const_pointer Data() const noexcept { return reinterpret_cast<const value_type*>(this); }

    CHTHOLLY_INLINE typename array_type::reference operator[](size_t i) noexcept { return ToArray()[i]; }
    CHTHOLLY_INLINE typename array_type::const_reference operator[](size_t i) const noexcept { return ToArray()[i]; }
    CHTHOLLY_INLINE bool operator==(const Child& y) const noexcept { return ToArray() == y.ToArray(); }
    CHTHOLLY_INLINE bool operator!=(const Child& y) const noexcept { return ToArray() != y.ToArray(); }
    CHTHOLLY_INLINE bool operator< (const Child& y) const noexcept { return ToArray() <  y.ToArray(); }
    CHTHOLLY_INLINE bool operator> (const Child& y) const noexcept { return ToArray() >  y.ToArray(); }
    CHTHOLLY_INLINE bool operator<=(const Child& y) const noexcept { return ToArray() <= y.ToArray(); }
    CHTHOLLY_INLINE bool operator>=(const Child& y) const noexcept { return ToArray() >= y.ToArray(); }
    friend CHTHOLLY_INLINE std::ostream& operator<<(std::ostream& o, const Child& x) 
    {
        auto it = x.Begin();
        for(; it != x.End() - 1; ++it)
            o << *it << " ";
        o << *it;
        return o;
    }
    friend CHTHOLLY_INLINE std::istream& operator>>(std::istream& i, const Child& x) 
    {
        for(auto it = x.Begin(); it != x.End(); ++it)
            i >> *it;
        return i;
    }

};
}


#endif