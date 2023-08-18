#ifndef _BASE_TYPE_H_
#define _BASE_TYPE_H_

#include "Chtholly.h"
#include <simd/simd.h>

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

CHTHOLLY_INLINE int2 MakeInt2(int x, int y) { return { x, y }; }
CHTHOLLY_INLINE int2 MakeInt2(const int3& v3) { return { v3.x, v3.y}; }
CHTHOLLY_INLINE int2 MakeInt2(int3&& v3) { return { v3.x, v3.y}; }
CHTHOLLY_INLINE int2 MakeInt2(const int4& v4) { return { v4.x, v4.y}; }
CHTHOLLY_INLINE int2 MakeInt2(int4&& v4) { return { v4.x, v4.y}; }
CHTHOLLY_INLINE int3 MakeInt3(const int2& v2, int z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE int3 MakeInt3(int2&& v2, int z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE int3 MakeInt3(int x, int y, int z) { return { x, y, z }; }
CHTHOLLY_INLINE int3 MakeInt3(const int4& v4) { return { v4.x, v4.y, v4.z}; }
CHTHOLLY_INLINE int3 MakeInt3(int4&& v4) { return { v4.x, v4.y, v4.z}; }
CHTHOLLY_INLINE int4 MakeInt4(const int3& v3, int w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE int4 MakeInt4(int3&& v3, int w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE int4 MakeInt4(const int2& v2, int z, int w) { return { v2.x, v2.y, z, w }; }
CHTHOLLY_INLINE int4 MakeInt4(int2&& v2, int z, int w) { return { v2.x, v2.y, z, w }; }
CHTHOLLY_INLINE int4 MakeInt4(int x, int y, int z, int w) { return { x, y, z, w }; }

CHTHOLLY_INLINE float2 MakeFloat2(float x, float y) { return { x, y }; }
CHTHOLLY_INLINE float2 MakeFloat2(const float3& v3) { return { v3.x, v3.y}; }
CHTHOLLY_INLINE float2 MakeFloat2(float3&& v3) { return { v3.x, v3.y}; }
CHTHOLLY_INLINE float2 MakeFloat2(const float4& v4) { return { v4.x, v4.y}; }
CHTHOLLY_INLINE float2 MakeFloat2(float4&& v4) { return { v4.x, v4.y}; }
CHTHOLLY_INLINE float3 MakeFloat3(const float2& v2, float z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE float3 MakeFloat3(float2&& v2, float z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE float3 MakeFloat3(float x, float y, float z) { return { x, y, z }; }
CHTHOLLY_INLINE float3 MakeFloat3(const float4& v4) { return { v4.x, v4.y, v4.z}; }
CHTHOLLY_INLINE float3 MakeFloat3(float4&& v4) { return { v4.x, v4.y, v4.z}; }
CHTHOLLY_INLINE float4 MakeFloat4(const float3& v3, float w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE float4 MakeFloat4(float3&& v3, float w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE float4 MakeFloat4(const float2& v2, float z, float w) { return { v2.x, v2.y, z, w }; }
CHTHOLLY_INLINE float4 MakeFloat4(float2&& v2, float z, float w) { return { v2.x, v2.y, z, w }; }
CHTHOLLY_INLINE float4 MakeFloat4(float x, float y, float z, float w) { return { x, y, z, w }; }

CHTHOLLY_INLINE double2 MakeDouble2(double x, double y) { return { x, y }; }
CHTHOLLY_INLINE double2 MakeDouble2(const double3& v3) { return { v3.x, v3.y}; }
CHTHOLLY_INLINE double2 MakeDouble2(double3&& v3) { return { v3.x, v3.y}; }
CHTHOLLY_INLINE double2 MakeDouble2(const double4& v4) { return { v4.x, v4.y}; }
CHTHOLLY_INLINE double2 MakeDouble2(double4&& v4) { return { v4.x, v4.y}; }
CHTHOLLY_INLINE double3 MakeDouble3(const double2& v2, double z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE double3 MakeDouble3(double2&& v2, double z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE double3 MakeDouble3(double x, double y, double z) { return { x, y, z }; }
CHTHOLLY_INLINE double3 MakeDouble3(const double4& v4) { return { v4.x, v4.y, v4.z}; }
CHTHOLLY_INLINE double3 MakeDouble3(double4&& v4) { return { v4.x, v4.y, v4.z}; }
CHTHOLLY_INLINE double4 MakeDouble4(const double3& v3, double w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE double4 MakeDouble4(double3&& v3, double w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE double4 MakeDouble4(const double2& v2, double z, double w) { return { v2.x, v2.y, z, w }; }
CHTHOLLY_INLINE double4 MakeDouble4(double2&& v2, double z, double w) { return { v2.x, v2.y, z, w }; }
CHTHOLLY_INLINE double4 MakeDouble4(double x, double y, double z, double w) { return { x, y, z, w }; }

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

CHTHOLLY_INLINE int2 operator+(const int2& v, int a)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) + vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE int2 operator+(int2&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) + vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE int2 operator+(int a, const int2& v)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) + vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE int2 operator+(int a, int2&& v)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) + vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE int2 operator-(const int2& v, int a)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) - vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x - a, v.y - a };
#endif
}

CHTHOLLY_INLINE int2 operator-(int2&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) - vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x - a, v.y - a };
#endif
}

CHTHOLLY_INLINE int2 operator*(const int2& v, int a)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) * vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE int2 operator*(int2&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) * vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE int2 operator*(int a, const int2& v)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) * vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE int2 operator*(int a, int2&& v)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) * vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE int2 operator/(const int2& v, int a)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) / vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x / a, v.y / a };
#endif
}

CHTHOLLY_INLINE int2 operator/(int2&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&v.x) / vdup_n_s32(a);
    return *(int2*)&simd_ret;
#else   
    return { v.x / a, v.y / a };
#endif
}

CHTHOLLY_INLINE int2& operator+=(int2& l, const int2& r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) + vld1_s32(&r.x);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator+=(int2& l, int2&& r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) + vld1_s32(&r.x);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator-=(int2& l, const int2& r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) - vld1_s32(&r.x);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator-=(int2& l, int2&& r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) - vld1_s32(&r.x);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator*=(int2& l, const int2& r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) * vld1_s32(&r.x);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator*=(int2& l, int2&& r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) * vld1_s32(&r.x);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator/=(int2& l, const int2& r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) / vld1_s32(&r.x);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator/=(int2& l, int2&& r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) / vld1_s32(&r.x);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator+=(int2& l, int r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) + vdup_n_s32(r);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x += r;
    l.y += r;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator-=(int2& l, int r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) - vdup_n_s32(r);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r;
    l.y -= r;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator*=(int2& l, int r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) * vdup_n_s32(r);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r;
    l.y *= r;
    return l;
#endif
}

CHTHOLLY_INLINE int2& operator/=(int2& l, int r)
{
#if defined(__ARM_NEON__)
    int32x2_t simd_ret = vld1_s32(&l.x) / vdup_n_s32(r);
    vst1_s32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r;
    l.y /= r;
    return l;
#endif
}

CHTHOLLY_INLINE int3 operator+(const int3& a, const int3& b)
{
#if defined(__ARM_NEON__)
	int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } + (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE int3 operator+(const int3& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } + (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE int3 operator+(int3&& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } + (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE int3 operator+(int3&& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } + (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE int3 operator-(const int3& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } - (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE int3 operator-(const int3& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } - (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE int3 operator-(int3&& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } - (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE int3 operator-(int3&& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } - (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE int3 operator*(const int3& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } * (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE int3 operator*(const int3& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } * (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE int3 operator*(int3&& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } * (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE int3 operator*(int3&& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } * (int32x4_t){ b.x, b.y, b.z, 0 };
    return *(int3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE int3 operator/(const int3& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } / (int32x4_t){ b.x, b.y, b.z, 1 };
    return *(int3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE int3 operator/(const int3& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } / (int32x4_t){ b.x, b.y, b.z, 1 };
    return *(int3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE int3 operator/(int3&& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } / (int32x4_t){ b.x, b.y, b.z, 1 };
    return *(int3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE int3 operator/(int3&& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ a.x, a.y, a.z, 0 } / (int32x4_t){ b.x, b.y, b.z, 1 };
    return *(int3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE int3 operator+(const int3& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} + vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE int3 operator+(int3&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} + vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE int3 operator+(int a, const int3& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} + vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE int3 operator+(int a, int3&& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} + vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE int3 operator-(const int3& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} - vdupq_n_s32(a);     
    return *(int3*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a };
#endif
}

CHTHOLLY_INLINE int3 operator-(int3&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} - vdupq_n_s32(a);  
    return *(int3*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a };
#endif
}

CHTHOLLY_INLINE int3 operator*(const int3& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} * vdupq_n_s32(a);     
    return *(int3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE int3 operator*(int3&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} * vdupq_n_s32(a);     
    return *(int3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE int3 operator*(int a, const int3& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} * vdupq_n_s32(a);     
    return *(int3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE int3 operator*(int a, int3&& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} * vdupq_n_s32(a);     
    return *(int3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE int3 operator/(const int3& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} / vdupq_n_s32(a);     
    return *(int3*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a };
#endif
}

CHTHOLLY_INLINE int3 operator/(int3&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ v.x, v.y, v.z, 0} / vdupq_n_s32(a);     
    return *(int3*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a };
#endif
}

CHTHOLLY_INLINE int3& operator+=(int3& l, const int3& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } + (int32x4_t){ r.x, r.y, r.z, 0 };
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator+=(int3& l, int3&& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } + (int32x4_t){ r.x, r.y, r.z, 0 };
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator-=(int3& l, const int3& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } - (int32x4_t){ r.x, r.y, r.z, 0 };
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator-=(int3& l, int3&& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } - (int32x4_t){ r.x, r.y, r.z, 0 };
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator*=(int3& l, const int3& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } * (int32x4_t){ r.x, r.y, r.z, 0 };
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator*=(int3& l, int3&& r)
{
#if defined(__ARM_NEON__)
     int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } * (int32x4_t){ r.x, r.y, r.z, 0 };
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator/=(int3& l, const int3& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } / (int32x4_t){ r.x, r.y, r.z, 1 };
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator/=(int3& l, int3&& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } / (int32x4_t){ r.x, r.y, r.z, 1 };
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator+=(int3& l, int r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } + vdupq_n_s32(r);
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x += r;
    l.y += r;
    l.z += r;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator-=(int3& l, int r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } - vdupq_n_s32(r);
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x -= r;
    l.y -= r;
    l.z -= r;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator*=(int3& l, int r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } * vdupq_n_s32(r);
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x *= r;
    l.y *= r;
    l.z *= r;
    return l;
#endif
}

CHTHOLLY_INLINE int3& operator/=(int3& l, int r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = (int32x4_t){ l.x, l.y, l.z, 0 } / vdupq_n_s32(r);
    vst1_s32(&l.x, vget_low_s32(simd_ret));
    vst1_lane_s32(&l.z, vget_high_s32(simd_ret), 0);
    return l;
#else   
    l.x /= r;
    l.y /= r;
    l.z /= r;
    return l;
#endif
}

CHTHOLLY_INLINE int4 operator+(const int4& a, const int4& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) + vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE int4 operator+(const int4& a, int4&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) + vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE int4 operator+(int4&& a, const int4& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) + vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE int4 operator+(int4&& a, int4&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) + vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE int4 operator-(const int4& a, const int4& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) - vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE int4 operator-(const int4& a, int4&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) - vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE int4 operator-(int4&& a, const int4& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) - vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE int4 operator-(int4&& a, int4&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) - vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE int4 operator*(const int4& a, const int4& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) * vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE int4 operator*(const int4& a, int4&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) * vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE int4 operator*(int4&& a, const int4& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) * vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE int4 operator*(int4&& a, int4&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) * vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE int4 operator/(const int4& a, const int4& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) / vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE int4 operator/(const int4& a, int4&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) / vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE int4 operator/(int4&& a, const int4& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) / vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE int4 operator/(int4&& a, int4&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&a.x) / vld1q_s32(&b.x);
    return *(int4*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE int4 operator+(const int4& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) + vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE int4 operator+(int4&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) + vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE int4 operator+(int a, const int4& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) + vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE int4 operator+(int a, int4&& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) + vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE int4 operator-(const int4& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) - vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a, v.w - a };
#endif
}

CHTHOLLY_INLINE int4 operator-(int4&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) - vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a, v.w - a };
#endif
}

CHTHOLLY_INLINE int4 operator*(const int4& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) * vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a, v.w * a};
#endif
}

CHTHOLLY_INLINE int4 operator*(int4&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) * vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a, v.w * a};
#endif
}

CHTHOLLY_INLINE int4 operator*(int a, const int4& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) * vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a, v.w * a};
#endif
}

CHTHOLLY_INLINE int4 operator*(int a, int4&& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) * vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a, v.w * a};
#endif
}

CHTHOLLY_INLINE int4 operator/(const int4& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) / vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a, v.w / a };
#endif
}

CHTHOLLY_INLINE int4 operator/(int4&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&v.x) / vdupq_n_s32(a);
    return *(int4*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a, v.w / a };
#endif
}

CHTHOLLY_INLINE int4& operator+=(int4& l, const int4& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) + vld1q_s32(&r.x);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    l.w += r.w;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator+=(int4& l, int4&& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) + vld1q_s32(&r.x);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    l.w += r.w;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator-=(int4& l, const int4& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) - vld1q_s32(&r.x);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    l.w -= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator-=(int4& l, int4&& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) - vld1q_s32(&r.x);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    l.w -= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator*=(int4& l, const int4& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) * vld1q_s32(&r.x);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    l.w *= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator*=(int4& l, int4&& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) * vld1q_s32(&r.x);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    l.w *= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator/=(int4& l, const int4& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) / vld1q_s32(&r.x);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    l.w /= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator/=(int4& l, int4&& r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) / vld1q_s32(&r.x);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    l.w /= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator+=(int4& l, int r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) + vdupq_n_s32(r);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x += r;
    l.y += r;
    l.z += r;
    l.w += r;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator-=(int4& l, int r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) - vdupq_n_s32(r);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r;
    l.y -= r;
    l.z -= r;
    l.w -= r;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator*=(int4& l, int r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) * vdupq_n_s32(r);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r;
    l.y *= r;
    l.z *= r;
    l.w *= r;
    return l;
#endif
}

CHTHOLLY_INLINE int4& operator/=(int4& l, int r)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vld1q_s32(&l.x) / vdupq_n_s32(r);
    vst1q_s32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r;
    l.y /= r;
    l.z /= r;
    l.w /= r;
    return l;
#endif
}


CHTHOLLY_INLINE float2 operator+(const float2& a, const float2& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) + vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE float2 operator+(const float2& a, float2&& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) + vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE float2 operator+(float2&& a, const float2& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) + vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE float2 operator+(float2&& a, float2&& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) + vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE float2 operator-(const float2& a, const float2& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) - vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE float2 operator-(const float2& a, float2&& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) - vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE float2 operator-(float2&& a, const float2& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) - vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE float2 operator-(float2&& a, float2&& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) - vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE float2 operator*(const float2& a, const float2& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) * vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE float2 operator*(const float2& a, float2&& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) * vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE float2 operator*(float2&& a, const float2& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) * vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE float2 operator*(float2&& a, float2&& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) * vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE float2 operator/(const float2& a, const float2& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) / vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE float2 operator/(const float2& a, float2&& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) / vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE float2 operator/(float2&& a, const float2& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) / vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE float2 operator/(float2&& a, float2&& b)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&a.x) / vld1_f32(&b.x);
    return *(float2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE float2 operator+(const float2& v, float a)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) + vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE float2 operator+(float2&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) + vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE float2 operator+(float a, const float2& v)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) + vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE float2 operator+(float a, float2&& v)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) + vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE float2 operator-(const float2& v, float a)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) - vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x - a, v.y - a };
#endif
}

CHTHOLLY_INLINE float2 operator-(float2&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) - vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x - a, v.y - a };
#endif
}

CHTHOLLY_INLINE float2 operator*(const float2& v, float a)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) * vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE float2 operator*(float2&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) * vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE float2 operator*(float a, const float2& v)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) * vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE float2 operator*(float a, float2&& v)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) * vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE float2 operator/(const float2& v, float a)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) / vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x / a, v.y / a };
#endif
}

CHTHOLLY_INLINE float2 operator/(float2&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&v.x) / vdup_n_f32(a);
    return *(float2*)&simd_ret;
#else   
    return { v.x / a, v.y / a };
#endif
}

CHTHOLLY_INLINE float2& operator+=(float2& l, const float2& r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) + vld1_f32(&r.x);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator+=(float2& l, float2&& r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) + vld1_f32(&r.x);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator-=(float2& l, const float2& r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) - vld1_f32(&r.x);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator-=(float2& l, float2&& r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) - vld1_f32(&r.x);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator*=(float2& l, const float2& r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) * vld1_f32(&r.x);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator*=(float2& l, float2&& r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) * vld1_f32(&r.x);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator/=(float2& l, const float2& r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) / vld1_f32(&r.x);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator/=(float2& l, float2&& r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) / vld1_f32(&r.x);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator+=(float2& l, float r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) + vdup_n_f32(r);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x += r;
    l.y += r;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator-=(float2& l, float r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) - vdup_n_f32(r);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r;
    l.y -= r;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator*=(float2& l, float r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) * vdup_n_f32(r);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r;
    l.y *= r;
    return l;
#endif
}

CHTHOLLY_INLINE float2& operator/=(float2& l, float r)
{
#if defined(__ARM_NEON__)
    float32x2_t simd_ret = vld1_f32(&l.x) / vdup_n_f32(r);
    vst1_f32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r;
    l.y /= r;
    return l;
#endif
}

CHTHOLLY_INLINE float3 operator+(const float3& a, const float3& b)
{
#if defined(__ARM_NEON__)
	float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } + (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE float3 operator+(const float3& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } + (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE float3 operator+(float3&& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } + (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE float3 operator+(float3&& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } + (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE float3 operator-(const float3& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } - (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE float3 operator-(const float3& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } - (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE float3 operator-(float3&& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } - (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE float3 operator-(float3&& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } - (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE float3 operator*(const float3& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } * (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE float3 operator*(const float3& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } * (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE float3 operator*(float3&& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } * (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE float3 operator*(float3&& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } * (float32x4_t){ b.x, b.y, b.z, 0 };
    return *(float3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE float3 operator/(const float3& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } / (float32x4_t){ b.x, b.y, b.z, 1 };
    return *(float3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE float3 operator/(const float3& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } / (float32x4_t){ b.x, b.y, b.z, 1 };
    return *(float3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE float3 operator/(float3&& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } / (float32x4_t){ b.x, b.y, b.z, 1 };
    return *(float3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE float3 operator/(float3&& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ a.x, a.y, a.z, 0 } / (float32x4_t){ b.x, b.y, b.z, 1 };
    return *(float3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE float3 operator+(const float3& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} + vdupq_n_f32(a);   
    return *(float3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE float3 operator+(float3&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} + vdupq_n_f32(a);   
    return *(float3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE float3 operator+(float a, const float3& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} + vdupq_n_f32(a);   
    return *(float3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE float3 operator+(float a, float3&& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} + vdupq_n_f32(a);   
    return *(float3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE float3 operator-(const float3& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} - vdupq_n_f32(a);     
    return *(float3*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a };
#endif
}

CHTHOLLY_INLINE float3 operator-(float3&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} - vdupq_n_f32(a);  
    return *(float3*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a };
#endif
}

CHTHOLLY_INLINE float3 operator*(const float3& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} * vdupq_n_f32(a);     
    return *(float3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE float3 operator*(float3&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} * vdupq_n_f32(a);     
    return *(float3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE float3 operator*(float a, const float3& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} * vdupq_n_f32(a);     
    return *(float3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE float3 operator*(float a, float3&& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} * vdupq_n_f32(a);     
    return *(float3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE float3 operator/(const float3& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} / vdupq_n_f32(a);     
    return *(float3*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a };
#endif
}

CHTHOLLY_INLINE float3 operator/(float3&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ v.x, v.y, v.z, 0} / vdupq_n_f32(a);     
    return *(float3*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a };
#endif
}

CHTHOLLY_INLINE float3& operator+=(float3& l, const float3& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } + (float32x4_t){ r.x, r.y, r.z, 0 };
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator+=(float3& l, float3&& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } + (float32x4_t){ r.x, r.y, r.z, 0 };
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator-=(float3& l, const float3& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } - (float32x4_t){ r.x, r.y, r.z, 0 };
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator-=(float3& l, float3&& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } - (float32x4_t){ r.x, r.y, r.z, 0 };
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator*=(float3& l, const float3& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } * (float32x4_t){ r.x, r.y, r.z, 0 };
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator*=(float3& l, float3&& r)
{
#if defined(__ARM_NEON__)
     float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } * (float32x4_t){ r.x, r.y, r.z, 0 };
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator/=(float3& l, const float3& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } / (float32x4_t){ r.x, r.y, r.z, 1 };
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator/=(float3& l, float3&& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } / (float32x4_t){ r.x, r.y, r.z, 1 };
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator+=(float3& l, float r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } + vdupq_n_f32(r);
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x += r;
    l.y += r;
    l.z += r;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator-=(float3& l, float r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } - vdupq_n_f32(r);
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x -= r;
    l.y -= r;
    l.z -= r;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator*=(float3& l, float r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } * vdupq_n_f32(r);
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x *= r;
    l.y *= r;
    l.z *= r;
    return l;
#endif
}

CHTHOLLY_INLINE float3& operator/=(float3& l, float r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = (float32x4_t){ l.x, l.y, l.z, 0 } / vdupq_n_f32(r);
    vst1_f32(&l.x, vget_low_f32(simd_ret));
    vst1_lane_f32(&l.z, vget_high_f32(simd_ret), 0);
    return l;
#else   
    l.x /= r;
    l.y /= r;
    l.z /= r;
    return l;
#endif
}

CHTHOLLY_INLINE float4 operator+(const float4& a, const float4& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) + vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE float4 operator+(const float4& a, float4&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) + vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE float4 operator+(float4&& a, const float4& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) + vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE float4 operator+(float4&& a, float4&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) + vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE float4 operator-(const float4& a, const float4& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) - vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE float4 operator-(const float4& a, float4&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) - vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE float4 operator-(float4&& a, const float4& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) - vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE float4 operator-(float4&& a, float4&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) - vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE float4 operator*(const float4& a, const float4& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) * vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE float4 operator*(const float4& a, float4&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) * vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE float4 operator*(float4&& a, const float4& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) * vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE float4 operator*(float4&& a, float4&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) * vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE float4 operator/(const float4& a, const float4& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) / vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE float4 operator/(const float4& a, float4&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) / vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE float4 operator/(float4&& a, const float4& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) / vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE float4 operator/(float4&& a, float4&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&a.x) / vld1q_f32(&b.x);
    return *(float4*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE float4 operator+(const float4& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) + vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE float4 operator+(float4&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) + vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE float4 operator+(float a, const float4& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) + vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE float4 operator+(float a, float4&& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) + vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE float4 operator-(const float4& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) - vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a, v.w - a };
#endif
}

CHTHOLLY_INLINE float4 operator-(float4&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) - vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a, v.w - a };
#endif
}

CHTHOLLY_INLINE float4 operator*(const float4& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) * vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a, v.w * a};
#endif
}

CHTHOLLY_INLINE float4 operator*(float4&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) * vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a, v.w * a};
#endif
}

CHTHOLLY_INLINE float4 operator*(float a, const float4& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) * vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a, v.w * a};
#endif
}

CHTHOLLY_INLINE float4 operator*(float a, float4&& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) * vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a, v.w * a};
#endif
}

CHTHOLLY_INLINE float4 operator/(const float4& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) / vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a, v.w / a };
#endif
}

CHTHOLLY_INLINE float4 operator/(float4&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&v.x) / vdupq_n_f32(a);
    return *(float4*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a, v.w / a };
#endif
}

CHTHOLLY_INLINE float4& operator+=(float4& l, const float4& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) + vld1q_f32(&r.x);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    l.w += r.w;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator+=(float4& l, float4&& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) + vld1q_f32(&r.x);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    l.w += r.w;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator-=(float4& l, const float4& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) - vld1q_f32(&r.x);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    l.w -= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator-=(float4& l, float4&& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) - vld1q_f32(&r.x);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    l.w -= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator*=(float4& l, const float4& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) * vld1q_f32(&r.x);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    l.w *= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator*=(float4& l, float4&& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) * vld1q_f32(&r.x);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    l.w *= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator/=(float4& l, const float4& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) / vld1q_f32(&r.x);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    l.w /= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator/=(float4& l, float4&& r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) / vld1q_f32(&r.x);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    l.w /= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator+=(float4& l, float r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) + vdupq_n_f32(r);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x += r;
    l.y += r;
    l.z += r;
    l.w += r;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator-=(float4& l, float r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) - vdupq_n_f32(r);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x -= r;
    l.y -= r;
    l.z -= r;
    l.w -= r;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator*=(float4& l, float r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) * vdupq_n_f32(r);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x *= r;
    l.y *= r;
    l.z *= r;
    l.w *= r;
    return l;
#endif
}

CHTHOLLY_INLINE float4& operator/=(float4& l, float r)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vld1q_f32(&l.x) / vdupq_n_f32(r);
    vst1q_f32(&l.x, simd_ret);
    return l;
#else   
    l.x /= r;
    l.y /= r;
    l.z /= r;
    l.w /= r;
    return l;
#endif
}

CHTHOLLY_INLINE double2 operator+(const double2& a, const double2& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE double2 operator+(const double2& a, double2&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE double2 operator+(double2&& a, const double2& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE double2 operator+(double2&& a, double2&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y };
#endif
}

CHTHOLLY_INLINE double2 operator-(const double2& a, const double2& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE double2 operator-(const double2& a, double2&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE double2 operator-(double2&& a, const double2& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE double2 operator-(double2&& a, double2&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y };
#endif
}

CHTHOLLY_INLINE double2 operator*(const double2& a, const double2& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE double2 operator*(const double2& a, double2&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE double2 operator*(double2&& a, const double2& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE double2 operator*(double2&& a, double2&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y };
#endif
}

CHTHOLLY_INLINE double2 operator/(const double2& a, const double2& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE double2 operator/(const double2& a, double2&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE double2 operator/(double2&& a, const double2& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE double2 operator/(double2&& a, double2&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    return *(double2*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y };
#endif
}

CHTHOLLY_INLINE double2 operator+(const double2& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) + vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE double2 operator+(double2&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) + vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE double2 operator+(double a, const double2& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) + vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE double2 operator+(double a, double2&& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) + vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x + a, v.y + a };
#endif
}

CHTHOLLY_INLINE double2 operator-(const double2& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) - vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x - a, v.y - a };
#endif
}

CHTHOLLY_INLINE double2 operator-(double2&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) - vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x - a, v.y - a };
#endif
}

CHTHOLLY_INLINE double2 operator*(const double2& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) * vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE double2 operator*(double2&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) * vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE double2 operator*(double a, const double2& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) * vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE double2 operator*(double a, double2&& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) * vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x * a, v.y * a };
#endif
}

CHTHOLLY_INLINE double2 operator/(const double2& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) / vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x / a, v.y / a };
#endif
}

CHTHOLLY_INLINE double2 operator/(double2&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&v.x) / vdupq_n_f64(a);
    return *(double2*)&simd_ret;
#else   
    return { v.x / a, v.y / a };
#endif
}

CHTHOLLY_INLINE double2& operator+=(double2& l, const double2& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) + vld1q_f64(&r.x);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator+=(double2& l, double2&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) + vld1q_f64(&r.x);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator-=(double2& l, const double2& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) - vld1q_f64(&r.x);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator-=(double2& l, double2&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) - vld1q_f64(&r.x);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator*=(double2& l, const double2& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) * vld1q_f64(&r.x);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator*=(double2& l, double2&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) * vld1q_f64(&r.x);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator/=(double2& l, const double2& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) / vld1q_f64(&r.x);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator/=(double2& l, double2&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) / vld1q_f64(&r.x);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator+=(double2& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) + vdupq_n_f64(r);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x += r;
    l.y += r;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator-=(double2& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) - vdupq_n_f64(r);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x -= r;
    l.y -= r;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator*=(double2& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) * vdupq_n_f64(r);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x *= r;
    l.y *= r;
    return l;
#endif
}

CHTHOLLY_INLINE double2& operator/=(double2& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret = vld1q_f64(&l.x) / vdupq_n_f64(r);
    vst1q_f64(&l.x, simd_ret);
    return l;
#else   
    l.x /= r;
    l.y /= r;
    return l;
#endif
}

CHTHOLLY_INLINE double3 operator+(const double3& a, const double3& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) + vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE double3 operator+(const double3& a, double3&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) + vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE double3 operator+(double3&& a, const double3& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) + vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE double3 operator+(double3&& a, double3&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) + vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE double3 operator-(const double3& a, const double3& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) - vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE double3 operator-(const double3& a, double3&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) - vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE double3 operator-(double3&& a, const double3& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) - vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE double3 operator-(double3&& a, double3&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) - vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE double3 operator*(const double3& a, const double3& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) * vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE double3 operator*(const double3& a, double3&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) * vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE double3 operator*(double3&& a, const double3& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) * vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE double3 operator*(double3&& a, double3&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) * vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE double3 operator/(const double3& a, const double3& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) / vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE double3 operator/(const double3& a, double3&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) / vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE double3 operator/(double3&& a, const double3& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) / vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE double3 operator/(double3&& a, double3&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    float64x1_t simd_ret_high = vld1_f64(&a.z) / vld1_f64(&b.z);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE double3 operator+(const double3& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) + vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) + vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x + a, v.y + a , v.z + a };
#endif
}

CHTHOLLY_INLINE double3 operator+(double3&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) + vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) + vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x + a, v.y + a , v.z + a };
#endif
}

CHTHOLLY_INLINE double3 operator+(double a, const double3& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) + vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) + vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x + a, v.y + a , v.z + a };
#endif
}

CHTHOLLY_INLINE double3 operator+(double a, double3&& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) + vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) + vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x + a, v.y + a , v.z + a };
#endif
}

CHTHOLLY_INLINE double3 operator-(const double3& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) - vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) - vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x - a, v.y - a , v.z - a };
#endif
}

CHTHOLLY_INLINE double3 operator-(double3&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) - vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) - vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x - a, v.y - a , v.z - a };
#endif
}

CHTHOLLY_INLINE double3 operator*(const double3& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) * vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) * vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x * a, v.y * a , v.z * a };
#endif
}

CHTHOLLY_INLINE double3 operator*(double3&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) * vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) * vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x * a, v.y * a , v.z * a };
#endif
}

CHTHOLLY_INLINE double3 operator*(double a, const double3& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) * vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) * vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x * a, v.y * a , v.z * a };
#endif
}

CHTHOLLY_INLINE double3 operator*(double a, double3&& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) * vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) * vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x * a, v.y * a , v.z * a };
#endif
}

CHTHOLLY_INLINE double3 operator/(const double3& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) / vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) / vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a };
#endif
}

CHTHOLLY_INLINE double3 operator/(double3&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) / vdupq_n_f64(a);
    float64x1_t simd_ret_high = vld1_f64(&v.z) / vdup_n_f64(a);
    double3 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a };
#endif
}

CHTHOLLY_INLINE double3& operator+=(double3& l, const double3& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) + vld1q_f64(&r.x);
    float64x1_t simd_ret_high = vld1_f64(&l.z) + vld1_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator+=(double3& l, double3&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) + vld1q_f64(&r.x);
    float64x1_t simd_ret_high = vld1_f64(&l.z) + vld1_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator-=(double3& l, const double3& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) - vld1q_f64(&r.x);
    float64x1_t simd_ret_high = vld1_f64(&l.z) - vld1_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator-=(double3& l, double3&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) - vld1q_f64(&r.x);
    float64x1_t simd_ret_high = vld1_f64(&l.z) - vld1_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator*=(double3& l, const double3& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) * vld1q_f64(&r.x);
    float64x1_t simd_ret_high = vld1_f64(&l.z) * vld1_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator*=(double3& l, double3&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) * vld1q_f64(&r.x);
    float64x1_t simd_ret_high = vld1_f64(&l.z) * vld1_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator/=(double3& l, const double3& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) / vld1q_f64(&r.x);
    float64x1_t simd_ret_high = vld1_f64(&l.z) / vld1_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator/=(double3& l, double3&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) / vld1q_f64(&r.x);
    float64x1_t simd_ret_high = vld1_f64(&l.z) / vld1_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator+=(double3& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) + vdupq_n_f64(r);
    float64x1_t simd_ret_high = vld1_f64(&l.z) + vdup_n_f64(r);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x += r;
    l.y += r;
    l.z += r;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator-=(double3& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) - vdupq_n_f64(r);
    float64x1_t simd_ret_high = vld1_f64(&l.z) - vdup_n_f64(r);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x -= r;
    l.y -= r;
    l.z -= r;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator*=(double3& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) * vdupq_n_f64(r);
    float64x1_t simd_ret_high = vld1_f64(&l.z) * vdup_n_f64(r);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x *= r;
    l.y *= r;
    l.z *= r;
    return l;
#endif
}

CHTHOLLY_INLINE double3& operator/=(double3& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) / vdupq_n_f64(r);
    float64x1_t simd_ret_high = vld1_f64(&l.z) / vdup_n_f64(r);
    vst1q_f64(&l.x, simd_ret_low);
    vst1_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x /= r;
    l.y /= r;
    l.z /= r;
    return l;
#endif
}

CHTHOLLY_INLINE double4 operator+(const double4& a, const double4& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) + vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE double4 operator+(const double4& a, double4&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) + vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE double4 operator+(double4&& a, const double4& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) + vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE double4 operator+(double4&& a, double4&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) + vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) + vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

CHTHOLLY_INLINE double4 operator-(const double4& a, const double4& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) - vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE double4 operator-(const double4& a, double4&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) - vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE double4 operator-(double4&& a, const double4& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) - vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE double4 operator-(double4&& a, double4&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) - vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) - vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

CHTHOLLY_INLINE double4 operator*(const double4& a, const double4& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) * vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE double4 operator*(const double4& a, double4&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) * vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE double4 operator*(double4&& a, const double4& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) * vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE double4 operator*(double4&& a, double4&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) * vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) * vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

CHTHOLLY_INLINE double4 operator/(const double4& a, const double4& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) / vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE double4 operator/(const double4& a, double4&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) / vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE double4 operator/(double4&& a, const double4& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) / vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE double4 operator/(double4&& a, double4&& b)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&a.x) / vld1q_f64(&b.x);
    float64x2_t simd_ret_high = vld1q_f64(&a.z) / vld1q_f64(&b.z);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

CHTHOLLY_INLINE double4 operator+(const double4& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) + vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) + vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x + a, v.y + a , v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE double4 operator+(double4&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) + vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) + vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x + a, v.y + a , v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE double4 operator+(double a, const double4& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) + vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) + vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x + a, v.y + a , v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE double4 operator+(double a, double4&& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) + vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) + vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x + a, v.y + a , v.z + a, v.w + a };
#endif
}

CHTHOLLY_INLINE double4 operator-(const double4& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) - vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) - vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x - a, v.y - a , v.z - a, v.w - a };
#endif
}

CHTHOLLY_INLINE double4 operator-(double4&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) - vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) - vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x - a, v.y - a , v.z - a, v.w - a };
#endif
}

CHTHOLLY_INLINE double4 operator*(const double4& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) * vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) * vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x * a, v.y * a , v.z * a, v.w * a };
#endif
}

CHTHOLLY_INLINE double4 operator*(double4&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) * vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) * vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x * a, v.y * a , v.z * a, v.w * a };
#endif
}

CHTHOLLY_INLINE double4 operator*(double a, const double4& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) * vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) * vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x * a, v.y * a , v.z * a, v.w * a };
#endif
}

CHTHOLLY_INLINE double4 operator*(double a, double4&& v)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) * vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) * vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x * a, v.y * a , v.z * a, v.w * a };
#endif
}

CHTHOLLY_INLINE double4 operator/(const double4& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) / vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) / vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a, v.w / a };
#endif
}

CHTHOLLY_INLINE double4 operator/(double4&& v, double a)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&v.x) / vdupq_n_f64(a);
    float64x2_t simd_ret_high = vld1q_f64(&v.z) / vdupq_n_f64(a);
    double4 simd_ret;
    vst1q_f64(&simd_ret.x, simd_ret_low);
    vst1q_f64(&simd_ret.z, simd_ret_high);
    return simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a, v.w / a };
#endif
}

CHTHOLLY_INLINE double4& operator+=(double4& l, const double4& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) + vld1q_f64(&r.x);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) + vld1q_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    l.w += r.w;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator+=(double4& l, double4&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) + vld1q_f64(&r.x);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) + vld1q_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
    l.w += r.w;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator-=(double4& l, const double4& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) - vld1q_f64(&r.x);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) - vld1q_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    l.w -= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator-=(double4& l, double4&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) - vld1q_f64(&r.x);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) - vld1q_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    l.w -= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator*=(double4& l, const double4& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) * vld1q_f64(&r.x);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) * vld1q_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    l.w *= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator*=(double4& l, double4&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) * vld1q_f64(&r.x);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) * vld1q_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x *= r.x;
    l.y *= r.y;
    l.z *= r.z;
    l.w *= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator/=(double4& l, const double4& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) / vld1q_f64(&r.x);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) / vld1q_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    l.w /= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator/=(double4& l, double4&& r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) / vld1q_f64(&r.x);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) / vld1q_f64(&r.z);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x /= r.x;
    l.y /= r.y;
    l.z /= r.z;
    l.w /= r.w;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator+=(double4& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) + vdupq_n_f64(r);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) + vdupq_n_f64(r);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x += r;
    l.y += r;
    l.z += r;
    l.w += r;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator-=(double4& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) - vdupq_n_f64(r);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) - vdupq_n_f64(r);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x -= r;
    l.y -= r;
    l.z -= r;
    l.w -= r;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator*=(double4& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) * vdupq_n_f64(r);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) * vdupq_n_f64(r);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x *= r;
    l.y *= r;
    l.z *= r;
    l.w *= r;
    return l;
#endif
}

CHTHOLLY_INLINE double4& operator/=(double4& l, double r)
{
#if defined(__ARM_NEON__)
    float64x2_t simd_ret_low = vld1q_f64(&l.x) / vdupq_n_f64(r);
    float64x2_t simd_ret_high = vld1q_f64(&l.z) / vdupq_n_f64(r);
    vst1q_f64(&l.x, simd_ret_low);
    vst1q_f64(&l.z, simd_ret_high);
    return l;
#else   
    l.x /= r;
    l.y /= r;
    l.z /= r;
    l.w /= r;
    return l;
#endif
}

}

#endif
