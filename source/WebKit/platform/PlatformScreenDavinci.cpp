/*
 * PlatformScreenDavinci.cpp: Screen implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "PlatformScreen.h"

#include "FloatRect.h"
#include "NotImplemented.h"
#include "Widget.h"

#include <wtf/text/CString.h>
#include <wtf/text/WTFString.h>

#include "DavinciGlobal.h"

namespace WebCore {

int screenDepth(Widget*)
{
    return bytesPerPixel() * 8;
}

int screenDepthPerComponent(Widget* widget)
{
    int depth = screenDepth(widget);

    switch (depth) {
    // Special treat 0 as an error, and return 8 bit per component.
    case 0:
    case 24:
    case 32:
        return 8;
    case 8:
        return 2;
    default:
        return depth / 3;
    }
}

bool screenIsMonochrome(Widget* widget)
{
    return screenDepth(widget) < 2;
}

FloatRect screenRect(Widget* widget)
{
    return FloatRect(0, 0, screenWidth(), screenHeight());
}

FloatRect screenAvailableRect(Widget* widget)
{
    return screenRect(widget);
}

void screenColorProfile(ColorProfile&)
{
    notImplemented();
}

}
