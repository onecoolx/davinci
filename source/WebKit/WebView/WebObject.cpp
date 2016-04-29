/*
 * WebObject.cpp: Base Object implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "mconfig.h"

#include <new>
#include <stdlib.h>
#include "WebCommon.h"
#include "WebObject.h"

namespace davinci {

void* WebObject::operator new(size_t size) throw()
{
    return malloc(size);
}

void WebObject::operator delete(void* p) throw()
{
    free(p);
}

void* WebObject::operator new[](size_t size) throw ()
{
    return malloc(size);
}

void WebObject::operator delete[](void* p) throw()
{
    free(p);
}

}
