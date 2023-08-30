#ifndef _I_ARRAY_H_
#define _I_ARRAY_H_

#include "Math/TypeBase.h"

namespace ktl
{
template<class Father, class Child>
struct IArray : Father
{
    using Father::Father;
    using T = math_traits_t<Child>;
    static constexpr int N = vec_traits_len<Child>;
    using ArrayT = std::array<T, N>;

    CHTHOLLY_INLINE ArrayT& ToArray() noexcept { return reinterpret_cast<std::array<T, N>&>(*this); }
    CHTHOLLY_INLINE const ArrayT& ToArray() const noexcept { return reinterpret_cast<const std::array<T, N>&>(*this); }

    CHTHOLLY_INLINE void Fill(T v) noexcept { ToArray().fill(v); };
    CHTHOLLY_INLINE void Swap(Child& other) noexcept { ToArray().swap(other.ToArray()); }

    CHTHOLLY_INLINE typename ArrayT::iterator Begin() noexcept { return ToArray().begin(); }
    CHTHOLLY_INLINE typename ArrayT::const_iterator Begin() const noexcept { return ToArray().begin(); }
    CHTHOLLY_INLINE typename ArrayT::iterator End() noexcept { return ToArray().end(); }
    CHTHOLLY_INLINE typename ArrayT::const_iterator End() const noexcept { return ToArray().end(); }

    CHTHOLLY_INLINE typename ArrayT::reverse_iterator RBegin() noexcept { return ToArray().rbegin(); }
    CHTHOLLY_INLINE typename ArrayT::const_reverse_iterator RBegin() const noexcept { return ToArray().rbegin(); }
    CHTHOLLY_INLINE typename ArrayT::reverse_iterator REnd() noexcept { return ToArray().rend(); }
    CHTHOLLY_INLINE typename ArrayT::const_reverse_iterator REnd() const noexcept { return ToArray().rend(); }

    CHTHOLLY_INLINE typename ArrayT::const_iterator CBegin() const noexcept { return Begin(); }
    CHTHOLLY_INLINE typename ArrayT::const_iterator CEnd() const noexcept { return End(); }
    CHTHOLLY_INLINE typename ArrayT::const_reverse_iterator CRBegin() const noexcept { return RBegin(); }
    CHTHOLLY_INLINE typename ArrayT::const_reverse_iterator CREnd() const noexcept { return REnd(); }

    constexpr size_t Size() const noexcept { return N; }
    constexpr size_t MaxSize() const noexcept { return N; }
    constexpr bool Empty() const noexcept { return false; }

    CHTHOLLY_INLINE typename ArrayT::reference At(size_t i) { return ToArray().at(i); }
    CHTHOLLY_INLINE typename ArrayT::const_reference At(size_t i) const { return ToArray().at(i); }
    CHTHOLLY_INLINE typename ArrayT::reference Front() noexcept { return ToArray().front(); }
    CHTHOLLY_INLINE typename ArrayT::const_reference Front() const noexcept { return ToArray().front(); }
    CHTHOLLY_INLINE typename ArrayT::reference Back() noexcept { return ToArray().back(); }
    CHTHOLLY_INLINE typename ArrayT::const_reference Back() const noexcept { return ToArray().back(); }

    CHTHOLLY_INLINE typename ArrayT::pointer Data() noexcept { return reinterpret_cast<T*>(this); }
    CHTHOLLY_INLINE typename ArrayT::const_pointer Data() const noexcept { return reinterpret_cast<const T*>(this); }

    CHTHOLLY_INLINE typename ArrayT::reference operator[](size_t i) noexcept { return ToArray()[i]; }
    CHTHOLLY_INLINE typename ArrayT::const_reference operator[](size_t i) const noexcept { return ToArray()[i]; }
    CHTHOLLY_INLINE bool operator==(const Child& y) const noexcept { return ToArray() == y.ToArray(); }
    CHTHOLLY_INLINE bool operator!=(const Child& y) const noexcept { return ToArray() != y.ToArray(); }
    CHTHOLLY_INLINE bool operator< (const Child& y) const noexcept { return ToArray() <  y.ToArray(); }
    CHTHOLLY_INLINE bool operator> (const Child& y) const noexcept { return ToArray() >  y.ToArray(); }
    CHTHOLLY_INLINE bool operator<=(const Child& y) const noexcept { return ToArray() <= y.ToArray(); }
    CHTHOLLY_INLINE bool operator>=(const Child& y) const noexcept { return ToArray() >= y.ToArray(); }
};
}


#endif