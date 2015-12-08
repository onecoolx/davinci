/*
 * DragImageDavinci.cpp: DragImage implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "DragImage.h"

#include "Image.h"
#include "NotImplemented.h"

namespace WebCore {

IntSize dragImageSize(DragImageRef)
{
    notImplemented();
    return IntSize(0, 0);
}

void deleteDragImage(DragImageRef)
{
    notImplemented();
}

DragImageRef scaleDragImage(DragImageRef image, FloatSize)
{
    notImplemented();
    return image;
}

DragImageRef dissolveDragImageToFraction(DragImageRef image, float)
{
    notImplemented();
    return image;
}

DragImageRef createDragImageFromImage(Image*, ImageOrientationDescription)
{
    notImplemented();
    return 0;
}

DragImageRef createDragImageIconForCachedImageFilename(const String&)
{
    notImplemented();
    return 0;
}

}
