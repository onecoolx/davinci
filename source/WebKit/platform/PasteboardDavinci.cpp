/*
 * PasteboardDavinci.cpp: Pasteboard implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "Pasteboard.h"

#include "DocumentFragment.h"
#include "NotImplemented.h"
#include "Range.h"
#include <wtf/text/StringHash.h>

namespace WebCore {

Pasteboard* Pasteboard::generalPasteboard()
{
    static Pasteboard* pasteboard = new Pasteboard();
    return pasteboard;
}

Pasteboard::Pasteboard()
{
    notImplemented();
}

void Pasteboard::writePlainText(const String&, SmartReplaceOption)
{
    notImplemented();
}

void Pasteboard::writeSelection(Range*, bool, Frame*, ShouldSerializeSelectedTextForClipboard)
{
    notImplemented();
}

void Pasteboard::writeURL(const KURL&, const String&, Frame*)
{
    notImplemented();
}

void Pasteboard::writeImage(Node*, const KURL&, const String&)
{
    notImplemented();
}

void Pasteboard::clear()
{
    notImplemented();
}

bool Pasteboard::canSmartReplace()
{
    notImplemented();
    return false;
}

PassRefPtr<DocumentFragment> Pasteboard::documentFragment(Frame*, PassRefPtr<Range>, bool, bool&)
{
    notImplemented();
    return 0;
}

String Pasteboard::plainText(Frame*)
{
    notImplemented();
    return String();
}

PassOwnPtr<Pasteboard> Pasteboard::createForCopyAndPaste()
{
    return adoptPtr(new Pasteboard);
}

PassOwnPtr<Pasteboard> Pasteboard::createPrivate()
{
    return createForCopyAndPaste();
}

#if ENABLE(DRAG_SUPPORT)
PassOwnPtr<Pasteboard> Pasteboard::createForDragAndDrop()
{
    return createForCopyAndPaste();
}

PassOwnPtr<Pasteboard> Pasteboard::createForDragAndDrop(const DragData&)
{
    return createForCopyAndPaste();
}
#endif

bool Pasteboard::hasData()
{
    notImplemented();
    return false;
}

void Pasteboard::clear(const String&)
{
    notImplemented();
}

String Pasteboard::readString(const String&)
{
    notImplemented();
    return String();
}

bool Pasteboard::writeString(const String&, const String&)
{
    notImplemented();
    return false;
}

Vector<String> Pasteboard::types()
{
    notImplemented();
    return Vector<String>();
}

Vector<String> Pasteboard::readFilenames()
{
    notImplemented();
    return Vector<String>();
}

#if ENABLE(DRAG_SUPPORT)
void Pasteboard::setDragImage(DragImageRef, const IntPoint&)
{
    notImplemented();
}
#endif

void Pasteboard::writePasteboard(const Pasteboard&)
{
    notImplemented();
}

}
