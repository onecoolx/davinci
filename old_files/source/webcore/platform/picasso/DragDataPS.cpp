/*
** DragData.cpp DragData implement.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"
#include "PlatformString.h"
#include "DragData.h"
#include "DocumentFragment.h"
#include "Debug.h"

namespace WebCore {

Clipboard* DragData::createClipboard(ClipboardAccessPolicy) const
{
    notImplemented()
    return NULL;
}

bool DragData::containsURL() const
{
    notImplemented()
    return false;
}

bool DragData::containsPlainText() const
{
    notImplemented()
    return false;
}

bool DragData::containsCompatibleContent() const
{
    notImplemented()
    return false;
}

String DragData::asURL(String* title) const
{
    notImplemented()
    return String();
}

String DragData::asPlainText() const
{
    notImplemented()
    return String();
}

void DragData::asFilenames(Vector<String>&) const
{
    notImplemented()
}

Color DragData::asColor() const
{
    notImplemented()
    return Color();
}

PassRefPtr<DocumentFragment> DragData::asFragment(Document*) const
{
    notImplemented()
	return PassRefPtr<DocumentFragment>(0);
}

bool DragData::canSmartReplace() const
{
    notImplemented()
    return false;
}

bool DragData::containsColor() const
{
    notImplemented()
    return false;
}

bool DragData::containsFiles() const
{
    notImplemented()
    return false;
}

}
