#include <wtf/Platform.h>

#define HAVE_PCREPOSIX 1

#define WTF_CHANGES 1

#if PLATFORM(WIN32)
typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long int  uint64_t;
typedef signed char     int8_t;
typedef short int       int16_t;
typedef int             int32_t;
typedef long long int   int64_t;
typedef int			        intptr_t;
typedef unsigned int        uintptr_t;
#endif

#ifdef __cplusplus
#undef new
#undef delete
#include <wtf/FastMalloc.h>
#endif

