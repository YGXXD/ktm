#ifndef _KTM_VEC_DATA_SIMD_INL_
#define _KTM_VEC_DATA_SIMD_INL_

#include "vec_data_fwd.h"
#include "../../simd/intrin.h"

#if defined(KTM_SIMD_ARM)

template<>
struct ktm::detail::vec_data_implement::vec_storage<2, float>
{
    typedef float32x2_t type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<3, float>
{
    typedef float32x4_t type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<4, float>
{
    typedef float32x4_t type;
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
        ret.st = neon_shuffle_f32(v.st, v.st, S1, S0);
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
        ret.st = vcopy_laneq_f32(ret.st, 0, v.st, S0);
        ret.st = vcopy_laneq_f32(ret.st, 1, v.st, S1); 
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
        ret.st = neon_shuffleq_f32(v.st, v.st, 3, S2, S1, S0);
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
        ret.st = neon_shuffleq_f32(v.st, v.st, S3, S2, S1, S0);
        return ret;
    }
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<2, int>
{
    typedef int32x2_t type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<3, int>
{
    typedef int32x4_t type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<4, int>
{
    typedef int32x4_t type;
};

#elif defined(KTM_SIMD_X86)

template<>
struct ktm::detail::vec_data_implement::vec_storage<2, float>
{
    typedef __m64 type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<3, float>
{
    typedef __m128 type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<4, float>
{
    typedef __m128 type;
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
        __m128 tmp = _mm_shuffle_ps(v.st, v.st, _MM_SHUFFLE(3, 2, S1, S0));
        _mm_storel_pi(&ret.st, tmp);
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
        ret.st = _mm_shuffle_ps(v.st, v.st, _MM_SHUFFLE(3, S2, S1, S0));
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
        ret.st = _mm_shuffle_ps(v.st, v.st, _MM_SHUFFLE(S3, S2, S1, S0));
        return ret;
    }
};

#if KTM_SIMD_X86 & KTM_SIMD_SSE2_FLAG 

template<>
struct ktm::detail::vec_data_implement::vec_swizzle<2, 2, float>
{
    using V = vec<2, float>;
    using RetV = vec<2, float>;
    template<size_t S0, size_t S1>
    static KTM_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        __m128i tmp = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(&v.st));
        _mm_storel_epi64(reinterpret_cast<__m128i*>(&ret.st), _mm_shuffle_epi32(tmp, _MM_SHUFFLE(3, 2, S1, S0)));
        return ret;
    }
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<2, int>
{
    typedef __m64 type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<3, int>
{
    typedef __m128i type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<4, int>
{
    typedef __m128i type;
};

#endif // KTM_SIMD_X86 & KTM_SIMD_SSE2_FLAG 

#endif

#if defined(KTM_SIMD_ARM) || defined(KTM_SIMD_X86)

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