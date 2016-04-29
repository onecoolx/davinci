/*
 * WebCommon.h: Common types define for davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_COMMON_H_
#define _DAVINCI_COMMON_H_

#if defined(WIN32)
    #ifdef DLL_EXPORT
        #ifdef EXPORT
            #define EXPORT_API __declspec(dllexport)
        #else
            #define EXPORT_API __declspec(dllimport)
        #endif
    #else
        #define EXPORT_API
    #endif
#else
#define EXPORT_API __attribute__((visibility("default")))
#endif

#include <limits.h>
#if defined(WIN32)
typedef wchar_t UChar;
typedef unsigned char Byte;
typedef unsigned int UInt32;
#else
#include <stdint.h>
typedef uint16_t UChar;
typedef uint8_t Byte;
typedef uint32_t UInt32;
#endif

#define DECLARE_NO_COPY_AND_ASSIGN(name) \
        name(const name&); \
        name& operator=(const name&);

#endif /*_DAVINCI_COMMON_H_*/
