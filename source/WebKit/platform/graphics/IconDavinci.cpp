/*
 * IconDavinci.cpp: Icon implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"

#include "Icon.h"

#include "GraphicsContext.h"
#include "MIMETypeRegistry.h"
#include "NotImplemented.h"
#include <wtf/PassRefPtr.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

Icon::Icon()
{
    notImplemented();
}

Icon::~Icon()
{
}

PassRefPtr<Icon> Icon::createIconForFiles(const Vector<String>&)
{
    notImplemented();
    return 0;
}

void Icon::paint(GraphicsContext*, const IntRect&)
{
    notImplemented();
}

}
