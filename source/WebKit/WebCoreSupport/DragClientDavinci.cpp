/*
 * DragClientDavinci.cpp: DragClientDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "DragClientDavinci.h"

#include "NotImplemented.h"

using namespace WebCore;

namespace WebKit {

void DragClientDavinci::willPerformDragDestinationAction(DragDestinationAction, DragData*)
{
    notImplemented();
}

void DragClientDavinci::willPerformDragSourceAction(DragSourceAction, const IntPoint&, Clipboard*)
{
    notImplemented();
}

DragDestinationAction DragClientDavinci::actionMaskForDrag(DragData*)
{
    notImplemented();
    return DragDestinationActionAny;
}

DragSourceAction DragClientDavinci::dragSourceActionMaskForPoint(const IntPoint&)
{
    notImplemented();
    return DragSourceActionAny;
}

void DragClientDavinci::startDrag(DragImageRef, const IntPoint&, const IntPoint&, Clipboard*, Frame*, bool)
{
    notImplemented();
}

void DragClientDavinci::dragControllerDestroyed()
{
    delete this;
}

} // namespace WebKit
