/*
 * devel.h: Platform backend develop headers for davinci.
 *
 * Copyright(C) 2018 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_DEVEL_H_
#define _DAVINCI_DEVEL_H_

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

#include "PlatformEventLoop.h"


#endif /*_DAVINCI_DEVEL_H_*/
