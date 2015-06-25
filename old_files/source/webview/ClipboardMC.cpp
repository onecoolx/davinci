
#include "config.h"
#include "HashTable.h"
#include "ClipboardPlatform.h"
#include "IntPoint.h"
#include "PlatformString.h"
#include "StringHash.h"
#include "Pasteboard.h"
#include "Debug.h"

namespace WebCore {

ClipboardPlatform::ClipboardPlatform(ClipboardAccessPolicy policy, bool forDragging) 
    : Clipboard(policy, forDragging)
{
}

ClipboardPlatform::~ClipboardPlatform()
{
}

void ClipboardPlatform::clearData(const String& type)
{
    notImplemented();
}

void ClipboardPlatform::clearAllData() 
{
    Pasteboard::generalPasteboard()->clear();
}

String ClipboardPlatform::getData(const String& type, bool& success) const 
{
    notImplemented();
    return ""; 
}

bool ClipboardPlatform::setData(const String& type, const String& data) 
{
    notImplemented();
    return false;
}

// extensions beyond IE's API
HashSet<String> ClipboardPlatform::types() const 
{
    notImplemented();
    HashSet<String> result;
    return result;
}

IntPoint ClipboardPlatform::dragLocation() const 
{ 
    notImplemented();
    return IntPoint(0,0);
}

CachedImage* ClipboardPlatform::dragImage() const 
{
    notImplemented();
    return 0; 
}

void ClipboardPlatform::setDragImage(CachedImage*, const IntPoint&) 
{
    notImplemented();
}

Node* ClipboardPlatform::dragImageElement() 
{
    notImplemented();
    return 0; 
}

void ClipboardPlatform::setDragImageElement(Node*, const IntPoint&)
{
    notImplemented();
}

DragImageRef ClipboardPlatform::createDragImage(IntPoint& dragLoc) const
{ 
    notImplemented();
    return 0;
}

void ClipboardPlatform::declareAndWriteDragImage(Element*, const KURL&, const String&, Frame*) 
{
    notImplemented();
}

void ClipboardPlatform::writeURL(const KURL& url, const String& string, Frame* frame) 
{
    Pasteboard::generalPasteboard()->writeURL(url, string, frame);
}

void ClipboardPlatform::writeRange(Range*, Frame*) 
{
    notImplemented();
}

bool ClipboardPlatform::hasData() 
{
    notImplemented();
    return false;
}

}
