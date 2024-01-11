#ifndef _SETUP_BASE_H_
#define _SETUP_BASE_H_

// debug state
#ifndef NDEBUG
	#define CHTHOLLY_DEBUG_ENABLE
#endif

// c++ compiler config
#if defined(__clang__) && defined(__GNUC__)
	#define CHTHOLLY_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__MINGW32__)
	#define CHTHOLLY_COMPILER_GCC
#elif defined(_MSC_VER)
	#define CHTHOLLY_COMPILER_MSVC
#else
	#error "Chtholly Engine don't support unkown c++ compiler, it's only support clang++, g++ and visual c++"
#endif

// function Function config
#if defined(CHTHOLLY_COMPILER_CLANG)
	#define CHTHOLLY_INLINE __inline__ __attribute__((always_inline))
	#define CHTHOLLY_NOINLINE __attribute__((noinline))
	#define CHTHOLLY_FUNC __inline__ __attribute__((always_inline, nothrow, nodebug))
#elif defined(CHTHOLLY_COMPILER_GCC)
	#define CHTHOLLY_INLINE __inline__ __attribute__((__always_inline__))
	#define CHTHOLLY_NOINLINE __attribute__((__noinline__))
	#define CHTHOLLY_FUNC __inline__ __attribute__((__always_inline__, __nothrow__, __artificial__))
#elif defined(CHTHOLLY_COMPILER_MSVC)
	#define CHTHOLLY_INLINE __forceinline
	#define CHTHOLLY_NOINLINE __declspec(noinline)
	#define CHTHOLLY_NOTHROW __declspec(nothrow)
	#define CHTHOLLY_FUNC __forceinline __declspec(nothrow)
#endif



// build engine config
#if defined(CHTHOLLY_COMPILER_CLANG)
	#define CHTHOLLY_ENGINE_API __attribute__ ((visibility("default")))
#elif defined(CHTHOLLY_COMPILER_GCC)
	#if defined(CHTHOLLY_PLATFORM_WINDOWS)
		#ifdef CHTHOLLY_BUILD_DLL 
			#define CHTHOLLY_ENGINE_API __attribute__((dllexport))
		#else
			#define CHTHOLLY_ENGINE_API __attribute__((dllimport))
		#endif	
	#else
		#define CHTHOLLY_ENGINE_API __attribute__ ((visibility("default")))	
	#endif
#elif defined(CHTHOLLY_COMPILER_MSVC)
	#ifdef CHTHOLLY_BUILD_DLL 
		#define CHTHOLLY_ENGINE_API __declspec(dllexport) 
	#else
		#define CHTHOLLY_ENGINE_API __declspec(dllimport) 
	#endif
#endif

#endif
