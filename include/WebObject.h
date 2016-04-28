/*
 * WebObject.h: Base Object implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_OBJECT_H_
#define _DAVINCI_OBJECT_H_

namespace davinci {

class EXPORT_API WebObject
{
public:
    virtual ~WebObject() { }

    /* Overridden new and delete operators. */
    void* operator new(size_t) throw();
    void operator delete(void*) throw();

    void* operator new[](size_t) throw();
    void operator delete[](void*) throw();
};

} /* namespace davinci */

#endif /*_DAVINCI_OBJECT_H_*/
