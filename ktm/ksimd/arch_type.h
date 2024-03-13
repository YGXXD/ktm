#ifndef _KTM_ARCH_TYPE_H_
#define _KTM_ARCH_TYPE_H_

#include "intrin.h"
#include "../traits/type_traits_ext.h"

#define SIMD_INTRINSICS_STRUCT_TYPE(plat, latest, past) \
template<> \
struct intrinsics<eintrin::latest> : intrinsics<eintrin::past> \
{ \
    constexpr static KTM_INLINE uint32_t get_platform() noexcept \
    { \
        return static_cast<uint32_t>(eplatform::plat); \
    } \
    constexpr static KTM_INLINE uint32_t get_support() noexcept \
    { \
        return static_cast<uint32_t>(eintrin::latest) | intrinsics<eintrin::past>::get_support(); \
    } \
    template<eintrin ...Es> \
    constexpr static KTM_INLINE bool is_support() noexcept \
    { \
        return get_support() & (static_cast<uint32_t>(Es) | ...); \
    } \
};

namespace simd
{

enum class eplatform : uint32_t
{
    none = 0,
    arm = 1,
    x86 = 2
};

enum class eintrin : uint32_t
{
    none = 0,
    neon = 1,
    neon64 = 2,
    sse = 4,
    sse2 = 8,
    sse3 = 16,
    sse4_1 = 32,
    sse4_2 = 64
};

template<eintrin MAX>
struct intrinsics
{
    constexpr static KTM_INLINE uint32_t get_platform() noexcept 
    { 
        return static_cast<uint32_t>(eplatform::none); 
    };

    constexpr static KTM_INLINE uint32_t get_support() noexcept 
    { 
        return static_cast<uint32_t>(eintrin::none);
    };

    template<eintrin ...Es>
    constexpr static KTM_INLINE bool is_support() noexcept
    {
        return false;
    };
};

template<eintrin MAX>
using requests_intrin = std::add_lvalue_reference_t<std::add_const_t<intrinsics<MAX>>>;

SIMD_INTRINSICS_STRUCT_TYPE(arm, neon, none)
SIMD_INTRINSICS_STRUCT_TYPE(arm, neon64, neon)

template<eintrin E, typename T, typename = std::enable_if_t<intrinsics<E>::get_support()>>
struct skv64;

template<eintrin E>
struct skv64<E, float, std::enable_if_t<intrinsics<E>::template is_support<eintrin::neon>()>>
{
    using type = float32x2_t;
};

template<eintrin E>
struct skv64<E, int, std::enable_if_t<intrinsics<E>::template is_support<eintrin::neon>()>>
{
    using type = int32x2_t;
};

template<eintrin E, typename T>
using skv64_t = typename skv64<E, T>::type;

template<eintrin E, typename T, typename = std::enable_if_t<intrinsics<E>::get_support()>>
struct skv128;

template<eintrin E>
struct skv128<E, float, std::enable_if_t<intrinsics<E>::template is_support<eintrin::neon>()>>
{
    using type = float32x4_t;
};

template<eintrin E>
struct skv128<E, int, std::enable_if_t<intrinsics<E>::template is_support<eintrin::neon>()>>
{
    using type = int32x4_t;
};

template<eintrin E, typename T>
using skv128_t = typename skv64<E, T>::type;

}

#endif