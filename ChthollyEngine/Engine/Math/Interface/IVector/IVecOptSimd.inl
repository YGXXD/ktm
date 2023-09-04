#ifndef _I_VEC_OPT_SIMD_INL_
#define _I_VEC_OPT_SIMD_INL_

#include "IVecOpt.h"

#ifdef __ARM_NEON__
#include <arm_neon.h>

template<size_t N, class V>
struct ktm::detail::vec_opt_implement::add<N, std::enable_if_t<(N == 3 || N == 4), float>, V>
{
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        vst1q_f32(reinterpret_cast<float*>(&ret), vaddq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y))));
        return ret;
    }
};

#endif

#endif