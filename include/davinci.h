/**
 * \file davinci.h
 * \author Zhang Ji Peng (onecoolx@gmail.com)
 * \date 2016/04/26
 *
 * This file includes interfaces of davinci engine.
 *
 \verbatim

    Copyright (C) 2009 ~ 2016 Zhang Ji Peng

    All rights reserved.

    This file is part of Davinci HTML5 engine.

 \endverbatim
 */


#ifndef _DAVINCI_H_
#define _DAVINCI_H_

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
#define EXPORT_API
#endif

#include "DavInput.h"

typedef int DS_CURSOR;  //tmp implements



#endif /*_DAVINCI_H_*/
