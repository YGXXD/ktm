#ifndef _KTM_SETUP_H_
#define _KTM_SETUP_H_

// debug state
#ifndef NDEBUG
	#define KTM_DEBUG_ENABLE
#endif

// c++ compiler config
#if defined(__clang__) && defined(__GNUC__)
	#define KTM_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__MINGW32__)
	#define KTM_COMPILER_GCC
#elif defined(_MSC_VER)
	#define KTM_COMPILER_MSVC
#else
	#error "Chtholly Engine don't support unkown c++ compiler, it's only support clang++, g++ and visual c++"
#endif

// function Function config
#if defined(KTM_COMPILER_CLANG)
	#define KTM_INLINE __inline__ __attribute__((always_inline))
	#define KTM_NOINLINE __attribute__((noinline))
	#define KTM_FUNC __inline__ __attribute__((always_inline, nothrow, nodebug))
#elif defined(KTM_COMPILER_GCC)
	#define KTM_INLINE __inline__ __attribute__((__always_inline__))
	#define KTM_NOINLINE __attribute__((__noinline__))
	#define KTM_FUNC __inline__ __attribute__((__always_inline__, __nothrow__, __artificial__))
#elif defined(KTM_COMPILER_MSVC)
	#define KTM_INLINE __forceinline
	#define KTM_NOINLINE __declspec(noinline)
	#define KTM_NOTHROW __declspec(nothrow)
	#define KTM_FUNC __forceinline __declspec(nothrow)
#endif



// build engine config
#if defined(KTM_COMPILER_CLANG)
	#define KTM_ENGINE_API __attribute__ ((visibility("default")))
#elif defined(KTM_COMPILER_GCC)
	#if defined(KTM_PLATFORM_WINDOWS)
		#ifdef KTM_BUILD_DLL 
			#define KTM_ENGINE_API __attribute__((dllexport))
		#else
			#define KTM_ENGINE_API __attribute__((dllimport))
		#endif	
	#else
		#define KTM_ENGINE_API __attribute__ ((visibility("default")))	
	#endif
#elif defined(KTM_COMPILER_MSVC)
	#ifdef KTM_BUILD_DLL 
		#define KTM_ENGINE_API __declspec(dllexport) 
	#else
		#define KTM_ENGINE_API __declspec(dllimport) 
	#endif
#endif

#include "Acsi/Acsi.h"

#endif