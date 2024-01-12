#ifndef _KTM_COMMON_INL_
#define _KTM_COMMON_INL_

#include "common_fwd.h"
#include "../../setup.h"
#include "../../type/basic.h"
#include "../../function/arithmetic.h"

template<size_t StepN, size_t N, typename T>
struct ktm::detail::common_implement::elem_move
{
    static_assert(StepN > 0 && StepN < N);
	using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = x[(Ns + StepN) < N ? Ns + StepN : Ns + StepN - N]), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::reduce_add
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        return (x[Ns] + ...);
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::reduce_min
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N - 1>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        if constexpr(sizeof...(Ns))
        {
            T ret = x[0];
            ((ret = ktm::min(ret, x[Ns + 1])), ...);
            return ret;
        }
        else
            return x[0];
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::reduce_max
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N - 1>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE T call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        if constexpr(sizeof...(Ns))
        {
            T ret = x[0];
            ((ret = ktm::max(ret, x[Ns + 1])), ...);
            return ret;
        }
        else
            return x[0];
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::abs
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        if constexpr(std::is_unsigned_v<T>)
            return x;
        else
            return call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::abs(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::min
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::min(x[Ns], y[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::max
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        return call(x, y, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, const V& y, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::max(x[Ns], y[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::clamp
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        return call(v, min, max, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& v, const V& min, const V& max, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::clamp(v[Ns], min[Ns], max[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::floor
{
    using V = vec<N, T>;
    static_assert(std::is_floating_point_v<T>);
    static KTM_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::floor(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::ceil
{
    using V = vec<N, T>;
    static_assert(std::is_floating_point_v<T>);
    static KTM_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::ceil(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::round
{
    using V = vec<N, T>;
    static_assert(std::is_floating_point_v<T>);
    static KTM_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::round(x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::lerp
{
    using V = vec<N, T>;
    static_assert(std::is_floating_point_v<T>);
    static KTM_INLINE V call(const V& x, const V& y, T t) noexcept
    {
        return call(x, y, t, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, const V& y, T t, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::mix(x[Ns], y[Ns], t)), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::mix
{
    using V = vec<N, T>;
    static_assert(std::is_floating_point_v<T>);
    static KTM_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        return call(x, y, t, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, const V& y, const V& t, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::mix(x[Ns], y[Ns], t[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::recip
{
    using V = vec<N, T>;
    static_assert(std::is_floating_point_v<T>);
    static KTM_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = one<T> / x[Ns]), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::step
{
    using V = vec<N, T>;
    static_assert(std::is_floating_point_v<T>);
    static KTM_INLINE V call(const V& edge, const V& x) noexcept
    {
        return call(edge, x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& edge, const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::step(edge[Ns], x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::smoothstep
{
    using V = vec<N, T>;
    static_assert(std::is_floating_point_v<T>);
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        return call(edge0, edge1, x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::smoothstep(edge0[Ns], edge1[Ns], x[Ns])), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::common_implement::fract
{
    using V = vec<N, T>;
    static_assert(std::is_floating_point_v<T>);
    static KTM_INLINE V call(const V& x) noexcept
    {
        return call(x, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static KTM_INLINE V call(const V& x, std::index_sequence<Ns...>) noexcept
    {
        V ret;
        ((ret[Ns] = ktm::fract(x[Ns])), ...);
        return ret;
    }
};

#endif
