#ifndef _KTM_VEC_DATA_SIMD_INL_
#define _KTM_VEC_DATA_SIMD_INL_

#include "vec_data_fwd.h"
#include "../../ksimd/intrin_api.h"

#if KTM_SIMD_ENABLE(KTM_SIMD_NEON)

template<>
struct ktm::detail::vec_data_implement::vec_storage<2, float>
{
    typedef skv64_f32 type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<3, float>
{
    typedef skv128_f32 type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<4, float>
{
    typedef skv128_f32 type;
};

template<>
struct ktm::detail::vec_data_implement::vec_swizzle<2, 2, float>
{
    using V = vec<2, float>;
    using RetV = vec<2, float>;
    template<size_t S0, size_t S1>
    static KTM_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = _shuff64_one_f32(v.st, S1, S0);
        return ret;
    }
};

template<size_t IN>
struct ktm::detail::vec_data_implement::vec_swizzle<2, IN, float, std::enable_if_t<IN == 3 || IN == 4>>
{
    using V = vec<IN, float>;
    using RetV = vec<2, float>;
    template<size_t S0, size_t S1>
    static KTM_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = _cast128_to64_f32(_shuff128_one_f32(v.st, S1, S0, S1, S0))
        return ret;
    }
};

template<size_t IN>
struct ktm::detail::vec_data_implement::vec_swizzle<3, IN, float, std::enable_if_t<IN == 3 || IN == 4>>
{
    using V = vec<IN, float>;
    using RetV = vec<3, float>;
    template<size_t S0, size_t S1, size_t S2>
    static KTM_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = _shuff128_one_f32(v.st, 0, S2, S1, S0);
        return ret;
    }
};

template<>
struct ktm::detail::vec_data_implement::vec_swizzle<4, 4, float>
{
    using V = vec<4, float>;
    using RetV = vec<4, float>;
    template<size_t S0, size_t S1, size_t S2, size_t S3>
    static KTM_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = _shuff128_one_f32(v.st, S3, S2, S1, S0);
        return ret;
    }
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<2, int>
{
    typedef skv64_s32 type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<3, int>
{
    typedef skv64_s32 type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<4, int>
{
    typedef skv64_s32 type;
};

#endif

#if KTM_SIMD_SUPPORT

template<size_t IN, typename T>
struct ktm::detail::vec_data_implement::vec_swizzle<2, IN, T, std::enable_if_t<sizeof(T) == sizeof(float) && !std::is_same_v<T, float> && IN >=2 && IN <= 4>>
{
    using V = vec<IN, T>;
    using RetV = vec<2, T>;
    using FV = vec<IN, float>;
    using FRetV = vec<2, float>;
    template<size_t S0, size_t S1>
    static KTM_INLINE RetV call(const V& v) noexcept
    {
        FRetV ret = vec_swizzle<2, IN, float>::template call<S0, S1>(reinterpret_cast<const FV&>(v)); 
        return *reinterpret_cast<RetV*>(&ret);
    }
};

template<size_t IN, typename T>
struct ktm::detail::vec_data_implement::vec_swizzle<3, IN, T, std::enable_if_t<sizeof(T) == sizeof(float) && !std::is_same_v<T, float> && IN >=3 && IN <= 4>>
{
    using V = vec<IN, T>;
    using RetV = vec<3, T>;
    using FV = vec<IN, float>;
    using FRetV = vec<3, float>;
    template<size_t S0, size_t S1, size_t S2>
    static KTM_INLINE RetV call(const V& v) noexcept
    {
        FRetV ret = vec_swizzle<3, IN, float>::template call<S0, S1, S2>(reinterpret_cast<const FV&>(v)); 
        return *reinterpret_cast<RetV*>(&ret);
    }
};

template<typename T>
struct ktm::detail::vec_data_implement::vec_swizzle<4, 4, T, std::enable_if_t<sizeof(T) == sizeof(float) && !std::is_same_v<T, float>>>
{
    using V = vec<4, T>;
    using RetV = vec<4, T>;
    using FV = vec<4, float>;
    using FRetV = vec<4, float>;
    template<size_t S0, size_t S1, size_t S2, size_t S3>
    static KTM_INLINE RetV call(const V& v) noexcept
    {
        FRetV ret = vec_swizzle<4, 4, float>::template call<S0, S1, S2, S3>(reinterpret_cast<const FV&>(v)); 
        return *reinterpret_cast<RetV*>(&ret);
    }
};

#endif

#endif