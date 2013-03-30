/*
** IconPS.cpp: icon rending implements file.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"

#include <wtf/PassRefPtr.h>
#include "Icon.h"

#include "Debug.h"

namespace WebCore {


Icon::~Icon()
{
}
    
PassRefPtr<Icon> Icon::newIconForFile(const String& filename)
{
    notImplemented();
    return new Icon();
}

void Icon::paint(GraphicsContext*, const IntRect&)
{
    notImplemented();
}

}
