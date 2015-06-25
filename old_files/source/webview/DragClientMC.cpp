/*
** DragClient.cpp: DragClient implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "DragClientMC.h"
#include "DragImage.h"

#include "Debug.h"

namespace WebCore
{

DragClientMC::DragClientMC()
{

}

DragClientMC::~DragClientMC()
{

}

void DragClientMC::willPerformDragDestinationAction(DragDestinationAction, DragData*)
{
    notImplemented();
}

void DragClientMC::willPerformDragSourceAction(DragSourceAction, const IntPoint&, Clipboard*)
{
    notImplemented();
}

DragDestinationAction DragClientMC::actionMaskForDrag(DragData*)
{
    notImplemented();
    return DragDestinationActionNone;
}

DragSourceAction DragClientMC::dragSourceActionMaskForPoint(const IntPoint& windowPoint)
{
    notImplemented();
    return DragSourceActionNone;
}

void DragClientMC::startDrag(DragImageRef dragImage, const IntPoint& dragImageOrigin, 
                                    const IntPoint& eventPos, Clipboard*, Frame*, bool linkDrag)
{
    notImplemented();
}

DragImageRef DragClientMC::createDragImageForLink(KURL&, const String&, Frame*)
{
    notImplemented();
    return NULL;
}

}
