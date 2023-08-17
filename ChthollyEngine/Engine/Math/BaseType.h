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

CHTHOLLY_INLINE int2 MakeInt2(int x, int y) { return { x, y }; }
CHTHOLLY_INLINE int3 MakeInt3(const int2& v2, int z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE int3 MakeInt3(int2&& v2, int z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE int3 MakeInt3(int x, int y, int z) { return MakeInt3(MakeInt2(x, y), z); }
CHTHOLLY_INLINE int4 MakeInt4(const int3& v3, int w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE int4 MakeInt4(int3&& v3, int w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE int4 MakeInt4(const int2& v2, int z, int w) { return MakeInt4(MakeInt3(v2, z), 2); }
CHTHOLLY_INLINE int4 MakeInt4(int2&& v2, int z, int w) { return MakeInt4(MakeInt3(v2, z), 2); }
CHTHOLLY_INLINE int4 MakeInt4(int x, int y, int z, int w) { return MakeInt4(MakeInt3(MakeInt2(x, y), z), w); }

CHTHOLLY_INLINE float2 MakeFloat2(float x, float y) { return { x, y }; }
CHTHOLLY_INLINE float3 MakeFloat3(const float2& v2, float z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE float3 MakeFloat3(float2&& v2, float z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE float3 MakeFloat3(float x, float y, float z) { return MakeFloat3(MakeFloat2(x, y), z); }
CHTHOLLY_INLINE float4 MakeFloat4(const float3& v3, float w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE float4 MakeFloat4(float3&& v3, float w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE float4 MakeFloat4(const float2& v2, float z, float w) { return MakeFloat4(MakeFloat3(v2, z), 2); }
CHTHOLLY_INLINE float4 MakeFloat4(float2&& v2, float z, float w) { return MakeFloat4(MakeFloat3(v2, z), 2); }
CHTHOLLY_INLINE float4 MakeFloat4(float x, float y, float z, float w) { return MakeFloat4(MakeFloat3(MakeFloat2(x, y), z), w); }

CHTHOLLY_INLINE double2 MakeDouble2(double x, double y) { return { x, y }; }
CHTHOLLY_INLINE double3 MakeDouble3(const double2& v2, double z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE double3 MakeDouble3(double2&& v2, double z) { return { v2.x, v2.y, z }; }
CHTHOLLY_INLINE double3 MakeDouble3(double x, double y, double z) { return MakeDouble3(MakeDouble2(x, y), z); }
CHTHOLLY_INLINE double4 MakeDouble4(const double3& v3, double w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE double4 MakeDouble4(double3&& v3, double w) { return { v3.x, v3.y, v3.z, w }; }
CHTHOLLY_INLINE double4 MakeDouble4(const double2& v2, double z, double w) { return MakeDouble4(MakeDouble3(v2, z), 2); }
CHTHOLLY_INLINE double4 MakeDouble4(double2&& v2, double z, double w) { return MakeDouble4(MakeDouble3(v2, z), 2); }
CHTHOLLY_INLINE double4 MakeDouble4(double x, double y, double z, double w) { return MakeDouble4(MakeDouble3(MakeDouble2(x, y), z), w); }

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

CHTHOLLY_INLINE int3 operator+(const int3& a, const int3& b)
{
#if defined(__ARM_NEON__)
	int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) + 
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE int3 operator+(const int3& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) + 
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE int3 operator+(int3&& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) + 
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE int3 operator+(int3&& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) + 
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE int3 operator-(const int3& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) - 
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE int3 operator-(const int3& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) - 
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE int3 operator-(int3&& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) - 
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE int3 operator-(int3&& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) - 
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE int3 operator*(const int3& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) *
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE int3 operator*(const int3& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) *
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE int3 operator*(int3&& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) *
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE int3 operator*(int3&& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) *
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(0), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE int3 operator/(const int3& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) /
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(1), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE int3 operator/(const int3& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) /
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(1), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE int3 operator/(int3&& a, const int3& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) /
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(1), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE int3 operator/(int3&& a, int3&& b)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(a.z, vsetq_lane_s32(a.y, vsetq_lane_s32(a.x, vdupq_n_s32(0), 0), 1), 2) /
		vsetq_lane_s32(b.z, vsetq_lane_s32(b.y, vsetq_lane_s32(b.x, vdupq_n_s32(1), 0), 1), 2);
    return *(int3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE int3 operator+(const int3& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) +
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE int3 operator+(int3&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) +
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE int3 operator+(int a, const int3& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) +
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE int3 operator+(int a, int3&& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) +
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE int3 operator-(const int3& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) -
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a };
#endif
}

CHTHOLLY_INLINE int3 operator-(int3&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) -
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a };
#endif
}

CHTHOLLY_INLINE int3 operator*(const int3& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) *
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE int3 operator*(int3&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) *
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE int3 operator*(int a, const int3& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) *
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE int3 operator*(int a, int3&& v)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) *
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE int3 operator/(const int3& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) /
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a };
#endif
}

CHTHOLLY_INLINE int3 operator/(int3&& v, int a)
{
#if defined(__ARM_NEON__)
    int32x4_t simd_ret = vsetq_lane_s32(v.z, vsetq_lane_s32(v.y, vsetq_lane_s32(v.x, vdupq_n_s32(0), 0), 1), 2) /
		vdupq_n_s32(a);   
    return *(int3*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a };
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

CHTHOLLY_INLINE float3 operator+(const float3& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) + 
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE float3 operator+(const float3& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) + 
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE float3 operator+(float3&& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) + 
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE float3 operator+(float3&& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) + 
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x + b.x, a.y + b.y, a.z + b.z };
#endif
}

CHTHOLLY_INLINE float3 operator-(const float3& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) - 
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE float3 operator-(const float3& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) - 
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE float3 operator-(float3&& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) - 
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE float3 operator-(float3&& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) - 
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x - b.x, a.y - b.y, a.z - b.z };
#endif
}

CHTHOLLY_INLINE float3 operator*(const float3& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) *
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE float3 operator*(const float3& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) *
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE float3 operator*(float3&& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) *
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE float3 operator*(float3&& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) *
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(0), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x * b.x, a.y * b.y, a.z * b.z };
#endif
}

CHTHOLLY_INLINE float3 operator/(const float3& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) /
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(1), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE float3 operator/(const float3& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) /
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(1), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE float3 operator/(float3&& a, const float3& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) /
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(1), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE float3 operator/(float3&& a, float3&& b)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(a.z, vsetq_lane_f32(a.y, vsetq_lane_f32(a.x, vdupq_n_f32(0), 0), 1), 2) /
		vsetq_lane_f32(b.z, vsetq_lane_f32(b.y, vsetq_lane_f32(b.x, vdupq_n_f32(1), 0), 1), 2);
    return *(float3*)&simd_ret;
#else   
    return { a.x / b.x, a.y / b.y, a.z / b.z };
#endif
}

CHTHOLLY_INLINE float3 operator+(const float3& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) +
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE float3 operator+(float3&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) +
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE float3 operator+(float a, const float3& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) +
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE float3 operator+(float a, float3&& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) +
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x + a, v.y + a, v.z + a };
#endif
}

CHTHOLLY_INLINE float3 operator-(const float3& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) -
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a };
#endif
}

CHTHOLLY_INLINE float3 operator-(float3&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) -
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x - a, v.y - a, v.z - a };
#endif
}

CHTHOLLY_INLINE float3 operator*(const float3& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) *
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE float3 operator*(float3&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) *
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE float3 operator*(float a, const float3& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) *
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE float3 operator*(float a, float3&& v)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) *
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x * a, v.y * a, v.z * a };
#endif
}

CHTHOLLY_INLINE float3 operator/(const float3& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) /
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a };
#endif
}

CHTHOLLY_INLINE float3 operator/(float3&& v, float a)
{
#if defined(__ARM_NEON__)
    float32x4_t simd_ret = vsetq_lane_f32(v.z, vsetq_lane_f32(v.y, vsetq_lane_f32(v.x, vdupq_n_f32(0), 0), 1), 2) /
		vdupq_n_f32(a);
    return *(float3*)&simd_ret;
#else   
    return { v.x / a, v.y / a, v.z / a };
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

}

#endif
