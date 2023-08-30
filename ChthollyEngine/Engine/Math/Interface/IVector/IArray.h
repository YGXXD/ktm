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

    CHTHOLLY_INLINE std::array<T, N>& ToArray() noexcept { return reinterpret_cast<std::array<T, N>&>(*this); }
    CHTHOLLY_INLINE const std::array<T, N>& ToArray() const noexcept { return reinterpret_cast<std::array<T, N>&>(*this); }

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using iterator = typename std::array<T, N>::iterator;
    using const_iterator = typename std::array<T, N>::const_iterator;
    using reverse_iterator = typename std::array<T, N>::reverse_iterator;
    using const_reverse_iterator = typename std::array<T, N>::const_reverse_iterator;

    CHTHOLLY_INLINE void Fill(T v) noexcept { ToArray().fill(v); };
    CHTHOLLY_INLINE void Swap(Child& other) noexcept { ToArray().swap(other.ToArray()); }

    CHTHOLLY_INLINE iterator Begin() noexcept { return ToArray().begin(); }
    CHTHOLLY_INLINE const_iterator Begin() const noexcept { return ToArray().begin(); }
    CHTHOLLY_INLINE iterator End() noexcept { return ToArray().end(); }
    CHTHOLLY_INLINE const_iterator End() const noexcept { return ToArray().end(); }

    CHTHOLLY_INLINE reverse_iterator RBegin() noexcept { return ToArray().rbegin(); }
    CHTHOLLY_INLINE const_reverse_iterator RBegin() const noexcept { return ToArray().rbegin(); }
    CHTHOLLY_INLINE reverse_iterator REnd() noexcept { return ToArray().rend(); }
    CHTHOLLY_INLINE const_reverse_iterator REnd() const noexcept { return ToArray().rend(); }

    CHTHOLLY_INLINE const_iterator CBegin() const noexcept { return Begin(); }
    CHTHOLLY_INLINE const_iterator CEnd() const noexcept { return End(); }
    CHTHOLLY_INLINE const_reverse_iterator CRBegin() const noexcept { return RBegin(); }
    CHTHOLLY_INLINE const_reverse_iterator CREnd() const noexcept { return REnd(); }

    constexpr size_t Size() const noexcept { return N; }
    constexpr size_t MaxSize() const noexcept { return N; }
    constexpr bool Empty() const noexcept { return false; }

    CHTHOLLY_INLINE reference At(size_t i) { return ToArray().at(i); }
    CHTHOLLY_INLINE const_reference At(size_t i) const { return ToArray().at(i); }
    CHTHOLLY_INLINE reference Front() noexcept { return ToArray().front(); }
    CHTHOLLY_INLINE const_reference Front() const noexcept { return ToArray().front(); }
    CHTHOLLY_INLINE reference Back() noexcept { return ToArray().back(); }
    CHTHOLLY_INLINE const_reference Back() const noexcept { return ToArray().back(); }

    CHTHOLLY_INLINE pointer Data() noexcept { return reinterpret_cast<T*>(this); }
    CHTHOLLY_INLINE const_pointer Data() const noexcept { return const_cast<IArray*>(this)->data(); }

    CHTHOLLY_INLINE reference operator[](size_t i) noexcept { return ToArray().at(i); }
    CHTHOLLY_INLINE const_reference operator[](size_t i) const noexcept { return ToArray().at(i); }
};
}


#endif