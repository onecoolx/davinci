
#ifndef WTF_Platform_h
#define WTF_Platform_h

#include "mconfig.h"

/* PLATFORM handles OS, operating environment, graphics API, and CPU */
#define PLATFORM(WTF_FEATURE) (defined( WTF_PLATFORM_##WTF_FEATURE ) && WTF_PLATFORM_##WTF_FEATURE)
#define COMPILER(WTF_FEATURE) (defined( WTF_COMPILER_##WTF_FEATURE ) && WTF_COMPILER_##WTF_FEATURE)
#define HAVE(WTF_FEATURE) (defined( HAVE_##WTF_FEATURE ) && HAVE_##WTF_FEATURE)
#define USE(WTF_FEATURE) (defined( WTF_USE_##WTF_FEATURE ) && WTF_USE_##WTF_FEATURE)
#define ENABLE(WTF_FEATURE) (defined( ENABLE_##WTF_FEATURE ) && ENABLE_##WTF_FEATURE)

/* CPU */

/* PLATFORM(PPC) */
#if   defined(__ppc__)     \
	   || defined(__PPC__)     \
   || defined(__powerpc__) \
   || defined(__powerpc)   \
   || defined(__POWERPC__) \
   || defined(_M_PPC)      \
   || defined(__PPC)
#define WTF_PLATFORM_PPC 1
#define WTF_PLATFORM_BIG_ENDIAN 1
#endif

/* PLATFORM(PPC64) */
#if   defined(__ppc64__) \
	   || defined(__PPC64__)
#define WTF_PLATFORM_PPC64 1
#define WTF_PLATFORM_BIG_ENDIAN 1
#endif



/* PLATFORM(X86) */
#if   defined(__i386__) \
   || defined(i386)     \
   || defined(_M_IX86)  \
   || defined(_X86_)    \
   || defined(__THW_INTEL)
#define WTF_PLATFORM_X86 1
#endif

/* PLATFORM(ARM)*/
#if   defined(arm)\
   || defined(__arm__) \
    || defined(ARM) \
    || defined(_ARM_) 
#define WTF_PLATFORM_ARM 1
#if defined(__ARMEB__)
#define WTF_PLATFORM_BIG_ENDIAN 1
#elif !defined(__ARM_EABI__) && !defined(__ARMEB__) && !defined(__VFP_FP__) && !defined(_WIN32_WCE) 
#define WTF_PLATFORM_MIDDLE_ENDIAN 1
#endif
#if !defined(__ARM_EABI__)
#define WTF_PLATFORM_FORCE_PACK 1
#endif
#endif

/* Operating systems - low-level dependencies */
#if   defined(unix)        \
   || defined(__unix)      \
   || defined(__unix__)    
#define WTF_PLATFORM_UNIX 1
#endif

#if defined(_WIN32_WCE)
#define WTF_PLATFORM_WINCE 1
#endif

#if   defined(WIN32) \
   || defined(_WIN32) \
   || defined(__WIN32) \
   || defined(__WIN32__) \
   || defined(WINNT) \
   || defined(__WINNT) \
   || defined(__WINNT__)
#define WTF_PLATFORM_WIN32 1
#endif

/* COMPILER(GCC) */
#if defined(__GNUC__)
#define WTF_COMPILER_GCC 1
#endif

/* COMPILER(MSVC) */
#if defined(_MSC_VER)
#define WTF_COMPILER_MSVC 1
#if _MSC_VER < 1400
#define WTF_COMPILER_MSVC7 1
#endif
#endif

#endif /* WTF_Platform_h */

