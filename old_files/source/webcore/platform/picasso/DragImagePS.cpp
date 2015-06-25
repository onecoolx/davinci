/*
** DragImagePS.cpp: DragImage implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "DragImage.h"
#include "Debug.h"

namespace WebCore {

IntSize dragImageSize(DragImageRef image)
{
    notImplemented()
    return IntSize();
}

void deleteDragImage(DragImageRef image)
{
    notImplemented()
}

DragImageRef scaleDragImage(DragImageRef, FloatSize scale)
{
    notImplemented()
    return NULL;
}

DragImageRef dissolveDragImageToFraction(DragImageRef image, float delta)
{
    notImplemented()
    return NULL;
}

DragImageRef createDragImageFromImage(Image*)
{
    notImplemented()
    return NULL;
}

DragImageRef createDragImageIconForCachedImage(CachedImage*)
{
    notImplemented()
    return NULL;
}

}
