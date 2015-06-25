
#ifndef _NPTYPES_H_
#define _NPTYPES_H_

#include "mconfig.h"

#if defined(ENABLE_PLUGIN) && !defined(HAVE_STDINT_H)

typedef int int32_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;
#if !defined(__cplusplus)
typedef int bool;
#endif

#endif

#endif /* _NPTYPES_H_ */
