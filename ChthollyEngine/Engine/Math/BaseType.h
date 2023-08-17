#ifndef _BASE_TYPE_H_
#define _BASE_TYPE_H_

#include "Chtholly.h"

#if defined(__ARM_NEON__)
    #include <arm_neon.h>
#endif

namespace xxd
{
typedef struct { int x, y; } int2; 

typedef struct { int x, y, z; } int3; 

typedef struct { int x, y, z, w; } int4; 

typedef struct { float x, y; } float2; 

typedef struct { float x, y, z; } float3; 

typedef struct { float x, y, z, w; } float4; 

typedef struct { double x, y; } double2; 

typedef struct { double x, y, z; } double3; 

typedef struct { double x, y, z, w; } double4; 

typedef struct { int2 col[2]; } int2x2;

typedef struct { int3 col[2]; } int3x2;

typedef struct { int3 col[3]; } int3x3;

typedef struct { int4 col[3]; } int4x3;

typedef struct { int4 col[4]; } int4x4;

typedef struct { float2 col[2]; } float2x2;

typedef struct { float3 col[2]; } float3x2;

typedef struct { float3 col[3]; } float3x3;

typedef struct { float4 col[3]; } float4x3;

typedef struct { float4 col[4]; } float4x4;

typedef struct { double2 col[2]; } double2x2;

typedef struct { double3 col[2]; } double3x2;

typedef struct { double3 col[3]; } double3x3;

typedef struct { double4 col[3]; } double4x3;

typedef struct { double4 col[4]; } double4x4;

CHTHOLLY_INLINE int2 operator+(const int2& a, const int2& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) + vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE int2 operator+(const int2& a, int2&& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) + vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE int2 operator+(int2&& a, const int2& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) + vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE int2 operator+(int2&& a, int2&& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) + vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE int2 operator-(const int2& a, const int2& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) - vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE int2 operator-(const int2& a, int2&& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) - vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE int2 operator-(int2&& a, const int2& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) - vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE int2 operator-(int2&& a, int2&& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) - vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE int2 operator*(const int2& a, const int2& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) * vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE int2 operator*(const int2& a, int2&& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) * vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE int2 operator*(int2&& a, const int2& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) * vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE int2 operator*(int2&& a, int2&& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) * vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE int2 operator/(const int2& a, const int2& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) / vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE int2 operator/(const int2& a, int2&& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) / vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE int2 operator/(int2&& a, const int2& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) / vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE int2 operator/(int2&& a, int2&& b)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&a.x) / vld1_s32(&b.x);
    return *(int2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}
}

#endif